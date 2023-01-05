#ifndef __MESSAGE_H_
#define __MESSAGE_H_

#include <string>

typedef unsigned int MESSAGEHEAD;
#define HEAD_LENGTH  4

class Message{
public:
    Message(const char* data,MESSAGEHEAD length);
    ~Message();
    std::string getData();
    void reInit(const char* data,MESSAGEHEAD length);

protected:
    Message(const Message& msg) = delete;
    Message& operator=(const Message& msg) = delete;

private:
    char* m_data;
    MESSAGEHEAD m_length; 
};

int getMessage(const char* data,int length,Message& msg);

#endif //__MESSAGE_H_