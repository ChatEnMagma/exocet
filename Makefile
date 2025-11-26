SRCDIR = src
INCDIR = include
OBJDIR = obj

CXX = g++
CXXFLAGS = -Wall -g -std=c++20 -I$(INCDIR) `sdl2-config --cflags`
CXXLIBS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf

ifeq ($(OS),Windows_NT)
	EXE = exocet.exe

	CXXLIBS = -static -static-libgcc -static-libstdc++ \
				`pkg-config --libs --static SDL2` \
				`pkg-config --libs --static SDL2_image` \
				`pkg-config --libs --static SDL2_ttf` \
				`pkg-config --libs --static SDL2_mixer` \
				-llua
	BEGIN_COMPILE = exocet.res | $(EXE)
	END_COPILE = $(CXX) -o $(EXE) $^ $(CXXLIBS) exocet.res
else
	EXE = exocet

	CXXLIBS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.4
	BEGIN_COMPILE = $(EXE)
	END_COPILE = $(CXX) -o $(EXE) $^ $(CXXLIBS)
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

RM = rm -f

.PHONY: all clean


all: $(BEGIN_COMPILE)

exocet.res: exocet.rc
	windres exocet.rc -O coff -o exocet.res

$(EXE): $(OBJ)
	$(END_COPILE)
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
	$(RM) exocet.res