#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "math.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    int **vertex;
    float translate[3][3], scale[3][3], rotate[3][3];
    float identity_matrix[3][3];
    int no_vertex;

    void initialize();

    void drawLine(int, int, int, int);
    //For ploting pixel w.r.t. the co-ordinate system...
    QImage plot_point(int x, int y, QRgb val, QImage image) {
        image.setPixel(x+460, 325-y, val);
        return image;
    }

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void drawPolygon();

    void assign_for_rotate(float angle) {
        rotate[0][0] = rotate[1][1] = cos(angle);
        rotate[1][0] = sin(angle);
        rotate[0][1] = -sin(angle);
    }

    void assign_for_translate(int tx, int ty) {
        translate[2][0] = tx;
        translate[2][1] = ty;
    }

    void assign_for_scale(int sx, int sy) {
        scale[0][0] = sx;
        scale[1][1] = sy;
    }

    int **Multiply(float [3][3]);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
