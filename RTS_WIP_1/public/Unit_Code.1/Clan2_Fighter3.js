class Clan2_Fighter3 extends Anim_FighterClass{


    constructor(xPos, yPos)
    {

        super(xPos, yPos);
        this.health = 50;
        this.dpi = 30;
        this.isAI = true;
		this.unitType = 'fighter'; //For AI to track what type of unit
        this.maxHealth = 50;
        this.type = "Mutantfighter3";
        this.size.x= 40;
        this.size.y= 41;
        this.spriteInfo.spriteSheet = "ships.json";
        this.spriteInfo.imgName = "Clan2_Fighter3.png";
        this.unit_projectile = "MF3Bullet";
        //This is to add the unit to the grid when the unit is initialized
    }
    
}