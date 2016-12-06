class BuildingClass extends EntityClass {


    constructor(xCoord, yCoord) {

        // run Entity Class constructor with x/y coords
        super(xCoord, yCoord);

        // mark the time the lab begins making an engineer
        this.startTime = 0;
        // flag whether or not enough time has passed

        this.unitReady = false;

        this.health = 1000;
        this.type = "";
        this.size.x = 100;
        this.size.y = 100;
        this.costToBuild = 0;
        // enter image name here
        this.spriteInfo.spriteSheet = "";
        this.spriteInfo.imgName = "";
        this.UnitsICreate = "";
        this.buildTime = 0;
        this.howManyUnits = 0;
        this.now = 0;
        this.currentBuildTime = 0;

        this.update = function (updateObj) {

            if(updateObj != null)
            {
                // if object needs to take damage
                if (updateObj.hasOwnProperty('damage'))
                    this._takeDamage(updateObj.damage);                    

                    


                if (this.health <= 0) {
                    this.killed = true;
                }
                // update lab's status
                if (updateObj.hasOwnProperty('state'))
                    this.state = updateObj.state;


                // GameState must send in a property called "anotherUnit" if building should start creating
                if (updateObj.hasOwnProperty('anotherUnit'))
                    this.howManyUnits += 1;

                if (updateObj.hasOwnProperty('selected'))
                    this.selected = updateObj.selected;                                                              
            }

            // If the building has been asked to make something, the "howManyUnits" property will be incremented.
            // check if it's greater than zero to being counter
            // mark the start of the construction time for the engineer. Once 30 seconds has passed, the building will be finished.
            if (this.howManyUnits > 0) {
                if (this.startTime == 0) {
                    this.startTime = performance.now();
                    this.unitReady = false;
                }
                    // if lab has begun building we must check duration of build. Once the correct amount of build time has finished, we must mark the lab as ready to to create an engineer.
                    // if an lab's "engineerReady" flag is true, we must let the gameEngine create a new Engineer.
                    // NOTE: THE gameEngine must change the engineerReady value back to FALSE once the engineer has been created.

                else
                {
                    this.now = performance.now();                    
                    this.currentBuildTime = (this.now - this.startTime);
                }
                    

                if ((this.now - this.startTime) >= this.buildTime)
                    {
                        //console.log("unitready is set to", this.unitReady);
                        //console.log("the current elapsed time:");

                        //console.log((this.now - this.startTime));
                        this.unitReady = true;
                        this.howManyUnits -= 1;
                        this.startTime = 0; // reset clock
                        this.now = 0;
                        //console.log(this.now);
                    }
                }





        }
        
           this.retrieveUnitInfo = function() {
						var unitInfo = {};
						unitInfo.spriteInfo = {spriteSheet: this.spriteInfo.spriteSheet, imgName:this.spriteInfo.imgName};
						unitInfo.isAI = this.isAI;
						unitInfo.currPos = this.currPos;
						unitInfo.destPos = this.destPos  
						unitInfo.size = {x:this.size.x, y:this.size.y};    
						unitInfo.selected = this.selected;
						unitInfo.maxHealth = this.maxHealth;
						unitInfo.currHealth = this.health;      
						unitInfo.velocity = this.velocity;
						unitInfo.state = this.state;
						unitInfo.target = this.target;
						unitInfo.type = this.type;
                        unitInfo.rotation = this.rotation_info.rotation;
						//unitInfo.inRange = this.enemyRange();
						return unitInfo;        
        };

    }
}

