class Clan1_Vehicle1 extends Anim_FighterClass{


    constructor(xPos, yPos)
    {

        super(xPos, yPos);
	    this.unitType = 'vehicle';
        this.dpi = 30;
        this.health = 150;
        this.maxHealth = 150;
        this.type = "Armedvehicle";
        this.size.x= 40;
        this.size.y= 44;
        this.costToBuild = 90;
        this.spriteInfo.spriteSheet = "ships.json";
        this.spriteInfo.imgName = "Clan1_Vehicle1.png";
        this.unit_projectile = "AVBullet";
        //This is to add the unit to the grid when the unit is initialized
    }

}