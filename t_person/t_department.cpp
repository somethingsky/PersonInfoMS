#include "t_department.h"

t_department::t_department()
{

}

int t_department::getId() const
{
    return id;
}

void t_department::setId(int value)
{
    id = value;
}

QString t_department::getDepartment_name() const
{
    return department_name;
}

void t_department::setDepartment_name(const QString &value)
{
    department_name = value;
}

int t_department::getDepartment_id() const
{
    return department_id;
}

void t_department::setDepartment_id(int value)
{
    department_id = value;
}

int t_department::getManager_id() const
{
    return manager_id;
}

void t_department::setManager_id(int value)
{
    manager_id = value;
}

int t_department::getDepartment_status() const
{
    return department_status;
}

void t_department::setDepartment_status(int value)
{
    department_status = value;
}
