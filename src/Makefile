CFLAGS =	`sdl-config --cflags` -g -Wall
CPPFLAGS =	$(CFLAGS)
LIBS =		`sdl-config --libs`

PROGS =		test

all:		$(PROGS) libremar2d.a

SRC = 		remar2d.o tinyxml.o tinystr.o tinyxmlerror.o \
		tinyxmlparser.o Sprite.o Animation.o SpriteInstance.o \
		TileSet.o Tile.o Font.o Character.o SurfaceCache.o

TEST =		test.o $(SRC)

libremar2d.a:	$(SRC)
	ar rvs $@ $(SRC)
	mkdir -p ../lib
	cp $@ ../lib/.
	mkdir -p ../include
	cp remar2d.h ../include/.

install:	libremar2d.a
	-cp libremar2d.a /usr/lib/.
	-cp remar2d.h /usr/include/.

uninstall:
	-rm /usr/lib/libremar2d.a
	-rm /usr/include/remar2d.h

test:		$(TEST)
		g++ -o $@ $^ $(LIBS)

clean:
		rm -f *.o *~ $(PROGS) libremar2d.a
		rm -rf ../lib ../include
