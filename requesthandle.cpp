#include "requesthandle.h"


PersonGetRequest::PersonGetRequest()
{

}

bool PersonGetRequest::personDelete(QMap<QString, QString> map)
{
    int id;
    /* 遍历数据要使用迭代器，QT提供了两种方式的迭代 */
    QMapIterator<QString, QString> iterator(map);
    while (iterator.hasNext()) {
        iterator.next();
        id=iterator.value().toInt();
    }
    SqliteOperator sqlTest=SqliteOperator::getInstance();
    sqlTest.openDb();
    if(sqlTest.deleteData(id))
    {
        sqlTest.closeDb();
        return true;
    }
    else
    {
        sqlTest.closeDb();
        return false;
    }

}

QJsonObject PersonGetRequest::personAllInfo()
{
    SqliteOperator sqlTest=SqliteOperator::getInstance(JSON);
    sqlTest.openDb();
    QList<t_person> list=sqlTest.queryTable();
    QJsonObject obj = JsonTools::jsonBuild(list);
    sqlTest.closeDb();
    return obj;
}

QJsonObject PersonGetRequest::personStatistics(QMap<QString, QString> map)
{
    QString type;
    type = map["type"];
    SqliteOperator sqlTest=SqliteOperator::getInstance(INI);
    sqlTest.openDb();
    if(type=="department")
    {
        QMap<QString,int> tmp=sqlTest.queryStatisticsDepart();
        QJsonObject obj;
        obj=JsonTools::jsonBuild(tmp);
        sqlTest.closeDb();
        return obj;
    }
    else if(type=="level")
    {
        QMap<QString,int> tmp=sqlTest.queryStatisticsLevel();
        QJsonObject obj;
        obj=JsonTools::jsonBuild(tmp);
        sqlTest.closeDb();
        return obj;
    }
    else if(type=="office")
    {
        QMap<QString,int> tmp=sqlTest.queryStatisticsOffice();
        QJsonObject obj;
        obj=JsonTools::jsonBuild(tmp);
        sqlTest.closeDb();
        return obj;
    }
    else
    {
        QJsonObject obj;
        return obj;
    }
}

PersonPostRequest::PersonPostRequest()
{

}

bool PersonPostRequest::personAdd(QByteArray byteArray)
{
    SqliteOperator sqlTest=SqliteOperator::getInstance();
    sqlTest.openDb();
    QJsonDocument document = QJsonDocument::fromJson(byteArray);
    if(!document.isNull() && document.isObject())
    {
        QJsonObject obj = document.object();
//        QJsonArray arr = obj["staff"].toArray();
//        QJsonObject person = arr.at(0).toObject();
//        if(sqlTest.singleInsertData(person))
        if(sqlTest.moreInsertData(obj))
        {
            sqlTest.closeDb();
            return true;
        }
        else
        {
            sqlTest.closeDb();
            return false;
        }
    }
    sqlTest.closeDb();
    return false;

}

bool PersonPostRequest::personModify(QMap<QString, QString> map, QByteArray byteArray)
{
    int id;
    id = map["id"].toInt();
    SqliteOperator sqlTest=SqliteOperator::getInstance();
    sqlTest.openDb();
    QList<t_person> list=JsonTools::jsonParse(byteArray);
    t_person tmp=list.at(0);
    if(sqlTest.modifyData(id,tmp))
    {
        sqlTest.closeDb();
        return true;
    }
    else
    {
        sqlTest.closeDb();
        return false;
    }

}

bool PersonPostRequest::fileUpload(QMap<QString, QString> map, QByteArray byteArray)
{
    QString boundary;
    /* 遍历数据使用迭代器 */
    QMapIterator<QString, QString> iterator(map);
    while (iterator.hasNext()) {
        iterator.next();
        if(iterator.key()=="Content-Type")
        {
             int i=iterator.value().indexOf("boundary=");
             boundary = iterator.value().mid(i+QString("boundary=").length());
        }
    }
    QMap<QString,QVariant> file;
    if(FileTools::parseFormData(byteArray,boundary,file))
    {
        QMapIterator<QString,QVariant> iteratorFile(file);

        while(iteratorFile.hasNext())
        {
            QString fileName;
            iteratorFile.next();
            QList<QVariant> arrayList(iteratorFile.value().toList());
            foreach (QVariant tmp, arrayList)
            {
                bool flag = false;
                QMap<QString,QVariant> map = tmp.toMap();
                fileName = map["filename"].toString();
                if(map["contentType"].toByteArray().contains("text"))
                {
                    flag=FileTools::saveFileText(fileName,map["value"].toByteArray());
                }
                else
                {
                    flag=FileTools::saveFileOther(fileName,map["value"].toByteArray());
                }
                if(flag)
                {
                    qDebug()<<fileName<<":"<<"Saved successfully!";
                }
                else
                {
                    qDebug()<<"Save failed";
                }
            }
        }
        return true;
    }

    return false;
}
