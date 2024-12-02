#ifndef OOP_FILEWRAPPER_H
#define OOP_FILEWRAPPER_H

#include <iostream>
#include "fstream"

class FileWrapper {
    private:
        std::fstream file;

    public:
        FileWrapper(std::string &filename, std::ios::openmode mode);
        ~FileWrapper();

        template<class T>
        void write(const T &data);

        template<class T>
        void read(T &data);
};

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
