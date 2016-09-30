#!/usr/bin/python

# create a file with random name
# add a random string to the file
# print the strings to the screen 
# close file
# loop three times
for index in range(3):                  
	filename = "file_" + str(index+1) + ".txt"
	newFile = open(filename, "wb")

	fileString = ""
	import random

	for index in range(10):
		fileString += (unichr(random.randint(97,122)))
	fileString += "\n"
	print("The random letters from " +  filename + " are:\n")
	print(fileString)
	newFile.write(fileString) 
	newFile.close()

# find two random numbers between 1 and 42, inclusive
# print their values
# print the product of the two random numbers

randInt1 = (random.randint(1,42))
randInt2 = (random.randint(1,42))

print("The first random integer is: " + str(randInt1) + "\n")
print("The second random integer is: " + str(randInt2) + "\n")

print("The product of these two numbers is: " + str(randInt1 * randInt2) + "\n")



