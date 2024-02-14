#include "sqliteoperator.h"
#include "log4qt/logger.h" //每个使用log4qt的类都需要包含此头文件

//在类的cpp文件中，使用此静态方法声明logger（此方法比较通用）
//第二个参数写类名字，因此，输出的log条目中包含其对应的类名
LOG4QT_DECLARE_STATIC_LOGGER(logger, SqliteOperator)

// 构造函数中初始化数据库对象，并建立数据库
SqliteOperator::SqliteOperator()
{
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        // 建立和数据库的连接
        database = QSqlDatabase::addDatabase("QMYSQL");

        database.setHostName("127.0.0.1");//设置主机
        database.setPort(3306);//设置端口号
        database.setUserName("root"); //设置用户名
        database.setPassword("123456"); //设置密码
        database.setDatabaseName("personInfo"); //设置数据库名称

    }
}
//构造函数通过读取不同配置初始化数据库
SqliteOperator::SqliteOperator(int code)
{
    switch(code)
    {
        default:
        case 1:
            {
                QList<QString> list;
                list=ConfigFile::readINI();
                this->driver=list.at(0);
                this->hostName=list.at(1);
                this->port=list.at(2).toInt();
                this->userName=list.at(3);
                this->password=list.at(4);
                this->databaseName=list.at(5);
            }
            break;
        case 2:
            {
                QList<QString> list;
                list=ConfigFile::readXML();
                this->driver=list.at(0);
                this->hostName=list.at(1);
                this->port=list.at(2).toInt();
                this->userName=list.at(3);
                this->password=list.at(4);
                this->databaseName=list.at(5);
            }
            break;
        case 3:
            {
                QList<QString> list;
                list=ConfigFile::readJSON();
                this->driver=list.at(0);
                this->hostName=list.at(1);
                this->port=list.at(2).toInt();
                this->userName=list.at(3);
                this->password=list.at(4);
                this->databaseName=list.at(5);
            }
            break;
    }
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        // 建立和数据库的连接
        database = QSqlDatabase::addDatabase(driver);

        database.setHostName(hostName);//设置主机
        database.setPort(port);//设置端口号
        database.setUserName(userName); //设置用户名
        database.setPassword(password); //设置密码
        database.setDatabaseName(databaseName); //设置数据库名称
    }
}

SqliteOperator &SqliteOperator::getInstance()
{

    static SqliteOperator instance;  //局部静态变量 C++11实现单例
    return instance;

}

SqliteOperator &SqliteOperator::getInstance(int config)
{
    static SqliteOperator instance(config);
    return instance;
}
// 打开数据库并在无表情况下自动初始化表结构
bool SqliteOperator::openDb()
{
    if (!database.open())
    {
        logger()->debug() << "Error: Failed to connect database." << database.lastError().text();
        return false;
    }

    if(database.tables().isEmpty())
    {
        createTable();
    }
    logger()->debug()<<"Database opened successfully!"<<endl;
    logger()->debug()<<"Database driver :"<<this->database.driverName();
    logger()->debug()<<"Database hostname :"<<this->database.hostName();
    logger()->debug()<<"Database port :"<<this->database.port();
    logger()->debug()<<"Database name :"<<this->database.databaseName()<<endl;
    return true;
}

// 创建数据表
void SqliteOperator::createTable()
{
    // 用于执行sql语句的对象
    QSqlQuery sqlQuery;

    QStringList sql_list=ConfigFile::readSQL();
    for(int i = 0 ;i < sql_list.size();i++)
    {
        // 构建创建数据库的sql语句字符串
        QString createSql =sql_list.at(i);
        bool sql_result = sqlQuery.exec(createSql);
        if (!sql_result) {
            QSqlError sql_error = sqlQuery.lastError();
            logger()->debug()<< sql_error.text()<< endl;
            return;
        }
    }

    logger()->debug()<<"Table created successfully!"<<endl;

}

// 判断数据库中某个数据表是否存在
bool SqliteOperator::isTableExist(const QString& tableName)
{
    QSqlDatabase database = QSqlDatabase::database();
    if(database.tables().contains(tableName))
    {
        logger()->debug()<<"Database table exists"<<endl;
        return true;
    }
    logger()->debug()<<"Database table does not exist"<<endl;
    return false;
}

