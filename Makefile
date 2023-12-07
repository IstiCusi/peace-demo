.PHONY: test_demo test_memory clean test


MAKEFLAGS += -j4
CC = gcc
CFLAGS = -O3 -Wall -Wmissing-declarations -ffunction-sections -Wextra -g -D_REENTRANT $(shell pkg-config --cflags sdl2 SDL2_ttf SDL2_mixer SDL2_image)
LIBS = -Wl,--gc-sections $(shell pkg-config --libs --static sdl2 SDL2_ttf SDL2_mixer SDL2_image)

all: demo use_scroller

demo: main.o scroller.o charoffset.o window.o water.o sdl_scroller.o event.o frame.o title.o color.o music.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

use_scroller: use_scroller.o scroller.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o demo *.a *.so use_scroller

test:	use_scroller
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./use_scroller

test_demo:	demo
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./demo

test_memory:    demo
	@pgrep -x demo >/dev/null || (./demo &)
	@ps -C demo -o rss= | awk '{sum+=$$1} END {print sum " KB"}'
