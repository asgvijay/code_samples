class Clan2_Vehicle3 extends Anim_FighterClass{


    constructor(xPos, yPos)
    {

        super(xPos, yPos);
        this.health = 50;
        this.dpi = 5;
		this.unitType = 'vehicle';
        this.maxHealth = 50;
        this.type = "Monster";
        this.size.x= 50;
        this.size.y= 48;
        this.isAI = true;
        this.spriteInfo.spriteSheet = "ships.json";
        this.spriteInfo.imgName = "Clan2_Vehicle2.png";
        this.unit_projectile = "MBullet";
    }
    
}