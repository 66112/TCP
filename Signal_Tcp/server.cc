#include "TcpSignalProcess.hpp"
int main(int argc,char* argv[])
{
    if(argc != 2){
        std::cerr << "argument error!" << " port" << std::endl;
        exit(1);
    }
    Server* sp = new Server(atoi(argv[1]));
    sp->ServerInit(5);
    sp->ServerStart();
    return 0;
}
