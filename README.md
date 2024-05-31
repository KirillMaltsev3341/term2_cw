# term2_cw

The coursework is a utility for processing PNG images. 
Available functionality: draw a circle, RGBFilter, split image into n*m parts, draw a square with diagonals, add a frame to the image.

## Installation and Building
```bash
git clone ...
cd term2_cw
make build_libs
make
```

To see detailed information about the launch flags
```bash
./cw --help
```

## Adding New Functionality and Flags
  1. In Handler.h:
    1. add new **#define NEW_FLAG_IDX1**, **#define NEW_FLAG_IDX2**, **...**
    2. change **#define FLAGS_NUMBER** value
  2. In Handler.cpp:
    1. add new flags in Handler::Handler() constructor
    2. add new case in Handler::handleFlags() method
  3. Add your new isFunction and doFunction in relevant .h and .cpp files
  4. Add new parsing functions if needed