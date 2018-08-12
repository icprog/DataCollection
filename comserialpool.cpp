#include "comserialpool.h"

ComSerialPool::ComSerialPool(QObject *par) : QObject(par)
{

}


ComSerialPool::~ComSerialPool()
{

}


QList<QSerialPortInfo> ComSerialPool::getSerialPortList()
{
    return( QSerialPortInfo::availablePorts() );
}


bool ComSerialPool::addCom( QString name, int raud )
{
    if(m_ComHandleList.contains( name ))
        return true;

    QSerialPort *handle = NULL;
    bool rtn = false;
    foreach(QSerialPortInfo p , ComSerialPool::getSerialPortList())
    {
        if(p.portName() == name)
        {
            handle = new QSerialPort(this);
            handle->setPort(p);
            rtn = true;
            break;
        }
    }

    if ( handle != NULL && !handle->isOpen())
    {
        handle->open( QIODevice::ReadWrite );
        handle->setBaudRate( raud );
        handle->setParity( QSerialPort::NoParity );
        handle->setDataBits( QSerialPort::Data8 );
        handle->setStopBits( QSerialPort::OneStop );
        handle->setFlowControl( QSerialPort::NoFlowControl );
        handle->clearError();
        handle->clear();
        m_ComHandleList.insert(name, handle);
    }
    return rtn;
}


void ComSerialPool::sendBuffSlot(const QString name, const QByteArray buff)
{
    if(m_ComHandleList.contains( name ))
    {
        m_ComHandleList.find(name).value()->write(buff);
        qDebug() << "aaaa";
    }
}
