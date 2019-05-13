#include "diretorio.h"


void diretorio::pesistencia(){
    delete("check.txt");
	ofstream myfile;
  	myfile.open ("check.txt");

  myfile.close();
}




bool diretorio::esta(file file_){

	for(int i = 0;i < this->arquivos.size();i++){

		file *arquivo = this->arquivos[i];
		if(strcmp(file_.getName(),arquivo->getName()) == 0){
			return true;
		}
	}
	return false;
}




diretorio::diretorio(char* nome){

	strcpy(this->diretc_name,nome);

}

void diretorio::print_diret(){

	for(int i = 0;i < this->arquivos.size();i++ ){

		file *file_ = this->arquivos[i];
		file_->printdata();

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
	int i = 0;
	DIR *dir;
	dirent *ent;

    ofstream myfile;
  	myfile.open ("check.txt");

	if ((dir = opendir (this->diretc_name)) != NULL) {
	  while ((ent = readdir (dir)) != NULL ) {
	  	if(i >= 2){

	  		file *file_ = new file(ent->d_name,this->diretc_name);
            if(!this->esta((*file_))){

                this->arquivos.push_back(file_);
                myfile << file_->getName()<<"\n";
				atualizou = true;
			}
		}
	    i++;
	  }
	  closedir (dir);
	}
	myfile.close();
	return atualizou;

}

