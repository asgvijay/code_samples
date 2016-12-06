class Resource2 extends ResourceClass
{

    constructor(xCoord, yCoord)

    {
        super(xCoord, yCoord);
        this.resource_amount = 3000;
        this.maxResource = 3000;
        this.type = "Resource2";
        this.size.x = 50;
        this.size.y = 50;
        this.spriteInfo.imgName = "resource2.png";
        this.spriteInfo.spriteSheet = "rbp.json";

        this.update =  function(updateObj)
        {

            // add collectors to array
            if(updateObj.hasOwnProperty('collectors'))
                this.collectors = updateObj.collectors;

            // check all collectors in array to see if they are ready to deplete the resources
            if(this.collectors.length>0)
            {
                for (var i = 0; i < this.collectors.length; i++) {
                    if (this.collectors[i].readyToDepleteResource == true)
                        this.resource_amount -= 10;
                    // NOT SURE IF THIS NEXT LINE WILL WORK -- WILL THE ARRAY PASSED IN THE UPDATEOBJ BE AN ARRAY
                    // OF REFERENCES TO OUR COLLECTORS?
                    this.collectors[i].ready_to_deplete_resource = false;
                }

            }
					  if (this.resource_amount == 0){
							this.all_gone == false;
						}

            if (updateObj.hasOwnProperty('selected'))
            {          
                this.selected = updateObj.selected;
            }                        
        }
    }

}
