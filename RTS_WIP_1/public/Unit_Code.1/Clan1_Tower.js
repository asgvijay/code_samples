class Clan1_Tower extends Tower{


    constructor(xPos, yPos)
    {
        super(xPos, yPos);
        this.health = 300;
        this.maxHealth = 300;
        this.type = "Clan1_Tower";
        this.costToBuild = 150;
        this.size.x= 20;
        this.size.y= 51;
        this.spriteInfo.spriteSheet = "rbp.json";
        this.spriteInfo.imgName = "Clan1_Tower.png";
        this.unit_projectile = "Clan1_TowerBullet";
        this.state = 'idle';
    }

}
