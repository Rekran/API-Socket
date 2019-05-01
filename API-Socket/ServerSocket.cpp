#include "ServerSocket.h"
#define BACKLOG_MAX 5

ServerSocket::ServerSocket()throw (IOException){

// criando o socket local para o servidor
    this->descritor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (this->descritor == INVALID_SOCKET)
    {
        throw IOException("Erro");

    }

};


ServerSocket::ServerSocket(int port) throw (IOException){

this->localAddr = InetAddress::getLocalHost();

// criando o socket local para o servidor
this->descritor = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (this->descritor == INVALID_SOCKET)
    {
        throw IOException("Erro");

    }

this->bind(port);

this->listen();

};


void ServerSocket::bind(int port) throw (IOException){


this->localAddr->ip_address.sin_port = htons(port);

//   interligando o socket com o endereço (local)
    if (::bind(this->descritor,(struct sockaddr *)&(*this->localAddr).ip_address, sizeof(this->localAddr->ip_address)) == SOCKET_ERROR){

        throw IOException("Erro em Bind()");

   }
}

void ServerSocket::listen() throw (IOException){

//coloca o socket para escutar as conexoes
    if (::listen(this->descritor, BACKLOG_MAX) == SOCKET_ERROR){

        throw IOException("Erro em listen()");

    }
}

Socket* ServerSocket::accept() throw (IOException)
{
    std::cout<<"Aceitando conexao"<<std::endl;
    Socket * remoteSocket;
    remoteSocket = new Socket();

    int remote_length =sizeof(remoteSocket->remoteAddr->ip_address);

    remoteSocket->remoteAddr =  InetAddress::getLocalHost();

    remoteSocket->descritor = ::accept(this->descritor, (struct sockaddr *)& remoteSocket->remoteAddr->ip_address,&remote_length );

    if(remoteSocket->descritor == INVALID_SOCKET){

         throw IOException("Erro ao aceitar");
    }

    std::cout<<"Conexao Estabelecida"<<std::endl;
    return remoteSocket;
}
