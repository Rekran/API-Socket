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
