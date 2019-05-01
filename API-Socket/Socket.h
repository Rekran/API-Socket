#ifndef SOCKET_H
#define SOCKET_H

#include "IOException.h"
#include "InetAddress.h"
#include <stdio.h>

class ServerSocket;

class Socket
{
public:
    //Cria um objeto socket não conectado.
    Socket();
    //Cria um socket e o conecta a um número de porta e em um endereço IP específicos.
    Socket(InetAddress *addr, int port) throw (IOException);
    //Cria um socket e o conecta para um número de porta e nome de host específico.
    Socket(string hostName, int port) throw (IOException, UnknownHostException);
    //Fecha este socket.
    void close() throw (IOException);

    //Envia a string no array msg para o socket remoto.
    void operator<<(const char* msg) throw (IOException);
    //Envia os bytes armazenados no array msg, no intervalo [0 size], para o socket remoto.
    int send(char * msg,int size) throw (IOException);
    //Ler a string do socket remoto e armazena no array msg.
    void operator>>(const char* msg) throw (IOException);
    //Ler size bytes do socket remoto e armazena no array msg.
    int recv(char * msg,int size) throw (IOException);


    //Retorna o endereço em que o socket está conectado.
    InetAddress *getInetAddress();
    //Retorna o endereço local em que o socket está amarrado.
    InetAddress *getLocalAddress();
    //Retorna o número porta local em que o socket está amarrado.
    int getLocalPort();
    //Retorna o número da porta remota em que o socket está conectado.
    int getPort();

    int getDescritor();
    ~Socket();//destrutor
      int descritorRemote;
private:
    void connect(InetAddress* remoteAddr)throw (IOException, UnknownHostException);
    int descritor;

    int localPort;
    int remotePort;
    InetAddress *localAddr;
    InetAddress *remoteAddr;
    friend void recv_t(Socket *s);
    friend class ServerSocket;

};
 #endif
