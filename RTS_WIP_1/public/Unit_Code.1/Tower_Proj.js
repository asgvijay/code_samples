class Tower_ProjClass extends ProjectileClass{

    constructor(startCoord, endCoord)

    {
        super(startCoord, endCoord);
        this.damage_infliction = 50;
        this.type = "TBullet";
        this.spriteInfo.imgName = "Clan1_Projectile2.png";
        this.spriteInfo.spriteSheet = "rpb.json";
        this.update =  function(updateObj){

            if(this.currPos.xCoord == this.destPos.x && this.currPos.yCoord == this.destPos.y )
                this.killed = true;

            // move projectile to next cell
            if(this.currPos.x != this.destPos.x || this.currPos.y != this.destPos.y) {
                this.currPos.x = this.path[this.path_index].x;
                this.currPos.y = this.path[this.path_index].y;
                this.path_index++;
            }

        }
    }
}
