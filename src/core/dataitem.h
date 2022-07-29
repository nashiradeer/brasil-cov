#ifndef _BRCOVDATAITEM_H_
#define _BRCOVDATAITEM_H_

#include <QString>

namespace BrasilCoV {
    class BrCoVDataItem;
}

class BrCoVDataItem
{
public:
    explicit BrCoVDataItem(QString name, quint32 suspects, quint32 cases, quint32 deaths);
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

#endif // _BRCOVDATAITEM_H
