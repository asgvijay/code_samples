//http://simonsarris.com/blog/510-making-html5-canvas-useful



function GameState(canvas, menu) {
  this.timerId = null;
  this.canvas = canvas;
  this.menu = menu;
  this.width = canvas.width;
  this.height = canvas.height;
  this.ctx = canvas.getContext('2d');
  this.menuCtx = menu.getContext('2d');
  var backgroundWidth = 1500;  
  var backgroundHeight = 844;
  this.camera = new Camera(map, 830, 500, backgroundWidth, backgroundHeight);
  // This complicates things a little but but fixes mouse co-ordinate problems
  // when there's a border or padding. See getMouse for more detail
  var stylePaddingLeft, stylePaddingTop, styleBorderLeft, styleBorderTop;
  if (document.defaultView && document.defaultView.getComputedStyle) {
    this.stylePaddingLeft = parseInt(document.defaultView.getComputedStyle(canvas, null)['paddingLeft'], 10)      || 0;
    this.stylePaddingTop  = parseInt(document.defaultView.getComputedStyle(canvas, null)['paddingTop'], 10)       || 0;
    this.styleBorderLeft  = parseInt(document.defaultView.getComputedStyle(canvas, null)['borderLeftWidth'], 10)  || 0;
    this.styleBorderTop   = parseInt(document.defaultView.getComputedStyle(canvas, null)['borderTopWidth'], 10)   || 0;
  }
  // Some pages have fixed-position bars (like the stumbleupon bar) at the top or left of the page
  // They will mess up mouse coordinates and this fixes that
  var html = document.body.parentNode;
  this.htmlTop = html.offsetTop;
  this.htmlLeft = html.offsetLeft;

  this.player = new Player();
  this.aiPlayer = new AIModule();

  this.gameLoading = true;
  this.gameOverVar = false;  
  this.gameType = null;
  this.savingGame = false;
  this.newGame = {type:"NEW GAME"};
  var currPosNewGame = {x:85, y:75};
  this.newGame.currPos = currPosNewGame;  
  this.loadGame = {type:"LOAD GAME"};
  var currPosLoadGame = {x:85, y:175};
  this.loadGame.currPos = currPosLoadGame;
  var gameTypeSize = {x:275, y:30};
  this.newGame.size = gameTypeSize;
  this.loadGame.size = gameTypeSize;

  this.easy = {type:"EASY"};
  var currPosEasy = {x:85, y:75};
  this.easy.currPos = currPosEasy;  
  this.hard = {type:"HARD"};
  var currPosHard = {x:85, y:175};
  this.hard.currPos = currPosHard;
  var gameDifficultySize = {x:200, y:30};
  this.easy.size = gameDifficultySize;
  this.hard.size = gameDifficultySize;
  this.dampner = 0;

  this.difficulty = 'hard';
  this.difficultyChosen = false;
  
  this.units = {
		pCombat: [],
		pGatherer: [],
		aiCombat: [],
		aiGatherer: []
  };

  this.unitUpdates = [];

  this.buildings = {
		pBuildings: [],
		aiBuildings: [],
		pTowers: [],
		aiTowers: [],
		pWalls: [],
		aiWalls: []
		
  };

  this.resources = [];
	
  this.groups = {
      pGroups: [],
      aiGroups: []
  };

  this.projectiles = [];

  this.selectedBuilding = [];
  this.selectRectangle = [];
  this.buildingSelectionRectangle = [];
  this.buildingToBuild = [];
  this.menuItems = [];

  var selectRectInitialX = 0;
  var selectRectInitialY = 0;
  var isDragging = false;
  var placingBuilding = false;
    
  // NEW VIJAY: creating new image variables referening the Atlases we are using
  this.shipsAtlas = new Image();
  this.shipsAtlas.src = 'Unit_Code.1/Sprites/ships.png';
  this.buildingResourceProjAtlas = new Image();
  this.buildingResourceProjAtlas.src = 'Unit_Code.1/Sprites/rbp.png';

  // Variable to record Clan Resource Holdings

  this.clan1Resources = 0;
  this.clan2Resources = 0;
    
  var myState = this;
  
  // This event listener handles camera movement
  document.addEventListener("keydown", function(e) {
    var moveX = 0;
    var moveY = 0;
    if(e.keyCode == 39) { moveX = 1; }
    if(e.keyCode == 37) { moveX = -1; }
    if(e.keyCode == 38) { moveY = -1; }
    if(e.keyCode == 40) { moveY = 1; }    
    s.camera.move(moveX, moveY);    
  });

  // This prevents an error with double clicking on the canvas
  canvas.addEventListener('selectstart', function(e) { e.preventDefault(); return false; }, false);

  // This handles mouse click events
  canvas.addEventListener('mousedown', function(e) {
    var mouse = myState.getMouse(e);
    var mx = mouse.x;
    var my = mouse.y;
    var units = myState.units;
    var buildings = myState.buildings;
    var selectedBuilding = myState.selectedBuilding;
    var playerBuilding = buildings.pBuildings.length;
    var playerCombUnits = units.pCombat.length;    
    var playerGathererUnits = units.pGatherer.length;
    var aiBuilding = buildings.aiBuildings.length;
    var aiCombUnits = units.aiCombat.length;    
    var aiGathererUnits = units.pGatherer.length;    
    var ug = units.pGatherer.length;    
    var resLength = myState.resources.length;
    var updateObject;

    if(myState.gameLoading)
    {
      // Handle user choices to start a new game or load an old game
      // Create loop that requires user to select an option
      // Once that option is chosen, start second loop until user
      // chooses a difficulty
      // Once both choices made, break loop and start game
      if(myState.isObjectSelected(myState.newGame, mx, my))
      {
        myState.gameType = "NEW";
        myState.gameLoading = false;
        myState.clear();
        drawGameMenuDifficulties(myState);    
        return;
      }
      else if(myState.isObjectSelected(myState.loadGame, mx, my))
      {
        myState.gameType = "LOAD";
        myState.difficultyChosen = true;
        myState.gameLoading = false;        
        var units = JSON.parse(localStorage.getItem("units"));        
        var buildings = JSON.parse(localStorage.getItem("buildings"));
        var resources = JSON.parse(localStorage.getItem("resources"));
        var player = JSON.parse(localStorage.getItem("player"));
        var projectiles = JSON.parse(localStorage.getItem("projectiles"));
        var difficulty = JSON.parse(localStorage.getItem("difficulty"));
        var aiPlayer = JSON.parse(localStorage.getItem("aiPlayer"));
        myState.loadSavedInformation(units, buildings, resources, player, projectiles, difficulty, aiPlayer);
        // NEED TO HANDLE THIS SITUATION. HOW DO WE LOAD THE GAME FROM A SAVED FILE?
        return;
      }
    }

    if(!myState.gameLoading && !myState.difficultyChosen)
    {
      if(myState.isObjectSelected(myState.easy, mx, my))
      {
        myState.difficultyChosen = true;
        myState.difficulty = "easy";
        initializeGameUnitsAndBuildings();
        return;
      }
      else if(myState.isObjectSelected(myState.hard, mx, my))
      {
        myState.difficultyChosen = true;
        myState.difficulty = "hard";
        initializeGameUnitsAndBuildings();        
        return;
      }      
    }

    if(placingBuilding)
    {      
      if(myState.buildingSelectionRectangle[0].color == "blue")
      {
        var rect = myState.buildingSelectionRectangle[0];
        switch (myState.buildingToBuild[0].type)
        {
          case "Clan1_Lab":
            s.addPlayerBuilding(new Clan1_Lab(rect.currPos.x, rect.currPos.y));
            break;
          case "Clan1_Factory1":      
            s.addPlayerBuilding(new Clan1_Factory1(rect.currPos.x, rect.currPos.y));
            break;
          case "Clan1_Factory2":
            s.addPlayerBuilding(new Clan1_Factory2(rect.currPos.x, rect.currPos.y));
            break;
          case "Clan1_Factory3":
            s.addPlayerBuilding(new Clan1_Factory3(rect.currPos.x, rect.currPos.y));
            break;       
          case "Clan1_MissileTower":
            s.addPlayerTowers(new Clan1_MissileTower(rect.currPos.x, rect.currPos.y));
            break;
          case "Clan1_Tower":
            s.addPlayerTowers(new Clan1_Tower(rect.currPos.x, rect.currPos.y));
            break;
          case "Clan1_Training1":
            s.addPlayerBuilding(new Clan1_Training1(rect.currPos.x, rect.currPos.y));
            break;
          case "Clan1_Training2":
            s.addPlayerBuilding(new Clan1_Training2(rect.currPos.x, rect.currPos.y));
            break;   
          case "Clan1_Training3":          
            s.addPlayerBuilding(new Clan1_Training3(rect.currPos.x, rect.currPos.y));
            break;                      
        }  
        myState.player.useResources(myState.buildingToBuild[0].cost);                      
        myState.buildingToBuild.splice(0,1);
        myState.buildingSelectionRectangle.splice(0,1);
        placingBuilding = false;
        return;        
      }

      // VIJAY: added this else statement to prevent the menu from saving building choices if user doesn't place
          // building after selection
      else {
        placingBuilding = false;
        myState.buildingToBuild.splice(0,1);
        myState.buildingSelectionRectangle.splice(0,1);
        return;
      }
    }

    if(e.shiftKey)
    {
      for (var i = 0; i < playerCombUnits; i++)
      {
        if (units.pCombat[i].selected)
        {
          updateObject.destPos = {x:mx,y:my};
          updateObject.state = "patrol";
          updateObject.selected = false;     
          units.pCombat[i].update(updateObject);
        }
      }
      return;
    }
    ////////////////////////////////////////////////////////
    /////////////BEGIN FIGHTER BLOCK 1 /////////////////////
    ////////////////////////////////////////////////////////
    // Iterate through all player Fighter Units
    // If any unit is SELECTED, we will iterate through all other units
    // to see if another unit has been selected. This block
    // then sends information about the relationship between
    // the two hypothetically SELECTED units, ie "on attack", etc
    // This looks for combat units that have been selected


    for (i = 0; i < playerCombUnits; i++)
    {
      var otherObjectSelected = false;            
      // If a unit has been selected...
      if (units.pCombat[i].selected)
      {      
        // Checks to see if user clicked on a player combat unit
        for (var y = 0; y < playerCombUnits; y++)
        {
          if (units.pCombat[i] !== units.pCombat[y])
          {
            var unitUpdates = myState.selectOtherFriendlyUnit(units.pCombat[y], mx, my);
            if(unitUpdates)
            {
              units.pCombat[i].update(unitUpdates[0]);
              units.pCombat[y].update(unitUpdates[1]);
              otherObjectSelected = true;
              return;
            }            
          }
        }    

        // Checks to see if user clicked on a player gatherer
        for (y = 0; y < playerGathererUnits; y++)
        {
          unitUpdate = myState.selectOtherFriendlyUnit(units.pGatherer[y], mx, my);
          if(unitUpdates)
          {
            units.pCombat[i].update(unitUpdate[0]);
            units.pGatherer[y].update(unitUpdate[1]);
            otherObjectSelected = true;
            return;
          }          
        }        

        // Check to see if user clicked on an AI combat unit
        for (y = 0; y < aiCombUnits; y++)
        {
          unitUpdate = myState.selectOtherEnemyUnit(units.aiCombat[y], mx, my);
          if(unitUpdate)
          {
            units.pCombat[i].update(unitUpdate);
            otherObjectSelected = true;
            //return;
          }          
        }   

        // Check to see if user clicked on an AI gatherer
        for (y = 0; y < aiGathererUnits; y++)
        {
          unitUpdate = myState.selectOtherEnemyUnit(units.aiGatherer[y], mx, my);
          if(unitUpdate)
          {
            units.pCombat[i].update(unitUpdate); 
            otherObjectSelected = true;         
          }          
        }           

        // Checks to see if user clicked on a player building
        for (y = 0; y < playerBuilding; y++) {
          unitUpdate = myState.selectOtherFriendlyBuilding(buildings.pBuildings[y], mx, my);
          {
            if(unitUpdate)
            {
              units.pCombat[i].update(unitUpdate[0]);
              buildings.pBuildings[y].update(unitUpdate[1]);
              selectedBuilding.splice(0,1);
              selectedBuilding.push(buildings.pBuildings[y]);  
              otherObjectSelected = true;        
              return;              
            }
          }
        }

        // Checks to see if user clicked on an AI building
        for (y = 0; y < aiBuilding; y++) {
          unitUpdate = myState.selectOtherEnemyBuilding(buildings.aiBuildings[y], mx, my);
          if (unitUpdate)
          {
            units.pCombat[i].update(unitUpdate);
            otherObjectSelected = true;
          }          
        }            

        // Checks to see if user clicked on a resource
        for (y = 0; y < resLength; y++) {
            var resourceUpdate = myState.selectResource(myState.resources[y], mx, my);
            if (resourceUpdate)
            {
                myState.resources[y].update(resourceUpdate);
                otherObjectSelected = true;
                return;
            }
        }           

        // If the user has clicked on some unoccupied point on the screen, send those coordinates to the unit
        // and begin movement
        if(!otherObjectSelected)
        {
          updateObject = {};
          updateObject.projectileReady = false;
          updateObject.destPos = {x:mx,y:my};
          updateObject.state = "enroute";
          updateObject.selected = false;
          units.pCombat[i].update(updateObject); 
        }        
      }
    }


    ////////////////////////////////////////////////////////
    /////////////END FIGHTER BLOCK 1 /////////////////////
    ////////////////////////////////////////////////////////






    ////////////////////////////////////////////////////////
    /////////////BEGIN COLLECTOR BLOCK 2 /////////////////////
    ////////////////////////////////////////////////////////

    // NOTES: SAME NOTES AS SEEN IN FIGHTER BLOCK 1

    // Same process for combat units, but with gatherers
    for (i = 0; i < playerGathererUnits; i++)
    {       
      var otherObjectSelected = false;                  
      // If a unit has been selected...
      if (units.pGatherer[i].selected)
      {         
        // Checks to see if user clicked on a player combat unit
        for (y = 0; y < playerCombUnits; y++)
        {
          updateObject = myState.selectOtherFriendlyUnit(units.pCombat[y], mx, my);
          if (updateObject)
          {
            units.pGatherer[i].update(updateObject[0]);
            units.pCombat[y].update(updateObject[1]);
            otherObjectSelected = true;
            return;
          }
        }

        // Checks to see if user clicked on a player gatherer
        for (y = 0; y < playerGathererUnits; y++)
        {
          if (units.pGatherer[i] !== units.pGatherer[y])
          {
            updateObject = myState.selectOtherFriendlyUnit(units.pGatherer[y], mx, my);
            if (updateObject)
            {     
              units.pGatherer[i].update(updateObject[0]);
              units.pGatherer[y].update(updateObject[1]);            
              otherObjectSelected = true;              
              return;
            }
          }
        }

        // Checks to see if user clicked on a resource
        for (var x = 0; x < resLength; x++)
        {
          updateObject = myState.selectResource(myState.resources[x], mx, my, 1);

          if (updateObject)
          {       
            myState.resources[x].update(updateObject[0]);          
            units.pGatherer[i].update(updateObject[1]);
            otherObjectSelected = true;                                  
          }
        }

        if(!otherObjectSelected)
        {
          var unitUpdate = {};
          unitUpdate.destPos = {x:mx,y:my};      
          unitUpdate.state = 'enroute';
          unitUpdate.resource = null;
          unitUpdate.selected = false;
          units.pGatherer[i].update(unitUpdate);
        }        
      }
    }

    ////////////////////////////////////////////////////////
    /////////////END COLLECTOR BLOCK 2 /////////////////////
    ////////////////////////////////////////////////////////







    ////////////////////////////////////////////////////////
    /////////////BEGIN BUILDING BLOCK 3 /////////////////////
    ////////////////////////////////////////////////////////
    // Same process for units, but with buildings
    for (i = 0; i < playerBuilding; i++)
    {      
      // If a building has already been selected...
      if (buildings.pBuildings[i].selected)
      {
        
        // Update the current building's status
        updateObject = {};
        updateObject.selected = false;
        buildings.pBuildings[i].update(updateObject); 

        // Check if user clicked on another building
        for (y = 0; y < playerBuilding; y++)
        {
          var buildingUpdate = myState.selectOtherFriendlyBuilding(buildings.pBuildings[y], mx, my);
          if (buildingUpdate)
          {
            buildings.pBuildings[i].update(buildingUpdate[0]);
            buildings.pBuildings[y].update(buildingUpdate[1]);
            selectedBuilding.splice(0,1);
            selectedBuilding.push(buildings.pBuildings[y]);
            myState.manageMenus(myState.selectedBuilding[0], myState.menuItems);
            return;            
          }
        }          
      }
    }

    ////////////////////////////////////////////////////////
    /////////////END BUILDING BLOCK 3 /////////////////////
    ////////////////////////////////////////////////////////






    ////////////////////////////////////////////////////////
    /////////////BEGIN FIGHTER BLOCK 4 /////////////////////
    ////////////////////////////////////////////////////////

    // NOTE: HOW ARE WE CHECKING IF NO UNITS ARE SELECTED
    // DO WE NEED AN IF-STATEMENT HERE????

    // No unit is currently selected; check if user clicked on a player combat unit
    for (i = 0; i < playerCombUnits; i++)
    {   
      // Checks if user clicked on a unit and updates its status accordingly
      if (myState.isObjectSelected(units.pCombat[i], mx, my))
      {
        // UNIT UPDATE HERE
        units.pCombat[i].update({selected: true});
        return;
      }      
    }

    ////////////////////////////////////////////////////////
    /////////////END FIGHTER BLOCK 4 /////////////////////
    ////////////////////////////////////////////////////////




    ////////////////////////////////////////////////////////
    /////////////BEGIN COLLECTOR BLOCK 5 /////////////////////
    ////////////////////////////////////////////////////////

    // NOTE: HOW ARE WE CHECKING IF NO UNITS ARE SELECTED
    // DO WE NEED AN IF-STATEMENT HERE????


    // No unit is currently selected; check if user clicked on a player gatherer unit
    for (i = 0; i < playerGathererUnits; i++)
    {   
      // Checks if user clicked on a unit and updates its status accordingly
      if (myState.isObjectSelected(units.pGatherer[i], mx, my))
      {
        units.pGatherer[i].update({selected: true});
        return;
      }      
    }

    ////////////////////////////////////////////////////////
    /////////////END COLLECTOR BLOCK 5 /////////////////////
    ////////////////////////////////////////////////////////




    ////////////////////////////////////////////////////////
    /////////////BEGIN BUILDING BLOCK 6 /////////////////////
    ////////////////////////////////////////////////////////

    // NOTE: HOW ARE WE CHECKING IF NO UNITS ARE SELECTED
    // DO WE NEED AN IF-STATEMENT HERE????


    
    // Check if building was selected
    for (i = 0; i < playerBuilding; i++)
    {
      // See if the user clicked on one, then update it accordingly
      if (myState.isObjectSelected(buildings.pBuildings[i], mx, my))
      {
        selectedBuilding.splice(0,1);
        selectedBuilding.push(buildings.pBuildings[i]);  
        buildings.pBuildings[i].update({selected: true});
        myState.manageMenus(myState.selectedBuilding[0], myState.menuItems);
        return;
      }
    }

    ////////////////////////////////////////////////////////
    /////////////END BUILDING BLOCK 5 /////////////////////
    ////////////////////////////////////////////////////////





    ////////////////////////////////////////////////////////
    /////////////BEGIN RESOURCE BLOCK 6 /////////////////////
    ////////////////////////////////////////////////////////

    // NOTE: HOW ARE WE CHECKING IF NO UNITS ARE SELECTED
    // DO WE NEED AN IF-STATEMENT HERE????


    // Check if resource is selected
    for (i = 0; i < resLength; i++)
    {
      if(myState.resources[i].selected)
      {
        // Set current resource selection to false
        myState.resources[i].update({selected: false});
      }
        
      if (myState.isObjectSelected(myState.resources[i], mx, my))
      {
        // Set new resource selection to true
        myState.resources[i].update({selected: true});   
        return;
      }  
    }



    ////////////////////////////////////////////////////////
    /////////////END RESOURCE BLOCK 6 /////////////////////
    ////////////////////////////////////////////////////////





    // Click & Drag functionality
    selectRectInitialX = mouse.x;
    selectRectInitialY = mouse.y;
    isDragging = true;
    myState.selectRectangle.push(new SelectRect(selectRectInitialX, selectRectInitialY, 0, 0, "blue"));
    myState.manageMenus();

  }, true);  

  canvas.addEventListener('mousemove', function(e) {
    if (isDragging)
    {
      mouse = myState.getMouse(e);
      mx = mouse.x;
      my = mouse.y;
      var width =  Math.abs(selectRectInitialX-mx);
      var height = Math.abs(selectRectInitialY-my);
      var xCoord = null;
      var yCoord = null;

      if (selectRectInitialX <= mx)
      {
        xCoord = selectRectInitialX;
      }
      else
      {
        xCoord = mx;
      }

      if (selectRectInitialY <= my)
      {
        yCoord = selectRectInitialY;
      }
      else
      {
        yCoord = my; 
      }

      updateObj = {};
      var size = {y:height,x:width};
      updateObj.currPos = {x:xCoord,y:yCoord};
      updateObj.size = size;

      myState.selectRectangle[0].updateSelectRectInfo(updateObj);
    }

    if(placingBuilding)   
    {
      var mouse = myState.getMouse(e);
      var mx = mouse.x;
      var my = mouse.y;

      var updateObj = {};
      updateObj.currPos = {x:mx,y:my};

      if(myState.selectRectCollision(myState.buildingSelectionRectangle[0].retrieveSelectRectInfo()))
      {
        updateObj.blocked = true;
      }

      myState.buildingSelectionRectangle[0].updateSelectRectInfo(updateObj);      
    } 
  });

  canvas.addEventListener('mouseup', function(e) {
    if (isDragging)
    {
      isDragging = false;
      var mouse = myState.getMouse(e);
      var mx = mouse.x;
      var my = mouse.y;
      var width =  Math.abs(selectRectInitialX-mx);
      var height = Math.abs(selectRectInitialY-my);
      var xCoord = 0;
      var yCoord = 0;

      if (selectRectInitialX <= mx)
      {
        xCoord = selectRectInitialX;
      }
      else
      {
        xCoord = mx;
      }

      if (selectRectInitialY <= my)
      {
        yCoord = selectRectInitialY;
      }
      else
      {
        yCoord = my; 
      }

      var selectionBox = new SelectRect(xCoord, yCoord, width, height);

      for (var i = myState.units.pCombat.length-1; i >= 0; i--)
      {      

        // Checks if user clicked on a unit and updates its status accordingly
        if (detectCollision(selectionBox, myState.units.pCombat[i]))
        {
          myState.units.pCombat[i].update({selected: true});
        }  
      }    
      for (i = myState.units.pGatherer.length-1; i >= 0; i--)
      {      
        // Checks if user clicked on a unit and updates its status accordingly
        if (detectCollision(selectionBox, myState.units.pGatherer[i]))
        {
          myState.units.pGatherer[i].update({selected: true});
        }  
      }       
      myState.selectRectangle.splice(0, 1);       
      }
  });


  menu.addEventListener('mousedown', function(e) {
    var mouse = myState.getMouseMenu(e);
    var mx = mouse.x;
    var my = mouse.y;
    var selectedBuilding = myState.selectedBuilding;
    var menuItems = myState.menuItems;
    var m = menuItems.length;

    if(myState.buildingToBuild.length > 0)
    {
      myState.buildingToBuild.splice(0,1);      
    }

    if(myState.buildingSelectionRectangle.length > 0)
    {
        myState.buildingSelectionRectangle.splice(0,1);
    }    

    for (var i = m-1; i >= 0; i--)
    {
      var menuItemInfo = getMenuItemInfo(menuItems[i]);      
      if (myState.isMenuObjectSelected(menuItemInfo, mx, my))
      {
        if (menuItemInfo.type == "Clan1_Lab" ||
            menuItemInfo.type == "Clan1_Factory1" ||
            menuItemInfo.type == "Clan1_Factory2" ||
            menuItemInfo.type == "Clan1_Factory3" ||
            menuItemInfo.type == "Clan1_MissileTower" ||
            menuItemInfo.type == "Clan1_Tower" ||
            menuItemInfo.type == "Clan1_Training1" ||
            menuItemInfo.type == "Clan1_Training2" ||
            menuItemInfo.type == "Clan1_Training3")
        {              
          // Implement function to show user where to place building
          if (menuItemInfo.cost <= myState.player.getResources())
          {
            placingBuilding = true;
            myState.chooseBuildingArea(menuItemInfo)
          }
        }
        else
        {
          if (menuItemInfo.cost <= myState.player.getResources())
          {
            myState.player.useResources(menuItemInfo.cost);
            myState.selectedBuilding[0].update({anotherUnit: true});
          }
        }
        return;
      }                  
    }    
  }, true);

  if(this.gameLoading)
  {
    drawGameMenuChoices(myState);
  }
}

