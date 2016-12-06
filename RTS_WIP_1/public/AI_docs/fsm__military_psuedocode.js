var isAI = false; //This would be a boolean value to help differentiate behaviors between aI units and player units
var state = 'idle'; //This would be initilized to "idle" and would be updated over time depending on game state and current state
var homeBase = {}; //This will be the x, y coordinates of the building the created this unit
var path = [] //msot recent path the unit was told to travel, if null it means the unit was idle
var holdGround = false; //This boolean indicates whether a unit should flee if outnumbered or dying
var assigned_enemy = {} //This holds a reference to the current closest unit for this unit to attack, or the unit that was assigned to be attacked
var nearest_enemy = {} //This holds the nearest enemy to the unit
var being_attacked = false; //indicates whether a unit is attacking this unit


function updateState(state) {
    switch(state) {
        case 'idle':
            //check if enemies are nearby
            if (enemiesNearby()){
                //check if outnumbered
                if(!outNumbered()){
                    //not outnumbered attack
                    nearest_enemy = getNearestEnemy();
                    attack(enemy);
                    this.state = 'attack';
                    break;
                } 
                if (holdGround == false) {
                    path = findPath(currentPos, this.homeBase, true)
                    move(path);
                    this.state = 'moving';
                    break;
                }
            }
            break;
        //moving means unit will not actively attack enemy units, but will defend if attacked
        case 'moving': 
            //check if being attacked, not actually sure how we would tell a unit this
            if (beingAttacked()) {
                nearest_enemy = attackingUnit();
                attack(nearest_enemy);
                state = 'attack';
                break;
            }
            if (assigned_enemy != null){
                //look at the attack case for notes about the next if block
                if (attackDistance(unit, enemy) == 0) { 
                    attack(assigned_enemy);
                    state = 'attack';
                    break;
                } else {
                    this.path = findPath(current_position, enemy_position, true);
                    state = 'moving';
                    break;
                }
            }
            if (path.length() == 0) {
                state = 'idle';
                break;
            }
            break;
        //means unit will actively seek to attack enemy units while moving
        case 'patrol':
             //check if enemies are nearby
            if (enemiesNearby()){
                nearest_enemy = getNearestEnemy();
                attack(nearest_enemy);
                this.state = 'attack';
                break;
            }
            break;
        //unit will not attack enemy units and will not defend, they will merely attempt to retreat to homeBase
        case 'flee': 
            if (current_position == this.homeBase) {
                this.state = 'idle';
                break;
            }
            break;
        case 'attack':
            //first check what my health is at
            //lowhealth would return true if under 50%
            if (!lowHealth()) {
                //check if unit should be attacking a nearby enemy
                if(nearest_enemy != null) {
                    attack(nearest_enemy);
                    break;
                }


                //check if unit has been told to attack a specific enemy
                if(assigned_enemy != null) {
                    //check if near assigned enemy
                    //This nest statement calculates the distance range of the units attack compared to the target units position
                    //This of course will need to be written.
                    if (attackDistance(unit, enemy) == 0) { 
                        attack(assigned_enemy);
                        state = 'attack';
                        break;
                    } else {
                        this.path = findPath(current_position, enemy_position, true);
                        state = 'moving';
                        break;
                    }
                } 
            } else {
                path = findPath(current_position, this.homeBase, true);
                move(path);
                state = 'flee';
                break;
            }
            
            break;
    }
}