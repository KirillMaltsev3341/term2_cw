TARGET = cw
CXX = g++

SRC_DIR = ./src
INCLUDE_DIR = ./include
LIB_DIR = ./libs
BIN_DIR = ./bin

CXXFLAGS = -I$(INCLUDE_DIR) -I$(LIB_DIR)/ImageEditor/include -Wl,-rpath=$(LIB_DIR)/ImageEditor/lib -L$(LIB_DIR)/ImageEditor/lib -lImageEditor

SRC = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/Handler/*.cpp)
OBJ = $(patsubst %.cpp, $(BIN_DIR)/%.o, $(notdir $(SRC)))

all : create_bin_folder $(TARGET)

$(TARGET) : $(OBJ)
	$(CXX) $^ $(CXXFLAGS) -o $@

$(BIN_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) -c $< $(CXXFLAGS) -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/Handler/%.cpp
	$(CXX) -c $< $(CXXFLAGS) -o $@

create_bin_folder :
	@mkdir -p $(BIN_DIR)

build_libs :
	cd $(LIB_DIR)/ImageEditor; make

clean:
	@rm -f $(TARGET)
	@rm -rf $(BIN_DIR)