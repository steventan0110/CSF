CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g 
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

ALL=cache

all: $(ALL)

cache: cache.o caching.o DIR_caching.o ASS_caching.o SET_caching.o BLK_caching.o NWA_caching.o PRF_caching.o
	g++ -o cache cache.o caching.o DIR_caching.o ASS_caching.o SET_caching.o BLK_caching.o NWA_caching.o PRF_caching.o


caching.o: caching.cpp caching.hpp 
	g++ -c caching.cpp $(CFLAGS)

DIR_caching.o: DIR_caching.cpp DIR_caching.hpp caching.hpp
	g++ -c DIR_caching.cpp $(CFLAGS)

ASS_caching.o: ASS_caching.cpp ASS_caching.hpp caching.hpp
	g++ -c ASS_caching.cpp $(CFLAGS)

SET_caching.o: SET_caching.cpp SET_caching.hpp caching.hpp
	g++ -c SET_caching.cpp $(CFLAGS)

BLK_caching.o: BLK_caching.cpp BLK_caching.hpp caching.hpp
	g++ -c BLK_caching.cpp $(CFLAGS)

NWA_caching.o: NWA_caching.cpp NWA_caching.hpp caching.hpp
	g++ -c NWA_caching.cpp $(CFLAGS)

PRF_caching.o: PRF_caching.cpp PRF_caching.hpp caching.hpp
	g++ -c PRF_caching.cpp $(CFLAGS)

.PHONY: clean
clean:
	rm -f *.o cache
