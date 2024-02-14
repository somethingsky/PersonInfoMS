#include "configfile.h"

ConfigFile::ConfigFile()
{

}

QStringList ConfigFile::readSQL()
{
    QString path=QDir::currentPath() + "/personInfo.sql";
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"failed to open";
    }
    if(!file.exists())
    {
        qDebug()<<"file not exists";
    }
    //将文件内容读取到数组中
    QByteArray data(file.readAll());
    file.close();	//关闭文件
    QString sql(data);
    QStringList qlist=sql.split(";");

    return qlist;
}

QList<QString> ConfigFile::readINI()
{
    QList<QString> list;
    QString strPath=QDir::currentPath() + "/config.ini";
    QSettings settings(strPath, QSettings::IniFormat);
    settings.beginGroup("DatabaseConfig");
    QString driver = settings.value("driver").toString();
    QString hostName = settings.value("hostName").toString();
    QString port = settings.value("port").toString();
    QString userName = settings.value("userName").toString();
    QString password = settings.value("password").toString();
    QString databaseName = settings.value("databaseName").toString();
    list.append(driver);
    list.append(hostName);
    list.append(port);
    list.append(userName);
    list.append(password);
    list.append(databaseName);
    return list;
}

void ConfigFile::writeINI(QList<QString> list)
{
    //创建QSettings对象并指定ini文件路径并将格式设置为ini
    QString strPath=QDir::currentPath() + "/config.ini";
    QSettings setting(strPath, QSettings::IniFormat);
    setting.setValue("DatabaseConfig/driver", list.at(0));
    setting.setValue("DatabaseConfig/hostName", list.at(1));
    setting.setValue("DatabaseConfig/port", list.at(2));
    setting.setValue("DatabaseConfig/userName", list.at(3));
    setting.setValue("DatabaseConfig/password", list.at(4));
    setting.setValue("DatabaseConfig/databaseName", list.at(5));
    setting.sync();
}



QList<QString> ConfigFile::readXML()
{
    // 新建QDomDocument类对象，它代表一个XML文档
    QDomDocument doc;
    QString strPath=QDir::currentPath() + "/config.xml";
    QFile file(strPath);
//    qDebug()<<file.exists();
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"文件不可读";
        QList<QString> q;
        return q;
    }
    // 将文件内容读到doc中
    if (!doc.setContent(&file)) {//从file中读取XML文档，如果成功解析了内容，返回true
        file.close();
    }
    // 关闭文件
    file.close();
    // 返回根元素
    QDomElement docElem = doc.documentElement();
    // 返回根节点的第一个子结点
    QDomNode n = docElem.firstChild();

    QString driver;
    QString hostName;
    QString port;
    QString userName;
    QString password;
    QString databaseName;
    // 如果结点不为空，则转到下一个节点
    while(!n.isNull())
    {
        // 如果结点是元素
        if (n.isElement())
        {
            // 将其转换为元素
            QDomElement e = n.toElement();
            if(e.tagName()=="driver")
            {
                driver =e.text();
            }
            if(e.tagName()=="hostName")
            {
                hostName =e.text();
            }
            if(e.tagName()=="port")
            {
                port =e.text();
            }
            if(e.tagName()=="userName")
            {
                userName =e.text();
            }
            if(e.tagName()=="password")
            {
                password =e.text();
            }
            if(e.tagName()=="databaseName")
            {
                databaseName =e.text();
            }

        }
        // 转到下一个兄弟结点
        n = n.nextSibling();
    }
    QList<QString> list;
    list<<driver<<hostName<<port<<userName<<password<<databaseName;
    return list;
}

