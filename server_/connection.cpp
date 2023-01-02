 #include "connection.h"
 #include <unistd.h>

 Connection::Connection(int fd):m_sockfd(fd)
 {

 }

 Connection::~Connection()
 {
    close(m_sockfd);
 }

 size_t Connection::read()
 {
    return m_inputBuffer.readDataFromFD(m_sockfd);
 }

 size_t Connection::write()
 {
    return m_outputBuffer.writeDataToFD(m_sockfd);
 }