class Clan2_Training1 extends BuildingClass{


    constructor(xPos, yPos)
    {
        super(xPos, yPos);
        this.health = 1000;
        this.maxHealth = 1000;
        this.unitType = 'training';
        this.isAI = true;
        this.type = "Clan2_Training1";
        this.UnitsICreate = "Mutantfighter1";
        this.size.x= 50;
        this.size.y= 54;
        this.costToBuild = 300;
        this.unitCostToBuild = 40;
        this.buildTime = 10000; // milliseconds
        this.spriteInfo.spriteSheet = "rbp.json";
        this.spriteInfo.imgName = "Clan2_Training.png";
    }

}