bool ConfigFile::writeXML(QList<QString> list)
{
    //创建QDomDocument对象
    QDomDocument xDoc;
    QDomProcessingInstruction inStruction;
    //写入xml文件头(xml版本信息和编码信息)
    inStruction = xDoc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    xDoc.appendChild(inStruction);

    //创建根节点并将其添加到xDoc中
    QDomElement root = xDoc.createElement("Database");
    xDoc.appendChild(root);

    //创建子节点1
    QDomElement childNode1 = xDoc.createElement("driver");
    //! 为子节点childNode1添加节点值
    //! 创建QDomText对象并设置其值
    QDomText nodeVal = xDoc.createTextNode(list.at(0));
    //使用QDomElement对象的节点，添加节点值需添加QDomText对象，否则有可能不显示该值
    childNode1.appendChild(nodeVal);
    //将子节点1添加到根节点中
    root.appendChild(childNode1);

    //创建子节点2
    QDomElement childNode2 = xDoc.createElement("hostName");
    QDomText nodeVal2 = xDoc.createTextNode(list.at(1));
    childNode2.appendChild(nodeVal2);
    root.appendChild(childNode2);

    //创建子节点3
    QDomElement childNode3 = xDoc.createElement("port");
    QDomText nodeVal3 = xDoc.createTextNode(list.at(2));
    childNode3.appendChild(nodeVal3);
    root.appendChild(childNode3);

    //创建子节点4
    QDomElement childNode4 = xDoc.createElement("userName");
    QDomText nodeVal4 = xDoc.createTextNode(list.at(3));
    childNode4.appendChild(nodeVal4);
    root.appendChild(childNode4);

    //创建子节点5
    QDomElement childNode5 = xDoc.createElement("password");
    QDomText nodeVal5 = xDoc.createTextNode(list.at(4));
    childNode5.appendChild(nodeVal5);
    root.appendChild(childNode5);

    //创建子节点6
    QDomElement childNode6 = xDoc.createElement("databaseName");
    QDomText nodeVal6 = xDoc.createTextNode(list.at(5));
    childNode6.appendChild(nodeVal6);
    root.appendChild(childNode6);

    //指定xml文件路径
    QString strPath=QDir::currentPath() + "/config.xml";
    QFile file(strPath);
    //以只读方式打开，并且会清空文件内容
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return false;
    //使用文本流写入文件
    QTextStream outputStream(&file);
    xDoc.save(outputStream, 4); //缩进四格
    file.close();
    return true;
}



QList<QString> ConfigFile::readJSON()
{
    QString strPath=QDir::currentPath() + "/config.json";
    QFile file(strPath);	//创建QFile对象，并指定json文件路径
    //打开json文件并判断
    if(!file.open(QIODevice::ReadOnly))
        qDebug()<<"读取失败";
    //将文件内容读取到数组中
    QByteArray data(file.readAll());
    file.close();	//关闭文件
    QJsonParseError jError;	//创建QJsonParseError对象
    //使用QJsonDocument的fromJson函数读取json串，并将QJsonParseError对象传入获取错误值
    QJsonDocument jDoc = QJsonDocument::fromJson(data, &jError);
    //判断QJsonParseError对象获取的error是否包含错误，包含则返回0
    if(jError.error != QJsonParseError::NoError)
        qDebug()<<jError.errorString();
    QJsonObject jObj = jDoc.object();
    //对象类型需要使用新的QJsonObject对象存放，然后使用新的QJsonObject获取其中值
    QJsonObject jObj2 = jObj["Database"].toObject();
    //获取jObj2中指定键的值（值对应的类型直接使用对应函数转）
    QString driver = jObj2["driver"].toString();
    QString hostName = jObj2["hostName"].toString();
    QString port = jObj2["port"].toString();
    QString userName = jObj2["userName"].toString();
    QString password = jObj2["password"].toString();
    QString databaseName = jObj2["databaseName"].toString();
    QList<QString> list;
    list<<driver<<hostName<<port<<userName<<password<<databaseName;
    return list;
}

bool ConfigFile::writeJSON(QList<QString> list)
{
    //创建QJsonObject对象（姑且称之为根对象），用于存放需要写入的数据
    QJsonObject jObj;
    //对象类型需要一个子QJsonObject对象存放，然后在添加到根QJsonObject对象中
    QJsonObject jChildObj;
    //添加值
    jChildObj.insert("driver", QJsonValue(list.at(0)));
    jChildObj.insert("hostName", QJsonValue(list.at(1)));
    jChildObj.insert("port", QJsonValue(list.at(2)));
    jChildObj.insert("userName", QJsonValue(list.at(3)));
    jChildObj.insert("password", QJsonValue(list.at(4)));
    jChildObj.insert("databaseName", QJsonValue(list.at(5)));
    //当子对象的值添加完成后将子对象添加到根对象中即可
    jObj.insert("Database", jChildObj);
    //创建QJsonDocument对象并将根对象传入
    QJsonDocument jDoc(jObj);
    //打开存放json串的文件
    QString strPath=QDir::currentPath() + "/config.json";
    QFile file(strPath);
    if(!file.open(QIODevice::WriteOnly))
        return false;
    //使用QJsonDocument的toJson方法获取json串并保存到数组
    QByteArray data(jDoc.toJson());
    //将json串写入文件
    file.write(data);
    file.close();
    return true;
}

