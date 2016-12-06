class Clan2_Vehicle2 extends Anim_FighterClass{


    constructor(xPos, yPos)
    {

        super(xPos, yPos);
        this.health = 50;
        this.dpi = 40;
        this.isAI = true;
		this.unitType = 'vehicle';
        this.maxHealth = 50;
        this.type = "Mutantgiant";
        this.size.x= 50;
        this.size.y= 50;
        this.spriteInfo.spriteSheet = "ships.json";
        this.spriteInfo.imgName = "Clan2_Vehicle2.png";
        this.unit_projectile = "MGBullet";
    }
    
}