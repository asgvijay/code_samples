function Unit(health, sprite, xCoord, yCoord, width, height, isAI)
{
  this.spriteInfo = {spriteSheet: "", imgName: ""};
  this.spriteInfo.imgName = new Image();
  this.spriteInfo.imgName.src = sprite;

  this.currPos = {x: xCoord, y: yCoord};
  this.size = {h:height, w:width};
  this.destPos = {type:"", x:xCoord, y:yCoord};
  this.selected = false;
  this.maxHealth = health; 
  this.currHealth = health;
  this.type = "unit";
  this.state = "Idle";
  this.isAI = isAI;
  this.killed = false;
  this.beingAttacked = false;
  this.homeBase = {x:xCoord,y:yCoord};
  this.nearest_enemy = {};
  this.velocity = 1;
  this.target = null;
}

Unit.prototype.retrieveUnitInfo = function()
{
  var unitInfo = {};
  unitInfo.spriteInfo = {spriteSheet: this.spriteInfo.spriteSheet, imgName:this.spriteInfo.imgName};
  unitInfo.maxHealth = this.maxHealth;
  unitInfo.currHealth = this.currHealth;
  unitInfo.isAI = this.isAI;
  unitInfo.currPos = {x:this.currPos.x, y:this.currPos.y};
  unitInfo.destPos = {x:this.destPos.x, y:this.destPos.y};  
  unitInfo.size = {h:this.size.h, w:this.size.w};    
  unitInfo.selected = this.selected;
  unitInfo.velocity = this.velocity;
  unitInfo.state = this.state;
  unitInfo.target = this.target;
  unitInfo.inRange = this.enemyRange();
// Vijay added this to get rid of error
  unitInfo.rotation = 0;
  return unitInfo;
}

Unit.prototype.update = function(updateObj)
{
  //console.log(updateObj);
  
  if (updateObj)
  {
    if (typeof updateObj.isAI !== 'undefined')
    {
      this.isAI = updateObj.isAI;
    }

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

    if (this.destPos.x != this.currPos.x || this.destPos.y != this.currPos.y)
    {
      this.enRoute = true;  
    }
    else
    {
      this.enRoute = false;  
    }
          
    if(typeof updateObj.selected !== 'undefined')
    {
      this.selected = updateObj.selected;  
    }

    if(typeof updateObj.state !== 'undefined')
    {
      console.log("state updated");
      if (updateObj.state)
      {
        this.state = updateObj.state;
      }      
    }   

    if (updateObj.target) 
    {
      this.target = updateObj.target;
    }

    if(updateObj.damage)
    {
      this._takeDamage(updateObj.damage);
    }
  }
}

Unit.prototype._takeDamage = function(damage)
{
  this.currHealth -= damage;
  this.beingAttacked = true;
}

Unit.prototype.enemyRange = function()
{
    
    a = Math.abs(this.currPos.x - this.destPos.x);
    b = Math.abs(this.currPos.y - this.destPos.y);
    
    c_square = Math.pow(a,2) + Math.pow(b,2);
    
    if(Math.sqrt(c_square) <= 200)
        return true;
    else
        return false;
    
}
