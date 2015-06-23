// function for resizing the windows.
var objectExp = {};

window.addEventListener("message", function(e){
    parent.postMessage(JSON.stringify(
            {"pos":JSON.parse(e.data).pos,"obj":JSON.parse(e.data).obj,"height":document.body.scrollHeight,"width":document.body.scrollWidth}
        )
        // this needs to contain the final interface source
        ,"*");
    objectExp.pos = JSON.parse(e.data).pos;
    objectExp.obj = JSON.parse(e.data).obj;

}, false);

// adding css styles nessasary for acurate 3D transformations.
var style = document.createElement('style');
style.type = 'text/css';
style.innerHTML = 'body, html{ height: 100%; margin:0; padding:0;}';
document.getElementsByTagName('head')[0].appendChild(style);
