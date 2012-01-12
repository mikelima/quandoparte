var view = undefined
var about = undefined

function showAboutPage()
{
    var component = Qt.createComponent("AboutPage.qml")
    if (component.status === Component.Ready) {
        about = component.createObject(stationListPage)
        pageStack.push(about)
    } else
        console.log('Cannot load component: ' + component.errorString());
}

function loadStation(name)
{
    var component = Qt.createComponent("StationPage.qml");
    if (component.status === Component.Ready) {
        view = component.createObject(stationListPage)
        stationListPage.stationView = view
        pageStack.push(view)
        view.name = name
    }
    else
        console.log('Cannot load component: ' + component.errorString());
}

function highlightSearch(s, color)
{
    // TODO compile RegExp on change, or find a way to cleanly use
    // stationListProxyModel.filterRegExp
    if (searchField.text.length) {
        var r = new RegExp(searchField.text, 'i')
        var match = r.exec(s)
        return s.replace(r, '<span style="text-decoration:underline;color:' + color + ';">' +
                         match + '</span>')
    } else {
        return s
    }
}

