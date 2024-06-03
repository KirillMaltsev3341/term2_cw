TARGET = cw
CXX = g++

SRC_DIR = ./src
INCLUDE_DIR = ./include
LIB_DIR = ./libs
BIN_DIR = ./bin

CXXFLAGS = -I$(INCLUDE_DIR) -I$(LIB_DIR)/ImageEditor/include 
LDFLAGS = -Wl,-rpath=$(LIB_DIR)/ImageEditor/lib -L$(LIB_DIR)/ImageEditor/lib -lImageEditor

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC = $(call rwildcard,$(SRC_DIR),*.cpp)
OBJ = $(patsubst %.cpp, $(BIN_DIR)/%.o, $(notdir $(SRC)))

all : create_bin_dir $(TARGET)

$(TARGET) : $(OBJ)
	$(CXX) $^ $(CXXFLAGS) $(LDFLAGS) -o $@

$(BIN_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) -c $< $(CXXFLAGS) $(LDFLAGS) -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/**/%.cpp
	$(CXX) -c $< $(CXXFLAGS) $(LDFLAGS) -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/**/**/%.cpp
	$(CXX) -c $< $(CXXFLAGS) $(LDFLAGS) -o $@

create_bin_dir :
	@mkdir -p $(BIN_DIR)

build_libs :
	cd $(LIB_DIR)/ImageEditor; make

install_required_soft :
	cd $(LIB_DIR)/ImageEditor; make install_required_soft

clean:
	@rm -f $(TARGET)
	@rm -rf $(BIN_DIR)