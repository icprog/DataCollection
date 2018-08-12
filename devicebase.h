#ifndef DEVICEBASE_H
#define DEVICEBASE_H

#include <QDebug>
#include <QQueue>

class DeviceBase : public QObject
{
public:
    enum ParamModel                 /* 设备关联参数类型 */
    {
        ALL,                    /* 全部类型参数 */
        Normal,                 /* 非开关量类型参数 */
        IO,                     /* 开关量类型参数 */
        DO,                     /* 输出信号开关量类型参数 */
        DI,                     /* 输入信号开关量类型参数 */
        PH,
        WaterFlow,
        COD,
    };


    enum ControlType               /* 设备操作类型 */
    {
        RealData                /* 实时数据采集 */
    };


    struct ControlInfo             /* 设备操作结构体 */
    {
        //QDateTime time;         /* 操作记录时间 */
        ControlType type;       /* 操作指令集 */
        QString name;           /* 操作名称 */
        int span;               /* 操作间隔 (ms) */
        int number;             /* 操作次数 -1:无限*/
        bool send;              /* 是否发送指令 */
        bool revc;              /* 是否接收指令 */
        int  sleep;             /* 等待时间 (ms) */
        bool control;           /* 是否为手动指令 */
        ControlInfo(ControlType type, QString name, int span, int number, bool send, bool revc, int sleep, bool control)
        {
            this->type = type;
            this->name = name;
            this->span = span;
            this->number = number;
            this->send = send;
            this->revc = revc;
            this->sleep = sleep;
            this->control = control;
        }
    };


    enum ConfigType                 /* 设备参数配置类型 */
    {
        Channel,                /* 通道 */
        RegisterAddress,        /* 寄存器地址 */
        Formula,                /* 公式 */
        Coefficient,            /* 系数 */
        RangeMax,               /* 最大数据量程 */
        RangeMin,               /* 最小数据量程 */
        ADMax,                  /* 最大电流量程 */
        ADMin,                  /* 最小电流量程 */
    };


    struct ConfigInfo
    {
        ConfigType type;
        QString name;
        ConfigInfo(ConfigType type, QString name)
        {
            this->type = type;
            this->name = name;
        }
    };


    struct ParamInfo
    {
        QHash<ConfigType, QString>	data_config;
    };


    DeviceBase(QObject *par);


    QString getDeviceName();                                        /* 获取设备名称 */


    ParamModel getParamModel();                                     /* 获取设备关联参数类型 */


    void setComName( QString name );                          /* 设置设备接口名称 */


    QString getComName();                                     /* 获取设备接口名称 */


    void setAddress( int address );                                 /* 设置设备地址 */


    quint16 getAddress();                                               /* 获取设备地址 */


    int getDeviceParamMax();                                        /* 获取设备支持最大数量 */


    void addParamInfo( int index, ParamInfo info );                 /* 增加设备参数 */


    void deleteParamInfo( int index );                              /* 删除设备参数 */


    QHash<int, ParamInfo> getParamInfoList();                       /* 获取设备参数列表 */


    QList<ConfigInfo> getConfigInfoList();                         /* 获取设备配置列表 */


    QList<ControlInfo> getControlInfoList();                       /* 获取设备控制列表 */


    virtual bool DataPacket( ControlType type, QByteArray & data ) = 0;        /* 封包 */


    virtual bool UnDataPacket( ControlType type, QByteArray & data ) = 0;      /* 解包 */


    static bool ModelBelong( ParamModel src, ParamModel dec );      /* 判断设备关联参数类型 */


protected:
    void setDeviceName(const QString name );                             /* 设置设备名称 */


    void setParamModel( const ParamModel model );                         /* 设置设备关联参数类型 */


    void setDeviceParamMax( int value );                            /* 设置设备支持最大数量 */


    void addDeviceConfig( ConfigInfo type );                        /* 设置设备参数配置 */


    void addDeviceControl( ControlInfo type);                       /* 设置设备控制 */


    QByteArray getCrc(const QByteArray data);


    bool checkCrc(const QByteArray data);


private:
    QString			        m_DeviceName;           /* 设备名称 */
    QString			        m_ComName;              /* 设备接口名称 */
    int			            m_Address;              /* 设备地址 */
    int			            m_ParamMax;             /* 设备支持最大参数数量 */
    ParamModel		        m_ParamModel;           /* 设备关联参数类型 */
    QHash<int, ParamInfo>	m_ParamInfoMap;         /* 设备参数容器 */
    QList<ConfigInfo>	    m_DeviceConfigMap;      /* 设备配置容器 */
    QList<ControlInfo>      m_usedDeviceParamControlMap;      /* 设备支持控制容器 */

};

#endif /* DEVICEBASE_H */
