# OpenNitemare3D
a C++ engine reimplementation of the 1994 MS-DOS FPS shooter Nitemare 3D

### Note: this requires the original shareware Nitemare 3D game-files to work

## About:
I started this project because I believe every game has the right to be ported to modern operating systems,
the original game was made in C with some x86 assembly, this new version is in C++ and only uses open source, cross platform libraries.


## features:
* loads original bitmap files
* loads original maps
* software based raycaster
* portable and could easily ported to most graphics libraries

## todo:
* load VOC sounds and MIDI music from SND.DAT
* load PCX images from UIF.DAT

## bugs 
* map tiles are drawn with the incorrect sprite as some of them are animated and this offsets the sprite index


## map format:
maps are in MAP.1-3


### data:
bytes 0-514:  ¯\_(ツ)_/¯.
after that each map is stored in a 8192 byte chunk, with even bytes containing tiles, and odd bytes containing item.


## installing
in order to run this you need some of the original game files [which can still be bought from David Gray's Website](https://www.dgray.com/n3dpage.htm).

### files needed:
* IMG.1
* MAP.1
