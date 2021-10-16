SRCDIR = src
OBJDIR = obj

CC = g++
CXXFLAGS = -g -Wall -O3


STRUCTURE := $(shell find $(SRCDIR) -type d)

CODEFILES := $(addsuffix /*,$(STRUCTURE))
CODEFILES := $(wildcard $(CODEFILES))

# Filter Only Specific Files
SRCFILES := $(filter %.cc,$(CODEFILES))
HDRFILES := $(filter %.hh,$(CODEFILES))
OBJFILES := $(subst $(SRCDIR),$(OBJDIR),$(SRCFILES:%.cc=%.o))

# Filter Out Function main for Libraries
LIBDEPS := $(filter-out $(OBJDIR)/main.o,$(OBJFILES))

$(OBJDIR)/%.o: $(addprefix $(SRCDIR)/,%.cc %.hh)
	    $(CC) -c $< -o $@ $(CFLAGS)

compile: $(OBJFILES)
	$(CC) -o coinche $^

#phony : always evaluated (even if the dependencies are up to date)
.PHONY: clean

clean:
	    -rm -r $(OBJDIR)/*
