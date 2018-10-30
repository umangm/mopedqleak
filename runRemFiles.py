# Import system modules
import subprocess, os

directoryname = "examples"

fileOut = open("remTestOut.txt", "w")

# Run through all of the files within the specified directory that end with .rem and write them to an output file
for filename in os.listdir(directoryname):
	if filename.endswith(".rem"):
		fileOut.write("\n" + filename + "\n")
		fileOut.flush()
		subprocess.check_call("./mql -min " + directoryname + "/"+ filename, stdout=fileOut, stderr=fileOut, shell=True)
		

fileOut.close()


fileInOrig = open("originalMinVals.txt", "r")

origFile = fileInOrig.read()

fileInOrig.close()

# Split entire file into an array for easy access of different files/values stored
origFileSplit = origFile.split("\n")

fileIn = open("remTestOut.txt", "r")
testFile = ""

newValue = 0.00

for line in fileIn:
	word = line.split(" ")
	if word[0].endswith(".rem\n"):
		testFileArr = word[0].split("\n", 1)
		testFile = testFileArr[0]
	if word[0] == "MinEntropy":
		valueArr = word[2].split("\n", 1)
		newValue = float(valueArr[0])
		for i in range(len(origFileSplit)):
			if(origFileSplit[i] == testFile):
				print(testFile)
				print("Difference: "+ str(float(origFileSplit[i+1]) - newValue) + "\n")

fileIn.close()
