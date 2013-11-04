#include <QPaintEvent>
#include "glwidget.h"

#include <QDebug>


GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    // Initialize OpenGL context
    setFormat(QGLFormat(QGL::DoubleBuffer));

    // Set widget size
    //resize(parent->width(), parent->height());

    backgroundColor = QColor(Qt::black);
    gridColor = QColor(Qt::gray);
}


void GLWidget::initializeGL()
{
    // Set clear color buffer = black
    // Here we use Qt's convenience method qglClearColor() instead of OpenGL's glClearColor()
    qglClearColor(backgroundColor);
}


void GLWidget::updateGL()
{
    qDebug() << "updateGL";
    draw();
}


void GLWidget::paintGL()
{
    qDebug() << "paintGL";
    draw();

}


void GLWidget::resizeGL(int width, int height)
{
    qDebug() << "resizeGL";
    // Set the viewport (drawable area) to the entire widget
    glViewport(0, 0, width, height);
}


void GLWidget::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawGrid();


}


// Draw a grid of horizontal/vertical lines
void GLWidget::drawGrid()
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
