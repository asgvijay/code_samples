from Crypto.PublicKey import RSA # for creating keys
from Crypto import Random # to create random generator
import hashlib # for hashing user input
import sys # for argument access
import os
from objdict import ObjDict
import json
import base64
from Crypto.Cipher import PKCS1_OAEP
from fill_json import fill_json

# Ensure 2 arguments. 
# If >2 or <2 arguments, print error and exit
if len(sys.argv) != 2:
    print 'Incorrect number of arguments. Please try again.'
    exit()

# create a new hash for use with user input
sha_256 = hashlib.sha256()
sha_256.update(sys.argv[1])
hash_input = sha_256.hexdigest()

# create a root folder for all dynamically created
# key folders
if not os.path.exists('key_folder'):
    os.mkdir('key_folder')
    os.chdir('key_folder')
else:
    os.chdir('key_folder')
    
# create unique directory for each user input
# if directory does not exist, we create the directory
# and change our location to the newly created directory
if not os.path.exists(hash_input):
    os.mkdir(hash_input)
    os.chdir(hash_input)
    
# if the directory already exists, we change to the existing
# directory and access the JSON file
else:
    os.chdir(hash_input)
    jData = open('datafile', 'r')  #open JSON file for reading
    load_j_data = json.load(jData) #parse JSON data
   
    # NOTE: Due to JSON's unorderded mappings, data may print out of order compared to example. We can force to print in order specified using a couple more lines of code. However, without knowing the purpose of the formatting, I opted to use the natural behaviors of JSON. 
    # print json data 
    print json.dumps(load_j_data['properties'], indent=4)
    
    # close file and exit the program
    jData.close() 
    exit() 

# create a new RSA key pair using a random_generator    
random_generator = Random.new().read
key = RSA.generate(1024, random_generator)

publickey = key.publickey() # get public key
pkey = PKCS1_OAEP.new(publickey) # create object for encryption
encrypted_message = pkey.encrypt(hash_input) # encrypt hashed input

enc_base64 = encrypted_message.encode('base64') #convert to base64

# If we want to decrypt a message, we must use the private key accessible
# in the user's folder. This is not intended for actual use, but for 
# testing only. In actual use cases, we do not save the private key

# let's keep both the keys in the unique folder
pubKeyFile = open('./pubKey', 'w+') 
print >> pubKeyFile, publickey.exportKey() # write public key to new file

privKeyFile = open('./privKey.PEM', 'w+') 
print >> privKeyFile, key.exportKey() # write private key to new file

# Create and populate an object for dumping into JSON
# Each property within the data object that is set equal to ObjDict() is an object that contains its own properties
json_obj = fill_json(enc_base64, sys.argv[1], publickey)


# push json object to its own file        
jsonFile = open('./datafile', 'w+')
print >> jsonFile, json_obj


#close out files
pubKeyFile.close()
privKeyFile.close()
jsonFile.close()
