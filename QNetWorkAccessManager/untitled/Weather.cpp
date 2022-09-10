#include "Weather.h"

Weather::Weather(QObject *parent)
    : QObject{parent}
{
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &Weather::replyFinished);
}

void Weather::get()
{
    qInfo() << "Getting from server....";
    manager->get(QNetworkRequest(QUrl("http://api.openweathermap.org/data/2.5/weather?lat=16.068&lon=108.212&appid=5e93b605b28ee0aae9b2d53f134d439b")));
}

void Weather::replyFinished(QNetworkReply *reply)
{
    qInfo() << "ReadyRead";
    QByteArray data = reply->readAll();

    QJsonParseError err;
    QJsonDocument myDoc = QJsonDocument::fromJson(data, &err);
    QJsonObject myObject = myDoc.object();
    if(myObject.isEmpty()){
        qDebug() << "Object is empty";
    }else{
        ReadRecursion(myObject);
    }
}
void Weather::ReadRecursion(QJsonObject myObject)
{
    for(int it = 0; it <myObject.size(); it++){

         QString key = myObject.keys().at(it);
        if(myObject[key].isBool()){
            qDebug() << key + " : " << myObject.value(key).toBool();
        }
        else if(myObject[key].isString()){
            qDebug() << key + " : " << myObject.value(key).toString();
        }
        else if(myObject[key].isDouble()){
            qDebug() << key + " : " << myObject.value(key).toDouble();
        }
        else if(myObject[key].isArray()){
            ReadArrRecursion(myObject[key].toArray());

        }else{
          qDebug() << key + " : " << myObject.value(key);
          if(myObject[key].isObject()){
              QJsonObject myObj = myObject[key].toObject();
              ReadRecursion(myObj);
            }
        }
    }
}
void Weather::ReadArrRecursion(QJsonArray myArr)
{
    for(int i = 0; i < myArr.size(); i ++){
        if(myArr[i].isObject()){

            ReadRecursion(myArr[i].toObject());

        }else if(myArr[i].isBool()){

            qDebug() << myArr[i].toBool();

        }else if(myArr[i].isDouble()){

            qDebug() << myArr[i].toDouble();

        }else if(myArr[i].isString()){

            qDebug() << myArr[i].toString();

        }else if(myArr[i].isArray()){

            QJsonArray myA = myArr[i].toArray();
            ReadArrRecursion(myA);

        }
    }
}
