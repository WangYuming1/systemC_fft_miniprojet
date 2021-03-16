
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
	data_req=true;
	int count=0;
	while(1){
		if (count>16) {
			cout<< "finish writing" <<endl;
			data_req=false;
			break;
		}
		else if(data_valid && data_req) {	
			tmp_valreal =out_real.read();
			tmp_valimg =out_imag.read();
			cout<<" "<< tmp_valreal;
			cout<<" "<< tmp_valimg;
			fileStream << tmp_valreal;
			fileStream <<" "<<tmp_valimg<< endl;
			count++;
			cout << "writing" << endl;
		}
		else 
			cout<<" data not valid yet in FFT";
		wait();
	}
}
