#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QDialog>
#include "spectrumwidget.h"
#include "prefdialog.h"
#include "settings.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow();
    
signals:
    
public slots:
    //void animate();

private:
    void createActions();
    void createMenus();

    SpectrumWidget *spectrumWidget;

    QAction *quitAct;
    QAction *prefAct;

    QMenu *fileMenu;

    PrefDialog *prefDialog;

private slots:
    void quit();
    void showPrefDialog();
};

#endif // MAINWINDOW_H
