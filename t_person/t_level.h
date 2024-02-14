#ifndef T_LEVEL_H
#define T_LEVEL_H
#include <QCoreApplication>
#include <QString>


//职级类
class t_level
{
public:
    t_level();
    int getId() const;
    void setId(int value);

    QString getLevel_name() const;
    void setLevel_name(const QString &value);

    int getLevel_id() const;
    void setLevel_id(int value);

private:
    int id;
    QString level_name;
    int level_id;
};

#endif // T_LEVEL_H
