#include "InetAddress.h"
#include <ws2tcpip.h>
#include <iostream>
//Retorna o endereço IP (objeto InetAddress) de um host, dando o nome do host.
InetAddress *InetAddress::getByName(string host) throw (UnknownHostException)
{
    hostent *he = gethostbyname(host.c_str());
    if(he == NULL)
        throw UnknownHostException(host + " is a unknown host.");

    return InetAddress::create(he);
}

//Retorna o endereço IP (objeto InetAddress), dando o endereço IP bruto.
InetAddress *InetAddress::getByAddress(string hostAddr) throw (UnknownHostException)
{
    struct in_addr addr;
    //LINUX : inet_aton(hostAddr.c_str(), &addr);
    //inet_pton(AF_INET, hostAddr.c_str(), &addr);

    addr.S_un.S_addr = inet_addr/**<  */(hostAddr.c_str()); // ip contains 16777343 [0x0100007f in hex]
    hostent *he = gethostbyaddr((const char *)&addr, sizeof(addr), AF_INET);

    if(he == NULL)
    {
        throw UnknownHostException(hostAddr + " is a unknown host.");
    }

    return InetAddress::create(he);
}

InetAddress *InetAddress::create(struct hostent *he)
{
    InetAddress * address = new InetAddress();
    memset(&(*address).ip_address, 0, sizeof(address->ip_address));

    memcpy(&(*address).ip_address.sin_addr.s_addr, he->h_addr_list[0], he->h_length);
    address->ip_address.sin_family = AF_INET;

    address->hostAddr = string(inet_ntoa(*(struct in_addr*)he->h_addr));
    address->hostName = string(he->h_name);

    return address;
}

//Retorna o endereço IP (objeto InetAddress) do host local.
InetAddress *InetAddress::getLocalHost() throw (UnknownHostException)
{
    return InetAddress::getByName("localhost");
}

//Fornece o nome do host
string InetAddress::getHostName()
{
    return hostName;
}
//Fornece o endereço IP do host
string InetAddress::getHostAddress()
{
    return hostAddr;
}


