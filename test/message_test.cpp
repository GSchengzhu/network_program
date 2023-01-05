#include "../common/message.h"

#include <stdio.h>
#include <string.h>
#include <iostream>
int main()
{
    Message a("world",5);
    std::string a_string = a.getData();
    std::cout << 11 << a_string << std::endl;

    char buffer[1024] = {0};
    *(MESSAGEHEAD*)buffer = 5;
    
    const char* hello = "hello";
    std::copy(hello,hello+5,buffer+HEAD_LENGTH);
    int ret = getMessage(buffer,9,a);
    std::cout << 22 << ret << a.getData() << std::endl;
    return 0;
}