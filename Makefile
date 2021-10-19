CCX = mpic++
CXXFLAGS = -std=c++20 -Wall -Werror -Wextra -pedantic
CPPFLAGS = -Isrc

TARGET = titanic

RPC = \
        src/rpc/append-entries.cc \
        src/rpc/request-vote.cc \
        src/rpc/rpc.cc \
        $(NULL)

SRC = \
        src/main.cc \
        $(RPC) \
        $(NULL)

OBJS = $(SRC:.cc=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

hello: src/hello-world.cc
	mpic++ $< -o $@
	mpirun $@