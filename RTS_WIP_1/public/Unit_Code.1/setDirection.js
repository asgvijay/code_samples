
var setDirection = function(destPos, currPos, imgMovement)
{

// Direction is NE
    if(destPos.x > currPos.x && destPos.y > currPos.y)
    {
        // already on the way, simply increment index
        if(imgMovement.direction == "NE" && imgMovement.imgAnimateIndex < imgMovement.spriteLibLength)                                          imgMovement.imgAnimateIndex++;
        
        else if(imgMovement.direction == "NE" && imgMovement.imgAnimateIndex == imgMovement.spriteLibLength)                              imgMovement.imgAnimateIndex = 1;
    
        // just starting out NE, set index ceiling and start at 1
        else
        {
            imgMovement.spriteLibLength = Fighter1SpriteLib.moveNE.length;
            imgMovement.imgAnimateIndex = 1;
            imgMovement.direction = "NE";
    
        }
    
    }
                                   
// Direction is NW
    if(destPos.x < currPos.x && destPos.y > currPos.y)
    {
        // already on the way, simply increment index
        if(imgMovement.direction == "NW" && imgMovement.imgAnimateIndex < imgMovement.spriteLibLength)                              imgMovement.imgAnimateIndex++;
        
         else if(imgMovement.direction == "NW" && imgMovement.imgAnimateIndex == imgMovement.spriteLibLength)                              imgMovement.imgAnimateIndex = 1;
    
        // just starting out NE, set index ceiling and start at 1
        else
        {
            imgMovement.spriteLibLength = Fighter1SpriteLib.moveNW.length;
            imgMovement.imgAnimateIndex = 1;
            imgMovement.direction = "NW";
        }
    
    }
// Direction is SE
    if(destPos.x > currPos.x && destPos.y < currPos.y)
    {
        // already on the way, simply increment index
        if(imgMovement.direction == "SE" && imgMovement.imgAnimateIndex < imgMovement.spriteLibLength)                              imgMovement.imgAnimateIndex++;
        else if(imgMovement.direction == "SE" && imgMovement.imgAnimateIndex == imgMovement.spriteLibLength)                              imgMovement.imgAnimateIndex = 1;
    
        // just starting out NE, set index ceiling and start at 1
        else
            {
                imgMovement.spriteLibLength = Fighter1SpriteLib.moveSE.length;
                imgMovement.imgAnimateIndex = 1;
                imgMovement.direction = "SE";
            }
    
    }

// Direction is SW
    if(destPos.x < currPos.x && destPos.y > currPos.y)
    {
        // already on the way, simply increment index
        if(imgMovement.direction == "SW" && imgMovement.imgAnimateIndex < imgMovement.spriteLibLength)
                imgAnimateIndex++;
        else if(imgMovement.direction == "SW" && imgMovement.imgAnimateIndex == imgMovement.spriteLibLength)                              imgMovement.imgAnimateIndex = 1;
    
        // just starting out NE, set index ceiling and start at 1
        else
        {
            imgMovement.spriteLibLength = Fighter1SpriteLib.moveSW.length;
            imgMovement.imgAnimateIndex = 1;
            imgMovement.direction = "SW";
    
        }
    
    }



}
  
  
  