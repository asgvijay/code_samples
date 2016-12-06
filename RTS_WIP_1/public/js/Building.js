function Building(health, sprite, xCoord, yCoord, width, height, buildingType, isAI)
{
  this.spriteInfo = {spriteSheet: "", imgName: ""};
  this.spriteInfo.imgName = new Image();
  this.spriteInfo.imgName.src = sprite;

  this.isAI = isAI;
  this.currPos = {x: xCoord, y: yCoord};
  this.size = {h:height, w:width};
  this.type = "building";
  this.maxHealth = health; 
  this.currHealth = health; 
  this.selected = false;
  this.buildingType = buildingType;
}

Building.prototype.retrieveBuildingInfo = function()
{
  var buildingInfo = {};
  buildingInfo.spriteInfo = {spriteSheet: this.spriteInfo.spriteSheet, imgName:this.spriteInfo.imgName};
  buildingInfo.isAI = this.isAI;
  buildingInfo.currPos = {x:this.currPos.x, y:this.currPos.y};
  buildingInfo.size = {h:this.size.h, w:this.size.w};    
  buildingInfo.maxHealth = this.maxHealth; 
  buildingInfo.currHealth = this.currHealth;
  buildingInfo.selected = this.selected;
  buildingInfo.buildingType = this.buildingType;
  return buildingInfo;
};

Building.prototype.update = function(updateObj)
{
  
  if (updateObj)
  {
    if(typeof updateObj.selected !== 'undefined')
    {
      this.selected = updateObj.selected;  
    }

    if(updateObj.damage)
    {    
      this._takeDamage(updateObj.damage);
    }

  }
};

Building.prototype._takeDamage = function(damage)
{
  this.currHealth -= damage;
};