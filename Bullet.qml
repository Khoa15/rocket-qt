import QtQuick 2.15

Rectangle{
    id: bullet
    width: 10
    height: 30
    color: "black"
    x: model.x
    y: model.y
}
