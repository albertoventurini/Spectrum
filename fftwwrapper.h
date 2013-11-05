#ifndef FFTWWRAPPER_H
#define FFTWWRAPPER_H

#include <fftw3.h>
#include "settings.h"

class FFTWWrapper
{
public:
    FFTWWrapper();
    ~FFTWWrapper();

    void init(int buffer_size);
    void power_spectrum(float *in); // Calculates the power spectrum

    fftwf_plan p;

    // The "out" buffer contains the power spectrum of the incoming signal
    float *out;
    int out_size;
    float out_max;


private:
    fftwf_complex *fft_out;
    int fft_points;


};

#endif // FFTWWRAPPER_H
