//Creado por Elias Rodriguez Chimal

#include<iostream>
#include<fstream>
#include<vector>
#include<dirent.h>

using namespace std;

class Objeto{
	public:
		vector<string> files;
		vector<string> size;
};

int recorrer(string path, Objeto& listaV, int &subIndex){
	subIndex++;
	int sumTotal = 0, nuevaSuma = 0;
	string fileName = " ", newPath = " ";
   	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (path.c_str())) != NULL) {
	  while ((ent = readdir (dir)) != NULL) {
	  	fileName = ent->d_name;
	  	newPath = path+"/"+fileName;
	    ifstream in_file(newPath, ios::binary);
	   	in_file.seekg(0, ios::end);
	   	int file_size = in_file.tellg();
	   	if(file_size!=-1 && fileName!="." && fileName!=".."){
	   		sumTotal+=file_size;
	   		if(subIndex<=1){
	   			listaV.files.push_back("\"name\":\""+fileName+"\"");
	   			listaV.size.push_back("\"size\":"+to_string(file_size));
	   		}	
	   	}else if(file_size==-1 && fileName!="." && fileName!=".."){
	  		nuevaSuma = recorrer(newPath, listaV, subIndex);
			sumTotal += nuevaSuma;
	  		if(subIndex<=1){
	  			listaV.files.push_back("\"name\":\""+fileName+"\"");
	  		}
	   	}
	  }
	  closedir (dir);
	} else {
	  perror ("No se pudo abrir el archivo");
	}
	if(subIndex<=2){
		listaV.size.push_back("\"size\":"+to_string(sumTotal));
	}
	subIndex--;
	return sumTotal;
}

int main(int argc, char *argv[]) {
	Objeto lista1;
	int subIndex = 0;
	string path = argv[argc-1];
	recorrer(path, lista1, subIndex);
	ofstream jsonFile ("dir.json");
	if(jsonFile.is_open()){
		jsonFile << "{\"files\":[\n";
		for(int i = 0; i<lista1.files.size(); i++){
			jsonFile << "	{";
			jsonFile << lista1.files[i];
			jsonFile << ",";
			jsonFile << lista1.size[i];
			if(i == lista1.files.size()-1){
				jsonFile << "}";
			}else{
				jsonFile << "},\n";
			}
		}
		jsonFile << "]}";
	}else{
		cout << "No se pudo crear el archivo JSON";
	}
   	return 0;
}
