#include <QCoreApplication>
// Qt lib import
#include <QtCore>
#include <QImage>
// JQLibrary import
#include <JQHttpServer>

#include "log4qt/logger.h" //每个使用log4qt的类都需要包含此头文件
#include "log4qt_init_helper_by_coding.h"
#include "log4qt_init_helper_by_config.h"
#include "requestfactory.h"
#include "requesthandle.h"

#define SUCCESS 1  //代表成功失败返回json代码
#define FALSE 0



//在类的cpp文件中，使用此静态方法声明logger（此方法比较通用）
//第二个参数写类名字，因此，输出的log条目中包含其对应的类名
LOG4QT_DECLARE_STATIC_LOGGER(logger, Main)

void initializeHttpServer()
{
    static JQHttpServer::TcpServerManage tcpServerManage( 5 ); // 设置最大处理线程数
    tcpServerManage.setHttpAcceptedCallback( []( const QPointer< JQHttpServer::Session > &session )
    {
        if(session->requestMethod()=="GET")
        {
            if(session->requestUrlPath().contains("/api/person",Qt::CaseInsensitive))
            {
                //通过模板工厂方法处理请求
                ConcreteFactory<GetRequestHandle,PersonGetRequest> requestHandle;
                GetRequestHandle *pGetHandle = requestHandle.CreateRequestHandle();

                if(!QString::compare(session->requestUrlPath(),"/api/person/delete"))
                {
                    if(pGetHandle->personDelete(session->requestUrlQuery()))
                    {
                        session->replyJsonObject(JsonTools::jsonSend(SUCCESS));
                    }
                    else
                    {
                        session->replyJsonObject(JsonTools::jsonSend(FALSE));
                    }
                    delete pGetHandle;
                    pGetHandle = nullptr;
                }
                else if(!QString::compare(session->requestUrlPath(),"/api/person/all_info"))
                {
                    QJsonObject obj = pGetHandle->personAllInfo();
                    if(!obj.isEmpty())
                    {
                        session->replyJsonObject(obj);
                    }
                    else
                    {
                        session->replyJsonObject(JsonTools::jsonSend(FALSE));
                    }
                    delete pGetHandle;
                    pGetHandle = nullptr;
                }
                else if(!QString::compare(session->requestUrlPath(),"/api/person/statistics"))
                {
                    QJsonObject obj = pGetHandle->personStatistics(session->requestUrlQuery());
                    if(!obj.isEmpty())
                    {
                        session->replyJsonObject(obj);
                    }
                    else
                    {
                        session->replyJsonObject(JsonTools::jsonSend(FALSE));
                    }
                    delete pGetHandle;
                    pGetHandle = nullptr;
                }
                else
                {
                    delete pGetHandle;
                    pGetHandle = nullptr;
                    session->replyJsonObject(JsonTools::jsonSend(FALSE));
                }
            }
            else if(session->requestUrlPath().contains("/api/fileDownload",Qt::CaseInsensitive))
            {
                session->replyFile("file2.txt");
            }
            else
            {
                session->replyJsonObject(JsonTools::jsonSend(FALSE));
            }

        }
        else if(session->requestMethod()=="POST")
        {
            if(session->requestUrlPath().contains("/api/person",Qt::CaseInsensitive))
            {   //通过模板工厂方法处理请求
                ConcreteFactory<PostRequestHandle,PersonPostRequest> requestHandle;
                PostRequestHandle *pPostHandle =requestHandle.CreateRequestHandle();

                if(!QString::compare(session->requestUrlPath(),"/api/person/add"))
                {
                    if(pPostHandle->personAdd(session->requestBody()))
                    {
                        session->replyJsonObject(JsonTools::jsonSend(SUCCESS));
                    }
                    else
                    {
                        session->replyJsonObject(JsonTools::jsonSend(FALSE));
                    }
                    delete pPostHandle;
                    pPostHandle = nullptr;
                }
                else if(!QString::compare(session->requestUrlPath(),"/api/person/modify"))
                {
                    if(pPostHandle->personModify(session->requestUrlQuery(),session->requestBody()))
                    {
                        session->replyJsonObject(JsonTools::jsonSend(SUCCESS));
                    }
                    else
                    {
                        session->replyJsonObject(JsonTools::jsonSend(FALSE));
                    }
                    delete pPostHandle;
                    pPostHandle = nullptr;
                }
                else
                {
                   delete pPostHandle;
                   pPostHandle = nullptr;
                   session->replyJsonObject(JsonTools::jsonSend(FALSE));
                }
            }
            else if(session->requestUrlPath().contains("/api/fileUpload",Qt::CaseInsensitive))
            {   //通过模板工厂方法处理请求
                ConcreteFactory<PostRequestHandle,PersonPostRequest> requestHandle;
                PostRequestHandle *pPostHandle = requestHandle.CreateRequestHandle();

                if(pPostHandle->fileUpload(session->requestHeader(),session->requestBody()))
                {
                    session->replyJsonObject(JsonTools::jsonSend(SUCCESS));
                }
                else
                {
                    session->replyJsonObject(JsonTools::jsonSend(FALSE));
                }
                delete pPostHandle;
                pPostHandle = nullptr;
            }
            else
            {
                session->replyJsonObject(JsonTools::jsonSend(FALSE));
            }
        }

    } );

    const auto listenSucceed = tcpServerManage.listen( QHostAddress::Any, 23413 );
    qDebug() << "HTTP server listen:" << listenSucceed;
}





int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString my_path = QDir::currentPath() +"/log4qt.properties";
    SetupLog4QtByConfigWithConfigFileAbsPath(my_path);
    initializeHttpServer();


    int ret=a.exec();
    ShutDownLog4QtByConfig();//exec()执行完成后，才关闭logger
    return ret;
}
