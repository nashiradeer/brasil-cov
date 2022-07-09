#ifndef __CORE_H__
#define __CORE_H__

#include <QString>
#include <QVector>
#include <QMutex>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

namespace BrasilCoV
{
    class CoVDataItem;
    class CoVDataManager;
    class CoVNetworkManager;
}

class CoVDataItem
{
public:
    static CoVDataItem fromJson(QJsonObject object);
    explicit CoVDataItem(QString name, quint32 suspects, quint32 cases, quint32 deaths);
    QString name();
    quint32 suspects();
    quint32 cases();
    quint32 deaths();

private:
    QString _name;
    quint32 _suspect;
    quint32 _cases;
    quint32 _deaths;
};

class CoVDataManager : public QObject
{
    Q_OBJECT

public:
    explicit CoVDataManager();
    virtual ~CoVDataManager();
    void update(QJsonArray json);
    int size();
    CoVDataItem operator[](int i);

signals:
    void updated();

private:
    QMutex *mutex;
    QVector<CoVDataItem> *data;
};

class CoVNetworkManager : public QObject
{
    Q_OBJECT

public:
    explicit CoVNetworkManager(CoVDataManager *datamanager);
    virtual ~CoVNetworkManager();
    bool fetchCountries();
    bool fetchStates();
    bool busy();

private:
    CoVDataManager *data;
    QNetworkAccessManager *networkmanager;
    QNetworkReply *reply;
    void replyHandler();
};

#endif