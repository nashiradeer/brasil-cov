#include "network.h"

BrCoVNetwork::BrCoVNetwork(QObject *parent) : QObject(parent)
{
    waitingdata = false;
    fwdata = new QFutureWatcher<QVector<BrCoVDataItem>>(this);
    connect(fwdata, &QFutureWatcher<QVector<BrCoVDataItem>>::finished, this, &BrCoVNetwork::parse);
    netmgr = new QNetworkAccessManager(this);
    connect(netmgr, &QNetworkAccessManager::finished, this, &BrCoVNetwork::handler);
}

BrCoVNetwork::~BrCoVNetwork()
{
    delete fwdata;
    delete netmgr;
}

bool BrCoVNetwork::busy()
{
    return waitingdata || fwdata->isFinished();
}

bool BrCoVNetwork::fetchCountries()
{
    return fetch(QUrl("https://covid19-brazil-api.now.sh/api/report/v1/countries"));
}

bool BrCoVNetwork::fetchStates()
{
    return fetch(QUrl("https://covid19-brazil-api.now.sh/api/report/v1"));
}

bool BrCoVNetwork::fetch(QUrl url)
{
    if (busy())
        return false;

    waitingdata = true;
    QNetworkRequest request(url);
    request.setAttribute(QNetworkRequest::RedirectPolicyAttribute, true);
    netmgr->get(request);
    return true;
}

void BrCoVNetwork::handler(QNetworkReply *reply)
{
    int statuscode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if (reply->isReadable() && statuscode == 200)
    {
        QByteArray response = reply->readAll();
        QFuture<QVector<BrCoVDataItem>> fdata = QtConcurrent::run(brcovDataParser, &response);
        fwdata->setFuture(fdata);
    }

    waitingdata = false;
}

QVector<BrCoVDataItem> BrCoVNetwork::data()
{
    return fwdata->result();
}
