#include <windows.h>
#include <iostream>
#include "dirent.h"
#include <vector>
#include <fstream>
using namespace std;

struct data{
	
	int dia;
	int mes;
	int ano;
	int hora;
	int minuto;
	
};

class file {
	
	public:
		char *getName();
		bool atualizou();
		file(char * name,char * diretorio);
		void atualizar();
		void printdata();
	private:
		char fileName[64];
		data antiga;
		data nova;

		
};


char* file::getName(){
	return this->fileName;
}

bool file::atualizou(){
	
	if(this->nova.ano > this->antiga.ano){
		return true;
	}
	else if(this->nova.mes > this->antiga.mes){
		return true;
	}
	else if(this->nova.dia > this->antiga.dia){
		return true;
	}
	else if(this->nova.hora > this->antiga.hora){
		return true;
	}
	else if(this->nova.minuto > this->antiga.minuto){
		return true;
	}
	
	return false;
}

file::file(char * name,char * diretorio){
	
	char aux[100];
	strcpy (aux,diretorio);
	strcat (aux,"/");
  	strcat (aux,name);
	
	strcpy(this->fileName,aux);
		
	this->atualizar();
	

}

void file::printdata(){
	
		printf("Nome: %s\n",this->fileName);
		
	    printf("Data: %02d/%02d/%d \nHora: %02d:%02d \n",
        this->nova.dia,this->nova.mes , this->nova.ano,
        this->nova.hora, this->nova.minuto);
        cout<<endl;
}

void file::atualizar(){
	
	    HANDLE hFile = CreateFile(TEXT(this->fileName),
                   GENERIC_READ,         
                   FILE_SHARE_READ,       
                   NULL,                 
                   OPEN_EXISTING,         
                   FILE_ATTRIBUTE_NORMAL,
                   NULL);                 
 
    FILETIME ftCreate, ftAccess, ftWrite;
    SYSTEMTIME stUTC, stLocal;

   
    GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite);

   
    FileTimeToSystemTime(&ftWrite, &stUTC);
    SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

    this->antiga.ano = this->nova.ano;
    this->antiga.mes = this->nova.mes;
    this->antiga.dia = this->nova.dia ;
    this->antiga.hora = this->nova.hora;
    this->antiga.minuto = this->nova.minuto ;
    
    
    this->nova.ano = stLocal.wYear;
    this->nova.mes = stLocal.wMonth;
    this->nova.dia = stLocal.wDay;
    this->nova.hora = stLocal.wHour;
    this->nova.minuto = stLocal.wMinute;
    
    CloseHandle(hFile);
	
}
