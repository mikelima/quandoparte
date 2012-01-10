function setDisplayIndex(index) {
    console.log("Selection changed to: " + index)
    if (optionList === undefined || optionList.count === 0 ||
            optionList.get(index) === undefined) {
        header.text = " "
    } else {
        header.text = optionList.get(index).name
        console.log("Selection text is: " + header.text)
    }
}

function init()
{
    console.log("option length " + header.options.length)
    for (var i = 0; i < header.options.length; ++i) {
        console.log("option " + header.options[i])
        optionList.append({name: header.options[i]})
        Private.setDisplayIndex(selectedIndex)
    }
}
