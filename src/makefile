# Nome do compilador 
CXX = g++

# Flags de compilação
CXXFLAGS = -std=c++11 -Wall 

# Nome do executável
TARGET = main.exe

# Arquivos fonte
SRC = main.cpp

# Regra para compilar e gerar o executável
$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Regra para limpar arquivos gerados
clean:
	rm -f $(TARGET)

# Regra padrão para rodar o executável
run: $(TARGET)
	./$(TARGET)

# Regra para buildar o projeto
build: clean $(TARGET)
