PRG=gnu.exe
GCC=g++
MSC=cl
GCCFLAGS=-Wall -Wextra -ansi -pedantic -Wunused
DRIVER0=driver.cpp

VALGRIND_OPTIONS=-q --leak-check=full

MSCFLAGS=/EHa /W4 /Za /Zc:forScope /nologo /D_CRT_SECURE_NO_DEPRECATE /D"_SECURE_SCL 0" /O2i /GL

OSTYPE := $(shell uname)
ifeq (,$(findstring CYGWIN,$(OSTYPE)))
CYGWIN=
else
CYGWIN=-Wl,--enable-auto-import
endif


all: # used by online testing
	@echo Compile with C and C++
	gcc -c splitter.c $(GCCFLAGS)
	g++ -c driver.cpp $(GCCFLAGS)
	g++ -o $(PRG) splitter.o driver.o $(GCCFLAGS)

gcc_c:
	echo Compile all with C
	gcc -c splitter.c -Wall -Wextra -ansi -pedantic
	gcc -c driver.c -Wall -Wextra -ansi -pedantic
	gcc -o $@.exe splitter.o driver.o -Wall -Wextra -ansi -pedantic

gcc_c_cpp:
	echo Compile with C and C++
	gcc -c splitter.c -Wall -Wextra -ansi -pedantic
	g++ -c driver.cpp -Wall -Wextra  -ansi -pedantic
	g++ -o $@.exe splitter.o driver.o $(CYGWIN) -Wall -Wextra  -ansi -pedantic

gcc_cpp:
	echo Compile all with C++
	g++ -c splitter.c -Wall -Wextra -ansi -pedantic
	g++ -c driver.cpp -Wall -Wextra -ansi -pedantic
	g++ -o $@.exe splitter.o driver.o $(CYGWIN) -Wall -Wextra -ansi -pedantic

msc_c:
	echo compile all with C
	cl /D  "_CRT_SECURE_NO_DEPRECATE" /W4 /Za /TC splitter.c /c
	cl /D  "_CRT_SECURE_NO_DEPRECATE" /W4 /Za /TC driver.c /c
	cl /W4 /Fe$@.exe splitter.obj driver.obj

msc_c_cpp:
	echo compile with C and C++
	cl /D  "_CRT_SECURE_NO_DEPRECATE" /W4 /Za /TC splitter.c /c
	cl /D  "_CRT_SECURE_NO_DEPRECATE" /W4 /Za /TP /EHsc driver.cpp /c
	cl /W4 /Fe$@.exe splitter.obj driver.obj

msc_cpp:
	echo compile all with C++
	cl /D  "_CRT_SECURE_NO_DEPRECATE" /W4 /Za /TP splitter.c /c
	cl /D  "_CRT_SECURE_NO_DEPRECATE" /W4 /Za /TP /EHsc driver.cpp /c
	cl /W4 /Fe$@.exe splitter.obj driver.obj

0:
	@echo "Split 120-byte-file file into 100-byte pieces"
	rm -f studentout$@
	@echo "should run in less than 300 ms"
	./$(PRG) -s 100 -o test$@_ -i test0_input 2>>studentout$@
	ls test$@_???? >>studentout$@ 2>>studentout$@; echo 1
	diff test0_master_0001 test0_0001 >>studentout$@ 2>>studentout$@; echo 1
	diff test0_master_0002 test0_0002 >>studentout$@ 2>>studentout$@; echo 1
	diff out$@ studentout$@ --strip-trailing-cr > difference$@

1:
	@echo "Split 200-byte-file file into 100-byte pieces"
	@echo "should run in less than 300 ms"
	./$(PRG) -s 100 -o test$@_ -i test1_input 2>>studentout$@
	rm -f studentout$@
	ls test$@_???? >>studentout$@ 2>>studentout$@; echo 1
	diff test1_master_0001 test1_0001 >>studentout$@ 2>>studentout$@; echo 1
	diff test1_master_0002 test1_0002 >>studentout$@ 2>>studentout$@; echo 1
	diff out$@ studentout$@ --strip-trailing-cr > difference$@

2:
	@echo "Join 2 files"
	@echo "should run in less than 100 ms"
	./$(PRG) -j -o test2_student_output -i test2_input_1 test2_input_2 >/dev/null
	diff test2_student_output test2_master_joined >difference$@

mem0:
	@echo "running memory test when splitting 120-byte-file file into 100-byte pieces"
	@echo "should run in less than 2000 ms"
	valgrind $(VALGRIND_OPTIONS) ./$(PRG) -s 100 -o test$@_ -i test0_input 1>/dev/null 2>difference$@	
	@echo "lines after this are memory errors"; cat difference$@

mem1:
	@echo "running memory test when splitting 200-byte-file file into 100-byte pieces"
	@echo "should run in less than 2000 ms"
	valgrind $(VALGRIND_OPTIONS) ./$(PRG) -s 100 -o test$@_ -i test1_input 1>/dev/null 2>difference$@	
	@echo "lines after this are memory errors"; cat difference$@

mem2:
	@echo "running memory test when joining 2 files"
	@echo "should run in less than 2000 ms"
	valgrind $(VALGRIND_OPTIONS) ./$(PRG) -j -o test2_student_output -i test2_input_1 test2_input_2 1>/dev/null 2>difference$@	
	@echo "lines after this are memory errors"; cat difference$@

clean:
	rm -f *.exe *.tds *.o *.obj *manifest*
