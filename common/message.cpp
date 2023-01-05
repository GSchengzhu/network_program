#include "message.h"
#include <strings.h>
#include <stdio.h>

Message::Message(const char* data,MESSAGEHEAD length):
    m_data(nullptr),m_length(0)
{
    reInit(data,length);
}

Message::~Message()
{
    if(m_data != nullptr)
    {
        free(m_data);
        m_data = nullptr;
        m_length = 0;
    }
}

std::string Message::getData()
{
    return std::string(m_data+HEAD_LENGTH,m_length);
}

void Message::reInit(const char* data,MESSAGEHEAD length)
{
    if(m_data != nullptr)
    {
        free(m_data);
        m_data = nullptr;
    }
    if(length == 0)
    {
        return;
    }
    m_data = (char*)malloc(length+HEAD_LENGTH);
    bzero(m_data,length+HEAD_LENGTH);
    *((MESSAGEHEAD*)m_data) = 4;
    std::copy(data,data+length,m_data+HEAD_LENGTH);
    m_length = length;

}

int getMessage(const char* data,int length,Message& msg)
{
    if(length <= HEAD_LENGTH)
    {
        return 0;
    }
    
    int data_length = *((MESSAGEHEAD*)data);
    if(length < (data_length+HEAD_LENGTH))
    {
        return 0;
    }

    msg.reInit(data+HEAD_LENGTH,data_length);
    return data_length+HEAD_LENGTH;
}

