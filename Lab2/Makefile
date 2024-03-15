CXX = gcc
EXECUTABLE = test

HOME = $(shell pwd)
CXXFLAGS = -I $(HOME)

BUILD_DIR = build/bin
OBJECTS_DIR = build
SOURCES = main.c list_stack.c tests.c arr_stack.c

OBJECTS = $(SOURCES:%.c=$(OBJECTS_DIR)/%.o)

.PHONY: all
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $^ -o $@ $(CXXFLAGS)

$(OBJECTS_DIR)/%.o : %.c
	$(CXX) -c $^ -o $@ $(CXXFLAGS)

.PHONY: clean makedirs

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS_DIR)/*.o

makedirs:
	mkdir -p $(BUILD_DIR)

