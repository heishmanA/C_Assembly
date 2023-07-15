# Tags for all files used 
labfiles = *.s lab5readme makefile
test_cases = test_one tc_mixed thebesttestcase
expected = test_one_expected
outputnames = encrypt.out decrypt.out
s_files = Lab5Encrypt.s Lab5Decrypt.s
# Compile the required lab files, create a zip and then clean the .out files
all: compile 

# Compile first to verify they can, create directory for zipping
# copy all files to the directory then zip the file and the files from the directory
lab5zip : compile 
	mkdir lab5
	cp	$(labfiles) $(test_cases) $(expected) ./lab5
	zip lab5 ./lab5 ./lab5/*
	rm -rf *.out lab5

# compile additional assembly file to .out executable (if lab requires it)
compile: Lab5Encrypt.s Lab5Decrypt.s
	gcc -g $(word 1,$^) -o $(word 1,$(outputnames))
	gcc -g $(word 2,$^) -o $(word 2,$(outputnames))

#encrypt all the test cases
encrypt_test: compile
	$(word 1,$(outputnames)) < $(word 1, $(test_cases)) > $@1
	$(word 1,$(outputnames)) < $(word 2, $(test_cases)) > $@2
	$(word 1,$(outputnames)) < $(word 3, $(test_cases)) > $@3

# decrypt all the test cases
decrypt_test: encrypt_test 
	$(word 2,$(outputnames)) < $^1 > $@1
	$(word 2,$(outputnames)) < $^2 > $@2
	$(word 2,$(outputnames)) < $^3 > $@3

# did not make an expected for test two and the best test case
# simply because they weren't required for encryption
# but diff checking the decrypted version with the original
# should be good enough to tell whether it worked correctly or not
diff_test_encrypted: encrypt_test
	diff $^1 $(expected)

# encrypt all files, then decrypt all files, and then diff check all decrypted files
# with their original ones
diff_test_decrypted: encrypt_test decrypt_test
	diff $(word 2, $^1) $(word 1, $(test_cases))
	diff $(word 2, $^2) $(word 2, $(test_cases))
	diff $(word 2, $^3) $(word 3, $(test_cases))

# remove all .out and _test files
clean:
	rm -rf *.out *_test* 