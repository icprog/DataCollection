#include "devicethread.h"

DeviceThread::DeviceThread(QObject* par) : QThread(par)
{

}


DeviceThread::~DeviceThread()
{

}


void DeviceThread::run()
{
    int i = 0;
    while(1)
    {
        foreach (DeviceBase* device, m_Device)
        {
            foreach (DeviceBase::ControlInfo info, device->getControlInfoList())
            {
                if(info.send)
                {
                    device->DataPacket();
                }
            }
        }
        emit sendBuffSign(m_Index, QByteArray::fromHex("04 01 00 00 10"));
        msleep(200);
        if(i++ > 3)
        {
            break;
        }
    }
}


void DeviceThread::setIndex(QString index)
{
    m_Index = index;
}


void DeviceThread::addDevice(DeviceBase *device)
{
    m_Device.append(device);
}


void DeviceThread::release()
{

}
