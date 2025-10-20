#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create the main window
    MainWindow w;
    w.setWindowTitle("Qt Line Segment Detection");

    w.show(); // Show the main window

    return a.exec();
}
