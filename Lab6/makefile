
# Compile the required lab files, create a zip and then clean the .out files
all: compile 

# Compile first to verify they can, create directory for zipping
# copy all files to the directory then zip the file and the files from the directory
lab6zip : compile 
	mkdir Lab6
	cp	readme makefile Lab6.s ./Lab6
	zip Lab6 ./Lab6 ./Lab6/*
	rm -rf *.out lab6

# compile additional assembly file to .out executable (if lab requires it)
compile: 
	gcc -g Lab6.s -o Lab6.out

# remove all .out and _test files
clean:
	rm -rf *.out 
