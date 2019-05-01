#include <cstdlib>
#include <iostream>
#include "Socket.h"
#include "ServerSocket.h"
#include "InetAddress.h"
#include <thread>
#define BUFFER_SIZE 512
#include <stdlib.h>

using namespace std;
char msg_recv[BUFFER_SIZE];
char msg_send[BUFFER_SIZE];


void send_t(Socket * s){

FILE *arq_in;
arq_in = fopen("check.txt", "rb");
size_t block_size = 0;

if (arq_in == NULL)  // Se houve erro na abertura
{
     printf("Problemas na abertura do arquivo\n");
     return ;
}


while(true){
    try
    {
        memset(&msg_send, 0, BUFFER_SIZE);
        block_size = fread (msg_send, sizeof(char),BUFFER_SIZE, arq_in);

        if(block_size != 512)
            cout<<block_size<<endl;

        if(feof(arq_in)&& block_size <= 0)
            break;

        s->send(msg_send,block_size);

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

s->send("end",4);

fclose(arq_in);

}

void recv_t(Socket * s){

FILE *arq_out;
arq_out = fopen("check.txt", "wb");
size_t block_size = 0;

if (arq_out == NULL)
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
                printf("%d\n", block_size);

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
getchar();

}

int main()
{
    WSADATA wsadata;
    if(WSAStartup(0x101,(LPWSADATA)&wsadata) != 0)
    {
       exit(1);
    }
    int menu_1,menu_2,porta;
    char ip[24];
    Socket * socket;
    Socket * recv;
    Socket * send;

    ServerSocket * server;
    InetAddress * servAddr;

    cout<<"1.Servidor "<<endl;
    cout<<"2.Cliente "<<endl;
    cin>>menu_1;

switch(menu_1){

    case 1:
        cout<<"Qual a porta deseja usar?"<<endl;
        cin>>porta;

        try{

            server = new ServerSocket(porta);
            socket = server->accept();

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
    break;

    case 2:
        cout<<"Qual o ip do servidor?"<<endl;
        cin>>ip;
        cout<<"Qual a porta do servidor?"<<endl;
        cin>>porta;
            try
            {
            servAddr = InetAddress::getByAddress(ip);
            socket = new Socket(servAddr,porta);

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
    break;

    }
cout<<"Voce deseja receber ou enviar?"<<endl;
cout<<"1.Receber"<<endl;
cout<<"2.Enviar"<<endl;
cin>>menu_2;

switch(menu_2){

case 2:{
    thread send_(send_t,socket);
    send_.detach();

    }break;

case 1:

    thread recv_(recv_t,socket);

    recv_.detach();

    break;

}






    pthread_exit(NULL);
}
