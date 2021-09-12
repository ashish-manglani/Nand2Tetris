#include <bits/stdc++.h>
using namespace std;
// @ashish-manglani

int labels_used=0;
vector<string> clear_things_out(string myText)
{
    std::vector<string> output;
    string temp="";
    for(int i=0;i<myText.size() and myText[i]!='/';i++)
    {
        if(myText[i]==' ' || myText[i]=='\n' || myText[i]=='\r')
        {
            if(temp.size())
            {
                output.push_back(temp);
                temp.clear();
            }
        }
        else
            temp.push_back(myText[i]);
    }
    if(temp.size())
        output.push_back(temp);
    return output;
}

string push_it(string segment, string index)
{
    // need to get value from the segment and push that value to the stack
    // required index in ram=segment_base_address+index

    // @index
    // D=A

    // @base_add
    // A=A+D    // fetch value from segment[index]

    // D=M

    // @SP
    // A=M      // write to address pointed by stack pointer
    // M=D

    // @SP
    // M=M+1

    string result="";
    result+="@"+index+'\n'+"D=A"+'\n';

    if (segment == "constant") 
    {
        ; // do nothing
    }
    else if (segment == "static") 
    {
        result += "@16\n";    // base address is 16
        result += "A=A+D\nD=M\n";
    }
    else if (segment == "temp") 
    {
        result += "@5\n";    // base address is 5
        result += "A=A+D\nD=M\n";
    }
    else if (segment == "local") 
    {
        result += "@LCL\n";  // base address is stored in lcl
        result += "A=M\n";  // A=*lcl
        result += "A=A+D\nD=M\n";
    }
    else if (segment == "argument") 
    {
        result += "@ARG\n"; // base address is stored in ARG
        result += "A=M\n";  // A=*Arg
        result += "A=A+D\nD=M\n";
    }
    else if (segment == "this") 
    {
        result += "@THIS\n";    // base address is stored in THIS
        result += "A=M\n";  // A=*THIS
        result += "A=A+D\nD=M\n";
    }
    else if (segment == "that") 
    {
        result += "@THAT\n";    // base address is stored in THAT
        result += "A=M\n";  // A=*THAT
        result += "A=A+D\nD=M\n";
    }
    else if (segment == "pointer") 
    {
        if(index=="0")
        {
            result += "@THIS\n";
        }
        else
        {
            result += "@THAT\n";
        }
        result += "D=M\n";
    }

    result+="@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    return result;
}

string pop_it(string segment,string index)
{
    // need to get value from the last element of the stack and pop it into D-register
    // put this popped value value to segment[index]

    // @SP
    // M=M-1    // popped last element

    // A=M
    // D=M      // stored the popped value

    // using general purpose registers to temporarily store the popped value
    // @13
    // M=D    // Ram[13] contains popped value

    // @index
    // D=A

    // @base_add
    // D=A+D

    // using general purpose registers to temporarily store the final address
    // @14
    // M=D  // final address in ram[14]
    

    // Now we have both final address and the value we want to write
    // @13
    // D=M

    // @14
    // A=M

    // M=D

    string result="";

    string part1="@SP\nM=M-1\nA=M\nD=M\n@13\nM=D\n";
    part1+="@"+index+'\n'+"D=A\n";

    string part2="@14\nM=D\n@13\nD=M\n@14\nA=M\nM=D\n";

    if (segment == "constant") 
    {
        ; // do nothing
    }
    else if (segment == "static") 
    {
        result = part1;
        result += "@16\n";    // base address is 16
        result += "D=A+D\n";
        result += part2;
    }
    else if (segment == "temp") 
    {
        result = part1;
        result += "@5\n";    // base address is 5
        result += "D=A+D\n";
        result += part2;
    }
    else if (segment == "local") 
    {
        result = part1;
        result += "@LCL\n";  // base address is stored in lcl
        result += "A=M\n";  // A=*lcl
        result += "D=A+D\n";
        result += part2;
    }
    else if (segment == "argument") 
    {
        result = part1;
        result += "@ARG\n"; // base address is stored in ARG
        result += "A=M\n";  // A=*Arg
        result += "D=A+D\n";
        result += part2;
    }
    else if (segment == "this") 
    {
        result = part1;
        result += "@THIS\n";    // base address is stored in THIS
        result += "A=M\n";  // A=*THIS
        result += "D=A+D\n";
        result += part2;
    }
    else if (segment == "that") 
    {
        result = part1;
        result += "@THAT\n";    // base address is stored in THAT
        result += "A=M\n";  // A=*THAT
        result += "D=A+D\n";
        result += part2;
    }
    else if (segment == "pointer") 
    {
        result = "@SP\nM=M-1\nA=M\nD=M\n";
        if(index=="0")
        {
            result += "@THIS\n";
        }
        else
        {
            result += "@THAT\n";
        }
        result += "M=D\n";
    }
    return result;
}

