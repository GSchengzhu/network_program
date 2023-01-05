#include "buffer.h"
#include <sys/uio.h>
#include <stdio.h>
#include <unistd.h>

DataBuffer::DataBuffer(int initSize):
    m_buffer(initSize),m_readPos(0),m_writePos(0)
{

}

DataBuffer::~DataBuffer()
{

}

void DataBuffer::append(const char* appendData,int length)
{
    //扩充空间
    if(m_readPos+(m_buffer.size() - m_writePos) < length)
    {
         m_buffer.resize(m_writePos+length+1);
    }else
    {
        std::copy(&*m_buffer.begin()+m_readPos,&*m_buffer.begin()+m_writePos,&*m_buffer.begin());
        m_writePos = m_writePos-m_readPos;
        m_readPos = 0;
    }
    std::copy(appendData,appendData+length,&*m_buffer.begin()+m_writePos);
    m_writePos = m_writePos+length;
}

size_t DataBuffer::readDataFromFD(int fd)
{
    char tmpBuffer[1024] = {0};
    struct iovec data[2];
    data[0].iov_base = &*m_buffer.begin()+m_writePos;
    data[0].iov_len = m_buffer.size() - m_writePos;
    data[1].iov_base = tmpBuffer;
    data[1].iov_len = 1024;

    size_t length = readv(fd,data,2);
    if(length < 0)
    {
        perror("readv error:");
        return -1;
    }
    
    //数据长度小于等于当前buffer可写长度数据将直接填充在iovbase指定的地址  无需考虑
    if(length <= data[0].iov_len)
    {
        m_writePos += length;
    }else
    {
        //数据长度大于当前buffer可写长度
        m_writePos = m_buffer.size();
        append(tmpBuffer,length - data[0].iov_len);
    }
}

size_t DataBuffer::writeDataToFD(int fd)
{
    size_t writen = write(fd,&*m_buffer.begin()+m_readPos,m_writePos-m_readPos);
    if(writen < 0)
    {
        perror("write error:");
        return writen;
    }
    m_readPos += writen;
    return writen;
}

const char *DataBuffer::readableData()
{
    return &(*m_buffer.begin())+ m_readPos;
}

size_t DataBuffer::readableDataLength()
{
    return m_writePos-m_readPos;
}
