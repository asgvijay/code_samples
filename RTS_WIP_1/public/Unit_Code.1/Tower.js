class Tower extends EntityClass{

    constructor(xCoord, yCoord){

        super(xCoord, yCoord);

        //this.imgMovement = {
        //  imgAnimateIndex: 0,
        //spriteLibLength: 0,
        //direction: ""
        //};

        this.unit_projectile =  "";

        this.enemyCoords= {x: 0, y: 0};

        this.inRange= false;

        this.assignedEnemy= {};

        this.enemies= [];

        this.onAttack= true;

        this.nearbyEnemy= {};

        this.rotation= 0;

        this.type = "";

        this.projectileReady = false;

        this.projectileTime = 0;

        this.projectileCreateInterval = 333;

        this.update =  function(updateObj){


            ///////// UPDATE HEALTH INFORMATION ///////////////
            if(updateObj != null) {
                // if object needs to take damage
                if (updateObj.hasOwnProperty('damage'))
                    this._takeDamage(updateObj.damage);

                if (this.health <= 0) {
                    this.killed = true;
                }
                ///////// SET ENEMY UNIT //////////////////

                if (updateObj.hasOwnProperty('enemy'))
                    this.assignedEnemy = updateObj.enemy;


                //////////// CALL THE UPDATE STATE METHOD TO LOOK FOR TRANSITION CONDITIONS /////////////



                ///////// ADD ATTACKING UNITS //////////////////
                if(updateObj.hasOwnProperty('enemyArray'))
                {
                    this.enemies = updateObj.enemyArray;
                    //console.log("in Tower enemies update. Enemies is: ", this.enemies);

                }


                ///////// UPDATE ROTATION ///////////////


                ///////// UPDATE SELECTED STATE ///////////////

                if (updateObj.hasOwnProperty('selected'))
                    this.selected = true;
            }

            this.updateState(this.state);

        };

        this.updateState = function(state) {
            switch (state) {
                case 'onAttack':

                    //console.log ("This is the state in onAttack: ", this.state);
                    //console.log("This assigned enemy is: ", this.assignedEnemy);
                    if (this.assignedEnemy == 'undefined') {
                        this.state = 'idle';
                        this.inRange = false;
                        break;
                    }
                    if (this.assignedEnemy.killed){
                        this.assignedEnemy = null;
                        this.state = 'idle';
                        this.inRange = false;
                        break;
                    }

                    if(enemyRange(this, this.assignedEnemy)) {
                        // Timing functionality for projectile creation
                        if (this.projectileTime == 0) {
                            this.projectileTime = performance.now();
                            break;
                        }
                        if ((performance.now() - this.projectileTime   ) >= this.projectileCreateInterval) {
                            this.projectileReady = true;
                            this.projectileTime = 0;
                            break;
                        }


                    }

                    else
                        this.inRange = false;


                    break;


                case 'idle':
                    //console.log("in Idle Switch for Tower");
                    //this.nearbyEnemy = this.getNearestEnemy();
                    //console.log("getNearestEnemy returned: ", this.nearbyEnemy);
                    //console.log("this is the towers state:", this.state);
                    if(this.enemies.length >0)
                    {
                        console.log("in enemies>0");
                        for(var i =0 ;i <this.enemies.length; i++)
                        {
                            console.log("in for loop");
                            if(enemyRange(this, this.enemies[i]))
                            {
                                console.log("IN ENEMY CONDITION");
                                this.assignedEnemy = this.enemies[i];
                                this.inRange = true;
                                this.state = 'onAttack';
                                break;
                            }



                        }

                        this.enemies = [];
                    }
                    break;

                    //if (this.nearbyEnemy != null) {
                      //  this.assignedEnemy = this.nearbyEnemy;
                       // this.nearbyEnemy = null;
                        //this.state = 'onAttack';
                        //break;
                    //} else {
                      //  this.beingAttacked = false;
                        //break;
                    //}
                   // break;
                default:
                    console.log('no states were passed in');
            }

        };
    }
}

