function StartMenu(canvas) {
  this.ctx = canvas;
  this.newGame = {x:canvas.width/2-200, y:canvas.height/2-200};
  this.loadGame = {x:canvas.width/2-200, y:canvas.height/2};
  this.easyDifficulty = {x:canvas.width/2-200, y:canvas.height/2-200};
  this.hardDifficulty = {x:canvas.width/2-200, y:canvas.height/2};
}

StartMenu.prototype.showNewGameButton = function () {
  this.ctx.font = "30px Arial";
  this.ctx.lineWidth = 3;
  this.ctx.strokeStyle = 'black';
  this.ctx.strokeText("NEW GAME" this.newGame.x, this.newGame.y);
  this.ctx.fillStyle = 'white';
  this.ctx.fillText("NEW GAME" this.newGame.x, this.newGame.y);
};

StartMenu.prototype.showLoadGameButton = function () {
  this.ctx.font = "30px Arial";
  this.ctx.lineWidth = 3;
  this.ctx.strokeStyle = 'black';
  this.ctx.strokeText("LOAD GAME" this.loadGame.x, this.loadGame.y);
  this.ctx.fillStyle = 'white';
  this.ctx.fillText("LOAD GAME" this.loadGame.x, this.loadGame.y);    
};

StartMenu.prototype.showEasyDifficultyButton = function () {
  this.ctx.font = "30px Arial";
  this.ctx.lineWidth = 3;
  this.ctx.strokeStyle = 'black';
  this.ctx.strokeText("EASY" this.easyDifficulty.x, this.easyDifficulty.y);
  this.ctx.fillStyle = 'white';
  this.ctx.fillText("EASY" this.easyDifficulty.x, this.easyDifficulty.y);
};

StartMenu.prototype.showEasyDifficultyButton = function () {
  this.ctx.font = "30px Arial";
  this.ctx.lineWidth = 3;
  this.ctx.strokeStyle = 'black';
  this.ctx.strokeText("HARD" this.hardDifficulty.x, this.hardDifficulty.y);
  this.ctx.fillStyle = 'white';
  this.ctx.fillText("HARD" this.hardDifficulty.x, this.hardDifficulty.y);
};
