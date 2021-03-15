
#include<iostream>
#include<fstream>
#include"source.h"

using std::cout;
using std::endl;

void SOURCE::COMPORTEMENT(){

	std::ifstream fileStream("input_samples.txt");
	float tmp_valreal, tmp_valimg;
	if(!fileStream)
		cout<<"le fichier ne peut pas etre trouve"<<endl;
	wait();
	while(1){
		if(!fileStream.eof){
			if(FIFO_OUT.num_free()>1){
				fileStream>>tmp_valreal;
				fileStream>>tmp_valimg;
				FIFO_OUT.write(tmp_valreal);
				FIFO_OUT.write(tmp_valimg);
				wait();
			}
			else
				cout<<"pas assez d'espace,attends"<<endl;
		}
		else{
			cout<<"fin de fichier"<<endl
			wait();
		}	

	}
	


}
