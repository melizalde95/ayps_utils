//
// Created by morrigan on 31/01/18.
//
#include <iostream>
#include <functional>
#include <cmath>
#include <fstream>

using namespace std;

int N=100;
double dt=0.1;

double s(double t){
    return t*t;
}

double int_s(double t1, double t2){
    return (pow(t2,3.0)-pow(t1,3.0))/3.0;
}

double heaviside(double t){
    if (t<0) return 0;
    return 1;
}

double int_heaviside(double t1, double t2){
    if (t1<0) t1 = 0;
    return t2-t1;
}

double s_approx(double t, function<double(double)> f){
    double  sum=0;

    for(double tk=0;tk<N*dt;tk+=dt){
        sum+=(-s(tk)+s(tk+dt))*f(t - tk);
    }

    return sum;
}

double int_s_approx(double t1, double t2, function<double(double, double)> int_f){
    double  sum=0;

    for(double tk=0;tk<N*dt;tk+=dt){
        sum+=(-s(tk)+s(tk+dt))*int_f(t1 - tk, t2 - tk);
    }

    return sum;
}

int main(int arc, char** argv){

    ofstream file("/home/morrigan/tmp/boinc_fast/clase_1.dat");

    for (double t=0; t < dt*N; t += dt/10.0){
        file << t << " " << s_approx(t, heaviside) << " " << s(t)  << endl;
    }
    file.close();

    //cout << "Integrate approx: " << int_s_approx(0, N*dt, int_heaviside) << endl;
    //cout << "Integrate exact: " << int_s(0, N*dt) << endl;

    return 0;
}

