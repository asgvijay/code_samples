class Clan1_MissileTower extends Tower{

    constructor(xPos, yPos)
    {
        super(xPos, yPos);
        this.health = 500;
        this.maxHealth = 500;
        this.type = "Clan1_MissileTower";
        this.size.x= 40;
        this.size.y= 73;
        this.costToBuild = 250;
        this.spriteInfo.spriteSheet = "rbp.json";
        this.spriteInfo.imgName = "Clan1_MissileTower.png";
        this.unit_projectile = "Clan1_Projectile3";
        this.state = 'idle';
    }
}