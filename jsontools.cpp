#include "jsontools.h"

JsonTools::JsonTools()
{

}

//构建人员信息返回json
QJsonObject JsonTools::jsonBuild(QList<t_person> list)
{
    QJsonObject json;
    QJsonArray versionArray;
    QListIterator<t_person> strIterator(list);
    while(strIterator.hasNext())
    {
        QJsonObject obj;
        QJsonArray location;
        t_person tmp=strIterator.next();
        obj.insert("name",tmp.getName());
        obj.insert("number",tmp.getNumber());
        obj.insert("born",tmp.getBorn());
        obj.insert("tel",tmp.getTel());
        obj.insert("intime",tmp.getIntime());
        obj.insert("admin",tmp.getAdmin());
        obj.insert("level_name",tmp.getLevel().getLevel_name());
        obj.insert("office_name",tmp.getOffice().getOffice_name());
        obj.insert("department_name",tmp.getDepartment().getDepartment_name());
        location.append(tmp.getLocation().getLongitude());
        location.append(tmp.getLocation().getLatitude());
        obj.insert("location",location);
        obj.insert("auth",tmp.getAuth().getAuth());
        versionArray.append(obj);
    }
    json.insert("staff",versionArray);
    return json;
}

//构建统计返回json
QJsonObject JsonTools::jsonBuild(QMap<QString, int> map)
{
    QJsonObject json;
    QMapIterator<QString,int> mapIterator(map);
    while(mapIterator.hasNext())
    {
        mapIterator.next();
        QString key=mapIterator.key();
        int v=mapIterator.value();
        json.insert(key,v);
    }
    return json;
}

//使用QJsonObject解析json
QList<t_person> JsonTools::jsonParse(QByteArray byteArray)
{
    //JSON解析的错误码
    QJsonParseError jsonError;
    QList<t_person> list;
    QJsonDocument document = QJsonDocument::fromJson(byteArray, &jsonError);
    if (!document.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
        if (document.isObject())
        {
            QJsonObject object = document.object();
            if (object.contains("staff"))
            {
                QJsonValue value = object.value("staff");
                if (value.isArray())
                {
                    QJsonArray array = value.toArray();
                    int nSize = array.size();
                    for (int i = 0; i < nSize; ++i)
                    {
                        QJsonValue value = array.at(i);
                        t_person tmp;

                        if (value.isObject())
                        {
                            QJsonObject obj=value.toObject();
                            if(obj.contains("number"))
                            {
                                QJsonValue value = obj.value("number");
                                if (value.isString())
                                {
                                    tmp.setNumber(value.toString());
                                }
                            }
                            if(obj.contains("level"))
                            {
                                QJsonValue value = obj.value("level");
                                if (value.isDouble())
                                {
                                    t_level level;
                                    level.setId(value.toInt());
                                    tmp.setLevel(level);
                                }
                            }
                            if(obj.contains("name"))
                            {
                                QJsonValue value = obj.value("name");
                                if (value.isString())
                                {
                                    tmp.setName(value.toString());
                                }
                            }
                            if(obj.contains("born"))
                            {
                                QJsonValue value = obj.value("born");
                                if (value.isString())
                                {
                                    tmp.setBorn(value.toString());
                                }
                            }
                            if(obj.contains("tel"))
                            {
                                QJsonValue value = obj.value("tel");
                                if (value.isString())
                                {
                                    tmp.setTel(value.toString());
                                }
                            }
                            if(obj.contains("office"))
                            {
                                QJsonValue value = obj.value("office");
                                if (value.isDouble())
                                {
                                    t_office office;
                                    office.setId(value.toInt());
                                    tmp.setOffice(office);
                                }
                            }
                            if(obj.contains("department"))
                            {
                                QJsonValue value = obj.value("department");
                                if (value.isDouble())
                                {
                                    t_department department;
                                    department.setDepartment_id(value.toInt());
                                    tmp.setDepartment(department);
                                }
                            }
                            if(obj.contains("intime"))
                            {
                                QJsonValue value = obj.value("intime");
                                if (value.isString())
                                {
                                    tmp.setIntime(value.toString());
                                }
                            }
                            if(obj.contains("property"))
                            {
                                QJsonValue value = obj.value("property");
                                if (value.isString())
                                {
                                    tmp.setProperty(value.toString());
                                }
                            }
                            if(obj.contains("leave_s"))
                            {
                                QJsonValue value = obj.value("leave_s");
                                if (value.isDouble())
                                {
                                    tmp.setLeave_s(value.toInt());
                                }
                            }
                            if(obj.contains("away_s"))
                            {
                                QJsonValue value = obj.value("away_s");
                                if (value.isDouble())
                                {
                                    tmp.setAway_s(value.toInt());
                                }
                            }
                            if(obj.contains("admin"))
                            {
                                QJsonValue value = obj.value("admin");
                                if (value.isDouble())
                                {
                                    tmp.setAdmin(value.toInt());
                                }
                            }
                            if(obj.contains("delete_s"))
                            {
                                QJsonValue value = obj.value("delete_s");
                                if (value.isDouble())
                                {
                                    tmp.setDelete_s(value.toInt());
                                }
                            }

                        }
                        list.append(tmp);
                    }
                }
            }
        }
    }
    else
    {
        qDebug()<<jsonError.errorString();
    }
    return list;
}
//使用CJosnObject解析json
QList<t_person> JsonTools::jsonParse2(QByteArray byteArray)
{
    QList<t_person> list;
    std::string str=byteArray.toStdString();
    neb::CJsonObject oJson(str);
    for(int i=0; i < oJson["staff"].GetArraySize();i++)
    {
        t_person tmp;
        std::string key;
        while(oJson["staff"][i].GetKey(key))
        {
            t_level level;
            t_office office;
            t_department department;
            tmp.setNumber(QString::fromStdString(oJson["staff"][i]("number")));
            level.setId(std::stoi(oJson["staff"][i]("level")));
            tmp.setLevel(level);
            tmp.setName(QString::fromStdString(oJson["staff"][i]("name")));
            tmp.setBorn(QString::fromStdString(oJson["staff"][i]("born")));
            tmp.setTel(QString::fromStdString(oJson["staff"][i]("tel")));
            office.setId(std::stoi(oJson["staff"][i]("office")));
            tmp.setOffice(office);
            department.setDepartment_id(std::stoi(oJson["staff"][i]("department")));
            tmp.setDepartment(department);
            tmp.setIntime(QString::fromStdString(oJson["staff"][i]("intime")));
            tmp.setProperty(QString::fromStdString(oJson["staff"][i]("property")));
            tmp.setLeave_s(std::stoi(oJson["staff"][i]("leave_s")));
            tmp.setAway_s(std::stoi(oJson["staff"][i]("away_s")));
            tmp.setAdmin(std::stoi(oJson["staff"][i]("admin")));
            tmp.setDelete_s(std::stoi(oJson["staff"][i]("delete_s")));
        }
        list.append(tmp);

    }
    return list;
}


//发送成功或者错误的返回json
QJsonObject JsonTools::jsonSend(const int code)
{
    if(code==0)
    {
        QJsonObject json;
        json.insert("status", "0");
        return json;
    }
    if(code==1)
    {
        QJsonObject json;
        json.insert("status", "1");
        return json;
    }
}
