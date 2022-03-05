#include<bits/stdc++.h>

#define boolAdd(x) x + 0 = x;

#define boolAdd0(x) x + 1 = 1;

#define boolAddSelf(x) x + x = x;

#define boolAddComplement(x) x + !x = 1;

//#include<graphics.h>
using namespace std;
//function to calculate length of string
int strLength(string str)
{
    int len = 0;
    while(str[len] != '\0')
    {
        len++;
    }
    return len;
}


bool isOperator(char c)
{
    return (!isalpha(c) && !isdigit(c));
}
 
int getPriority(char C)
{
    if (C == '-' || C == '+')
        return 1;
    else if (C == '*' || C == '/')
        return 2;
    else if (C == '^')
        return 3;
    return 0;
}
 
string infixToPostfix(string infix)
{
    infix = '(' + infix + ')';
    int l = strLength(infix);
    stack<char> char_stack;
    string output;
 
    for (int i = 0; i < l; i++) {
 
        // Checking for operand and adding to stack
        if (isalpha(infix[i]) || isdigit(infix[i]))
            output += infix[i];
 
        //Pushing all detected '(' to the stack)
        else if (infix[i] == '(')
            char_stack.push('(');
 
        //Starting popping when ')' is detected until next '('
        else if (infix[i] == ')') {
            while (char_stack.top() != '(') {
                output += char_stack.top();
                char_stack.pop();
            }
 
            // Remove '(' from the stack
            char_stack.pop();
        }
 
        // Operator found
        else{
            if (isOperator(char_stack.top())){
                if(infix[i] == '^'){
                      while (getPriority(infix[i]) <= getPriority(char_stack.top())){
                         output += char_stack.top();
                         char_stack.pop();
                       }
                     
                }
                else{
                    while (getPriority(infix[i]) < getPriority(char_stack.top()))
                       {
                         output += char_stack.top();
                         char_stack.pop();
                       }
                     
                }
 
                // Push current Operator on stack
                char_stack.push(infix[i]);
            }
        }
    }
      while(!char_stack.empty()){
          output += char_stack.top();
        char_stack.pop();
    }
    return output;
}
 
string infixToPrefix(string infix)
{
    /* Reverse String and replace opening and closing parentheses */
    int l = infix.size();
 
    // Reverse infix
    for (int i = 0; i < l / 2; i++) {
        char temp = infix[i];
        infix[i] = infix[l - i - 1];
        infix[l - i - 1] = temp;
    }
 
    // Replace ( with ) and vice versa
    for (int i = 0; i < l; i++) {
 
        if (infix[i] == '(') {
            infix[i] = ')';
            i++;
        }
        else if (infix[i] == ')') {
            infix[i] = '(';
            i++;
        }
    }
 
    string prefix = infixToPostfix(infix);
 
    // Reverse postfix
    for (int i = 0; i < l / 2; i++) {
        char temp = prefix[i];
        prefix[i] = prefix[l - i - 1];
        prefix[l - i - 1] = temp;
    }
 
    return prefix;
}

using namespace std;
int main(){
    string inputExp;
    cout<<"Please enter expression to be evaluated: ";
    cin>>inputExp;

    string postfixExp = infixToPostfix(inputExp);
    cout<<"Postfix expression: "<<postfixExp<<endl;

    string prefixExp = infixToPrefix(inputExp);
    cout<<"Prefix expression: "<<prefixExp<<endl;

    

    //searching for AND and OR operators
    for(int i=0; i<inputExp.length(); i++){
        if(inputExp[i]=='+'){
            cout<<"AND operator found at position "<<i<<endl;
            //and gate truth table for two variables
            

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