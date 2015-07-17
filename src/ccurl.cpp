#include "ccurl.h"

CCurl::CCurl(QObject *parent) :
    QObject(parent)
{
}

QString CCurl::open(QString url)
{
    curl = curl_easy_init();
    if(curl)
    {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, url.toStdString().c_str());
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return url;
}
