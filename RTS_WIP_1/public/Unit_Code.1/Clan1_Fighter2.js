class Clan1_Fighter2 extends Anim_FighterClass{


    constructor(xPos, yPos)
    {

        super(xPos, yPos);
        this.health = 75;
        this.dpi = 14;
		this.unitType = 'fighter'; //For AI to track what type of unit
        this.maxHealth = 75;
        this.type = "Fighter2";
        this.costToBuild = 60;
        this.size.x= 40;
        this.size.y= 31;
        this.spriteInfo.spriteSheet = "ships.json";
        this.spriteInfo.imgName = "Clan1_Fighter2.png";
        this.unit_projectile = "Fighter2Bullet";
    }
    
}