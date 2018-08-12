#include "deviceart.h"

DeviceART::DeviceART(QObject *par) : DeviceBase(par)
{
    setDeviceName("阿尔泰数模转换器");
    setParamModel(Normal);
    setDeviceParamMax(8);
    addDeviceConfig(ConfigInfo(Channel,"通道号"));
    addDeviceControl(ControlInfo(RealData, "实时数据", 2, -1, true, true, 200, false));
}

bool DeviceART::DataPacket( ControlType type, QByteArray & data )
{
    data.clear();
    switch(type)
    {
    case RealData:
        data += getAddress();
        data += QByteArray::fromHex("04 01 00 00 10");
        data += getCrc(data);
        break;
    default:
        break;
    }
    return true;
}

bool DeviceART::UnDataPacket( ControlType type, QByteArray & data )
{
    switch(type)
    {
    case RealData:
        break;
    default:
        break;
    }
    data.clear();
    return true;
}
