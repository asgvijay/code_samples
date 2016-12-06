// this function takes two coordinates (x/y) and returns the angle in which our image should be rotated in order to face that destination. 
// this is accomplished by creating an imaginary triangle between currPos, DestPos and an imaginary point directly above the currPos (the length between imaginary point and currPos is the same as the length between currPos and DestPos)
// we find distances b/w all three points then using those measurements we use COS and ARCOS functions to measure the degree of the angle that measures the difference between 0 degree and our destination degree.


var cardinalDirection = function(currPos, destPos)
    {
        
        //console.log("inside cardinalDirection");
        //console.log("cD's currPos is: ", currPos);
        //console.log("cD's desPos is: ", destPos);
        //IF DESTPOS.X < CURRPOS.X, WE ROTATE COUNTERCLOCKWISE IN RETURNED DEGREES, ELSE WE ROATATE CLOCKWISE IN DEGREES.
            
        if(currPos.x == destPos.x)
        		return 0;
        
        if(currPos.y == destPos.y)
        		return 90;
          
        
        // distance from curr to dest
        var a = Math.abs(currPos.x - destPos.x);
        var b = Math.abs(currPos.y- destPos.y);
        
    		// get distance b/w currPos and destPos... this is our radius
        var distance = Math.sqrt(Math.pow(a,2) + Math.pow(b,2));
        
        // coordinates of the top of our imaginary circle
        // we need this point to find the angle of enemy away from zero
        // x coord equals the same as our currPos.x and y coord is currPosY + the radius
        var top_circle_coords = {x : currPos.x, y : currPos.y + distance};
        
        // measure distance between dest and "imaginary point"
        var a1 = Math.abs(destPos.x - top_circle_coords.x);
        var b1 = Math.abs(destPos.y - top_circle_coords.y);
    
        // get distance b/w destination point and our imaginary point
        var distanceA = Math.sqrt(Math.pow(a1,2) + Math.pow(b1,2));
        
        
        
        // Calculate Cosign of angle A
        var cosA = (((Math.pow(distance,2) + Math.pow(distance,2) - Math.pow(distanceA,2) ))/(2*distance*distance));
        
        // get angle of A in radians by inversing the COS
        var angleA = Math.acos(cosA);
        //console.log("in cardinalDirection, angleA is: ", angleA);
        // convert radians to degrees
        var degrees = angleA * (180/Math.PI);
        

        return angleA;
      
        
    }