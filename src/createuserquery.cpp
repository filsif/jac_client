#include "createuserquery.h"

#include <QNetworkRequest>
#include <QUrlQuery>
#include "jacclient.h"
#include <QTextDocument>

#include <QPixmap>

#include <QHttpMultiPart>
#include <QHttpPart>
#include <QByteArray>
#include <QBuffer>



namespace jac
{
CreateUserQuery::CreateUserQuery( JacClient & jac , QObject * datas):
m_client(jac)
,m_reply(Q_NULLPTR)
{

    QHttpMultiPart *multipart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QUrl url = m_client.baseUrl();
    QString str = QString("player/add/");
    url = url.resolved( str );



    QHttpPart data_part_username;
    data_part_username.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"username\""));
    QVariant username = datas->property("username");
    data_part_username.setBody( username.toString().toUtf8());
    multipart->append( data_part_username );

    QHttpPart data_part_firstname;
    data_part_firstname.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"firstname\""));
    QVariant firstname = datas->property("firstname");
    data_part_firstname.setBody( firstname.toString().toUtf8());
    multipart->append( data_part_firstname );

    QHttpPart data_part_lastname;
    data_part_lastname.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"lastname\""));
    QVariant lastname = datas->property("lastname");
    data_part_lastname.setBody( lastname.toString().toUtf8());
    multipart->append( data_part_lastname );

    QHttpPart data_part_email;
    data_part_email.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"email\""));
    QVariant email = datas->property("email");
    data_part_email.setBody( email.toString().toUtf8());
    multipart->append( data_part_email );

    QHttpPart data_part_password;
    data_part_password.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"password\""));
    QVariant password = datas->property("password");
    data_part_password.setBody( password.toString().toUtf8());
    multipart->append( data_part_password );

    QHttpPart data_part_address;
    data_part_address.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"address\""));
    QVariant address = datas->property("address");
    data_part_address.setBody( address.toString().toUtf8());
    multipart->append( data_part_address );

    QHttpPart data_part_mobile;
    data_part_mobile.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"mobilephone\""));
    QVariant mobile = datas->property("mobilephone");
    data_part_mobile.setBody( mobile.toString().toUtf8());
    multipart->append( data_part_mobile );

    QHttpPart data_part_bggnick;
    data_part_bggnick.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"bggnickname\""));
    QVariant bggnick = datas->property("bggnickname");
    data_part_bggnick.setBody( bggnick.toString().toUtf8());
    multipart->append( data_part_bggnick );



    QNetworkRequest request;
    request.setUrl(url);


    m_reply = jac.postReply( request , multipart );
    multipart->setParent(m_reply); // delete the multipart with the reply
    connect ( m_reply , SIGNAL(finished()) , this , SLOT(on_create_user_finished()));

}

CreateUserQuery::~CreateUserQuery()
{

}


void
CreateUserQuery::on_create_user_finished()
{




    if (m_reply->error() != QNetworkReply::NoError)
    {
        qWarning() << "Network error. Error code is : " << m_reply->error();
    }
    else
    {

    }

    emit results( this , false );

    m_reply->deleteLater();
    m_reply = Q_NULLPTR;
}

}
