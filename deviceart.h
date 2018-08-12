#ifndef DEVICEART_H
#define DEVICEART_H

#include "devicebase.h"
class DeviceART : public DeviceBase
{
public:
    DeviceART(QObject *par = 0);
    bool DataPacket( ControlType type, QByteArray & data );
    bool UnDataPacket( ControlType type, QByteArray & data );
};

#endif // DEVICEART_H
