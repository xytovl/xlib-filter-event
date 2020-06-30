# Workaround for SDL2 with fullscreen games

When SDL2 detects a focus loss on a fullscreen window, it minimizes it.
This small library blocks the focusin/out events, so nothing happens.

## Building
Dependencies are Xlib and libdl
```
make
```

## Usage
This library should be used with LD_PRELOAD.

For instance in Civilization VI, edit the Civ6 script and add
```
LD_PRELOAD=/path/to/xlib-filter.so
```
