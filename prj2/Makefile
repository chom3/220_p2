PROJECT = prj2
COURSE = cs220f14
TARGET = bcd-float

SRC_FILES = \
  Makefile \
  README \
  bcd-float.c \
  bcd-float.h \
  main.c

OBJ_FILES = \
  bcd-float.o \
  main.o

CC = gcc
CFLAGS = -g -Wall -std=c99

$(TARGET):  	$(OBJ_FILES)
		$(CC) $(OBJ_FILES) -o $@

$(PROJECT).tar.gz \
dist:		$(SRC_FILES)
		tar -cvf $(PROJECT).tar $(SRC_FILES)
		gzip $(PROJECT).tar

clean:
		rm -f $(TARGET) *.o *~

bcd-float.o:	bcd-float.c bcd-float.h
main.o:		main.c bcd-float.h
