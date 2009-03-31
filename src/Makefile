CFLAGS =	`sdl-config --cflags` -g -Wall
CPPFLAGS =	$(CFLAGS)
LIBS =		`sdl-config --libs`

PROGS =		test

all:		$(PROGS)

SRC = 		remar2d.o tinyxml.o tinystr.o tinyxmlerror.o \
		tinyxmlparser.o Sprite.o Animation.o SpriteInstance.o \
		TileSet.o Tile.o Font.o Character.o SurfaceCache.o

TEST =		test.o $(SRC)

libremar2d.a:	$(SRC)
	ar rvs $@ $(SRC)

install:	libremar2d.a
	-cp libremar2d.a /usr/lib/.
	-cp remar2d.h /usr/include/.

test:		$(TEST)
		g++ -o $@ $^ $(LIBS)

clean:
		rm -f *.o *~ $(PROGS)
