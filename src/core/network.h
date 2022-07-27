#ifndef _BRCOVNETWORK_H_
#define _BRCOVNETWORK_H_

#include <QFuture>
#include <QFutureWatcher>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtConcurrent/QtConcurrent>
#include "dataparser.h"
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
    bool busy();
    bool fetchStates();
    bool fetchCountries();
    QVector<BrCoVDataItem> data();

private slots:
    void handler(QNetworkReply *reply);

signals:
    void parse();

private:
    bool waitingdata;
    QFutureWatcher<QVector<BrCoVDataItem>> *fwdata;
    QNetworkAccessManager *netmgr;
    bool fetch(QUrl url);
};

#endif // _BRCOVNETWORK_H_
