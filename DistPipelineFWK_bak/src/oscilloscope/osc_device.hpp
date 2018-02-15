//
// Created by morrigan on 1/31/17.
//

#ifndef COMPPHYSFWK_OSCILLOSCOPE_ADAPTOR_HPP
#define COMPPHYSFWK_OSCILLOSCOPE_ADAPTOR_HPP

#include "../core/data_packet_types.h"
#include "../core/base_splitter.hpp"

/*
 * The OscFrame includes ready to use oscilloscope dynamic data fields
 * each time oscilloscope asks for data, the new object of tOscFrame
 * is prepared. After the Oscilloscope will not need it, the data
 * is cleaned up automatically by a shared_ptr destructor.
 */
struct OscFrame{
    std::vector<double> data_y;
    std::vector<double> data_x;

    //empty constructor
    OscFrame(){};

    //copy constructor
    OscFrame(const OscFrame& frame){
        this->data_x = frame.data_x;
        this->data_y = frame.data_y;
    };
};

/*
 * There may be other oscilloscope devices, for example for complex data input packets etc.,
 * any other derived from the device below or a completely new one. Therefore,
 * an oscilloscope need not to know what is an exact implementation of this device is given.
 * This implementation needs only to implement the next interface:
 */

struct IOscDevice{
    virtual std::shared_ptr<OscFrame> get_frame() = 0;
    virtual std::string get_x_units() = 0;
    virtual std::string get_y_units() = 0;
};

/*
 * This class interfaces the pipeline filtering system with the oscilloscope renderer.
 * As long as tOscDevice is derived from the BaseNode template, it has it's own thread.
 * Therefore, all public functions shell use BaseNode<>::local_state_mtx to protect
 * simultaneous access to the shared data.
 *
 * The "drop" policy is recommended in a "put" function of tOscDevice class, the packet
 * loss here is not important for oscilloscope, this is just a graphical tool, nothing more.
 */
template<typename tIn>
class OscDevice : public BaseNode<tIn>, public IOscDevice{
    static_assert(std::is_base_of<RealSignalPkt,tIn>(),"The tIn shell be derived from RealSignalPkt class");

public:
    using tBase = BaseNode<tIn>;
    using tPtrIn = std::shared_ptr<tIn>;
    using tPtrFrame = std::shared_ptr<OscFrame>;

    OscDevice(std::string name = "OscDevice"):
            tBase(name),
            x_units("sec"), //seconds by default
            y_units("p.d.u."), //p.d.u is an arbitrary unit or a procedure defined unit
            sampling_rate(1.0),
            new_data(false),
            new_sampling_rate(false){};

    /*
     * This function will copy the most recent last_frame data into the newly allocated
     * output frame in a thread safe manner. Direct access to the last_frame is not thread safe
     * because t's data would be accessible from any other thread while it is changing
     */
    tPtrFrame get_frame(){
        //lock mutex until the function returns
        std::unique_lock<std::mutex> lck(tBase::local_state_mtx);

        //no new packets arrived yet, no matter if a sampling rate
        //has changed, it will be applied to the next new packet
        if(!new_data)
            //at the beginning the last_frame is null so we can't dereference it
            return last_frame ? tPtrFrame(new OscFrame(*last_frame)) : nullptr;

        //keep old data_x if there already exist a frame
        if(!last_frame) last_frame = tPtrFrame(new OscFrame);

        //just copy the 'y' data from the input packet
        if(new_data) last_frame->data_y = last_pkt->data;
        auto N = last_frame->data_y.size();

        //usually the data_x does not change, so we won't to renew this
        //data cell by cell each time when not necessary
        if(last_frame->data_x.size() != N || new_sampling_rate){
            //ensure the data size is correct
            if(last_frame->data_x.size() != N) last_frame->data_x.resize(N);

            double t = 0.0;
            //the '+' operation is a bit faster than '/'
            const double dt = 1.0/sampling_rate;
            for(size_t i = 0; t < N; i++) {
                last_frame->data_x[i] = t;
                t += dt;
            }

            //the new sampling rate has been applied
            new_sampling_rate = false;
        }

        //the 'last_frame' is already renewed so if get_frame will be called before
        //next process_usr_msg, the already known last_frame data copy will be returned,
        //therefore there is no need to keep the last_pkt any more
        last_pkt.reset();

        //frame renewed, no new data
        new_data = false;

        return tPtrFrame(new OscFrame(*last_frame));
    }

    void set_sampling_rate(double x){
        //lock mutex until the function returns
        std::unique_lock<std::mutex> lck(tBase::local_state_mtx);
        sampling_rate = x;
        new_sampling_rate = true;
    }

    std::string get_x_units(){
        //lock mutex until the function returns
        std::unique_lock<std::mutex> lck(tBase::local_state_mtx);
        return x_units;
    }

    std::string get_y_units(){
        //lock mutex until the function returns
        std::unique_lock<std::mutex> lck(tBase::local_state_mtx);
        return y_units;
    }

protected:
    //the current last_pkt is just replaced with the newly arrived
    virtual bool process_usr_msg(tPtrIn&& in_msg){
        //lock mutex until the function returns
        std::unique_lock<std::mutex> lck(tBase::local_state_mtx);
        last_pkt = in_msg;
        new_data = true;
        return true;
    };

/*
 * These fields can be accessed by public functions.
 */
private:
    tPtrIn last_pkt; //keeps last input packet until the get_frame is called
    std::string x_units; //name of the 'x' axis on the oscilloscope
    std::string y_units; //name of the 'y' axis on the oscilloscope

    /*
     * A number of samples per second, where each sample is an 'y' input data cell.
     * It is measured in Hz, that is a number of samples per second
     */
    double sampling_rate;

/*
 * Pure local fields, there is no external access for these ones
 */
private:
    tPtrFrame last_frame;
    bool new_data;
    bool new_sampling_rate;
};

#endif //COMPPHYSFWK_OSCILLOSCOPE_ADAPTOR_HPP
