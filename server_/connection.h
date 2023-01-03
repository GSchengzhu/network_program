#ifndef __CONNECTION_H_
#define __CONNECTION_H_

#include "buffer.h"

class Connection{
public:
    Connection(int fd);
    ~Connection();
    int getFD(){ return m_sockfd; }
    bool process();
    size_t read();
    size_t write();

private:
    int m_sockfd;
    DataBuffer m_inputBuffer;
    DataBuffer m_outputBuffer;
};



#endif