# TODO 

* add greyscale to SSD1306 SPI too
* make greyscale / monochrome switchable via flag
* embed LCD_WIDTH and LCD_HEIGHT as settable variables. If we only refer to them inside the pico-screens directory we can also set defaults
  * LCD_X_OFFSET and LCD_Y_OFFSET?
* have st7789 use mipi_display too?
  * set up a comparison
* a portion of the screen freezes onto the greyscale version of doom for some reason...
  * honestly this might just be the USB bugging out and thinking it detects a keypress. it's really hard to tell
* figure out how to generalize weights for area average
* remove all TODOs
* fix saving :(
* make some modifications to the readme:
  * explain what I changed and why

# Maybe not todo...

* render whole lines via blocking st7789_write
  * this doesn't work, but I'm pretty sure it's because I've flipped the memory 90 degrees and now I have to end on a word or something