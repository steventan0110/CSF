CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g 
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

branch: branch.o Predictor.o STA_Predictor.o BAH_Predictor.o TAH_Predictor.o BTA_Predictor.o SAT_Predictor.o COL_Predictor.o TWO_Predictor.o
	g++ -o branch branch.o Predictor.o STA_Predictor.o BAH_Predictor.o TAH_Predictor.o BTA_Predictor.o SAT_Predictor.o COL_Predictor.o TWO_Predictor.o

STA_Predictor.o: STA_Predictor.cpp STA_Predictor.hpp Predictor.hpp
	g++ -c STA_Predictor.cpp $(CFLAGS)

BAH_Predictor.o: BAH_Predictor.cpp BAH_Predictor.hpp Predictor.hpp
	g++ -c BAH_Predictor.cpp $(CFLAGS)

TAH_Predictor.o: TAH_Predictor.cpp TAH_Predictor.hpp Predictor.hpp
	g++ -c TAH_Predictor.cpp $(CFLAGS)

BTA_Predictor.o: BTA_Predictor.cpp BTA_Predictor.hpp Predictor.hpp
	g++ -c BTA_Predictor.cpp $(CFLAGS)

COL_Predictor.o: COL_Predictor.cpp COL_Predictor.hpp Predictor.hpp
	g++ -c COL_Predictor.cpp $(CFLAGS)

SAT_Predictor.o: SAT_Predictor.cpp SAT_Predictor.hpp Predictor.hpp
	g++ -c SAT_Predictor.cpp $(CFLAGS)

TWO_Predictor.o: TWO_Predictor.cpp TWO_Predictor.hpp Predictor.hpp
	g++ -c TWO_Predictor.cpp $(CFLAGS)

Predictor.o: Predictor.cpp Predictor.hpp
	g++ -c Predictor.cpp $(CFLAGS)


.PHONY: clean
clean:
	rm -f *.o branch
