#include "fftwwrapper.h"
#include <math.h>
#include <QDebug>
#include "settings.h"

FFTWWrapper::FFTWWrapper() :
    p(NULL), out(NULL), fft_out(NULL)
{
}


void FFTWWrapper::init(int buffer_size, Settings *settings)
{
    fft_points = buffer_size;

    // Allocate the out buffer
    fft_out = (fftwf_complex *)fftwf_malloc(sizeof(fftwf_complex) * buffer_size);

    // We set the out size to fft_points/2, because we will use only half of the fft output (the rest is redundants)
    // See here: http://www.fftw.org/fftw3_doc/One_002dDimensional-DFTs-of-Real-Data.html#One_002dDimensional-DFTs-of-Real-Data
    out_size = fft_points / 2;

    out = new float[buffer_size];
    memset(out, 0, sizeof(float)*buffer_size);

    this->settings = settings;
}


FFTWWrapper::~FFTWWrapper()
{
    if(fft_out) fftwf_free(fft_out);
    if(out) delete [] out;
}


void FFTWWrapper::power_spectrum(float *in)
{
    // Compute a 1-dimensional real-to-complex Fourier transform
    p = fftwf_plan_dft_r2c_1d(fft_points, in, fft_out, FFTW_ESTIMATE);
    fftwf_execute(p);
    fftwf_destroy_plan(p);

    // We have the FFT in "fft_out". Now we will apply some transformations
    // to get its power spectrum (magnitude)

    float tmp;
    out_max = 0.0;

    for (int i = 0; i < out_size; i++)
    {
        // Take the magnitude of each frequency bin and normalize it
        tmp = (fft_out[i][1]*fft_out[i][1] + fft_out[i][0]*fft_out[i][0]) / fft_points;

        // Take the cubic root (better than square root, according to Audacious' source code)
        tmp = pow(tmp, (1.0 / 3.0));

        // Calculate dB / 10 and apply some gain
        tmp = settings->gain * log10(tmp + 1);

        // Apply falloff effect
        if(out[i] < tmp) out[i] = tmp; else out[i] -= (out[i] - tmp) / settings->falloff;

        // Calculate max value (for information)
        if(out[i] > out_max) out_max = out[i];
    }

    //qDebug() << out_max;
}
