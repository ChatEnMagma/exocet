SRCDIR = src
INCDIR = include
OBJDIR = obj

CXX = g++
CXXFLAGS = -Wall -Wextra -O3 -g -std=c++20 -ffast-math -fno-rtti -flto=$(shell nproc) -I$(INCDIR) `sdl2-config --cflags`
CXXLIBS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf

ifeq ($(OS),Windows_NT)
	EXE = exocet.exe

	CXXLIBS = 	-static -static-libgcc -static-libstdc++ \
            	$(shell pkg-config --libs --static SDL2 SDL2_image SDL2_ttf SDL2_mixer) \
				-llua
else
	EXE = exocet
	CXXLIBS =  $(shell sdl2-config --libs) -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.4
endif

SRC = $(shell find $(SRCDIR) -name '*.cpp')
INC = $(shell find $(INCDIR) -name '*.hpp')
OBJ = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))
DEP = $(OBJ:.o=.d)

RM = rm -f

.PHONY: all clean run

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(CXXLIBS)
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INC)
	@mkdir -p $(dir $@)

	$(CXX) $(CXXFLAGS) -MMD -MP -o $@ -c $<

-include $(DEP)

run: all
	./$(EXE)

clean:
	$(RM) -r $(OBJDIR)
	$(RM) $(EXE)

ifeq ($(OS),Windows_NT)
$(EXE): exocet.res
exocet.res: exocet.rc
	windres exocet.rc -O coff -o exocet.res
clean::
	$(RM) exocet.res
endif