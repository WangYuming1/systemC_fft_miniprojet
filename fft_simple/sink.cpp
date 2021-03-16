
#include<iostream>
#include<fstream>
#include"sink.h"

using std::cout;
using std::endl;

void SINK::COMPORTEMENT(){

	std::ofstream fileStream("out_samples.txt");
	float tmp_valreal, tmp_valimg;
	//fileStream.open("out_samples.txt");
	if(!fileStream)
		cout<<"le fichier ne peut pas etre trouve"<<endl;
	wait();
	while(1){

		if(SINK_FIFO_IN.num_available() > 1) {	
			tmp_valreal =SINK_FIFO_IN.read();
			tmp_valimg =SINK_FIFO_IN.read();
			cout<<" "<< tmp_valreal;
			cout<<" "<< tmp_valimg;
		
			fileStream << tmp_valreal;
			fileStream << tmp_valimg;
		
			cout << "writing" << endl;
		}
		else 
			cout<<"pas assez data sink";
		wait();
	}
}
