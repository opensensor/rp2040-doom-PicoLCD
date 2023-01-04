# TODO 


## Greyscale Epic

* add greyscale to SSD1306 SPI too
* make greyscale flash less
  * this might require fully rewinding multithreading
  * if interrupts are fast and accurate enough (microseconds) maybe we can just interrupt one of the threads instead?
* make greyscale / monochrome switchable via flag

## ST7789 / 7735 Cleanup Epic

* embed LCD_WIDTH and LCD_HEIGHT as settable variables. If we only refer to them inside the pico-screens directory we can also set defaults
  * LCD_X_OFFSET and LCD_Y_OFFSET?
* have st7789 use mipi_display too?
  * set up a comparison
* figure out how to generalize weights for area average


## Bugs

* a portion of the screen freezes onto the greyscale version of doom for some reason...
  * honestly this might just be the USB bugging out and thinking it detects a keypress. it's really hard to tell
* fix saving :(


## Misc

* remove all TODOs
* make some modifications to the readme:
  * explain what I changed and why