#ifndef REQUESTFACTORY_H
#define REQUESTFACTORY_H
#include <QCoreApplication>
#include <QtCore>


// 抽象模板工厂类
// 模板参数：Abstract_t 请求抽象类
template <class Abstract_t>
class AbstractFactory
{
public:
    virtual Abstract_t *CreateRequestHandle() = 0;
    virtual ~AbstractFactory() {}
};

// 具体模板工厂类
// 模板参数：Abstract_t 请求抽象类，Concrete_t 具体类
template <class Abstract_t, class Concrete_t>
class ConcreteFactory : public AbstractFactory<Abstract_t>
{
public:
    Abstract_t *CreateRequestHandle()
    {
        return new Concrete_t();
    }
};




#endif // REQUESTFACTORY_H
