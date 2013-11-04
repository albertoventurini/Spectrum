#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    GLWidget(QWidget *parent);

signals:

public slots:
    void updateGL(); // this slot can be used for animations (e.g. it can be connected to a QTimer)

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

private:
    void draw();
    void drawGrid();
    QColor backgroundColor;
    QColor gridColor;

};

#endif // GLWIDGET_H