// 查询全部数据
QList<t_person> SqliteOperator::queryTable()
{
    QSqlQuery sqlQuery;
    QList<t_person> qlist;
    sqlQuery.exec("SELECT t_person.name,t_person.number,t_person.born,t_person.tel,t_person.intime,\
                  t_person.admin,t_level.level_name,t_office.office_name,t_department.department_name,\
                  t_location.longitude,t_location.latitude,t_auth.auth \
                  FROM t_person \
                  LEFT OUTER JOIN t_level \
                  ON t_person.level = t_level.id \
                  LEFT OUTER JOIN t_office \
                  ON t_person.office =t_office.id \
                  LEFT OUTER JOIN t_department \
                  ON t_person.department =t_department.department_id \
                  LEFT OUTER JOIN t_location \
                  ON t_person.id =t_location.person_id \
                  LEFT OUTER JOIN t_auth \
                  ON t_person.id =t_auth.person_id");
    if(!sqlQuery.exec())
    {
        logger()->debug() << "Error: Fail to query table. " << sqlQuery.lastError().text();
    }
    else
    {
        while(sqlQuery.next())
        {
            t_person tmp;
            t_level level;
            t_office office;
            t_department department;
            t_location location;
            t_auth auth;
            tmp.setName(sqlQuery.value(0).toString());
            tmp.setNumber(sqlQuery.value(1).toString());
            tmp.setBorn(sqlQuery.value(2).toString());
            tmp.setTel(sqlQuery.value(3).toString());
            tmp.setIntime(sqlQuery.value(4).toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            tmp.setAdmin(sqlQuery.value(5).toInt());
            level.setLevel_name(sqlQuery.value(6).toString());
            tmp.setLevel(level);
            office.setOffice_name(sqlQuery.value(7).toString());
            tmp.setOffice(office);
            department.setDepartment_name(sqlQuery.value(8).toString());
            tmp.setDepartment(department);
            location.setLongitude(sqlQuery.value(9).toDouble());
            location.setLatitude(sqlQuery.value(10).toDouble());
            tmp.setLocation(location);
            auth.setAuth(sqlQuery.value(11).toString());
            tmp.setAuth(auth);

            qlist.append(tmp);
        }
        logger()->debug()<<"sql executed :"<<sqlQuery.executedQuery()<<endl;
    }
    return qlist;
}
//查询部门的统计数据
QMap<QString, int> SqliteOperator::queryStatisticsDepart()
{
    QSqlQuery sqlQuery;
    QMap<QString,int> map;
    sqlQuery.exec("SELECT t_department.department_name,count(t_person.id) as 人数 \
                  FROM t_person,t_department WHERE t_person.department =t_department.department_id \
                   GROUP BY t_department.department_name");
    if(!sqlQuery.exec())
    {
        logger()->debug() << "Error: Fail to query table. " << sqlQuery.lastError().text();
    }
    else
    {
        while(sqlQuery.next())
        {
            QString key=sqlQuery.value(0).toString();
            int num=sqlQuery.value(1).toInt();
            map.insert(key,num);
        }
        logger()->debug()<<"sql executed :"<<sqlQuery.executedQuery()<<endl;
    }
            return map;
}
//查询职级的统计数据
QMap<QString, int> SqliteOperator::queryStatisticsLevel()
{
    QSqlQuery sqlQuery;
    QMap<QString,int> map;
    sqlQuery.exec("SELECT t_level.level_name,count(t_person.id) as 人数 \
                  FROM t_person,t_level WHERE t_person.level =t_level.id \
                   GROUP BY t_level.level_name");
    if(!sqlQuery.exec())
    {
        logger()->debug() << "Error: Fail to query table. " << sqlQuery.lastError().text();
    }
    else
    {
        while(sqlQuery.next())
        {
            QString key=sqlQuery.value(0).toString();
            int num=sqlQuery.value(1).toInt();
            map.insert(key,num);
        }
        logger()->debug()<<"sql executed :"<<sqlQuery.executedQuery()<<endl;
    }
            return map;
}
//查询职位信息的统计数据
QMap<QString, int> SqliteOperator::queryStatisticsOffice()
{
    QSqlQuery sqlQuery;
    QMap<QString,int> map;
    sqlQuery.exec("SELECT t_office.office_name,count(t_person.id) as 人数 \
                  FROM t_person,t_office WHERE t_person.office =t_office.id \
                   GROUP BY t_office.office_name");
    if(!sqlQuery.exec())
    {
        logger()->debug() << "Error: Fail to query table. " << sqlQuery.lastError().text();
    }
    else
    {
        while(sqlQuery.next())
        {
            QString key=sqlQuery.value(0).toString();
            int num=sqlQuery.value(1).toInt();
            map.insert(key,num);
        }
        logger()->debug()<<"sql executed :"<<sqlQuery.executedQuery()<<endl;
    }
            return map;
}

// 插入单条数据
bool SqliteOperator::singleInsertData(t_person &singledb)
{
    QSqlQuery sqlQuery;
    sqlQuery.prepare("INSERT INTO t_person VALUES(NULL,\
                     :number,:level,:name,:born,:tel,:office,\
                     :department,:intime,:property,:leave_s,:away_s,\
                     :admin,:delete_s)");
    sqlQuery.bindValue(":number", singledb.getNumber());
    sqlQuery.bindValue(":level", singledb.getLevel().getId());
    sqlQuery.bindValue(":name", singledb.getName());
    sqlQuery.bindValue(":born", singledb.getBorn());
    sqlQuery.bindValue(":tel", singledb.getTel());
    sqlQuery.bindValue(":office", singledb.getOffice().getId());
    sqlQuery.bindValue(":department", singledb.getDepartment().getDepartment_id());
    sqlQuery.bindValue(":intime", singledb.getIntime());
    sqlQuery.bindValue(":property", singledb.getProperty());
    sqlQuery.bindValue(":leave_s", singledb.getLeave_s());
    sqlQuery.bindValue(":away_s", singledb.getAway_s());
    sqlQuery.bindValue(":admin", singledb.getAdmin());
    sqlQuery.bindValue(":delete_s", singledb.getDelete_s());
    if(!sqlQuery.exec())
    {
        logger()->debug() << "Error: Fail to insert data. " << sqlQuery.lastError().text();
        return false;
    }
    else
    {
        logger()->debug()<<"sql executed :"<<sqlQuery.executedQuery()<<endl;
        return true;
    }
}

bool SqliteOperator::singleInsertData(QJsonObject obj)
{
    QSqlQuery sqlQuery;
    sqlQuery.prepare("INSERT INTO t_person VALUES(NULL,\
                     :number,:level,:name,:born,:tel,:office,\
                     :department,:intime,:property,:leave_s,:away_s,\
                     :admin,:delete_s)");
    sqlQuery.bindValue(":number", obj["number"].toString());
    sqlQuery.bindValue(":level", obj["level"].toInt());
    sqlQuery.bindValue(":name", obj["name"].toString());
    sqlQuery.bindValue(":born", obj["born"].toString());
    sqlQuery.bindValue(":tel", obj["tel"].toString());
    sqlQuery.bindValue(":office", obj["office"].toInt());
    sqlQuery.bindValue(":department", obj["department"].toInt());
    sqlQuery.bindValue(":intime", obj["intime"].toString());
    sqlQuery.bindValue(":property", obj["property"].toString());
    sqlQuery.bindValue(":leave_s", obj["leave_s"].toInt());
    sqlQuery.bindValue(":away_s", obj["away_s"].toInt());
    sqlQuery.bindValue(":admin", obj["admin"].toInt());
    sqlQuery.bindValue(":delete_s", obj["delete_s"].toInt());
    if(!sqlQuery.exec())
    {
        logger()->debug() << "Error: Fail to insert data. " << sqlQuery.lastError().text();
        return false;
    }
    else
    {
        logger()->debug()<<"sql executed :"<<sqlQuery.executedQuery()<<endl;
        return true;
    }
}




// 插入多条数据
bool SqliteOperator::moreInsertData(QList<t_person>& moredb)
{
    if(moredb.isEmpty())
    {
        return false;
    }
    // 进行多个数据的插入时，可以利用绑定进行批处理
    QSqlQuery sqlQuery;
    database.transaction(); //开启事务
    sqlQuery.prepare("INSERT INTO t_person VALUES(NULL,?,?,?,?,?,?,?,?,?,?,?,?,?)");
    QVariantList numberList,levelList,nameList,bornList,telList,officeList,
            departmentList,intimeList,propertyList,leave_sList,away_sList,adminList,deleteList;
    for(int i=0; i< moredb.size(); i++)
    {
        numberList <<  moredb.at(i).getNumber();
        levelList << moredb.at(i).getLevel().getId();
        nameList << moredb.at(i).getName();
        bornList << moredb.at(i).getBorn();
        telList << moredb.at(i).getTel();
        officeList << moredb.at(i).getOffice().getId();
        departmentList << moredb.at(i).getDepartment().getDepartment_id();
        intimeList << moredb.at(i).getIntime();
        propertyList << moredb.at(i).getProperty();
        leave_sList << moredb.at(i).getLeave_s();
        away_sList << moredb.at(i).getAway_s();
        adminList << moredb.at(i).getAdmin();
        deleteList << moredb.at(i).getDelete_s();
    }
    sqlQuery.addBindValue(numberList);
    sqlQuery.addBindValue(levelList);
    sqlQuery.addBindValue(nameList);
    sqlQuery.addBindValue(bornList);
    sqlQuery.addBindValue(telList);
    sqlQuery.addBindValue(officeList);
    sqlQuery.addBindValue(departmentList);
    sqlQuery.addBindValue(intimeList);
    sqlQuery.addBindValue(propertyList);
    sqlQuery.addBindValue(leave_sList);
    sqlQuery.addBindValue(away_sList);
    sqlQuery.addBindValue(adminList);
    sqlQuery.addBindValue(deleteList);

    if (!sqlQuery.execBatch()) // 进行批处理，如果出错就输出错误
    {
        database.rollback();
        logger()->debug() << sqlQuery.lastError().text();
        return false;
    }
    database.commit();
    logger()->debug()<<"sql executed :"<<sqlQuery.executedQuery()<<endl;
    return true;
}

bool SqliteOperator::moreInsertData(QJsonObject obj)
{
    if(obj.isEmpty())
    {
        return false;
    }
    QJsonArray arr = obj["staff"].toArray();
    // 进行多个数据的插入时，可以利用绑定进行批处理
    QSqlQuery sqlQuery;
    database.transaction(); //开启事务
    sqlQuery.prepare("INSERT INTO t_person VALUES(NULL,?,?,?,?,?,?,?,?,?,?,?,?,?)");
    QVariantList numberList,levelList,nameList,bornList,telList,officeList,
            departmentList,intimeList,propertyList,leave_sList,away_sList,adminList,deleteList;
    for(int i=0; i< arr.size(); i++)
    {
        QJsonObject json =arr.at(i).toObject();
        numberList << json["number"].toString() ;
        levelList << json["level"].toInt();
        nameList << json["name"].toString();
        bornList << json["born"].toString();
        telList << json["tel"].toString();
        officeList << json["office"].toInt();
        departmentList << json["department"].toInt();
        intimeList << json["intime"].toString();
        propertyList << json["property"].toString();
        leave_sList << json["leave_s"].toInt();
        away_sList << json["away_s"].toInt();
        adminList << json["admin"].toInt();
        deleteList << json["delete_s"].toInt();
    }
    sqlQuery.addBindValue(numberList);
    sqlQuery.addBindValue(levelList);
    sqlQuery.addBindValue(nameList);
    sqlQuery.addBindValue(bornList);
    sqlQuery.addBindValue(telList);
    sqlQuery.addBindValue(officeList);
    sqlQuery.addBindValue(departmentList);
    sqlQuery.addBindValue(intimeList);
    sqlQuery.addBindValue(propertyList);
    sqlQuery.addBindValue(leave_sList);
    sqlQuery.addBindValue(away_sList);
    sqlQuery.addBindValue(adminList);
    sqlQuery.addBindValue(deleteList);

    if (!sqlQuery.execBatch()) // 进行批处理，如果出错就输出错误
    {
        database.rollback();
        logger()->debug() << sqlQuery.lastError().text();
        return false;
    }
    database.commit();
    logger()->debug()<<"sql executed :"<<sqlQuery.executedQuery()<<endl;
    return true;
}




// 修改数据
bool SqliteOperator::modifyData(int id, t_person tp)
{
    QSqlQuery sqlQuery;
    sqlQuery.prepare("UPDATE t_person SET number=?,level=?,name=?,born=?,tel=?,\
                                          office=?,department=?,intime=?,property=?,\
                                          leave_s=?,away_s=?,admin=?,delete_s=?  WHERE id=?");
    sqlQuery.addBindValue(tp.getNumber());
    sqlQuery.addBindValue(tp.getLevel().getId());
    sqlQuery.addBindValue(tp.getName());
    sqlQuery.addBindValue(tp.getBorn());
    sqlQuery.addBindValue(tp.getTel());
    sqlQuery.addBindValue(tp.getOffice().getId());
    sqlQuery.addBindValue(tp.getDepartment().getDepartment_id());
    sqlQuery.addBindValue(tp.getIntime());
    sqlQuery.addBindValue(tp.getProperty());
    sqlQuery.addBindValue(tp.getLeave_s());
    sqlQuery.addBindValue(tp.getAway_s());
    sqlQuery.addBindValue(tp.getAdmin());
    sqlQuery.addBindValue(tp.getDelete_s());
    sqlQuery.addBindValue(id);
    if(!sqlQuery.exec())
    {
        logger()->debug() << sqlQuery.lastError().text();
        return false;
    }
    else
    {
        logger()->debug()<<"sql executed :"<<sqlQuery.executedQuery()<<endl;
        logger()->debug() << "updated data successfully!";
        return true;
    }
}

// 删除数据
bool SqliteOperator::deleteData(int id)
{
    QSqlQuery sqlQuery;

    sqlQuery.exec(QString("DELETE FROM t_person WHERE id = %1").arg(id));
    if(!sqlQuery.exec())
    {
        logger()->debug()<<sqlQuery.lastError().text();
        return false;
    }
    else
    {
        logger()->debug()<<"sql executed :"<<sqlQuery.executedQuery()<<endl;
        logger()->debug()<<"deleted data successfully!";
        return true;
    }
}

//删除数据表
bool SqliteOperator::deleteTable(QString& tableName)
{
    QSqlQuery sqlQuery;

    sqlQuery.exec(QString("DROP TABLE %1").arg(tableName));
    if(!sqlQuery.exec())
    {
        logger()->debug() << sqlQuery.lastError().text();
        return false;
    }
    else
    {
        logger()->debug()<<"sql executed :"<<sqlQuery.executedQuery()<<endl;
        logger()->debug() << "deleted table successfully";
        return true;
    }
}
//关闭数据库
void SqliteOperator::closeDb(void)
{

    database.close();
    logger()->debug()<<"Database closed"<<endl;
}
//保存数据库连接信息
void SqliteOperator::save(int config)
{
    QList<QString> list;
    driver=database.driverName();
    hostName=database.hostName();
    port=database.port();
    userName=database.userName();
    password=database.password();
    databaseName=database.databaseName();
    list<<driver<<hostName<<QString::number(port)<<userName<<password<<databaseName;
    switch (config) {
    case 1:
        ConfigFile::writeINI(list);
        logger()->debug()<<"Save database configuration as INI file"<<endl;
        break;
    case 2:
        ConfigFile::writeXML(list);
        logger()->debug()<<"Save database configuration as XML file"<<endl;
        break;
    case 3:
        ConfigFile::writeJSON(list);
        logger()->debug()<<"Save database configuration as JSON file"<<endl;
        break;
    default:
        logger()->debug()<<"Invalid configuration parameter"<<endl;
        break;
    }
}
