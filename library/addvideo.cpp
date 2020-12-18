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
    this->setGeometry(400, 400, 400, 400);
    setWindowTitle("Add New Video");
    openButton = new QPushButton("Open", this);
    connect(openButton, SIGNAL(clicked()), this, SLOT(openFile()));

    pathField = new QLineEdit(this);
    pathField->setReadOnly(true);
    dateField = new QCalendarWidget(this);
    locationField = new QLineEdit(this);
    memoField = new QTextEdit(this);

    QBoxLayout *pathLayout = new QHBoxLayout();
    pathLayout->addWidget(pathField);
    pathLayout->addWidget(openButton);
    pathLayout->setMargin(0);

    okButton = new QPushButton("OK", this);
    okButton->setDisabled(true);
    connect(okButton, SIGNAL(clicked()), this, SLOT(submit()));

    cancelButton = new QPushButton("Cancel", this);
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));

    QBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    QFormLayout *form = new QFormLayout();
    form->addRow("Video path:", pathLayout);
    form->addRow("Filmed at:", dateField);
    form->addRow("Location:", locationField);
    form->addRow("Memory:", memoField);

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
    memoField->clear();
    okButton->setDisabled(true);
}

void Addvideo::cancel() {
    reset();
    hide();
}

void Addvideo::setTagId(int id) {
    m_tagId = id;
}

void Addvideo::submit() {
    QSqlQuery query;
    bool success = true;
    query.prepare(
        "INSERT INTO videos "
        "(title, date, location, path, memo, tag_id) "
        "VALUES (?, ?, ?, ?, ?, ?)");

    QVariantList names;
    QVariantList dates;
    QVariantList locations;
    QVariantList paths;
    QVariantList memos;
    QVariantList tagIds;

    for (int i = 0; i < files.size(); i++) {
        auto path = files[i];
        names << QFileInfo(path).fileName();
        dates << dateField->selectedDate();
        locations << locationField->text();
        paths << path;
        memos << memoField->toPlainText();
        tagIds << m_tagId;
    }

    query.addBindValue(names);
    query.addBindValue(dates);
    query.addBindValue(locations);
    query.addBindValue(paths);
    query.addBindValue(memos);
    query.addBindValue(tagIds);
    qDebug() << tagIds;

    if (query.execBatch()) {
        emit videoAddDone();
        cancel();
    } else {
        qDebug() << query.lastError();
    }
}
