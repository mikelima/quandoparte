var items = {
	"./index.html" : "Home",
	// disable for now because Nokia QA does not want competition
	//"https://garage.maemo.org/frs/?group_id=2194" : "Download",
	"./screenshots.html" : "Screenshots",
	"https://garage.maemo.org/forum/forum.php?forum_id=7093" : "Support & Help"
}

function generate_anchor(value, index, array)
{
	var navigation = document.getElementById('navigation');
	var anchorElement = document.createElement('a');
	var captionElement = document.createTextNode(value);
	var spacerElement = document.createElement('span');
	
	anchorElement.setAttribute("href", index);
	spacerElement.setAttribute("class", "spacer");
	anchorElement.appendChild(captionElement);
	navigation.appendChild(anchorElement);
	navigation.appendChild(spacerElement);
}

function build_navigation_bar()
{
	for (var key in items) {
		generate_anchor(items[key], key, items);
	}
}

if (window.addEventListener) {
	window.addEventListener('load', build_navigation_bar, false);
} else if (window.attachEvent) {
	window.attachEvent('onload', build_navigation_bar);
}
