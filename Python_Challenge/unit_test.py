import os
from random import randint
import string
import random
import shutil

# test input within a certain range or string length. 
# To stay within four hour time limit set by recruiter, I have not built exhaustive unit tests. This test is simply for randomizing a string and brut force testing the program with random user input.
# With further testing development, we would be ensuring that Public/Private keys are encoding and decoding messages properly. This testing can be implemented into the randomizer function below.

for i in range(5):
    num_chars = (randint(0,256))
    random_argument = ""
    for index in range(num_chars):
        random_argument += random.choice(string.letters)
    os.system("python rsa1.py " + random_argument + ">> output.txt")
    f = open('output.txt', 'a+')
    print >> f, "******************************************************\n"
    f.close() 
    
shutil.rmtree('key_folder')
