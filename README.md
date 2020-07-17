# OpenNitemare3D
a C++ engine reimplementation of the 1994 MS-DOS FPS shooter Nitemare 3D

### Note: this requires the original shareware Nitemare 3D game-files to work

## About:
I started this project because I believe every game has the right to be ported to modern operating systems,
the original game was made in C with some x86 assembly, this new version is in C++ and only uses open source, cross platform libraries.

# file format documentation:

## map format
maps are in MAP.1-3

bytes 0-514:  ¯\_(ツ)_/¯
after that each map is stored in a 8192 byte chunk, with even bytes containing tiles, and odd bytes containing item
