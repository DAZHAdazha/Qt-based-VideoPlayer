#include "addvideo.h"

#include <qboxlayout.h>
#include <qlabel.h>
#include <qnamespace.h>
#include <qpushbutton.h>

Addvideo::Addvideo(QWidget *parent) : QWidget(parent) {
    window = new QWidget(this);
    window->setWindowTitle("Add new video");

    openbutton = new QPushButton(this);
    openbutton->setText("Open");

    QLineEdit *pathField = new QLineEdit();
    QString path = pathField->text();
    dateField = new QLineEdit(this);
    QString date = dateField->text();
    locationField = new QLineEdit(this);
    QString location = locationField->text();

    //Layout of path
    QBoxLayout *pathLayout = new QHBoxLayout();
    pathLayout->addWidget(pathField);
    pathLayout->addWidget(openbutton);
    pathLayout->setMargin(0);

    okButton = new QPushButton(this);
    okButton->setText("OK");
    //TODO:点击OK button以后将field里面的参数传给videoItem
    //参数为Q     QString date, location

    cancelButton = new QPushButton(this);
    cancelButton->setText("Cancel");
    //TODO:点击cancel button以后关闭本页面，不作任何更改

    QBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    pathl = new QLabel(this);
    pathl->setText(path);
    datel = new QLabel(this);
    datel->setText(date);

    // Arrange widgets
    QFormLayout* form = new QFormLayout();
    form->addRow("Video path:", pathLayout);
    form->addRow("Filmed at:", dateField);
    form->addRow("Location:", locationField);

    form->addRow(buttonLayout);
    form->setHorizontalSpacing(10);
    form->setVerticalSpacing(10);
    form->setLabelAlignment(Qt::AlignCenter);

    window->setLayout(form);
    window->show();
}

