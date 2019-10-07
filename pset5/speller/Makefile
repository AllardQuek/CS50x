# compiler to use
CC = clang

# flags to pass compiler
CFLAGS = -fsanitize=signed-integer-overflow -fsanitize=undefined -ggdb3 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wshadow

# name for executable
EXE = speller

# space-separated list of header files
HDRS = dictionary.h

# space-separated list of libraries, if any,
# each of which should be prefixed with -l; Odds are you won’t need to enumerate any libraries for this problem, but variable included in case.
LIBS =

# space-separated list of source files
SRCS = speller.c dictionary.c

# automatically generated list of object files
# defines variable OBJS, value of which == SRCS, except that each file’s extension is not .c but .o.
OBJS = $(SRCS:.c=.o)


# default target; tells make how to compile speller
$(EXE): $(OBJS) $(HDRS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

# dependencies; our .o files all "depend on" dictionary.h and Makefile so that changes to either induce recompilation of the former when you run make
$(OBJS): $(HDRS) Makefile

# housekeeping
clean:
	rm -f core $(EXE) *.o

# Welcome to modify this Makefile. You should if you created any .c or .h files. DO NOT change any tabs (i.e., \t) to spaces, since make expects the former to be present below each target.
# use: make speller OR make
# to delete speller plus any core or .o files: make clean