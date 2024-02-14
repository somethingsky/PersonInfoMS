#include "t_level.h"

t_level::t_level()
{

}

int t_level::getId() const
{
    return id;
}

void t_level::setId(int value)
{
    id = value;
}

QString t_level::getLevel_name() const
{
    return level_name;
}

void t_level::setLevel_name(const QString &value)
{
    level_name = value;
}

int t_level::getLevel_id() const
{
    return level_id;
}

void t_level::setLevel_id(int value)
{
    level_id = value;
}
