#include <iostream>
#include "PngWriter.hpp"

// to build:
//
// g++ main.cpp -lpng 

int PngWriter_main(int argc,char * argv[]) {
  constexpr const int width{960};
  constexpr const int height{600};

  PngWriter png(width,height);

  // set some pixels....

  for (int i = 0; i < width; ++i)
    for (int j = 0; j < height; ++j)
      png.set(i,j,i+j,i-j,j-i); // set function assumes (0,0) is bottom left 
  
  // then write...
  
  png.write("sample.png");

  // you can make some changes and write another...

  png.set(400,300,0,0,0);
  
  png.write("sample2.png");
  
}

