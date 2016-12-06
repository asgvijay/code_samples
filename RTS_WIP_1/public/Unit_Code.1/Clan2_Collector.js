class Clan2_Collector extends Anim_CollectorClass{

    constructor(xPos, yPos)
    {
        super(xPos, yPos);
        this.health = 50;
        this.maxHealth = 50;
        this.type = "MutantHuman";
        this.payloadLimit = 20;
        this.isAI = true;
        this.size.x= 30;
        this.size.y= 18;
        this.costToBuild = 40;
        // enter image name here
        this.spriteInfo.spriteSheet = "ships.json";
        this.spriteInfo.imgName = "Clan2_Collector.png";
    }
        

	
}
