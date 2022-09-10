#ifndef WEATHER_H
#define WEATHER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonArray>

class Weather : public QObject
{
    Q_OBJECT
public:
    explicit Weather(QObject *parent = nullptr);
    void ReadRecursion(QJsonObject);
    void ReadArrRecursion(QJsonArray);
    void get();

private slots:
    void replyFinished(QNetworkReply *reply);
private:
    QNetworkAccessManager *manager;
};

#endif // WEATHER_H
