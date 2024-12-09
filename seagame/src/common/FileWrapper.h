#ifndef OOP_FILEWRAPPER_H
#define OOP_FILEWRAPPER_H

#include <iostream>
#include "fstream"

class FileWrapper {
    private:
        std::fstream file;

    public:
        FileWrapper(std::string filename, std::ios::openmode mode);
        ~FileWrapper();

        template<class T>
        void write(const T &data);

        template<class T>
        void read(T &data);
        bool isEof();
};

inline FileWrapper::FileWrapper(std::string filename, std::ios::openmode mode): file(filename, mode) {}

inline FileWrapper::~FileWrapper() {
    if(file.is_open()){
        file.close();
    }
}

inline bool FileWrapper::isEof() {
    return file.eof();
}

template<class T>
void FileWrapper::write(const T &data) {
    if(!file.is_open()){
        throw std::runtime_error("File not opened in output mode");
    }

    file << data;
}

template<class T>
void FileWrapper::read(T &data) {
    if(!file.is_open()){
        throw std::runtime_error("File not opened in output mode");
    }

    file >> data;
}


#endif
