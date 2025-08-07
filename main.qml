import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts

Window {
    width: 1512
    height: 922
    visible: true
    title: qsTr("Hello World")

    Text{
        id: score1
        text: "Score: " + control.showScore()
        color: "black"
        x: 50
        y: 50
        font.pixelSize: 25

        Connections
        {
            target: control
            function onScoreChanged()
            {
                score1.text = "Score: " + control.showScore()
            }
        }
    }

    Rectangle
    {
        id: startGameBtn
        anchors.centerIn: parent
        visible: true
        Text {
            id: startGame
            text: qsTr("Start Game")
            color: "white"
            anchors.centerIn: parent
            font.bold: true
            font.pixelSize: 15
        }
        width: 100
        height: 50
        color: "black"
        opacity: 0.9

        MouseArea
        {
            hoverEnabled: true
            anchors.fill: parent
            onClicked:
            {
                control.startGame()
                startGameBtn.visible = false
            }
            onEntered:
            {
                startGameBtn.color = "gray"
            }
            onExited:
            {
                startGameBtn.color = "black"
            }
        }
    }

    Rectangle
    {
        id: gameOverlay
        anchors.fill: parent
        visible: false
        color: "black"
        opacity: 0.7
        z: 1001

        ColumnLayout
        {
            anchors.centerIn: parent
            spacing: 20
            Text {
                id: gameOver
                text: qsTr("Game Over")
                color: "white"
                anchors.horizontalCenter: parent
            }

            RowLayout
            {
                spacing: 20
                Rectangle
                {
                    id: closeBtn
                    width: 300
                    height: 35
                    color: "gray"
                    radius: 20
                    Text
                    {
                        text: qsTr("Close")
                        color: "white"
                        anchors.centerIn: parent
                    }

                    MouseArea
                    {
                        hoverEnabled: true
                        anchors.fill: parent
                        onClicked:
                        {
                            Qt.quit()
                        }
                        onEntered:
                        {
                            closeBtn.color = "blue"
                        }
                        onExited:
                        {
                            closeBtn.color = "gray"
                        }
                    }
                }
                Rectangle
                {
                    id: restartBtn
                    width: 300
                    height: 35
                    color: "gray"
                    radius: 20

                    Text
                    {
                        text: qsTr("Restart")
                        color: "white"
                        anchors.centerIn: parent
                    }

                    MouseArea
                    {
                        hoverEnabled: true
                        anchors.fill: parent
                        onClicked:
                        {
                            control.restartGame();
                            gameOverlay.visible = false
                        }
                        onEntered:
                        {
                            restartBtn.color = "blue"
                        }
                        onExited:
                        {
                            restartBtn.color = "gray"
                        }
                    }
                }
            }
        }
    }

    Connections
    {
        target: control
        function onGameOver()
        {
            gameOverlay.visible = true
        }
    }

    Rectangle {
        id: move
        width: 50
        height: 50
        color: "red"
        x: control.x
        y: control.y
        focus: true
        Keys.onPressed: (event) =>
                        {
                            if(event.key === Qt.Key_Left)
                            {
                                control.moveLeft()
                            }
                            if(event.key === Qt.Key_Right)
                            {
                                control.moveRight()
                            }
                            if(event.key === Qt.Key_Up)
                            {
                                control.applyThrust()
                            }
                            if(event.key === Qt.Key_Space)
                            {
                                control.fireBullet()
                            }
                            if(event.key === Qt.Key_Shift)
                            {
                                control.createEnemy()
                            }
                        }
        Keys.onReleased: (event) =>
                         {
                             if(event.key === Qt.Key_Left || event.key === Qt.Key_Right)
                             {
                                 control.stopMovement()
                             }
                         }
    }

    Repeater
    {
        model: control.bullets
        delegate: Bullet{}

    }

    Repeater
    {
        model: control.enemies
        delegate: Enemy{}

    }



}

