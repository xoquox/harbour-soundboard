#ifndef CCURL_H
#define CCURL_H

#include <QObject>
#include <curl/curl.h>

class CCurl : public QObject
{
    Q_OBJECT
public:
    explicit CCurl(QObject *parent = 0);
    Q_INVOKABLE QString open(QString url);
private:
    CURL *curl;

};

#endif // CCURL_H

