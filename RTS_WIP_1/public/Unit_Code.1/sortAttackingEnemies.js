// MERGE SORT 

// this function will merge sort an array of attacking enemies by their distance to the unit they are attacking. this will allow the unit being attacked to attack its nearest attacker

// FUNCTION MUST BE TESTED


var sortAttackingEnemies = function(array_of_attackers, currPos)
    {
        if(length.array_of_attackers == 1)
            return array_of_attackers;
        var low = 0;
        var high = length.array_of_attackers;
        var mid = floor(high + low /2);        
        var lower_half = sortAttackingEnemies(array_of_attackers, currPos);
        var upper_half = sortAttackingEnemies(array_of_attackers, currPos);
        return _merge(lower_half, upper_half, currPos);
    }
    
    


var _merge = function(lower_half, upper_half, currPos)

    {
        var merged_array = [];
        var i = 0;

        while( length.lower_half >0 && length.upper_half>0)
            {

                // sort by distance to enemy
                if(distanceTo(currPos, lower_half[0].currPos) > distanceTo(currPos, upper_half[0].currPos))
                    {
                        merged_array[i] = lower_half[0];
                        lower_half.splice(0,1);
                        i++;
                    }
                else
                    {
                        merged_array[i] = upper_half[0];
                        upper_half.splice(0,1);
                        i++;
                    }

            }

        while(length.lower_half>0)
            {
                merged_array[i] = lower_half[0];
                lower_half.splice(0,1);
                i++;

            }

           while(upper_half>0)
            {
                merged_array[i] = upper_half[0];
                upper_half.splice(0,1);
                i++;

            }

        return merged_array;


    }
