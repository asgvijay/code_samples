class ResourceClass {

    constructor(xCoord, yCoord) {


        // sprite info
        this.spriteInfo  = {spriteSheet: "", imgName:""};
        // current position of object on map
        this.currPos = {x: xCoord, y: yCoord};

        // size of object
        this.size = {x: 0, y:0};

        // variable to flag whether object is selected or not
        this.selected = false;

        // variable to measure objects health
        this.resource_amount = 0;


        // variable to identify type of object
        this.type = "";

        this.all_gone = false;

        // array of collectors currently depleting resource amount
        this.collectors = [];

        // function to update the object each tick. This function will be overloaded by the actual entity
        this.update = function () {};
        
           this.retrieveUnitInfo = function() {
						var unitInfo = {};
						unitInfo.spriteInfo = {spriteSheet: this.spriteInfo.spriteSheet, imgName:this.spriteInfo.imgName};
						unitInfo.isAI = this.isAI;
						unitInfo.currPos = this.currPos;
						unitInfo.size = {x:this.size.x, y:this.size.y};    
						unitInfo.selected = this.selected;
						unitInfo.state = this.state;
						unitInfo.type = this.type;
                        unitInfo.resourceAmount = this.resource_amount;
            
						//unitInfo.inRange = this.enemyRange();
						return unitInfo;        
        };


    }
}
