CXX = gcc
EXECUTABLE = test

HOME = $(shell pwd)
CXXFLAGS = -I $(HOME)

BUILD_DIR = build/bin
OBJECTS_DIR = build
SOURCES = main.c tests.c

LIST_SOURCES = list/list_stack.c
ARR_SOURCES  = array/arr_stack.c

LIST_DIR = list
ARR_DIR = array

OBJECTS = $(SOURCES:%.c=$(OBJECTS_DIR)/%.o)
LIST_OBJECTS = $(LIST_SOURCES:$(LIST_DIR)/%.c=$(OBJECTS_DIR)/%.o)
ARR_OBJECTS = $(ARR_SOURCES:$(ARR_DIR)/%.c=$(OBJECTS_DIR)/%.o)

.PHONY: all
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(ARR_OBJECTS) $(LIST_OBJECTS)
	$(CXX) $^ -o $@ $(CXXFLAGS)

$(OBJECTS_DIR)/%.o : %.c
	$(CXX) -c $^ -o $@ $(CXXFLAGS)

$(OBJECTS_DIR)/%.o : $(LIST_DIR)/%.c
	$(CXX) -c $^ -o $@ $(CXXFLAGS)

$(OBJECTS_DIR)/%.o : $(ARR_DIR)/%.c
	$(CXX) -c $^ -o $@ $(CXXFLAGS)


.PHONY: clean makedirs

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS_DIR)/*.o

makedirs:
	mkdir -p $(BUILD_DIR)

