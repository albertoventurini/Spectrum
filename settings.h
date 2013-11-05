#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

///////////////////////////////////////////////////////////////
// The Settings class contains global settings that
// will be used by various components.
//
// This class implements a Singleton design pattern, so that
// only one copy of Settings exists.
// Client classes can get a copy of the Settings class by calling
// the static method Settings::getInstance()
///////////////////////////////////////////////////////////////

class Settings : public QObject
{
    Q_OBJECT
public:
    static Settings *getInstance();

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

private:
    Settings(); // private constructor (Singleton pattern)
    static Settings *instance; // unique instance
};

#endif // SETTINGS_H
