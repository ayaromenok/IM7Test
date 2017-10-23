import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtWebView 1.1
//import MagickTest 1.0

ApplicationWindow {
    visible: true
    width: 360
    height: 640
    title: qsTr("ImageMagick7 for Andoid - Test")

    signal sigTestAll(string value)

    function fnTestOmpAuto(result){
        console.log("OmpAuto:" + result)
        lbOmpAutoRes.text = result
    }

    function fnTestOmpOne(result){
        console.log("OmpOne:" + result)
        lbOmpOneThreadRes.text = result
    }

    function fnTestOmpTwo(result){
        console.log("OmpTwo:" + result)
        lbOmpTwoThreadRes.text = result
    }

    function fnTestOmpFour(result){
        console.log("OmpFour:" + result)
        lbOmpFourThreadRes.text = result
    }

    function fnTestOmpEight(result){
        console.log("OmpEight" + result)
        lbOmpEightThreadRes.text = result
        busyInd.running = false;
    }

    function fnTestAll(){
        console.log("fnTestAll()");
        busyInd.running = true;
        sigTestAll("0 1 2 4 8")
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page {
            ColumnLayout{
                id:mainLayout
                anchors.fill: parent
                anchors.margins: 10
                Layout.alignment: Qt.AlignTop

                Label {
                    id: lbAppInfo
                    text: qsTr("ImageMagic 7 for Android")
                    font.bold: true
                    font.pixelSize: 20
                    Layout.preferredWidth: 240
                    Layout.preferredHeight: 50
                    Layout.alignment: Qt.AlignHCenter
                }
                Label {
                    id: lbPerfTest
                    text: qsTr("OpenMP Performance Tests")
                    font.bold: true
                    font.pixelSize: 16
                    Layout.preferredWidth: 240
                    Layout.preferredHeight: 50
                    Layout.alignment: Qt.AlignHCenter
                }
                GridLayout{
                    Layout.fillWidth: true
                    columns: 2
                    Label {
                        id: lbOmpType
                        text: qsTr("Test type")
                        font.bold: true
                        Layout.preferredWidth: 240
                    }
                    Label {
                        id: lbOmpRes
                        text: qsTr("Result,\nmsec")
                        font.bold: true
                    }

                    Label {
                        id: lbOmpAuto
                        text: qsTr("OpenMP auto threads")
                    }
                    Label {
                        id: lbOmpAutoRes
                        text: qsTr("0")
                    }

                    Label {
                        id: lbOmpOneThread
                        text: qsTr("Single thread")
                    }
                    Label {
                        id: lbOmpOneThreadRes
                        text: qsTr("0")
                    }
                    Label {
                        id: lbOmpTwoThread
                        text: qsTr("Two threads")
                    }
                    Label {
                        id: lbOmpTwoThreadRes
                        text: qsTr("0")
                    }
                    Label {
                        id: lbOmpFourThread
                        text: qsTr("Four threads")
                    }
                    Label {
                        id: lbOmpFourThreadRes
                        text: qsTr("0")
                    }
                    Label {
                        id: lbOmpEightThread
                        text: qsTr("Eight thread")
                    }
                    Label {
                        id: lbOmpEightThreadRes
                        text: qsTr("0")
                    }
                }
                BusyIndicator{
                    id: busyInd;
                    Layout.alignment: Qt.AlignHCenter
                    running: false
                }

                Rectangle{
                    Layout.fillHeight: true
                }
                Button {
                    id: btAll
                    text: qsTr("Run all tests")
                    Layout.alignment: Qt.AlignHCenter
                    Layout.preferredWidth: 280
                    onClicked:fnTestAll()
                }
            }


        }

        Page {
            WebView {
                    anchors.fill: parent
                    url: "qrc:/IM7TestInfo.html"
                }
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("Performance tests")
        }
        TabButton {
            text: qsTr("Additional info")
        }
    }
}