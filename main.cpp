#include "mainwindow.h"
#include <QApplication>

// Yang Yang

// the following code should have used model view controller. Didn't realize until later.
// mainwindow and monopoly are badly coupled and could have been written much cleaner.
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
