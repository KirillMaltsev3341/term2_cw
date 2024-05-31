# term2_cw

The coursework is a utility for processing PNG images. 
Available functionality: draw a circle, RGBFilter, split image into n*m parts, draw a square with diagonals, add a frame to the image.

## Installation and Building
```bash
git clone https://github.com/KirillMaltsev3341/term2_cw.git
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
    1.1. add new **#define NEW_FLAG_IDX1**, **#define NEW_FLAG_IDX2**, **...**
    2.2. change **#define FLAGS_NUMBER** value
  3. In Handler.cpp:
    2.1. add new flags in Handler::Handler() constructor
    2.2. add new case in Handler::handleFlags() method
  5. Add your new isFunction and doFunction in relevant .h and .cpp files
  6. Add new parsing functions if needed

100. First list item
     100.1. First nested list item
