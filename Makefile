#-------------------------------------------------------------------------------
# BUILD OPTIONS
#-------------------------------------------------------------------------------

# Project name
PROJNAME := MVDatagen

# On which projects this project depends
DEPENDS := GPUMVToolset MVToolset CoreUtils

# Source root folder
SOURCEROOT := Source

include ../my_settings.mk
include ../common_settings.mk
include ../common_build.mk

# Builds the projects
all: $(EXECUTABLE) $(LIBRARY)