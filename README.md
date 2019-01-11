-> ![Gif](https://github.com/phikimon/hellfire/raw/master/toggle.gif) <-

This is the remake of the fire animation implemented on PS X
by Doom developers. Palette and the idea are taken from this article:
http://fabiensanglard.net/doom_fire_psx/

## Usage:
```bash
$ make
$ ./fire
```
By pressing Ctrl-C you can toggle the presence of fire source(bottom line,
can be noticed in the GIF). Program exits when there are no more fire
cells on the screen or when you press Ctrl-\\.

Be free to experiment with the spread_fire() functions as they
affect fire behavior in a very interesting way.

Also, arbitrary shapes of fire source are possible. Just add new shape in
shapes.lst, in the enum in terminal.h and in parse_fire_source(), or just
edit existing shapes.

Commit 'Add SHAPE_HEART' might be useful, if you are willing to add your
shape.

