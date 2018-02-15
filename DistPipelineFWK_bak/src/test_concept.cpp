//
// Created by morrigan on 15/01/18.
//

#include <iostream>
#include <chrono>

#include "config.h"

using namespace std;
int main (void){
#ifdef CUDA_FOUND
    cout << "CUDA_FOUND: " << CUDA_FOUND << endl;
#endif
    return 0;
}

//t0 = steady_clock::now();
//t1 = steady_clock::now();
//cout << duration_cast<microseconds>(t1 - t0).count() << " us" << endl;