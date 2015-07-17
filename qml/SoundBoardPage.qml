import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page
    SilicaListView {
        width: 480; height: 800
        id: listView
        model: soundsList
        anchors.fill: parent
        header: PageHeader {
            title: qsTr("Backspace Soundboard")
        }
        delegate: BackgroundItem {
            id: delegate
            Text {

                x: Theme.paddingLarge
                text: modelData
                anchors.verticalCenter: parent.verticalCenter
                color: delegate.highlighted ? Theme.highlightColor : Theme.primaryColor
            }
            onClicked: myCurl.open("https://int.bckspc.de/spielwiese/soundboard.php?play=" + modelData);

        }
        VerticalScrollDecorator {}
    }
}
