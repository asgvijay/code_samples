class Clan2_Vehicle1 extends Anim_FighterClass{


    constructor(xPos, yPos)
    {

        super(xPos, yPos);
        this.health = 50;
        this.dpi = 40;
        this.isAI = true;
		this.unitType = 'vehicle';
        this.maxHealth = 50;
        this.type = "Supermutant";
        this.size.x= 50;
        this.size.y= 32;
        this.costToBuild = 90;
        this.spriteInfo.spriteSheet = "ships.json";
        this.spriteInfo.imgName = "Clan2_Vehicle1.png";
        this.unit_projectile = "SMBullet";
    }
    
}