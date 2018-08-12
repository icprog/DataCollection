#include "devicebase.h"

DeviceBase::DeviceBase(QObject *par) : QObject(par)
{
}


QString DeviceBase::getDeviceName()
{
    return(m_DeviceName);
}


DeviceBase::ParamModel DeviceBase::getParamModel()
{
    return(m_ParamModel);
}


void DeviceBase::setComName( QString name )
{
    m_ComName = name;
}


QString DeviceBase::getComName()
{
    return(m_ComName);
}


void DeviceBase::setAddress( int address )
{
    m_Address = address;
}


quint16  DeviceBase::getAddress()
{
    return(m_Address);
}


int DeviceBase::getDeviceParamMax()
{
    return(m_ParamMax);
}


void DeviceBase::addParamInfo( int index, ParamInfo info )
{
    m_ParamInfoMap[index] = info;
}


void DeviceBase::deleteParamInfo( int index )
{
    m_ParamInfoMap.remove( index );
}


QHash<int, DeviceBase::ParamInfo> DeviceBase::getParamInfoList()
{
    return m_ParamInfoMap;
}


QList<DeviceBase::ConfigInfo> DeviceBase::getConfigInfoList()
{
    return(m_DeviceConfigMap);
}


QList<DeviceBase::ControlInfo> DeviceBase::getControlInfoList()
{
    return(m_usedDeviceParamControlMap);
}


void DeviceBase::setDeviceName(const QString name )
{
    m_DeviceName = name;
}


void DeviceBase::setParamModel(const ParamModel model )
{
    m_ParamModel = model;
}


void DeviceBase::setDeviceParamMax( int value )
{
    m_ParamMax = value;
}


void DeviceBase::addDeviceConfig( ConfigInfo type )
{
    m_DeviceConfigMap.append( type );
}


void DeviceBase::addDeviceControl(ControlInfo type)
{
    m_usedDeviceParamControlMap.append( type );
}


QByteArray DeviceBase::getCrc(const QByteArray data)
{
    quint16 crc16 = 0xFFFF;
    for(int i=0; i<data.size(); i++)
    {
        crc16 ^= data[i];
        for(int j=0; j<8; j++)
        {
            if(crc16 & 1)
            {
                crc16 >>= 1;
                crc16 ^= 0xA001;
            }
            else
            {
                crc16 >>= 1;
            }
        }
    }

    QByteArray crcByte;
    crcByte.resize(2);
    memcpy(crcByte.data(),&crc16,sizeof(crc16));
    return crcByte;
}


bool DeviceBase::checkCrc(const QByteArray data)
{
    QByteArray crc16;
    QByteArray buf;
    return true;
}


bool DeviceBase::ModelBelong( ParamModel src, ParamModel dec )
{
    bool rtn = false;
    switch ( src )
    {
    case ALL:
        rtn = true;
        break;
    case Normal:
        rtn = (dec != IO || dec != DO || dec != DI || src == dec);
        break;
    case IO:
        rtn = (dec == DO || dec == DI || src == dec);
        break;
    default:
        if ( src == dec )
            rtn = true;
        break;
    }
    return(rtn);
}


