class Clan1_Vehicle2 extends Anim_FighterClass{


    constructor(xPos, yPos)
    {

        super(xPos, yPos);
	    this.unitType = 'vehicle';
        this.dpi = 35;
        this.health = 150;
        this.maxHealth = 150;
        this.type = "Warbus";
        this.costToBuild = 100;
        this.size.x= 40;
        this.size.y= 62;
        this.spriteInfo.spriteSheet = "ships.json";
        this.spriteInfo.imgName = "Clan1_Vehicle2.png";
        this.unit_projectile = "WBBullet";
        //This is to add the unit to the grid when the unit is initialized
    }
    
}