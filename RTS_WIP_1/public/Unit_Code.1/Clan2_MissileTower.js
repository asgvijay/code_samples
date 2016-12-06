class Clan2_MissileTower extends Tower{

    constructor(xPos, yPos)
    {
        super(xPos, yPos);
        this.health = 500;
        this.maxHealth = 500;
        this.type = "Clan2_MissileTower";
        this.isAI = true;
        this.size.x= 30;
        this.size.y= 49;
        this.costToBuild = 250;
        this.spriteInfo.spriteSheet = "rbp.json";
        this.spriteInfo.imgName = "Clan2_MissileTower.png";
        this.unit_projectile = "Clan2_MissileTowerBullet";
    }
}

