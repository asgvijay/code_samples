"use strict";

var AIModule = function() {
	this.resources = 500;
	this.lastCalcState = []; //saves a copy of the features from last pass
	this.oldQvalue = 0;
	this.oldActionIndex = -1;
	this.actions = [
        this.makeVehicle,
        this.makeFighter,
        this.makeBuilder,
        this.buildFactory,
        this.buildTraining,
        this.buildTower,
        //this.buildLab,
        this.builderToGather,
        //this.builderToRepair,
        //this.addUnitToGroup,
        this.unitAttackBuilding,
        //this.groupAttackBuilding,
        this.unitAttackBuilder,
        //this.groupAttackBuilder,
        this.unitAttackComUnit,
        //this.groupAttackComUnit,
        this.unitDefend
        //this.groupDefend
	];
	this.pVehicles = 0;
	this.pFighters = 0;
	this.aiVehicles = 0;
	this.aiFighters = 0;
	this.trainingCost = 300;
	this.factoryCost = 250;
	this.towerCost = 150;
	this.beingAttacked = false;
	this.beingAttackedLocation = null;
	this.buildLocation = null;
	this.maxBuildings = 0;
	this.lastBuildLocation = null;
    this.homeBase = null;
    this.buildDirection = 1;
    this.attacking = false; //gets set by the aiModules when a unit or group are sent to attack a player building
	this.idleBuilderObj = null; //holds a reference to an idle builder if one is found
    //this.farResource = {x: 0, y :0}; //stores information about a distant resource that we are currently gathering from
    //this.damagedBuildingObj = null; //holds a reference to the most recently found damaged building
    //this.nonAttackingGroups = []; //holds an array of groups that are not currently attacking
    //this.labTimer = 0;
};



AIModule.prototype.updateAI =  function(gameState) {
    //console.log('this is the game difficulty: ' + gameState.difficulty);
	var featuresArray = this.calcFeatures(gameState); //calculate the features of the current gameState
    //console.log('featuresArray: ' + featuresArray);
	var qValues = this.getQValues(featuresArray, gameState); //Calculate the Q values for each action/state pair
    //console.log('qValues: ' + qValues);
	var maxQValue = this.getMaxOfArray(qValues); //Get the highest Q value
    //console.log('maxQValue: ' + maxQValue);
	var actionIndex = qValues.indexOf(maxQValue); //use the highest Q value to find the index of the action
    gameState.aiPlayer.updateLastState(gameState, maxQValue, gameState.aiPlayer.oldQvalue, gameState.aiPlayer.oldActionIndex, gameState.aiPlayer.lastCalcState); //update the last state weights using the new state
	//use the above function and an array of functions to call the appropriate function
    gameState.aiPlayer.lastCalcState = featuresArray.slice(0); //save the old gameState
    //console.log('this is the last state of the game: ', this.lastCalcState);
    gameState.aiPlayer.oldQvalue = maxQValue; //save the old Qvalue
    gameState.aiPlayer.oldActionIndex = actionIndex; //save the old index to get the weights
    gameState.aiPlayer.actions[actionIndex](gameState);
    //console.log('This is the actionIndex: ' + actionIndex);
    //console.log(aiWeights[gameState.difficulty][actionIndex]);
    //console.log(gameState.units.aiCombat);
    //console.log(gameState.buildings.aiBuildings);
	//return control to the gameLoop
};

AIModule.prototype.calcFeatures = function(gameState) {
    gameState.aiPlayer.getCombatCounts(gameState);
    gameState.aiPlayer.calcBeingAttacked(gameState);
    var gs;
    gs = [];
    gs.push(gameState.aiPlayer.noFactory(gameState));

    gs.push(gameState.aiPlayer.noTraining(gameState));

	gs.push(gameState.aiPlayer.playerHasMoreVehicles(gameState));

	gs.push(gameState.aiPlayer.playerHasLessVehicles(gameState));

	gs.push(gameState.aiPlayer.playerHasMoreFighters(gameState));

	gs.push(gameState.aiPlayer.playerHasLessFighters(gameState));

	gs.push(gameState.aiPlayer.playerHasMoreResources(gameState));

	gs.push(gameState.aiPlayer.aiHasMoreResources(gameState));

	gs.push(gameState.aiPlayer.getBeingAttacked(gameState));

	gs.push(gameState.aiPlayer.getAttacking(gameState));

	gs.push(gameState.aiPlayer.aiHasMoreBuildings(gameState));

	gs.push(gameState.aiPlayer.playerHasMoreBuildings(gameState));

	gs.push(gameState.aiPlayer.aiHasMoreBuilders(gameState));

	gs.push(gameState.aiPlayer.playerHasMoreBuilders(gameState));

	gs.push(gameState.aiPlayer.idleBuilder(gameState));

	gs.push(gameState.aiPlayer.lowResourceRatio(gameState));

	gs.push(gameState.aiPlayer.highResourceRatio(gameState));

	//gs.push(this.longBuilderTravelPath(gameState)); //temp removed for simplicity; may add again later

	gs.push(gameState.aiPlayer.damagedBuilding(gameState));

	//gs.push(this.enoughLooseUnits(gameState)); //temp removed for simplicity; may add again later

	//gs.push(this.allGroupsAttacking(gameState));

	//gs.push(this.nonAttackingGroups(gameState));

	//gs.push(this.enoughGroupsToAttack(gameState));

	gs.push(gameState.aiPlayer.buildersRecentlyAttacked(gameState));

	//gs.push(this.noGroupsFormed(gameState));

	//gs.push(this.labTimerDone());

    return gs;
};

