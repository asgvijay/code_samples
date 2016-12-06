class Clan1_Factory1 extends BuildingClass{


    constructor(xPos, yPos)
    {
        super(xPos, yPos);
        this.health = 1000;
        this.unitType = 'factory';
        this.maxHealth = 1000;
        this.type = "Clan1_Factory1";
        this.UnitsICreate = "armedvehicle";
        this.size.x= 60;
        this.size.y= 52;
        this.costToBuild = 250;
        this.buildTime = 25000; // milliseconds
        this.spriteInfo.spriteSheet = "rbp.json";
        this.spriteInfo.imgName = "Clan1_Factory1.png";
    }

}