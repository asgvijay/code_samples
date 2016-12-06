class Clan1_Factory2 extends BuildingClass{


    constructor(xPos, yPos)
    {
        super(xPos, yPos);
        this.health = 1000;
        this.maxHealth = 1000;
        this.unitType = 'factory';
        this.type = "Clan1_factory2";
        this.UnitsICreate = "warbus";
        this.size.x= 75;
        this.size.y= 132;
        this.costToBuild = 400;
        this.buildTime = 30000; // milliseconds
        this.spriteInfo.spriteSheet = "rbp.json";
        this.spriteInfo.imgName = "Clan1_Factory2.png";
    }

}