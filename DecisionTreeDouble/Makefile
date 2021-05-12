CC = g++
CFLAGS=-c -w -O3
SOURCES=functions.cpp DecisionTree.cpp
#SOURCES=functions.cpp DecisionTreeUseRules.cpp
#SOURCES=functions.cpp DecisionTreeUseSepRules.cpp
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=dtree

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -g $< -o $@
clean:
	rm -rf *o dtree
	rm -rf decisionTreeOutput.txt
