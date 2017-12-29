#include "mainwindow.h"
#include "ui_mainwindow.h"

typedef unsigned int outcode;
QImage image(541,641,QImage::Format_RGB888);
QImage image1(511,631,QImage::Format_RGB888);

QRgb white = qRgb(255,255,255);

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

int MainWindow::sign(int a)
{
    if(a<0)
    {
        return -1;
    }
    else if(a>0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


void MainWindow::line(int x1, int y1, int x2, int y2)
{
            int dx,dy,e;
            int x,y;
            int inter,i=0;
            int s1,s2;
             x=x1;
             y=y1;
         dx=abs(x2-x1);
         dy=abs(y2-y1);
         s1=sign(x2-x1);
         s2=sign(y2-y1);
         if(dx<dy)
         {
             int temp=dx;
             dx=dy;
             dy=temp;
             inter=1;
         }
         else
         {
             inter=0;
         }
             e=(2*dy)-dx;
             for(i=0;i<dx;i++)
             {
                 image.setPixel(x,y,white);

                 while(e>=0)
                 {
                     if(inter==1)
                     {
                         x=x+s1;
                     }
                     else
                     {
                         y=y+s2;
                     }
                     e=e-(2*dx);
                 }
                 if(inter==1)
                 {
                     y=y+s2;
                 }
                 else
                 {
                     x=x+s1;
                 }
                 e=e+(2*dy);
             }
             ui->label->setPixmap(QPixmap::fromImage(image));

}

void MainWindow::line1(int x1, int y1, int x2, int y2)
{
            int dx,dy,e;
            int x,y;
            int inter,i=0;
            int s1,s2;
             x=x1;
             y=y1;
         dx=abs(x2-x1);
         dy=abs(y2-y1);
         s1=sign(x2-x1);
         s2=sign(y2-y1);
         if(dx<dy)
         {
             int temp=dx;
             dx=dy;
             dy=temp;
             inter=1;
         }
         else
         {
             inter=0;
         }
             e=(2*dy)-dx;
             for(i=0;i<dx;i++)
             {
                 image1.setPixel(x,y,white);

                 while(e>=0)
                 {
                     if(inter==1)
                     {
                         x=x+s1;
                     }
                     else
                     {
                         y=y+s2;
                     }
                     e=e-(2*dx);
                 }
                 if(inter==1)
                 {
                     y=y+s2;
                 }
                 else
                 {
                     x=x+s1;
                 }
                 e=e+(2*dy);
             }
             ui->label_2->setPixmap(QPixmap::fromImage(image1));
}

int a[10],b[10],c[10],d[10];
int i=0;
int count=4;
int j=0,xmi,ymi,xm,ym;

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QString x= QString::number(event->x());
    QString y= QString::number(event->y());

    if(j<count)
    {
     a[i]=x.toInt();
     b[i]=y.toInt();
    }
     if(j==count)
     {
         xmi=x.toInt();
         ymi= y.toInt();
     }
    j++;
}


void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{

    QString x= QString::number(event->x());
    QString y= QString::number(event->y());
    if(j<count+1)
    {
     c[i]=x.toInt();
     d[i]=y.toInt();
     line(a[i],b[i],c[i],d[i]);
    }

     if(j==count+1)
     {
         xm=x.toInt();
         ym=y.toInt();
     }
      i++;
}


enum{TOP=0x1,BOTTOM=0x2,RIGHT=0x4,LEFT=0x8};

outcode compute(double x0, double y0, double xmin, double xmax, double ymin, double ymax)
{
    outcode temp=0;
    if(x0>xmax)
    {
        temp|=RIGHT;
    }
    if(x0<xmin)
    {
        temp|=LEFT;
    }
    if(y0>ymax)
    {
        temp|=TOP;
    }
    if(y0<ymin)
    {
        temp|=BOTTOM;
    }
    return temp;
}

outcode outcode0=0;
outcode outcode1=0;

void MainWindow::clip(double x0, double y0, double x1, double y1, double xmin, double xmax, double ymin, double ymax)
{
    outcode0= compute(x0,y0,xmin,xmax,ymin,ymax);
    outcode1= compute(x1,y1,xmin,xmax,ymin,ymax);
    int x,y;

    bool done= false;
    bool draw= false;
    do
    {
        if(outcode0==0 && outcode1==0)
        {
            done=true;
            draw=true;
        }
        else if(outcode0 & outcode1)
        {
            done=true;
        }
        else
        {
            outcode equ= outcode0 ? outcode0:outcode1;
            if(equ & TOP)
            {
               y=ymax;
               x=x0 + (ymax-y0)*(x1-x0)/(y1-y0);
            }

            else if(equ & BOTTOM)
            {
               y=ymin;
               x= x0 + (ymin-y0)*(x1-x0)/(y1-y0);
            }

            else if(equ & LEFT)
            {
                x=xmin;
                y= y0 + (xmin-x0)*(y1-y0)/(x1-x0);
            }
            else if(equ & RIGHT)
            {
                x=xmax;
                y= y0 +(xmax-x0)*(y1-y0)/(x1-x0);
            }

            if(equ==outcode0)
            {
                x0=x;
                y0=y;
                outcode0=compute(x0,y0,xmin,xmax,ymin,ymax);
            }
            else
            {
                x1=x;
                y1=y;
                outcode1=compute(x1,y1,xmin,xmax,ymin,ymax);
            }
        }



    }while(done==false);

    if(draw==true)
    {
        line1(x0,y0,x1,y1);
    }

}


void MainWindow::on_pushButton_3_clicked()
{
    count=ui->textEdit->toPlainText().toInt();
}

void MainWindow::on_pushButton_2_clicked()
{
    line(xmi,ymi,xm,ymi);
    line(xmi,ymi,xmi,ym);
    line(xmi,ym,xm,ym);
    line(xm,ym,xm,ymi);
}


void MainWindow::on_pushButton_clicked()
{
    line1(xmi,ymi,xm,ymi);
    line1(xmi,ymi,xmi,ym);
    line1(xmi,ym,xm,ym);
    line1(xm,ym,xm,ymi);

    for(int i=0;i<count;i++)
    {
        clip(a[i],b[i],c[i],d[i],xmi,xm,ymi,ym);
    }
}
