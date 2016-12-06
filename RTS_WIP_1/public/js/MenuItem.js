function MenuItem(type, xCoord, yCoord, width, height, cost)
{
  //this.spriteInfo = { spriteSheet : "Unit_Code.1/Sprites/Sprite_JSON/ships.json", imgName: "Unit_Code.1/Sprites/Sprite_JSON/ships.png"};
  this.type = type;
  //this.spriteInfo.imgName = new Image();
  //this.spriteInfo.imgName.src = "Unit_Code.1/Sprites/Sprite_JSON/ships.png";
  this.currPos = {x: xCoord, y: yCoord};
  this.size = {h:height, w:width};
  this.cost = cost;
}

MenuItem.prototype.retrieveMenuItemInfo = function()
{
  var menuItemInfo = {};
  menuItemInfo.type = this.type;
  //menuItemInfo.spriteInfo = {spriteSheet: this.spriteInfo.spriteSheet, imgName:this.spriteInfo.imgName};
  menuItemInfo.currPos = {x:this.currPos.x, y:this.currPos.y};
  menuItemInfo.size = {h:this.size.h, w:this.size.w};   
  menuItemInfo.cost = this.cost; 
  return menuItemInfo;
}
