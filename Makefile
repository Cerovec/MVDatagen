#-------------------------------------------------------------------------------
# TOOLS
#-------------------------------------------------------------------------------

CXX := ccache g++
LD := g++
RM := @rm -rf
SHELL := /bin/bash

#-------------------------------------------------------------------------------
# BUILD OPTIONS
#-------------------------------------------------------------------------------

# Executable name
EXECUTABLE := MVDatagen

# Source root folder
SOURCEROOT := Source

# Directories with sources
SOURCEDIRS := $(SOURCEROOT) $(SOURCEROOT)/Marker $(SOURCEROOT)/Generator $(SOURCEROOT)/Utils

# Intermediate and output files are placed into BUILDDIR
BUILDDIR := Build

# Defined macros
MACROS := DEBUG IMSHOW

# Include folders
INCLUDES := $(SOURCEROOT) /usr/local/include

# Additional compiler flags
CXXFLAGS := -O0 -Wall

# Library search folders
LDPATHS := /usr/local/lib

# Libraries linked
LIBS := opencv_core opencv_highgui opencv_imgproc

# Additional linker flags
LDFLAGS := 

#-------------------------------------------------------------------------------
# HELPER VARIABLES
#-------------------------------------------------------------------------------

# Dummy file that marks created build directories
DIRS_CREATED := $(BUILDDIR)/.null

# Finds all source files in source directories
SOURCES := $(foreach DIR, $(SOURCEDIRS), $(wildcard $(DIR)/*.cpp))

# Calculates the object file for every source file
OBJECTS := $(addprefix $(BUILDDIR)/, $(SOURCES:.cpp=.o))

# Calculates the dependency file for every source file
DEPENDENCIES := $(OBJECTS:.o=.d)

#-------------------------------------------------------------------------------
# RULES
#-------------------------------------------------------------------------------

all: $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS)
	@echo '[Building target: $@]'
	@echo '[Invoking: $(LD) Linker]'
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@ \
		$(foreach LIB, $(LIBS), -l $(LIB)) \
		$(foreach LDPATH, $(LDPATHS), -L $(LDPATH))
	@echo '[Finished building target: $@]'
	@echo ' '
	
$(DIRS_CREATED):
	@echo '[Creating dirs]' 
	@mkdir -p $(BUILDDIR)
	@touch $(DIRS_CREATED)
	@echo '[Finished creating dirs]'

$(BUILDDIR)/%.o: %.cpp $(DIRS_CREATED)
	@echo '[Compiling file: $<]'
	@echo '[Invoking: $(CXX) Compiler]'
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@ \
		$(foreach INC, $(INCLUDES), -I $(INC)) \
		$(foreach MACRO, $(MACROS), -D $(MACRO))
	@echo '[Finished compiling: $<]'
	@echo ' '
	
.PHONY : clean
clean:
	@echo '[Cleaning...]'
	$(RM) $(BUILDDIR) $(EXECUTABLE)
	@echo '[Finished]'
	
-include $(DEPENDENCIES)