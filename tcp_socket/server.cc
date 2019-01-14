#include "Tcpserver.hpp"
int main(int argc,char* argv[])
{
    if(argc != 3){
        std::cerr << "argument error!" << "ip , port" << std::endl;
        exit(1);
    }
    Server* sp = new Server(argv[1],atoi(argv[2]));
    sp->ServerInit(5);
    sp->ServerStart();
    return 0;
}
