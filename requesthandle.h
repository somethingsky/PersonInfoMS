#ifndef REQUESTHANDLE_H
#define REQUESTHANDLE_H
#include <QCoreApplication>
#include <QFile>
#include <QtCore>
#include <QStringList>
#include "sqliteoperator.h"
#include "jsontools.h"
#include "filetools.h"
#define INI 1
#define XML 2
#define JSON 3
//get请求处理父类
class GetRequestHandle
{
public:
    virtual bool personDelete(QMap<QString,QString> map) = 0;
    virtual QJsonObject personAllInfo() = 0;
    virtual QJsonObject personStatistics(QMap<QString,QString> map) = 0;
    virtual ~GetRequestHandle(){}
};
//请求处理子类
class PersonGetRequest:public GetRequestHandle
{
public:
    PersonGetRequest();


    // GetRequestHandle interface
public:
    //人员删除
    bool personDelete(QMap<QString, QString> map);
    //信息查询
    QJsonObject personAllInfo();
    //统计接口处理
    QJsonObject personStatistics(QMap<QString, QString> map);
};


//post请求处理父类
class PostRequestHandle
{
public:
    virtual bool personAdd(QByteArray byteArray) = 0;
    virtual bool personModify(QMap<QString,QString> map, QByteArray byteArray) = 0;
    virtual bool fileUpload(QMap<QString,QString> map, QByteArray byteArray) = 0;
    virtual ~PostRequestHandle(){}
};
//请求处理子类
class PersonPostRequest:public PostRequestHandle
{
public:
    PersonPostRequest();

    // PostRequestHandle interface
public:
    //增加人员信息
    bool personAdd(QByteArray byteArray);
    //修改人员信息
    bool personModify(QMap<QString, QString> map, QByteArray byteArray);
    //上传文件
    bool fileUpload(QMap<QString, QString> map, QByteArray byteArray);
};


#endif // REQUESTHANDLE_H
