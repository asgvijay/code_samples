class Clan1_Vehicle3_Proj extends ProjectileClass{

    constructor(startCoord, endCoord)

    {
        super(startCoord, endCoord);
        this.damage_infliction = 10; // was 50
        this.size.x = 10;
        this.size.y = 10;
        this.type = "STBullet";
        this.spriteInfo.imgName = "Clan1_Projectile3.png";
        this.spriteInfo.spriteSheet = "rbp.json";
        this.update =  function(updateObj){

            if(this.currPos.x == this.destPos.x && this.currPos.y == this.destPos.y )
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
