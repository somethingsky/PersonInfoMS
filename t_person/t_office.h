#ifndef T_OFFICE_H
#define T_OFFICE_H
#include <QCoreApplication>
#include <QString>


//职位信息类
class t_office
{
public:
    t_office();
    int getId() const;
    void setId(int value);

    QString getOffice_name() const;
    void setOffice_name(const QString &value);

    int getOffice_id() const;
    void setOffice_id(int value);

private:
    int id;
    QString office_name;
    int office_id;
};

#endif // T_OFFICE_H
