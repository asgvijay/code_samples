class Clan2_Fighter2 extends Anim_FighterClass{


    constructor(xPos, yPos)
    {

        super(xPos, yPos);
        this.health = 50;
        this.dpi = 20;
        this.isAI = true;
		this.unitType = 'fighter'; //For AI to track what type of unit
        this.maxHealth = 50;
        this.type = "Mutantfighter2";
        this.size.x= 50;
        this.size.y= 27;
        this.spriteInfo.spriteSheet = "ships.json";
        this.spriteInfo.imgName = "Clan2_Fighter2.png";
        this.unit_projectile = "MF2Bullet";
        //This is to add the unit to the grid when the unit is initialized
}
    
}