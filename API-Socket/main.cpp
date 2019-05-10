#include <cstdlib>
#include <iostream>
#include "Socket.h"
#include "ServerSocket.h"
#include "InetAddress.h"
#include <thread>
#include <stdlib.h>
#include <fstream>
#include "diretorio.h"


#define BUFFER_SIZE 512

using namespace std;
char msg_recv[1024];
char msg_send[BUFFER_SIZE];


void send_t(Socket * s){
diretorio *main= new diretorio("main");
size_t block_size = 0;

cout<<"entrou"<<endl;
  if(main->atualizar()){
            ifstream arquivo("check.txt");
            char filename[24];
            string filename_str;
                   while(getline(arquivo,filename_str)){
                        Sleep(1);
                        strcpy(filename,&filename_str[0]);
                        FILE *arq_in;
                        arq_in = fopen(filename,"rb");

                            if (arq_in == NULL)  // Se houve erro na abertura
                            {
                                 printf("Problemas na abertura do arquivo\n");
                                 return ;
                            }

                        s->send(filename,BUFFER_SIZE);

                        while(true){
                            try
                            {
                                memset(&msg_send, 0, BUFFER_SIZE);
                                block_size = fread (msg_send, sizeof(char),BUFFER_SIZE, arq_in);

                                if(block_size <= 0)
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
                            Sleep(1);
                        }

                    fclose(arq_in);
                    s->send("end",5);
                   }
                   arquivo.close();
                   s->send("parar",5);


  }

}




void recv_t(Socket * s){
char filename[64];

while(true){

        memset(&msg_recv, 0, BUFFER_SIZE);
        s->recv(msg_recv,BUFFER_SIZE);

        if(strcmp("parar",msg_recv) == 0){
            break;
        }

        strcpy(filename,msg_recv);

        FILE *arq_out;
        arq_out = fopen(filename, "wb");
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

                    if(strcmp("end",msg_recv) == 0)
                        break;

                    cout << block_size << endl;
                    fwrite(msg_recv, sizeof(char),block_size, arq_out);


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
}


void accept_t(Socket * s,ServerSocket *Serve){
system("CLS");
s = Serve->accept();
    thread send_(send_t,s);
    thread recv_(recv_t,s);
        try{
            recv_.join();
            cout << "Recebeu" << endl;
            send_.join();
        }
         catch (exception& e)
        {
         cout << e.what() << '\n';
        }


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


    InetAddress * servAddr;

    cout<<"1.Servidor "<<endl;
    cout<<"2.Cliente "<<endl;
    cin>>menu_1;

switch(menu_1){

    case 1:{
        while(true){

            cout<<"Qual a porta deseja usar?"<<endl;
            cin>>porta;

            try{

                ServerSocket * server;
                Socket * socket_t;
                server = new ServerSocket(porta);
                thread acept(accept_t,socket_t,server);
                acept.detach();

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
        }
    }break;

    case 2:{
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
                thread recv_(recv_t,socket);
                thread send_(send_t,socket);

        system("CLS");
        try{
            send_.join();
            cout << "Enviou" << endl;
            recv_.join();
            cout << "Recebeu" << endl;
           }
            catch (exception& e)
            {
                cout << "cliente"<<e.what() << '\n';
            }


    }break;




    pthread_exit(NULL);
}
}
