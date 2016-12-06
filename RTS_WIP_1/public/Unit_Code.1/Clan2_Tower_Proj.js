class Clan2_Tower_Proj extends ProjectileClass {

    constructor(startCoord, endCoord) {
        super(startCoord, endCoord);
        this.damage_infliction = 6; // was 30
        this.type = "Clan1_TowerBullet";
        this.size.x = 2;
        this.size.y = 16;
        this.isAI = true;
        this.spriteInfo.imgName = "Clan2_Projectile2.png";
        this.spriteInfo.spriteSheet = "rbp.json";
        this.update = function (updateObj) {

            if (this.currPos.x == this.destPos.x && this.currPos.y == this.destPos.y)
                this.killed = true;

            // move projectile to next cell
            if (this.currPos.x != this.destPos.x || this.currPos.y != this.destPos.y) {
                this.currPos.x = this.path[this.path_index].x;
                this.currPos.y = this.path[this.path_index].y;
                this.path_index++;
            }
        }
    }
}