GameState.prototype.chooseBuildingArea = function(building)
{
    this.buildingSelectionRectangle.push(new SelectRect(0, 0, building.size.w, building.size.h));
    this.buildingToBuild.push(building);
};

GameState.prototype.addNewUnit = function(building, unit) 
{
  var unitToCreate = null;
  // 1 = playerCombat, 2 = aiCombat, 3 = playerGatherer, 4 = aiGatherer
  var unitType = null;
  if (unit)
  {
    switch (unit.type)
    {    
      // Clan 1 units
      case "Fighter1":
        unitType = 1;
        unitToCreate = new Clan1_Fighter1(building.currPos.x+70, building.currPos.y);
        break;
      case "Fighter2":
        unitType = 1;
        unitToCreate = new Clan1_Fighter2(building.currPos.x+70, building.currPos.y);
        break;
      case "Fighter3":
        unitType = 1;      
        unitToCreate = new Clan1_Fighter3(building.currPos.x+70, building.currPos.y);
      break;
      case "armedvehicle":
        unitType = 1;
        unitToCreate = new Clan1_Vehicle1(building.currPos.x+70, building.currPos.y);
      break;
      case "warbus":
        unitType = 1;
        unitToCreate = new Clan1_Vehicle2(building.currPos.x+70, building.currPos.y);
      break;
      case "semitruck":
        unitType = 1;
        unitToCreate = new Clan1_Vehicle3(building.currPos.x+125, building.currPos.y);
      break;                                 
      case "engineer":
        unitType = 3;
        unitToCreate = new Clan1_Collector(building.currPos.x+70, building.currPos.y);
      break;

      // Clan 2 units
      case "Mutantfighter1":
        unitType = 2;      
        unitToCreate = new Clan2_Fighter1(building.currPos.x+70, building.currPos.y);
        break;
      case "Mutantfighter2":
        unitType = 2;      
        unitToCreate = new Clan2_Fighter2(building.currPos.x+70, building.currPos.y);
        break;
      case "Mutantfighter3":
        unitType = 2;      
        unitToCreate = new Clan2_Fighter3(building.currPos.x+70, building.currPos.y);
        break;
      case "Supermutant":
        unitType = 2;      
        unitToCreate = new Clan2_Vehicle1(building.currPos.x+70, building.currPos.y);
        break;
      case "Mutantgiant":
        unitType = 2;      
        unitToCreate = new Clan2_Vehicle2(building.currPos.x+70, building.currPos.y);
        break;
      case "Monster":
        unitType = 2;      
        unitToCreate = new Clan2_Vehicle3(building.currPos.x+70, building.currPos.y);
        break;                                 
      case "MutantHuman":
        unitType = 4;      
        unitToCreate = new Clan2_Collector(building.currPos.x+70, building.currPos.y);
        break;                                
    }

    switch(unitType)
    {
      case 1:
        this.addPlayerCombatUnit(unitToCreate);          
        break;
      case 2:
        this.addAICombatUnit(unitToCreate);          
        break;
      case 3:
        this.addPlayerGathererUnit(unitToCreate);         
        break;
      case 4:
        this.addAIGathererUnit(unitToCreate);          
        break;
    }

    building.unitReady = false;         
  }
};

GameState.prototype.manageMenus = function(selectedBuilding, menuItems)
{
  if(selectedBuilding)
  {
    this.menuItems.splice(0, this.menuItems.length);
    if(selectedBuilding.type == "Clan1_Lab")
    {      
      // Engineers
      var engineer = new Clan1_Collector(0,0);
      menuItems.push(new MenuItem("Clan1_Collector.png",0,0,100,100, engineer.costToBuild));
    }
    else if (selectedBuilding.type == "Clan1_Factory1")
    {      
      // Armed Vehicle
      var armedvehicle = new Clan1_Vehicle1(0,0);
      menuItems.push(new MenuItem("Clan1_Vehicle1.png",0,0,100,100, armedvehicle.costToBuild));
    }
    else if (selectedBuilding.type == "Clan1_factory2")
    {      
      // Warbus
      var warbus = new Clan1_Vehicle2(0,0); 
      menuItems.push(new MenuItem("Clan1_Vehicle2.png",0,0,100,100, warbus.costToBuild));
    }
    else if (selectedBuilding.type == "Clan1_Factory3")
    {      
      // semitruck
      var semitruck = new Clan1_Vehicle3(0,0);  
      menuItems.push(new MenuItem("Clan1_Vehicle3.png",0,0,100,100, semitruck.costToBuild));
    }
    else if (selectedBuilding.type == "Clan1_Training1")
    {      
      // semitruck
      var fighter1 = new Clan1_Fighter1(0,0);              
      menuItems.push(new MenuItem("Clan1_Fighter1.png",0,0,100,100, fighter1.costToBuild));
    }
    else if (selectedBuilding.type == "Clan1_Training2")
    {      
      // semitruck
      var fighter2 = new Clan1_Fighter2(0,0);              
      menuItems.push(new MenuItem("Clan1_Fighter2.png",0,0,100,100, fighter2.costToBuild));
    }
    else if (selectedBuilding.type == "Clan1_Training3")
    {      
      // semitruck
      var fighter3 = new Clan1_Fighter3(0,0);              
      menuItems.push(new MenuItem("Clan1_Fighter3.png",0,0,100,100, fighter3.costToBuild));
    }    
  } 
  else
  {
    // Load buildings into the menu selection screen
    this.menuItems.splice(0, this.menuItems.length);
    var clan1lab = new Clan1_Lab(0,0);                  
    this.menuItems.push(new MenuItem("Clan1_Lab", 0, 0, 100, 100, clan1lab.costToBuild));
    var fact1 = new Clan1_Factory1(0,0);                  
    this.menuItems.push(new MenuItem("Clan1_Factory1", 100, 0, 100, 100, fact1.costToBuild));
    var fact2 = new Clan1_Factory2(0,0);                  
    this.menuItems.push(new MenuItem("Clan1_Factory2", 200, 0, 100, 100, fact2.costToBuild));
    var fact3 = new Clan1_Factory3(0,0);                  
    this.menuItems.push(new MenuItem("Clan1_Factory3", 0, 100, 100, 100, fact3.costToBuild));
    var missiletower = new Clan1_MissileTower(0,0);                  
    this.menuItems.push(new MenuItem("Clan1_MissileTower", 100, 100, 100, 100, missiletower.costToBuild));  
    var tower = new Clan1_Tower(0,0);                  
    this.menuItems.push(new MenuItem("Clan1_Tower", 200, 100, 100, 100, tower.costToBuild));     
    var training1 = new Clan1_Training1(0,0);                  
    this.menuItems.push(new MenuItem("Clan1_Training1", 0, 200, 100, 100, training1.costToBuild));
    var training2 = new Clan1_Training2(0,0);                  
    this.menuItems.push(new MenuItem("Clan1_Training2", 100, 200, 100, 100, training2.costToBuild));
    var training3 = new Clan1_Training3(0,0);                  
    this.menuItems.push(new MenuItem("Clan1_Training3", 200, 200, 100, 100, training3.costToBuild));      
  }
};

