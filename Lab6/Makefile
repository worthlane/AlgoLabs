CXX = gcc
EXECUTABLE = test
CXXFLAGS =  -D _DEBUG -ggdb3 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations \
			-Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts       \
			-Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal  \
			-Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline          \
			-Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked            \
			-Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo  \
			-Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn                \
			-Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default      \
			-Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast           \
			-Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing   \
			-Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation    \
			-fstack-protector -fstrict-overflow -fno-omit-frame-pointer -Wlarger-than=8192         \
			-Wstack-usage=8192 -fPIE -Werror=vla

HOME = $(shell pwd)
CXXFLAGS += -I $(HOME)

BUILD_DIR = build/bin
OBJECTS_DIR = build

SOURCES = main.c testing.c
OBJECTS = $(SOURCES:%.c=$(OBJECTS_DIR)/%.o)

TREE_DIR = trees
TREE_SRC = avl.c treap.c splay.c bst.c
TREE_OBJ = $(TREE_SRC:%.c=$(OBJECTS_DIR)/%.o)

#LAUNCH_DIR = launch
#LAUNCH_SRC = load_factor_test.c research_func.c ideal_hash_research.c
#LAUNCH_OBJ = $(LAUNCH_SRC:%.c=$(OBJECTS_DIR)/%.o)

GEN_DIR = tests

ARR_GEN = arrgen
ARR_SRC = arraygen.c
ARR_OBJ = $(ARR_SRC:%.c=$(OBJECTS_DIR)/%.o)

.PHONY: all
all: $(EXECUTABLE) $(GEN_DIR)/$(ARR_GEN)

$(GEN_DIR)/$(ARR_GEN): $(ARR_OBJ)
	$(CXX) $^ -o $@ $(CXXFLAGS)

$(OBJECTS_DIR)/%.o : $(GEN_DIR)/%.c
	$(CXX) -c $^ -o $@ $(CXXFLAGS)

$(EXECUTABLE): $(TREE_OBJ) $(OBJECTS)
	$(CXX) $^ -o $@ $(CXXFLAGS)

$(OBJECTS_DIR)/%.o : $(TREE_DIR)/%.c
	$(CXX) -c $^ -o $@ $(CXXFLAGS)

$(OBJECTS_DIR)/%.o : %.c
	$(CXX) -c $^ -o $@ $(CXXFLAGS)


.PHONY: clean makedirs

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS_DIR)/*.o $(GEN_DIR)/$(ARR_GEN)

makedirs:
	mkdir -p $(BUILD_DIR)

