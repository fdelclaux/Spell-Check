#Makefile for p3
#COSC160

p3: p3.out
	
p3.out: p3.o hash.o 
	g++ -std=c++11 p3.o hash.o

p3.o: p3.cpp p3.h hash.h
	g++ -std=c++11 -c p3.cpp

hash.o: hash.cpp hash.h
	g++ -std=c++11 -c hash.cpp 
	
submit:
	rm -f submit.zip
	zip submit.zip p3.cpp p3.h hash.cpp hash.h Makefile

clean:
	rm -f *.o core p3.out