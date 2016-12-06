var distanceTo = function(currPos, destPos)
{
    
    var a = Math.abs(currPos.x - destPos.x);
    var b = Math.abs(currPos.y - destPos.y);
    
    var c  = Math.sqrt(Math.pow(a,2) + Math.pow(b,2));
    
    return c;
    
}
