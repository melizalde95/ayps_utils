//
// Created by morrigan on 1/31/17.
//

#ifndef COMPPHYSFWK_OSCILLOSOPE_HPP
#define COMPPHYSFWK_OSCILLOSOPE_HPP

#include <vector>
#include <cmath>
#include <ctime>
#include <string>

#include <gsl/gsl_interp.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "renderer.hpp"
#include "commons.hpp"
#include "osc_device.hpp"

using namespace std;

class Oscilloscope : public Bitmap2DRenderer{

public:
    Oscilloscope(shared_ptr<IOscDevice> src, size_t resolution = 40) :
            Bitmap2DRenderer(), src{src}, Nx{10*resolution}, Ny{8*resolution} {
        v.resize(Nx);
        for(int i = 0; i < Nx; i++){
            v[i].x = i;
            v[i].z = 0;
            v[i].u = 0;
            v[i].v = 0;
        }

        v_scale_idx = 0;
        t_scale_idx = 0;

        for(int i = -12; i <= 12; i++){
            scale.push_back(1*pow(10,(float)i));
            scale.push_back(2*pow(10,(float)i));
            scale.push_back(5*pow(10,(float)i));
            if(i < 0) v_scale_idx += 3;
            if(i < -7) t_scale_idx +=3;
        }
    };

    string getName(){return name;}
    void setName(string new_name){name = new_name;}

    size_t& getNx(){return Nx;};
    size_t& getNy(){return Ny;};

protected:
    void draw_memory(){

        al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_ONE);
        al_clear_to_color(al_map_rgba(0, 0, 0, 50));
        al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ZERO);

        //draw grid
        for(int i = 1; i <= 9; i++) al_draw_line(i*Nx/10,0,i*Nx/10,Ny,al_map_rgb(50,50,50),1);
        for(int i = 1; i <= 7; i++) al_draw_line(0,i*Ny/8,Nx,i*Ny/8,al_map_rgb(50,50,50),1);

        //zero-level line
        al_draw_line(0, ((double)Ny/2+cv),Nx,((double)Ny/2+cv),al_map_rgb(200,200,255),2);

        //get the data
        auto data = src->get_frame();
        if(!data || data->data_y.empty() || data->data_x.empty()) return;

        //save data if requested
        if(save_next_frame) {
            osc_comm::save_data(name, data->data_x, data->data_y);
            save_next_frame = false;
        }

        //interpolate
        auto Npts = data->data_x.size();
        auto interp = shared_ptr<gsl_interp>(gsl_interp_alloc(gsl_interp_linear,Npts),
                                                 [&](gsl_interp* p_ctx) {gsl_interp_free(p_ctx);});

        gsl_interp_init(interp.get(), data->data_x.data(), data->data_y.data(),Npts);
        auto acc = shared_ptr<gsl_interp_accel>(gsl_interp_accel_alloc(), [&](gsl_interp_accel* pa){ gsl_interp_accel_free(pa);});

        //estimate best scale on first packet
        if(auto_adjust_scale){
            v_scale_idx = osc_comm::get_best_scale(data->data_y, scale, 8.0);
            t_scale_idx = osc_comm::get_best_scale(data->data_x, scale, 10.0);
            auto_adjust_scale = false;
        }

        //continuous limits (for interpolation)
        const double x_min = data->data_x.front();
        const double x_max = data->data_x.back();
        //discrete limits (for al_draw_prim)
        int start = 0, end = Nx;

        float y;
        for(double i = 0; i < Nx; i++){

            //transform from OSC coordinate to physical unit
            double x = 10.0*scale[t_scale_idx]*(i - ts)/(double)Nx;
            y = -1;

            if(x < x_min){
                start++;
            }else if(x > x_max){
                end--;
            }else{
                y = gsl_interp_eval(interp.get(), data->data_x.data(), data->data_y.data(), x, acc.get());

                //transform from physical units to OSC coordinate
                y = (double)Ny/2 + cv - y*(double)Ny/(8.0*scale[v_scale_idx]);
            }

            v[i].y = y;
            v[i].color = al_map_rgb(0,255,0);
        }

        if(start < end)
            al_draw_prim(v.data(), nullptr, nullptr, start, end, ALLEGRO_PRIM_LINE_STRIP);

    }

    virtual void msg_proc(const ALLEGRO_EVENT& ev){
        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            mouse_down = true;
        }else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            mouse_down = false;
        }else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES){
            if(mouse_down) {
                cv += ev.mouse.dy;
                ts += ev.mouse.dx;
            }
        }else if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
            if(ev.keyboard.keycode == ALLEGRO_KEY_DOWN){
                if(v_scale_idx > 0)v_scale_idx--;
            }else if(ev.keyboard.keycode == ALLEGRO_KEY_UP){
                if(v_scale_idx < scale.size()-1)v_scale_idx++;
            }else if(ev.keyboard.keycode == ALLEGRO_KEY_LEFT){
                if(t_scale_idx > 0)t_scale_idx--;
            }else if(ev.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                if(t_scale_idx < scale.size()-1)t_scale_idx++;
            }else if(ev.keyboard.keycode == ALLEGRO_KEY_S){
                save_next_frame = true;
            }
        }
    }

protected:
    size_t Nx; //screen width (10)
    size_t Ny; //screen height (8)
    vector<ALLEGRO_VERTEX> v;
    vector<double> scale; //scale factors
    shared_ptr<IOscDevice> src;

    bool mouse_down = false;
    bool save_next_frame = false;
    bool auto_adjust_scale = true; //best initial scale is estimated on first packet
    double cv = 0, ts = 0; //voltage center [volts], time start [sec]
    int v_scale_idx; //voltage scale [volts]
    int t_scale_idx; //time scale [sec]

    string name;
};

#endif //COMPPHYSFWK_OSCILLOSOPE_HPP
