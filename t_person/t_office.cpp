#include "t_office.h"

t_office::t_office()
{

}

int t_office::getId() const
{
    return id;
}

void t_office::setId(int value)
{
    id = value;
}

QString t_office::getOffice_name() const
{
    return office_name;
}

void t_office::setOffice_name(const QString &value)
{
    office_name = value;
}

int t_office::getOffice_id() const
{
    return office_id;
}

void t_office::setOffice_id(int value)
{
    office_id = value;
}