GameState.prototype.getSelectedBuilding = function() {
  return this.selectedBuilding;
};

GameState.prototype.addPlayerCombatUnit = function(unit) {
  this.units.pCombat.push(unit);
};

GameState.prototype.addAICombatUnit = function(unit) {
  this.units.aiCombat.push(unit);
};

GameState.prototype.addPlayerGathererUnit = function(unit) {
  this.units.pGatherer.push(unit);
};

GameState.prototype.addAIGathererUnit = function(unit) {
  this.units.aiGatherer.push(unit);
};

GameState.prototype.addResource = function(resource) {
  this.resources.push(resource);
};

GameState.prototype.addPlayerBuilding = function(building) {
  this.buildings.pBuildings.push(building);
};

GameState.prototype.addAIBuilding = function(building) {
  this.buildings.aiBuildings.push(building);
};

GameState.prototype.addPlayerTowers = function(building) {
  this.buildings.pTowers.push(building);
};

GameState.prototype.addAITowers = function(building) {
  this.buildings.aiTowers.push(building);
};

GameState.prototype.addPlayerWalls = function(building) {
  this.buildings.pWalls.push(building);
};

GameState.prototype.addAIWalls = function(building) {
  this.buildings.aiWalls.push(building);
};


GameState.prototype.addProjectile = function(projectile) {
  this.projectiles.push(projectile);
};

GameState.prototype.clear = function() {
  this.ctx.clearRect(0, 0, this.width, this.height);
};

GameState.prototype.updateResources = function()
{

  // Need to detect how many gatherers are colliding with a given resource
  /*
  *  Iterate through resources
  *  -- For each resource, iterate through gatherers: n^2
  *  ---- Check for collision between the resource and the gatherer
  *  ---- If a collision is detected, add that gatherer to an array
  *  -- Once done iterating through gatherers, if the array.length > 0, send an update
  *  -- to the resource in the outer loop
  *
  */
  
  var gathererArr = [];

  for (var i = 0; i < this.resources.length; i++)
  {
    for (var y = 0; y < this.units.pGatherer.length; y++)
    {      
      if(detectCollision(this.resources[i], this.units.pGatherer[y]))
      {
        gathererArr.push(this.units.pGatherer[y]);
      }
    }
    
    for (y = 0; y < this.units.aiGatherer.length; y++)
    {
      if(detectCollision(this.resources[i], this.units.aiGatherer[y]))
      {
        gathererArr.push(this.units.aiGatherer[y]);
      }      
    }    

    this.resources[i].update(gathererArr);  
  }  
};

GameState.prototype.processUserCommands = function()
{
  
};


GameState.prototype.processAICommands = function()
{
    if(this.gameLoading == false && this.difficultyChosen == true){
        if (this.dampner = 100) {
            this.aiPlayer.updateAI(this);
            this.dampner = 0;
        } else {
            this.dampner++;
        }
    }
};

GameState.prototype.drawObjects = function()
{
  if(!this.gameOverVar)
  {  
    this.ctx.save();
    this.ctx.translate(-this.camera.x, -this.camera.y);
    // Draw game map
    this.drawMap();

    // Draw Resources
    var res = this.resources.length;
    for (var resources = 0; resources < res; resources++)
    {
      this.drawObject(this.resources[resources]);
    }    

    // Draw player buildings 
    var pb = this.buildings.pBuildings.length;
    for (var building = 0; building < pb; building++)
    {    
      this.drawObject(this.buildings.pBuildings[building]);
    }    

    // Draw ai buildings
    var aib = this.buildings.aiBuildings.length;
    for (building = 0; building < aib; building++)
    {
      this.drawObject(this.buildings.aiBuildings[building]);
    }     
        
    // Draw player towers 
    var pt = this.buildings.pTowers.length;
    for (var tower = 0; tower < pt; tower++)
    {    
      this.drawObject(this.buildings.pTowers[tower]);
    }    

    // Draw ai towers 
    var ait = this.buildings.aiTowers.length;
    for (tower = 0; tower < ait; tower++)
    {    
      this.drawObject(this.buildings.aiTowers[tower]);
    }    

    // Draw player walls 
    var pw = this.buildings.pWalls.length;
    for (var wall = 0; wall < pw; wall++)
    {    
      this.drawObject(this.buildings.pWalls[wall]);
    }    

    // Draw ai walls 
    var aiw = this.buildings.aiTowers.length;
    for (wall = 0; wall < aiw; wall++)
    {    
      this.drawObject(this.buildings.aiTowers[wall]);
    }    


    // Draw player combat units
    var u = this.units.pCombat.length;
    for (var unit = 0; unit < u; unit++)
    {
      this.drawObject(this.units.pCombat[unit]);
    }    

    // Draw player gatherer units
    var ug = this.units.pGatherer.length;
    for (unit = 0; unit < ug; unit++)
    {    
      this.drawObject(this.units.pGatherer[unit]);
    }     

    // Draw ai combat units
    var ai = this.units.aiCombat.length;
    for (unit = 0; unit < ai; unit++)
    {
      this.drawObject(this.units.aiCombat[unit]);
    }    

    // Draw ai gatherer units
    var aig = this.units.aiGatherer.length;
    for (unit = 0; unit < aig; unit++)
    {
      this.drawObject(this.units.aiGatherer[unit]);
    }     

    // Draw Projectiles
    var p = this.projectiles.length;
    for (var projectile = 0; projectile < p; projectile++)
    {
      this.drawObject(this.projectiles[projectile]);
    }

    var rectSelect = this.selectRectangle.length;
    for (var rect = 0; rect < rectSelect; rect++)
    {
      this.drawSelectRectangle(this.selectRectangle[rect].retrieveSelectRectInfo());
    }  

    var buildSelect = this.buildingSelectionRectangle.length;
    for (var build = 0; build < buildSelect; build++)
    {
      this.drawSelectRectangle(this.buildingSelectionRectangle[build].retrieveSelectRectInfo());
    }  

    this.ctx.restore();    

    if(!this.gameLoading && this.difficultyChosen)
    {
      this.drawPlayerResourcesText(this.player);
      this.menuCtx.clearRect(0,0,300,300);
      var m = this.menuItems.length;
      for (var menuItem = 0; menuItem < m; menuItem++)
      {
        this.drawMenuItem(this.menuItems[menuItem].retrieveMenuItemInfo());
      }
    }

    if(this.savingGame)
    {
      var canvas = this.ctx;
      var opacity = 1;
      interval = setInterval(function() {
        canvas.font = "20px Arial";
        canvas.lineWidth = 2;
        canvas.fillStyle = "rgba(255, 255, 255)";
        canvas.fillText("GAME SAVED", 350, 200);  
        opacity -= 0.02;
        if(opacity < 0)  
        {
          clearInterval(interval);
        }
      }, 1, canvas, opacity);
      this.savingGame = false;
    }
  }
};

// Creates an object with x and y defined, set to the mouse position relative to the state's canvas
// If you wanna be super-correct this can be tricky, we have to worry about padding and borders
GameState.prototype.getMouse = function(e) {
  var element = this.canvas, offsetX = 0, offsetY = 0, mx, my;
  
  // Compute the total offset
  if (element.offsetParent !== undefined)
  {
    do {
      offsetX += element.offsetLeft;
      offsetY += element.offsetTop;
    } while ((element = element.offsetParent));
  }

  mx = e.pageX - offsetX + this.camera.x;
  my = e.pageY - offsetY + this.camera.y;

  document.getElementById('mouse_x').textContent = mx;
  document.getElementById('mouse_y').textContent = my;

  
  // We return a simple javascript object (a hash) with x and y defined
  return {x: mx, y: my};
};

GameState.prototype.getMouseMenu = function(e) {
  var element = this.menuCtx, offsetX = 14, offsetY = 0, mx, my;
  
  // Compute the total offset
  if (element.offsetParent !== undefined)
  {
    do {
      offsetX += element.offsetLeft;
      offsetY += element.offsetTop;      
    } while ((element = element.offsetParent));
  }

  mx = e.pageX - offsetX - this.canvas.width;
  my = e.pageY - offsetY - (this.canvas.height-this.menu.height);

  return {x: mx, y: my};
};

///////////////////////////////////////////
// CREATE GAMESTATE
///////////////////////////////////////////

var s = new GameState(document.getElementById('canvas'), document.getElementById('menu')); 

function mainGameLoop()
{
  if(!s.gameLoading && s.difficultyChosen)
  {
    s.processUserCommands(); // empty function
    s.processAICommands(); // empty function
    s.updatePlayerComUnits();
    s.updatePlayerGatherers();
    s.updateAIGatherers();
    s.updateAIComUnits();
    s.updateBuildings();
    s.updateProjectiles();
    s.updateResources();
    s.drawObjects();
  }
}

function init() {
  //while(!shipsJson['frames'] || !rbpJson['frames']) // waiting to ensure the json has loaded
    //console.log("waiting for json to load");
  mainGameLoop();
  s.timerId = setInterval(mainGameLoop,1);
}

GameState.prototype.breakMainGameLoop = function()
{
  clearInterval(this.timerId);
}

////////////////////////////////////////////////////////////////////
/////////////////// UPDATE Player combat Units FUNCTION /////////////////////////
//////////////////////////////////////////////////////////////////

GameState.prototype.updatePlayerComUnits = function()
{

  // GET LENGTHS OF ALL UNIT ARRAYS
  var pcombat = this.units.pCombat.length;
  var aicombat = this.units.aiCombat.length;
  var pgatherer = this.units.pGatherer.length;
  var aigatherer = this.units.aiGatherer.length;  
  var pbuilding = this.buildings.pBuildings.length;
  var aibuilding = this.buildings.aiBuildings.length;
  var ptower = this.buildings.pTowers.length;
  var aitower = this.buildings.aiTowers.length;  
  var pwall = this.buildings.pWalls.length;
  var aiwall = this.buildings.aiWalls.length;
  var resources = this.resources.length;


  // ITERATE THROUGH PLAYER'S COMBAT UNITS
  for (var i = 0; i < pcombat; i++)
  {
    // Retrieve all information from unit
    // Update unit coords
    if (this.units.pCombat[i].health <= 0)
    {
      this.units.pCombat[i].killed = true;
      this.units.pCombat.splice(i, 1);
      break;
    }

    // UNITUPDATE CONTAINS UNITS CURRENT POSITION
    var unitUpdate = {colPos:{x:this.units.pCombat[i].currPos.x, y:this.units.pCombat[i].currPos.y}};


    // DETECT ANY COLLISIONS IF UNIT IS MOVING
    if(this.units.pCombat[i].state == "enroute" || this.units.pCombat[i].state == "onAttack")
    {
			// Write a breadth first search function using the grid to make this more efficient later
      // Check for collision against player combat unit
        /*
      for (var secondUnit = 0; secondUnit < pcombat; secondUnit++)
      {
        if(this.units.pCombat[i] != this.units.pCombat[secondUnit])
        {
          if (detectCollision(this.units.pCombat[i], this.units.pCombat[secondUnit]))
          {
            unitUpdate = adjustCollisionCoords(unitUpdate, this.units.pCombat[i], this.units.pCombat[secondUnit]);
          }
        }
      }*/

        // Check for collision against ai combat unit
        for (secondUnit = 0; secondUnit < aicombat; secondUnit++)
        {
            if(this.units.pCombat[i] != this.units.aiCombat[secondUnit])
            {
                if (detectCollision(this.units.pCombat[i], this.units.aiCombat[secondUnit]))
                {
                    unitUpdate = adjustCollisionCoords(unitUpdate, this.units.pCombat[i], this.units.aiCombat[secondUnit]);
                }
            }
        }

        // Check for collision against player gatherer unit
        /*
        for (secondUnit = 0; secondUnit < pgatherer; secondUnit++)
        {
            if(this.units.pCombat[i] != this.units.pGatherer[secondUnit])
            {
                if (detectCollision(this.units.pCombat[i], this.units.pGatherer[secondUnit]))
                {
                    unitUpdate = adjustCollisionCoords(unitUpdate, this.units.pCombat[i], this.units.pGatherer[secondUnit]);
                }
            }
        }*/


        // Check for collision against ai gatherer unit
        for (secondUnit = 0; secondUnit < aigatherer; secondUnit++)
        {
            if(this.units.pCombat[i] != this.units.aiGatherer[secondUnit])
            {
                if (detectCollision(this.units.pCombat[i], this.units.aiGatherer[secondUnit]))
                {
                    unitUpdate = adjustCollisionCoords(unitUpdate, this.units.pCombat[i], this.units.aiGatherer[secondUnit]);
                }
            }
        }


        //This can also be made into a breadth first search to make it more efficient
      // Check for collision against a player building
        /*
      for (var pbuild = 0; pbuild < pbuilding; pbuild++)
      {
        if (detectCollision(this.units.pCombat[i], this.buildings.pBuildings[pbuild]))
        {
          unitUpdate = adjustCollisionCoords(unitUpdate, this.units.pCombat[i], this.buildings.pBuildings[pbuild]);
        }
      }

      // Check for collision against an ai building
      for (var aibuild = 0; aibuild < aibuilding; aibuild++)
      {
        if (detectCollision(this.units.pCombat[i], this.buildings.aiBuildings[aibuild]))
        {
          unitUpdate = adjustCollisionCoords(unitUpdate, this.units.pCombat[i], this.buildings.aiBuildings[aibuild]);
        }
      }
         */
      // Check for collision against an player tower
        /*
      for (var ptow = 0; ptow < ptower; ptow++)
      {
        if (detectCollision(this.units.pCombat[i], this.buildings.pTowers[ptow]))
        {
          unitUpdate = adjustCollisionCoords(unitUpdate, this.units.pCombat[i], this.buildings.pTowers[ptow]);
        }
      }

      // Check for collision against an ai tower
      for (var aitow = 0; aitow < aitower; aitow++)
      {
        if (detectCollision(this.units.pCombat[i], this.buildings.aiTowers[aitow]))
        {
          unitUpdate = adjustCollisionCoords(unitUpdate, this.units.pCombat[i], this.buildings.aiTowers[aitow]);
        }
      }*/

        // Check for collision against a resource
        /*
        for (var res = 0; res < resources; res++)
        {
            if (detectCollision(this.units.pCombat[i], this.resources[res]))
            {
                unitUpdate = adjustCollisionCoords(unitUpdate, this.units.pCombat[i], this.resources[res]);
            }
        }

      ///////////////
      // NO WALLS
      ///////////////


      // Check for collision against an player wall
      for (var pwal = 0; pwal < pwall; pwal++)
      {
        if (detectCollision(this.units.pCombat[i], this.buildings.pWalls[pwal]))
        {
          unitUpdate = adjustCollisionCoords(unitUpdate, this.units.pCombat[i], this.buildings.pWalls[pwal]);
        }
      }  

      // Check for collision against an ai wall
      for (var aiwal = 0; aiwal < aiwall; aiwal++)
      {
        if (detectCollision(this.units.pCombat[i], this.buildings.pWalls[aiwal]))
        {
          unitUpdate = adjustCollisionCoords(unitUpdate, this.units.pCombat[i], this.buildings.pWalls[aiwal]);
        }
      }
*/

    }


    // CREATE PROJECTILE FOR UNIT IF UNIT IS READY TO ATTACK
    if (this.units.pCombat[i].state == "onAttack" && this.units.pCombat[i].inRange == true && this.units.pCombat[i].projectileReady == true)
    {
        //console.log("onattack");
        //console.log("CREATING BULLETS");
        //console.log(this.units.pCombat[i].assignedEnemy);
        // create new projectile here
        if(this.units.pCombat[i].type = "Fighter1") {
          //console.log("creating projectile");

          s.addProjectile(new Clan1_Fighter1_Proj(this.units.pCombat[i].currPos, this.units.pCombat[i].assignedEnemy.currPos));


        }
        else if(this.units.pCombat[i].type = "Fighter2")
            s.addProjectile(new Clan1_Fighter2_Proj(this.units.pCombat[i].currPos, this.units.pCombat[i].assignedEnemy.currPos));
        else if(this.units.pCombat[i].type = "Fighter3")
            s.addProjectile(new Clan1_Fighter3_Proj(this.units.pCombat[i].currPos, this.units.pCombat[i].assignedEnemy.currPos));
        else if(this.units.pCombat[i].type = "Armedvehicle")
            s.addProjectile(new Clan1_Vehicle1_Proj(this.units.pCombat[i].currPos, this.units.pCombat[i].assignedEnemy.currPos));
        else if(this.units.pCombat[i].type = "Warbus")
            s.addProjectile(new Clan1_Vehicle2_Proj(this.units.pCombat[i].currPos, this.units.pCombat[i].assignedEnemy.currPos));
        else if(this.units.pCombat[i].type = "Semitruck")
            s.addProjectile(new Clan1_Vehicle3_Proj(this.units.pCombat[i].currPos, this.units.pCombat[i].assignedEnemy.currPos));
        else if(this.units.pCombat[i].type = "Clan1_MissileTower")
            s.addProjectile(new Clan1_MissileTower_Proj(this.units.pCombat[i].currPos, this.units.pCombat[i].assignedEnemy.currPos));
        else if(this.units.pCombat[i].type = "Clan1_Tower")
            s.addProjectile(new Clan1_Tower_Proj(this.units.pCombat[i].currPos, this.units.pCombat[i].assignedEnemy.currPos));
        

        // update units projectileReady flags

        this.units.pCombat[i].projectileReady = false;
        this.units.pCombat[i].inRange = false;

        //unitUpdate.state = "Idle";
    }


    unitUpdate.enemyArray = this.units.aiCombat;

    // UNIT UPDATE HERE
    this.units.pCombat[i].update(unitUpdate);
  }
};