AIModule.prototype.setBuildLocation = function(gameState) {
    if (gameState.aiPlayer.maxBuildings == 8){
        console.log('too many buildings');
        return null;
    }
    if (gameState.aiPlayer.lastBuildLocation == null){
        if (gameState.aiPlayer.homeBase == null){
            return null;
        }
        gameState.aiPlayer.lastBuildLocation = gameState.aiPlayer.homeBase;
    }

    var buildDirection = gameState.aiPlayer.buildDirection;
    var adjustment = {x: 0, y:0 };

    //figure out the adjustments for the direction we are trying to build
    if (buildDirection == 1){
        adjustment.y =  - 65;
    } else if (buildDirection == 2){
        adjustment.x = 65;
        adjustment.y = -65;
    } else if (buildDirection == 3){
        adjustment.x = 65;
    } else if (buildDirection == 4) {
        adjustment.y = 65;
        adjustment.x = 65;
    } else if (buildDirection == 5){
        adjustment.y = -65;
    } else if (buildDirection == 6){
        adjustment.x = -65;
        adjustment.y =65;
    } else if (buildDirection == 7){
        adjustment.x = -65;
    } else if (buildDirection == 8){
        adjustment.x =-65;
        adjustment.y =-65;
    }
    var location = {currPos: {x: gameState.aiPlayer.lastBuildLocation.x + adjustment.x, y:gameState.aiPlayer.lastBuildLocation.y +adjustment.y},
                    size: {x: 65, y: 65}};
    var looking = true;

    if (location.currPos.x > 1500 || location.currPos.x < 0 || location.currPos.y > 844 || location.currPos.y < 0 ){
        console.log('the x and y coords are too either too big or too large');
        console.log(location);
        gameState.aiPlayer.buildDirection++;
        return null;
    }



    while(looking){
        if (checkLocation(location, gameState)){
            location.currPos.x += adjustment.x;
            location.currPos.y = adjustment.y;

            if (location.currPos.x > 1500 || location.currPos.x < 0 || location.currPos.y > 844 || location.currPos.y < 0){
                console.log('the x and y coords are too large');
                console.log(location);
                gameState.aiPlayer.buildDirection++;
                return null;
            }
        } else {
            looking = false;
        }

    }

    gameState.aiPlayer.buildDirection++;
    if (gameState.aiPlayer.buildDirection > 8){
        gameState.aiPlayer.buildDirection = 1;
    }
    gameState.aiPlayer.lastBuildLocation = location.currPos;
    gameState.aiPlayer.maxBuildings++;

    return location.currPos;


};


function checkLocation(location, gameState){
    var resources = gameState.resources;
    var aiBuildings = gameState.buildings.aiBuildings;
    var pBuildings = gameState.buildings.pBuildings;
    var aiTowers = gameState.buildings.aiTowers;
    var pTowers = gameState.buildings.pTowers;

    for (var i = 0; i < resources.length; i++){
        if (detectCollision(location, resources[i])){
            return true;
        }
    }

    for ( i = 0; i < aiBuildings.length; i++){
        if (detectCollision(location, aiBuildings[i])){
            return true;
        }
    }

    for ( i = 0; i < pBuildings.length; i++){
        if (detectCollision(location, pBuildings[i])){
            return true;
        }
    }

    for (i = 0; i < aiTowers.length; i++){
        if (detectCollision(location, aiTowers[i])){
            return true;
        }
    }

    for (i = 0; i < pTowers.length; i++){
        if (detectCollision(location, pTowers[i])){
            return true;
        }
    }
    return false;
};





/*This function takes a numerical array and returns the highest value
It is of note that I found this function on the MDN website at the following URL:
https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Math/max*/
AIModule.prototype.getMaxOfArray = function(numArray) {
    return Math.max.apply(null, numArray);
};


