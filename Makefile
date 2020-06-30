xlib-filter.so: xlib-filter.c
	gcc -ldl -lX11 xlib-filter.c -shared -fPIC -o xlib-filter.so
