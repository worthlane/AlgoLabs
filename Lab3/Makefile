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
SOURCES = tester.c

SORTS_SOURCES = sorts/common.c sorts/intro_sorts.c sorts/merge_sorts.c sorts/MLSD_sorts.c \
				sorts/pyramid_sorts.c sorts/quadratic_sorts.c sorts/quick_part_sorts.c 	  \
				sorts/quick_pivots_sorts.c

SORTS_DIR = sorts

OBJECTS = $(SOURCES:%.c=$(OBJECTS_DIR)/%.o)
SORTS_OBJECTS = $(SORTS_SOURCES:$(SORTS_DIR)/%.c=$(OBJECTS_DIR)/%.o)

.PHONY: all
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(SORTS_OBJECTS)
	$(CXX) $^ -o $@ $(CXXFLAGS)

$(OBJECTS_DIR)/%.o : %.c
	$(CXX) -c $^ -o $@ $(CXXFLAGS)

$(OBJECTS_DIR)/%.o : $(SORTS_DIR)/%.c
	$(CXX) -c $^ -o $@ $(CXXFLAGS)

.PHONY: clean makedirs

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS_DIR)/*.o

makedirs:
	mkdir -p $(BUILD_DIR)
