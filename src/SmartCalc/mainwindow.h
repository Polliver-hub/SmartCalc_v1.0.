#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QClipboard>
#include <QKeyEvent>
#include <QMainWindow>
#include <QScreen>

//#include "graph.h"
#include "polish.h"

#define END 0
#define NUMBER 1  //цифры
#define SIGN 2    //знаки
#define DOT 3     //точка
#define BOP 4     //(
#define BCL 5     //)
#define BTX 6     //х
#define OPR 7     // sin
#define EQL 8

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
//  graph *graph_form;
  double arg;

 private slots:
  void digits_numbers();
  void digits_sign();
  void pi_e_clicked();
  void on_Button_c_clicked();
  void on_Button_del_clicked();
  void on_Button_point_clicked();
  void on_Button_args_clicked();
  void on_Button_bracketopening_clicked();
  void on_Button_bracketclosing_clicked();

  void on_doubleSpinBox_arg_valueChanged(double arg1);
  void on_result_show_textChanged();
  void on_checkBox_clicked(bool checked);
  void Window_Pos();

  QString first_num(QString butt);
  bool Validate(int clicked_button);
  void on_Button_xy_clicked();
  void on_Button_mod_clicked();
  void function_trig();
  void on_Button_equally_clicked();
  void on_doubleSpinBox_obl_x1_valueChanged(double arg1);
  void on_doubleSpinBox_obl_x2_valueChanged(double arg1);
  void on_doubleSpinBox_obl_y1_valueChanged(double arg1);
  void on_doubleSpinBox_obl_y2_valueChanged(double arg1);

 protected:
  virtual void keyPressEvent(QKeyEvent *event);

 signals:
  void sendPrint(const char *str_in1, double *ranges);
};
#endif  // MAINWINDOW_H
