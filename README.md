# OpenNitemare3D
reimplementation of the 1994 FPS Nitemare 3D


## features:
* Loading of original bitmap images
* Loading of original maps
* Easily portable to most graphics libraries
* Playback of MIDI music
* Playback of SFX from the Windows version

## currently being worked on:
* SFX loading for Dos format
* PCX image loading
* Loading entities from map and drawing them

## notes:
### game quirks:
* In the Dos version, player speed is not capped/deltatimed, this is fixed in the Windows version
* Sprites are saved sideways in the IMG bitmap files
* Player speed varies based on rotation

### file formats:

#### DAT:
Nitemare 3D uses the .DAT format(also used by David Gray in the Hugo series),
this consists of a header that contains offsets for every file stored in the container, the offset consists of a unsigned 16 bit integer for the length followed by a unsiged 32 bit integer for the position.
<br></br>
files in SND.DAT consist of MIDI files followed by either 16 bit VOC or 8 bit PCM audio files(depending on the version).
UIF.DAT consists of 256 color 320x200 PCX images


#### MAP:
maps are stored as text files and are very easy to read, the first 514 bytes are still unknown by me(could be tile definitions?)
after that every map is stored as a 8192 byte chunk, every even byte is a tile id and every odd byte is a item id.


