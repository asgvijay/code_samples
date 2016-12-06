class Clan1_Factory3 extends BuildingClass{


    constructor(xPos, yPos)
    {
        super(xPos, yPos);
        this.health = 1000;
        this.unitType = 'factory';
        this.maxHealth = 1000;
        this.type = "Clan1_Factory3";
        this.UnitsICreate = "semitruck";
        this.size.x= 100;
        this.size.y= 50;
        this.costToBuild = 500;
        this.buildTime = 60000; // milliseconds
        this.spriteInfo.spriteSheet = "rbp.json";
        this.spriteInfo.imgName = "Clan1_Factory3.png";
    }

}