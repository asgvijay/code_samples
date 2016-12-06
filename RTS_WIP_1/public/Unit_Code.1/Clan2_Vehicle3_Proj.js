class Clan2_Vehicle3_Proj extends ProjectileClass {

    constructor(startCoord, endCoord) {
        super(startCoord, endCoord);
        this.damage_infliction = 10; // was 50
        this.size.x = 3;
        this.size.y = 25;
        this.type = "MBullet";
        this.spriteInfo.imgName = "Clan2_Projectile3.png";
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