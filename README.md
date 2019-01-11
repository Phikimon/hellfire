<p align="center">
  <img src="https://github.com/phikimon/hellfire/raw/master/toggle.gif" alt="Toggle gif"/>
</p>

This is the remake of the fire animation implemented on PS X
by Doom developers. Palette and the idea are taken from this article:
http://fabiensanglard.net/doom_fire_psx/

This project depends on no libraries but libc, it only requires your
terminal to support True Colour mode. List of supported terminals
can be found [here](https://gist.github.com/XVilka/8346728).

There is a quick, but not very reliable way to check if your
terminal supports truecolor:
```bash
$ echo $COLORTERM
...
```
Look for '24bit' or 'truecolor' words in the output of echo.


## Usage:
```bash
$ make
$ ./fire
```
By sending SIGINT(pressing Ctrl-C) you can toggle the fire source shape.
Program exits when there are no more fire
cells on the screen or when you press Ctrl-\\.

Be free to experiment with the spread_fire() functions as they
affect fire behavior in a very interesting way.

Also, arbitrary shapes of fire source are possible. Just add new shape in
shapes.lst, in the enum in terminal.h and in parse_fire_source(), or just
edit existing shapes.

Commit 'Add SHAPE_HEART' might be useful, if you are willing to add your
shape.

