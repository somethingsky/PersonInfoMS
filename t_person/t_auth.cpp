#include "t_auth.h"

t_auth::t_auth()
{

}

int t_auth::getId() const
{
    return id;
}

void t_auth::setId(int value)
{
    id = value;
}

int t_auth::getPerson_id() const
{
    return person_id;
}

void t_auth::setPerson_id(int value)
{
    person_id = value;
}

QString t_auth::getAuth() const
{
    return auth;
}

void t_auth::setAuth(const QString &value)
{
    auth = value;
}
