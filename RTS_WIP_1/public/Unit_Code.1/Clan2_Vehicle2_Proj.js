class Clan2_Vehicle2_Proj extends ProjectileClass {

    constructor(startCoord, endCoord) {
        super(startCoord, endCoord);
        this.damage_infliction = 8; // was 40
        this.size.x = 2;
        this.size.y = 16;
        this.type = "MGBullet";
        this.spriteInfo.imgName = "Clan2_Projectile2.png";
        this.spriteInfo.spriteSheet = "rbp.json";
        this.isAI = true;
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