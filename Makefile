EXEDIR := build
OBJDIR := obj
SRCDIR := engine/src

EXE := $(EXEDIR)/game.exe
LOG := $(wildcard $(EXEDIR)/*.log)
SRC := $(shell find $(SRCDIR) -name *.cpp)
OBJ := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))

CPPFLAGS := -I$(SRCDIR)
CPPFLAGS += -Iengine/include
CPPFLAGS += -Iengine/json/single_include
CPPFLAGS += -Iengine/type_safe/include
CPPFLAGS += -Iengine/type_safe/external/debug_assert
CPPFLAGS += -Iengine/magic_enum/include
CPPFLAGS += -Iengine/spdlog/include

CPPFLAGS += -IC:/SFML/include
CPPFLAGS += -IC:/MinGW/include
CPPFLAGS += -IC:/MinGW/include/c++/8.2.0
CPPFLAGS += -MMD -MP -DSFML_STATIC

CXXFLAGS := -std=c++17 -Wall -Wno-parentheses -pedantic

LDFLAGS := -LC:MinGW/lib/
LDFLAGS += -LC:/SFML/lib

LDLIBS := -lsfml-graphics-s -lsfml-window-s -lsfml-system-s
LDLIBS += -lopengl32 -lwinmm -lgdi32 -lfreetype

.PHONY: all clean

all: setup $(EXE)

setup:
	mkdir -p $(OBJDIR)
	mkdir -p $(EXEDIR)
	mkdir -p $(EXEDIR)/font
	cp -r asset $(EXEDIR)
	
clean:
	rm -rf $(EXEDIR)
	rm -rf $(OBJDIR)

$(EXE): $(OBJ)
	$(CXX) $^ $(LDFLAGS) $(LDLIBS) -o $@ 

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@