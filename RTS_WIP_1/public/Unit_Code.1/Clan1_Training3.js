class Clan1_Training3 extends BuildingClass{


    constructor(xPos, yPos)
    {
        super(xPos, yPos);
        this.health = 1000;
        this.unitType = 'training';
        this.maxHealth = 1000;
        this.type = "Clan1_Training3";
        this.UnitsICreate = "Fighter3";
        this.size.x= 60;
        this.size.y= 81;
        this.costToBuild = 300;
        this.buildTime = 20000; // milliseconds
        this.spriteInfo.spriteSheet = "rbp.json";
        this.spriteInfo.imgName = "Clan1_Training.png";
    }

}
