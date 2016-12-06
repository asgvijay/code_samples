class Clan2_Factory1 extends BuildingClass{


    constructor(xPos, yPos)
    {
        super(xPos, yPos);
        this.health = 1000;
        this.unitType = 'factory';
        this.isAI = true;
        this.health = 1000;
        this.type = "Clan2_Factory1";
        this.UnitsICreate = "Supermutant";
        this.size.x= 50;
        this.size.y= 50;
        this.costToBuild = 250;
        this.unitCostToBuild = 90;
        this.buildTime = 30000; // milliseconds
        this.spriteInfo.spriteSheet = "rbp.json";
        this.spriteInfo.imgName = "Clan2_Factory1.png";
    }

}