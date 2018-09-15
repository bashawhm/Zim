CC = clang++
CFLAGS += -pipe -std=c++17 -g -march=native -Wall -Wextra -O3 
#LDFLAGS +=  

TARGET := zim

SRC := main.cpp program.cpp builtin.cpp

DEPS := $(addprefix .build/,$(SRC:.cpp=.d))
OBJS := $(addprefix .build/,$(SRC:.cpp=.o))

.SUFFIXES:
.PRECIOUS: %/.dir
.PHONY: all clean depend
.DEFAULT: all

all: $(TARGET)
depend: $(DEPS)

$(TARGET): $(OBJS) $(DIR)
	@echo "LD $@"
	@$(CC) -o $@ $(OBJS) $(LDFLAGS)

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPS)
endif

.build/%.o: src/%.cpp .build/%.d .build/.dir
	@echo "CC $(@F)"
	@$(CC) $(CFLAGS) -c -o $@ $<

.build/%.d: src/%.cpp .build/.dir
	@echo "DEP $(@F)"
	@$(CC) $(CFLAGS) -M -MP -MT $(subst .cpp,.o,$(subst src/,.build/,$<)) $< > $@ 2>/dev/null

%/.dir:
	@echo "MKDIR $(@D)"
	@mkdir -p "$(@D)"
	@touch "$@"

clean:
	-rm -rf .build $(TARGET)
