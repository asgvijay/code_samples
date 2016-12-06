class EntityClass {

    constructor(xCoord, yCoord) {


        // sprite info
        this.spriteInfo  = {spriteSheet: "", imgName:""};
        // current position of object on map
        this.currPos = {x: Math.round(xCoord), y: Math.round(yCoord)};
        this.homeBase = {x: Math.round(xCoord), y: Math.round(yCoord)};

        // size of object
        this.size = {h: 0, w:0};

        // cost to build unit
        this.costToBuild = 0;

        // desitination position
        this.destPos = {type: "", x: xCoord, y: yCoord};

        // variable to flag whether object is selected or not
        this.selected = false;

        //Indicates if a unit is in a group
        this.isGrouped = false;

        // variable to measure objects health
        this.health = 0;
        this.maxHealth = 0;
        // variable to identify type of object
        this.type = "";

        // variable to identify current state of unit (attacking, patrol, collecting, idle, etc)
        this.state = "idle";

        this.isAI = false;

        this.killed = false;

        this.beingAttacked = false;


        

        // function to take damage (if necessary)
        this._takeDamage = function (amount_of_damage) {
            //I'm not sure this logic is correct
            this.health -= amount_of_damage;
            console.log('the take damage function is being called');
            this.beingAttacked = true;
        };



        // function to update the object each tick. This function will be overloaded by the actual entity
        this.update = function () {};

        this.lowHealth = function() {
            return this.health < (this.maxHealth / 2);
        };


        this._atHomeBase = function () {
            if(this.homeBase != null){
                if(this.currPos.x == this.homeBase.x && this.currPos.y == this.homeBase.y )
                    return true;

            }
            return false;
        };

		// overloaded in anim_collector and anim_fighter
		this.retrieveUnitInfo = function() {};

    }
}
