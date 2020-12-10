#ifndef DEMO_H
#define DEMO_H

#include <QWidget>

namespace Ui {
class Demo;
}

class Demo : public QWidget
{
    Q_OBJECT

public:
    explicit Demo(QWidget *parent = 0);
    ~Demo();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Demo *ui;
};

#endif // DEMO_H
