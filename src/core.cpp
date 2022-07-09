#include "core.h"

CoVDataItem CoVDataItem::fromJson(QJsonObject object)
{
    QString name;
    quint32 cases;
    quint32 suspects;
    quint32 deaths;
    if (object.contains(QString("uf")))
    {
        name = QString(object["uf"].toString());
        if (object.contains(QString("state")))
        {
            name += " (" + object["state"].toString() + ")";
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

    return CoVDataItem(name, suspects, cases, deaths);
}

CoVDataItem::CoVDataItem(QString name, quint32 suspects, quint32 cases, quint32 deaths)
{
    _name = name;
    _suspect = suspects;
    _cases = cases;
    _deaths = deaths;
}

QString CoVDataItem::name()
{
    return _name;
}

quint32 CoVDataItem::cases()
{
    return _cases;
}

quint32 CoVDataItem::suspects()
{
    return _suspect;
}

quint32 CoVDataItem::deaths()
{
    return _deaths;
}

CoVDataManager::CoVDataManager(QObject *parent) : QObject(parent)
{
    mutex = new QMutex();
    data = new QVector<CoVDataItem>();
}

CoVDataManager::~CoVDataManager()
{
    delete data;
    delete mutex;
}

void CoVDataManager::update(QJsonArray json)
{
    QMutexLocker locker(mutex);
    data->clear();
    for (int i = 0; i < json.count(); i++)
    {
        data->append(CoVDataItem::fromJson(json[i].toObject()));
    }
    emit updated();
}

int CoVDataManager::size()
{
    QMutexLocker locker(mutex);
    return data->size();
}

CoVDataItem CoVDataManager::operator[](int i)
{
    QMutexLocker locker(mutex);
    return data->operator[](i);
}

CoVNetworkManager::CoVNetworkManager(CoVDataManager *datamanager, QObject *parent) : QObject(parent)
{
    reply = nullptr;

    data = datamanager;

    networkmanager = new QNetworkAccessManager(this);
    mutex = new QMutex();
}

CoVNetworkManager::~CoVNetworkManager()
{
    delete networkmanager;
    if (reply != nullptr)
        delete reply;
    delete mutex;
}

bool CoVNetworkManager::busy()
{
    QMutexLocker lock(mutex);
    return reply == nullptr;
}

bool CoVNetworkManager::fetchCountries()
{
    QMutexLocker lock(mutex);
    if (reply != nullptr)
        return false;
    reply = networkmanager->get(QNetworkRequest(QUrl("https://covid19-brazil-api.now.sh/api/report/v1/countries")));
    connect(reply, &QIODevice::readyRead, this, &CoVNetworkManager::replyHandler);
    return true;
}

bool CoVNetworkManager::fetchStates()
{
    QMutexLocker lock(mutex);
    if (reply != nullptr)
        return false;
    reply = networkmanager->get(QNetworkRequest(QUrl("https://covid19-brazil-api.now.sh/api/report/v1")));
    connect(reply, &QIODevice::readyRead, this, &CoVNetworkManager::replyHandler);
    return true;
}

void CoVNetworkManager::replyHandler()
{
    QMutexLocker lock(mutex);
    if (reply->isReadable() && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200)
    {
        QByteArray response = reply->readAll();
        QJsonDocument json = QJsonDocument::fromJson(response);
        data->update(json["data"].toArray());
    }

    reply->deleteLater();
    reply = nullptr;
}

CoVNetworkThread::CoVNetworkThread(CoVNetworkManager *manager, bool brazilOnly, QObject *parent) : QThread(parent)
{
    mgr = manager;
    brOnly = brazilOnly;
}

bool CoVNetworkThread::brazil()
{
    return brOnly;
}

bool CoVNetworkThread::success()
{
    return result;
}

void CoVNetworkThread::setBrazil(bool brazilOnly)
{
    if (!isRunning())
        brOnly = brazilOnly;
}

void CoVNetworkThread::run()
{
    if (brOnly)
        result = mgr->fetchStates();
    else
        result = mgr->fetchCountries();
}