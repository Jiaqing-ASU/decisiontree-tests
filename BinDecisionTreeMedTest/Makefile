CC = g++
CFLAGS=-c -w -O3
SOURCES=functions.cpp BinDecisionTreeArray.cpp
#SOURCES=functions.cpp BinDecisionTreePointer.cpp
#SOURCES=functions.cpp BinDecisionTreePath.cpp
#SOURCES=functions.cpp BinDecisionTreeSpecialized.cpp

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
