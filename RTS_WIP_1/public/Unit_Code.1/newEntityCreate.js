// Function takes a string as an argument
// creates a new entity based on that string
// returns the new entity
// WE MUST INCLUDE ALL OUR GAME'S ENTITIES HERE.
var newEntityCreate= function (typename) {
 
    // Clan 1 Players
    if(typename == "Clan1_Collector")
        return new Clan1_Collector();
           
    if(typename == "Clan1_Fighter1")
        return new Clan1_Fighter1();
    
    if(typename == "Clan1_Fighter2")
        return new Clan1_Fighter2();
    
    if(typename == "Clan1_Fighter3")
        return new Clan1_Fighter3();
    
    // Clan 2 Players
    
    if(typename == "Clan2_Collector")
        return new Clan2_Collector();
           
    if(typename == "Clan2_Fighter1")
        return new Clan1_Fighter1();
    
    if(typename == "Clan2_Fighter2")
        return new Clan2_Fighter2();

    if(typename == "Clan2_Fighter3")
        return new Clan1_Fighter3();
    
    // Clan 1 Vehicles
    
    if(typename == "Clan1_Vehicle1")
        return new Clan1_Vehicle1();
    
    if(typename == "Clan1_Vehicle2")
        return new Clan1_Vehicle2();
    
    if(typename == "Clan1_Vehicle3")
        return new Clan1_Vehicle3();
    
    // Clan 2 "Vehicles"
    
    if(typename == "Clan2_Vehicle1")
        return new Clan2_Vehicle1();
    
    if(typename == "Clan2_Vehicle2")
        return new Clan2_Vehicle2();
    
    if(typename == "Clan2_Vehicle3")
        return new Clan2_Vehicle3();
      
    // Clan 1 and 2 Player Projectiles
    
     if(typename == "Clan1_Fighter1_Proj")
        return new Clan1_Fighter1_Proj();
    
    if(typename == "Clan1_Fighter2_Proj")
        return new Clan2_Fighter2_Proj();
    
    if(typename == "Clan1_Fighter3_Proj")
        return new Clan2_Fighter3_Proj();

    if(typename == "Clan2_Fighter1_Proj")
        return new Clan2_Fighter1_Proj();

    if(typename == "Clan2_Fighter2_Proj")
        return new Clan2_Fighter2_Proj();

    if(typename == "Clan2_Fighter3_Proj")
        return new Clan2_Fighter3_Proj();
        
    // Clan 1 Vehicle Projectile
        
    if(typename == "Clan1_Vehicle1_Proj")
        return new Clan1_Vehicle1_Proj();
    
    if(typename == "Clan1_Vehicle2_Proj")
        return new Clan1_Vehicle2_Proj();
    
    if(typename == "Clan1_Vehicle3_Proj")
        return new Clan1_Vehicle3_Proj();
    
    // Clan 2 Vehicle Projectiles
    
    if(typename == "Clan2_Vehicle1_Proj")
        return new Clan2_Vehicle1_Proj();
    
     if(typename == "Clan2_Vehicle2_Proj")
        return new Clan2_Vehicle2_Proj();
    
     if(typename == "Clan2_Vehicle3_Proj")
        return new Clan2_Vehicle3_Proj();
    
    // Game play structures
              
    if(typename == "Clan1_Tower")
        return new Clan1_Tower();
    
    if(typename == "Clan1_MissileTower")
        return new Clan1_MissileTower();
    
    //if(typename == "Wall")
      //  return new WallClass();

    if(typename == "Clan2_Tower")
        return new Clan2_Tower();

    if(typename == "Clan2_MissileTower")
        return new Clan2_MissileTower();

    // Tower Projectiles

    if(typename == "Clan1_Tower_Proj")
        return new Clan1_Tower_Proj();

    if(typename == "Clan1_MissileTower_Proj")
        return new Clan1_MissileTower();

    if(typename == "Clan2_Tower_Proj")
        return new Clan2_Tower_Proj();

    if(typename == "Clan2_MissileTower_Proj")
        return new Clan2_MissileTower_Proj();

    // Resources

    if(typename == "resource1")
        return new Resource1();

    if(typename == "resource2")
        return new Resource2();

    if(typename == "resource3")
        return new Resource3();


    }


    
        