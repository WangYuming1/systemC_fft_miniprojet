
#include<iostream>
#include<fstream>
#include"sink.h"

using std::cout;
using std::endl;

void SINK::COMPORTEMENT(){

	std::ofstream fileStream("out_samples.txt");
	float tmp_valreal, tmp_valimg;
	if(!fileStream)
		cout<<"le fichier ne peut pas etre trouve"<<endl;
	wait();
	while(1){

		if(FFT_OUT.num_available() > 1) {	
			tmp_valreal =FFT_OUT.read();
			tmp_valimg =FFT_OUT.read();
			fileStream << tmp_valreal;
			fileStream << tmp_valimg;
			cout << "writing" << endl;
		}
		else 
			cout<<"pas assez data";
		wait();
	}
}
