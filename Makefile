CXX = g++
CXXFLAGS = -Wfatal-errors -Wall -Wextra
CXXFLAGS := '-std=c++17' $(CXX_FLAGS)
srcs = $(wildcard *.cpp)
tests = $(wildcard *Tests.cpp)
gameboard = GameBoard.o
objs = $(srcs:.cpp=.o)
deps = $(srcs:.cpp=.d)

test: $(objs)
	$(CXX) $(CXXFLAGS) -o $@  test_main.o $(tests) $(gameboard)
	./test

gol: $(objs)
	$(CXX) $(CXXFLAGS) gol.cpp -o $@  $(gameboard)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

.PHONY: clean

# $(RM) is rm -f by default
clean:
	$(RM) $(objs) $(deps) test

-include $(deps)
