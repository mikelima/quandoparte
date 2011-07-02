var screenshots = {
	"screenshot-stationlist.png" : "The Station List View",
	"screenshot-stationview.png" : "The Station Departures View",
	"screenshot-stationlist-menu.png" : "The Station List Menu",
	"screenshot-stationview-menu.png" : "The Station Departures Menu",
};

function generate_div(value, index, array)
{
	var screenshots = document.getElementById('screenshot-list');
	var screenshotDiv = document.createElement('div');
	screenshotDiv.setAttribute('class', 'screenshot');
	
	var p1Element = document.createElement('div');
	var p2Element = p1Element.cloneNode(true);
	
	var aElement = document.createElement('a');
	aElement.setAttribute('href', index);

	var imgElement = document.createElement('img');
	imgElement.setAttribute('src', index);

	var captionElement = document.createTextNode(value);

	p1Element.appendChild(aElement);
	aElement.appendChild(imgElement);
	p2Element.appendChild(captionElement);

	screenshotDiv.appendChild(p1Element);
	screenshotDiv.appendChild(p2Element);
	screenshots.appendChild(screenshotDiv);
}

function build_screenshot_list()
{
	for (var key in screenshots)
		generate_div(screenshots[key], key, screenshots);
}

if (window.addEventListener) {
	window.addEventListener('load', build_screenshot_list, false);
} else if (window.attachEvent) {
	window.attachEvent('onload', build_screenshot_list);
}