/*This function takes the old state and and the index of the new state to calculate the updated Q value and weights for a given state.*/
AIModule.prototype.updateLastState = function(gameState, newQValue, oldQvalue, oldActionIndex, lastState){

	var discount = 0.9;
	var learningRate = 0.2;
	var reward = 0;
	var weights;
	var gameOver = gameState.gameOver();
	//console.log('this is the gameover value in updateLastState: ' + gameOver);

	//decide the reward value
	if (gameOver == 0) {
		reward = -2;
	} else if (gameOver == 1){
		reward = -100; //means ai lost
	} else {
		reward = 100; //means ai won
	}

    if(gameState.difficulty == 'easy'){
        weights = easyWeights['easy'];
    } else {
        weights = aiWeights['hard'];
    }

	var correction =  reward + discount * newQValue - oldQvalue;
    //console.log('The length of lastState: ' + lastState.length);

    if(lastState.length < 19){
        console.log('It appears the lastState does not have enough features');
        return;
    }

	//update the weights for the previous action taken
    for (var j = 0; j < lastState.length;j++) { //loop over the old features and update the weights based on the correction value and the learning rate
        weights[oldActionIndex][j] += learningRate * correction * lastState[j];
        //console.log('The length of the weights: ' + weights[oldActionIndex].length);
    }

    if(gameOver != 0){
        saveWeights();
        gameState.breakMainGameLoop();
        gameState.drawGameOverText(gameOver);
    }

};




/*This function extracts the information from the weights.json file and uses it to calculate the actionValues for each possible choice given the current gameState. It then returns an array with an actionValue for each possible choice in the order they are presented in teh json document.*/
AIModule.prototype.getQValues = function(gsArray, gameState) {
	var actionValues = []; //array that will hold the end values for each action
	var total; //holds the total for each iteration
    var weights;

    if(gameState.difficulty == 'easy'){
        weights = easyWeights['easy'];
    } else {
        weights = aiWeights['hard'];
    }

	//This outer loop iterates over the highLevel object to extract the weights array for each high level decision
	for (var j = 0; j < weights.length; j ++){
        total = 0;
        //console.log('prop inside getQValues: ' + weights[j]);
        //This loops through the gsArray and the weights for a particular decision and adds it to the appropriate index in the actionValues array
        for(var i = 0; i < gsArray.length; i++){
            total += weights[j][i] * gsArray[i];
        }
        actionValues.push(total); //push the total onto the array
	}

	return actionValues;
};




//This function performs a breadth first search to find the nearest enemy combat unit
AIModule.prototype.findNearestEnemyComUnit = function(unit, gameState){
    var unitX = unit.currPos.x;
    var unitY = unit.currPos.y;
    var  gatherers = gameState.units.pCombat;
    var best = 10000;
    var bestEnemy;

    if (gatherers.length <= 0){
        //console.log('there are not resources in the game according to findNearestResource');
        return null;
    }

    for (var i = 0 ; i < gatherers.length; i++) {
        var a = unitX - gatherers[i].currPos.x;
        var b = unitY - gatherers[i].currPos.y;

        a = Math.pow(a, 2);
        b = Math.pow(b, 2);

        var result = Math.sqrt(a+b);

        if (result < best){
            best = result;
            bestEnemy = gatherers[i];
        }
    }

    return bestEnemy;
};


//This function performs a breadth first search to find the nearest enemy building
//This function tries to find a tower before a building to help target their defensive
//buildings first
AIModule.prototype.findNearestEnemyBuilding = function(unit, gameState){
    var unitX = unit.currPos.x;
    var unitY = unit.currPos.y;
    var buildings = gameState.buildings.pBuildings;
    var towers = gameState.buildings.pTowers;
    var walls = gameState.buildings.pWalls;
    var best = 10000;
    var bestEnemy = null;

    if (buildings.length <= 0 && towers.length <= 0 && walls.length <= 0){
        //console.log('there are not resources in the game according to findNearestEnemyBuilding');
        return null;
    }

    for (var i = 0 ; i < buildings.length; i++) {
        var a = unitX - buildings[i].currPos.x;
        var b = unitY - buildings[i].currPos.y;

        a = Math.pow(a, 2);
        b = Math.pow(b, 2);

        var result = Math.sqrt(a+b);

        if (result < best){
            best = result;
            bestEnemy = buildings[i];
        }
    }

    if (bestEnemy != null) {
        return bestEnemy;
    }

    for (i = 0 ; i < towers.length; i++) {
        a = unitX - towers[i].currPos.x;
        b = unitY - towers[i].currPos.y;

        a = Math.pow(a, 2);
        b = Math.pow(b, 2);

        result = Math.sqrt(a+b);

        if (result < best){
            best = result;
            bestEnemy = towers[i];
        }
    }

    if (bestEnemy != null) {
        return bestEnemy;
    }

    for (i = 0 ; i < walls.length; i++) {
        a = unitX - walls[i].currPos.x;
        b = unitY - walls[i].currPos.y;

        a = Math.pow(a, 2);
        b = Math.pow(b, 2);

        result = Math.sqrt(a+b);

        if (result < best){
            best = result;
            bestEnemy = walls[i];
        }
    }

    return bestEnemy;
};


