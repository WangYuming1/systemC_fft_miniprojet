
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
		data_req=true;								//data_req initialized to 1 in each reading data from fft.
		if (count>31) {
			cout<< "finish writing" <<endl;
			data_req=false;
			break;		
		}
		if(data_valid && data_req) {				//when the fft has valid data and the sink is available to read the data
			tmp_valreal =out_real.read();
			tmp_valimg =out_imag.read();
			fileStream << tmp_valreal;
			fileStream <<" "<<tmp_valimg<< endl;
			count++;
			
		}
		
		wait();
	}
}
