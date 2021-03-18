
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
	
	int count=0;
	while(1){
		data_req=true;
		if (count>31) {
			cout<< "finish writing" <<endl;
			data_req=false;
			break;		
		}
		if(data_valid && data_req) {	
			tmp_valreal =out_real.read();
			tmp_valimg =out_imag.read();
			fileStream << tmp_valreal;
			fileStream <<" "<<tmp_valimg<< endl;
			count++;
			
		}
		
		wait();
		data_req=false;
	}
}