GameState.prototype.updateAIGatherers = function() {
    //console.log("current ai Resources are inside updateAIGatherers: ",this.aiPlayer.resources );
    // GET LENGTHS OF ALL UNIT ARRAYS
    var pcombat = this.units.pCombat.length;
    var aicombat = this.units.aiCombat.length;
    var pgatherer = this.units.pGatherer.length;
    var aigatherer = this.units.aiGatherer.length;
    var pbuilding = this.buildings.pBuildings.length;
    var aibuilding = this.buildings.aiBuildings.length;
    var ptower = this.buildings.pTowers.length;
    var aitower = this.buildings.aiTowers.length;
    var pwall = this.buildings.pWalls.length;
    var aiwall = this.buildings.aiWalls.length;
    var resources = this.resources.length;


    // ITERATE THROUGH AI gatherers
    for (var i = 0; i < aigatherer; i++) {
        // Retrieve all information from unit
        // Update unit coords
        if (this.units.aiGatherer[i].health <= 0) {
          this.units.aiGatherer[i].killed = true;
        this.units.aiGatherer.splice(i, 1);
        continue;
        }


        // Updates ai's resources from returning gatherer
        if (detectCollectorHomeBaseCollision(this.units.aiGatherer[i])) {
            //console.log("adding resources to player");
            //console.log("the units payload is: " + this.units.aiGatherer[i].payload)
            this.aiPlayer.resources += (this.units.aiGatherer[i].payload);
            this.units.aiGatherer[i].payload = 0;
            //console.log("current ai Resources are: ",this.aiPlayer.resources );
        }

      // UNITUPDATE CONTAINS UNITS CURRENT POSITION
      var unitUpdate = {colPos: {x: this.units.aiGatherer[i].currPos.x, y: this.units.aiGatherer[i].currPos.y}};


       // DETECT ANY COLLISIONS IF UNIT IS MOVING
       if(this.units.aiGatherer[i].state == "enroute")
       {
         // Write a breadth first search function using the grid to make this more efficient later
         // Check for collision against player combat unit
         for (var secondUnit = 0; secondUnit < pcombat; secondUnit++)
         {
           if(this.units.aiGatherer[i] != this.units.pCombat[secondUnit])
           {
           if (detectCollision(this.units.aiGatherer[i], this.units.pCombat[secondUnit]))
           {
               unitUpdate = adjustCollisionCoords(unitUpdate, this.units.aiGatherer[i], this.units.pCombat[secondUnit]);
           }
         }
       }
       /*

       // Check for collision against ai combat unit
       for (secondUnit = 0; secondUnit < aicombat; secondUnit++)
       {
       if(this.units.aiGatherer[i] != this.units.aiCombat[secondUnit])
       {
       if (detectCollision(this.units.aiGatherer[i], this.units.aiCombat[secondUnit]))
       {
       unitUpdate = adjustCollisionCoords(unitUpdate, this.units.aiGatherer[i], this.units.aiCombat[secondUnit]);
       }
       }
       }*/


       // Check for collision against player gatherer unit
       for (secondUnit = 0; secondUnit < pgatherer; secondUnit++)
       {
           if(this.units.aiGatherer[i] != this.units.pGatherer[secondUnit])
           {
               if (detectCollision(this.units.aiGatherer[i], this.units.pGatherer[secondUnit]))
               {
                   unitUpdate = adjustCollisionCoords(unitUpdate, this.units.aiGatherer[i], this.units.pGatherer[secondUnit]);
               }
           }
       }
       /*


       // Check for collision against ai gatherer unit
       for (secondUnit = 0; secondUnit < aigatherer; secondUnit++)
       {
       if(this.units.aiGatherer[i] != this.units.aiGatherer[secondUnit])
       {
       if (detectCollision(this.units.aiGatherer[i], this.units.aiGatherer[secondUnit]))
       {
       unitUpdate = adjustCollisionCoords(unitUpdate, this.units.aiGatherer[i], this.units.aiGatherer[secondUnit]);
       }
       }
       }

      //This can also be made into a breadth first search to make it more efficient
      // Check for collision against a player building
      for (var pbuild = 0; pbuild < pbuilding; pbuild++) {
        if (detectCollision(this.units.aiGatherer[i], this.buildings.pBuildings[pbuild])) {
          unitUpdate = adjustCollisionCoords(unitUpdate, this.units.aiGatherer[i], this.buildings.pBuildings[pbuild]);
        }
      }

      // Check for collision against an ai building
      for (var aibuild = 0; aibuild < aibuilding; aibuild++) {
        if (detectCollision(this.units.aiGatherer[i], this.buildings.pBuildings[aibuild])) {
          unitUpdate = adjustCollisionCoords(unitUpdate, this.units.aiGatherer[i], this.buildings.pBuildings[aibuild]);
        }
      }

      // Check for collision against an player tower
      for (var ptow = 0; ptow < ptower; ptow++) {
        if (detectCollision(this.units.aiGatherer[i], this.buildings.pTowers[ptow])) {
          unitUpdate = adjustCollisionCoords(unitUpdate, this.units.aiGatherer[i], this.buildings.pTowers[ptow]);
        }
      }

      // Check for collision against an ai tower
      for (var aitow = 0; aitow < aitower; aitow++) {
        if (detectCollision(this.units.aiGatherer[i], this.buildings.aiTowers[aitow])) {
          unitUpdate = adjustCollisionCoords(unitUpdate, this.units.aiGatherer[i], this.buildings.aiTowers[aitow]);
        }
      }
      // Check for collision against a resource
      for (aitow = 0; aitow < resources; aitow++) {
        if (detectCollision(this.units.aiGatherer[i], this.resources[aitow])) {
          unitUpdate = adjustCollisionCoords(unitUpdate, this.units.aiGatherer[i], this.resources[aitow]);
        }*/
      }

      ///////////////
      // NO WALLS
      ///////////////

      /*
       // Check for collision against an player wall
       for (var pwal = 0; pwal < pwall; pwal++)
       {
       if (detectCollision(this.units.aiGatherer[i], this.buildings.pWalls[pwal]))
       {
       unitUpdate = adjustCollisionCoords(unitUpdate, this.units.aiGatherer[i], this.buildings.pWalls[pwal]);
       }
       }

       // Check for collision against an ai wall
       for (var aiwal = 0; aiwal < aiwall; aiwal++)
       {
       if (detectCollision(this.units.aiGatherer[i], this.buildings.pWalls[aiwal]))
       {
       unitUpdate = adjustCollisionCoords(unitUpdate, this.units.aiGatherer[i], this.buildings.pWalls[aiwal]);
       }
       }

       */


      // UNIT UPDATE HERE
      this.units.aiGatherer[i].update(unitUpdate);

    }
};



GameState.prototype.updatePlayerGatherers = function(){
    // GET LENGTHS OF ALL UNIT ARRAYS
    var pcombat = this.units.pCombat.length;
    var aicombat = this.units.aiCombat.length;
    var pgatherer = this.units.pGatherer.length;
    var aigatherer = this.units.aiGatherer.length;
    var pbuilding = this.buildings.pBuildings.length;
    var aibuilding = this.buildings.aiBuildings.length;
    var ptower = this.buildings.pTowers.length;
    var aitower = this.buildings.aiTowers.length;
    var pwall = this.buildings.pWalls.length;
    var aiwall = this.buildings.aiWalls.length;
    var resources = this.resources.length;


    // ITERATE THROUGH PLAYER'S COMBAT UNITS
    for (var i = 0; i < pgatherer; i++) {
      //this.player.addResources(detectCollectorHomeBaseCollision(this.units.pGatherer[i]));
      // Retrieve all information from unit
      // Update unit coords
      if (this.units.pGatherer[i].health <= 0) {
        this.units.pGatherer[i].killed = true;
        this.units.pGatherer.splice(i, 1);
        break;
      }

      // Updates player's resources from returning gatherer
      if (detectCollectorHomeBaseCollision(this.units.pGatherer[i])) {
        this.player.addResources(this.units.pGatherer[i].payload);
        this.units.pGatherer[i].payload = 0;
      }

      // UNITUPDATE CONTAINS UNITS CURRENT POSITION
      var unitUpdate = {colPos: {x: this.units.pGatherer[i].currPos.x, y: this.units.pGatherer[i].currPos.y}};


      /*
       // DETECT ANY COLLISIONS IF UNIT IS MOVING
       if(this.units.pGatherer[i].state == "enroute")
       {
       // Write a breadth first search function using the grid to make this more efficient later
       // Check for collision against player combat unit
       for (var secondUnit = 0; secondUnit < pcombat; secondUnit++)
       {
       if(this.units.pGatherer[i] != this.units.pCombat[secondUnit])
       {
       if (detectCollision(this.units.pGatherer[i], this.units.pCombat[secondUnit]))
       {
       unitUpdate = adjustCollisionCoords(unitUpdate, this.units.pGatherer[i], this.units.pCombat[secondUnit]);
       }
       }
       }*/


       // Check for collision against ai combat unit
       for (secondUnit = 0; secondUnit < aicombat; secondUnit++)
       {
       if(this.units.pGatherer[i] != this.units.aiCombat[secondUnit])
       {
       if (detectCollision(this.units.pGatherer[i], this.units.aiCombat[secondUnit]))
       {
       unitUpdate = adjustCollisionCoords(unitUpdate, this.units.pGatherer[i], this.units.aiCombat[secondUnit]);
       }
       }
       }

       /*
       // Check for collision against player gatherer unit
       for (secondUnit = 0; secondUnit < pgatherer; secondUnit++)
       {
       if(this.units.pGatherer[i] != this.units.pGatherer[secondUnit])
       {
       if (detectCollision(this.units.pGatherer[i], this.units.pGatherer[secondUnit]))
       {
       unitUpdate = adjustCollisionCoords(unitUpdate, this.units.pGatherer[i], this.units.pGatherer[secondUnit]);
       }
       }
       }*/


       // Check for collision against ai gatherer unit
       for (secondUnit = 0; secondUnit < aigatherer; secondUnit++)
       {
           if(this.units.pGatherer[i] != this.units.aiGatherer[secondUnit])
           {
               if (detectCollision(this.units.pGatherer[i], this.units.aiGatherer[secondUnit]))
               {
                   unitUpdate = adjustCollisionCoords(unitUpdate, this.units.pGatherer[i], this.units.aiGatherer[secondUnit]);
               }
           }
       }
       /*
      //This can also be made into a breadth first search to make it more efficient
      // Check for collision against a player building
      for (var pbuild = 0; pbuild < pbuilding; pbuild++) {
        if (detectCollision(this.units.pGatherer[i], this.buildings.pBuildings[pbuild])) {
          unitUpdate = adjustCollisionCoords(unitUpdate, this.units.pGatherer[i], this.buildings.pBuildings[pbuild]);
        }
      }

      // Check for collision against an ai building
      for (var aibuild = 0; aibuild < aibuilding; aibuild++) {
        if (detectCollision(this.units.pGatherer[i], this.buildings.pBuildings[aibuild])) {
          unitUpdate = adjustCollisionCoords(unitUpdate, this.units.pGatherer[i], this.buildings.pBuildings[aibuild]);
        }
      }

      // Check for collision against an player tower
      for (var ptow = 0; ptow < ptower; ptow++) {
        if (detectCollision(this.units.pGatherer[i], this.buildings.pTowers[ptow])) {
          unitUpdate = adjustCollisionCoords(unitUpdate, this.units.pGatherer[i], this.buildings.pTowers[ptow]);
        }
      }

      // Check for collision against an ai tower
      for (var aitow = 0; aitow < aitower; aitow++) {
        if (detectCollision(this.units.pGatherer[i], this.buildings.aiTowers[aitow])) {
          unitUpdate = adjustCollisionCoords(unitUpdate, this.units.pGatherer[i], this.buildings.aiTowers[aitow]);
        }
      }

      // Check for collision against a resource
      for (aitow = 0; aitow < resources; aitow++) {
        if (detectCollision(this.units.pGatherer[i], this.resources[aitow])) {
          //unitUpdate = adjustCollisionCoords(unitUpdate, this.units.pGatherer[i], this.resources[aitow]);
        }
      }
*/
      ///////////////
      // NO WALLS
      ///////////////

      /*
       // Check for collision against an player wall
       for (var pwal = 0; pwal < pwall; pwal++)
       {
       if (detectCollision(this.units.pGatherer[i], this.buildings.pWalls[pwal]))
       {
       unitUpdate = adjustCollisionCoords(unitUpdate, this.units.pGatherer[i], this.buildings.pWalls[pwal]);
       }
       }

       // Check for collision against an ai wall
       for (var aiwal = 0; aiwal < aiwall; aiwal++)
       {
       if (detectCollision(this.units.pGatherer[i], this.buildings.pWalls[aiwal]))
       {
       unitUpdate = adjustCollisionCoords(unitUpdate, this.units.pGatherer[i], this.buildings.pWalls[aiwal]);
       }
       }

       */


      // UNIT UPDATE HERE
      this.units.pGatherer[i].update(unitUpdate);

    }
    };



