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
		vector<file>arquivos;
		char diretc_name[24];

};



void diretorio::pesistencia(){
	ofstream myfile;
  	myfile.open ("check.txt");

	for(int i = 0;i < this->arquivos.size();i++){
		file &arquivo = this->arquivos[i];
		myfile << arquivo.getName()<<"\n";
	}
  myfile.close();
}




bool diretorio::esta(file file_){

	for(int i = 0;i < this->arquivos.size();i++){
		file &arquivo = this->arquivos[i];

		if(strcmp(file_.getName(),arquivo.getName()) == 0){
			return true;
		}


	}

	return false;

}




diretorio::diretorio(char* nome){

	strcpy(this->diretc_name,nome);
	this->atualizar();

}

void diretorio::print_diret(){

	for(int i = 0;i < this->arquivos.size();i++ ){

		file &file_ = this->arquivos[i];
		file_.printdata();

	}

}




bool diretorio::esta_pasta(file check){

	int i = 0;
	DIR *dir;
	dirent *ent;

	if ((dir = opendir (this->diretc_name)) != NULL) {
	  while ((ent = readdir (dir)) != NULL ) {
	  	if(i >= 2){

	  		file file_ = file(ent->d_name,this->diretc_name);
            if(strcmp(check.getName(),file_.getName()) == 0){
                return true;

            }
		}
	    i++;
	  }
	  closedir (dir);
	}

return false;
}




bool diretorio::atualizar(){

	bool atualizou = false;
	bool apagar[this->arquivos.size()];
	int i = 0;
	DIR *dir;
	dirent *ent;

	if ((dir = opendir (this->diretc_name)) != NULL) {
	  while ((ent = readdir (dir)) != NULL ) {
	  	if(i >= 2){

	  		file file_ = file(ent->d_name,this->diretc_name);
	  		if(!this->esta(file_)){
				this->arquivos.push_back(file_);
				atualizou = true;
			}
		}
	    i++;
	  }
	  closedir (dir);
	}

	for(int i =0; i < this->arquivos.size();i++ ){
        file &check = arquivos[i];

        if(this->esta_pasta(check)){
            apagar[i] = false;
        }
        else{
            apagar[i] = true;
        }
	}



    for(int i =0; i < this->arquivos.size();i++ ){
        if(apagar[i]){

            arquivos.erase (arquivos.begin()+ i);
            atualizou = true;
        }

    }










	return atualizou;
}
