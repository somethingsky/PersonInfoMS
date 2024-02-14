#include "t_person.h"

t_person::t_person()
{

}

int t_person::getId() const
{
    return id;
}

void t_person::setId(int value)
{
    id = value;
}

QString t_person::getNumber() const
{
    return number;
}

void t_person::setNumber(const QString &value)
{
    number = value;
}

QString t_person::getName() const
{
    return name;
}

void t_person::setName(const QString &value)
{
    name = value;
}

QString t_person::getBorn() const
{
    return born;
}

void t_person::setBorn(const QString &value)
{
    born = value;
}

QString t_person::getTel() const
{
    return tel;
}

void t_person::setTel(const QString &value)
{
    tel = value;
}

QString t_person::getProperty() const
{
    return property;
}

void t_person::setProperty(const QString &value)
{
    property = value;
}

int t_person::getLeave_s() const
{
    return leave_s;
}

void t_person::setLeave_s(int value)
{
    leave_s = value;
}

int t_person::getAway_s() const
{
    return away_s;
}

void t_person::setAway_s(int value)
{
    away_s = value;
}

t_level t_person::getLevel() const
{
    return level;
}

void t_person::setLevel(const t_level &value)
{
    level = value;
}

t_office t_person::getOffice() const
{
    return office;
}

void t_person::setOffice(const t_office &value)
{
    office = value;
}

t_location t_person::getLocation() const
{
    return location;
}

void t_person::setLocation(const t_location &value)
{
    location = value;
}

t_department t_person::getDepartment() const
{
    return department;
}

void t_person::setDepartment(const t_department &value)
{
    department = value;
}

t_auth t_person::getAuth() const
{
    return auth;
}

void t_person::setAuth(const t_auth &value)
{
    auth = value;
}

QString t_person::getIntime() const
{
    return intime;
}

void t_person::setIntime(const QString &value)
{
    intime = value;
}

int t_person::getAdmin() const
{
    return admin;
}

void t_person::setAdmin(int value)
{
    admin = value;
}

int t_person::getDelete_s() const
{
    return delete_s;
}

void t_person::setDelete_s(int value)
{
    delete_s = value;
}
