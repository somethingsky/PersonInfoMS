#ifndef T_AUTH_H
#define T_AUTH_H
#include <QCoreApplication>
#include <QString>

//人员权限类
class t_auth
{
public:
    t_auth();
    int getId() const;
    void setId(int value);

    int getPerson_id() const;
    void setPerson_id(int value);

    QString getAuth() const;
    void setAuth(const QString &value);

private:
    int id;
    int person_id;
    QString auth;
};

#endif // T_AUTH_H