GameState.prototype.updateAIComUnits = function()
{

    // GET LENGTHS OF ALL UNIT ARRAYS
    var pcombat = this.units.pCombat.length;
    var aicombat = this.units.aiCombat.length;
    var pgatherer = this.units.pGatherer.length;
    var aigatherer = this.units.aiGatherer.length;
    var pbuilding = this.buildings.pBuildings.length;
    var aibuilding = this.buildings.aiBuildings.length;
    var ptower = this.buildings.pTowers.length;
    var aitower = this.buildings.aiTowers.length;
    var pwall = this.buildings.pWalls.length;
    var aiwall = this.buildings.aiWalls.length;
    var resources = this.resources.length;



    // ITERATE THROUGH AI COMBAT UNITS
    for (var i = 0; i < aicombat; i++) {
      // Retrieve all information from unit
      // Update unit coords
      if (this.units.aiCombat[i].health <= 0) {
        //console.log("SPLICING AN AICOMBAT UNIT", this.units.aiCombat[i]);
        this.units.aiCombat[i].killed = true;
        this.units.aiCombat.splice(i, 1);
        //console.log("this is the unit that was spliced: ", this.units.aiCombat[i]);
        break;
      }

      // UNITUPDATE CONTAINS UNITS CURRENT POSITION
      var unitUpdate = {colPos: {x: this.units.aiCombat[i].currPos.x, y: this.units.aiCombat[i].currPos.y}};


       // DETECT ANY COLLISIONS IF UNIT IS MOVING
       if(this.units.aiCombat[i].state == "enroute" || this.units.aiCombat[i].state == "onAttack")
       {
       // Write a breadth first search function using the grid to make this more efficient later
       // Check for collision against another ai unit
           /*
       for (var secondUnit = 0; secondUnit < aicombat; secondUnit++)
       {
       if(this.units.aiCombat[i] != this.units.aiCombat[secondUnit])
       {
       if (detectCollision(this.units.aiCombat[i], this.units.aiCombat[secondUnit]))
       {
       unitUpdate = adjustCollisionCoords(unitUpdate, this.units.aiCombat[i], this.units.aiCombat[secondUnit]);
       }
       }
       }*/

       // Check for collision against a player combat unit
       for (secondUnit = 0; secondUnit < pcombat; secondUnit++)
       {
           if(this.units.aiCombat[i] != this.units.pCombat[secondUnit])
           {
               if (detectCollision(this.units.aiCombat[i], this.units.pCombat[secondUnit]))
               {
                   unitUpdate = adjustCollisionCoords(unitUpdate, this.units.aiCombat[i], this.units.pCombat[secondUnit]);
               }
           }
       }

       // Check for collision against a player gatherer unit
       for (secondUnit = 0; secondUnit < pgatherer; secondUnit++)
       {
           if(this.units.aiCombat[i] != this.units.pGatherer[secondUnit])
           {
               if (detectCollision(this.units.aiCombat[i], this.units.pGatherer[secondUnit]))
               {
                   unitUpdate = adjustCollisionCoords(unitUpdate, this.units.aiCombat[i], this.units.pGatherer[secondUnit]);
               }
           }
       }

       // Check for collision against a ai gatherer unit

       for (secondUnit = 0; secondUnit < aigatherer; secondUnit++)
       {
       if(this.units.aiCombat[i] != this.units.aiGatherer[secondUnit])
       {
       if (detectCollision(this.units.aiCombat[i], this.units.aiGatherer[secondUnit]))
       {
       unitUpdate = adjustCollisionCoords(unitUpdate, this.units.aiCombat[i], this.units.aiGatherer[secondUnit]);
       }
       }
       }
           /*

       //This can also be made into a breadth first search to make it more efficient
       // Check for collision against a player building
       for (var pbuild = 0; pbuild < pbuilding; pbuild++)
       {
           if (detectCollision(this.units.aiCombat[i], this.buildings.pBuildings[pbuild]))
           {
               unitUpdate = adjustCollisionCoords(unitUpdate, this.units.aiCombat[i], this.buildings.pBuildings[pbuild]);
           }
       }


      // Check for collision against an ai building

      for (var aibuild = 0; aibuild < aibuilding; aibuild++) {
        if (detectCollision(this.units.aiCombat[i], this.buildings.aiBuildings[aibuild])) {
          unitUpdate = adjustCollisionCoords(unitUpdate, this.units.aiCombat[i], this.buildings.aiBuildings[aibuild]);
        }
      }

      // Check for collision against an player tower
      for (var ptow = 0; ptow < ptower; ptow++) {
        if (detectCollision(this.units.aiCombat[i], this.buildings.pTowers[ptow])) {
          unitUpdate = adjustCollisionCoords(unitUpdate, this.units.aiCombat[i], this.buildings.pTowers[ptow]);
        }
      }

      // Check for collision against an ai tower

      for (var aitow = 0; aitow < aitower; aitow++) {
        if (detectCollision(this.units.aiCombat[i], this.buildings.aiTowers[aitow])) {
          unitUpdate = adjustCollisionCoords(unitUpdate, this.units.aiCombat[i], this.buildings.aiTowers[aitow]);
        }
      }*/

       // Check for collision against a resource
           /*
       for (aitow = 0; aitow < resources; aitow++)
       {
           if (detectCollision(this.units.aiCombat[i], this.resources[aitow]))
           {
               unitUpdate = adjustCollisionCoords(unitUpdate, this.units.aiCombat[i], this.resources[aitow]);
           }
       }*/

      ///////////////
      // NO WALLS
      ///////////////

      /*
       // Check for collision against an player wall
       for (var pwal = 0; pwal < pwall; pwal++)
       {
       if (detectCollision(this.units.aiCombat[i], this.buildings.pWalls[pwal]))
       {
       unitUpdate = adjustCollisionCoords(unitUpdate, this.units.aiCombat[i], this.buildings.pWalls[pwal]);
       }
       }

       // Check for collision against an ai wall
       for (var aiwal = 0; aiwal < aiwall; aiwal++)
       {
       if (detectCollision(this.units.aiCombat[i], this.buildings.pWalls[aiwal]))
       {
       unitUpdate = adjustCollisionCoords(unitUpdate, this.units.aiCombat[i], this.buildings.pWalls[aiwal]);
       }
       }

       */


      // CREATE PROJECTILE FOR UNIT IF UNIT IS READY TO ATTACK
      if (this.units.aiCombat[i].state == "onAttack" && this.units.aiCombat[i].inRange && this.units.aiCombat[i].projectileReady) {
        //console.log("onattack");
        //console.log("CREATING BULLETS");
        //console.log(this.units.aiCombat[i].assignedEnemy);
        // create new projectile here

        if (this.units.aiCombat[i].type = "Mutantfighter1")
          s.addProjectile(new Clan2_Fighter1_Proj(this.units.aiCombat[i].currPos, this.units.aiCombat[i].assignedEnemy.currPos));
        else if (this.units.aiCombat[i].type = "Mutantfighter2")
          s.addProjectile(new Clan2_Fighter2_Proj(this.units.aiCombat[i].currPos, this.units.aiCombat[i].assignedEnemy.currPos));
        else if (this.units.aiCombat[i].type = "Mutantfighter3")
          s.addProjectile(new Clan2_Fighter3_Proj(this.units.aiCombat[i].currPos, this.units.aiCombat[i].assignedEnemy.currPos));
        else if (this.units.aiCombat[i].type = "Supermutant")
          s.addProjectile(new Clan2_Vehicle1_Proj(this.units.aiCombat[i].currPos, this.units.aiCombat[i].assignedEnemy.currPos));
        else if (this.units.aiCombat[i].type = "Mutantgiant")
          s.addProjectile(new Clan2_Vehicle2_Proj(this.units.aiCombat[i].currPos, this.units.aiCombat[i].assignedEnemy.currPos));
        else if (this.units.aiCombat[i].type = "Monster")
          s.addProjectile(new Clan2_Vehicle3_Proj(this.units.aiCombat[i].currPos, this.units.aiCombat[i].assignedEnemy.currPos));
        else if (this.units.aiCombat[i].type = "Clan2_MissileTower")
          s.addProjectile(new Clan2_MissileTower_Proj(this.units.aiCombat[i].currPos, this.units.aiCombat[i].assignedEnemy.currPos));
        else if (this.units.aiCombat[i].type = "Clan2_Tower")
          s.addProjectile(new Clan2_Tower_Proj(this.units.aiCombat[i].currPos, this.units.aiCombat[i].assignedEnemy.currPos));


        // update units projectileReady flags

        this.units.aiCombat[i].projectileReady = false;
          this.units.aiCombat[i].inRange = false;

        //unitUpdate.state = "Idle";
      }

      unitUpdate.enemyArray = this.units.pCombat;

      // UNIT UPDATE HERE
      this.units.aiCombat[i].update(unitUpdate);
    }

}};

function adjustCollisionCoords(unitUpdate, firstUnit, secondObject)
{
  if (firstUnit.currPos.x < secondObject.currPos.x)
  {    
    unitUpdate.colPos.x -= 2;
  }
  else if (firstUnit.currPos.x + firstUnit.size.x > secondObject.currPos.x)
  {
    unitUpdate.colPos.x += 2;
  }

  if (firstUnit.currPos.y < secondObject.currPos.y)
  {
    unitUpdate.colPos.y -= 2;
  }
  else if (firstUnit.currPos.y + firstUnit.size.y > secondObject.currPos.y)
  {
    unitUpdate.colPos.y += 2;
  }
  return unitUpdate;
}




GameState.prototype.updateProjectiles = function()
{
  var p = this.projectiles.length;
  if(p>0)
  {

  }
  for (var projectile = 0; projectile < p; projectile++)
  {
    // Retrieve all information from unit
    // Update unit coords
    var projectileUpdate = this.updateProjectileCoords(this.projectiles[projectile]);
    // Send updated coords to unit

    // AI projectile, check for damage against player units/buildings
    if(this.projectiles[projectile].isAI==true)
    {
        //console.log("AI Projectile Exists!!!");
        //console.log(this.projectiles[projectile]);
      // Player combat units
      for (var i = 0; i < this.units.pCombat.length; i++)
      {
        if (detectCollision(this.projectiles[projectile], this.units.pCombat[i]))
        {
            //console.log("TARGET HIT in ai -> pCom");
            this.units.pCombat[i].update({damage: this.projectiles[projectile].damage_infliction});
            this.projectiles.splice(projectile, 1);     
            return;                
        }
      }

      // Player combat units
      for (i = 0; i < this.units.pGatherer.length; i++)
      {
        if (detectCollision(this.projectiles[projectile], this.units.pGatherer[i]))
        {
            //console.log("TARGET HIT in ai -> pGath");
            this.units.pGatherer[i].update({damage: this.projectiles[projectile].damage_infliction});
            this.projectiles.splice(projectile, 1);    
            return;                 
        }
      }      

      // Player buildings
      for (i = 0; i < this.buildings.pBuildings.length; i++)
      {
        if (detectCollision(this.projectiles[projectile], this.buildings.pBuildings[i]))
        {
          //console.log("TARGET HIT in ai -> pBuild");
          this.buildings.pBuildings[i].update({damage: this.projectiles[projectile].damage_infliction});
          this.projectiles.splice(projectile, 1);
          return;
        }      
      }   

      // Player towers
      for (i = 0; i < this.buildings.pTowers.length; i++)
      {
        if (detectCollision(this.projectiles[projectile], this.buildings.pTowers[i]))
        {
          //console.log("TARGET HIT in ai -> pWall");
          this.buildings.pTowers[i].update({damage: this.projectiles[projectile].damage_infliction});
          this.projectiles.splice(projectile, 1);
          return;
        }      
      }   

/*
      // Player walls
      for (i = 0; i < this.buildings.pWalls.length; i++)
      {
        if (detectCollision(this.projectiles[projectile], this.buildings.pWalls[i]))
        {
          console.log("TARGET HIT");
          this.buildings.pWalls[i].update({damage: this.projectiles[projectile].damage_infliction});
          this.projectiles.splice(projectile, 1);
        }      
      }

              */
    }
    // Player projectile, check for damage against ai units/buildings    
    else
    {
      // AI combat units
      for (i = 0; i < this.units.aiCombat.length; i++)
      {
        if (detectCollision(this.projectiles[projectile], this.units.aiCombat[i]))
        {
            //console.log("TARGET HIT p -> aiCom");
            this.units.aiCombat[i].update({damage: this.projectiles[projectile].damage_infliction});
            this.projectiles.splice(projectile, 1);  
            return;                   
        }
      }

      // AI combat units
      for (i = 0; i < this.units.aiGatherer.length; i++)
      {
        if (detectCollision(this.projectiles[projectile], this.units.aiGatherer[i]))
        {
            //console.log("TARGET HIT in p -> aiGath");
            this.units.aiGatherer[i].update({damage: this.projectiles[projectile].damage_infliction});
            this.projectiles.splice(projectile, 1);     
            return;                
        }
      }      

      // AI buildings
      for (i = 0; i < this.buildings.aiBuildings.length; i++)
      {
        if (detectCollision(this.projectiles[projectile], this.buildings.aiBuildings[i]))
        {
          //console.log("TARGET HIT p -> aiBuild");
          this.buildings.aiBuildings[i].update({damage: this.projectiles[projectile].damage_infliction});
          this.projectiles.splice(projectile, 1);
          return;
        }      
      }   

      // AI towers
      for (i = 0; i < this.buildings.aiTowers.length; i++)
      {
        if (detectCollision(this.projectiles[projectile], this.buildings.aiTowers[i]))
        {
          //console.log("TARGET HIT p -> aiTower");
          this.buildings.aiTowers[i].update({damage: this.projectiles[projectile].damage_infliction});
          this.projectiles.splice(projectile, 1);
          return;
        }      
      }   
/*
      // AI walls
      for (i = 0; i < this.buildings.aiWalls.length; i++)
      {
        if (detectCollision(this.projectiles[projectile], this.buildings.aiWalls[i]))
        {
          console.log("TARGET HIT");
          this.buildings.aiWalls[i].update({damage: this.projectiles[projectile].damage_infliction});
          this.projectiles.splice(projectile, 1);
        }      
      }

         */
    }


    //if projectile is at its destination but didn't hit anything
      if(this.projectiles[projectile].currPos.x == this.projectiles[projectile].destPos.x && this.projectiles[projectile].currPos.y == this.projectiles[projectile].destPos.y) {
          this.projectiles.splice(projectile, 1);
            return;
      }

      // PROJECTILE UPDATE HERE
          this.projectiles[projectile].update(projectileUpdate);
  }

};

