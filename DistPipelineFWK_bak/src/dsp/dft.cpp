//
// Created by morrigan on 17/01/18.
//
#include <exception>
#include <stdexcept>
#include <gsl/gsl_fft_real.h>
#include <gsl/gsl_fft_complex.h>

#include "dft.h"

using namespace std;

void
DFT::initialize(size_t N, CONTEXT_TYPE t){

    if(N == 0) throw runtime_error("DFT initialize: N cannot be 0");

    if(t == REAL || t == ALL) {

        auto rwt_deleter = [](gsl_fft_real_wavetable *p) { gsl_fft_real_wavetable_free(p); };
        real_wavetable.reset(gsl_fft_real_wavetable_alloc(N), rwt_deleter);

        auto rws_deleter = [](gsl_fft_real_workspace *p) { gsl_fft_real_workspace_free(p); };
        real_workspace.reset(gsl_fft_real_workspace_alloc(N), rws_deleter);
    }

    if(t == COMPLEX || t == ALL){
        auto cwt_deleter = [](gsl_fft_complex_wavetable* p){gsl_fft_complex_wavetable_free(p); };
        complex_wavetable = tPtrComplexWavetable(gsl_fft_complex_wavetable_alloc(N), cwt_deleter);

        auto cws_deleter = [](gsl_fft_complex_workspace* p){gsl_fft_complex_workspace_free(p);};
        complex_workspace = tPtrComplexWorkspace(gsl_fft_complex_workspace_alloc(N), cws_deleter);
    }
}

bool
DFT::is_initialized(size_t N, CONTEXT_TYPE t){
    if(t == REAL) {
        return (real_wavetable && real_workspace && real_workspace->n == N);
    }else if(t == COMPLEX){
        return (complex_wavetable && complex_workspace && complex_workspace->n == N);
    }else if(t == ALL){
        return is_initialized(N, REAL) && is_initialized(N, COMPLEX);
    }
}

void
DFT::dft(vector<double>& s){
    if(!is_initialized(s.size(), REAL)) throw runtime_error("FFT: REAL context not initialized");

    auto N = real_workspace->n;
    std::vector<double> out(2*N);
    gsl_fft_real_transform(s.data(), 1, N, real_wavetable.get(), real_workspace.get());
    gsl_fft_halfcomplex_unpack(s.data(), out.data(), 1, N);
    s = move(out);
}


void
DFT::ift(std::vector<double>& S){
    if(!is_initialized(S.size()/2, COMPLEX)) throw runtime_error("FFT: COMPLEX context not initialized");

    auto N = real_workspace->n;
    gsl_fft_complex_inverse(S.data(),1,N,complex_wavetable.get(),complex_workspace.get());
}