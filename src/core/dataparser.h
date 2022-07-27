#ifndef _BRCOVDATAPARSER_H_
#define _BRCOVDATAPARSER_H_

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVector>
#include "dataitem.h"

QVector<BrCoVDataItem> brcovDataParser(QByteArray arr);

#endif // _BRCOVDATAPARSER_H
