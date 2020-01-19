#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <bitset>
#include <map>
#include <array>
#include <queue>

using namespace std;

int main (int argc, char** argv) {
	ifstream config;
	config.open(argv[1]);

	int m, k;
	config >> m >> k;
 
	config.close();


	ofstream out;
	string out_file_name = string(argv[2]) + ".out";
	out.open(out_file_name.c_str());
	
	ifstream trace;
	trace.open(argv[2]);
	unsigned long pc; bool taken;
	trace >> std::hex >> pc >> taken;
	
	// initialize
	vector<int> bhr(k,1);
	map<string, int> branch;

	while (!trace.eof()) {
		bool prediction;
		prediction = true;
		
		int column = 0;
		int row = 0;
		for (int i=0; i<k; i++){
			int pos = bhr.size()-i-1;
			//out<<"pos"<<pos<<endl;
			//out<<"bhr"<<bhr[pos]<<endl;
			column += bhr[pos]*pow(2, i);
			// out<<"row"<<row<<endl;
		}
			
		int temp = pow(2,m);
		row = pc%temp;
		string addr = to_string(column);
		addr.append(" ");
		addr.append(to_string(row));
		
		if (branch.find(addr) == branch.end()){
			if (taken == 0){
				branch[addr] = 2;
			}
			else{
				branch[addr] = 3;
			}
			prediction = true;
			
		}else{
			prediction = branch[addr]>1?true:false;
			if (taken == 0){
				switch(branch[addr]){
					case 1: branch[addr] = 0;
					break;
					case 2: branch[addr] = 0;
					break;
					case 3: branch[addr] = 2;
					break;
				}
			}
			else {
				switch(branch[addr]){
					case 0: branch[addr] = 1;
					break;
					case 1: branch[addr] = 3;
					break;
					case 2: branch[addr] = 3;
					break;
				}
			}
		}
		
		out << prediction<<endl;
		bhr.push_back(taken==true?1:0);
		trace >> std::hex >> pc >> taken;
	}
	 
	trace.close();	
	out.close();
}
