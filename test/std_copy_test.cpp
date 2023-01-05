#include <string>
int main()
{
    char buffer[1024] = {0};
    const char *hello = "123";
    std::copy(hello,hello+3,buffer);
    printf("%d\n",sizeof(buffer));
    printf("%s\n",buffer);
    return 0;

}