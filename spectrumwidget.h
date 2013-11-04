#ifndef SPECTRUMWIDGET_H
#define SPECTRUMWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include "jackclient.h"
#include "fftwwrapper.h"
#include "settings.h"


class SpectrumWidget : public QGLWidget
{
    Q_OBJECT
public:
    SpectrumWidget(QWidget *parent, Settings *settings);
    Settings *settings;

    int getFftPoints() { return fftw_wrapper.out_size; }

signals:

public slots:
    void animate();
    void changeFps();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

private:
    void drawSpectrum();
    void drawGrid();
    QColor backgroundColor;
    QColor gridColor;
    JackClient jackClient;

    FFTWWrapper fftw_wrapper;

    QTimer *animateTimer;
};

#endif // SPECTRUMWIDGET_H
