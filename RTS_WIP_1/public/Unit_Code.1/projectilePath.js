// This function takes a starting point (x,y) and a destination point (x,y) and computes a coordinate based path
// that will result in an approximately straight line across a 2d Grid between the two points

class Coordinates{

    constructor(x, y){

        this.x = x;
        this.y = y;

    }
}
function projectilePath (startCoordinates, endCoordinates) {
    var coordinatesArray = new Array();
    // Translate coordinates
    var x1 = startCoordinates.x;
    var y1 = startCoordinates.y;
    var x2 = endCoordinates.x;
    var y2 = endCoordinates.y;
    // Define differences and error check
    var dx = Math.abs(x2 - x1);
    var dy = Math.abs(y2 - y1);
    var sx = (x1 < x2) ? 1 : -1;
    var sy = (y1 < y2) ? 1 : -1;
    var err = dx - dy;
    // Set first coordinates
    coordinatesArray.push(new Coordinates(x1, y1));
    // Main loop
    while (!((x1 == x2) && (y1 == y2))) {
        var e2 = err << 1;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
        // Set coordinates
        coordinatesArray.push(new Coordinates(x1, y1));
    }
    // Return the result
    return coordinatesArray;
}


// code for Bresenham's Algorithm borrowed from: http://stackoverflow.com/questions/4672279/bresenham-algorithm-in-javascript