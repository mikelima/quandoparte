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

function loadStation(name, code)
{
    var component = Qt.createComponent("StationPage.qml");
    if (component.status === Component.Ready) {
        view = component.createObject(stationListPage)
        stationListPage.stationView = view
        pageStack.push(view)

        /*
            XXX Ugliness ahead! Changing the name triggers the station
            schedule to be fetched. So any extra data (the code specifically)
            must be set before changing the name.
         */
        if (code !== undefined) view.code = code
        view.name = name
    }
    else
        console.log('Cannot load component: ' + component.errorString());
}

function highlightSearch(s, color)
{
    // TODO compile RegExp on change, or find a way to cleanly use
    // stationListProxyModel.filterRegExp
    if (searchPattern.length) {
        var r = new RegExp(searchPattern, 'i')
        var match = r.exec(s)
	console.log('s is ' + s);
	if (match) {
		return s.replace(r, '<font color="' + color + '">' +
				match + '</font>')
	} else {
		return s
	}
    } else {
        return s
    }
}

