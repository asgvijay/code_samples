class Clan1_Vehicle2_Proj extends ProjectileClass {

    constructor(startCoord, endCoord) {
        super(startCoord, endCoord);
        this.damage_infliction = 7; // was 35
        this.size.x = 7;
        this.size.y = 7;
        this.type = "WBBullet";
        this.spriteInfo.imgName = "Clan1_Projectile2.png";
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