//This function performs a breadth first search to find the nearest enemy combat unit
AIModule.prototype.findNearestResource = function(unit, gameState){
    var unitX = unit.currPos.x;
    var unitY = unit.currPos.y;
    var resources = gameState.resources;
    var best = 10000;
    var bestResource;

    if (resources.length <= 0){
        //console.log('there are not resources in the game according to findNearestResouce');
        return null;
    }

    for (var i = 0 ; i < resources.length; i++) {
        var a = unitX - resources[i].currPos.x;
        var b = unitY - resources[i].currPos.y;

        a = Math.pow(a, 2);
        b = Math.pow(b, 2);

        var result = Math.sqrt(a+b);

        if (result < best){
            best = result;
            bestResource = resources[i];
        }
    }

    return bestResource;
};


//This method searches from the units current location to find the nearest enemy gatherer to attack
AIModule.prototype.findNearestEnemyGatherUnit = function(unit, gameState){
    var unitX = unit.currPos.x;
    var unitY = unit.currPos.y;
    var gatherers = gameState.units.pGatherer;
    var best = 10000;
    var bestEnemy;

    if (gatherers.length <= 0){
        //console.log('there are not resources in the game according to findNearestResouce');
        return null;
    }

    for (var i = 0 ; i < gatherers.length; i++) {
        var a = unitX - gatherers[i].currPos.x;
        var b = unitY - gatherers[i].currPos.y;

        a = Math.pow(a, 2);
        b = Math.pow(b, 2);

        var result = Math.sqrt(a+b);

        if (result < best){
            best = result;
            bestEnemy = gatherers[i];
        }
    }

    return bestEnemy;
};


//This function iterates over the combat units for the player and the ai to get
//some quick counts regarding the vehicles and fighters for each side
AIModule.prototype.getCombatCounts = function(gameState) {
	gameState.aiPlayer.pVehicles = 0;
    gameState.aiPlayer.pFighters = 0;
    gameState.aiPlayer.aiVehicles = 0;
    gameState.aiPlayer.aiFighters = 0;

	var pCombat = gameState.units.pCombat;
	var aiCombat = gameState.units.aiCombat;
	for (var i = 0; i < pCombat.length; i++) {
		if (pCombat[i].unitType == 'vehicle') {
            gameState.aiPlayer.pVehicles += 1;
		} else {
            gameState.aiPlayer.pFighters += 1;
		}
	}

	for (var j = 0; j < aiCombat.length; j++) {
		if (aiCombat[j].unitType == 'vehicle') {
            gameState.aiPlayer.aiVehicles += 1;
		} else {
            gameState.aiPlayer.aiFighters += 1;
		}
	}

};



//This iterates over the buildings to get information about the current gameState
//It checks to see if any buildings are being attacked and returns the coordinates
//for the first building being attacked
AIModule.prototype.calcBeingAttacked = function( gameState ) {
    gameState.aiPlayer.beingAttacked = false; //set this to false to ignore old gameState

	//gets an object of just the ai buildings
	var buildings = [
		gameState.buildings.aiBuildings,
		gameState.buildings.aiTowers,
		gameState.buildings.aiWalls
	];
	//this loops over the object variables
	for (var j = 0 ; j < buildings.length; j++) {
        for (var i = 0; i < buildings[j].length; i++) {
            //console.log(buildings[j][i]);
            //this checks if that building is beingAttacked and if so sets the appropriate variables
            if (buildings[j][i].beingAttacked == true) {
                gameState.aiPlayer.beingAttackedLocation = {x:buildings[j][i].currPos.x, y:buildings[j][i].currPos.y};
                gameState.aiPlayer.beingAttacked = true;
                break; //we found a building being attacked so we return
            }
        }
    }
};


//this method checks if the ai has a factory
//if there is no factory it returns true
AIModule.prototype.noFactory = function(gameState) {
    var buildings = gameState.buildings.aiBuildings;

    if(buildings.length == 1) {
        return true;
    }

    for (var i = 0; i < buildings.length; i++){
        if (buildings[i].unitType == 'factory') {
            return false;
        }
    }
    return true;
};


//this methods checks if the ai has a training center
//if the ai does it returns false
AIModule.prototype.noTraining = function(gameState) {
    var buildings = gameState.buildings.aiBuildings;

    if(buildings.length == 1) {
        return true;
    }

    for (var i = 0; i < buildings.length; i++){
        if (buildings[i].unitType == 'training') {
            return false;
        }
    }
    return true;
};


//returns true if the player has mroe vehicles than the player
AIModule.prototype.playerHasMoreVehicles = function(gameState)
{

	return gameState.aiPlayer.aiVehicles < gameState.aiPlayer.pVehicles;

};


