var shipsJson = {};
var ships = [];


var getShipsJson = function ()
{


    var oReq = new XMLHttpRequest();
    oReq.onload = reqListener;
    oReq.open("get", "/jsonFiles/ships.json", false);
    oReq.send();

    function reqListener(e) {

        shipsJson = JSON.parse(this.responseText);
        //console.log('Type of shipsJSON:', shipsJson);
        //ships = shipsJson['frames'];
        
    }
    
    
}

getShipsJson();

