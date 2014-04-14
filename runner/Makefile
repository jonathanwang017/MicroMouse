SRC_DIR = ../micromouse
INCLUDEOPTS = -I$(SRC_DIR)
CXXFLAGS += -DGROUND_TEST
export CXXFLAGS
TARGETS = init_maze navigation

all: $(TARGETS)

clean:
	cd $(SRC_DIR) && $(MAKE) clean
	$(RM) *.o
	$(RM) $(TARGETS)

init_maze:
	cd $(SRC_DIR) && $(MAKE) maze-and-wall
	$(CXX) $(CXXFLAGS) $(INCLUDEOPTS) -c -o init_maze.o init_maze.cpp
	$(CXX) -o init_maze init_maze.o $(SRC_DIR)/maze.o $(SRC_DIR)/wall.o \
		$(SRC_DIR)/move.o $(SRC_DIR)/utils_and_consts.o \
		$(SRC_DIR)/walldetection.o

navigation:
	cd $(SRC_DIR) && $(MAKE) maze-and-wall
	$(CXX) $(CXXFLAGS) $(INCLUDEOPTS) -c -o navigation.o navigation.cpp
	$(CXX) -o navigation navigation.o $(SRC_DIR)/maze.o $(SRC_DIR)/wall.o \
		$(SRC_DIR)/move.o $(SRC_DIR)/utils_and_consts.o \
		$(SRC_DIR)/walldetection.o
