#ifndef JSONTOOLS_H
#define JSONTOOLS_H
#include <QCoreApplication>
#include <QtCore>
#include "t_person.h"
#include "CJsonObject.hpp"
#include "cJSON.h"
#include <string>


//JSON数据处理工具类
class JsonTools
{
public:
    JsonTools();
    //构建发送的人员json
    static QJsonObject jsonBuild(QList<t_person> list);
    //函数重载构建统计发送json
    static QJsonObject jsonBuild(QMap<QString,int> map);
    //QJsonObject解析json
    static QList<t_person> jsonParse(QByteArray byteArray);
    //CJsonObject解析json
    static QList<t_person> jsonParse2(QByteArray byteArray);

    //错误或成功的json返回码
    static QJsonObject jsonSend(int code);
};

#endif // JSONTOOLS_H
