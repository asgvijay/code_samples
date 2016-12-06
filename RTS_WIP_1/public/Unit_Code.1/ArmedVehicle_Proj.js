class ArmedVehicle_ProjClass extends ProjectileClass{

    constructor(xCoord, yCoord, destX, destY)

    {
        super(xCoord, yCoord, destX, destY);
        this.damage_infliction = 40;
        this.type = "AVBullet";
        this.spriteInfo.imgName = "Clan1_Projectile1.png";
        this.spriteInfo.spriteSheet = "rbp.json";
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
