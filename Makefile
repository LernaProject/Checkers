.PHONY: all clean

SRC   := src
BUILD := bin

HEADERS := $(wildcard $(SRC)/*.h)
OBJECTS := $(foreach EXT,cpp sh,$(patsubst $(SRC)/%.$(EXT),$(BUILD)/%,$(wildcard $(SRC)/*.$(EXT))))
OBJECTS := $(filter-out $(BUILD)/float,$(OBJECTS))
OBJECTS += $(foreach N,$(shell seq 1 10),$(BUILD)/float$N)
CXXFLAGS := -std=c++11 -O2
CXXFLAGS += -Wall -Wextra -pedantic -Wformat=2 -Wfloat-equal -Wlogical-op -Wredundant-decls
CXXFLAGS += -Wconversion -Wcast-qual -Wcast-align -Wuseless-cast -Wno-unused-local-typedefs

define abbrev
	@echo $1 ...
	@$1 $2
endef

all: $(OBJECTS) $(BUILD)/ok

$(BUILD)/%: $(SRC)/%.cpp $(HEADERS)
	@mkdir -p $(@D)
	$(call abbrev,$(CXX) $< -o $@,$(CXXFLAGS))

$(BUILD)/float%: $(SRC)/float.cpp $(HEADERS)
	@mkdir -p $(@D)
	$(call abbrev,$(CXX) $< -o $@ -DPREC=$*,$(CXXFLAGS))

$(BUILD)/%: $(SRC)/%.sh
	@mkdir -p $(@D)
	ln -sf ../$< $@

$(BUILD)/ok: $(shell which true)
	@mkdir -p $(@D)
	ln -sf $< $@

clean:
	rm -rf $(BUILD)
