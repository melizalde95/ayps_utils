//
// Created by morrigan on 2/9/18.
//

#ifndef DISTPIPELINEFWK_DFRFT_CUBLAS_H
#define DISTPIPELINEFWK_DFRFT_CUBLAS_H

#include "dfrft_gsl.h"

class DFrFTCuBLAS: public DFrFTGSL{
public:

    using tBase = DFrFTGSL;

    DFrFTCuBLAS();

    void create_basis(size_t);
    virtual void init_transform(double a);
    virtual void dfrft(std::vector<double>& );

private:
    /*
     * In the constructor we search for CUDA compatible device,
     * and if it is not found, all functions will repeat the
     * DFrFTGSL functionality.
     */
    bool device_found;

};


#endif //DISTPIPELINEFWK_DFRFT_CUBLAS_H
