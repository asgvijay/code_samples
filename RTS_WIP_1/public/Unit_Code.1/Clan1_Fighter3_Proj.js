class Clan1_Fighter3_Proj extends ProjectileClass {

    constructor(startCoord, endCoord) {
        super(startCoord, endCoord);
        this.damage_infliction = 4; // was 20
        this.size.x = 9;
        this.size.y = 9;
        this.type = "Fighter3Bullet";
        this.spriteInfo.imgName = "Clan1_Projectile3.png";
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