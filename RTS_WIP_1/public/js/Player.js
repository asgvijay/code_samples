function Player() {
    this.resources = 500;    
}

Player.prototype.getResources = function () {
    return this.resources;
};


Player.prototype.addResources = function (resources)
{
    this.resources += resources;
};

Player.prototype.useResources = function (resources)
{
  if (resources > this.resources)
  {
  	console.log("Insufficient resources");
  }
  else
  {
  	this.resources -= resources;
  }
};

