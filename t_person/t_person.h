#ifndef T_PERSON_H
#define T_PERSON_H
#include <QCoreApplication>
#include <QString>
#include "t_level.h"
#include "t_office.h"
#include "t_location.h"
#include "t_department.h"
#include "t_auth.h"

//人员信息类
class t_person
{
public:
    t_person(); 
    int getId() const;
    void setId(int value);

    QString getNumber() const;
    void setNumber(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    QString getBorn() const;
    void setBorn(const QString &value);

    QString getTel() const;
    void setTel(const QString &value);

    QString getProperty() const;
    void setProperty(const QString &value);

    int getLeave_s() const;
    void setLeave_s(int value);

    int getAway_s() const;
    void setAway_s(int value);

    int getAdmin() const;
    void setAdmin(int value);

    int getDelete_s() const;
    void setDelete_s(int value);

    t_level getLevel() const;
    void setLevel(const t_level &value);

    t_office getOffice() const;
    void setOffice(const t_office &value);

    t_location getLocation() const;
    void setLocation(const t_location &value);

    t_department getDepartment() const;
    void setDepartment(const t_department &value);

    t_auth getAuth() const;
    void setAuth(const t_auth &value);

    QString getIntime() const;
    void setIntime(const QString &value);

private:
    int id;
    QString number;
    QString name;
    QString born;
    QString tel;
    QString intime;
    QString property;
    t_level level;
    t_office office;
    t_department department;
    int leave_s;
    int away_s;
    int admin;
    int delete_s;
    t_location location;
    t_auth auth;
};

#endif // T_PERSON_H
