# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = harbour-soundboard

CONFIG += sailfishapp

SOURCES += src/harbour-soundboard.cpp \
    src/ccurl.cpp

OTHER_FILES += qml/harbour-soundboard.qml \
    qml/cover/CoverPage.qml \
    rpm/harbour-soundboard.changes.in \
    rpm/harbour-soundboard.spec \
    rpm/harbour-soundboard.yaml \
    translations/*.ts \
    harbour-soundboard.desktop \
    qml/SoundBoardPage.qml

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/harbour-soundboard-de.ts

HEADERS += \
    src/ccurl.h

LIBS *= -lcurl