//returns true if the ai has more vehicles than the player
AIModule.prototype.playerHasLessVehicles = function(gameState) {
	return gameState.aiPlayer.aiVehicles > gameState.aiPlayer.pVehicles;

};

//returns true if the player has more fighters and false otherwise
AIModule.prototype.playerHasMoreFighters = function(gameState) {
	return gameState.aiPlayer.aiFighters <= gameState.aiPlayer.pFighters;

};

//returns true if the ai has more fighters and false otherwise
AIModule.prototype.playerHasLessFighters = function(gameState) {
	return gameState.aiPlayer.aiFighters >= gameState.aiPlayer.pFighters;

};

//returns true if the player has more resources and false otherwise
AIModule.prototype.playerHasMoreResources = function(gameState) {
	return gameState.aiPlayer.resources < gameState.player.getResources ();

};

//returns true if the ai has more resources false otherwise
AIModule.prototype.aiHasMoreResources = function(gameState) {
	return gameState.aiPlayer.resources > gameState.player.getResources ();
};

//returns true if any AI buildings are being attacked
AIModule.prototype.getBeingAttacked = function(gameState) {
	return gameState.aiPlayer.beingAttacked;
};


//returns true if AI is attacking
AIModule.prototype.getAttacking = function(gameState) {
	return gameState.aiPlayer.attacking;

};

//returns true if AI has mroe buildings than the player
AIModule.prototype.aiHasMoreBuildings = function(gameState){
	return gameState.buildings.aiBuildings.length > gameState.buildings.pBuildings.length;

};

//returns true if the player has mroe buildings
AIModule.prototype.playerHasMoreBuildings = function(gameState) {
	return gameState.buildings.aiBuildings.length < gameState.buildings.pBuildings.length;
};


//returns true if the ai has more builders
AIModule.prototype.aiHasMoreBuilders  = function(gameState) {
	return gameState.units.aiGatherer.length > gameState.units.pGatherer.length;
};

//returns true if the player has more builders
AIModule.prototype.playerHasMoreBuilders  = function(gameState) {
	return gameState.units.aiGatherer.length < gameState.units.pGatherer.length;
};

//returns true if there are any idle builders/gatherers
AIModule.prototype.idleBuilder  = function(gameState) {
    //console.log('isnide the idleBuilder()');
	var builders = gameState.units.aiGatherer;
	//console.log('builder length ' + builders.length);
	for (var i = 0; i < builders.length; i++) {
	    //console.log(builders[i]);
        if ((builders[i].state == 'idle')) {
            //console.log('inside the idle builder method');
            //console.log(builders[i]);
            gameState.aiPlayer.idleBuilderObj = builders[i];
            return true;
        }
        //console.log('still inside the idleBuilder method');
    }
    return false;

};

//This returns true if the AI has a low resource ratio
//This is based on the number of units + buildings 
AIModule.prototype.lowResourceRatio  = function(gameState) {
    var buildings = gameState.buildings.aiBuildings;
    var towers = gameState.buildings.aiTowers;
    var gatherers = gameState.units.aiGatherer;
    var comUnits = gameState.units.aiCombat;

    var total = buildings.length + towers.length + gatherers.length + comUnits.length;

    return gameState.aiPlayer.resources / total < 50;


};

AIModule.prototype.highResourceRatio  = function(gameState) {
    var buildings = gameState.buildings.aiBuildings;
    var towers = gameState.buildings.aiTowers;
    var gatherers = gameState.units.aiGatherer;
    var comUnits = gameState.units.aiCombat;

    var total = buildings.length + towers.length + gatherers.length + comUnits.length;

    return gameState.aiPlayer.resources / total > 100;
};

/* temp removed for simplicity
//This function calculates the euclidean distance for each gatherer to their currently assigned resource
//if that value is over 100 it returns true
AIModule.prototype.longBuilderTravelPath  = function(gameState) {
	var gatherers = gameState.units.aiGatherer;
    for (var i = 0; i < gatherers.length; i++) {
        var distX = gatherers[i].currPos.x - gatherers[i].currentResource.currPos.x;
        var distY = gatherers[i].currPos.y - gatherers[i].currentResource.currPos.y;

        distX = Math.pow(distX, 2);
        distY = Math.pow(distY, 2);

        var result = Math.sqrt(distX + distY);

        if (result > 100){
            this.farResource.x = gatherers[i].currentResource.currPos.x;
            this.farResource.y = gatherers[i].currentResource.currPos.y;
            return true;
        }
    }
	return false;
};*/


