#ifndef CONFIGFILE_H
#define CONFIGFILE_H
#include <QCoreApplication>
#include <QFile>
#include <QtXml>
#include <QSettings>
//读写文件工具类
class ConfigFile
{
public:
    ConfigFile();
    //读写sql建表
    static QStringList readSQL();

    //读写ini文件
    static QList<QString> readINI();
    static void writeINI(QList<QString> list);
    //读写XML文件
    static QList<QString> readXML();
    static bool writeXML(QList<QString> list);
    //读写JSON文件
    static QList<QString> readJSON();
    static bool writeJSON(QList<QString> list);
};

#endif // CONFIGFILE_H
