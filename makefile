# Makefile for the smash program
CC = gcc
CXX = g++
RM = rm -f
CXXFLAGS = -g -Wall -std=c++11 -pthread
SRCS= main.cpp Account.cpp bank.cpp logs.cpp locker.cpp
OBJS = $(subst .cpp,.o,$(SRCS))

all:Bank
# Creating the  executable
Bank: $(OBJS)
	$(CXX) -pthread -o bank $(OBJS)
# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* core.*

