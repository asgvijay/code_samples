class Clan2_Lab extends BuildingClass{


    constructor(xPos, yPos)
    {
        super(xPos, yPos);
        this.health = 2000;
        this.health = 2000;
        this.type = "Clan2_Lab";
        this.unitType = 'lab';
        this.isAI = true;
        this.UnitsICreate = "MutantHuman";
        this.size.x= 60;
        this.size.y= 60;
        this.costToBuild = 750;
        this.unitCostToBuild = 40;
        this.buildTime = 10000; // milliseconds
        this.spriteInfo.spriteSheet = "rbp.json";
        this.spriteInfo.imgName = "Clan2_Lab.png";
    }

}