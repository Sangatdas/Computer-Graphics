#include "circle.h"
#include "ui_circle.h"
#include "math.h"
QImage image(991,491, QImage::Format_RGB888);
Circle::Circle(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Circle)
{
    ui->setupUi(this);
}

Circle::~Circle()
{
    delete ui;
}



int Circle::sign(double a)
{
    if(a>0)
    {
        return 1;
    }
    else if(a<0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}
void Circle::circle_bresen(double x1,double y1,double ra)
{
    double x,y,p,r;
    r=ra;
    x=0;
    y=r;
    QRgb value=qRgb(255,0,0);
    p=3-(2*r);

    for(x=0;x<=y;x++)
    {
    if (p<0)
    {

    p=(p+(4*x)+6);
    }
    else
    {
    y=y-1;
    p=p+(4*(x-y))+10;
    }


    image.setPixel(x1+x,y1-y,value);
    image.setPixel(x1-x,y1-y,value);
    image.setPixel(x1+x,y1+y,value);
    image.setPixel(x1-x,y1+y,value);
    image.setPixel(x1+y,y1-x,value);
    image.setPixel(x1-y,y1-x,value);
    image.setPixel(x1+y,y1+x,value);
    image.setPixel(x1-y,y1+x,value);

    }

   ui->label_4->setPixmap(QPixmap::fromImage(image));

}


void Circle::circle_dda(double xc, double yc, double r)
{

      double xc1,xc2,yc1,yc2,eps,sx,sy;

      double val,i;

      xc1=r;

      yc1=0;

      sx=xc1;

      sy=yc1;

      i=0;

      do{

          val=pow(2,i);

          i++;

          }while(val<r);

      eps = 1/pow(2,i-1);

      do{

          xc2 = xc1 + yc1*eps;
          yc2 = yc1 - eps*xc2;

          image.setPixel(xc+xc2,yc-yc2,qRgb(255,0,0));

          xc1=xc2;

          yc1=yc2;

         }while((yc1-sy)<eps || (sx-xc1)>eps);
     ui->label_4->setPixmap(QPixmap::fromImage(image));
}

void Circle::line_bresen(double x1, double y1, double x2, double y2)
{
    double dx,dy,e;
    double x,y;
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
         image.setPixel(x,y,qRgb(255,0,0));
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
     ui->label_4->setPixmap(QPixmap::fromImage(image));
}

void Circle:: on_pushButton_clicked()
{
    //Bresenham Circle Drawing
    double x1,y1,r;
    x1=ui->textEdit->toPlainText().toDouble();
    y1=ui->textEdit_2->toPlainText().toDouble();
    r=ui->textEdit_3->toPlainText().toDouble();

    circle_bresen(x1,y1,2*r);

}

void Circle::on_pushButton_2_clicked()
{
    //DDA circle drawing
    double x1,y1,r;
    x1=ui->textEdit->toPlainText().toDouble();
    y1=ui->textEdit_2->toPlainText().toDouble();
    r=ui->textEdit_3->toPlainText().toDouble();

    circle_dda(x1,y1,r);
}

void Circle::on_pushButton_3_clicked()
{
    double x1,y1,r;
//Triangle Drawing
    x1=ui->textEdit->toPlainText().toDouble();
    y1=ui->textEdit_2->toPlainText().toDouble();
    r=ui->textEdit_3->toPlainText().toDouble();


    line_bresen(x1-pow(3,0.5)*r,y1+r,x1,y1-2*r);
    line_bresen(x1,y1-2*r,x1+pow(3,0.5)*r,y1+r);
    line_bresen(x1-pow(3,0.5)*r,y1+r,x1+pow(3,0.5)*r,y1+r);
}

