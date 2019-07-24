EXE = better51
SOURCES = main.cpp i8051.cpp
SOURCES += framework/imgui/imgui_impl_sdl.cpp framework/imgui/imgui_impl_opengl3.cpp
SOURCES += framework/imgui/imgui.cpp framework/imgui/imgui_demo.cpp framework/imgui/imgui_draw.cpp framework/imgui/imgui_widgets.cpp
OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))
UNAME_S := $(shell uname -s)

CXXFLAGS = -I../ -I../../ -I./framework/imgui
CXXFLAGS += -g -Wall -Wformat
LIBS =

## Using OpenGL loader: gl3w [default]
SOURCES += /libs/gl3w/GL/gl3w.c
CXXFLAGS += -I./libs/gl3w

ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_MESSAGE = "Linux"
	LIBS += -lGL -ldl `sdl2-config --libs`

	CXXFLAGS += -I../libs/gl3w `sdl2-config --cflags`
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(UNAME_S), Darwin) #APPLE
	ECHO_MESSAGE = "Mac OS X"
	LIBS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo `sdl2-config --libs`
	LIBS += -L/usr/local/lib -L/opt/local/lib

	CXXFLAGS += -I../libs/gl3w `sdl2-config --cflags`
	CXXFLAGS += -I/usr/local/include -I/opt/local/include
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(findstring MINGW,$(UNAME_S)),MINGW)
   ECHO_MESSAGE = "MinGW"
   LIBS += -lgdi32 -lopengl32 -limm32 `pkg-config --static --libs sdl2`

   CXXFLAGS += -I../libs/gl3w `pkg-config --cflags sdl2`
   CFLAGS = $(CXXFLAGS)
endif

##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:../%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:../../%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:./framework/imgui/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:./libs/gl3w/GL/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(EXE)
	@echo Build complete for $(ECHO_MESSAGE)

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)
	rm -f imgui.ini
	rm -f $(OBJS)

clean:
	rm -f $(EXE) $(OBJS)
