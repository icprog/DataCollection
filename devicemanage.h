#ifndef DEVICEMANAGE_H
#define DEVICEMANAGE_H


#include "comserialpool.h"
#include "devicethread.h"

class DeviceManage : public QObject
{
public:
    DeviceManage(QObject *par = 0);


    ~DeviceManage();


    void init();    /* 设备管理器初始化 */


    void release();    /* 设备管理器释放 */


    void start();    /* 设备管理器启动 */


    void stop();    /* 设备管理器停止 */


private:
    QList<DeviceThread*> m_DeviceThreadList;


    ComSerialPool *m_ComPool;


};

#endif /* DEVICEMANAGE_H */
