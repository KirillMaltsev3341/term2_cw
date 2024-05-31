# term2_cw

The coursework is a utility for processing PNG images. 
Available functionality: draw a circle, RGBFilter, split image into n*m parts, draw a square with diagonals, add a frame to the image.
See used [lib](https://github.com/KirillMaltsev3341/ImageEditor)

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
   - Add new **#define NEW_FLAG_IDX1**, **#define NEW_FLAG_IDX2**, **...**
   - Change **#define FLAGS_NUMBER** value
2. In Handler.cpp:
   - Add new flags in Handler::Handler() constructor
   - Add new case in Handler::handleFlags() method
3. Add your new isFunction and doFunction in relevant .h and .cpp files
4. Add new parsing functions if needed
