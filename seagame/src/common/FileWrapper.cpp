#include "FileWrapper.h"

FileWrapper::FileWrapper(std::string &filename, std::ios::openmode mode): file(filename, mode) {}

FileWrapper::~FileWrapper() {
    if(file.is_open()){
        file.close();
    }
}