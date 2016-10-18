import json
from objdict import ObjDict

# Parameters: Encoded Message, User Input Argument, RSA public Key
# Preconditions: Encoded Message must be base64, User Input must be a string, and RSA public key must be a valid key
# Postconditions: Returns a JSON object populated with all necessary data
# Description: Function populates a JSON object with all necessary data as per the challenge, then returns the completed object.

def fill_json(enc, arg, publickey):
        data = ObjDict()
        data ['$schema'] = 'http://json-schema.org/draft-04/schema#'
        data ['title'] = 'Signed Identifier'
        data ['description'] = 'Schema for a signed identifier'
        data ['type'] = 'object'
        data ['required'] = ['message', 'signature', 'pubkey']
        data ['properties'] = ObjDict()
        data.properties.message = ObjDict()
        data.properties.message.type = arg
        data.properties.message.description = "original string provided as the input to your app"
        data.properties.signature = ObjDict()
        data.properties.signature.type = enc.rstrip('\n')
        data.properties.signature.description = "RFC 4648 compliant Base64 encoded cryptographic signature of the input, calculated using the private key and the SHA256 digest of the input"
        data.properties.pubkey = ObjDict()
        data.properties.pubkey.type = publickey.exportKey() 
        data.properties.pubkey.description = "Base64 encoded string (PEM format) of the public key generated from the private key used to create the digital signature"
        
        # dump the info from data object into a json object
        json_data = json.dumps(data)
        
        # print the content of data in JSON format
        print json.dumps(data.properties, indent=4)

        return json_data