import webapp2
from google.appengine.ext import ndb
import json

# entity type to be used in creating and storing database entries
# each entity will have a first name, last name and a resume in JSON format
class Resume(ndb.Model):
    first_name = ndb.StringProperty(required=True)
    last_name = ndb.StringProperty(required=True)
    resume = ndb.JsonProperty(required=True)
   

    # This class handles the addition of resumes to the datastore
    # It is called when a call to the endpoint .../newres/first_name/last_name
    # is made.
class createResume(webapp2.RequestHandler):
    def post(self, *args):
        #if user doesn't accept JSON return error
        if 'application/json' not in self.request.accept:
            self.response.status = 406
            self.response.status_message = "API only supports JSON"            
            return
        
        # get keywords sent in url
        this_first = args[0]
        this_last = args[1]
        
        # If both keywords were present we query the resource.
        # If resource exists we send an object that contains a message stating
        # resume already exists. If resource does not exist, we add new entity
        # to datastore using the keywords as the first_name and last_name and the 
        # body of the post as the JSON formatted resume.
        
        # both keywords exist
        if this_first and this_last:
            res_query = Resume.query(Resume.first_name == this_first, Resume.last_name == this_last)
            res_key = res_query.get()
            
            # the resume referenced via the keywords does not exist so we are clear to create new entity
            if res_key == None:
                new_res = Resume(first_name = this_first, last_name = this_last, resume = self.request.body)
                new_res_key = new_res.put()
                out = {"message":"Resume Added"}
                self.response.headers["cache-control"]= "max-age=120"
                self.response.headers['Access-Control-Allow-Methods'] = 'POST'
                self.response.write(json.dumps(out))
                
            # resume referenced via the keywords already exists. We will not create new entity    
            else:
                out = {"message":"Resume already exists for this person."}
                self.response.write(json.dumps(out))
                
        # insufficient # of keywords       
        else:
            out = {"message":"Please include all fields"}
            self.response.write(json.dumps(out))
    
    
# This handler is used for our GET requests. It requires a first name and last name to access
# the resource. 

class getRes(webapp2.RequestHandler):
    def get(self, *args):
        #if user doesn't accept JSON return error
        if 'application/json' not in self.request.accept:
            self.response.status = 406
            self.response.status_message = "API only supports JSON"            
            return
        
        # get keywords sent in url
        this_first = args[0]
        this_last = args[1]
        
        # If both keywords were present we query the resource.
        # If resource exists we return the JSON formatted resume
        # If resource does not exists we return object with message stating
        # resource does not exist.
           
            
        # both keywords exist
        if this_first and this_last:
            res_query = Resume.query(Resume.first_name == this_first, Resume.last_name == this_last)
            res_key = res_query.get()
            
            # we succesfully queried the resource
            if res_key != None:
                out = json.loads(res_key.resume)
                self.response.headers["cache-control"]= "max-age=120"
                self.response.headers.add_header("Access-Control-Allow-Origin", "*")
                self.response.write(json.dumps(out, indent=4))
            
            # the query returned nothing, therefore the resource does not exist
            else:
                out = {"message":"Resume does not exist for this person"}
                self.response.write(json.dumps(out))
                
        # both keywords were not present        
        else:
            out = {"message":"Must include first and last name in resource request."}
            self.response.write(json.dumps(out))
    
# this variable calls the appropriate handler when a call to the API is made.                      
app = webapp2.WSGIApplication([
        (r'/(\w+)/(\w+)', getRes),
        (r'/newres/(\w+)/(\w+)', createResume)
        ])

        




