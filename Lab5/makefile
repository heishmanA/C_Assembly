# Makefile for easy testing

all: encrypt #decrypt

encrypt: 
	gcc -g Lab5Encrypt.s -o encrypt.out

run_tests: encrypt_file run_diff
		@echo "Test complete"

encrypt_file: encrypt
		encrypt.out < test_one > test_one_encrypted

run_diff: encrypt_file
		diff test_one_encrypted test_one_expected