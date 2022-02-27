CXXFLAGS = -g -Wall -O0 -std=c++2a -fsanitize=address -fsanitize=undefined
LDFLAGS = -lasan -lubsan -lpthread -lgmock -lgtest

PROJDIR := $(realpath $(CURDIR)/..)
SOURCEDIR := $(PROJDIR)/src
BUILDDIR := $(PROJDIR)/build

TARGET = coinche

VERBOSE = TRUE

DIRS = .
SOURCEDIRS = $(foreach dir, $(DIRS), $(addprefix $(SOURCEDIR)/, $(dir)))
TARGETDIRS = $(foreach dir, $(DIRS), $(addprefix $(BUILDDIR)/, $(dir)))

# Generate the GCC includes parameters by adding -I before each source folder
INCLUDES = $(foreach dir, $(SOURCEDIRS), $(addprefix -I, $(dir)))

# Add this list to VPATH, the place make will look for the source files
VPATH = $(SOURCEDIRS)

SOURCES = $(foreach dir,$(SOURCEDIRS),$(wildcard $(dir)/*.cc))

OBJS := $(subst $(SOURCEDIR),$(BUILDDIR),$(SOURCES:.cc=.o))

DEPS = $(OBJS:.o=.d)

# Name the compiler
CXX = g++

SEP=/

# Remove space after separator
PSEP = $(strip $(SEP))

# Hide or not the calls depending of VERBOSE
ifeq ($(VERBOSE),TRUE)
    HIDE =  
else
    HIDE = @
endif

# Define the function that will generate each rule
define generateRules
$(1)/%.o: %.cc
	@echo Building $$@
	$(HIDE)$(CXX) $(CXXFLAGS) -c $$(INCLUDES) -o $$@ $$< -MP -MMD
endef

.PHONY: all clean directories 

all: directories $(TARGET)

$(info [${TARGET}])
$(TARGET): $(OBJS)
	$(HIDE)echo Linking $@
	$(HIDE)$(CXX)  $(OBJS) -o $(TARGET) $(LDFLAGS)

# Include dependencies
-include $(DEPS)

# Generate rules
$(foreach targetdir, $(TARGETDIRS), $(eval $(call generateRules, $(targetdir))))

directories: 
	$(HIDE)mkdir -p $(subst /,$(PSEP),$(TARGETDIRS)) 2> /dev/null

# Remove all objects, dependencies and executable files generated during the build
clean:
	$(HIDE)rm -rf $(subst /,$(PSEP),$(TARGETDIRS)) 2> /dev/null
	$(HIDE)rm -rf $(TARGET) $(ERRIGNORE)
	@echo Cleaning done ! 
