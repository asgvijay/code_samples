class Clan1BasicTowerClass extends TowerClass{

    constructor(xCoord, yCoord){

        super(xCoord, yCoord);

        //this.imgMovement = {
        //  imgAnimateIndex: 0,
        //spriteLibLength: 0,
        //direction: ""
        //};

        this.unit_projectile =  "Clan1_TowerProj";
        this.type = "Clan1_Tower";
        this.spriteInfo.imgName = "Clan1_Tower.png";
        this.spriteInfo.spriteSheet = "rpb.json";

    }
}