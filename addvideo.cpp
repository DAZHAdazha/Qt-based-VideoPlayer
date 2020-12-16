#include "addvideo.h"

#include <qboxlayout.h>
#include <qcalendarwidget.h>
#include <qlabel.h>
#include <qnamespace.h>
#include <qpushbutton.h>

#include <iostream>

using namespace std;

Addvideo::Addvideo(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Add New Video");
    openButton = new QPushButton("Open", this);
    connect(openButton, SIGNAL(clicked()), this, SLOT(openFile()));

    pathField = new QLineEdit(this);
    pathField->setDisabled(true);
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
    auto fileName = QFileDialog::getOpenFileName(this, tr("Select Video"), ".",
                                                 "Video Files (*.mp4 *.mov *.wmv)");
    if (fileName.isEmpty()) {
        return;
    }
    pathField->setText(fileName);

    QFileInfo info(fileName);
    auto createdTime = info.birthTime();
    if (createdTime.isValid()) {
        dateField->setSelectedDate(createdTime.date());
    }

    okButton->setDisabled(false);
}

void Addvideo::reset() {
    dateField->showToday();
    pathField->clear();
    locationField->clear();
    okButton->setDisabled(true);
}

void Addvideo::cancel() {
    reset();
    hide();
}

void Addvideo::submit() {}