CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall -fopenmp
LDFLAGS = -lGL -lglut -lGLU

SRC_DIR = src
OBJ_DIR = obj

# Lista de archivos fuente en src/
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Lista de archivos objeto generados a partir de los archivos fuente
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Nombre de los programas ejecutables
TARGET = countWords
TARGET2 = makeInvertedIndex  # Segundo programa ejecutable
TARGET3 = invertedIndexSearcher  # Tercer progrma
TARGET4 = makeTree
TARGET5 = makeCircular
TARGET6 = grafico

all: $(TARGET) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5) $(TARGET6)

$(TARGET): $(OBJ_DIR)/countWords.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TARGET2): $(OBJ_DIR)/makeInvertedIndex.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TARGET3): $(OBJ_DIR)/invertedIndexSearcher.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TARGET4): $(OBJ_DIR)/makeTree.o
	$(CXX) $(CXXFLAGS) -o $@ $^
	
$(TARGET5): $(OBJ_DIR)/makeCircular.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TARGET6): $(OBJ_DIR)/grafico.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5) $(TARGET6)
