SRCDIR = src
INCDIR = include
OBJDIR = obj

CXX = g++
CXXFLAGS = -Wall -g -std=c++20 -I$(INCDIR) `sdl2-config --cflags`
CXXLIBS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf

ifeq ($(OS),Windows_NT)
	CXXLIBS = -L. -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -llua
else
	CXXLIBS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -llua5.4
endif

SRC = 	$(wildcard $(SRCDIR)/*.cpp) \
		$(wildcard $(SRCDIR)/ecs/*.cpp) \
		$(wildcard $(SRCDIR)/ecs/ui/*.cpp) \
		$(wildcard $(SRCDIR)/gfx/*.cpp) \
		$(wildcard $(SRCDIR)/state/*.cpp)

INC = 	$(wildcard $(INCDIR)/*.hpp) \
		$(wildcard $(SRCDIR)/ecs/*.hpp) \
		$(wildcard $(SRCDIR)/ecs/ui/*.hpp) \
		$(wildcard $(INCDIR)/input/*.hpp) \
		$(wildcard $(SRCDIR)/gfx/*.hpp) \
		$(wildcard $(SRCDIR)/state/*.cpp)

OBJ = $(SRC:$(SRCDIR)%.cpp=$(OBJDIR)%.o)

EXE = exocet

RM = rm -f

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(CXXLIBS) -o $@
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INC)
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/ecs
	@mkdir -p $(OBJDIR)/ecs/ui
	@mkdir -p $(OBJDIR)/gfx
	@mkdir -p $(OBJDIR)/state

	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	$(RM) -r $(OBJDIR)
	$(RM) $(EXE)