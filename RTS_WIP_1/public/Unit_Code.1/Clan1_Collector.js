class Clan1_Collector extends Anim_CollectorClass{
    
    constructor(xPos, yPos)
    {
        super(xPos, yPos);
        this.health = 50;
        this.maxHealth = 50;
        this.type = "engineer";
        this.payloadLimit = 30;
        this.costToBuild = 50;
        this.size.x= 30;
        this.size.y= 16;
        // enter image name here
        this.spriteInfo.spriteSheet = "ships.json";
        this.spriteInfo.imgName = "Clan1_Collector.png";
        //This is to add the unit to the grid when the unit is initialized
    }
    
}