//this function determines if we have any damaged buildings
//if so it assigns the damaged buildings variable and returns true
AIModule.prototype.damagedBuilding  = function(gameState) {
    var buildings = gameState.buildings.aiBuildings;
    var towers = gameState.buildings.aiTowers;
    var walls =  gameState.buildings.aiWalls;

    for (var i = 0; i < buildings.length; i++){
        if (buildings[i].health < buildings[i].maxHealth) {
            gameState.aiPlayer.damagedBuildingObj = buildings[i];
            return true;
        }
    }

    for (var j = 0; j < towers.length; j++) {
        if (towers[i].health < towers[i].maxHealth) {
            gameState.aiPlayer.damagedBuildingObj = towers[i];
            return true;
        }
    }

    for (var k = 0; k < walls.length; k++){
        if(walls[i].health < walls[i].maxHealth){
            gameState.aiPlayer.damagedBuildingObj = walls[i];
            return true;
        }
    }
	return false;
};

/*temp removed for simplicity
//This function checks to see if we have more than 3 vehicles loose and five fighters loose
//and returns true if we do
AIModule.prototype.enoughLooseUnits  = function(gameState) {
    var vehicleCount = 0;
    var fighterCount = 0;
    var units = gameState.units.aiCombat;

    for (var i = 0; i < units.length; i++) {
        if (!units[i].isGrouped) {
            if (units[i].unitType == 'vehicle'){
                vehicleCount++;
            } else {
                fighterCount++;
            }
        }
    }

    return !!(vehicleCount >= 3 && fighterCount >= 5);


};*/


/*temp removed for simplicity
//This looks through the groups and returns true if all groups are attacking
AIModule.prototype.allGroupsAttacking  = function(gameState) {
    var groups = gameState.groups.aiGroups;

    if (groups.length == 0){
        return false;
    }

    for (var i = 0; i < groups.length; i++){
        if (groups[i].isAttacking == false) {
            return false;
        }
    }
	 return true;
};*/


/*temp removed for simplicity
//This method checks to see if there are groups that are not currently attacking
//it adds any nonAttackingGroups to an array
//it returns true if there are any that aren't attacking
//if there are no aiGroups it returns false
//it sets the value of nonAttackingGroup to the first group it finds
AIModule.prototype.nonAttackingGroups  = function(gameState) {
    var nonAttackingGroups = [];
    var groups = gameState.groups.aiGroups;

    if (groups.length == 0) {
        return false;
    }

    for (var i = 0; i < groups.length; i++){
        if(groups[i].isAttacking == false){
            nonAttackingGroups.push(groups[i]);
        }
    }

    if (nonAttackingGroups.length > 0) {
        this.nonAttackingGroups = nonAttackingGroups;
        return true;
    }

    return false;

};*/



/*temp removed for simplicity
//This function checks to see if there are enough groups to attack a player building
//if there are more than 3 groups available it returns true
AIModule.prototype.enoughGroupsToAttack  = function(gameState) {
    return gameState.groups.aiGroups.length > 3;
};*/


//This method checks if
AIModule.prototype.buildersRecentlyAttacked  = function(gameState) {
    var gatherers = gameState.units.aiGatherer;

    for (var i = 0; i < gatherers.length; i++){
        if (gatherers[i].state == 'flee') {
            return true;
        }
    }
	return false;
};

/*temp removed for simplicity
//This method checks if there are any groups and returns true if there are none
AIModule.prototype.noGroupsFormed  = function(gameState) {
    return gameState.groups.aiGroups.length == 0;

};*/


/*temp removed for simplicity
//This method checks if the lab timer is done
AIModule.prototype.labTimerDone  = function() {
	var now = performance.now();
    var temp = (this.labTimer - now)/1000;

    return temp >= 15;
};*/



//This method tells the tells an aiBuilding to make another vehicle
//it iterates over the aiBuildings and looks for a factory type
//it then tells the building to add another vehicle to its queue
AIModule.prototype.makeVehicle  = function(gameState) {
    var buildings = gameState.buildings.aiBuildings;
	var factory = null; //hold the reference to the factory
	var queue = 100;

	//iterate over the buildings to find the factory with the lowest queue
    for (var i = 0; i < buildings.length; i++){
		if (buildings[i].unitType == 'factory'){
			if(buildings[i].howManyUnits <  queue) {
				queue = buildings[i].howManyUnits;
				factory = buildings[i];
			}
		}
    }
    if (factory == null){
        console.log('no factories to make a vehicle');
    }

    //if no factories return
	if (factory != null && gameState.aiPlayer.resources >= factory.unitCostToBuild) { //check if I have enough resources
		factory.howManyUnits++;
		console.log('incrementing the building units count');
        gameState.aiPlayer.resources -= factory.unitCostToBuild;
        //console.log('deducting resources for vehicle');
        return;
	}
	console.log(gameState.aiPlayer.resources);
	console.log('this is exiting wihtout doing anything');
};


