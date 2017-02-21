# Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
# Time-stamp: <2017-02-21 15:18:58 (jmiller)>

# The default compiler and flags
CXX = mpic++
CXXFLAGS = -Wall -O3
BINARIES = basic_comm_test.bin
LIBRARIES = 

default: all
all: basic_comm_test

basic_comm_test: basic_comm_test.bin
basic_comm_test.bin: basic_comm_test.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: default all basic_comm_test
clean:
	$(RM) ${BINARIES} ${LIBRARIES}
