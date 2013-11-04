#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

// The Settings class contains global settings that
// will be used by various components.

class Settings : public QObject
{
    Q_OBJECT
public:
    Settings();

    int fps;
    double gain;
    double falloff;
    int min_fft_point;
    int max_fft_point;

signals:
    void fpsChanged();

public slots:
    void setFps(int fps);
    void setGain(double gain);
    void setFalloff(double falloff);
    void setMinFftPoint(int m);
    void setMaxFftPoint(int m);


};

#endif // SETTINGS_H
