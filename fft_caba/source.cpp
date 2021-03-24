#include"source.h"
#include<iostream>
#include<fstream>


using std::cout;
using std::endl;

void SOURCE::COMPORTEMENT(){

	std::ifstream fileStream("input_samples.txt");
	sc_int < L > tmp_valreal, tmp_valimg;
	data_valid=false; 
	if(!fileStream)
		cout<<"le fichier ne peut pas etre trouve"<<endl;
	wait();
	int count=0;											//count the data already wrote in
	while(1){
		if(count<32){
			if((!data_valid)&&(data_req)){					//when the data_valid not prepared and not finished writing the data try to write the data

				fileStream>>tmp_valreal;
				fileStream>>tmp_valimg;
				in_real.write(tmp_valreal);
				in_imag.write(tmp_valimg);
				data_valid=true;							//after wrting 2 data in the port , the data_valid set to 1
				count++;
			}
			else if (data_req){
				data_valid=false;							//when the fft can read the data, set data_valid to 0 to start writing new data to the port
			}
		}
		else{
			cout<<"fin de fichier"<<endl;
			data_valid=false;
			break;							//after writing all the data, jump out of the loop. Set the data_valid to 1
		}
		
		wait();
		
	}
}