GameState.prototype.updateBuildings = function()
{
  var pbuilding = this.buildings.pBuildings.length;
  var aibuilding = this.buildings.aiBuildings.length;
  var ptower = this.buildings.pTowers.length;
  var aitower = this.buildings.aiTowers.length;  
  var pwall = this.buildings.pWalls.length;
  var aiwall = this.buildings.aiWalls.length;   

  for (var pbuild = 0; pbuild < pbuilding; pbuild++)
  {
    if (this.buildings.pBuildings[pbuild].health <= 0)
    {
      if (this.buildings.pBuildings[pbuild] == this.selectedBuilding[0])
      {
          this.selectedBuilding.splice(0,1);
      }
      this.buildings.pBuildings[pbuild].killed = true;
      this.buildings.pBuildings.splice(pbuild, 1);
      continue;
    }

    if(this.buildings.pBuildings[pbuild].unitReady)
    {
      var unitToCreate = this.buildings.pBuildings[pbuild].UnitsICreate;
      this.addNewUnit(this.buildings.pBuildings[pbuild], {type: unitToCreate});
      this.buildings.pBuildings[pbuild].unitReady = false;
    }

    this.buildings.pBuildings[pbuild].update({});
  }


  for (var aibuild = 0; aibuild < aibuilding; aibuild++)
  {
    if(this.buildings.aiBuildings[aibuild].unitReady)
    {
      //console.log("fighters avail before new unit ready", this.units.aiGatherer.length);
      unitToCreate = this.buildings.aiBuildings[aibuild].UnitsICreate;
      //console.log(unitToCreate);
      this.addNewUnit(this.buildings.aiBuildings[aibuild], {type: unitToCreate});
      this.buildings.aiBuildings[aibuild].unitReady = false;
      //console.log("fighters avail after new unit ready", this.units.aiGatherer.length);
    }

    if (this.buildings.aiBuildings[aibuild].health <= 0)
    {
      this.buildings.aiBuildings[aibuild].killed = true;
      this.buildings.aiBuildings.splice(aibuild, 1);
    }

    this.buildings.aiBuildings[aibuild].update({});
  }


  //////////////////////////////////////////////////
  // This block iterates through all PLAYER towers
  // It checks the tower health and kills tower if
  // necessary. Then it creates any necessary
  // projectiles based on the tower's stats. Next,
  // it sends an array of enemies to the tower in
  // the update function. This array of enemies
  // is used by the tower to lock on to an enemy.
  // PRE: PLAYER TOWERS MUST EXIST
  // POST: NECESSARY PLAYER TOWERS ARE KILLED
  // POST: NECESSARY PROJECTILES ARE CREATED
  // POST: TOWER'S UPDATE FUNCTION IS CALLED
  //////////////////////////////////////////////////

  for (var ptow = 0; ptow < ptower; ptow++)
  {


    if (this.buildings.pTowers[ptow].health <= 0) {
      this.buildings.pTowers[ptow].killed = true;
      this.buildings.pTowers.splice(ptow, 1);
    }
    else {


      var enemies = {enemyArray: this.units.aiCombat};
      //console.log("in GameState: Enemies Array is: ", enemies);

      // CREATE PROJECTILE FOR UNIT IF UNIT IS READY TO ATTACK
      if (this.buildings.pTowers[ptow].state == "onAttack" && this.buildings.pTowers[ptow].inRange == true && this.buildings.pTowers[ptow].projectileReady == true)
      {
          //console.log("onattack");
          //console.log("CREATING BULLETS FOR PLAYER TOWER");
          //console.log(this.buildings.pTowers[ptow].assignedEnemy);
          // create new projectile here
          if (this.buildings.pTowers[ptow].type = "Clan1_Tower") {
            //console.log("creating projectile");
            //console.log("projectile length before creation:", this.projectiles.length);
            s.addProjectile(new Clan1_Tower_Proj(this.buildings.pTowers[ptow].currPos, this.buildings.pTowers[ptow].assignedEnemy.currPos));
            //console.log("projectile length after creation:", this.projectiles.length);

          }

          if (this.buildings.pTowers[ptow].type = "Clan1_MissileTower")
          {
            //console.log("creating projectile");
            s.addProjectile(new Clan1_MissileTower_Proj(this.buildings.pTowers[ptow].currPos, this.buildings.pTowers[ptow].assignedEnemy.currPos));
          }

        this.buildings.pTowers[ptow].projectileReady = false;

      }

      this.buildings.pTowers[ptow].update(enemies);
    }
  }


  //////////////////////////////////////////////////
  // This block iterates through all AI towers
  // It checks the tower health and kills tower if
  // necessary. Then it creates any necessary
  // projectiles based on the tower's stats. Next,
  // it sends an array of enemies to the tower in
  // the update function. This array of enemies
  // is used by the tower to lock on to an enemy.
  // PRE: AI TOWERS MUST EXIST
  // POST: NECESSARY AI TOWERS ARE KILLED
  // POST: NECESSARY PROJECTILES ARE CREATED
  // POST: TOWER'S UPDATE FUNCTION IS CALLED
  //////////////////////////////////////////////////

  for (var aitow = 0; aitow < aitower; aitow++)
  {


    if (this.buildings.aiTowers[aitow].health <= 0) {
      this.buildings.aiTowers[aitow].killed = true;
      this.buildings.aiTowers.splice(aitow, 1);
    }
    else {


      var enemies = {enemyArray: this.units.pCombat};
      //console.log("in GameState: Enemies Array is: ", enemies);

      // CREATE PROJECTILE FOR UNIT IF UNIT IS READY TO ATTACK
      if (this.buildings.aiTowers[aitow].state == "onAttack" && this.buildings.aiTowers[aitow].inRange == true && this.buildings.aiTowers[aitow].projectileReady == true)
      {
        //console.log("onattack");
        //console.log("CREATING BULLETS FOR AI TOWER");
        //console.log(this.buildings.aiTowers[aitow].assignedEnemy);
        // create new projectile here
        if (this.buildings.aiTowers[aitow].type = "Clan2_Tower") {
          //console.log("creating projectile");
          //console.log("projectile length before creation:", this.projectiles.length);
          s.addProjectile(new Clan2_Tower_Proj(this.buildings.aiTowers[aitow].currPos, this.buildings.aiTowers[ptow].assignedEnemy.currPos));
          //console.log("projectile length after creation:", this.projectiles.length);

        }

        if (this.buildings.aiTowers[aitow].type = "Clan2_MissileTower")
        {
          //console.log("creating projectile");
          s.addProjectile(new Clan2_MissileTower_Proj(this.buildings.aiTowers[aitow].currPos, this.buildings.aiTowers[aitow].assignedEnemy.currPos));
        }

        this.buildings.aiTowers[aitow].projectileReady = false;

      }

      this.buildings.aiTowers[aitow].update(enemies);
    }
  }

  /*
  for (var pwal = 0; pwal < pwall; pwal++)
  {
    if (this.buildings.pWalls[pwal].health <= 0)
    {
      this.buildings.pWalls.splice(pwal, 1);
    }

    this.buildings.pWalls[pwal].update({});
  }

  for (var aiwal = 0; aiwal < aiwall; aiwal++)
  {
    if (this.buildings.aiWalls[aiwal].health <= 0)
    {
      this.buildings.aiWalls.splice(aiwal, 1);
    }

    this.buildings.aiWalls[aiwal].update({});
  }  
*/



};

GameState.prototype.updateProjectileCoords = function(projInfo)
{
  var projUpdate = {};
  var currPos = {x:0,y:0};
  
  if (projInfo.currPos.x > projInfo.destPos.x)
  {         
    currPos.x = projInfo.currPos.x - projInfo.velocity;          
  }
  else if (projInfo.currPos.x < projInfo.destPos.x)
  {          
    currPos.x = projInfo.currPos.x + projInfo.velocity;    
  }  
  else
  {
    currPos.x = projInfo.currPos.x;
  }

  if (projInfo.currPos.y > projInfo.destPos.y)
  {          
    currPos.y = projInfo.currPos.y - projInfo.velocity;    
  }
  else if (projInfo.currPos.y < projInfo.destPos.y)
  {          
    currPos.y = projInfo.currPos.y + projInfo.velocity;    
  }
  else
  {
    currPos.y = projInfo.currPos.y;
  }

  projUpdate.currPos = currPos;

  return projUpdate;
};

GameState.prototype.drawMap = function()
{
  var avatarMap = new Image();
  avatarMap.src = "../img/avatar.jpg";
  this.ctx.drawImage(avatarMap, 0, 0);
};

GameState.prototype.drawObject = function(object)
{
  drawObjectSprite(this.ctx, this.camera, object, this);
  
  if (object.selected)
  {
    if (object.resource_amount)
    {
      drawObjectResourceBar(this.ctx, this.camera, object);
    }
    else
    {
      drawObjectHealthBar(this.ctx, this.camera, object);
    }

    if(object.startTime > 0)    
    {
      drawObjectBuildBar(this.ctx, this.camera, object);
    }
  }  
};


// this function takes the gamestate so it can access the images that are loaded when the gamestate was created
// using getShipsJson and getRbpJson files we load the json into variables "shipsJson" and "rbpJson". They are arrays we can access globally and the contain all the JSON information for use when drawing the sprites.

function drawObjectSprite(ctx, camera, object, gs)
{
    var index;
    //NEW VIJAY: example: drawImage(image, sx, sy, sw, sh, dx, dy, dw, dh);
  if (object.type == "engineer" || object.type == "Fighter1" || object.type == "Fighter2" || object.type == "Fighter3" || object.type == "Armedvehicle" || object.type == "Warbus" || object.type == "Semitruck" ||object.type == "MutantHuman" || object.type == "Mutantfighter1" || object.type == "Mutantfighter2" || object.type == "Mutantfighter3" || object.type == "Mutantgiant" || object.type == "Supermutant" || object.type == "Monster" )
  {
    
      
        for (var i = 0; i< shipsJson.frames.length; i++)
        {
          
            //console.log('inside for');
            if(shipsJson.frames[i].filename== object.spriteInfo.imgName)
            {
                //console.log('inside comparison');
                index = i;
                break;
            }
        }
      
        var drawThis = shipsJson.frames[index];
        //console.log('this is drawThis in Ships ', drawThis);
        //console.log('this is the object in ships: ', object);
/*
      if(object.currPos.x != object.destPos.x || object.currPos.y != object.destPos.y) {
        // rotate image appropriately
        ctx.save();
        // this creates a new origin draw point, so when we actually draw the image, we just use 0,0 as the dest x/y coords
        ctx.translate(object.currPos.x, object.currPos.y);
        // need the object's rotation property to reflect the correct property in the unit.
        // ctx.rotate(object.rotation);

        var yDiff = Math.abs(object.destPos.y - object.currPos.y);
        var yCoord;

        if (object.destPos.y >= object.currPos.y)
          yCoord = object.currPos.y - yDiff;
        else
          yCoord = object.currPos + yDiff;

        var radians = Math.atan2(yCoord - object.currPos.y, object.destPos.x - object.currPos.x);
        if (radians < 0)
          radians = radians + (2 * Math.PI);

        ctx.rotate(radians);
        //ctx.rotate(0);
        //ctx.drawImage(gs.shipsAtlas, drawThis.frame.x, drawThis.frame.y, drawThis.frame.h, drawThis.frame.w, object.currPos.x, object.currPos.y, -(object.size.x/2), -(object.size.y/2));
        ctx.drawImage(gs.shipsAtlas, drawThis.frame.x, drawThis.frame.y, drawThis.frame.w, drawThis.frame.h, 0, 0, object.size.x, object.size.y);

        ctx.restore();
      }
*/
  //    else
        ctx.drawImage(gs.shipsAtlas, drawThis.frame.x, drawThis.frame.y, drawThis.frame.w, drawThis.frame.h, object.currPos.x, object.currPos.y, object.size.x, object.size.y);

      }
/*
      else if(object.type == "MF1Bullet" || object.type == "MF2Bullet" || object.type == "MF3Bullet" )
      {


                for (i = 0; i< rbpJson.frames.length; i++)
                {

                  //console.log('inside for');
                  if(rbpJson.frames[i].filename== object.spriteInfo.imgName)
                  {
                    //console.log('inside comparison');
                    index = i;
                    break;
                  }
                }

              var drawThis = rbpJson.frames[index];
              //console.log('this is drawThis in Ships ', drawThis);
              //console.log('this is the object in ships: ', object);

              if(object.currPos.x != object.destPos.x || object.currPos.y != object.destPos.y) {
                // rotate image appropriately
                ctx.save();
                // this creates a new origin draw point, so when we actually draw the image, we just use 0,0 as the dest x/y coords
                ctx.translate(object.currPos.x, object.currPos.y);
                // need the object's rotation property to reflect the correct property in the unit.
                // ctx.rotate(object.rotation);

                var yDiff = Math.abs(object.destPos.y - object.currPos.y);
                var yCoord;

                if (object.destPos.y >= object.currPos.y)
                  yCoord = object.currPos.y - yDiff;
                else
                  yCoord = object.currPos + yDiff;

                var radians = Math.atan2(yCoord - object.currPos.y, object.destPos.x - object.currPos.x);
                if (radians < 0)
                  radians = radians + (2 * Math.PI);

                ctx.rotate(radians);
                //ctx.rotate(0);
                //ctx.drawImage(gs.shipsAtlas, drawThis.frame.x, drawThis.frame.y, drawThis.frame.h, drawThis.frame.w, object.currPos.x, object.currPos.y, -(object.size.x/2), -(object.size.y/2));
                ctx.drawImage(gs.buildingResourceProjAtlas, drawThis.frame.x, drawThis.frame.y, drawThis.frame.w, drawThis.frame.h, 0, 0, object.size.x, object.size.y);

                ctx.restore();
              }

              else
                ctx.drawImage(gs.buildingResourceProjAtlas, drawThis.frame.x, drawThis.frame.y, drawThis.frame.w, drawThis.frame.h, object.currPos.x, object.currPos.y, object.size.x, object.size.y);

  }
    */
    else{
        
            //console.log('this is the objects spriteInfo...',object.spriteInfo.imgName );
            //console.log('this is rbpJson.frames[1] filename inside drawObject: ', rbpJson.frames[1].filename);

            for (i = 0; i< rbpJson.frames.length; i++)
            {

              //console.log('inside for');
              if(rbpJson.frames[i].filename== object.spriteInfo.imgName)
              {
                    //console.log('inside comparison');
                    index = i;
                    break;
                }
            }

            drawThis = rbpJson.frames[index];
            //console.log('this is drawThis in rbp : ', drawThis);
            //console.log('this is the object in rbp: ', object);
            ctx.drawImage(gs.buildingResourceProjAtlas, drawThis.frame.x, drawThis.frame.y, drawThis.frame.w, drawThis.frame.h, object.currPos.x, object.currPos.y, object.size.x, object.size.y);
    }
}

function drawObjectHealthBar(ctx, camera, object)
{
  ctx.strokeRect(object.currPos.x, object.currPos.y-10, object.size.x, 5);
  ctx.fillStyle = "#FF0000";
  ctx.fillRect(object.currPos.x, object.currPos.y-9, (object.health/object.maxHealth)*object.size.x, 4);  
}

