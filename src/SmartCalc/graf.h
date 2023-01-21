#ifndef GRAF_H
#define GRAF_H

#include <QWidget>

namespace Ui {
class graf;
}

class graf : public QWidget
{
    Q_OBJECT

public:
    explicit graf(QWidget *parent = nullptr);
    ~graf();

private:
    Ui::graf *ui;
};

#endif // GRAF_H
