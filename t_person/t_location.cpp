#include "t_location.h"

t_location::t_location()
{

}

int t_location::getId() const
{
    return id;
}

void t_location::setId(int value)
{
    id = value;
}

int t_location::getPerson_id() const
{
    return person_id;
}

void t_location::setPerson_id(int value)
{
    person_id = value;
}

double t_location::getLongitude() const
{
    return longitude;
}

void t_location::setLongitude(double value)
{
    longitude = value;
}

double t_location::getLatitude() const
{
    return latitude;
}

void t_location::setLatitude(double value)
{
    latitude = value;
}
