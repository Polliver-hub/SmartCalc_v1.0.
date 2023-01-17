#include "mainwindow.h"

#include "ui_mainwindow.h"

bool sign = false;
int butt_end = END;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->Button_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  connect(ui->Button_plus, SIGNAL(clicked()), this, SLOT(digits_sign()));
  connect(ui->Button_minus, SIGNAL(clicked()), this, SLOT(digits_sign()));
  connect(ui->Button_separation, SIGNAL(clicked()), this, SLOT(digits_sign()));
  connect(ui->Button_x, SIGNAL(clicked()), this, SLOT(digits_sign()));

  connect(ui->Button_e, SIGNAL(clicked()), this, SLOT(pi_e_clicked()));
  connect(ui->Button_pi, SIGNAL(clicked()), this, SLOT(pi_e_clicked()));

  connect(ui->Button_cos, SIGNAL(clicked()), this, SLOT(function_trig()));
  connect(ui->Button_sin, SIGNAL(clicked()), this, SLOT(function_trig()));
  connect(ui->Button_acos, SIGNAL(clicked()), this, SLOT(function_trig()));
  connect(ui->Button_asin, SIGNAL(clicked()), this, SLOT(function_trig()));
  connect(ui->Button_atan, SIGNAL(clicked()), this, SLOT(function_trig()));
  connect(ui->Button_tan, SIGNAL(clicked()), this, SLOT(function_trig()));
  connect(ui->Button_log, SIGNAL(clicked()), this, SLOT(function_trig()));
  connect(ui->Button_sqrt, SIGNAL(clicked()), this, SLOT(function_trig()));
  connect(ui->Button_ln, SIGNAL(clicked()), this, SLOT(function_trig()));

//  graph_form = new graph();
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_doubleSpinBox_arg_valueChanged(double arg1) { arg = arg1; }

void MainWindow::on_Button_c_clicked() {
  Validate(END);
  ui->result_show->setPlainText("0");
}

void MainWindow::digits_numbers() {
  if (Validate(NUMBER)) {
    QPushButton *button = (QPushButton *)sender();
    ui->label_input->setPlainText(first_num(button->text()));
  }
}

void MainWindow::pi_e_clicked() {
  QString new_label;
  QPushButton *button = (QPushButton *)sender();
  if (button->text() == "Pi")
    new_label = "3.1415926";
  else if (button->text() == "e")
    new_label = "2.7182818";

  if (butt_end == SIGN || butt_end == BOP || butt_end == OPR)
    ui->result_show->setPlainText(ui->result_show->toPlainText() + new_label);
  else
    ui->result_show->setPlainText(new_label);
  sign = false;
  butt_end = NUMBER;
}

void MainWindow::digits_sign() {
  if (Validate(SIGN)) {
    QPushButton *button = (QPushButton *)sender();
    if (ui->result_show->toPlainText() == "0" ||
        ui->result_show->toPlainText() == "(") {
      if (button->text() == "+" || button->text() == "-")
        ui->result_show->setPlainText(button->text());
    } else {
      ui->result_show->setPlainText(ui->result_show->toPlainText() +
          button->text());
    }
  }
}

void MainWindow::on_Button_xy_clicked() {
  if (Validate(SIGN))
    ui->result_show->setPlainText(ui->result_show->toPlainText() + "^");
}

void MainWindow::on_Button_mod_clicked() {
  if (Validate(SIGN))
    ui->result_show->setPlainText(ui->result_show->toPlainText() + " mod ");
}

void MainWindow::on_Button_point_clicked() {
  if (Validate(DOT))
    ui->result_show->setPlainText(ui->result_show->toPlainText() + ".");
}

void MainWindow::on_Button_bracketopening_clicked() {
  if (Validate(BOP)) ui->result_show->setPlainText(first_num("("));
}

void MainWindow::on_Button_bracketclosing_clicked() {
  if (Validate(BCL)) ui->result_show->setPlainText(first_num(")"));
}

void MainWindow::on_Button_args_clicked() {
  if (Validate(BTX)) ui->result_show->setPlainText(first_num("x"));
}

void MainWindow::function_trig() {
  if (Validate(OPR)) {
    QString new_label;
    QPushButton *button = (QPushButton *)sender();
    if (button->text() == "cos")
      new_label = "cos(";
    else if (button->text() == "sin")
      new_label = "sin(";
    else if (button->text() == "sin")
      new_label = "sin(";
    else if (button->text() == "tan")
      new_label = "tan(";
    else if (button->text() == "acos")
      new_label = "acos(";
    else if (button->text() == "asin")
      new_label = "asin(";
    else if (button->text() == "atan")
      new_label = "atan(";
    else if (button->text() == "log")
      new_label = "log(";
    else if (button->text() == "ln")
      new_label = "ln(";
    else if (button->text() == "sqrt")
      new_label = "sqrt(";

    ui->result_show->setPlainText(first_num(new_label));
  }
}

