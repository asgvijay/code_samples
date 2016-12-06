class ProjectileClass {

    constructor(startCoord, endCoord) {


        // sprite info
        this.spriteInfo  = {spriteSheet: "", imgName:""};
        // current position of object on map
        this.currPos = {x: startCoord.x, y: startCoord.y};

        // size of object
        this.size = {x: 0, y:0};

        // desitination position
        this.destPos = {type: "", x: endCoord.x, y: endCoord.y};

        // variable to identify type of object
        this.type = "";

        //this.isAI = false;

        this.killed = false;

        this.damage_infliction = 0;

        // this function determines the coordinate path for the projectile
        this.path = projectilePath(this.currPos, this.destPos);

        this.path_length = this.path.length;

        this.path_index = 0;

        // function to update the object each tick. This function will be overloaded by the actual entity
        this.update = function () {};

    }
}
