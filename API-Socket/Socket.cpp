#include "Socket.h"

//Cria um objeto socket não conectado.
Socket::Socket(){

    this->descritor = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

};

//Cria um socket e o conecta a um número de porta e em um endereço IP específicos.
Socket::Socket(InetAddress *addr, int port)  throw (IOException){

    this->descritor = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (this->descritor == INVALID_SOCKET){

       throw IOException("Erro ao criar o socket");
    }

    this->remotePort = port;

    this->remoteAddr  = addr;
    this->remoteAddr->ip_address.sin_port = htons(port);

    this->localAddr = InetAddress::getLocalHost();
    this->localAddr->ip_address.sin_port = htons(port);

    this->connect(this->remoteAddr);

    };
//Cria um socket e o conecta para um número de porta e nome de host específico.
Socket::Socket(string hostName, int port) throw (IOException, UnknownHostException){

    this->remotePort = port;

    this->remoteAddr  = InetAddress::getByName(hostName);
    this->remoteAddr->ip_address.sin_port = htons(port);

    this->localAddr = InetAddress::getLocalHost();
    this->localAddr->ip_address.sin_port = htons(port);


    this->connect(this->remoteAddr);

    };


void Socket::connect(InetAddress *remoteAddr)throw (IOException, UnknownHostException){

this->descritorRemote = ::connect(this->descritor, (struct sockaddr *) &(this->localAddr)->ip_address, sizeof(remoteAddr->ip_address));

        if (this->descritorRemote == SOCKET_ERROR){

            throw IOException("Erro ao conectar");
        }

};
    //Envia a string no array msg para o socket remoto.
void Socket::operator<<(const char* msg) throw (IOException){



};

    //Envia os bytes armazenados no array msg, no intervalo [0 size], para o socket remoto.
int Socket::send(char * msg,int size) throw (IOException){


    int message_length = strlen(msg);
    this->descritorRemote = ::send(this->descritor, msg, message_length, 0);
        // envia a mensagem para o servidor
    if (this->descritorRemote == SOCKET_ERROR)
    {
        throw IOException("Erro");
    }
    return this->descritorRemote;

};
    //Ler a string do socket remoto e armazena no array msg.
void Socket::operator>>(const char* msg) throw (IOException)
{


};
    //Ler size bytes do socket remoto e armazena no array msg.
int Socket::recv(char * msg,int size) throw (IOException)
{

    int message_length = ::recv(this->descritor, msg, size, 0);

    if(message_length == SOCKET_ERROR)
        throw IOException("Erro na mensagem");



    return message_length;

};

    //Retorna o endereço em que o socket está conectado.
InetAddress* Socket::getInetAddress(){

    return this->remoteAddr;

};

    //Retorna o endereço local em que o socket está amarrado.
InetAddress* Socket::getLocalAddress(){

    return this->localAddr;

};
    //Retorna o número porta local em que o socket está amarrado.
int Socket::getLocalPort(){

return this->localPort;


};
    //Retorna o número da porta remota em que o socket está conectado.
int Socket::getPort(){

    return this->remotePort;
};

int Socket::getDescritor(){
        return this->descritor;
}

