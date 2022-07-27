#include "network.h"

BrCoVNetwork::BrCoVNetwork(QObject *parent) : QObject(parent)
{
    busy = false;
    data = new QVector<BrCoVDataItem>;
    netmgr = new QNetworkAccessManager(this);

    connect(netmgr, &QNetworkAccessManager::finished, this, &BrCoVNetwork::handler);
}

BrCoVNetwork::~BrCoVNetwork()
{
    delete data;
    delete netmgr;
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
    if (busy)
        return false;
    busy = true;

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
        parse(response);
        emit finished();
    }

    busy = false;
    reply->deleteLater();
}

QVector<BrCoVDataItem> BrCoVNetwork::result()
{
    return *data;
}

bool BrCoVNetwork::isBusy()
{
    return busy;
}

void BrCoVNetwork::parse(QByteArray rawdata)
{
    data->clear();
    data->squeeze();

    QJsonDocument json = QJsonDocument::fromJson(rawdata);
    QJsonArray arr = json["data"].toArray();
    for (int i = 0; i < arr.count(); i++)
    {
        QJsonObject object = arr[i].toObject();
        QString name;
        quint32 cases;
        quint32 suspects;
        quint32 deaths;
        if (object.contains(QString("state")))
        {
            name = QString(object["state"].toString());
            if (object.contains(QString("uf")))
            {
                name += " (" + object["uf"].toString() + ")";
            }

            cases = object["cases"].toInt();
            suspects = object["suspects"].toInt();
        }
        else
        {
            name = QString(object["country"].toString());
            cases = object["confirmed"].toInt();
            suspects = object["cases"].toInt();
        }
        deaths = object["deaths"].toInt();
        data->append(BrCoVDataItem(name, suspects, cases, deaths));
        QCoreApplication::processEvents();
    }
}
