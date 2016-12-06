
var ImageLoader = { images: {} };

ImageLoader.loadImage = function (key, src) {
    var img = new Image();
    var d = new Promise(function (resolve, reject) {
        img.onload = function () {
            this.images[key] = img;
            resolve(img);
        }.bind(this);

    }.bind(this));

    img.src = src;
    return d;
};

ImageLoader.returnImage = function (key) {
    return this.images[key];
};