class Clan1_Vehicle3 extends Anim_FighterClass{


    constructor(xPos, yPos)
    {

        super(xPos, yPos);
		this.unitType = 'vehicle';
        this.dpi = 50;
        this.health = 250;
        this.maxHealth = 250;
        this.type = "Semitruck";
        this.size.x= 50;
        this.size.y= 48;
        this.costToBuild = 200;
        this.spriteInfo.spriteSheet = "ships.json";
        this.spriteInfo.imgName = "Clan1_Vehicle3.png";
        this.unit_projectile = "STBullet";
        //This is to add the unit to the grid when the unit is initialized
    }
    
}