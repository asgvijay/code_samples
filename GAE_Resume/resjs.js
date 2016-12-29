function activateButton()
{
    var submitButton = document.getElementById("submit_button");
    submitButton.addEventListener("click", function ()
    {

        event.preventDefault();
        
        var jObjDiv = document.getElementById("json");
        console.log(jObjDiv);

        var first = document.getElementById("first_name").value;
        var last = document.getElementById("last_name").value;
        
        var req = new XMLHttpRequest();
        
        req.open("GET", "https://resume-api-emc.appspot.com/" + first + "/" + last, true);

        req.addEventListener("load", function() 
        {
          if (req.status >= 200 && req.status < 400)
              {
                var response = JSON.parse(req.responseText);
                console.log(response);
                var jString = document.createTextNode(JSON.stringify(response, null, 4))
                jObjDiv.appendChild(jString);
                
            }
          else
            console.log("Error in network request: " + req.status);

        });
        req.send(null);
    });
}

document.addEventListener("DOMContentLoaded", activateButton);
