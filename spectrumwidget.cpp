#include <QPaintEvent>
#include <QDebug>
#include <QTimer>

#include "mainwindow.h"
#include "spectrumwidget.h"
#include "jackclient.h"


SpectrumWidget::SpectrumWidget(QWidget *parent) :
    QGLWidget(parent), jackClient("Spectrum")
{
    // Get the settings instance
    Settings *settings = Settings::getInstance();

    // Initialize OpenGL context
    setFormat(QGLFormat(QGL::DoubleBuffer));

    backgroundColor = QColor(Qt::black);
    gridColor = QColor(Qt::gray);

    // Initialize the FFTW wrapper object
    fftw_wrapper.init(jackClient.buffer_size);

    settings->min_fft_point = 0;
    settings->max_fft_point = fftw_wrapper.out_size;

    // Create the animation timer object
    animateTimer = new QTimer(this);
    connect(animateTimer, SIGNAL(timeout()), this, SLOT(animate()));
    animateTimer->setInterval(1000.0 / (float)settings->fps);


    connect(settings, SIGNAL(fpsChanged()), this, SLOT(changeFps()));
}


// When the FPS change, we change the animateTimer interval
void SpectrumWidget::changeFps()
{
    animateTimer->setInterval(1000.0 / (float)(Settings::getInstance()->fps));
}


void SpectrumWidget::initializeGL()
{
    // Set clear color buffer = black
    // Here we use Qt's convenience method qglClearColor() instead of OpenGL's glClearColor()
    qglClearColor(backgroundColor);

    // Start a timer to animate the widget
    animateTimer->start();
}


void SpectrumWidget::animate()
{
    // Calculate the power spectrum
    if(jackClient.incoming) fftw_wrapper.power_spectrum((float *)jackClient.incoming);

    // Draw it
    updateGL();
}


void SpectrumWidget::resizeGL(int width, int height)
{
    // Set the viewport (drawable area) to the entire widget
    glViewport(0, 0, width, height);
}


void SpectrumWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    //drawGrid();
    drawSpectrum();

}


// Draw a grid of horizontal/vertical lines
void SpectrumWidget::drawGrid()
{
    glBegin(GL_LINES);
    qglColor(gridColor);

    for (GLfloat x = -1; x < 1; x += 0.2)
    {
        glVertex2f(x, -1);
        glVertex2f(x, 1);
    }


    for (GLfloat y = -1; y < 1; y += 0.2)
    {
        glVertex2f(-1, y);
        glVertex2f(1, y);
    }

    glEnd();
}


void SpectrumWidget::drawSpectrum()
{
    if(fftw_wrapper.out)
    {
        Settings *settings = Settings::getInstance();
        int min = settings->min_fft_point;

        // Let's protect ourselves from a potential segfault here: we cannot read more than fftw_wrapper.out_size samples
        int max = settings->max_fft_point > fftw_wrapper.out_size ? fftw_wrapper.out_size : settings->max_fft_point;

        glColor3f(1,1,1);
        glBegin(GL_LINE_STRIP);

        float x, y;
        for(int i = min; i < max; i++)
        {
            // Scale x and y
            x = ((float)(i - min) / (float) (max - min)) * 2 - 1;
            y = fftw_wrapper.out[i] - 1;

            glVertex2f(x, y);
        }


        glEnd();
    }
}
