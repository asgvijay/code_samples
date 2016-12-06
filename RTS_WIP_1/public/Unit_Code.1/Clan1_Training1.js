class Clan1_Training1 extends BuildingClass{


    constructor(xPos, yPos)
    {
        super(xPos, yPos);
        this.health = 1000;
        this.unitType = 'training';
        this.unitType = 'factory';
        this.maxHealth = 1000;
        this.type = "Clan1_Training1";
        this.UnitsICreate = "Fighter1";
        this.size.x= 60;
        this.size.y= 81;
        this.costToBuild = 300;
        this.buildTime = 12000; // milliseconds
        this.spriteInfo.spriteSheet = "rbp.json";
        this.spriteInfo.imgName = "Clan1_Training.png";
    }

}