void MainWindow::on_Button_equally_clicked() {
  char str_in1[STACK_DEPTH];
  strcpy(str_in1, ui->result_show->toPlainText().toLocal8Bit().data());
  if (sign)
    on_Button_del_clicked(),
        strcpy(str_in1, ui->result_show->toPlainText().toLocal8Bit().data());
  double rez = 0.0;
  dijkstra_algorithm(str_in1);
  int is_error = 0;
  QString history = ui->result_show->toPlainText();
  bool checkBox = ui->checkBox->isChecked();
  QString str_out = "0";
//  if (checkBox) {
//    is_error = operand(str_in1, &rez, 1);
//    if (!is_error) {
//      Window_Pos();
//      double ranges[4] = {
//          ui->doubleSpinBox_obl_x1->value(), ui->doubleSpinBox_obl_x2->value(),
//          ui->doubleSpinBox_obl_y1->value(), ui->doubleSpinBox_obl_y2->value()};
//      connect(this, SIGNAL(sendPrint(const char*,double*)), graph_form,
//          SLOT(Print(const char*,double*)), Qt::DirectConnection);
//      graph_form->show();
//      emit sendPrint(str_in1, ranges);
//    }
//    butt_end = END;
//  } else {
//    is_error = operand(str_in1, &rez, arg);
//    str_out = QString::number(rez, 'f', 7);
//    rez = QVariant{str_out}.toDouble();
//    str_out = QVariant{rez}.toString();
//    butt_end = EQL;
//    sign = false;
//  }

  switch (is_error) {
    case -1:
      str_out = "стек переполнен";
      break;
    case -2:
      str_out = "недостаточно операндов в стеке";
      break;
    case -3:
      str_out = "неверное значение";
      break;
    case -4:
      str_out = "нечисло";
      break;
    case -5:
      str_out = "бесконечность";
      break;
  }
  ui->result_show->setPlainText(str_out);
  if (!checkBox) history += " = " + str_out;
  ui->result_history->appendPlainText(history);
}

void MainWindow::on_Button_del_clicked() {
  QString new_label = ui->result_show->toPlainText().mid(
      ui->result_show->toPlainText().length(), 1);
  int len = 1;
  if (new_label == '+' || new_label == '-' || new_label == '*' ||
      new_label == '/' || new_label == '^')
    sign = false;

  for (int i = 3; i < 6; i++) {
    new_label = ui->result_show->toPlainText().mid(
        ui->result_show->toPlainText().length() - i, i);
    if (new_label == "ln(")
      len = 3;
    else if (new_label == "cos(" || new_label == "sin(" ||
        new_label == "tan(" || new_label == "log(")
      len = 4;
    else if (new_label == "acos(" || new_label == "asin(" ||
        new_label == "atan(" || new_label == " mod " ||
        new_label == "sqrt(")
      len = 5;
  }

  new_label = ui->result_show->toPlainText().mid(
      ui->result_show->toPlainText().length() - 1, 1);
  if (new_label >= '0' && new_label <= '9')
    butt_end = NUMBER;
  else if (new_label == '+' || new_label == '-' || new_label == '*' ||
      new_label == '/' || new_label == '^' || new_label == ' ')
    butt_end = SIGN, sign = true;
  else if (new_label == '.')
    butt_end = DOT;
  else if (new_label == '(') {
    new_label = ui->result_show->toPlainText().mid(
        ui->result_show->toPlainText().length() - 2, 1);
    if (new_label >= 'a' && new_label <= 'z')
      butt_end = OPR;
    else
      butt_end = BOP;
  } else if (new_label == ')')
    butt_end = BCL;
  else if (new_label == 'x')
    butt_end = BTX;

  new_label = ui->result_show->toPlainText().remove(
      ui->result_show->toPlainText().length() - len, len);
  if (new_label == "") new_label = "0", butt_end = END;
  ui->result_show->setPlainText(new_label);
}

void MainWindow::on_result_show_textChanged() {
  if (ui->result_show->toPlainText().length() > 255) on_Button_del_clicked();
  if (!ui->result_show->toPlainText().contains('x')) {
    arg = 1.0;
    ui->label_arg->setEnabled(false);
    ui->doubleSpinBox_arg->setEnabled(false);
    if (ui->checkBox->isChecked()) {
      on_checkBox_clicked(0);
      ui->checkBox->setChecked(0);
    }
  } else {
    if (!ui->checkBox->isChecked()) {
      arg = ui->doubleSpinBox_arg->value();
      ui->label_arg->setEnabled(true);
      ui->doubleSpinBox_arg->setEnabled(true);
    }
  }
}

