class Anim_FighterClass extends EntityClass{

    constructor(xCoord, yCoord) {

        super(xCoord, yCoord);

        //this.imgMovement = {
        //  imgAnimateIndex: 0,
        //spriteLibLength: 0,
        //direction: ""
        //};

        this.unit_projectile = "";

        this.inRange = false;

        this.costToBuild = 0;

        this.assignedEnemy = null;

        this.onAttack = false;

        this.nearbyEnemy = null;

        this.projectileReady = false;

        this.projectileTime = 0;

        this.projectileCreateInterval = 333;

        this.state = "idle";

        this.enemies = [];


        this.rotation_info = {rotation: 0, rotation_direction: ""};

        //this.update = this.update;

        this.update = function (updateObj) {
            if (!this.isAI){
                if(this.state == 'enroute'){
                    //console.log(this);
                }

            }

            ///////// UPDATE HEALTH INFORMATION ///////////////

            // if object needs to take damage
            if (updateObj.hasOwnProperty('damage')) {
                console.log('the unit is taking damage');
                console.log(updateObj.damage);
                this._takeDamage(updateObj.damage);
            }

            if (this.health <= 0) {
                this.killed = true;
            }


            ///////// UPDATE STATE INFORMATION ///////////////


            if (updateObj.hasOwnProperty('state')) {
                if (updateObj.state == 'enroute') {
                    this.assignedEnemy = null;
                }
                this.state = updateObj.state;
                //console.log(this.state);
            }


            ///////// SET ENEMY UNIT //////////////////

            if (updateObj.hasOwnProperty('enemy')) {
                this.assignedEnemy = updateObj.enemy;

                console.log("the assigned enemy is: ", this.assignedEnemy);

            }

            /////Manually Resets the Projectile ready and timer /////////
            ////Mainly for when the unit is attacking but the user tells it to move to somewhere else
            if (updateObj.hasOwnProperty('projectileReady')) {
                this.projectileReady = false;
                this.projectileTime = 0;
            }

            ///////// updates destination coordinates //////////////////

            if (updateObj.hasOwnProperty('destPos')) {
                this.destPos.x = updateObj.destPos.x;
                this.destPos.y = updateObj.destPos.y;
            }


            ///////// Makes adjustments for collisions//////////////////
            if(updateObj.hasOwnProperty('colPos')) {
                this.currPos.x = updateObj.colPos.x;
                this.currPos.y = updateObj.colPos.y;
            }

            //////// if state is enroute then makeNextmove ////////
            if (this.state == 'enroute' || this.state == 'onAttack') {
                this.makeNextMove();
            }


            ///////// update array of enemies ///////////////

            if(updateObj.hasOwnProperty('enemyArray'))
            {

                this.enemies = updateObj.enemyArray;


            }

            //////////// CALL THE UPDATE STATE METHOD TO LOOK FOR TRANSITION CONDITIONS /////////////
            this.updateState(this.state);



            ///////// UPDATE SELECTED STATE ///////////////
            //console.log(updateObj.selected);
            if (updateObj.hasOwnProperty('selected'))
            {          
                this.selected = updateObj.selected;
            }
            //else
            //    this.selected = false;


        };



        this.retrieveUnitInfo = function () {
            var unitInfo = {};
            unitInfo.spriteInfo = {spriteSheet: this.spriteInfo.spriteSheet, imgName: this.spriteInfo.imgName};
            unitInfo.isAI = this.isAI;
            unitInfo.currPos = this.currPos;
            unitInfo.destPos = this.destPos;
            unitInfo.size = {x: this.size.x, y: this.size.y};
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


        this.updateState = function (state) {
            var now;
            switch (state) {
                case 'idle':
                    //check if there is a nearby enemy
                    if(this.enemies.length >0)
                    {
                        //console.log("in enemies>0");
                        for(var i =0 ;i <this.enemies.length; i++)
                        {
                            //console.log("in for loop");
                            if(enemyRange(this, this.enemies[i]))
                            {
                                //console.log("IN ENEMY CONDITION");
                                this.assignedEnemy = this.enemies[i];
                                this.inRange = true;
                                this.state = 'onAttack';
                            }

                            else
                                this.inRange = false;
                        }
                    }

                    else
                    {
                        this.assignedEnemy = null;
                    }

                    break;
                //moving means unit will not actively attack enemy units, but will defend if attacked
                case 'enroute':
                    //check if being attacked
                    /*
                    if (this.beingAttacked)
                    {
                        this.assignedEnemy = this.getNearestEnemy();
                        this.state = 'onAttack';
                        break;
                    }
*/
                    if(this.enemies.length >0)
                    {
                            //console.log("in enemies>0");
                            for(var i =0 ;i <this.enemies.length; i++)
                            {
                                //console.log("in for loop");
                                if(enemyRange(this, this.enemies[i]))
                                {
                                    //console.log("IN ENEMY CONDITION");
                                    this.assignedEnemy = this.enemies[i];
                                    this.inRange = true;
                                    this.state = 'onAttack';
                                }

                                else
                                    this.inRange = false;
                            }
                    }

                    if (this.destPos.x == this.currPos.x && this.destPos.y == this.currPos.y) {
                        this.state = 'idle';
                        this.assignedEnemy = null;
                        break;
                    }
                    break;

                /*
                //means unit will actively seek to attack enemy units while moving
                case 'patrol':
                    //check if enemies are nearby
                    this.nearbyEnemy = this.getNearestEnemy();
                    if (this.nearbyEnemy != null) {
                        this.assignedEnemy = this.nearbyEnemy;
                        this.state = 'attack';
                        break;
                    }
                    break;

                    */
                //unit will not attack enemy units and will not defend, they will merely attempt to retreat to homeBase
                case 'flee':
                    if (this.currPos.x == this.homeBase.x + 10 || this.currPos.x == this.homeBase.x - 10
                        && this.currPos.y == this.homeBase.y + 10 || this.currPos.y == this.homeBase.y) {
                        this.state = 'idle';
                        this.assignedEnemy = null;
                        break;
                    } else if (this.destPos.x != this.homeBase.x || this.destPos.y != this.homeBase.y) {
                        this.destPos.x = this.homeBase.x;
                        this.destPos.y = this.homeBase.y;
                        break;
                    }
                    break;

                case 'onAttack':
                    if (this.assignedEnemy != null)
                    {
                        if (this.assignedEnemy.killed) {
                            this.assignedEnemy = null;
                            this.state = 'idle';
                            this.inRange = false;
                            break;
                        }

                        if (enemyRange(this, this.assignedEnemy)) {
                            this.inRange = true;
                            this.destPos.x = this.currPos.x;
                            this.destPos.y = this.currPos.y;
                        } else {
                            this.destPos.x = this.assignedEnemy.currPos.x;
                            this.destPos.y = this.assignedEnemy.currPos.y;
                            break;
                        }
                        // Timing functionality for projectile creation
                        // need to ensure fighter is inrange = true
                        if (this.inRange) {
                            if (this.projectileTime == 0) {
                                this.projectileTime = performance.now();
                            }
                            now = performance.now();
                            if ((now - this.projectileTime) >= this.projectileCreateInterval) {
                                this.projectileReady = true;
                                this.projectileTime = 0;
                            }
                        }
                    }
                    break;
                default:
                    console.log('not statements selected');

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

    };
}