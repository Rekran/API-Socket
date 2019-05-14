#include "file.h"


class diretorio {

	public:
		diretorio(char* name);
		bool atualizar();
		bool esta(file file_);
		bool esta_pasta(file check);
		void print_diret();
		void pesistencia();
		vector<file*>arquivos;

	private:

		vector<file*>atualizados;
		char diretc_name[24];

};
