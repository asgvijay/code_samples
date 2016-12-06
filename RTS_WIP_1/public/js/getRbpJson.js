var rbpJson = {};
var rbp = [];


var getRbpJson = function ()
{


    var oReq = new XMLHttpRequest();
    oReq.onload = reqListener;
    oReq.open("get", "/jsonFiles/rbp.json", false);
    oReq.send();

    function reqListener(e) {

        rbpJson = JSON.parse(this.responseText);
        //console.log('Type of shipsJSON:', rbpJson);
        //rbp = rbpJson['frames'];
        
    }
    
    
}

getRbpJson();
