#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
QImage image(1241,621,QImage::Format_RGB888);
int r=255,g=255,b=255;


void MainWindow::line(float x1, float y1, float x2, float y2)
{
    float dx,dy,xinc,yinc,x,y;
    int L;

    x=x1;
    y=y1;

    dx=(x2-x1);
    dy=(y2-y1);

    if(abs(dx)<dy)
    {
        L=abs(dy);
    }
    else
    {
        L=abs(dx);
    }

    xinc=dx/L;
    yinc=dy/L;

    for(int i=0;i<L;i++)
    {
        image.setPixel(x,y,qRgb(r,g,b));
        x+=xinc;
        y+=yinc;

    }
    ui->label->setPixmap(QPixmap::fromImage(image));

}
int first=0;
int x1,y1,x2,y2;
int xi,yi;
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint p=event->pos();
    if(first==0)
    {
        x1=p.x();
        y1=p.y();
        first=1;
        xi=x1;
        yi=y1;
    }
    else if(first==1)
    {
        x2=p.x();
        y2=p.y();
        line(x1,y1,x2,y2);
        x1=x2;
        y1=y2;
    }
}


void MainWindow::on_pushButton_clicked()
{
    r=ui->textEdit->toPlainText().toInt();
    g=ui->textEdit_2->toPlainText().toInt();
    b=ui->textEdit_3->toPlainText().toInt();
}

void MainWindow::on_pushButton_2_clicked()
{
        line(x2,y2,xi,yi);
        first=0;
}
