class Clan2_Factory2 extends BuildingClass{


    constructor(xPos, yPos)
    {
        super(xPos, yPos);
        this.health = 1000;
        this.unitType = 'factory';
        this.maxHealth = 1000;
        this.isAI = true;
        this.type = "Clan2_Factory2";
        this.UnitsICreate = "mutantgiants";
        this.size.x= 50;
        this.size.y= 50;
        this.costToBuild = 400;
        this.buildTime = 30000; // milliseconds
        this.spriteInfo.spriteSheet = "rbp.json";
        this.spriteInfo.imgName = "Clan2_Factory2.png";
    }

}