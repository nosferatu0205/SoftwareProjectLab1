#include<bits/stdc++.h>

#include<graphics.h>



using namespace std;
int main(){
    string inputExp;
    cout<<"Please enter expression to be evaluated: ";
    cin>>inputExp;

    /*//karnaugh map to solve boolean problem

    //initialize the map
    int map[4][4];
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            map[i][j]=0;
        }
    }
    
    //initialize the truth table
    int truthTable[16];
    for(int i=0;i<16;i++){
        truthTable[i]=0;
    }*/

    //initialize string to store input expression
    
    //converting string to Chomsky normal form
    string cnfExp;
    cnfExp=inputExp;
    int cnfExpLength=cnfExp.length();
    for(int i=0;i<cnfExpLength;i++){
        if(cnfExp[i]=='.'){
            cnfExp[i]='^';
        }
    }


    //initialize stack to store operators
    stack<char> opStack;

    //initialize stack to store operands
    stack<char> opdStack;

    //initialize stack to store result
    stack<char> resStack;

    //convert input expression to postfix 
    for(int i=0;i<inputExp.length();i++){
        if(inputExp[i]=='('){
            opStack.push(inputExp[i]);
        }
        else if(inputExp[i]==')'){
            while(opStack.top()!='('){
                opdStack.push(opStack.top());
                opStack.pop();
            }
            opStack.pop();
        }
        else if(inputExp[i]=='&' || inputExp[i]=='|' || inputExp[i]=='^'){
            while(!opStack.empty() && opStack.top()!='('){
                opdStack.push(opStack.top());
                opStack.pop();
            }
            opStack.push(inputExp[i]);
        }
        else{
            opdStack.push(inputExp[i]);
        }
    }
    

    //searching for AND and OR operators
    for(int i=0; i<inputExp.length(); i++){
        if(inputExp[i]=='+'){
            cout<<"AND operator found at position "<<i<<endl;
            //and gate logic diagram printing

            }
        else if(inputExp[i]=='|'){
            cout<<"OR operator found at position "<<i<<endl;
            //or gate logic diagram printing

        }
        else if(inputExp[i]=='^'){
            cout<<"XOR operator found at position "<<i<<endl;
            //xor gate logic diagram printing
        }
    }
}