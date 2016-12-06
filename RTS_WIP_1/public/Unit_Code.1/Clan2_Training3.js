class Clan2_Training3 extends BuildingClass{


    constructor(xPos, yPos)
    {
        super(xPos, yPos);
        this.health = 1000;
        this.unitType = 'training';
        this.isAI = true;
        this.maxHealth = 1000;
        this.type = "Clan2_Training3";
        this.UnitsICreate = "Mutantfighter3";
        this.size.x= 60;
        this.size.y= 81;
        this.costToBuild = 300;
        this.buildTime = 20000; // milliseconds
        this.spriteInfo.spriteSheet = "rbp.json";
        this.spriteInfo.imgName = "Clan2_Training.png";
    }

}