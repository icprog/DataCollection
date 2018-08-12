#ifndef DEVICETHREAD_H
#define DEVICETHREAD_H


#include <QThread>
#include "deviceart.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <devicebase.h>

class DeviceThread : public QThread
{
    Q_OBJECT
public:
    DeviceThread(QObject *par = 0);


    ~DeviceThread();


    void setIndex(QString index);


    void addDevice(DeviceBase *device);


    void release();


signals:
    void sendBuffSign(const QString index, const QByteArray buff);


protected:
    void run();


private:
    QString m_Index;


    QList<DeviceBase*> m_Device;
};

#endif // DEVICETHREAD_H
