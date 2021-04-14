#------------------------------------------------------------------------------
#  Makefile for List ADT
#  # 
#  make             makes poly
#  #  make clean       removes object files
#  make check       runs valgrind to check for memory errors
#  #
#  poly.c	this is where you put your application code
#  #  		i.e. polynomial multiplication.  there are
#  		some function stubs that you may need.
#  		#  List.h	given. you just need to include this in your .c files
#  List.c	this is where you implement the functions listed in
#  #  		List.h.  This is also where you would define ListObj
#------------------------------------------------------------------------------

poly:	poly.o List.o
	cc -o prog1 poly.o List.o -g 

poly.o: List.h poly.c
	cc -c poly.c -g

List.o: List.h List.c
	cc -c List.c -g

clean:
	rm -f poly poly.o List.o
