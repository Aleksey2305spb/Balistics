#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   QPixmap pix (":/resource/logo.jpg");
   int w = ui->image->width();
   int h = ui->image->height();
   ui->image->setPixmap (pix.scaled (w,h, Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
   delete ui;
}

