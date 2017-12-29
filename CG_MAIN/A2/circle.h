#ifndef CIRCLE_H
#define CIRCLE_H

#include <QMainWindow>

namespace Ui {
class Circle;
}

class Circle : public QMainWindow
{
    Q_OBJECT

public:
    explicit Circle(QWidget *parent = 0);
    ~Circle();
    void circle_bresen(double, double ,double);
    void circle_dda(double , double , double);
    void line_bresen(double, double, double, double);
    int sign(double);
    void mh(double& ,double&, double&);
    void md(double& ,double&, double&);
    void mv(double& ,double&, double&);


private:
    Ui::Circle *ui;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
};

#endif // CIRCLE_H
