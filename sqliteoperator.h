#ifndef SQLITEOPERATOR_H
#define SQLITEOPERATOR_H

#include "configfile.h"
#include "t_person.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>
#include <QSettings>

//数据库操作类
class SqliteOperator
{
public:
    //单例模式返回对象
    static SqliteOperator& getInstance();
    static SqliteOperator& getInstance(int config);

    // 打开数据库并在无表情况下自动初始化表结构
    bool openDb(void);
    // 创建数据表
    void createTable(void);
    // 判断数据表是否存在
    bool isTableExist(const QString &tableName);
    // 查询全部数据
    QList<t_person> queryTable();
    //查询部门的统计数据
    QMap<QString,int> queryStatisticsDepart();
    //查询职级的统计数据
    QMap<QString,int> queryStatisticsLevel();
    //查询职位信息的统计数据
    QMap<QString,int> queryStatisticsOffice();
    // 插入数据
    bool singleInsertData(t_person &singledb); // 插入单条数据
    bool singleInsertData(QJsonObject obj);
    bool moreInsertData(QList<t_person>& moredb); // 插入多条数据
    bool moreInsertData(QJsonObject obj);

    // 修改数据
    bool modifyData(int id, t_person tp);
    // 删除数据
    bool deleteData(int id);
    //删除数据表
    bool deleteTable(QString& tableName);
    // 关闭数据库
    void closeDb(void);
    //保存数据库连接信息到文件
    void save(int config);

private:
    SqliteOperator();
    //构造函数通过读取不同配置初始化数据库
    SqliteOperator(int code);

private:
    QSqlDatabase database;// 用于建立和数据库的连接
    QString driver; //连接驱动类型
    QString hostName;  //主机IP
    int port;//端口号
    QString databaseName; //数据库名称
    QString userName;//用户名
    QString password;//密码

};

#endif // SQLITEOPERATOR_H
