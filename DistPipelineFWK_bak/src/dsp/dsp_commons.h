//
// Created by morrigan on 19/01/18.
//

#ifndef DISTPIPELINEFWK_DSP_COMMONS_H
#define DISTPIPELINEFWK_DSP_COMMONS_H

namespace dsp{
    void print_zero_crossings_vec(const gsl_vector*);
    void print_zero_crossings_mat(const gsl_matrix*);
    void print_vec(const gsl_vector*);
    void print_mat(const gsl_matrix*);

    // A = B * A * Transpose[B]
    void congruence_transform(gsl_matrix* A, const gsl_matrix* B);

    // compute eigenvectors and eigenvalues,
    // A will be filled with it's eigenvectors
    void eigen(gsl_matrix* A, gsl_vector* B);
}

#endif //DISTPIPELINEFWK_DSP_COMMONS_H
