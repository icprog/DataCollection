#ifndef COMSERIALPOOL_H
#define COMSERIALPOOL_H

#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QString>

class ComSerialPool : public QObject
{
    Q_OBJECT
public:
    static QList<QSerialPortInfo> getSerialPortList();                              /* 获取串口链表 */


    ComSerialPool(QObject *par = 0);


    ~ComSerialPool();


    bool addCom( QString name, int raud );


public slots:
    void sendBuffSlot(const QString name, const QByteArray buff);


private:
    QMap<QString, QSerialPort*> m_ComHandleList;


};

#endif /* COMSERIALPOOL_H */
