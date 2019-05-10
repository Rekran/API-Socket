#include "file.h"


class diretorio {

	public:
		diretorio(char* name);
		bool atualizar();
		bool esta(file file_);
		bool esta_pasta(file check);
		void print_diret();
		void pesistencia();

	private:
		vector<file*>arquivos;
		char diretc_name[24];

};
