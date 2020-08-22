#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("Cellbit");
    a.setApplicationName("Image Viewer");
    SmartPtr<MainWindow> w = new MainWindow;
    w->show();

    return a.exec();
}
