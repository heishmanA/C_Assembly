# General purpose makefile

all: fib_nopie #change this to fib_pie if you get an error

in = fibonacci.s
out = fib.out

# Run this to if you get the 'relocation R_X86_64_32s against <directive> error to compile
fib_nopie: 
	gcc -g -no-pie $(in) -o $(out)

# Run this on the fpie related systems (redhat for example)
fib_pie:
	gcc -g $(in) -o $(out)

# run to remove *.out files on linux
clean_lin:
	rm -rf *.out

clean_wd:
	del *.out

test_five:
	./fib.out 5
