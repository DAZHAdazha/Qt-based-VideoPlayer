#ifndef READER_H
#define READER_H

#include <QWidget>

namespace Ui {
class Reader;
}

class Reader : public QWidget
{
    Q_OBJECT

public:
    explicit Reader(QWidget *parent = 0);
    ~Reader();

private:
    Ui::Reader *ui;
};

#endif // READER_H