function drawObjectBuildBar(ctx, camera, object)
{
  ctx.strokeRect(object.currPos.x, object.currPos.y-16, object.size.x, 5);
  ctx.fillStyle = "#00FF00";
  ctx.fillRect(object.currPos.x, object.currPos.y-15, (object.currentBuildTime/object.buildTime)*object.size.x, 4);  
}

function drawObjectResourceBar(ctx, camera, object)
{
  ctx.strokeRect(object.currPos.x, object.currPos.y-6, object.size.x, 5);
  ctx.fillStyle = "#0000FF";
  ctx.fillRect(object.currPos.x, object.currPos.y-5, (object.resource_amount/object.maxResource)*object.size.x, 4);  
}

GameState.prototype.drawSelectRectangle = function(object)
{
  this.ctx.beginPath();
  this.ctx.globalAlpha=0.5;
  this.ctx.rect(object.currPos.x, object.currPos.y, object.size.x, object.size.y);      
  this.ctx.fillStyle = object.color;
  this.ctx.fill();
};

GameState.prototype.drawPlayerResourcesText = function(object)
{
  this.ctx.font = "20px Arial";
  this.ctx.lineWidth = 3;
  this.ctx.strokeStyle = 'black';
  this.ctx.strokeText("Resources: " + object.getResources(), 600, 50);
  this.ctx.fillStyle = 'white';
  this.ctx.fillText("Resources: " + object.getResources(), 600, 50);
};

GameState.prototype.drawGreyOutBoxForMenuItem = function(xCoord, yCoord)
{
  this.menuCtx.beginPath();
  this.menuCtx.rect(xCoord, yCoord, 100, 100);      
  this.menuCtx.fillStyle = "rgba(255, 255, 255, 0.5)";
  this.menuCtx.fill(); 
};

GameState.prototype.drawMenuItemCost = function(cost, xCoord, yCoord)
{
  this.menuCtx.font = "15px Arial";
  this.menuCtx.lineWidth = 3;
  this.menuCtx.strokeStyle = 'black';
  this.menuCtx.strokeText(cost, xCoord, yCoord);
  this.menuCtx.fillStyle = 'white';
  this.menuCtx.fillText(cost, xCoord, yCoord);
};

GameState.prototype.drawMenuItem = function(object)
{
  var drawable;
  var ship = true;
  if (object.type)
  {
    switch (object.type)
    {
      case "Clan1_Collector.png":
        drawable = shipsJson.frames[this.findJsonIndex("Clan1_Collector.png", shipsJson)];
        break;      
      case "Clan1_Fighter1.png":
        drawable = shipsJson.frames[this.findJsonIndex("Clan1_Fighter1.png", shipsJson)];
        break;
      case "Clan1_Fighter2.png":
        drawable = shipsJson.frames[this.findJsonIndex("Clan1_Fighter2.png", shipsJson)];
        break;
      case "Clan1_Fighter3.png":
        drawable = shipsJson.frames[this.findJsonIndex("Clan1_Fighter3.png", shipsJson)];
        break;
      case "Clan1_Vehicle1.png":
        drawable = shipsJson.frames[this.findJsonIndex("Clan1_Vehicle1.png", shipsJson)];
        break;        
      case "Clan1_Vehicle2.png":
        drawable = shipsJson.frames[this.findJsonIndex("Clan1_Vehicle2.png", shipsJson)];
        break;  
      case "Clan1_Vehicle3.png":
        drawable = shipsJson.frames[this.findJsonIndex("Clan1_Vehicle3.png", shipsJson)];       
        break;                        
      case "Clan1_Lab":  
        ship = false;
        drawable = rbpJson.frames[this.findJsonIndex("Clan1_Lab.png", rbpJson)];        
        break;
      case "Clan1_Factory1":   
        ship = false;     
        drawable = rbpJson.frames[this.findJsonIndex("Clan1_Factory1.png", rbpJson)];      
        break;
      case "Clan1_Factory2": 
        ship = false;
        drawable = rbpJson.frames[this.findJsonIndex("Clan1_Factory2.png", rbpJson)];       
        break;
      case "Clan1_Factory3": 
        ship = false;
        drawable = rbpJson.frames[this.findJsonIndex("Clan1_Factory3.png", rbpJson)]; 
        break;
      case "Clan1_MissileTower":    
        ship = false;
        drawable = rbpJson.frames[this.findJsonIndex("Clan1_MissileTower.png", rbpJson)]; 
        break;
      case "Clan1_Tower": 
        ship = false;             
        drawable = rbpJson.frames[this.findJsonIndex("Clan1_Tower.png", rbpJson)]; 
        break;
      case "Clan1_Training1":
        ship = false;              
        drawable = rbpJson.frames[this.findJsonIndex("Clan1_Training.png", rbpJson)]; 
        break;        
      case "Clan1_Training2":    
        ship = false;          
        drawable = rbpJson.frames[this.findJsonIndex("Clan1_Training.png", rbpJson)]; 
        break;  
      case "Clan1_Training3":   
        ship = false;           
        drawable = rbpJson.frames[this.findJsonIndex("Clan1_Training.png", rbpJson)]; 
        break;              
    }    

    if(ship)
    {
      this.menuCtx.drawImage(this.shipsAtlas, drawable.frame.x, drawable.frame.y, drawable.frame.w, drawable.frame.h, object.currPos.x, object.currPos.y, 100,100);                   
      if(object.cost > this.player.getResources())
      {
        // Can't afford unit
        this.drawGreyOutBoxForMenuItem(object.currPos.x, object.currPos.y)
      }
      this.drawMenuItemCost(object.cost, object.currPos.x, object.currPos.y+100);            
    }
    else
    {
      var hRatio = object.size.w / 100;
      var vRatio = object.size.h / 100;
      var ratio = Math.min(hRatio, vRatio);
      this.menuCtx.drawImage(this.buildingResourceProjAtlas, drawable.frame.x, drawable.frame.y, drawable.frame.w, drawable.frame.h, object.currPos.x, object.currPos.y, 100*ratio, 100*ratio);           
      if(object.cost > this.player.getResources())
      {
        // Can't afford unit
        this.drawGreyOutBoxForMenuItem(object.currPos.x, object.currPos.y)
      }
      this.drawMenuItemCost(object.cost, object.currPos.x, object.currPos.y+100);
    }    
  }
};

GameState.prototype.findJsonIndex = function(filename, jsonFile)
{
  for (var i = 0; i< jsonFile.frames.length; i++)
  {      
    if(jsonFile.frames[i].filename== filename)
    {
      return i;
    }
  }

  return -1;
};

GameState.prototype.selectOtherEnemyUnit = function(enemyUnit, mx, my)
{
  if (enemyUnit)
  {
    if (this.isObjectSelected(enemyUnit, mx, my))
    {          
      var primaryUpdateObject = {};
      var destPos = {x:mx,y:my};
      primaryUpdateObject.state = "onAttack";
      primaryUpdateObject.destPos = destPos;
      primaryUpdateObject.enemy = enemyUnit;    
      primaryUpdateObject.selected = false;
      return primaryUpdateObject;
    }
  }  
};

GameState.prototype.selectOtherFriendlyUnit = function(secondUnit, mx, my)
{
  if(secondUnit)
  {
    if (this.isObjectSelected(secondUnit, mx, my))
    {          
      var updateArr = [];
      var primaryUpdateObject = {};
      var secondaryUpdateObject = {};
      primaryUpdateObject.selected = false;
      secondaryUpdateObject.selected = true;
      updateArr.push(primaryUpdateObject, secondaryUpdateObject);
      return updateArr;
    }
  }
};

GameState.prototype.selectOtherFriendlyBuilding = function(building, mx, my)
{
  if(building)
  {
    if (this.isObjectSelected(building, mx, my))
    {          
      var updateArr = [];
      var primaryUpdateObject = {};
      var secondaryUpdateObject = {};
      primaryUpdateObject.selected = false;
      secondaryUpdateObject.selected = true;
      updateArr.push(primaryUpdateObject, secondaryUpdateObject);
      return updateArr;
    }
  }  
};


GameState.prototype.selectOtherEnemyBuilding = function(building, mx, my)
{
  if(building)
  {
    if (this.isObjectSelected(building, mx, my))
    {          
      var primaryUpdateObject = {};
      primaryUpdateObject.state = "onAttack";
      primaryUpdateObject.destPos = {x:mx,y:my};
      primaryUpdateObject.enemy = building;    
      primaryUpdateObject.selected = false;
      return primaryUpdateObject;
    }
  }  
};


//This method returns 0 if niether player has won and 1 or 2 otherwise,
//it checks if either player's lab has been destroyed
GameState.prototype.gameOver = function () {
  //console.log('inside the gameOVer method');
  var aiBuildings = this.buildings.aiBuildings;
  var pBuildings = this.buildings.pBuildings;
  var pCount = 0;
  var aiCount = 0;
  var i;

    //console.log('inside the aiBuildings in gameOVer in gameState');
  for (i = 0; i < aiBuildings.length; i++){
    if (aiBuildings[i].unitType == 'lab'){
        //console.log('this is supposed to be a lab');
        //console.log(aiBuildings[i]);
      aiCount++;
    }
  }

  for (i = 0; i < pBuildings.length; i++){
    if (pBuildings[i].unitType == 'lab'){
      pCount++;
    }
  }
  //console.log('this is the pcount: '+ pCount);
    //console.log('this is the aiCount ' + aiCount);

  if (pCount == 0){
    return 2;
  } else if (aiCount == 0){
    return 1;
  } else {
    return 0;
  }
};

GameState.prototype.drawGameOverText = function(victory)
{
  this.clear();
  this.ctx.font = "80px Arial";
  this.ctx.lineWidth = 3;
  this.ctx.strokeStyle = 'black';
  this.ctx.strokeText("GAME OVER", 200, 250);
  this.ctx.fillStyle = 'white';
  this.ctx.fillText("GAME OVER", 200, 250);

  this.ctx.font = "50px Arial";

  if(victory == 1)
  {
    this.ctx.strokeStyle = 'black';
    this.ctx.strokeText("You won!", 340, 350);
    this.ctx.fillStyle = 'white';
    this.ctx.fillText("You won!", 340, 350);
  }
  else
  {
    this.ctx.strokeStyle = 'black';
    this.ctx.strokeText("You lost!", 340, 350);
    this.ctx.fillStyle = 'white';
    this.ctx.fillText("You lost!", 340, 350);    
  }
  this.gameOverVar = true;  
};

GameState.prototype.getUnits = function () {
  return this.units;
};

GameState.prototype.selectResource = function(resource, mx, my, gatherer)
{
  if (this.isObjectSelected(resource, mx, my))
  {         

    var resourceUpdate = {};
    //resourceUpdate.selected = true;
    if (gatherer)
    {
      var gathererUpdate = {};
      gathererUpdate.resource = resource;
      //console.log("in GameState selectResource(), resource is: " + resource);
      gathererUpdate.state = "enroute";
      gathererUpdate.selected = false;
      var updateArr = [];
      updateArr.push(resourceUpdate);
      updateArr.push(gathererUpdate);
      return updateArr;
    }
    return resourceUpdate;
  }
};

GameState.prototype.isObjectSelected = function(object, mx, my)
{
  return  (object.currPos.x <= mx) && (object.currPos.x + object.size.x >= mx) &&
          (object.currPos.y <= my) && (object.currPos.y + object.size.y >= my);          
};

GameState.prototype.isMenuObjectSelected = function(object, mx, my)
{
  return  (object.currPos.x <= mx) && (object.currPos.x + object.size.w >= mx) &&
          (object.currPos.y <= my) && (object.currPos.y + object.size.h >= my);          
};

GameState.prototype.animate = function(unitInfo)
{
  var updateObject;
  var shift = 0;
  var frameWidth = unitInfo.frameWidth;
  var frameHeight = unitInfo.frameHeight;
  var totalFrames = unitInfo.totalFrames;
  var currentFrame = unitInfo.currentFrame;

  //context.clearRect(120, 25, frameWidth, frameHeight);
 
  //draw each frame + place them in the middle
  this.ctx.drawImage(myImage, shift, 0, frameWidth, frameHeight,
                    120, 25, frameWidth, frameHeight);
 
  shift += frameWidth + 1;
 
  if (currentFrame == totalFrames) {
    shift = 0;
    currentFrame = 0;
  }
 
  currentFrame++;

  //updateObject.shift = shift;
  //updateObject.currentFrame = 0;
  //send updateObject to unit
 
  requestAnimationFrame(animate);
  
};

function getMenuItemInfo(menuItem)
{
  return menuItem.retrieveMenuItemInfo();
}

function detectCollision(thisObject, secondObject)
{
  if(thisObject !=null && secondObject !=null) {
    return (thisObject.currPos.x < secondObject.currPos.x + secondObject.size.x &&
    thisObject.currPos.x + thisObject.size.x > secondObject.currPos.x &&
    thisObject.currPos.y < secondObject.currPos.y + secondObject.size.y &&
    thisObject.size.y + thisObject.currPos.y > secondObject.currPos.y)
  }
}

GameState.prototype.selectRectCollision = function(selectrect)
{
  if(this.detectCollisionWithObjectArray(selectrect, this.units.pCombat))
  {
    return true;
  }

  if(this.detectCollisionWithObjectArray(selectrect, this.units.pGatherer))
  {
    return true;
  }

  if(this.detectCollisionWithObjectArray(selectrect, this.units.aiCombat))
  {
    return true;
  }

  if(this.detectCollisionWithObjectArray(selectrect, this.units.aiGatherer))
  {
    return true;
  }

  if(this.detectCollisionWithObjectArray(selectrect, this.buildings.pBuildings))
  {
    return true;
  }

  if(this.detectCollisionWithObjectArray(selectrect, this.buildings.aiBuildings))
  {
    return true;
  }

  if(this.detectCollisionWithObjectArray(selectrect, this.buildings.pTowers))
  {
    return true;
  }    

  if(this.detectCollisionWithObjectArray(selectrect, this.buildings.aiTowers))
  {
    return true;
  }

  if(this.detectCollisionWithObjectArray(selectrect, this.buildings.pWalls))
  {
    return true;
  }

  if(this.detectCollisionWithObjectArray(selectrect, this.buildings.aiWalls))
  {
    return true;
  }

    return this.detectCollisionWithObjectArray(selectrect, this.resources);

};

GameState.prototype.detectCollisionWithObjectArray = function(selectrect, arrayOfObjects)
{
  for (var i = 0; i < arrayOfObjects.length; i++)
  {
    if (detectCollision(selectrect, arrayOfObjects[i]))
    {
      return true;
    }
  }
};

// This function could be a repeat of James' _atHomeBase() -- double check this
// Otherwise, this function sees if a unit is at its homebase. If so, unit's payload is returned and set to zero

function detectCollectorHomeBaseCollision(unit)
{
    if(unit.currPos.x == unit.homeBase.x + 10 || unit.currPos.x == unit.homeBase.x - 10
        && unit.currPos.y == unit.homeBase.y + 10 || unit.currPos.y == unit.homeBase.y - 10)
    {
      return true;
    }

    return false;
};

function drawGameMenuChoices(gamestate)
{
    drawGameStateSelection(gamestate.ctx, gamestate.newGame);
    drawGameStateSelection(gamestate.ctx, gamestate.loadGame);
};

function drawGameMenuDifficulties(gamestate)
{
    drawGameStateSelection(gamestate.ctx, gamestate.easy);
    drawGameStateSelection(gamestate.ctx, gamestate.hard);
};

