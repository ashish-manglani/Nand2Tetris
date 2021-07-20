#include <bits/stdc++.h>
using namespace std;
// @ashish-manglani
bool isNumber(string& str)
{
    for(char c:str){
        if(isdigit(c) == 0) return false;
    }
    return true;
}


void clear_things_out(string &myText)
{
    myText.erase(std::remove_if(myText.begin(), myText.end(), ::isspace), myText.end());
    string temp="";
    int i=0;
    while(i<myText.length() and myText[i]!='/')
    {
        temp.push_back(myText[i]);
        i++;
    }
    myText=temp;
}

int main()
{
	// getting input file
	string file_name;
	cin>>file_name;
	ifstream MyReadFile(file_name);
	
	//create output file
	string output_file=file_name.substr(0,file_name.length()-4)+".hack";
	ofstream MyWriteFile(output_file);
	
	std::map<string, int> address;	// for symbols and labels
	
	// create destination_map
	map<string,string> destination_map;
	destination_map["M"]="001";
	destination_map["D"]="010";
	destination_map["MD"]="011";
	destination_map["A"]="100";
	destination_map["AM"]="101";
	destination_map["AD"]="110";
	destination_map["AMD"]="111";
	
	// create jump_map
	map<string,string> jump_map;
	jump_map["JGT"]="001";
	jump_map["JEQ"]="010";
	jump_map["JGE"]="011";
	jump_map["JLT"]="100";
	jump_map["JNE"]="101";
	jump_map["JLE"]="110";
	jump_map["JMP"]="111";
	
	// create comp_map
	map<string,string> comp_map;
	comp_map["0"]="0101010";
	comp_map["1"]="0111111";
	comp_map["-1"]="0111010";
	comp_map["D"]="0001100";
	comp_map["A"]="0110000";
	comp_map["!D"]="0001101";
	comp_map["!A"]="0110001";
	comp_map["-D"]="0001111";
	comp_map["-A"]="0110011";
	comp_map["D+1"]="0011111";
	comp_map["A+1"]="0110111";
	comp_map["D-1"]="0001110";
	comp_map["A-1"]="0110010";
	comp_map["D+A"]="0000010";
	comp_map["D-A"]="0010011";
	comp_map["A-D"]="0000111";
	comp_map["D&A"]="0000000";
	comp_map["D|A"]="0010101";
	
	comp_map["M"]="1110000";
	comp_map["!M"]="1110001";
	comp_map["-M"]="1110011";
	comp_map["M+1"]="1110111";
	comp_map["M-1"]="1110010";
	comp_map["D+M"]="1000010";
	comp_map["D-M"]="1010011";
	comp_map["M-D"]="1000111";
	comp_map["D&M"]="1000000";
	comp_map["D|M"]="1010101";
	
	
	
	// store built-in symbols
	
    address["SP"]= 0;
	address["LCL"]= 1;
	address["ARG"]= 2;
	address["THIS"]= 3;
	address["THAT"]= 4;
	address["R0"]= 0;
	address["R1"]= 1;
	address["R2"]= 2;
	address["R3"]= 3;
	address["R4"]= 4;
	address["R5"]= 5;
	address["R6"]= 6;
	address["R7"]= 7;
	address["R8"]= 8;
	address["R9"]= 9;
	address["R10"]=10;
	address["R11"]=11;
	address["R12"]=12;
	address["R13"]=13;
	address["R14"]=14;
	address["R15"]=15;
	address["SCREEN"]= 16384;
	address["KBD"]= 24576;
	
	// first pass, look for labels
    int nxt_instruction=0;
    string myText;
    while (getline (MyReadFile, myText)) 
    {
        clear_things_out(myText);
        // std::cout << myText << std::endl;
        if(myText.length()==0)
            continue;
        if(myText[0]=='(')
        {
            string temp=myText.substr(1,myText.length()-2);
            address[temp]=nxt_instruction;
        }
        else
            nxt_instruction++;
    }
    
    // second pass, look for variables
    MyReadFile.clear();
    MyReadFile.seekg(0,std::ios::beg);
    
    int nxtmemory=16;
    while (getline (MyReadFile, myText)) 
    {
        clear_things_out(myText);
        
        if(myText.length()==0 || myText[0]!='@')    // variable appears only in a-insruction
            continue;
        string temp=myText.substr(1,myText.length()-1);
        if(isNumber(temp))
            continue;
        if(address.find(temp)==address.end())
        {
            address[temp]=nxtmemory;
            nxtmemory++;
        }
    }
    
    // 3rd pass -> convert from assembly to machine
    
    MyReadFile.clear();
    MyReadFile.seekg(0,std::ios::beg);
    while (getline (MyReadFile, myText)) 
    {
        clear_things_out(myText);
        if(myText.length()==0)
            continue;
        
        // handel a-instruction
        if(myText[0]=='@')
        {
            string val_a=myText.substr(1,myText.length()-1);
            int int_val_a;
            if(isNumber(val_a))
            {
                int_val_a=stoi(val_a);
            }
            else int_val_a=address[val_a];
            string write="";
            int cntr=15;
            while(cntr--)
            {
                write+=to_string(int_val_a%2);
                int_val_a/=2;
            }
            write.push_back('0');
            reverse(write.begin(),write.end());
            MyWriteFile<<write<<endl;
        }
        
        // handel pseudo-instruction
        else if (myText[0]=='(')
        {
            continue;
        }
        
        // handel c-instruction
        else
        {
            string write="111";
            // check if assignment or jump
            int assignment=0,jump=0;
            for(auto ash:myText)
            {
                if(ash=='=')
                    assignment=1;
                else if(ash==';')
                    jump=1;
            }
            
            // handel assignment
            if(assignment)
            {
                string dest="";
                int strt=0;
                while(strt<myText.length() and myText[strt]!='=')
                {
                    dest+=myText[strt];
                    strt++;
                }
                string comp="";
                strt++;
                while(strt<myText.length())
                {
                    comp+=myText[strt];
                    strt++;
                }
                // cout<<comp<<endl;
                write+=comp_map[comp];
                
                write+=destination_map[dest];
                
                write+="000"; // no-jump
            }
            
            // handel jump
            if(jump)
            {
                string comp="";
                int strt=0;
                while(strt<myText.length() and myText[strt]!=';')
                {
                    comp+=myText[strt];
                    strt++;
                }
                string jmp="";
                strt++;
                while(strt<myText.length())
                {
                    jmp+=myText[strt];
                    strt++;
                }
                
                write+=comp_map[comp];
                
                write+="000";   // no-destination
                
                write+=jump_map[jmp];
            }
            MyWriteFile<<write<<endl;
        }
    }
    
}
