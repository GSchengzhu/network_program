#ifndef _BUFFER__H_
#define _BUFFER__H_

#include <vector>

class DataBuffer{
public:
    DataBuffer(int initSize = 1024);
    ~DataBuffer();

    size_t readDataFromFD(int fd);
    size_t writeDataToFD(int fd);

private:
    void append(const char* appendData,int length);

    std::vector<char> m_buffer;
    int m_readPos;
    int m_writePos;
};

#endif