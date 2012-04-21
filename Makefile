CC := ccache g++
LD := g++
RM := rm -rf

OBJECTS_DIR := Objects
SOURCE_DIR := Source

CFLAGS := -O0 -Wall -DDEBUG -DIMSHOW
LDFLAGS := -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc 
INCLUDES := -I$(SOURCE_DIR) -I/usr/local/include

SOURCES = $(wildcard $(SOURCE_DIR)/*.cpp) $(wildcard $(SOURCE_DIR)/*/*.cpp) $(wildcard $(SOURCE_DIR)/*/*/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS := $(subst $(SOURCE_DIR), $(OBJECTS_DIR), $(OBJECTS))
DIRS_CREATED = $(OBJECTS_DIR)/.null

EXECUTABLE = MVDatagen
    
$(EXECUTABLE): $(OBJECTS)
	@echo 'Building target: $@'
	@echo 'Invoking: $(LD) Linker'
	$(LD) $(OBJECTS) -o $@ $(LDFLAGS)
	
$(DIRS_CREATED):
	@mkdir -p $(OBJECTS_DIR)
	@touch $(DIRS_CREATED)

$(OBJECTS_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(DIRS_CREATED)
	@echo 'Building target: $@'
	@echo 'Invoking: $(CC) Compiler'
	@echo $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

all: $(EXECUTABLE)
	
.PHONY : clean
clean:
	@echo 'Cleaning target'
	$(RM) $(OBJECTS_DIR) $(EXECUTABLE)