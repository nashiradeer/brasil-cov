#ifndef __CORE_H__
#define __CORE_H__

#include <QString>
#include <QVector>
#include <QMutex>
#include <QThread>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTranslator>

namespace BrasilCoV
{
    class BrCoVDataItem;
    class BrCoVDataParser;
    class BrCoVDataManager;
    class BrCoVNetworkManager;
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

class BrCoVDataParser : public QThread
{
    Q_OBJECT

public:
    explicit BrCoVDataParser(QObject *parent = nullptr);
    virtual ~BrCoVDataParser();
    bool parse(QByteArray arr);
    QVector<BrCoVDataItem> data();

signals:
    void parsed();

protected:
    void run() override;

private:
    QMutex *mutex;
    QByteArray *rawdata;
    QVector<BrCoVDataItem> *dataparsed;
};

class BrCoVDataManager : public QObject
{
    Q_OBJECT

public:
    explicit BrCoVDataManager(QObject *parent = nullptr);
    virtual ~BrCoVDataManager();
    bool downloading();
    bool parsing();
    bool busy();
    bool fetchStates();
    bool fetchCountries();
    bool fetch(QUrl url);
    QVector<BrCoVDataItem> last();

private slots:
    void handlerReply(QNetworkReply *reply);

signals:
    void downloaded();
    void error(int statuscode);
    void parsed();

private:
    bool waitingdata;
    BrCoVDataParser *parser;
    QNetworkAccessManager *netmgr;
};

class BrCoVApplication : public QObject
{
    Q_OBJECT

public:
    explicit BrCoVApplication(QApplication *app, QObject *parent = nullptr);
    void init();
    void translate(QString lang);
    void setTheme(int theme);
    int getTheme();
    void updateSystemTheme();
    bool isSystemLight();

private:
    QApplication *application;
    QTranslator translator;

};

#endif
