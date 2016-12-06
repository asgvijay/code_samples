class Clan1_Fighter1 extends Anim_FighterClass{


    constructor(xPos, yPos)
    {

        super(xPos, yPos);
        this.health = 50;
        this.dpi = 10;
		this.unitType = 'fighter'; //For AI to track what type of unit
        this.maxHealth = 50;
        this.type = "Fighter1";
        this.size.x= 40;
        this.size.y= 48;
        this.costToBuild = 40;
        this.spriteInfo.spriteSheet = "ships.json";
        this.spriteInfo.imgName = "Clan1_Fighter1.png";
        this.unit_projectile = "Fighter1Bullet";
        this.state = 'idle';
        this.assignedEnemy = null;
        //This is to add the unit to the grid when the unit is initialized
    }
    
}
