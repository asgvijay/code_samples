class ArmvedVehicle extends Anim_FighterClass{


    constructor(xPos, yPos)
    {

        super(xPos, yPos);
        this.health = 50;
        this.type = "armedvehicle";
        this.unitType = "vehicle";
        this.size.x= 100;
        this.size.y= 100;
        this.spriteInfo.spriteSheet = "ships.json";
        this.spriteInfo.imgName = "Clan1_Vehicle1.png";
        this.unit_projectile = "AVBullet";
        //This is to add the unit to the grid when the unit is initialized
    }
    
}