//This method tells the tells an aiBuilding to make another fighter
//it iterates over the aiBuildings and looks for a training type
//it then tells the building to add another fighter to its queue
AIModule.prototype.makeFighter  = function(gameState) {
	var buildings = gameState.buildings.aiBuildings;
	var training = null; //hold the reference to the factory
	var queue = 100;

	//iterate over the buildings to find the training with the lowest queue
	for (var i = 0; i < buildings.length; i++){
		if (buildings[i].unitType == 'training'){
			if(buildings[i].howManyUnits <  queue) {
				queue = buildings[i].howManyUnits;
				training = buildings[i];
			}
		}
	}
	if(training == null){
        console.log('no training to make a fighter');
    }

	//if no training return
	if (training != null && gameState.aiPlayer.resources >= training.unitCostToBuild) { //check if I have enough resources
		training.howManyUnits++;
        gameState.aiPlayer.resources -= training.unitCostToBuild;
        //console.log('deducting resources for fighter');
	}
};


//This method tells the tells an aiBuilding to make another builder
//it iterates over the aiBuildings and looks for a lab type
//it then tells the building to add another builder to its queue
AIModule.prototype.makeBuilder  = function(gameState) {
	var buildings = gameState.buildings.aiBuildings;
	var lab = null; //hold the reference to the factory
	var queue = 100;

	//iterate over the buildings to find the training with the lowest queue
	for (var i = 0; i < buildings.length; i++){
		if (buildings[i].unitType == 'lab'){
			if(buildings[i].howManyUnits <  queue) {
				queue = buildings[i].howManyUnits;
				lab = buildings[i];
			}
		}
	}
	if (lab == null) {
        console.log('no lab to make a builder in makeBuilder');
    }
	//if no training return
	if (lab != null && gameState.aiPlayer.resources >= lab.unitCostToBuild) { //check if I have enough resources
		lab.howManyUnits++;
        gameState.aiPlayer.resources -= lab.unitCostToBuild;
        //console.log('deducting resources for gatherer');
	}
};


//This methods builds a factory if the resources are available and a location can be found
AIModule.prototype.buildFactory  = function(gameState) {
    if ((gameState.aiPlayer.resources - gameState.aiPlayer.factoryCost) < 0){
        console.log('not enough resources to build in buildFactory()');
        //console.log('Available Resources' + gameState.aiPlayer.resources);
        return;
    }

    var buildLocation = gameState.aiPlayer.setBuildLocation(gameState);

    if(buildLocation == null){
       //console.log('buildLocation returned null inside of buildFactory()');
        return;
    }

    gameState.aiPlayer.resources -= gameState.aiPlayer.factoryCost;
    //console.log('Resources inside build a factory after building' + gameState.aiPlayer.resources);

    var factory = new Clan2_Factory1(buildLocation.x, buildLocation.y);


    gameState.buildings.aiBuildings.push(factory);
};


//this method builds a training center if the resources are available and a
//location can be found
AIModule.prototype.buildTraining = function(gameState) {


    if ((gameState.aiPlayer.resources - gameState.aiPlayer.trainingCost) < 0){
        //console.log('not enough resources to build in buildTraining()');
        //console.log('Available Resources' + gameState.aiPlayer.resources);
        return;
    }

    var buildLocation = gameState.aiPlayer.setBuildLocation(gameState);

    if(buildLocation == null){
        //console.log('buildLocation returned null inside of buildTraining()');
        return;
    }

    gameState.aiPlayer.resources -= gameState.aiPlayer.trainingCost;
    //console.log('Resources inside build a training after building' + gameState.aiPlayer.resources);

    var training = new Clan2_Training1(buildLocation.x, buildLocation.y);

    gameState.buildings.aiBuildings.push(training);

};


//this method builds a tower if the resources are available and a location can be found
AIModule.prototype.buildTower  = function(gameState) {
    if ((gameState.aiPlayer.resources - gameState.aiPlayer.towerCost) < 0){
        //console.log('not enough resources to build in buildTower()');
        //console.log('Available Resources' + gameState.aiPlayer.resources);
        return;
    }

    var buildLocation = gameState.aiPlayer.setBuildLocation(gameState);

    if(buildLocation == null){
        //console.log('buildLocation returned null inside of buildTower()');
        return;
    }

    gameState.aiPlayer.resources -= gameState.aiPlayer.towerCost;
    //console.log('Resources inside build a tower after building' + gameState.aiPlayer.resources);

    var tower = new Clan2_Tower(buildLocation.x, buildLocation.y);

    gameState.buildings.aiBuildings.push(tower);

};

/*temp removed for project completion
AIModule.prototype.buildLab  = function(gameState) {

};*/



