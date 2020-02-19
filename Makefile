PKG := gstreamer-base-1.0
NAME := gstsaveframesink

all: inspect
so: obj
	gcc -shared -o $(NAME).so $(NAME).o $(shell pkg-config --libs gstreamer-1.0 $(PKG))

obj:
	gcc -Wall -Werror -fPIC $(CPPFLAGS) $(shell pkg-config --cflags gstreamer-1.0 $(PKG)) -c -o $(NAME).o $(NAME).c

inspect: so
	gst-inspect-1.0 ./$(NAME).so
