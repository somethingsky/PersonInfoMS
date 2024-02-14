#ifndef T_LOCATION_H
#define T_LOCATION_H
#include <QCoreApplication>
#include <QString>


//地理信息类
class t_location
{
public:
    t_location();
    int getId() const;
    void setId(int value);

    int getPerson_id() const;
    void setPerson_id(int value);

    double getLongitude() const;
    void setLongitude(double value);

    double getLatitude() const;
    void setLatitude(double value);

private:
    int id;
    int person_id;
    double longitude;
    double latitude;
};

#endif // T_LOCATION_H
