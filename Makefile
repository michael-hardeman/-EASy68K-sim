# lame Makefile that's just enough for what I need, feel free to
# add CMake or automake/conf to this.
TARGET ?= asy68ksim
PREFIX = /usr/local

CXX = g++
CXXFLAGS += -fpermissive

# Source files are in the src directory
SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp, obj/%.o, $(SRCS))

.PHONY: clean install

all:    $(TARGET)
	@echo  $(TARGET) has been built

obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $^

clean:
	rm -f $(TARGET) $(OBJS)

distclean: clean
	rm -f *~

install: $(TARGET)
	install -m 755 $(TARGET) $(DESTDIR)$(PREFIX)/bin

uninstall: $(TARGET)
	rm $(DESTDIR)$(PREFIX)/bin/$(TARGET)