//This tells an idle builder to gather to gather resources from the nearest resource
AIModule.prototype.builderToGather  = function(gameState) {
    if (gameState.aiPlayer.idleBuilderObj == null){
        //console.log('There are no idle builders inside builderToGather call');
        return;
    }
    var gatherer = gameState.aiPlayer.idleBuilderObj;
    gameState.aiPlayer.idleBuilderObj = null;
    //console.log('inside the builderTogether method');
    //console.log(gatherer);

    var resource = gameState.aiPlayer.findNearestResource(gatherer, gameState);

    //console.log('this is the resource');
    //console.log(resource);

    if (resource == null){
        //console.log('could not find a resource inside builderToGather()');
        return;
    }
    var updateObj = [];

    updateObj.resource = resource;
    updateObj.state = 'enroute';
    gatherer.update(updateObj);
    //console.log('after updating the gatherer');
    //console.log(gatherer);
    //gameState.aiPlayer.idleBuilderObj = null;
};


/*temp removed for project completion
AIModule.prototype.builderToRepair  = function(gameState) {
    if (this.damagedBuilding == null || this.idleBuilder == null) {
       console.log('There are either no idle builders or no damaged buildings inside builderToRepair()');
       return;
    }

    this.idleBuilder.destPos.x = this.damagedBuilding.currPos.x;
    this.idleBuilder.destPos.y = this.damagedBuilding.currPos.y;
    this.idleBuilder.repairTarget = this.damagedBuilding;
    this.idleBuilder.state = 'repair';
    this.idleBuilder = null;
    this.damagedBuilding = null;
};*/

/*temp removed for project completion
AIModule.prototype.addUnitToGroup  = function(gameState) {

};*/

AIModule.prototype.unitAttackBuilding  = function(gameState) {
    var units = gameState.units.aiCombat;

    for (var i = 0; i < units.length; i++){
        if (units[i].state == 'idle'){
            var enemy = gameState.aiPlayer.findNearestEnemyBuilding(units[i], gameState);
            if(enemy == null){
                //console.log('could not find any enemies to attack inside of unitAttackBuilding()');
                return;
            }
            units[i].destPos.x = enemy.currPos.x;
            units[i].destPos.y = enemy.currPos.y;
            units[i].assignedEnemy = enemy;
            units[i].state = 'onAttack';
            return;
        }
    }

    //console.log('Could not find an idle combat unit inside of the unitAttackBuilding method');

};

/*temp removed for project completion
AIModule.prototype.groupAttackBuilding  = function(gameState) {

};*/


//This method tells a combat unit to attack an enemy gatherer
AIModule.prototype.unitAttackBuilder  = function(gameState) {
    var units = gameState.units.aiCombat;

    for (var i = 0; i < units.length; i++){
        if (units[i].state == 'idle'){
            var enemy = gameState.aiPlayer.findNearestEnemyGatherUnit(units[i], gameState);
            if(enemy == null){
                //console.log('could not find any enemies to attack inside of unitAttackBuilder()');
                return;
            }
            units[i].destPos.x = enemy.currPos.x;
            units[i].destPos.y = enemy.currPos.y;
            units[i].assignedEnemy = enemy;
            units[i].state = 'onAttack';
            return;
        }
    }

    //console.log('Could not find an idle combat unit inside of the attackBuilder method');
};


/*temp removed for project completion
AIModule.prototype.groupAttackBuilder  = function(gameState) {

};*/

AIModule.prototype.unitAttackComUnit  = function(gameState) {
    var units = gameState.units.aiCombat;

    for (var i = 0; i < units.length; i++){
        if (units[i].state == 'idle'){
            var enemy = gameState.aiPlayer.findNearestEnemyComUnit(units[i], gameState);
            if(enemy == null){
                //console.log('could not find any enemies to attack inside of unitAttackComUnit()');
                return;
            }
            units[i].destPos.x = enemy.currPos.x;
            units[i].destPos.y = enemy.currPos.y;
            units[i].assignedEnemy = enemy;
            units[i].state = 'onAttack';
            return;
        }
    }

    //console.log('Could not find an idle combat unit inside of the attackcomUnit method');

};


/*temp removed for project completion
AIModule.prototype.groupAttackComUnit  = function(gameState) {

};*/


//This method looks for an idle combat unit and sends them to a location where gatherers
//have recently been attacked.
AIModule.prototype.unitDefend  = function(gameState) {
	var units = gameState.units.aiCombat;

    if (gameState.aiPlayer.beingAttackedLocation == null) {
        //console.log('The unitDefend() method is being called without a location to defend.');
        return;
    }
    //console.log('still inside the unitDefend method');

	for (var i = 0; i < units.length; i++){
		if (units[i].state == 'idle'){
            units[i].destPos.x = gameState.aiPlayer.beingAttackedLocation.x;
            units[i].destPos.y = gameState.aiPlayer.beingAttackedLocation.y;
            units[i].state = 'enroute';
            gameState.aiPlayer.beingAttackedLocation = null;
            break;
		}
	}

	//console.log('Could not find an idle combat unit inside of the unitDefend method');

};


/*temp removed for project completion
AIModule.prototype.groupDefend  = function(gameState) {

};*/




