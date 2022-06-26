TARGET = maker
SOURCES = maker.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	gcc -g3 $(SOURCES) -o $(TARGET)

test: $(TARGET)
	rm -rf saved
	./$(TARGET) $(TARGET)
	bash side_by_side.sh

clean:
	@# none

fclean: clean
	rm -f $(TARGET)

re: fclean all
