SRCDIR = src
OBJDIR = obj

CC = g++
CXXFLAGS = -g -Wall -O0 -std=c++2a -fsanitize=address -fsanitize=undefined -MP -MMD
LD_FLAGS = -lasan -lubsan -lpthread -lgmock -lgtest


STRUCTURE := $(shell find $(SRCDIR) -type d)

CODEFILES := $(addsuffix /*,$(STRUCTURE))
CODEFILES := $(wildcard $(CODEFILES))

# Filter Only Specific Files
SRCFILES := $(filter %.cc,$(CODEFILES))
HDRFILES := $(filter %.hh,$(CODEFILES))
OBJFILES := $(subst $(SRCDIR),$(OBJDIR),$(SRCFILES:%.cc=%.o))
DEPFILES := $(OBJFILES:.o=.d)

# Filter Out Function main for Libraries
LIBDEPS := $(filter-out $(OBJDIR)/main.o,$(OBJFILES))

$(OBJDIR)/%.o: $(addprefix $(SRCDIR)/,%.cc %.hh)
	    $(CC) -c $< -o $@ $(CXXFLAGS)

-include $(DEPFILES)

compile: $(OBJFILES)
	$(CC) -o coinche $^ $(LD_FLAGS)

#phony : always evaluated (even if the dependencies are up to date)
.PHONY: clean

clean:
	    -rm -r $(OBJDIR)/*
