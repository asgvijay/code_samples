var enemyRange =  function(unit, enemy)
{

    if(unit != null && enemy != null) {

        a = Math.abs(unit.currPos.x - enemy.currPos.x);
        b = Math.abs(unit.currPos.y - enemy.currPos.y);

        c_square = Math.pow(a, 2) + Math.pow(b, 2);

        if (Math.sqrt(c_square) <= 100)
            return true;
    }

    return false;
    
};