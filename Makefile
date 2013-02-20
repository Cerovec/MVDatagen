#-------------------------------------------------------------------------------
# PREREQUISITES
#-------------------------------------------------------------------------------

# Other makefiles to include

#-------------------------------------------------------------------------------
# TOOLS
#-------------------------------------------------------------------------------

ifdef CLANG
CXX := ccache clang++
LD := clang++
else
CXX := ccache g++
LD := g++
endif
AR := ar
RM := @rm -rf
SHELL := /bin/bash

#-------------------------------------------------------------------------------
# BUILD OPTIONS
#-------------------------------------------------------------------------------

# Project name
PROJNAME := MVDatagen

# Source root folder
SOURCEROOT := Source

# Sourcefiles extension
EXTENSION := cpp

# Directories with sources
SOURCEDIRS := $(SOURCEROOT) $(SOURCEROOT)/Marker $(SOURCEROOT)/Generator $(SOURCEROOT)/Utils $(SOURCEROOT)/Gpu

# Intermediate and output files are placed into BUILDDIR
BUILDDIR := Build

# Defined macros
MACROS := DEBUG IMSHOW

ifdef GPU
MACROS += USE_GPU_DEWARP
endif

ifdef LOG_LEVEL
MACROS += LOG_LEVEL=$(LOG_LEVEL)
endif

ifdef TIMER_ENABLED
MACROS += TIMER_ENABLED
endif

# Include folders
INCLUDES += $(SOURCEROOT) /opt/local/include /usr/local/include ../CoreUtils/Source ../GPUMVToolset/Source ../MVToolset/Source

# Additional compiler flags
CXXFLAGS := -O0 -Wall -g3 -fPIC

ifdef CLANG
CXXFLAGS += -Wno-overloaded-virtual
endif

# Library search folders
LDPATHS += 	/usr/local/lib /opt/local/lib /usr/lib \
			../GPUMVToolset/Build ../CoreUtils/Build \
			../MVToolset/Build

# Libraries linked
LIBS += MVToolset GPUMVToolset 

ifdef MACOS
else
ifdef GLX
LIBS += GL X11
else
LIBS += GLESv2 EGL
endif
endif

ifdef GLX
MACROS += USE_GLX
endif

LIBS += CoreUtils opencv_core opencv_highgui opencv_imgproc 

# Additional linker flags
ifdef MACOS
LDFLAGS := -framework OpenGL -framework Foundation -framework AppKit
else
LDFLAGS :=
endif

DEPLIBS := 	../GPUMVToolset/Build/libGPUMVToolset.a \
			../CoreUtils/Build/libCoreUtils.a \
			../MVToolset/Build/libMVToolset.a

#-------------------------------------------------------------------------------
# HELPER VARIABLES
#-------------------------------------------------------------------------------

# Executable name
EXECUTABLE := $(BUILDDIR)/$(PROJNAME)

# Library name
LIBRARY := $(BUILDDIR)/lib$(PROJNAME).a

# Finds all source files in source directories
SOURCES += $(foreach DIR, $(SOURCEDIRS), $(wildcard $(DIR)/*.$(EXTENSION)))

# Calculates the object file for every source file
OBJECTS := $(addprefix $(BUILDDIR)/, $(SOURCES:.$(EXTENSION)=.o))

# Calculates the dependency file for every source file
DEPENDENCIES += $(OBJECTS:.o=.d)

# Dummy file that marks created build directories
DIRS_CREATED := $(BUILDDIR)/.null

#-------------------------------------------------------------------------------
# RULES
#-------------------------------------------------------------------------------

# Builds the projects
all: $(EXECUTABLE) $(LIBRARY)
    
# Creates executable file
$(EXECUTABLE): $(OBJECTS)
	@echo '$(LD): $(PROJNAME) => $@'
	@$(LD) $(LDFLAGS) $(OBJECTS) -o $@ \
		$(foreach LIB, $(LIBS), -l $(LIB)) \
		$(foreach LDPATH, $(LDPATHS), -L $(LDPATH))
	
$(LIBRARY): $(OBJECTS)
	@echo '$(AR): $(PROJNAME) => $@'
	@$(AR) rcs $(LIBRARY) $(OBJECTS)
	
$(DIRS_CREATED):
	@echo '[Creating dirs]' 
	@-if [ ! -e $(BUILDDIR) ]; then mkdir -p $(BUILDDIR); fi; 
	@-$(foreach DIR, $(SOURCEDIRS), if [ ! -e $(BUILDDIR)/$(DIR) ]; \
		then mkdir -p $(BUILDDIR)/$(DIR); fi; )
	@touch $(DIRS_CREATED)

$(BUILDDIR)/%.o: %.$(EXTENSION) $(DIRS_CREATED)
	@echo '$(CXX): $(PROJNAME) <= $<'
	@$(CXX) $(CXXFLAGS) -MMD -c $< -o $@ \
		$(foreach INC, $(INCLUDES), -I $(INC)) \
		$(foreach MACRO, $(MACROS), -D $(MACRO))
	
.PHONY: clean
clean:
	@echo '[Cleaning]'
	$(RM) $(BUILDDIR)
	
-include $(DEPENDENCIES)