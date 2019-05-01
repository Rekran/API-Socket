#include <cstdlib>
#include <iostream>
#include "Socket.h"
#include "ServerSocket.h"
#include "InetAddress.h"
#include <thread>
#define BUFFER_SIZE 512
using namespace std;

using namespace std;
char msg_recv[BUFFER_SIZE];
char msg_send[BUFFER_SIZE];

void recv_t(Socket * s){

FILE *arq_out;
arq_out = fopen("teste.png", "wb");
size_t block_size = 0;

if (arq_out == NULL) // Se não conseguiu criar
{
    printf("Problemas na CRIACAO do arquivo\n");
   	return ;
}

 while(true){

        try
        {
            memset(&msg_recv, 0, BUFFER_SIZE);
            block_size = s->recv(msg_recv,BUFFER_SIZE);

            if(block_size != 512)
                printf("TAM: %d\n", block_size);

            if(strcmp(msg_recv,"end") == 0)
                break;

            fwrite(&msg_recv[0], sizeof(char),block_size, arq_out);


        }catch(UnknownHostException &uhe)
        {
            cout << uhe.what() << endl;
            break;
        }
        catch(IOException &uhe)
        {
            cout << uhe.what() << endl;
            break;
        }
}

fclose(arq_out);

}




int main(int argc, char *argv[])
{
    WSADATA wsadata;
    if(WSAStartup(0x101,(LPWSADATA)&wsadata) != 0)
    {
       exit(1);
    }
    Socket * local;
    InetAddress * localAddr;
    localAddr = InetAddress::getByAddress("127.0.0.1");

    try
    {

    local = new Socket(localAddr,2000);

    }catch(UnknownHostException &uhe)
    {
        cout << uhe.what() << endl;
        return 1;
    }
    catch(IOException &uhe)
    {
        cout << uhe.what() << endl;
        return 1;
    }

   thread recv (recv_t,local);

   recv.detach();

    pthread_exit(NULL);
}
