class Clan2_Factory3 extends BuildingClass{


    constructor(xPos, yPos)
    {
        super(xPos, yPos);
        this.health = 1000;
        this.unitType = 'factory';
        this.maxHealth = 1000;
        this.isAI = true;
        this.type = "Clan2_Factory3";
        this.UnitsICreate = "monsters";
        this.size.x= 75;
        this.size.y= 75;
        this.costToBuild = 500;
        this.buildTime = 60000; // milliseconds
        this.spriteInfo.spriteSheet = "rbp.json";
        this.spriteInfo.imgName = "Clan2_Factory3.png";
    }

}