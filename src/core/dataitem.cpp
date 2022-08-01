#include "dataitem.h"

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
