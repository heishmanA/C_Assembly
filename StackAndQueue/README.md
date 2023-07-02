# Stack/Queue project


## Description

This project was the 4th lab of my Systems I (CSE2421) course at OSU [hence why this is a private repostory]. All the functions in the header file were created by writing .java implementations of Queue and Stack and running them through a compiler that Braeden created himself that he calls 'Cavas'.

The point of this project was to create our own implementation of Stack and Queue. Stack.c and queue.c both contain my own implementation of each. However, there were two implementations for both. The first implementation of Stack and Queue were done with nodes, the second implementation of both were done with arrays.

This project uses command-line arguments, so it will require you to navigate to the specific folder destination that you have this installed. See 'How to Run for more' This should run natively on Linux based machines that have GNU / Make already [Windows users without these should check out the section 'Installation for Windows']



# How to run
- Neither main will include checks for non positive integer values, so if you enter these you'll more than likely segfault or have some undefined behavior
- Some functions include asserts (primarily dequeue/pop) to prevent certain edge cases, but not all [was not a requirement for this lab]
- Includes a clock timer that represents the total CPU_TIME for running [may not be the best way to test for efficiency]
- The optional step below refers to checking for leaks as this project required the use of malloc to allocate memory 
- May require the use of ./[executable] in order to run (depends on system and privilages)
- The program is written using regular integer values, so integers must be between [0, 2^31]
```
    1. Compile both main executable files and clean the object file [alternatively use make -r [queue_main] or make -r [stack_main] to install individually]
        $ make -r 
    2. Run by calling the specific file with command line arguments included, where x is a positive integer [the amount of entries to be pushed/queued]
        $ queue_main x 
        $ stack_main x
    
    Optional[Linux]: Check for leaks - x is a positive integer [the amount of entries to be pushed/queued]
        $ valgrind --leak-check = yes queue_main x
        $ valgrind --leak-check = yes stack_main x 

```

### Example input/output (using windows and queue)
```
    Input:
        C:/Users/UserName/StackAndQueue> ./queue_main 123456789
    Output:
        Testing Queue1 with 123456789 entries
        Ended with 0 errors
        Clock Time reads: 6.510000 seconds
        Testing Queue2 with 123456789 entries
        Clock Time reads: 1.115000 seconds
```
    


## This was written in ANSI-C [c89/c90] with specific flags. I'll provide a short explanation taken from the gnu.org website (link below)
```
    -ansi:                              Turns off certain features of GCC that are incompatible with ISO C89/90

    -Wpedantic                          Does not write a warning for alternate keywords wthat start/end with '__'

    -Wimplicit-function-declaration     Controls warnings when a declaration does not specify a type
    
    -Wreturn-type                       Controls warnings related to a non-void function without a return type
    
    -g                                  Allow for debugging with gdb
    -c                                  compile without linking
    -o                                  write the build output to an output file

    To read more about these flags use 
        [https://gcc.gnu.org/onlinedocs/gcc/C-Dialect-Options.html]
        [https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html]
        [https://www.intel.com/content/www/us/en/docs/cpp-compiler/developer-guide-reference/2021-8/wreturn-type.html]
        [https://www.rapidtables.com/code/linux/gcc.html]
```


#### Installation for windwows [requires these steps, then you can refer to the linux installation, just use a terminal/vscc to compile]
```
Useful links
For GNU/Mingw/Vscc Tutorial         https://code.visualstudio.com/docs/cpp/config-mingw
MSYS2/Mingw [for GNU/C/C++]         https://www.msys2.org/
For makefile                        https://earthly.dev/blog/makefiles-on-windows/
for chocolatey                      https://blog.chocolatey.org/2016/03/celebrating-5-years/
```

#### Installing MINGW to access GNU
```bash
    
    1. Download MSYS2 - https://github.com/msys2/msys2-installer/releases/download/2023-05-26/msys2-x86_64-20230526.exe
    2. Run the installer
    3. Open the MSYS2 URT64 shell and use the following command to install GNU
        - pacman -S mingw-w64-ucrt-x86_64-gcc
    3. Press enter after all packages show up to install all the packages
    4. After installation install the Mingw-w64 toolchain using MSYS2
        - pacman -S --needed base-devel mingw-w64-x86_64-toolchain
    5. Add the Mingw-w64 bin folder to your PATH environment (isntructions on the VSCC Tutorial)
    6. After adding Mingw-w64 to path you should be able to use gcc in your terminal (may require you to reopen a terminal if you have one open already)
        - gcc --verison
        - g++ --version
        - gdb --version
```

#### Installing chocolatey for makefile
```bash
    1. Open PowerShell with Administrative Privilages and use the following command to install chocolatey
        - Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
    2. After this installation is done run the following command in the PowerShell to install the required files to run make
        - choco install make
    3. Check to make sure that make was installed correctly using the following command
        - make -verison
```

# Aknowledgements
- The original idea, the main file and the header for this project was supplied by Braeden Jeske [https://github.com/braedenjeske]. I took the main file that was supplied by Braeden and broke it into two parts for easier testing.
