#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);


   MainWindow w;
   w.setWindowTitle("Балистический калькулятор");
   w.show();
   return a.exec();
}
