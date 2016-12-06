class Clan2_Fighter1_Proj extends ProjectileClass{

    constructor(startCoord, endCoord)

    {
        super(startCoord, endCoord);
        this.damage_infliction = 2; // was 10
        this.type = "MF1Bullet";
        this.size.x = 3;
        this.size.y = 12;
        this.isAI = true;
        this.spriteInfo.imgName = "Clan2_Projectile1.png";
        this.spriteInfo.spriteSheet = "rbp.json";
        this.update =  function(updateObj){

            if(this.currPos.x == this.destPos.x && this.currPos.y == this.destPos.y )
                this.killed = true;

            // move projectile to next cell
            if(this.currPos.x != this.destPos.x || this.currPos.y != this.destPos.y) {
                //console.log(this.currPos);
                //console.log(this.path[this.path_index]);
                this.currPos.x = this.path[this.path_index].x;
                this.currPos.y = this.path[this.path_index].y;
                this.path_index++;
        }
    }
}
}