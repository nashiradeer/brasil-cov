#include "core.h"

BrCoVDataItem::BrCoVDataItem(QString name, quint32 suspects, quint32 cases, quint32 deaths)
{
    _name = name;
    _suspect = suspects;
    _cases = cases;
    _deaths = deaths;
}

QString BrCoVDataItem::name()
{
    return _name;
}

quint32 BrCoVDataItem::cases()
{
    return _cases;
}

quint32 BrCoVDataItem::suspects()
{
    return _suspect;
}

quint32 BrCoVDataItem::deaths()
{
    return _deaths;
}

BrCoVDataParser::BrCoVDataParser(QObject *parent) : QThread(parent)
{
    mutex = new QMutex();
    dataparsed = new QVector<BrCoVDataItem>();
    rawdata = nullptr;
}

BrCoVDataParser::~BrCoVDataParser()
{
    delete rawdata;
    delete dataparsed;
    delete mutex;
}

QVector<BrCoVDataItem> BrCoVDataParser::data()
{
    QMutexLocker lock(mutex);
    QVector<BrCoVDataItem> r(*dataparsed);
    return r;
}

bool BrCoVDataParser::parse(QByteArray arr)
{
    if (isRunning())
        return false;

    QMutexLocker lock(mutex);
    delete rawdata;
    rawdata = new QByteArray(arr);
    start();
    return true;
}

void BrCoVDataParser::run()
{
    QMutexLocker lock(mutex);
    QVector<BrCoVDataItem>().swap(*dataparsed);
    QJsonDocument json = QJsonDocument::fromJson(*rawdata);
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
        dataparsed->append(BrCoVDataItem(name, suspects, cases, deaths));
    }
    emit parsed();
}

BrCoVDataManager::BrCoVDataManager(QObject *parent) : QObject(parent)
{
    netmgr = new QNetworkAccessManager(this);
    connect(netmgr, &QNetworkAccessManager::finished, this, &BrCoVDataManager::handlerReply);
    parser = new BrCoVDataParser(this);
    connect(parser, &BrCoVDataParser::parsed, this, &BrCoVDataManager::parsed);
    waitingdata = false;
}

BrCoVDataManager::~BrCoVDataManager()
{
    delete parser;
    delete netmgr;
}

bool BrCoVDataManager::downloading()
{
    return waitingdata;
}

bool BrCoVDataManager::parsing()
{
    return parser->isRunning();
}

bool BrCoVDataManager::busy()
{
    return downloading() || parsing();
}

bool BrCoVDataManager::fetchCountries()
{
    return fetch(QUrl("https://covid19-brazil-api.now.sh/api/report/v1/countries"));
}

bool BrCoVDataManager::fetchStates()
{
    return fetch(QUrl("https://covid19-brazil-api.now.sh/api/report/v1"));
}

bool BrCoVDataManager::fetch(QUrl url)
{
    if (busy())
        return false;
    waitingdata = true;
    QNetworkRequest request(url);
    request.setAttribute(QNetworkRequest::RedirectPolicyAttribute, true);
    netmgr->get(request);
    return true;
}

void BrCoVDataManager::handlerReply(QNetworkReply *reply)
{
    int statuscode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (reply->isReadable() && statuscode == 200)
    {
        QByteArray response = reply->readAll();
        emit downloaded();
        parser->parse(response);
    }
    else
    {
        emit error(statuscode);
    }
    waitingdata = false;
}

QVector<BrCoVDataItem> BrCoVDataManager::last()
{
    return parser->data();
}