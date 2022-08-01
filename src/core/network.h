#ifndef _BRCOVNETWORK_H_
#define _BRCOVNETWORK_H_

#include <QByteArray>
#include <QCoreApplication>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QVector>
#include "dataitem.h"

namespace BrasilCoV {
    class BrCoVNetwork;
}

class BrCoVNetwork : public QObject
{
    Q_OBJECT

public:
    explicit BrCoVNetwork(QObject *parent = nullptr);
    virtual ~BrCoVNetwork();
    bool fetchStates();
    bool fetchCountries();
    bool isBusy();
    QVector<BrCoVDataItem> result();

private slots:
    void handler(QNetworkReply *reply);

signals:
    void finished();

private:
    QVector<BrCoVDataItem> *data;
    QNetworkAccessManager *netmgr;
    bool busy;
    bool fetch(QUrl url);
    void parse(QByteArray rawdata);
};

#endif // _BRCOVNETWORK_H_
