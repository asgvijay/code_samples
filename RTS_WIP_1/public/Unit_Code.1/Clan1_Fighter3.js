class Clan1_Fighter3 extends Anim_FighterClass{


    constructor(xPos, yPos)
    {

        super(xPos, yPos);
        this.health = 90;
        this.dpi = 20;
		this.unitType = 'fighter'; //For AI to track what type of unit
        this.maxHealth = 90;
        this.type = "Fighter3";
        this.costToBuild = 85;
        this.size.x= 40;
        this.size.y= 51;
        this.spriteInfo.spriteSheet = "ships.json";
        this.spriteInfo.imgName = "Clan1_Fighter3.png";
        this.unit_projectile = "Fighter3Bullet.png";
        //This is to add the unit to the grid when the unit is initialized
    }
    
}
