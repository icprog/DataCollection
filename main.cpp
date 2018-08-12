#include <QCoreApplication>
#include "devicemanage.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    DeviceManage dManage(a.parent());
    dManage.init();
    dManage.start();
    //dManage.stop();
   // dManage.release();

    a.exec();

    return 0;
}
