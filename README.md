# make-shared-object

Tutorial on how to build shared object code and link to it dynamically from a another C/C++ program. The following instructions and the example source files provided assume a Linux development platform.  

### Compile the library source files and create the object code.
g++ -c -Wall -Werror -fPIC lib_helloworld.cpp  
$ ls  
lib_helloworld.cpp  lib_helloworld.h  lib_helloworld.o  main.cpp  

### Create the shared object code (linking).
$ g++ -shared -Wl,-soname,libhelloworld.so.1 -o libhelloworld.so.1.0 lib_helloworld.o  
ls  
lib_helloworld.cpp  lib_helloworld.h  lib_helloworld.o  libhelloworld.so.1.0  main.cpp  

### Move the shared object to a custom location and create soft links to the libhelloworld.so.1.0 file.  
$ sudo mv libhelloworld.so.1.0 /opt/lib/  
$ sudo ln -sf /opt/lib/libhelloworld.so.1.0 /opt/lib/libhelloworld.so.1  
$ sudo ln -sf /opt/lib/libhelloworld.so.1 /opt/lib/libhelloworld.so  

### Compile and link the main program (driver to test the library code).  
$ g++ -Wall -Werror -L/opt/lib/ main.cpp -lhelloworld -o hello_program  
$ ls  
hello_program  lib_helloworld.cpp  lib_helloworld.h  lib_helloworld.o  main.cpp  

### Run the executable. This is a likely runtime error when running the executable for the first time.  
$ ./hello_program  
./hello_program: error while loading shared libraries: libhelloworld.so.1: cannot open shared object file: No such file or directory  
$ ldd hello_program  
	linux-vdso.so.1 (0x00007fff2abd7000)  
	libhelloworld.so.1 => not found  
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007ff5b9d79000)  
	/lib64/ld-linux-x86-64.so.2 (0x00007ff5b9f85000)  

### Add and export the shared object library path.  
$ LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/lib/  
$ export LD_LIBRARY_PATH  
$ ldd hello_program  
	linux-vdso.so.1 (0x00007fff3f7b2000)  
	libhelloworld.so.1 => /opt/lib/libhelloworld.so.1 (0x00007fb936d3a000)  
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fb936b35000)  
	libstdc++.so.6 => /lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007fb936954000)  
	libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007fb936939000)  
	/lib64/ld-linux-x86-64.so.2 (0x00007fb936d47000)  
	libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007fb9367ea000)  

### Run the executable again  
$ ./hello_program  
Hello shared obj World  
