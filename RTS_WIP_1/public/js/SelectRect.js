function SelectRect(xCoord, yCoord, width, height, color)
{
  this.currPos = {x: xCoord, y: yCoord};
  this.size = {y:height, x:width};
  this.color = color;
}

SelectRect.prototype.retrieveSelectRectInfo = function()
{
  var rectInfo = {};
  rectInfo.currPos = {x:this.currPos.x, y:this.currPos.y};
  rectInfo.size = {y:this.size.y, x:this.size.x};  
  rectInfo.color = this.color;  
  return rectInfo;
}

SelectRect.prototype.updateSelectRectInfo = function(updateObj)
{
  if(updateObj)
  {
    this.currPos.x = updateObj.currPos.x;
    this.currPos.y = updateObj.currPos.y;

    if(updateObj.size)
    {
    this.size.y = updateObj.size.y;
    this.size.x = updateObj.size.x;      
    } 

    if(typeof updateObj.blocked !== 'undefined')   
    {
      if(updateObj.blocked)
      {
        this.color = "red";
      }
    }
    else
    {
      this.color = "blue";
    }
  }
}