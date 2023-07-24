# Aaron Heishman
# Makefile for lab 3

#change the last dependency for each new lab
all:  tags headers filesystem clean 
# this entry has to change for lab 2 - 4
# NEVER compile .c files with this rule - it lacks needed compile time flags
# There is an entry below that turns .c files into .o files


# HF = header functions
HF1 = mkdir.c pwd.c ls.c rmdir.c
HF2 = cd.c free_memory.c insertdir.c 
HF3 = finddupes.c mv.c file.c cat.c callfuncs.c
HF4 = cp.c rm.c findfile.c help.c dirent_f.c
HF5 = dirprint.c dwp.c ch_root.c obliterate.c
#Target
filesystem: $(HF1) $(HF2) $(HF3) $(HF4) $(HF5)  filesystem.o
	gcc -g -o $@ $^

# this is where you create an entry to build your zip file
# it will also update with new labs

lab3.zip: makefile *.c *.h headers.sh headers.awk $(HF1) $(HF2) $(HF3) $(HF4) $(HF5)
	zip lab3.zip makefile readme *.c *.h $^
	# optional - remove old install folder proCoder
	rm -rf install
	# create install folder
	mkdir install
	# unzip to install folder
	unzip lab3.zip -d install
	# make filesystem the target
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
%.o:%.c %*.h 
	gcc -ansi -pedantic -Wimplicit-function-declaration -Wreturn-type -g -c $< -o $@

# clean up object files (Not sure why .vs files get made as well)
clean:
	rm *.o 
	rm *.vs




