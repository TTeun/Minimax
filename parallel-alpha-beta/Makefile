CXXINCL = -I../../bsp/include
LDLIBS = -L../../bsp/lib -lmcbsp1.2.0 -lpthread
CXX = g++
CXXFLAGS = -MMD -O3 -std=c++0x
LINKER = $(CXX)
LDFLAGS = -lrt

TARGET = ../bin/parallel
SOURCES = main.cc $(wildcard **/*.cc)
OBJECTS = $(SOURCES:.cc=.o)

DEPS = $(OBJECTS:.o=.d)
ODIR = ./objects

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LINKER) $(LDFLAGS) $(OBJECTS) $(LDLIBS) -o $@

%.o: %.cc
	$(CXX) -c $(CXXFLAGS) $(CXXINCL) $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS) $(DEPS)

-include $(DEPS)
