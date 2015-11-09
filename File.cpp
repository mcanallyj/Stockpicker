//
//  File.cpp
//  StockPicker
//
//  Created by Jason McAnally on 7/10/15.
//  Copyright (c) 2015 Jason McAnally. All rights reserved.
//

#include "File.h"

File::File(std::string fName, std::string fDirectory) {
    fileName = fName;
    directory = fDirectory;
}

/*********************************************************************
 ** Function: timeLastModified
 ** Description: returns a pointer to a time_t type which corresponds to
 **     the date/time of the last time the argument file was modified
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: N/A
 *********************************************************************/
time_t File::timeLastModified() {
    struct tm *clock;
        
    stat(fileName.c_str(), &attr);
    clock = localtime(&(attr.st_mtimespec.tv_sec));
    
    return mktime(clock);
}

bool File::isEmpty() {
    struct stat attr;
    stat(fileName.c_str(), &attr);
    return (attr.st_size == 0);
}

std::string File::getFileName() {
    return fileName;
}

std::string File::getDirectory() {
    return directory;
}

/*********************************************************************
 ** Function: file_exists
 ** Description: returns whether or not the file exists
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: N/A
 *********************************************************************/
bool File::exists() {
    return (stat((directory + fileName).c_str(), &attr) == 0);
}