void MainWindow::on_checkBox_clicked(bool checked) {
  if (checked) {
    ui->label_arg->setEnabled(false);
    ui->doubleSpinBox_arg->setEnabled(false);
    ui->label_x->setEnabled(true);
    ui->doubleSpinBox_obl_x1->setEnabled(true);
    ui->doubleSpinBox_obl_x2->setEnabled(true);
    ui->label_y->setEnabled(true);
    ui->doubleSpinBox_obl_y1->setEnabled(true);
    ui->doubleSpinBox_obl_y2->setEnabled(true);
  } else {
    if (!ui->result_show->toPlainText().contains('x')) {
      ui->label_arg->setEnabled(false);
      ui->doubleSpinBox_arg->setEnabled(false);
    } else {
      ui->label_arg->setEnabled(true);
      ui->doubleSpinBox_arg->setEnabled(true);
    }
    ui->label_x->setEnabled(false);
    ui->doubleSpinBox_obl_x1->setEnabled(false);
    ui->doubleSpinBox_obl_x2->setEnabled(false);
    ui->label_y->setEnabled(false);
    ui->doubleSpinBox_obl_y1->setEnabled(false);
    ui->doubleSpinBox_obl_y2->setEnabled(false);
  }
}

void MainWindow::Window_Pos() {
  QScreen *screen = QGuiApplication::primaryScreen();
  QRect rect = screen->availableGeometry();
  QPoint center = rect.center();
  center.setX(center.x() - (this->width() + 5));
  center.setY(center.y() - (this->height() / 2));
  move(center);
}

QString MainWindow::first_num(QString butt) {
  return (ui->result_show->toPlainText() == "0")
         ? butt
         : ui->result_show->toPlainText() + butt;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  int key = event->key();
  QString str = event->text();
  if (key >= Qt::Key_0 && key <= Qt::Key_9) {
    this->findChild<QPushButton *>("Button_" + str)->click();
  } else if (key == Qt::Key_Backspace) {
    ui->Button_del->click();
  } else if (key == Qt::Key_Delete) {
    ui->Button_c->click();
  } else if (key == Qt::Key_Plus) {
    ui->Button_plus->click();
  } else if (key == Qt::Key_Minus) {
    ui->Button_minus->click();
  } else if (key == Qt::Key_Asterisk) {
    ui->Button_x->click();
  } else if (key == Qt::Key_ParenLeft) {
    ui->Button_bracketopening->click();
  } else if (key == Qt::Key_ParenRight) {
    ui->Button_bracketclosing->click();
  } else if (key == Qt::Key_Slash) {
    ui->Button_separation->click();
  } else if (key == Qt::Key_Period || key == Qt::Key_Comma) {
    ui->Button_point->click();
  } else if (key == Qt::Key_V && event->modifiers() & Qt::ControlModifier) {
    ui->result_show->setPlainText(QGuiApplication::clipboard()->text());
    ui->Button_equally->click();
  } else if (key == Qt::Key_Enter || key == Qt::Key_Return) {
    ui->Button_equally->click();
  } else if (key == Qt::Key_Escape) {
  }
}

bool MainWindow::Validate(int clicked_button) {
  bool rez = false;
  if (butt_end == END) ui->result_show->setPlainText("0");
  switch (clicked_button) {
    case END:
      rez = true;
      sign = false;
      break;
    case NUMBER:
      if (butt_end != BTX && butt_end != BCL && butt_end != EQL) {
        rez = true;
        sign = false;
      }
      break;
    case SIGN:
      if (butt_end != DOT) {
        rez = true;
        sign = true;
      }
      break;
    case DOT:
      if (butt_end == END || butt_end == NUMBER) rez = true;
      break;
    case BOP:
      if (butt_end == END || butt_end == SIGN || butt_end == BOP) {
        rez = true;
        sign = false;
      }
      break;
    case BCL:
      if (butt_end == NUMBER || butt_end == BTX || butt_end == BCL) rez = true;
      break;
    case BTX:
      if (butt_end == END || butt_end == SIGN || butt_end == BOP ||
          butt_end == OPR) {
        rez = true;
        sign = false;
      }
      break;
    case OPR:
      if (butt_end == END || butt_end == SIGN || butt_end == BOP ||
          butt_end == OPR) {
        rez = true;
        sign = false;
      }
      break;
  }

  if (rez) butt_end = clicked_button;
  return rez;
}

void MainWindow::on_doubleSpinBox_obl_x1_valueChanged(double arg1) {
  if (arg1 >= ui->doubleSpinBox_obl_x2->value())
    ui->doubleSpinBox_obl_x1->setValue(ui->doubleSpinBox_obl_x2->value() - 1);
}

void MainWindow::on_doubleSpinBox_obl_x2_valueChanged(double arg1) {
  if (arg1 <= ui->doubleSpinBox_obl_x1->value())
    ui->doubleSpinBox_obl_x2->setValue(ui->doubleSpinBox_obl_x1->value() + 1);
}

void MainWindow::on_doubleSpinBox_obl_y1_valueChanged(double arg1) {
  if (arg1 >= ui->doubleSpinBox_obl_y2->value())
    ui->doubleSpinBox_obl_y1->setValue(ui->doubleSpinBox_obl_y2->value() - 1);
}

void MainWindow::on_doubleSpinBox_obl_y2_valueChanged(double arg1) {
  if (arg1 <= ui->doubleSpinBox_obl_y1->value())
    ui->doubleSpinBox_obl_y2->setValue(ui->doubleSpinBox_obl_y1->value() + 1);
}
