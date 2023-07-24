# Aaron Heishman
# Makefile for lab 1-4.

#change the last dependency for each new lab
all:  tags headers encrypt decrypt encryptgonewrong 

# this entry has to change for lab 2 - 4
# NEVER compile .c files with this rule - it lacks needed compile time flags
# There is an entry below that turns .c files into .o files


encrypt: encrypt.o 
	gcc -g -o $@ convtobits.c power.c shiftleft.c $^

decrypt: decrypt.o
	gcc -g -o $@ convtobits.c power.c shiftright.c $^

encryptgonewrong: encryptgonewrong.o
	gcc -g -o $@ convtobits.c power.c shiftleft.c $^

# this is where you create an entry to build your zip file
# it will also update with new labs

lab2.zip: makefile *.c *.h 
	zip lab2.zip makefile *.c *.h lab2readme headers.sh headers.awk reqtestfile reqexpected tc_seven_ch tc_mixed thebesttestcase
	# optional - remove old install folder proCoder
	rm -rf install
	# create install folder
	mkdir install
	# unzip to install folder
	unzip lab2.zip -d install
	# make lab1 the target, not lab 1.zip
	make -C install all


	  
#this entry stays for C code labs
tags: *.c
	ctags -R .

# this entry stays for C code labs
headers: *.c tags
	headers.sh


# this entry takes care of C files depending on header files
# It has the flags for compiling the c code
# It you don't like makefiles, consider typing the following line a few
# thousand times this semester and reconsider.
# Be sure that this one doesn't get an inserted line break anywhere
%.o:%.c *.h 
	gcc -ansi -pedantic -Wimplicit-function-declaration -Wreturn-type -g -c $< -o $@

# clean up object files
clean:
	rm *.o 



