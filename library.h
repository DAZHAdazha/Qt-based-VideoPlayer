#ifndef LIBRARY_H
#define LIBRARY_H

#include <QWidget>

class Library : public QWidget {
    Q_OBJECT

   public:
    Library(QWidget *parent = 0);
    ~Library();
};

#endif