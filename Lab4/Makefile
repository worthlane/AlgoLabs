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

SOURCES = testing.c

OBJECTS = $(SOURCES:%.c=$(OBJECTS_DIR)/%.o)

HEAPS_DIR = heaps
HEAPS_SRC = common.c binheap.c
HEAPS_OBJ = $(HEAPS_SRC:%.c=$(OBJECTS_DIR)/%.o)

ARR_GEN = arrgen
GEN_DIR = tests
GEN_SRC = arraygen.c
GEN_OBJ = $(GEN_SRC:%.c=$(OBJECTS_DIR)/%.o)

HEAPARR = arrheap
HEAPARR_DIR = tests
HEAPARR_SRC = arrayheapify.c
HEAPARR_OBJ = $(HEAPARR_SRC:%.c=$(OBJECTS_DIR)/%.o)


.PHONY: all
all: $(EXECUTABLE) $(GEN_DIR)/$(ARR_GEN) $(HEAPARR_DIR)/$(HEAPARR)

$(HEAPARR_DIR)/$(HEAPARR): $(HEAPARR_OBJ) $(HEAPS_OBJ)
	$(CXX) $^ -o $@ $(CXXFLAGS)

$(OBJECTS_DIR)/%.o : $(HEAPARR_DIR)/%.c
	$(CXX) -c $^ -o $@ $(CXXFLAGS)

$(GEN_DIR)/$(ARR_GEN): $(GEN_OBJ)
	$(CXX) $^ -o $@ $(CXXFLAGS)

$(OBJECTS_DIR)/%.o : $(GEN_DIR)/%.c
	$(CXX) -c $^ -o $@ $(CXXFLAGS)

$(EXECUTABLE): $(OBJECTS) $(HEAPS_OBJ)
	$(CXX) $^ -o $@ $(CXXFLAGS)

$(OBJECTS_DIR)/%.o : $(HEAPS_DIR)/%.c
	$(CXX) -c $^ -o $@ $(CXXFLAGS)

$(OBJECTS_DIR)/%.o : %.c
	$(CXX) -c $^ -o $@ $(CXXFLAGS)


.PHONY: clean makedirs

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS_DIR)/*.o $(GEN_DIR)/$(ARR_GEN)

makedirs:
	mkdir -p $(BUILD_DIR)


