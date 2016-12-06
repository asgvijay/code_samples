function Camera(map, width, height, bgWidth, bgHeight) {
    this.x = 0;
    this.y = 0;
    this.width = width;
    this.height = height;
    this.maxX = bgWidth - width;
    this.maxY = bgHeight - height;
    this.SPEED = 256;
}

Camera.SPEED = 256; // pixels per second

Camera.prototype.move = function (dirx, diry) {
    // move camera
    this.x += dirx * this.SPEED * .02;
    this.y += diry * this.SPEED * .02;
    
    // clamp values
    this.x = Math.max(0, Math.min(this.x, this.maxX));
    this.y = Math.max(0, Math.min(this.y, this.maxY));
};

