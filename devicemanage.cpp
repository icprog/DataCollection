#include "devicemanage.h"

DeviceManage::DeviceManage(QObject *par) : QObject(par)
{

}


DeviceManage::~DeviceManage()
{

}


void DeviceManage::init()
{
    QString com = "COM1";
    int raud = 9600;
    m_ComPool = new ComSerialPool(this);
    m_ComPool->addCom(com, raud);

    for(int i = 0 ; i < 1 ; i++)
    {
        DeviceART* device = new DeviceART(this);
        device->setComName(com);
        device->setAddress(1);
        DeviceThread* dt = new DeviceThread(this);
        connect(dt, DeviceThread::sendBuffSign, m_ComPool, ComSerialPool::sendBuffSlot);
        dt->setIndex(com);
        dt->addDevice(device);
        m_DeviceThreadList.append(dt);
    }
}


void DeviceManage::release()
{
    for(int i = 0 ; i < m_DeviceThreadList.size() ; i++)
    {
        DeviceThread * dt = m_DeviceThreadList.at(i);
        dt->release();
    }
}


void DeviceManage::start()
{
    for(int i = 0 ; i < m_DeviceThreadList.size() ; i++)
    {
        DeviceThread * dt = m_DeviceThreadList.at(i);
        dt->start();
    }
}


void DeviceManage::stop()
{
    for(int i = 0 ; i < m_DeviceThreadList.size() ; i++)
    {
        DeviceThread * dt = m_DeviceThreadList.at(i);
        dt->terminate();
        dt->wait();
    }
}
