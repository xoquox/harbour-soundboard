/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifdef QT_QML_DEBUG
#include <QtQuick>
#include <QtQml>
#endif

#include <sailfishapp.h>
#include "ccurl.h"

QStringList getList(char* url);

int main(int argc, char *argv[])
{

    QStringList dataList = getList("ftp://nfs/music/ircSounds/");
    QGuiApplication *app = SailfishApp::application(argc, argv);
    QQuickView *view = SailfishApp::createView();

    qmlRegisterType<CCurl>("ccurl", 1, 0, "CCurl");

    view->rootContext()->setContextProperty("soundsList", QVariant::fromValue(dataList));
    view->setSource(SailfishApp::pathTo("qml/harbour-soundboard.qml"));
    view->showFullScreen();
    return app->exec();
}

QStringList getList(char* url)
{
    CURLcode res;
    FILE *ftpfile;
    QStringList dataList;
    CURL *curl;
    char tempstring[255];

    /* local file name to store the file as */
    ftpfile = fopen("/tmp/ftp_list", "w+");

    curl = curl_easy_init();
    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, ftpfile);
        curl_easy_setopt(curl, CURLOPT_DIRLISTONLY, 1);

        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
    }
    fseek(ftpfile,SEEK_SET,0);
    while(!feof(ftpfile))
    {
        fgets(tempstring, 255, ftpfile);
        for(int i = 0; i < 255; i++)
        {
            if(tempstring[i] == '\n')
            {
                tempstring[i] = '\0';
                break;
            }
        }

        dataList.append(tempstring);
    }
    fclose(ftpfile);
    return dataList;
}
