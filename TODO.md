This is Chocolate Doom’s “to do” list. Note that this is kind of an arbitrary
and unstructured wish list of features and improvements. The bug tracker
(http://chocolate-doom.org/bugs) has more feature requests.








am I reusing a pin somewhere, such that SPI communication is interrupted? maybe I should standardize the harness anyways, it's the same pins








* Delete all i2c networking code? maybe
* test sound card
* Get working on https://github.com/01Space/RP2040-0.42LCD ? if I can find it...
* render whole lines via blocking st7789_write
  * this doesn't work, but I'm pretty sure it's because I've flipped the memory 90 degrees and now I have to end on a word or something
* remove all TODOs
* make some modifications to the readme:
  * explain what I changed and why
* get downsampling working via weights
* implement dithering in shared (only for monochrome)
  * this may not actually work, the area average downsampler looks horrible in monochrome
* Nearest neighbor downsampler doesn't support "fixed point" downsampling
* I think the area average downsampler is also wrong... I'm worried I'm skipping lines (or re-rendering lines)