CXX=g++-9
CXXFLAGS=-I/usr/local/bin/include/ -Iinclude/ -std=c++1z -g -pipe
LDFLAGS=-L/usr/local/bin/lib
LDLIBS=-lslangcompiler -lslangparser -lslangcore

verigraph: