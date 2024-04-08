#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QLineEdit>
#include <QString>
#include <QtWidgets>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   QPixmap pix (":/resource/logo.jpg");
   int w = ui->image->width();
   int h = ui->image->height();
   ui->image->setPixmap (pix.scaled (w,h, Qt::KeepAspectRatio));
   shot = new ballistics ();

   QString str = QString::number (shot->arrow_->get_arrow_speed());
   ui->lineEdit_speed_ms->setText(str);
   ui->lineEdit_speed_ms->setEnabled(false);

   str = QString::number (shot->arrow_->get_arrow_speed_fps());
   ui->lineEdit_speed_fps->setText(str);
   ui->lineEdit_speed_fps->setEnabled(false);

   str = QString::number (shot->arrow_->get_arrow_weight());
   ui->lineEdit_weight_g->setText(str);
   ui->lineEdit_weight_g->setEnabled(false);

   str = QString::number (shot->arrow_->get_arrow_weight_gn());
   ui->lineEdit_weight_gn->setText(str);
   ui->lineEdit_weight_gn->setEnabled(false);

   str = QString::number (shot->arrow_->get_arrow_d());
   ui->lineEdit_diameter->setText(str);
   ui->lineEdit_diameter->setEnabled(false);

   str = QString::number (shot->arrow_->get_arrow_K_feather());
   ui->lineEdit_feather->setText(str);
   ui->lineEdit_feather->setEnabled(false);

   str = QString::number (0);
   ui->lineEdit_sight->setText(str);
   ui->lineEdit_sight->setEnabled(false);

   ui->sightSlider->setRange(-100,100);
   ui->sightSlider->setSliderPosition(0);
   ui->sightSlider->setEnabled(false);

   str = QString::number(18);
   ui->lineEdit_distance->setText(str);
   ui->lineEdit_distance->setEnabled(false);

   ui->distanceSlider->setRange(5, 100);
   ui->distanceSlider->setSliderPosition(105-18);
   ui->distanceSlider->setEnabled(true);

   QObject::connect (ui->distanceSlider, SIGNAL (valueChanged(int)), this, SLOT (distance_changed(int)));
}


MainWindow::~MainWindow()
{
   delete ui;
   delete shot;
}

void MainWindow::distance_changed(int value)
{
   QString str;
   value = 105 - value;
   str = QString::number(value);
   ui->lineEdit_distance->setText(str);
   value = -(shot->compound_bow_->get_sight(value));
   str = QString::number (value);
   ui->lineEdit_sight->setText(str);
   ui->sightSlider->setSliderPosition(value);
}
