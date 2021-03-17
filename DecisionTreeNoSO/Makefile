CC = g++
CFLAGS=-c -w -O2
#SOURCES=functions.cpp DecisionTree.cpp
SOURCES=functions.cpp DecisionTreeUseRules.cpp
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=dtree

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -rf *o dtree
	rm -rf decisionTreeOutput.txt