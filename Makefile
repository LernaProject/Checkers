.PHONY: all clean

BUILD = bin

HEADERS := $(wildcard *.h)
OBJECTS := $(foreach EXT,cpp sh,$(patsubst %.$(EXT),$(BUILD)/%,$(wildcard *.$(EXT))))
OBJECTS := $(filter-out $(BUILD)/float,$(OBJECTS))
OBJECTS += $(foreach N,$(shell seq 1 10),$(BUILD)/float$N)
CXXFLAGS := -std=c++11 -O2
CXXFLAGS += -Wall -Wextra -pedantic -Wformat=2 -Wfloat-equal -Wlogical-op -Wredundant-decls
CXXFLAGS += -Wconversion -Wcast-qual -Wcast-align -Wuseless-cast -Wno-unused-local-typedefs

define abbrev
	@echo $1 ...
	@$1 $2
endef

all: $(OBJECTS)

$(BUILD)/%: %.cpp $(HEADERS)
	@mkdir -p $(@D)
	$(call abbrev,g++ $< -o $@,$(CXXFLAGS))

$(BUILD)/float%: float.cpp $(HEADERS)
	@mkdir -p $(@D)
	$(call abbrev,g++ $< -o $@ -DPREC=$*,$(CXXFLAGS))

$(BUILD)/%: %.sh
	@mkdir -p $(@D)
	ln -s ../$< $@

clean:
	rm -rf $(BUILD)
