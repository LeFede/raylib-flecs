TARGET = a
FOLDER = src/
SYSTEMS = $(FOLDER)systems/
COMPONENTS = $(FOLDER)components/
SRC = $(FOLDER)main.c $(SYSTEMS)sy_HandleInput.c $(SYSTEMS)sy_PrepareCamera.c $(SYSTEMS)sy_BeginDraw.c $(SYSTEMS)sy_FinishDraw.c
# $(SYSTEMS)sy_DrawSprite.c
 # $(SYSTEMS)sy_PrintDelta.c
# $(FOLDER)spawn_aseprite.c

CC = gcc
CFLAGS = -Wall -std=c99

LIBS_UNIX = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lflecs

LIBS_WIN = -lraylib -lopengl32 -lgdi32 -lwinmm -lflecs

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
    LIBS = $(LIBS_UNIX)
else ifeq ($(UNAME_S), Darwin)
    LIBS = $(LIBS_UNIX)
else
    LIBS = $(LIBS_WIN)
endif

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)
