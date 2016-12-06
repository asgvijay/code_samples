function Projectile(sprite, xCoord, yCoord, width, height, damage, xDest, yDest, isAI)
{
  this.spriteInfo = {spriteSheet: "", imgName: ""};
  this.spriteInfo.imgName = new Image();
  this.spriteInfo.imgName.src = sprite;

  this.currPos = {x: xCoord, y: yCoord};
  this.size = {h:height, w:width};
  this.destPos = {type:"", x:xDest, y:yDest};
  this.type = "projectile";
  this.isAI = isAI;
  this.damage = damage;
  this.velocity = 1;
}

Projectile.prototype.retrieveProjectileInfo = function()
{
  var projInfo = {};
  projInfo.spriteInfo = {spriteSheet: this.spriteInfo.spriteSheet, imgName:this.spriteInfo.imgName};
  projInfo.isAI = this.isAI;
  projInfo.currPos = {x:this.currPos.x, y:this.currPos.y};
  projInfo.destPos = {x:this.destPos.x, y:this.destPos.y};  
  projInfo.size = {h:this.size.h, w:this.size.w};   
  projInfo.velocity = this.velocity;
  projInfo.damage = this.damage;
  return projInfo;
}

Projectile.prototype.update = function(updateObj)
{
  
  //console.log(updateObj);
  if (updateObj)
  {
    if (updateObj.currPos)
    {
      this.currPos.x = updateObj.currPos.x;  
      this.currPos.y = updateObj.currPos.y;  
    }

    if (updateObj.destPos)
    {
      this.destPos.x = updateObj.destPos.x;
      this.destPos.y = updateObj.destPos.y;
    }    
  }
}