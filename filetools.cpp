#include "filetools.h"

FileTools::FileTools()
{

}


//解析上传文件
bool FileTools::parseFormData(const QByteArray body, QString boundary, QMap<QString, QVariant> &file)
{
    QList<int> boundaryIndexList;
    QList<QByteArray> mainBodyList;
    int boundaryStart = 0;
    bool unfinished=true;
    //找到每组请求数据 开始的地方
    while (unfinished) {
        boundaryStart= body.indexOf(boundary.toUtf8(), boundaryStart);
        if(boundaryStart==-1)
        {
            unfinished=false;
        }
        else
        {
            boundaryStart+=boundary.toUtf8().length();
            boundaryIndexList.append(boundaryStart);
        }
    }
    //大于两段说明有多组数据
    if(boundaryIndexList.length()>=2){
        //截取数据
        int length = boundaryIndexList.length();
        for(int i=0;i<length-1;i++)
        {
            QByteArray temp = body.mid(boundaryIndexList[i],boundaryIndexList[i+1]-boundary.length()-boundaryIndexList[i]-2);
            mainBodyList.append(temp);
        }
        //存放value的列表
        QList<QVariant> arr;

        foreach(QByteArray item, mainBodyList)
        {
            QByteArray value;
            item= item.trimmed();
            //不同操作系统换行符不同,用变量a声明特殊分割点位的下标
            int a;
            if ((a = item.indexOf("\r\n\r\n")) != -1) {
                value = item.mid(a + 4);
            } else if ((a = item.indexOf("\r\r")) != -1) {
                value = item.mid(a + 2);
            } else if ((a = item.indexOf("\n\n")) != -1) {
                value = item.mid(a + 2);
            }


            //找到name：后面的数据
            QString key=item.mid(item.indexOf("name=\"")+QByteArray("name=\"").length(),
                                    item.indexOf("\";")-item.indexOf("name=\"")-QByteArray("name=\"").length());

            //是否为文件信息
            if (item.indexOf("filename") != -1)
            {
                QByteArray filename =item.mid(item.indexOf("filename=\"")+QByteArray("filename=\"").length(),
                                              item.indexOf("\"\r\n")-item.indexOf("filename=\"")-QByteArray("filename=\"").length());
                QByteArray contentType = item.mid(item.indexOf("Content-Type:")+QByteArray("Content-Type:").length(),
                                                  a-item.indexOf("Content-Type:")-QByteArray("Content-Type:").length());
                QMap<QString,QVariant> obj;
                obj["filename"] = filename;
                obj["contentType"] = contentType;
                obj["value"] = value;
                arr.append(obj);
                file.insert(key,arr);

            }
            else
            {
                return false;
            }
        }
        return  true;
    }
    else{
        return false;
    }
}

//保存文本格式文件
bool FileTools::saveFileText(QString fileName, QByteArray buffer)
{

    QFile file(fileName);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        qDebug() << "file open error!";
        return false;
    }
    QTextStream out(&file);
    out.setCodec("UTF-8");

    out<< buffer ;
    file.close();
    return true;
}

//保存其他类型文件
bool FileTools::saveFileOther(QString fileName, QByteArray buffer)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadWrite)){
        qDebug() << "file open error!";
        return false;
    }
    QDataStream out(&file);
    char *ch;
    ch = buffer.data();
    out.writeRawData(ch,buffer.size());
    file.close();
    return true;
}
