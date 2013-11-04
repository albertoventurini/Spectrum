#include <QHBoxLayout>
#include <QTimer>
#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QDialog>
#include <QAction>
#include <QDebug>
#include <QApplication>
#include "mainwindow.h"
#include "spectrumwidget.h"

MainWindow::MainWindow() :
    QMainWindow(0)
{
    // Create a new Settings object
    settings = new Settings();

    // Create a central widget
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    // set initial size
    resize(800, 600);

    // create a new openGL widget
    spectrumWidget = new SpectrumWidget(widget, settings);
    spectrumWidget->resize(width(), height());

    // create a basic layout and add the openGL widget to it
    // (note: if we don't want to use a layout, we have to handle the resizeEvent() function manually
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(spectrumWidget);
    widget->setLayout(layout);

    // Create the preference dialog object, but don't show it
    prefDialog = new PrefDialog(this, settings, spectrumWidget->getFftPoints());

    createActions();
    createMenus();
}


void MainWindow::createActions()
{
    quitAct = new QAction(tr("&Quit"), this);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit the application"));
    connect(quitAct, SIGNAL(triggered()), this, SLOT(quit()));

    prefAct = new QAction(tr("&Preferences"), this);
    prefAct->setStatusTip(tr("Set application preferences"));
    connect(prefAct, SIGNAL(triggered()), this, SLOT(showPrefDialog()));
}


void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(prefAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);
}


void MainWindow::quit()
{
    qApp->exit();
}


void MainWindow::showPrefDialog()
{
    // Show preference dialog
    prefDialog->show();
}
