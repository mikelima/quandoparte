var view = undefined

function loadStation(name)
{
    var component = Qt.createComponent("StationPage.qml");
    if (component.status == Component.Ready) {
        view = component.createObject(stationListPage)
        stationListPage.stationView = view
        pageStack.push(view)
        view.html = "<h1>Loading station " + name + "</h1><p>Lorem ipsum</p>"
        provider.stationSchedule(name)
    }
    else
        console.log('Cannot load component: ' + component.errorString());
}

function highlightSearch(s)
{
    // TODO compile RegExp on change, or find a way to cleanly use
    // stationListProxyModel.filterRegExp
    if (searchField.text.length) {
        var r = new RegExp(searchField.text, 'i')
        var match = r.exec(s)
        return s.replace(r, '<span style="text-decoration:underline">' +
                         match + '</span>')
    } else {
        return s
    }
}

