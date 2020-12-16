#ifndef ADDVIDEO_H
#define ADDVIDEO_H

//#include "videogridmodel.h"

#include <QWidget>
#include <QApplication>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
class QAbstractButton;
class QLabel;
class QLineEdit;
QT_END_NAMESPACE

class Addvideo : public QWidget {
    Q_OBJECT

   public:
    Addvideo(QWidget* parent = 0);
    ~Addvideo(){};

   private:

    QAbstractButton *openbutton;
    QLineEdit* pathField;
    QLineEdit* dateField;
    QLineEdit* locationField;
    QAbstractButton *okButton;
    QAbstractButton *cancelButton;
    QLabel* pathl;
    QLabel* datel;
    QWidget* window;

};


#endif // ADDVIDEO_H
