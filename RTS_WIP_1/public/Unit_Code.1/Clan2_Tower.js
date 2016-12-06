class Clan2_Tower extends Tower{


    constructor(xPos, yPos)
    {
        super(xPos, yPos);
        this.health = 300;
        this.maxHealth = 300;
        this.isAI = true;
        this.unitType = "tower";
        this.type = "Clan2_Tower";
        this.size.x= 10;
        this.size.y= 26;
        this.costToBuild = 150;
        this.spriteInfo.spriteSheet = "rbp.json";
        this.spriteInfo.imgName = "Clan2_Tower.png";
        this.unit_projectile = "Clan2_TowerBullet";
        this.state = 'idle';
    }

}