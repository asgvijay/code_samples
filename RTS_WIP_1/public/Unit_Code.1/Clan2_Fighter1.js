class Clan2_Fighter1 extends Anim_FighterClass{


    constructor(xPos, yPos)
    {

        super(xPos, yPos);
        this.health = 50;
        this.dpi = 10;
        this.isAI = true;
		this.unitType = 'fighter'; //For AI to track what type of unit
        this.maxHealth = 50;
        this.type = "Mutantfighter1";
        this.size.x= 40;
        this.size.y= 25;
        this.costToBuild = 40;
        this.spriteInfo.spriteSheet = "ships.json";
        this.spriteInfo.imgName = "Clan2_Fighter1.png";
        this.unit_projectile = "MF1Bullet";
        this.state = 'idle';
    }
    
}