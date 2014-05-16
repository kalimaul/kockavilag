DEFS =
INCS =
LIBS =

CFLAGS   = $(DEFS) $(INCS) -O2 -Wall
CXXFLAGS = $(DEFS) $(INCS) -O2 -Wall -std=c++11 -fno-rtti
LDFLAGS  = $(LIBS) -s

CFLAGS_DEBUG   = $(DEFS) $(INCS) -g -Wall -DDEBUG=1
CXXFLAGS_DEBUG = $(DEFS) $(INCS) -g -Wall -std=c++11 -DDEBUG=1 -fno-rtti
LDFLAGS_DEBUG  = $(LIBS)

SRCS = $(wildcard *.c *.cc *.cpp *.cxx)
EXT  = $(firstword $(suffix $(SRCS)))
OBJS = $(SRCS:$(EXT)=.o)
DEPS = $(SRCS:$(EXT)=.d)
BIN  = main

PREFIX=/usr/local

ifeq ($(EXT), .c)
LANG = C
else
LANG = CXX
endif

.PHONY: all debug strip install uninstall clean

all: $(BIN)

debug: CFLAGS   = $(CFLAGS_DEBUG)
debug: CXXFLAGS = $(CXXFLAGS_DEBUG)
debug: LDFLAGS  = $(LDFLAGS_DEBUG)
debug: all

strip: all
	strip $(BIN)

$(BIN): $(OBJS)
ifeq ($(LANG), C)
	$(CC) $(LDFLAGS) -o $@ $^
else
	$(CXX) $(LDFLAGS) -o $@ $^
endif

%.d: %$(EXT)
ifeq ($(LANG), C)
	$(CC) -MM -MP -MT $(patsubst %.d,%.o,$@) -MT $@ $< >$@
else
	$(CXX) -MM -MP -MT $(patsubst %.d,%.o,$@) -MT $@ $< >$@
endif

install: all
	install $(BIN) $(DESTDIR)$(PREFIX)/bin

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/$(BIN)

clean:
	rm -f $(BIN) *.o *.d

-include $(DEPS)
