# TODO 

* remove all TODOs
* make some modifications to the readme:
  * explain what I changed and why
* fix saving :(
* Refactor to use only mipi_display from hagl_hal
* a portion of the screen freezes onto the greyscale version of doom for some reason...
  * honestly this might just be the USB bugging out and thinking it detects a keypress. it's really hard to tell

# Maybe not todo...

* render whole lines via blocking st7789_write
  * this doesn't work, but I'm pretty sure it's because I've flipped the memory 90 degrees and now I have to end on a word or something