function drawGameStateSelection(ctx, object)
{  
  ctx.font = "50px Arial";
  ctx.lineWidth = 3;
  ctx.strokeStyle = 'black';
  ctx.strokeText(object.type, object.currPos.x, object.currPos.y+30);
  ctx.fillStyle = 'white';
  ctx.fillText(object.type, object.currPos.x, object.currPos.y+30);
};

function initializeGameUnitsAndBuildings()
{
  s.aiPlayer.homeBase = {x:600, y:600};
  s.addPlayerBuilding(new Clan1_Lab(100,100));
  s.addAIBuilding(new Clan2_Lab(600,600));

  s.addPlayerGathererUnit(new Clan1_Collector(200, 120));  
  s.addPlayerGathererUnit(new Clan1_Collector(200, 140));  
  s.addPlayerGathererUnit(new Clan1_Collector(200, 160));  
  s.addPlayerGathererUnit(new Clan1_Collector(200, 180));  
  s.addPlayerGathererUnit(new Clan1_Collector(200, 200));  

  s.addAIGathererUnit(new Clan2_Collector(700, 620));
  s.addAIGathererUnit(new Clan2_Collector(700, 640));
  s.addAIGathererUnit(new Clan2_Collector(700, 660));
  s.addAIGathererUnit(new Clan2_Collector(700, 680));
  s.addAIGathererUnit(new Clan2_Collector(700, 700));

 // s.addPlayerCombatUnit(new Clan1_Fighter1(300, 50));
  //s.addAICombatUnit(new Clan2_Fighter1(700, 720));
  s.addResource(new Resource1(300,100));
  s.addResource(new Resource2(300,200));
  s.addResource(new Resource3(300,300));
  s.addResource(new Resource1(500,600));
  s.addResource(new Resource2(500,650));
  s.addResource(new Resource3(500,700));  
}

document.getElementById("saveButton").addEventListener("click", function(){
  localStorage.setItem("units", JSON.stringify(s.units));  
  localStorage.setItem("buildings", JSON.stringify(s.buildings));   
  localStorage.setItem("resources", JSON.stringify(s.resources)); 
  localStorage.setItem("player", JSON.stringify(s.player)); 
  localStorage.setItem("projectiles", JSON.stringify(s.projectiles));  
  localStorage.setItem("difficulty", JSON.stringify(s.difficulty));  
  localStorage.setItem("aiPlayer", JSON.stringify(s.aiPlayer));
  s.savingGame = true;
});

document.getElementById("quitButton").addEventListener("click", function(){
  s.clear();
  s = new GameState(document.getElementById('canvas'), document.getElementById('menu')); 
  init();
});

GameState.prototype.loadSavedInformation = function(units, buildings, resources, player, projectiles, difficulty, aiPlayer)
{
  // Load all resources
  for (var i = 0; i < resources.length; i++)
  {
    //console.log(resources[i]);
    this.parseResourcesToObjects(resources[i]);    
  }  

  // Load all buildings
  for (var i = 0; i < buildings.pBuildings.length; i++)
  {
    this.parseBuildingsToObjects(buildings.pBuildings[i]);
  }

  for (var i = 0; i < buildings.aiBuildings.length; i++)
  {
    this.parseBuildingsToObjects(buildings.aiBuildings[i]);
  }

  for (var i = 0; i < buildings.pTowers.length; i++)
  {
    this.parseBuildingsToObjects(buildings.pTowers[i]);
  }

  for (var i = 0; i < buildings.aiTowers.length; i++)
  {
    this.parseBuildingsToObjects(buildings.aiTowers[i]);
  }

  for (var i = 0; i < buildings.pWalls.length; i++)
  {
    this.parseBuildingsToObjects(buildings.pWalls[i]);
  }

  for (var i = 0; i < buildings.aiWalls.length; i++)
  {
    this.parseBuildingsToObjects(buildings.aiWalls[i]);
  }

  // Load all units
  for (var i = 0; i < units.pCombat.length; i++)
  {
    this.parseUnitsToObjects(units.pCombat[i]);
  }

  for (var i = 0; i < units.pGatherer.length; i++)
  {    
    this.parseUnitsToObjects(units.pGatherer[i]);
  }

  for (var i = 0; i < units.aiCombat.length; i++)
  {
    this.parseUnitsToObjects(units.aiCombat[i]);
  }

  for (var i = 0; i < units.aiGatherer.length; i++)
  {
    this.parseUnitsToObjects(units.aiGatherer[i]);
  }

  // Load player resources
  this.player.resources = player.resources;

  // Load AI resources 
  this.aiPlayer.resources = aiPlayer.resources;
  this.aiPlayer.homeBase = {x:aiPlayer.homeBase.x, y:aiPlayer.homeBase.y};

  // Load difficulty  
  this.difficulty = difficulty;  
}

GameState.prototype.parseUnitsToObjects = function(unit)
{
  var unitToCreate = null;
  var unitType = null;
  if (unit)
  {
    switch (unit.type)
    {    
      // Clan 1 units
      case "Fighter1":
        unitType = 1;
        unitToCreate = new Clan1_Fighter1(unit.currPos.x, unit.currPos.y);
        break;
      case "Fighter2":
        unitType = 1;
        unitToCreate = new Clan1_Fighter2(unit.currPos.x, unit.currPos.y);
        break;
      case "Fighter3":
        unitType = 1;      
        unitToCreate = new Clan1_Fighter3(unit.currPos.x, unit.currPos.y);
        break;
      case "Armedvehicle":
        unitType = 1;
        unitToCreate = new Clan1_Vehicle1(unit.currPos.x, unit.currPos.y);
        break;
      case "Warbus":
        unitType = 1;
        unitToCreate = new Clan1_Vehicle2(unit.currPos.x, unit.currPos.y);
        break;
      case "Semitruck":
        unitType = 1;
        unitToCreate = new Clan1_Vehicle3(unit.currPos.x, unit.currPos.y);
        break;                                 
      case "engineer":
        unitType = 3;
        unitToCreate = new Clan1_Collector(unit.currPos.x, unit.currPos.y);
        break;

      // Clan 2 units
      case "Mutantfighter1":
        unitType = 2;      
        unitToCreate = new Clan2_Fighter1(unit.currPos.x, unit.currPos.y);
        break;
      case "Mutantfighter2":
        unitType = 2;      
        unitToCreate = new Clan2_Fighter2(unit.currPos.x, unit.currPos.y);
        break;
      case "Mutantfighter3":
        unitType = 2;      
        unitToCreate = new Clan2_Fighter3(unit.currPos.x, unit.currPos.y);
        break;
      case "Supermutant":
        unitType = 2;      
        unitToCreate = new Clan2_Vehicle1(unit.currPos.x, unit.currPos.y);
        break;
      case "Mutantgiant":
        unitType = 2;      
        unitToCreate = new Clan2_Vehicle2(unit.currPos.x, unit.currPos.y);
        break;
      case "Monster":
        unitType = 2;      
        unitToCreate = new Clan2_Vehicle3(unit.currPos.x, unit.currPos.y);
        break;                                 
      case "MutantHuman":
        unitType = 4;      
        unitToCreate = new Clan2_Collector(unit.currPos.x, unit.currPos.y);
        break;                                
    }

    unitToCreate.health = unit.health;
    unitToCreate.killed = unit.killed;
    unitToCreate.isAI = unit.isAI;

    switch(unitType)
    {
      case 1:      
        //unitToCreate.assignedEnemy = unit.assignedEnemy;
        if(unit.state == "onAttack")
        {
          unitToCreate.assignedEnemy = this.findAssignedEnemy(unit);
        }
        unitToCreate.state = unit.state;
        this.addPlayerCombatUnit(unitToCreate); 
        break;
      case 2:        
        this.addAICombatUnit(unitToCreate);          
        break;
      case 3:
       // If a collector was gathering, this finds the resource from which it was
       // gathering, and assigns it
        if(unit.state == "gathering")      
        {
          for (var i = 0; i < this.resources.length; i++)
          {
            if(unit.currentResource.currPos.x == this.resources[i].currPos.x
               && unit.currentResource.currPos.y == this.resources[i].currPos.y
               && unit.currentResource.type == this.resources[i].type
               && unit.currentResource.resource_amount == this.resources[i].resource_amount)
            {
              unitToCreate.currentResource = this.resources[i];
            }
          }
        }

        unitToCreate.state = unit.state; 
        unitToCreate.payload = unit.payload; 
        unitToCreate.homeBase.x = unit.homeBase.x;
        unitToCreate.homeBase.y = unit.homeBase.y;
        this.addPlayerGathererUnit(unitToCreate);         
        break;
      case 4:
        // currentResource??
        if(unit.state == "gathering")      
        {
          for (var i = 0; i < this.resources.length; i++)
          {
            if(unit.currentResource.currPos.x == this.resources[i].currPos.x
               && unit.currentResource.currPos.y == this.resources[i].currPos.y
               && unit.currentResource.type == this.resources[i].type
               && unit.currentResource.resource_amount == this.resources[i].resource_amount)
            {
              unitToCreate.currentResource = this.resources[i];
            }
          }
        }       
        unitToCreate.state = unit.state; 
        unitToCreate.payload = unit.payload;      
        unitToCreate.homeBase.x = unit.homeBase.x;
        unitToCreate.homeBase.y = unit.homeBase.y;           
        this.addAIGathererUnit(unitToCreate);          
        break;          
    }  
  }
}

GameState.prototype.parseBuildingsToObjects = function(building)
{
  var buildingToCreate = null;
  var buildingType = null;
  if (building)
  {
    switch (building.type)
    {    
    // Clan 1 buildings
    case "Clan1_Lab":
      buildingType = 1;
      buildingToCreate = new Clan1_Lab(building.currPos.x, building.currPos.y);
      break;
    case "Clan1_Factory1":      
      buildingType = 1;    
      buildingToCreate = new Clan1_Factory1(building.currPos.x, building.currPos.y);
      break;
    case "Clan1_factory2":
      buildingType = 1;
      buildingToCreate = new Clan1_Factory2(building.currPos.x, building.currPos.y);
      break;
    case "Clan1_Factory3":
      buildingType = 1;
      buildingToCreate = new Clan1_Factory3(building.currPos.x, building.currPos.y);
      break;       
    case "Clan1_MissileTower":
      buildingType = 3;
      buildingToCreate = new Clan1_MissileTower(building.currPos.x, building.currPos.y);
      break;
    case "Clan1_Tower":
      buildingType = 3;
      buildingToCreate = new Clan1_Tower(building.currPos.x, building.currPos.y);
      break;
    case "Clan1_Training1":
      buildingType = 1;
      buildingToCreate = new Clan1_Training1(building.currPos.x, building.currPos.y);
      break;
    case "Clan1_Training2":
      buildingType = 1;
      buildingToCreate = new Clan1_Training2(building.currPos.x, building.currPos.y);
      break;   
    case "Clan1_Training3":          
      buildingType = 1;
      buildingToCreate = new Clan1_Training3(building.currPos.x, building.currPos.y);
      break;    

    // Clan 2 buildings
    case "Clan2_Lab":
      buildingType = 2;
      buildingToCreate = new Clan2_Lab(building.currPos.x, building.currPos.y);
      break;
    case "Clan2_Factory1":      
      buildingType = 2;    
      buildingToCreate = new Clan2_Factory1(building.currPos.x, building.currPos.y);
      break;
    case "Clan2_Factory2":
      buildingType = 2;
      buildingToCreate = new Clan2_Factory2(building.currPos.x, building.currPos.y);
      break;
    case "Clan2_Factory3":
      buildingType = 2;
      buildingToCreate = new Clan2_Factory3(building.currPos.x, building.currPos.y);
      break;       
    case "Clan2_MissileTower":
      buildingType = 4;
      buildingToCreate = new Clan2_MissileTower(building.currPos.x, building.currPos.y);
      break;
    case "Clan2_Tower":
      buildingType = 4;
      buildingToCreate = new Clan2_Tower(building.currPos.x, building.currPos.y);
      break;
    case "Clan2_Training1":
      buildingType = 2;
      buildingToCreate = new Clan2_Training1(building.currPos.x, building.currPos.y);
      break;
    case "Clan2_Training2":
      buildingType = 2;
      buildingToCreate = new Clan2_Training2(building.currPos.x, building.currPos.y);
      break;   
    case "Clan2_Training3":          
      buildingType = 2;
      buildingToCreate = new Clan2_Training3(building.currPos.x, building.currPos.y);
      break;      
    }  

    buildingToCreate.health = building.health;
    buildingToCreate.isAI = building.isAI;
    buildingToCreate.killed = building.killed;

    if(building.currentBuildTime > 0)
    {
      buildingToCreate.currentBuildTime = building.currentBuildTime;
      buildingToCreate.howManyUnits = building.howManyUnits;
    }

    switch(buildingType)
    {
      case 1:      
        buildingToCreate.selected = building.selected;        
        this.addPlayerBuilding(buildingToCreate);          
        break;
      case 2:
        this.addAIBuilding(buildingToCreate);          
        break;
      case 3:
        buildingToCreate.selected = building.selected;  
        this.addPlayerTowers(buildingToCreate);         
        break;
      case 4:
        this.addAITowers(buildingToCreate);          
        break;          
    }     
  }   
}

GameState.prototype.parseResourcesToObjects = function(resource)
{
  var resourceToCreate = null;
  if (resource)
  {
    switch (resource.type)
    {    
    // Clan 1 buildings
    case "Resource1":
      resourceToCreate = new Resource1(resource.currPos.x, resource.currPos.y);
      break;
    case "Resource2":
      resourceToCreate = new Resource2(resource.currPos.x, resource.currPos.y);
      break;
    case "Resource3":
      resourceToCreate = new Resource3(resource.currPos.x, resource.currPos.y);
      break;            
    }  

    resourceToCreate.resource_amount = resource.resource_amount;
    resourceToCreate.selected = resource.selected;
    this.addResource(resourceToCreate);
  }   
}

GameState.prototype.findAssignedEnemy = function(playerUnit)
{
  // Iterate through AI combat units
  for (var i = 0; i < this.units.aiCombat.length; i++)
  {
    if (this.compareEnemyAttributes(playerUnit, this.units.aiCombat[i]))
    {
      return this.units.aiCombat[i];
    }
  }
  // Iterate through AI gatherers
  for (var i = 0; i < this.units.aiGatherer.length; i++)
  {
    if (this.compareEnemyAttributes(playerUnit, this.units.aiGatherer[i]))
    {
      return this.units.aiGatherer[i];
    }    
  }
  // Iterate through AI buildings
  for (var i = 0; i < this.buildings.aiBuildings.length; i++)
  {
    if (this.compareEnemyAttributes(playerUnit, this.buildings.aiBuildings[i]))
    {
      return this.buildings.aiBuildings[i];
    }    
  }

  // Iterate through AI towers
  for (var i = 0; i < this.buildings.aiTowers.length; i++)
  {
    if (this.compareEnemyAttributes(playerUnit, this.buildings.aiTowers[i]))
    {
      return this.buildings.aiTowers[i];
    }    
  }
}

GameState.prototype.compareEnemyAttributes = function(playerUnit, possibleTarget)
{
  return (playerUnit.assignedEnemy.type == possibleTarget.type
        && playerUnit.assignedEnemy.currPos.x == possibleTarget.currPos.x
        && playerUnit.assignedEnemy.currPos.y == possibleTarget.currPos.y
        && playerUnit.assignedEnemy.health == possibleTarget.health);
}

init();