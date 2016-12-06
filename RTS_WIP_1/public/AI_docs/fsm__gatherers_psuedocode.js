var isAI = false; //This would be a boolean value to help differentiate behaviors between aI units and player units
var state = 'idle'; //This would be initilized to "idle" and would be updated over time depending on game state and current state
var homeBase = {}; //This will be the x, y coordinates of the building the created this unit
var path = [] //most recent path the unit was told to travel, if null it means the unit was idle
var current_resource = {}; //this is a reference to the current resource that the unit is gathering
var being_attacked = false; //indicates whether a unit is attacking this unit
var carry_limit = 10; //arbitrary limit of how many resource a unit can carry at one time
var carrying = 0; //amount of resource the unit is currently carrying


function updateState(state) {
    switch(state) {
        case 'idle':
            //check if unit is at homeBase
            if (current_location == this.homeBase) {
                break;
            //if not at homeBase than travel there
            } else {
                path = findPath(current_position, this.homeBase, true);
                move(path);
                this.state = 'moving';
                break;
            }
            break;
        //Unit has a target resource and is moving to the location
        case 'gathering': 
            //check if being attacked, not actually sure how we would tell a unit this
            if (beingAttacked()) {
                this.state = 'flee';
                break;
            }
            //check if resource is depeleted
            if (!current_resource) {
                current_resource = find_resource(); //try to find a nearby resource
                if (current_resource == null) { //if we can't find a resource head home
                    state = 'idle';
                    break;
                }
                break;
            }
            //check if carry limit has been reached
            if (reach_carry_limit()){
                path = findPath(current_location, this.homeBase, true);
                move(path);
                state = 'delivering';
            }
            break;
        case 'delivering':
            if (carrying == 0) {
                gather(current_resource);
                state = 'gathering';
            }
            break;
        case 'flee':
            if (current_position == this.homeBase) {
                this.state = 'idle';
                break;
            }
            break;
    }
        
}