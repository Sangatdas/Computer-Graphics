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
QImage image(1241,601,QImage::Format_RGB888);
int sign(int a)
{
    if(a>0)
        return 1;
    else if(a<0)
        return -1;
    else
        return 0;
}

void MainWindow::DDA(float x1, float y1, float x2, float y2)
{
    float x,y,dx,dy,xinc,yinc;
    int L;

    x=x1;
    y=y1;

    dx=x2-x1;
    dy=y2-y1;

    abs(dx)>abs(dy)?L=abs(dx):L=abs(dy);

    xinc=dx/L;
    yinc=dy/L;

    for(int i=0;i<L;i++)
    {
        image.setPixel(x,y,qRgb(255,255,255));

        x+=xinc;
        y+=yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::Bressenham(int x1, int y1, int x2, int y2)
{
    int temp,x,y,dx,dy,e,s1,s2,swap=0;

    x=x1;
    y=y1;

    dx=abs(x2-x1);
    dy=abs(y2-y1);

    s1=sign(x2-x1);
    s2=sign(y2-y1);

    if(dx<dy)
    {
        temp=dx;
        dx=dy;
        dy=temp;
        swap=1;
    }

    e=2*dy-dx;
    for(int i=0;i<dx;i++)
    {
        image.setPixel(x,y,qRgb(255,255,255));
        if(e>=0)
        {
            x+=s1;
            y+=s2;
            e=e+2*(dy-dx);
        }
        else
        {
            if(swap==1)
            {
                y+=s2;
            }
            else
            {
                x+=s1;
            }
            e=e+2*dy;
        }
    }
    ui->label->setPixmap(QPixmap::fromImage(image));

}

void MainWindow::on_pushButton_2_clicked()
{
    x1=ui->textEdit->toPlainText().toInt();
    y1=ui->textEdit_2->toPlainText().toInt();
    h=ui->textEdit_3->toPlainText().toInt();
    w=ui->textEdit_4->toPlainText().toInt();

    DDA(x1+w/2,y1,x1+w,y1+h/2);
    DDA(x1+w,y1+h/2,x1+w/2,y1+h);
    DDA(x1+w/2,y1+h,x1,y1+h/2);
    DDA(x1,y1+h/2,x1+w/2,y1);
}


void MainWindow::on_pushButton_clicked()
{
    x1=ui->textEdit->toPlainText().toInt();
    y1=ui->textEdit_2->toPlainText().toInt();
    h=ui->textEdit_3->toPlainText().toInt();
    w=ui->textEdit_4->toPlainText().toInt();

    Bressenham(x1,y1,x1+w,y1);

    Bressenham(x1+w,y1,x1+w,y1+h);

    Bressenham(x1+w,y1+h,x1,y1+h);

    Bressenham(x1,y1+h,x1,y1);

    Bressenham(x1+w/4,y1+h/4,x1+3*w/4,y1+h/4);

    Bressenham(x1+3*w/4,y1+h/4,x1+3*w/4,y1+3*h/4);

    Bressenham(x1+3*w/4,y1+3*h/4,x1+w/4,y1+3*h/4);

    Bressenham(x1+w/4,y1+3*h/4,x1+w/4,y1+h/4);

}
