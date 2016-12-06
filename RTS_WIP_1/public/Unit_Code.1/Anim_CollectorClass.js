class Anim_CollectorClass extends EntityClass{

    constructor(xCoord, yCoord){

        super(xCoord, yCoord);
 
    
        this.startTime = 0;

        this.repairTarget = null;
    
        this.payload = 0;
        this.payloadLimit = 0;

        this.costToBuild = 0;

        this.arrived = false;
    
        // this flags whether or not we can create building
        this.readyToBuild = false;
	
        //This holds a reference to the current resource the unit is gathering from
        this.currentResource = null;
    
        // this marks the building the engineer is creating ie lab or factory
        this.whichUnitAmIBuilding = "";

        this.timeToBuild = 120000;

        this.rotation_info = {rotation: 0, rotation_direction: ""};

        this.readyToDepleteResource = false;

        this.update = function(updateObj){
            /*
            if(this.isAI){
                console.log('inside the update method');
                console.log(this);
                console.log(updateObj);
            }*/


            //console.log("in collector update. curr state is: ", this.state);

        ///////// Destination Update //////////////////

        if (updateObj.hasOwnProperty('destPos')) {
            this.destPos.x = updateObj.destPos.x;
            this.destPos.y = updateObj.destPos.y;
        }

        ///////// Makes adjustments for collisions//////////////////
        if(updateObj.hasOwnProperty('colPos')) {
            this.currPos.x = updateObj.colPos.x;
            this.currPos.y = updateObj.colPos.y;
        }

        ///// if state is enroute then make next move //////
        if (this.state != 'idle') {
            this.makeNextMove();
        }


        ////////// UPDATE HEALTH INFORMATION //////////////
    
            
        // if object needs to take damage
        if(updateObj.hasOwnProperty('damage'))
            this._takeDamage(updateObj.damage);
    
        if(this.health <= 0) {
            this.killed = true;
        }
    
      ////////// UPDATE STATUS INFORMATION //////////////
    
        // update engineer's status flag
        if(updateObj.hasOwnProperty('state')){
            this.state = updateObj.state;
        }


    
  
        ////////// UPDATE SELECTED INFORMATION //////////////
        
        // if object is selected by user                       
            if (updateObj.hasOwnProperty('selected'))
            {          
                this.selected = updateObj.selected;
            }



            /////////////// UPDATE RESOURCE ///////////////////////////

            if(updateObj.hasOwnProperty('resource'))
            {
                this.currentResource = updateObj.resource;
                if(this.currentResource != null) {
                    this.destPos.x = this.currentResource.currPos.x;
                    this.destPos.y = this.currentResource.currPos.y;
                    //console.log("in Update Resource, the current Resource coords are: ", this.currentResource.currPos.x, this.currentResource.currPos.y);
                }
            }

            ///// UPDATE STATE BASED ON STATE CONDITIONS /////

            this.updateState(this.state);


        };
        
        this.retrieveUnitInfo = function() {
            var unitInfo = {};
            unitInfo.spriteInfo = {spriteSheet: this.spriteInfo.spriteSheet, imgName:this.spriteInfo.imgName};
            unitInfo.isAI = this.isAI;
            unitInfo.currPos = this.currPos;
            unitInfo.destPos = this.destPos;
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
        



        this.updateState = function(state) {
            //console.log("Am I AI: ", this.isAI);
            //console.log("My state:", this.state);
            var now;
            switch(state) {
                case 'idle':

                    if(this.currentResource!=null)
                    {
                        this.destPos.x = this.currentResource.currPos.x;
                        this.destPos.y = this.currentResource.currPos.y;
                        this.state = 'enRoute';
                        break;
                    }
                    //check if unit is at homeBase
                    if (this.atHome()) {
                        break;
                        //if not at homeBase than travel there
                    } else {
                        if (this.isAI) {
                            this.destPos.x = this.homeBase.x;
                            this.destPos.y = this.homeBase.y;
                            this.state = 'enroute';
                            break;
                        }
                    }
                    break;
                //Unit has a target resource and is moving to the location
                case 'enroute':
                    //check if being attacked
                    if(this.isAI) {
                        if (this.beingAttacked) {
                            this.state = 'flee';
                            break;
                        }
                    }
                    if (this.currentResource != null) {
                        if (this.destPos.x != this.currentResource.currPos.x || this.destPos.y != this.currentResource.currPos.y) {
                            this.destPos.x = this.currentResource.currPos.x;
                            this.destPos.y =  this.currentResource.currPos.y;
                            break;
                        }
                    }

                    if (this.currentResource != null) {
                        //if (this.currPos.x == this.currentResource.x && this.currPos.y == this.currentResource.y)
                          if(this.atResource()) {
                              this.state = "gathering";
                              //console.log('being put into the gathering state');
                              break;
                          }
                    }

                    if(this.isAI){
                        if(this.currentResource == null){
                            this.state = 'idle';
                            break;
                        }
                    }
                    break;
                case 'delivering':
                    if (!this.atHome()) {
                        //this.state = 'enroute';
                        this.destPos.x = this.homeBase.x;
                        this.destPos.y = this.homeBase.y;
                        break;
                    } else {
                        this.state = 'enroute';
                        if (this.currentResource != null) {
                            this.destPos.x = this.currentResource.currPos.x;
                            this.destPos.y = this.currentResource.currPos.y;
                        } else {
                            this.state ='idle';
                        }
                    }
                    break;
                case 'gathering':
                    //console.log("gathering!!!");
                    if(this.startTime == 0){
                        this.startTime = performance.now();
                        break;
                    }
                    if(this.startTime > 0){
                        now = performance.now();
                        if (now - this.startTime >= 10000) {
                            //console.log("TIME'S UP");
                            this.currentResource.resource_amount -= this.payloadLimit;
                            this.payload = this.payloadLimit;
                            //this.currentResource = null;
                            this.destPos.x = this.homeBase.x;
                            this.destPos.y = this.homeBase.y;
                            this.state = 'delivering';                             
                            this.startTime = 0;
                            if(this.currentResource.resource_amount <= 0)
                            {
                                this.currentResource = null;
                            }
                            break;
                        }
               
                    }
                    break;
                //put in the conditions to transfer to delivering
                case 'flee':
                    if (this.atHome()) {
                        this.state = 'idle';
                        this.beingAttacked = false;
                        break;
                    }
                    if (this.destPos.x != this.homeBase.x || this.destPos.y != this.homeBase.y){
                        this.currPos.x = this.homeBase.x;
                        this.currPos.y = this.homeBase.y;
                        break;
                    }
                    break;


                default:
                    console.log('none of the cases were called');
                    this.state = 'idle';
                    break;
            }
        };

        this.makeNextMove = function() {

            if(this.currPos.x < this.destPos.x){
                this.currPos.x +=1;
            } else if (this.currPos.x > this.destPos.x) {
                this.currPos.x -= 1;
            }

            if (this.currPos.y < this.destPos.y){
                this.currPos.y += 1;
            } else if (this.currPos.y > this.destPos.y) {
                this.currPos.y -= 1;
            }

            var coords = {x:this.currPos.x, y:this.currPos.y};
        };

        this.atResource = function(){


            if(this.currentResource != null){


                if(this.currPos.x >= (this.currentResource.currPos.x - 10) || this.currPos.x <= (this.currentResource.currPos.x + 10) && this.currPos.y >= (this.currentResource.currPos.y - 10) || this.currPos.y <= (this.currentResource.currPos.y + 10) );
                    return true;

            }

            return false;


        };


        this.atHome = function(){


            if(this.homeBase != null){


                if(this.currPos.x == this.homeBase.x && this.currPos.y == this.homeBase.y )
                    return true;

            }

            return false;


        }



    }
}
