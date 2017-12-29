#include "mainwindow.h"
#include "ui_mainwindow.h"

QImage image(931, 651, QImage :: Format_RGB888);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    initialize();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int sign(int x) {
    return x > 0 ? 1 : (x < 0 ? -1 : 0);
}
//Initalize everything...
void MainWindow :: initialize() {
    no_vertex = 0;
    vertex = new int*[10];
    for(int i = 0; i < 10; i++)
        vertex[i] = new int[3];
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 3; j++)
            vertex[i][j] = j == 2 ? 1 : 0;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            translate[i][j] = scale[i][j] = identity_matrix[i][j] =  i == j ? 1.0 : 0.0;
            rotate[i][j] = i == j ? 1.0 : 0.0;
        }
    }
    drawLine(-460, 0, 460, 0);
    drawLine(0, -325, 0, 325);
}
//Multiply matrices...
int **MainWindow :: Multiply(float x[3][3]) {
    int **array = 0;
    array = new int*[no_vertex];
    for(int i = 0; i < no_vertex; i++)
        array[i] = new int[3];
    for(int i = 0; i < no_vertex; i++) {
        for(int j = 0; j < 3; j++) {
            array[i][j] = 0;
            for(int k = 0; k < 3; k++)
                array[i][j] += vertex[i][k] * x[k][j];
        }
    }
    return array;
}
//Line drawing Algorithm...
void MainWindow :: drawLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1), dy = abs(y2 - y1), error;
    int x = x1, y = y1;
    bool interchange = false;
    if(dy > dx) {
        interchange = true;
        int temp = dy;
        dy = dx;
        dx = temp;
    }
    error = 2 * dy - dx;
    for(int i = 0; i < dx; i++) {
        image = plot_point(x, y, qRgb(255, 255, 255), image);
        while(error > 0) {
            if(interchange)
                x += sign(x2-x1);
            else
                y += sign(y2-y1);
            error -= 2 * dx;
        }
        if(interchange)
            y += sign(y2-y1);
        else
            x += sign(x2-x1);
        error += 2 * dy;
    }
}
//Drawing polygon using successive line drawing...
void MainWindow :: drawPolygon() {
    for(int i = 0; i < no_vertex; i++)
        drawLine(vertex[i][0], vertex[i][1], vertex[(i+1)%no_vertex][0], vertex[(i+1)%no_vertex][1]);
}
//For accepting each and every vertex...
void MainWindow::on_pushButton_clicked()
{
    int x = ui->textEdit->toPlainText().toInt();
    int y = ui->textEdit_2->toPlainText().toInt();

    vertex[no_vertex][0] = x;
    vertex[no_vertex++][1] = y;
}
//for drawing polygon...
void MainWindow::on_pushButton_2_clicked()
{
    drawPolygon();
    ui->label->setPixmap(QPixmap :: fromImage(image));
}

//for rotation with respect to an arbitrary point...
void MainWindow::on_pushButton_5_clicked()
{
    int angle = ui->textEdit_3->toPlainText().toInt();
    int xr = ui->textEdit_5->toPlainText().toInt();
    int yr = ui->textEdit_4->toPlainText().toInt();
    float rot = angle * 3.14159273 / 180;

    assign_for_translate(-xr, -yr);
    assign_for_rotate(rot);

    vertex = Multiply(translate);
    vertex = Multiply(rotate);
    assign_for_translate(xr, yr);
    vertex = Multiply(translate);

    drawPolygon();
    ui->label->setPixmap(QPixmap :: fromImage(image));
}

//for reflection about x
void MainWindow::on_pushButton_6_clicked()
{
    identity_matrix[1][1] = -1;
    vertex = Multiply(identity_matrix);

    drawPolygon();
    ui->label->setPixmap(QPixmap :: fromImage(image));
    vertex = Multiply(identity_matrix);
    identity_matrix[1][1] = 1;
}
//for reflection about y
void MainWindow::on_pushButton_7_clicked()
{
    identity_matrix[0][0] = -1;
    vertex = Multiply(identity_matrix);

    drawPolygon();
    ui->label->setPixmap(QPixmap :: fromImage(image));
    vertex = Multiply(identity_matrix);
    identity_matrix[0][0] = 1;
}
//for reflection about line y = x
void MainWindow::on_pushButton_8_clicked()
{
    identity_matrix[0][0] = identity_matrix[1][1] = 0;
    identity_matrix[1][0] = identity_matrix[0][1] = 1;
    vertex = Multiply(identity_matrix);

    drawPolygon();
    ui->label->setPixmap(QPixmap :: fromImage(image));
    vertex = Multiply(identity_matrix);

    identity_matrix[0][0] = identity_matrix[1][1] = 1;
    identity_matrix[1][0] = identity_matrix[0][1] = 0;
}
