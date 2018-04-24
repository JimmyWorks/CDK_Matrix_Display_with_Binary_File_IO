#   Program 6
#   Author: Jimmy Nguyen
#   Email: tbn160230@utdallas.edu | Jimmy@JimmyWorks.net
#   CS 3377.502 Programming in UNIX Environment
#   University of Texas at Dallas
#
#   Description:
#   Makefile for Program 6: Binary File I/O Visualization
#   Commands:
#   make		Make all executables.
#   make clean		Clean all intermediate files
#   make backup 	Make a backup of the current project

# Project name for make backup
PROJECTNAME = Program6

#
# ATTENTION!!
# The two variables below must be changed to your library
# and header directories for CDK
#
CDK_LIB = /scratch/perkins/lib
CDK_HEAD = /scratch/perkins/include

# Filenames
 # Source
SRCS = program6.cc \
       binaryIO.cc

# Executables
EXE = program6
 # Input and Output
INPUTFILE = cs3377.bin

# Compilers and Flags

CXX = g++
CXXFLAGS = -Wall -g -std=c++11 
CPPFLAGS = -Wall -I./include/ -I$(CDK_HEAD) -std=c++11
LDFLAGS = -L$(CDK_LIB)
LDLIBS = -lcdk -lcurses

# Make Targets
OBJS=$(SRCS:cc=o)

 # make
all: $(EXE) 

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(LDLIBS) 

 # make clean
clean: 
	rm -f *.o $(EXE) *.d*

 # make test
#test:

Makefile: $(SRCS:.c=.d)

 # Pattern for .d files.
%.d:%.cc
	@echo Updating .d Dependency File
	@set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

 # make backup (Backup Target)
backup: clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!


 # Include the dependency files
-include $(SRCS:.cc=.d)


