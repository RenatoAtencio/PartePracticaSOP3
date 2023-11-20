CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall -fopenmp

SRC_DIR = src
OBJ_DIR = obj

# Lista de archivos fuente en src/
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Lista de archivos objeto generados a partir de los archivos fuente
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Nombre de los programas ejecutables
TARGET = app
TARGET2 = app2  # Segundo programa ejecutable
TARGET3 = app3  # Tercer progrma

all: $(TARGET) $(TARGET2) $(TARGET3)

$(TARGET): $(OBJ_DIR)/main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TARGET2): $(OBJ_DIR)/main2.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TARGET3): $(OBJ_DIR)/buscador.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(TARGET2) $(TARGET3)
