#include "settings.h"

// Here we implement a singleton pattern

// Initialize the unique settings instance to NULL
Settings *Settings::instance = NULL;

Settings::Settings()
{
    // Initial settings
    fps = 60;
    gain = 2.5;
    falloff = 10;
    min_fft_point = 0;
    max_fft_point = 1;
}


Settings *Settings::getInstance()
{
    if(instance == NULL) instance = new Settings;
    return instance;
}


void Settings::setFps(int fps)
{
    this->fps = fps;

    // When the FPS change we emit a signal, so that this is caught and handled by the QTimer object
    // that animates the SpectrumWidget
    emit fpsChanged();
}


void Settings::setGain(double gain)
{
    this->gain = gain;
}


void Settings::setFalloff(double falloff)
{
    this->falloff = falloff;
}


void Settings::setMinFftPoint(int m)
{
    min_fft_point = m;
}


void Settings::setMaxFftPoint(int m)
{
    max_fft_point = m;
}

