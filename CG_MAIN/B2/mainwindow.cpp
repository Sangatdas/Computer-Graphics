#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
QImage image(1241,601,QImage::Format_RGB888);
int r=255,g=255,b=255;
QRgb black=qRgb(0,0,0);
QRgb original=black;
QRgb final=qRgb(255,255,255);
MainWindow::~MainWindow()
{
    delete ui;
}

int sign(int a)
{
    if(a>0)
        return 1;
    else if(a<0)
        return -1;
    else
        return 0;
}

void MainWindow::line(int x1, int y1, int x2, int y2)
{
    int dx,dy,sx,sy,e,x,y,swap=0;

    x=x1;
    y=y1;

    dx=abs(x2-x1);
    dy=abs(y2-y1);

    sx=sign(x2-x1);
    sy=sign(y2-y1);

    if(dx<dy)
    {
        int temp=dx;
        dx=dy;
        dy=temp;
        swap=1;
    }

    e=2*dy-dx;
    for(int i=0;i<dx;i++)
    {
        image.setPixel(x,y,qRgb(r,g,b));
        if(e>0)
        {
            x+=sx;
            y+=sy;

            e=e+2*(dy-dx);
        }
        else
        {
            if(swap==1)
                y+=sy;
            else
                x+=sx;
            e=e+2*dy;
        }
    }
    image.setPixel(x,y,qRgb(r,g,b));
    ui->label->setPixmap(QPixmap::fromImage(image));

}
int x1,y1,x2,y2;
int first=0,flag=0;
int xi,yi;
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint p=event->pos();
    if(first==0 && flag==0)
    {
        x1=p.x();
        y1=p.y();
        first=1;
        xi=x1;
        yi=y1;
    }
    else if(first==1 && flag==0)
    {
        x2=p.x();
        y2=p.y();
        line(x1,y1,x2,y2);
        x1=x2;
        y1=y2;
    }
    else
    {
        x1=p.x();
        y1=p.y();
        seed(x1,y1,original,final);
        original=final;
    }
}
void MainWindow::seed(int x, int y, QRgb original, QRgb final)
{
    QRgb color=image.pixel(QPoint(x,y));
    if(color==original)
    {
        image.setPixel(x,y,final);
        seed(x+1,y,original,final);
        seed(x,y+1,original,final);
        seed(x-1,y,original,final);
        seed(x,y-1,original,final);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    r=ui->textEdit->toPlainText().toInt();
    g=ui->textEdit_2->toPlainText().toInt();
    b=ui->textEdit_3->toPlainText().toInt();
    final=qRgb(r,g,b);
}

void MainWindow::on_pushButton_clicked()
{
    line(x2,y2,xi,yi);
    first=0;
    flag=1;
}
