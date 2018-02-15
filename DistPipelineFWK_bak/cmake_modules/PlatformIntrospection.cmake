#https://cmake.org/Wiki/CMake:How_To_Write_Platform_Checks

include(CheckIncludeFiles)
include(CheckLibraryExists)

# OpenCL BLAS library (for not NVIDIA cards)

    #OpenCL_FOUND, OpenCL_LIBRARIES
    find_package(OpenCL)
    if(OpenCL_FOUND)
        #CLBLAS_FOUND, CLBLAS_LIBRARIES
        find_package(clBLAS)
            if(CLBLAS_FOUND)
                include_directories(${CLBLAS_INCLUDE_DIRS})
            endif(CLBLAS_FOUND)
        include_directories(${OpenCL_INCLUDE_DIRS})
    endif(OpenCL_FOUND)

# CUDA for NVIDIA cards (faster than OpenCl)

    #CUDA_FOUND, CUDA_LIBRARIES
    find_package(CUDA)
    if(CUDA_FOUND)
        # HAVE_CUBLAS_V2_H, => CUDA_ADD_CUBLAS_TO_TARGET( <target> )
        check_include_files("cublas_v2.h" HAVE_CUBLAS_V2_H)
        include_directories(${CUDA_INCLUDE_DIRS})
    endif(CUDA_FOUND)

# all application is multithreaded and is based on STL threads
find_package(Threads REQUIRED)

# needed for graphics (oscilloscope)
find_package(Allegro REQUIRED)

# a lot of math use GSL
find_package(GSL REQUIRED)
include_directories(${GSL_INCLUDE_DIR})

# system and filesystem are needed for file storage
# Boost thread is for ASIO (see signal_sources)
find_package(Boost COMPONENTS system filesystem thread REQUIRED)





