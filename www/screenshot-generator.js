var screenshots = {
	"@1" : "Version 0.5.0 for Meego Harmattan N9/N950",
	"harmattan-screenshot-stationlist.png" : "The Station List View",
	"harmattan-screenshot-stationview.png" : "The Station Departures View",
	"@2" : "Version 0.4.3 for Maemo 5 N900",
	"screenshot-stationlist.png" : "The Station List View",
	"screenshot-stationview.png" : "The Station Departures View",
	"screenshot-stationlist-menu.png" : "The Station List Menu",
	"screenshot-stationview-menu.png" : "The Station Departures Menu",
};

function dismiss_picture()
{
	var parent = this.parentNode;
	parent.style.opacity = 0.0;
	parent.style.visibility = 'hidden';
	parent.display = 'none';
}

function present_picture()
{
	var display = document.getElementById('picture-display');
	parent.display = 'block';
	display.style.visibility = 'visible';
	display.style.opacity = 1.0;
	display.style.left = (window.width  - display.width) / 2;
	display.style.top = (window.height  - display.height) / 2;
	var picture = document.getElementById('picture-display-picture');
	picture.setAttribute('src', this.getAttribute('src'));
}

function generate_div(value, index, array)
{
	var screenshots = document.getElementById('screenshot-list');
	var screenshotDiv = document.createElement('div');
	screenshotDiv.setAttribute('class', 'screenshot');
	
	var p1Element = document.createElement('div');
	var p2Element = p1Element.cloneNode(true);
	
	var aElement = document.createElement('img');
	aElement.setAttribute('src', index);
	if (aElement.addEventListener) {
		aElement.addEventListener('click', present_picture, true);
	} else if (aElement.attachEvent) {
		aElement.attachEvent('onclick', show_picture);
	}

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

function generate_section(value, index, array)
{
	var screenshots = document.getElementById('screenshot-list');
	var sectionElement = document.createElement('h3');
	var captionElement = document.createTextNode(value);
	
	sectionElement.appendChild(captionElement);
	screenshots.appendChild(sectionElement);
}

function build_screenshot_list()
{
	for (var key in screenshots) {
		if (key.match(/^@.*/)) 
			generate_section(screenshots[key], key, screenshots);
		else
			generate_div(screenshots[key], key, screenshots);
	}

	var element = document.getElementById('picture-display-picture');
	if (element.addEventListener) {
		element.addEventListener('click', dismiss_picture, false);
	} else if (element.attachEvent) {
		window.attachEvent('onclick', dismiss_picture);
	}
}

if (window.addEventListener) {
	window.addEventListener('load', build_screenshot_list, false);
} else if (window.attachEvent) {
	window.attachEvent('onload', build_screenshot_list);
}
