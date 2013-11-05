#ifndef PREFDIALOG_H
#define PREFDIALOG_H

#include <QDialog>
#include "settings.h"

// The PrefDialog class shows a preference dialog

class PrefDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PrefDialog(QWidget *parent, int fftPoints);
    
signals:
    
public slots:
    
};

#endif // PREFDIALOG_H