string arithmetic_logical(string operation)
{
    // pop 1st operand
    // @SP
    // M=M-1
    // A=M

    /*if(binary_operator)
    {
        // pop 2nd operand
        D=M
        @SP
        M=M-1;
        A=M
    }*/

    /*if(arithmetic_operator)
    {
        Apply computation
        M=result of computation
    }*/

    /*if(relational_operator)
    {
        D=M-D
        @label i
        D;condition      (jump to satisfied if condition is met)

        D=0     if not satisfied store D=false

        @label i+1
        0;JMP

        (label i)
        D=-1    // D=true, 2's compliment
        
        (label i+1)
        @SP
        A=M
        M=D
    }*/
    
    // @SP
    // M=M+1;

    string label1=to_string(labels_used+1);
    string label2=to_string(labels_used+2);

    string result="@SP\nM=M-1\nA=M\n";
    string Binary="D=M\n@SP\nM=M-1\nA=M\n";
    string computation="";

    string Relational_part1="D=M-D\n";
    Relational_part1+="@label"+label1+'\n'+"D;";
    string jump_condition="";
    string Relational_part2="D=0\n@label"+label2+"\n0;JMP\n"+"(label"+label1+")\nD=-1\n"+"(label"+label2+")\n@SP\nA=M\nM=D\n";

    string end_code="@SP\nM=M+1\n";


    if(operation=="add")    // binary
    {
        result+=Binary;
        computation="M=M+D\n";
    }
    else if(operation=="sub")   // binary
    {
        result+=Binary;
        computation="M=M-D\n";
    }
    else if(operation=="neg")   // unary
    {
        computation="M=-M\n";
    }
    else if(operation=="eq")  // relational
    {
        labels_used+=2;
        result+=Binary;
        result+=Relational_part1;
        jump_condition="JEQ\n";
        result+=jump_condition;
        result+=Relational_part2;
    }
    else if(operation=="gt")  // relational
    {
        labels_used+=2;
        result+=Binary;
        result+=Relational_part1;
        jump_condition="JGT\n";
        result+=jump_condition;
        result+=Relational_part2;
    }
    else if(operation=="lt")  // relational
    {
        labels_used+=2;
        result+=Binary;
        result+=Relational_part1;
        jump_condition="JLT\n";
        result+=jump_condition;
        result+=Relational_part2;
    }
    else if(operation=="and")   // binary
    {
        result+=Binary;
        computation="M=M&D\n";
    }
    else if(operation=="or")    // binary
    {
        result+=Binary;
        computation="M=M|D\n";
    }
    else if(operation=="not") // unary
    {
        computation="M=!M\n";
    }

    result+=computation+end_code;
    return result;
}

string translate(string myText)
{
    vector<string> parsed=clear_things_out(myText);
    string comment="// ";
    for(auto data:parsed)
    {
        comment+=data+" ";
    }
    comment+="\n";
    
    if(parsed.size()==0)
        return "";
    else if(parsed[0]=="push")
    {
        return comment+push_it(parsed[1],parsed[2]);
    }
    else if(parsed[0]=="pop")
    {
        return comment+pop_it(parsed[1],parsed[2]);
    }
    else
    {
        return comment+arithmetic_logical(parsed[0]);
    }
}

int main()
{
    // getting input file
    string file_name;
    cin>>file_name;
    ifstream MyReadFile(file_name);
    
    //create output file
    string output_file=file_name.substr(0,file_name.length()-3)+".asm";
    ofstream MyWriteFile(output_file);

    // reading line by line
    string myText;
    while (getline (MyReadFile, myText)) 
    {
        string write=translate(myText);
        if(write.size()!=0)
            MyWriteFile<<write<<endl;
    }
    return 0;
}
