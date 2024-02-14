#ifndef FILETOOLS_H
#define FILETOOLS_H
#include <QCoreApplication>
#include <QtCore>
#include <QDir>

//上传文件信息保存工具类
class FileTools
{
public:
    FileTools();
    //解析上传数据
    static bool parseFormData(const QByteArray body, QString boundary, QMap<QString, QVariant> &file);
    //保存文本类型
    static bool saveFileText(QString fileName, QByteArray buffer);
    //保存其他类型
    static bool saveFileOther(QString fileName, QByteArray buffer);

};

#endif // FILETOOLS_H
