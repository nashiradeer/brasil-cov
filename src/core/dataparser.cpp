#include "dataparser.h"

QVector<BrCoVDataItem> brcovDataParser(QByteArray rawdata)
{
    QVector<BrCoVDataItem> pdata;
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
        pdata.append(BrCoVDataItem(name, suspects, cases, deaths));
    }
    return pdata;
}
