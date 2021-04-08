#include "Carousel1.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Carousel1 mainWidget;
    mainWidget.AddImageList("://Resources/image1.jpg");
    mainWidget.AddImageList("://Resources/image2.jpg");
    mainWidget.AddImageList("://Resources/image3.jpg");
    mainWidget.AddImageList("://Resources/image4.jpg");
    mainWidget.show();
    mainWidget.StartPlay();
    return a.exec();
}
