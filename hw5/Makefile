CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g 
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

ALL=cache

all: $(ALL)

cache: cache.o caching.o DIR_caching.o
	g++ -o cache cache.o caching.o DIR_caching.o

# cache.o: cache.cpp DIR_caching.hpp caching.hpp
# 	g++ -c cache.cpp $(CFLAGS)

caching.o: caching.cpp caching.hpp 
	g++ -c caching.cpp $(CFLAGS)

DIR_caching.o: DIR_caching.cpp DIR_caching.hpp caching.hpp
	g++ -c DIR_caching.cpp $(CFLAGS)

.PHONY: clean
clean:
	rm -f *.o cache
