#include "graf.h"
#include "ui_graf.h"

graf::graf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::graf)
{
    ui->setupUi(this);
}

graf::~graf()
{
    delete ui;
}
