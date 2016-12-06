class Clan1_Fighter1_Proj extends ProjectileClass {


    constructor(startCoord, endCoord) {
        super(startCoord, endCoord);
        //console.log("startCoord is: ", startCoord);
        //console.log("endCoord is: ", endCoord);

        this.damage_infliction = 10; // was 10
        this.size.x = 5;
        this.size.y = 5;
        this.type = "Fighter1Bullet";
        this.spriteInfo.imgName = "Clan1_Projectile1.png";
        this.spriteInfo.spriteSheet = "rbp.json";
        this.update = function (updateObj) {

            if (this.currPos.x == this.destPos.x && this.currPos.y == this.destPos.y)
                this.killed = true;

            // move projectile to next cell
            if (this.currPos.x != this.destPos.x || this.currPos.y != this.destPos.y) {
                console.log(this.currPos);
                console.log(this.path[this.path_index]);
                this.currPos.x = this.path[this.path_index].x;
                this.currPos.y = this.path[this.path_index].y;
                this.path_index++;
            }
        }
    }
}