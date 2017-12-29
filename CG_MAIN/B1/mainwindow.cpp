#include "mainwindow.h"
#include "ui_mainwindow.h"

float fabs_u(float a)
{
    if(a<0)
        return a * -1;
    return a;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),image(500,500,QImage::Format_RGB888),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DDA(int x1,int y1,int x2,int y2,int mode)
{
  int flag=0;
  float dx=0,dy=0,L=0;
  dx=x2-x1;
  dy=y2-y1;
  dx=fabs_u(dx);
  dy=fabs_u(dy);
  if(dy>dx)
    L=dy;
  else
    L=dx;
  dx=float((x2-x1))/L;
  dy=float((y2-y1))/L;
  float x=x1,y=y1;
  if(mode==0)
    {
      for(int i=0;i<L;i++)
        {
            image.setPixel(x,y,qRgb(255,0,0));
            x=x+dx;
            y=y+dy;
        }
    }
  else if(mode==1)
    {
      for(int i=0;i<L;i++)
        {
          if(i%2==0)
                image.setPixel(x,y,qRgb(255,0,0));
            x=x+dx;
            y=y+dy;
        }
    }
  else if(mode==2)
  {
      for(int i=0;i<L;i++)
        {
          if(i%6<3)
          {
            image.setPixel(x,y,qRgb(255,0,0));
          }
            x=x+dx;
            y=y+dy;
        }
  }
  else
  {
      for(int i=0;i<L;i++)
        {
          if(i%10 < 5 || i%10==7)
          {
            image.setPixel(x,y,qRgb(255,0,0));
          }
            x=x+dx;
            y=y+dy;
        }

  }
}

void MainWindow::on_pushButton_clicked()
{
    int x1,y1,x2,y2,w;
    x1=ui->textEdit->toPlainText().toInt();
    y1=ui->textEdit_2->toPlainText().toInt();
    x2=ui->textEdit_3->toPlainText().toInt();
    y2=ui->textEdit_4->toPlainText().toInt();
    w=ui->textEdit_5->toPlainText().toInt();    
    float dx,dy;
    dx=y1-y2;
    dy=x2-x1;
    int l = fabs_u(dx) > fabs_u(dy) ? dx : dy;
    dx/=l;
    dy/=l;
    //DDA(x1,y1,x2,y2,0);
    w/=2;
    render(x1,y1,w);
    flood(x1,y1);
    render(x2,y2,w);
    flood(x2,y2);
    int ax,ay,bx,by,cx,cy,ex,ey;
    w;
    ax=x1+w*dx;
    ay=y1+w*dy;
    bx=x2+w*dx;
    by=y2+w*dy;
    cx=x1-w*dx;
    cy=y1-w*dy;
    ex=x2-w*dx;
    ey=y2-w*dy;
    DDA(ax,ay,bx,by,0);
    DDA(ax,ay,cx,cy,0);
    DDA(bx,by,ex,ey,0);
    DDA(cx,cy,ex,ey,0);
    flood((x2+x1)/2,(y2+y1)/2);
    //for(int i=0;i<w;i++)
    //{
    //    DDA(x1+i*dx,y1+i*dy,x2+i*dx,y2+i*dy,0);
    //    DDA(x1-i*dx,y1-i*dy,x2-i*dx,y2-i*dy,0);
    //}
    ui->label_5->setPixmap(QPixmap::fromImage(image));
}



void MainWindow::on_pushButton_2_clicked()
{
    int x1,y1,x2,y2;
    x1=ui->textEdit->toPlainText().toInt();
    y1=ui->textEdit_2->toPlainText().toInt();
    x2=ui->textEdit_3->toPlainText().toInt();
    y2=ui->textEdit_4->toPlainText().toInt();
    DDA(x1,y1,x2,y2,1);
    ui->label_5->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_pushButton_3_clicked()
{
    int x1,y1,x2,y2;
    x1=ui->textEdit->toPlainText().toInt();
    y1=ui->textEdit_2->toPlainText().toInt();
    x2=ui->textEdit_3->toPlainText().toInt();
    y2=ui->textEdit_4->toPlainText().toInt();
    DDA(x1,y1,x2,y2,2);
    ui->label_5->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_pushButton_4_clicked()
{
    int x1,y1,x2,y2;
    x1=ui->textEdit->toPlainText().toInt();
    y1=ui->textEdit_2->toPlainText().toInt();
    x2=ui->textEdit_3->toPlainText().toInt();
    y2=ui->textEdit_4->toPlainText().toInt();
    DDA(x1,y1,x2,y2,3);
    ui->label_5->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_pushButton_5_clicked()
{
    int x1,y1,x2,y2;
    x1=ui->textEdit->toPlainText().toInt();
    y1=ui->textEdit_2->toPlainText().toInt();
    x2=ui->textEdit_3->toPlainText().toInt();
    y2=ui->textEdit_4->toPlainText().toInt();
    DDA(x1,y1,x2,y2,0);
    ui->label_5->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::render(int xc,int yc,int r)
{
    float dy;
    float x=0,y=r;
    while(x<=y)
    {
        image.setPixel(xc+x,yc+y,qRgb(255,0,0));
        image.setPixel(xc+x,yc-y,qRgb(255,0,0));
        image.setPixel(xc-x,yc+y,qRgb(255,0,0));
        image.setPixel(xc-x,yc-y,qRgb(255,0,0));
        image.setPixel(xc+y,yc+x,qRgb(255,0,0));
        image.setPixel(xc+y,yc-x,qRgb(255,0,0));
        image.setPixel(xc-y,yc+x,qRgb(255,0,0));
        image.setPixel(xc-y,yc-x,qRgb(255,0,0));
        dy=-x/y;
        y=y+dy;
        ++x;
    }
}

void MainWindow::flood(int a,int b)
  {
    QRgb c = qRgb(255,0,0);
    if(c!=image.pixel(a,b))
      {
        image.setPixel(a,b,qRgb(255,0,0));
        flood(a+1,b);
        flood(a,b+1);
        flood(a-1,b);
        flood(a,b-1);
        //flood(a+1,b+1);
        //flood(a+1,b-1);
        //flood(a-1,b+1);
        //flood(a-1,b+1);
      }
  }
