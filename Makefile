EXECNAME ?= main

CXXFLAGS += -Wall -Wextra -std=gnu++14 -pedantic

LIBS +=

LDFLAGS +=

LD = $(CXX)
RM = rm

OBJS = main.o


SO_LIBS +=
LIBS += $(SO_LIBS)

INCLUDES = -Iinclude
CXXFLAGS += $(INCLUDES)

# ----------------------------------------------------------------------------

.PHONY: all clean run ee bee

all: $(EXECNAME)

clean:
	$(RM) -fv $(OBJS) $(EXECNAME)

run: $(EXECNAME)
	./$(EXECNAME)

# Debug .PHONY targets
ee: clean run
bee: clean all

# Not .PHONY targets
$(EXECNAME): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) $(LIBS) -o $(EXECNAME)
