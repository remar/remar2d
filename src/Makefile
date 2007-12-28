CFLAGS =	`sdl-config --cflags`
CPPFLAGS =	$(CFLAGS)
LIBS =		`sdl-config --libs`

PROGS =		test

all:		$(PROGS)

TEST =		test.o remar2d.o tinyxml.o tinystr.o tinyxmlerror.o \
		tinyxmlparser.o Sprite.o Animation.o SpriteInstance.o \
		TileSet.o Tile.o

test:		$(TEST)
		g++ -o $@ $^ $(LIBS)

clean:
		rm -f *.o *~ $(PROGS)
