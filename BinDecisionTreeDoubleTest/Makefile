CC = g++
CFLAGS=-c -w -O3
#SOURCES=functions.cpp BinDecisionTreeSimple.cpp
#SOURCES=functions.cpp BinDecisionTreeSimpleCompare.cpp
#SOURCES=functions.cpp BinDecisionTreeArray.cpp
#SOURCES=functions.cpp BinDecisionTreeArrayCompare.cpp
#SOURCES=functions.cpp BinDecisionTreeArraySwitch.cpp
#SOURCES=functions.cpp BinDecisionTreeFunctionCall.cpp
SOURCES=functions.cpp BinDecisionTreePath.cpp

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
