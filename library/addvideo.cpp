#include "addvideo.h"

#include <qboxlayout.h>
#include <qcalendarwidget.h>
#include <qlabel.h>
#include <qmessagebox.h>
#include <qnamespace.h>
#include <qpushbutton.h>
#include <qsqlerror.h>
#include <qsqlquery.h>

#include <iostream>

using namespace std;

Addvideo::Addvideo(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Add New Video");
    openButton = new QPushButton("Open", this);
    connect(openButton, SIGNAL(clicked()), this, SLOT(openFile()));

    pathField = new QLineEdit(this);
    pathField->setReadOnly(true);
    dateField = new QCalendarWidget(this);
    locationField = new QLineEdit(this);

    // Layout of path
    QBoxLayout *pathLayout = new QHBoxLayout();
    pathLayout->addWidget(pathField);
    pathLayout->addWidget(openButton);
    pathLayout->setMargin(0);

    okButton = new QPushButton("OK", this);
    connect(okButton, SIGNAL(clicked()), this, SLOT(submit()));
    okButton->setDisabled(true);

    cancelButton = new QPushButton("Cancel", this);
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));

    QBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    // Arrange widgets
    QFormLayout *form = new QFormLayout();
    form->addRow("Video path:", pathLayout);
    form->addRow("Filmed at:", dateField);
    form->addRow("Location:", locationField);

    form->addRow(buttonLayout);
    form->setHorizontalSpacing(10);
    form->setVerticalSpacing(10);
    form->setLabelAlignment(Qt::AlignCenter);

    setLayout(form);
}

void Addvideo::openFile() {
    files = QFileDialog::getOpenFileNames(this, tr("Select Video"), ".",
                                          "Video Files (*.mp4 *.mov *.wmv)");
    if (files.isEmpty()) {
        return;
    }

    QString filesDisp;
    QTextStream fileDispStream(&filesDisp);
    for (int i = 0; i < files.size(); i++) {
        fileDispStream << QFileInfo(files[i]).fileName() << "; ";
    }
    pathField->setText(filesDisp);

    QFileInfo info(files[0]);
    okButton->setDisabled(false);
}

void Addvideo::reset() {
    files.clear();
    dateField->showToday();
    pathField->clear();
    locationField->clear();
    okButton->setDisabled(true);
}

void Addvideo::cancel() {
    reset();
    hide();
}

void Addvideo::submit() {
    QSqlQuery query;
    bool success = true;
    for (int i = 0; i < files.size(); i++) {
        query.prepare(
            "INSERT INTO videos "
            "(title, date, location, path, memo) "
            "VALUES (?, ?, ?, ?, ?)");
        auto path = files[i];
        auto date = dateField->selectedDate();
        query.addBindValue(QFileInfo(path).fileName());
        query.addBindValue(date);
        query.addBindValue(locationField->text());
        query.addBindValue(path);
        query.addBindValue("");
        if (!query.exec()) {
            success = false;
            QMessageBox::critical(this, "Error", query.lastError().text());
            break;
        }
        emit videoAdded(query.lastInsertId().toInt());
    }

    if (success) {
        emit videoAddDone();
        cancel();
    } else {
        qDebug() << query.lastError();
    }
}
