#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>

#include <climits>

#include "prefdialog.h"

#include "settings.h"

//////////////////////////////////////////////////////////////////////////////
// Main constructor
// Inputs:
//   * parent widget
//   * pointer to the global settings object
//   * the number of points (frequency bins) in the FFT. We need this number to set a limit to one of the spinboxes below.
//

PrefDialog::PrefDialog(QWidget *parent, int fftPoints) :
    QDialog(parent)
{
    // Get the Settings instance
    Settings *settings = Settings::getInstance();

    setWindowTitle(tr("Preferences"));

    QLabel *label_fps = new QLabel(this);
    label_fps->setText(tr("Frames Per Second: "));
    QSpinBox *spinbox_fps = new QSpinBox(this);
    spinbox_fps->setValue(settings->fps);

    connect(spinbox_fps, SIGNAL(valueChanged(int)), settings, SLOT(setFps(int)));

    QLabel *label_gain = new QLabel(this);
    label_gain->setText(tr("Gain: "));
    QDoubleSpinBox *spinbox_gain = new QDoubleSpinBox(this);
    spinbox_gain->setValue(settings->gain);
    spinbox_gain->setSingleStep(0.2);

    connect(spinbox_gain, SIGNAL(valueChanged(double)), settings, SLOT(setGain(double)));

    QLabel *label_falloff = new QLabel(this);
    label_falloff->setText(tr("Falloff factor: "));
    QDoubleSpinBox *spinbox_falloff = new QDoubleSpinBox(this);
    spinbox_falloff->setValue(settings->falloff);

    connect(spinbox_falloff, SIGNAL(valueChanged(double)), settings, SLOT(setFalloff(double)));

    QLabel *label_min_fft_point = new QLabel(this);
    label_min_fft_point->setText(tr("Min FFT point: "));
    QSpinBox *spinbox_min_fft_point = new QSpinBox(this);
    spinbox_min_fft_point->setValue(settings->min_fft_point);
    spinbox_min_fft_point->setSingleStep(10);

    connect(spinbox_min_fft_point, SIGNAL(valueChanged(int)), settings, SLOT(setMinFftPoint(int)));

    QLabel *label_max_fft_point = new QLabel(this);
    label_max_fft_point->setText(tr("Max FFT point: "));
    QSpinBox *spinbox_max_fft_point = new QSpinBox(this);
    spinbox_max_fft_point->setMaximum(fftPoints);
    spinbox_max_fft_point->setSingleStep(10);
    spinbox_max_fft_point->setValue(settings->max_fft_point);

    connect(spinbox_max_fft_point, SIGNAL(valueChanged(int)), settings, SLOT(setMaxFftPoint(int)));


    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(label_fps, 0, 0);
    layout->addWidget(spinbox_fps, 0, 1);
    layout->addWidget(label_gain, 1, 0);
    layout->addWidget(spinbox_gain, 1, 1);
    layout->addWidget(label_falloff, 2, 0);
    layout->addWidget(spinbox_falloff, 2, 1);
    layout->addWidget(label_min_fft_point, 3, 0);
    layout->addWidget(spinbox_min_fft_point, 3, 1);
    layout->addWidget(label_max_fft_point, 4, 0);
    layout->addWidget(spinbox_max_fft_point, 4, 1);

    setLayout(layout);

    adjustSize();
    setFixedSize(width(), height());
}
