#ifndef T_DEPARTMENT_H
#define T_DEPARTMENT_H
#include <QCoreApplication>
#include <QString>


//部门信息类
class t_department
{
public:
    t_department();
    int getId() const;
    void setId(int value);

    QString getDepartment_name() const;
    void setDepartment_name(const QString &value);

    int getDepartment_id() const;
    void setDepartment_id(int value);

    int getManager_id() const;
    void setManager_id(int value);

    int getDepartment_status() const;
    void setDepartment_status(int value);

private:
    int id;
    QString department_name;
    int department_id;
    int manager_id;
    int department_status;
};

#endif // T_DEPARTMENT_H
