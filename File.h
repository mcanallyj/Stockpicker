//
//  File.h
//  StockPicker
//
//  Created by Jason McAnally on 7/10/15.
//  Copyright (c) 2015 Jason McAnally. All rights reserved.
//

#ifndef __StockPicker__File__
#define __StockPicker__File__

#include <stdio.h>
#include <string>
#include <sys/stat.h>

class File {
private:
    std::string fileName;
    std::string directory;
    struct stat attr;

    
public:
    File(std::string fName, std::string fDirectory);
    time_t timeLastModified();
    bool isEmpty();
    bool exists();
    
    std::string getFileName();
    std::string getDirectory();
};



#endif /* defined(__StockPicker__File__) */
