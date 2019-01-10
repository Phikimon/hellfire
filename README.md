![Gif](https://github.com/phikimon/hellfire/raw/master/fire.gif)

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

