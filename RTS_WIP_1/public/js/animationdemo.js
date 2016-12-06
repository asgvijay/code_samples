var canvas = document.getElementById("animationCanvas");
var context = canvas.getContext("2d");
 
var myImage = new Image();
myImage.src = "https://www.kirupa.com/stuff/sprites_blue.png";
myImage.addEventListener("load", loadImage, false);
 
function loadImage(e) {
  animate();
}
 
var shift = 0;
var frameWidth = 300;
var frameHeight = 300;
var totalFrames = 24;
var currentFrame = 0;
 
function animate() {
  context.clearRect(120, 25, 300, 300);
 
  //draw each frame + place them in the middle
  context.drawImage(myImage, shift, 0, frameWidth, frameHeight,
                    120, 25, frameWidth, frameHeight);
 
  shift += frameWidth + 1;
 
  /*
    Start at the beginning once you've reached the
    end of your sprite!
  */
  if (currentFrame == totalFrames) {
    shift = 0;
    currentFrame = 0;
  }
 
  currentFrame++;
 
  requestAnimationFrame(animate);
}