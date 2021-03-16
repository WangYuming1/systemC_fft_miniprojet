#include"source.h"
#include<iostream>
#include<fstream>


using std::cout;
using std::endl;

void SOURCE::COMPORTEMENT(){

	std::ifstream fileStream("input_samples.txt");
	float tmp_valreal, tmp_valimg;
	data_valid=false; 
	if(!fileStream)
		cout<<"le fichier ne peut pas etre trouve"<<endl;
	wait();
	int count=0;
	while(1){
		if(count<32){
			if((!data_valid)&&(data_req)){

				fileStream>>tmp_valreal;
				fileStream>>tmp_valimg;
			
				cout<< " " << tmp_valimg<< endl;
				cout<< " " << tmp_valreal<< endl;
				in_real.write(tmp_valreal);
				in_imag.write(tmp_valimg);
				data_valid=true;
				count++;
			}
			else{
				data_valid=false;
				cout<<"source data pas valid"<<endl;
			}
		}
		else{
			cout<<"fin de fichier"<<endl;
			break;
			
		}	
		wait();
	}
}
