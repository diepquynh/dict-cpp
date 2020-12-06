CC := g++
OBJ := dictionary.cpp
OUT := dictionary

all:
	$(CC) $(OBJ) -o $(OUT)

clean:
	@rm -f $(OUT)
