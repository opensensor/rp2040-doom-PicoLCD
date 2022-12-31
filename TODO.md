# TODO 

* remove all TODOs
* make some modifications to the readme:
  * explain what I changed and why
* fix saving :(
* experiment with greyscale rendering on monochrome LCDs 
  * I _think_ they are setting the screens to direct memory access, holding the "scanline" at the top of the screen until they draw the next frame then letting it loose, allowing for the fastest possible screen refresh. then what you do is refresh, for example, 3x faster for 2 bits of greyscale (2^n-1). if the color is 2 the pixel is white twice and black once, making greyscale
  * What I don't entirely understand is how this is so significantly faster than just updating the buffer? I guess there's no way to set the memory without the screen displaying it immediately - the memory window is 128x64, so you can't manipulate screen / column starts to double buffer. so maybe the scanline hold is mostly to reduce tearing
* get ST7735 screens working
  * hagl for hal works, and I could switch to that for st7789 screens (which would allow people to use ili screens, etc anything that supports MIPI) but it's a _lot_ of code and a lot of stuff I don't need. I could use just the screen drivers, that's going to be a bit of work though

# Maybe not todo...

* render whole lines via blocking st7789_write
  * this doesn't work, but I'm pretty sure it's because I've flipped the memory 90 degrees and now I have to end on a word or something