#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Arrow_ballistics.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   MainWindow(QWidget *parent = nullptr);
   ~MainWindow();
   ballistics *shot;
private:
   Ui::MainWindow *ui;
public slots:
   void distance_changed (int value);
};
#endif // MAINWINDOW_H
