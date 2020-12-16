#ifndef ADDVIDEO_H
#define ADDVIDEO_H

//#include "videogridmodel.h"

#include <QApplication>
#include <QWidget>
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

   private slots:
    void openFile();
    void cancel();
    void submit();

   private:
    void reset();
    
    QAbstractButton* openButton;
    QLineEdit* pathField;
    QCalendarWidget* dateField;
    QLineEdit* locationField;
    QAbstractButton* okButton;
    QAbstractButton* cancelButton;
};

#endif  // ADDVIDEO_H
