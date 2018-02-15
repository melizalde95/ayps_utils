//
// Created by morrigan on 2/9/18.
//

#include <cuda_runtime.h>

#include "dfrft_cublas.h"
#include "config.h"
#include "cublas_v2.h"

//todo: do not forget Fa = nullptr trick
//todo: inspect devices in constructor
//todo: add decision if it is better than CPU (run test task),  include all that in IDFrFT

#ifdef HAVE_CUBLAS_V2_H

//todo: remove this fkn macro
#define IDX2C(i,j,ld) (((j)*(ld))+(i))

DFrFTCuBLAS::DFrFTCuBLAS() : tBase() {
    /*
    cudaGetDeviceCount!!!!!!!!!!!
     setActive Device////
    cudaError_t cudaStat;
    cublasStatus_t stat;
    cublasHandle_t handle;
    int i, j;
    float* devPtrA;
    float* a = 0;
    a = (float *)malloc (M * N * sizeof (*a));
    if (!a) {
        printf ("host memory allocation failed");
        return EXIT_FAILURE;
    }
    for (j = 0; j < N; j++) {
        for (i = 0; i < M; i++) {
            a[IDX2C(i,j,M)] = (float)(i * M + j + 1);
        }
    }
    cudaStat = cudaMalloc ((void**)&devPtrA, M*N*sizeof(*a));
    if (cudaStat != cudaSuccess) {
        printf ("device memory allocation failed");
        return EXIT_FAILURE;
    }
    stat = cublasCreate(&handle);
    if (stat != CUBLAS_STATUS_SUCCESS) {
        printf ("CUBLAS initialization failed\n");
        return EXIT_FAILURE;
    }
    stat = cublasSetMatrix (M, N, sizeof(*a), a, M, devPtrA, M);
    if (stat != CUBLAS_STATUS_SUCCESS) {
        printf ("data download failed");
        cudaFree (devPtrA);
        cublasDestroy(handle);
        return EXIT_FAILURE;
    }
    modify (handle, devPtrA, M, N, 1, 2, 16.0f, 12.0f);
    stat = cublasGetMatrix (M, N, sizeof(*a), devPtrA, M, a, M);
    if (stat != CUBLAS_STATUS_SUCCESS) {
        printf ("data upload failed");
        cudaFree (devPtrA);
        cublasDestroy(handle);
        return EXIT_FAILURE;
    }
    cudaFree (devPtrA);
    cublasDestroy(handle);
    for (j = 0; j < N; j++) {
        for (i = 0; i < M; i++) {
            printf ("%7.0f", a[IDX2C(i,j,M)]);
        }
        printf ("\n");
    }
    free(a);


    Read more at: http://docs.nvidia.com/cuda/cublas/index.html#ixzz56b0HWvOf
    Follow us: @GPUComputing on Twitter | NVIDIA on Facebook
     */
}

void DFrFTCuBLAS::create_basis(size_t N){
    tBase::create_basis(N);
}

void DFrFTCuBLAS::init_transform(double a){
    tBase::init_transform(a);
}

void DFrFTCuBLAS::dfrft(std::vector<double>& data){
    tBase::dfrft(data);
}



//***********************************************************************************


/*
 * In the case of CUBLAS is not present, this class shell behave equivalently
 * to it's base class. So when this .cpp will be compiled, all will work, but slowly.
 *
 * todo: this is an ad-hook for students, shell be removed in future
 */
#elif HAVE_CUBLAS_V2_H
DFrFTCuBLAS::DFrFTCuBLAS() : tBase() {}
void DFrFTCuBLAS::create_basis(size_t N){tBase::create_basis(N);}
void DFrFTCuBLAS::init_transform(double a){tBase::init_transform(a);}
void DFrFTCuBLAS::dfrft(std::vector<double>& data){tBase::dfrft(data);}
#endif