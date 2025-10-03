CXX = g++
CPPFLAGS = -I./
CXXFLAGS = -std=gnu++20 -O2 -g

all: A.out B.out whiteman.out amicable.out

args.o: args.c++ args.h++
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -c $<

set.o: set.c++ set.h++
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -c $<

A.out: A.c++ args.h++ args.o
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o $@ $< args.o -lcombinat -lfftw3 -lm

B.out: B.c++ args.h++ args.o
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o $@ $< args.o -lcombinat -lfftw3 -lm

whiteman.out: whiteman.c++ sequence.h++
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o $@ $<

amicable.out: amicable.c++ set.o
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o $@ $< set.o

.PHONY: clean clean-all

clean:
	-rm -f *.o

clean-all:
	find -type f \( -executable -o -name "*.o" \) -delete
