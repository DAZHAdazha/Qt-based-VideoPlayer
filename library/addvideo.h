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

class AddVideoForm : public QWidget {
    Q_OBJECT

   public:
    AddVideoForm(QWidget* parent = 0);
    ~AddVideoForm(){};
    void setTagId(int id);

   private slots:
    void openFile();
    void cancel();
    void submit();

   signals:
    void videoAdded(int id);
    void videoAddDone();

   private:
    void reset();
    int m_tagId = 0;

    QAbstractButton* openButton;
    QLineEdit* pathField;
    QCalendarWidget* dateField;
    QLineEdit* locationField;
    QTextEdit* memoField;
    QAbstractButton* okButton;
    QAbstractButton* cancelButton;

    QStringList files;
};

#endif  // ADDVIDEO_H
