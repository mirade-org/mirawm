# mirawm
Window manager made in C++ for the "mirade" project

## Preview
![No picture for the moment](./)

## Dependencies
- make
- g++
- libX11
- xinit

## Build and test
Available "make" commands :
- `build` : to compile the project to a binary file (debug)
- `run` : to build and run the window manager (debug)
- `clean` : to delete all file in cache and previously compiled files

Before running it for testing, you probably should modify X11 properties

> Encountered error :
> `/usr/libexec/Xorg.wrap: Only console users are allowed to run the X server` \
> -> Add `allowed_users = anybody` to "/etc/X11/Xwrapper.config"

I do all my test directly on my system, but you can choose to create a screen on
your screen with "Xephyr".
```
XEPHYR = $(whereis -b Xephyr | cut -f2 -d' ')

xinit ./build/xinitrc" -- \
    $XEPHYR" \
        :100 \
        -ac \
        -screen 800x600 \
        -host-cursor
```