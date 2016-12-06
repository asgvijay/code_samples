class Clan1_Lab extends BuildingClass{


    constructor(xPos, yPos)
    {
        super(xPos, yPos);
        this.health = 2000;
        this.maxHealth = 2000;
        this.type = "Clan1_Lab";
        this.unitType = 'lab';
        this.UnitsICreate = "engineer";
        this.costToBuild = 750;
        this.size.x= 75;
        this.size.y= 65;
        this.buildTime = 15000; // milliseconds
        this.spriteInfo.spriteSheet = "rbp.json";
        this.spriteInfo.imgName = "Clan1_Lab.png";
    }

}