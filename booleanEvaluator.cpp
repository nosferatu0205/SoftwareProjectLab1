#include <bits/stdc++.h>
#include <graphics.h>
#include <conio.h>
#include <X11/Xlib.h>
#include "simplifier.h"

void drawNot();
void makeOutput();
void drawOr();
void drawAnd();
void setLevel();
void drawXor();

bool boolOR0(bool x)
{
    return x;
}
bool boolOR1(bool x)
{
    return 1;
}
bool boolORSelf(bool x)
{
    return x;
}
bool boolORComplement(bool x)
{
    return 1;
}

bool boolAND1(bool x)
{
    return x;
}
bool boolAND0(bool x)
{
    return 0;
}
bool boolANDself(bool x)
{
    return x;
}
bool boolANDcomplement(bool x)
{
    return 0;
}

#define SIZE 200

char shtack[SIZE];
int top = -1;

char input[SIZE];
char output[SIZE];
char keep[SIZE];
char postfix[SIZE];
int size1, size2 = 0, stackCheck = 0;
int numOfAnd = 0, numOfOr = 0, numOfNot = 0;
int clrOption = 0;
char A, B, str1[2], str2[2];

void makeInfix()
{
    int i, j;

    scanf("%s", input);

    makeOutput();

    for (size1 = 0; input[size1] != '\0'; ++size1)
        ;

    keep[size2] = input[0];
    size2++;

    for (i = 1; i < size1; i++)
    {

        if (input[i] == '(')
        {
            if (input[i - 1] == '+')
            {
                keep[size2] = input[i];
                size2++;
                continue;
            }
            keep[size2] = '*';
            size2++;
            keep[size2] = input[i];
            size2++;
            continue;
        }

        if (((int)input[i] >= 97) && ((int)input[i] <= 122))
        {

            if (input[i - 1] == '+' || input[i - 1] == '-' || input[i - 1] == '(')
            {
                keep[size2] = input[i];
                size2++;
            }
            else
            {
                keep[size2] = '*';
                size2++;
                keep[size2] = input[i];
                size2++;
            }
        }

        else
        {
            keep[size2] = input[i];
            size2++;
        }
    }
}

void push(char item)
{
    if (top >= SIZE - 1)
    {
        printf("Stack Overflow.\n");
    }

    else
    {
        top = top + 1;
        shtack[top] = item;
    }
}

char pop()
{
    char item;

    if (top < 0)
    {
        printf("Stack underflow - invalid infix expression.\n");
        getchar();
        exit(1);
    }

    else
    {
        item = shtack[top];
        top = top - 1;
        return (item);
    }
}

int is_operator(char symbol)
{
    if (symbol == '*' || symbol == '+' || symbol == '-')
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

int precedence(char symbol)
{   if (symbol == '^')
    {
        return (4);
    }
    else if (symbol == '*' || symbol == '-')
    {
        return (3);
    }
    else if (symbol == '+' || symbol == '-')
    {
        return (2);
    }
    else if (symbol == '-')
    {
        return (1);
    }
    else
    {
        return (0);
    }
}

void InfixToPostfix(char infix_exp[], char postfix_exp[])
{
    int i = 0, j = 0;
    char item;
    char x;

    push('(');
    strcat(infix_exp, ")");

    item = infix_exp[i];

    while (item != '\0')
    {
        if (item == '(')
        {
            push(item);
        }
        else if (isdigit(item) || isalpha(item))
        {
            postfix_exp[j] = item;
            j++;
        }
        else if (is_operator(item) == 1)
        {
            x = pop();
            while (is_operator(x) == 1 && precedence(x) >= precedence(item))
            {
                postfix_exp[j] = x;
                j++;
                x = pop();
            }
            push(x);

            push(item);
        }
        else if (item == ')')
        {
            x = pop();
            while (x != '(')
            {
                postfix_exp[j] = x;
                j++;
                x = pop();
            }
        }
        else
        {
            printf("Invalid infix Expression.\n");
            getchar();
            // exit(1);
        }
        i++;

        item = infix_exp[i];
    }

    if (top > 0)
    {
        printf("Invalid infix Expression.\n");
        getchar();
        // exit(1);
    }

    postfix_exp[j] = '\0';
}

void makeString()
{
    if (A == '#')
        str1[0] = ' ', str1[1] = '\0';
    else
        str1[0] = A, str1[1] = '\0';

    if (B == '#')
        str2[0] = ' ', str2[1] = '\0';
    else
        str2[0] = B, str2[1] = '\0';
}

void makeOutput()
{
    int length = strlen(input);

    for (int i = 0; i < length; i++)
    {
        output[i] = input[i];
    }

    output[length] = '\0';
}

void countGates()
{
    int i;
    char ch;
    for (i = 0; postfix[i] != '\0'; i++)
    {
        ch = postfix[i];

        if (ch == '+')
            numOfOr++;
        else if (ch == '-')
            numOfNot++;
        else if (ch == '*')
            numOfAnd++;
    }

    // printf("%d\t%d\t%d\n",numOfAnd,numOfOr,numOfNot);
}

void evaluationOfExpression(char postfix[])
{
    int i;
    char ch, temp = '#';

    for (i = 0; postfix[i] != '\0'; i++)
    {

        if (i == strlen(postfix) - 1)
            stackCheck = 1;

        ch = postfix[i];

        if (isalpha(ch))
        {
            push(ch);
        }

        else if (is_operator(ch))
        {
            if (ch == '-')
            {
                A = pop();

                makeString();
                // SetLevel();
                drawNot();
                push(temp);
            }

            else if (ch == '+')
            {
                A = pop();
                B = pop();

                makeString();

                drawOr();

                push(temp);
            }

            else if (ch == '*')
            {
                A = pop();
                B = pop();

                makeString();

                drawAnd();
                push(temp);
            }
            else if(ch == '^'){
                A = pop();
                B = pop();
                
                makeString();
                drawXor();
                push(temp);
            }
            else if(ch == '&'){
                A = pop();
                B = pop();

                makeString();
                drawXor();
                push(temp);
            }

        }
    }
}

void inputParse()
{
    printf("Enter Expression: ");
    makeInfix();
    InfixToPostfix(keep, postfix);
}

void drawFromExpression()
{
    inputParse();

    int i, flag = 0;

    setLevel();

    countGates();
    evaluationOfExpression(postfix);
}

double levelX = 1, levelY = 1;
double posX, posY, initAngleUpperArc, termAngleUpperArc, radiusUpperArc;
double initAngleOR_Arc1, initAngleOR_Arc2, termAngleOR_Arc1, termAngleOR_Arc2, radiusOR_Arc;
double radiusNOT_circle, halfRadiusNOT_circle, initLineX, initLineY, termLineX, termLineY, rsltLineX, rsltLineY;
int flagAnd = 0, flagOr = 0, flagNot = 0, chck = 0;

double preX = 0, preY = 0, preLY;

void SetVariables()
{
    initAngleUpperArc = -90;
    termAngleUpperArc = 90;
    radiusUpperArc = 29;
    initLineX = posX - 50;
    initLineY = posY;
    termLineX = posX + radiusUpperArc;
    termLineY = posY;
    rsltLineX = posX + 50;
    rsltLineY = posY;
    radiusNOT_circle = 4;

    return;
}

void setLevel()
{
    posX = 120;
    posY = 80;

    posX = posX * levelX;
    posY = posY * levelY;

    SetVariables();
}

void setAngles()
{
    initAngleOR_Arc1 = -90;
    initAngleOR_Arc2 = 20;
    termAngleOR_Arc1 = -25;
    termAngleOR_Arc2 = 90;
    radiusOR_Arc = 50;
}

void drawOr()
{

    setAngles();

    if (chck == 0 && flagOr == 0)
    {
        setLevel();
        chck = 1;

        flagAnd = 1;
        flagNot = 1;
        if (numOfAnd == 0 && numOfNot == 0)
            flagOr = 1;
    }

    else if (flagOr == 0)
    {
        flagAnd = 1;
        flagNot = 1;
        flagOr = 1;

        levelY++;
        preX = rsltLineX + 19;
        preY = rsltLineY;
        setLevel();

        if (preY > initLineY + 15)
            line(preX, preY, preX, initLineY + 15);
        else
            line(preX, preY, preX, initLineY - 55);
    }

    else
    {

        preLY = levelY;
        levelY = (levelY + levelX) / 2;
        levelX++;
        preX = rsltLineX + 19;
        preY = rsltLineY;
        setLevel();

        if (preY > initLineY + 15)
            line(preX, preY, preX, initLineY + 15);
        else if (preLY == levelY)
            line(preX, preY, preX, initLineY - 15);
        else
            line(preX, preY, preX, initLineY - 55);
    }

    arc(posX, posY, initAngleUpperArc, termAngleUpperArc, radiusUpperArc);

    arc(posX, posY + 20, initAngleOR_Arc1, termAngleOR_Arc1, radiusOR_Arc);
    arc(posX, posY - 20, initAngleOR_Arc2, termAngleOR_Arc2, radiusOR_Arc);

    line(rsltLineX - 3, rsltLineY, rsltLineX + 20, rsltLineY);

    circle(initLineX - 1, initLineY - 15, 2);
    circle(initLineX - 1, initLineY + 15, 2);
    line(initLineX, initLineY - 15, termLineX - 6, termLineY - 15);
    line(initLineX, initLineY + 15, termLineX - 6, initLineY + 15);

    outtextxy(initLineX - 2, initLineY + 19, str2);
    outtextxy(initLineX - 2, initLineY - 13, str1);

    if (stackCheck == 1)
        outtextxy(rsltLineX + 10, rsltLineY + 3, output);

    return;
}

void drawAnd()
{
    radiusUpperArc = 35;

    if (chck == 0 && flagAnd == 0)
    {
        setLevel();
        chck = 1;

        if (numOfOr == 0 && numOfNot == 0)
            flagAnd = 1;

        flagNot = 1;
        flagOr = 1;
    }

    else if (flagAnd == 0)
    {
        flagOr = 1;
        flagNot = 1;
        flagAnd = 1;

        levelY++;
        preX = posX + 2 * radiusUpperArc - 1;
        preY = rsltLineY;
        setLevel();

        if (preY > initLineY + 15)
            line(preX, preY, preX, initLineY + 15);
        else
            line(preX, preY, preX, initLineY - 55);
    }

    else
    {

        preLY = levelY;
        levelY = (levelY + levelX) / 2;
        levelX++;
        preX = posX + 2 * radiusUpperArc - 1;
        preY = rsltLineY;
        setLevel();

        if (preY > initLineY + 15)
            line(preX, preY, preX, initLineY + 15);
        else if (preLY == levelY)
            line(preX, preY, preX, initLineY - 15);
        else
            line(preX, preY, preX, initLineY - 55);
    }

    arc(posX, posY, initAngleUpperArc, termAngleUpperArc, radiusUpperArc);

    line(posX, posY + radiusUpperArc, posX, posY - radiusUpperArc);

    line(posX + radiusUpperArc, initLineY, posX + 2 * radiusUpperArc + 10, initLineY);

    circle(initLineX - 1, initLineY - 15, 2);
    circle(initLineX - 1, initLineY + 15, 2);
    line(initLineX, initLineY - 15, posX, initLineY - 15);
    line(initLineX, initLineY + 15, posX, initLineY + 15);

    outtextxy(initLineX - 2, initLineY + 19, str2);
    outtextxy(initLineX - 2, initLineY - 13, str1);

    if (stackCheck == 1)
        outtextxy(posX + radiusUpperArc + 10, initLineY + 3, output);

    return;
}

void drawNot()
{
    if (chck == 0 && flagNot == 0)
    {
        setLevel();
        chck = 1;
    }

    else if (flagNot == 0)
    {

        levelY++;
        flagAnd = 1;
        flagOr = 1;
        setLevel();
    }

    else
    {
        setLevel();
    }

    halfRadiusNOT_circle = radiusNOT_circle / 2;

    line(posX, posY + 10, posX, posY - 40);
    line(posX, posY + 10, posX + 20, posY - 15);
    line(posX + 20, posY - 15, posX, posY - 40);

    circle(posX + 23 + halfRadiusNOT_circle, posY - 15, radiusNOT_circle);

    circle(initLineX - 1, posY - 15, 2);
    line(initLineX, posY - 15, posX, posY - 15);
    line(posX + 25 + radiusNOT_circle, termLineY - 15, termLineX + 29, termLineY - 15);

    outtextxy(initLineX, posY - 15, str1);

    if (stackCheck == 1)
        outtextxy(posX + radiusNOT_circle + 35, termLineY - 12, output);
}

void BdrawOr()
{
    if (clrOption == 1)
        setcolor(YELLOW);
    setAngles();

    arc(posX, posY, initAngleUpperArc, termAngleUpperArc, radiusUpperArc);

    arc(posX, posY + 20, initAngleOR_Arc1, termAngleOR_Arc1, radiusOR_Arc);
    arc(posX, posY - 20, initAngleOR_Arc2, termAngleOR_Arc2, radiusOR_Arc);

    line(rsltLineX, rsltLineY, rsltLineX + 45, rsltLineY);

    // input lines
    circle(initLineX - 1, initLineY - 15, 2);
    circle(initLineX - 1, initLineY + 15, 2);
    line(initLineX, initLineY - 15, termLineX - 6, initLineY - 15);
    line(initLineX, initLineY + 15, termLineX - 6, initLineY + 15);
    // output text
    outtextxy(initLineX - 2, initLineY - 13, "a");
    outtextxy(initLineX - 2, initLineY + 19, "b");
    outtextxy(rsltLineX + 10, rsltLineY + 3, "a+b");
    return;
}

void BdrawAnd()
{
    radiusUpperArc = 35;
    // setLevel();

    arc(posX, posY, initAngleUpperArc, termAngleUpperArc, radiusUpperArc);

    line(posX, posY + radiusUpperArc, posX, posY - radiusUpperArc);
    line(posX + radiusUpperArc, initLineY, posX + 3 * radiusUpperArc, initLineY);

    // input lines
    circle(initLineX - 1, initLineY - 15, 2);
    circle(initLineX - 1, initLineY + 15, 2);
    line(initLineX, initLineY - 15, posX, initLineY - 15);
    line(initLineX, initLineY + 15, posX, initLineY + 15);
    // output text
    outtextxy(initLineX - 2, initLineY - 13, "a");
    outtextxy(initLineX - 2, initLineY + 19, "b");
    outtextxy(posX + 2 * radiusUpperArc, initLineY + 2, "ab");
    return;
}

void BdrawNot()
{

    halfRadiusNOT_circle = radiusNOT_circle / 2;

    line(posX / 2, posY - 10, posX / 2, posY - 50);
    line(posX / 2, posY - 10, (posX + 20) / 2, posY - 30);
    line((posX + 20) / 2, posY - 30, posX / 2, posY - 50);

    circle((posX + 20) / 2 + halfRadiusNOT_circle, posY - 30, radiusNOT_circle);

    circle((initLineX / 2) - 21, posY - 30, 2);
    line((initLineX / 2) - 20, posY - 30, posX / 2, posY - 30);
    line((posX + 20) / 2 + radiusNOT_circle, termLineY - 30, termLineX / 2 + 20, termLineY - 30);

    outtextxy((initLineX / 2) - 20, posY - 27, "a");
    outtextxy((posX + 20) / 2 + 2 * radiusNOT_circle, termLineY - 27, "-a");
}

void BdrawNor()
{

    setAngles();

    halfRadiusNOT_circle = radiusNOT_circle / 2;

    arc(posX, posY, initAngleUpperArc, termAngleUpperArc, radiusUpperArc);

    arc(posX, posY + 20, initAngleOR_Arc1, termAngleOR_Arc1, radiusOR_Arc);
    arc(posX, posY - 20, initAngleOR_Arc2, termAngleOR_Arc2, radiusOR_Arc);

    circle(rsltLineX + halfRadiusNOT_circle, rsltLineY, radiusNOT_circle);

    line(rsltLineX + radiusNOT_circle, rsltLineY, rsltLineX + 60, rsltLineY);

    // input lines
    circle(initLineX - 1, initLineY - 15, 2);
    circle(initLineX - 1, initLineY + 15, 2);
    line(initLineX, initLineY - 15, termLineX - 6, initLineY - 15);
    line(initLineX, initLineY + 15, termLineX - 6, initLineY + 15);
    // output text
    outtextxy(initLineX - 2, initLineY - 13, "a");
    outtextxy(initLineX - 2, initLineY + 19, "b");
    outtextxy(rsltLineX + 4 * radiusNOT_circle, rsltLineY + 3, "--(a+b)");

    return;
}

void BdrawNand()
{

    radiusUpperArc = 35;

    arc(posX, posY, initAngleUpperArc, termAngleUpperArc, radiusUpperArc);

    line(posX, posY + radiusUpperArc, posX, posY - radiusUpperArc);
    line(posX + radiusUpperArc + 2 * radiusNOT_circle, initLineY, posX + 3 * radiusUpperArc, initLineY);
    circle(posX + radiusUpperArc + radiusNOT_circle, rsltLineY, radiusNOT_circle);

    // input line
    circle(initLineX - 1, initLineY - 15, 2);
    circle(initLineX - 1, initLineY + 15, 2);
    line(initLineX, initLineY - 15, posX, initLineY - 15);
    line(initLineX, initLineY + 15, posX, initLineY + 15);
    // output text
    outtextxy(initLineX - 2, initLineY - 13, "a");
    outtextxy(initLineX - 2, initLineY + 19, "b");
    outtextxy(posX + 2 * radiusUpperArc, initLineY + 3, "-ab");

    return;
}

void drawXnor()
{
    setAngles();

    halfRadiusNOT_circle = radiusNOT_circle / 2;

    arc(posX, posY, initAngleUpperArc, termAngleUpperArc, radiusUpperArc);
    arc(posX - 8, posY, initAngleUpperArc + 10, termAngleUpperArc - 10, radiusUpperArc - 3);

    arc(posX, posY + 20, initAngleOR_Arc1, termAngleOR_Arc1, radiusOR_Arc);
    arc(posX, posY - 20, initAngleOR_Arc2, termAngleOR_Arc2, radiusOR_Arc);

    circle(rsltLineX + halfRadiusNOT_circle, rsltLineY, radiusNOT_circle);

    line(rsltLineX + radiusNOT_circle, rsltLineY, rsltLineX + 45, rsltLineY);

    circle(initLineX - 1, initLineY - 15, 2);
    circle(initLineX - 1, initLineY + 15, 2);
    line(initLineX, initLineY - 15, termLineX - 14, initLineY - 15);
    line(initLineX, initLineY + 15, termLineX - 14, initLineY + 15);
    // output text
    outtextxy(initLineX - 2, initLineY - 13, "a");
    outtextxy(initLineX - 2, initLineY + 19, "b");
    outtextxy(rsltLineX + 10, rsltLineY + 3, "ab+(-a-b)");

    return;
}

void drawXor()
{

    setAngles();

    arc(posX, posY, initAngleUpperArc, termAngleUpperArc, radiusUpperArc);
    arc(posX - 8, posY, initAngleUpperArc + 10, termAngleUpperArc - 10, radiusUpperArc - 3);

    arc(posX, posY + 20, initAngleOR_Arc1, termAngleOR_Arc1, radiusOR_Arc);
    arc(posX, posY - 20, initAngleOR_Arc2, termAngleOR_Arc2, radiusOR_Arc);

    line(rsltLineX, rsltLineY, rsltLineX + 45, rsltLineY);

    circle(initLineX - 1, initLineY - 15, 2);
    circle(initLineX - 1, initLineY + 15, 2);
    line(initLineX, initLineY - 15, termLineX - 14, initLineY - 15);
    line(initLineX, initLineY + 15, termLineX - 14, initLineY + 15);
    // output text
    outtextxy(initLineX - 2, initLineY - 13, "a");
    outtextxy(initLineX - 2, initLineY + 19, "b");
    outtextxy(rsltLineX + 10, rsltLineY + 3, "(-ab)+(-ba)");
    return;
}

void drawBasics()
{
    int i, choicedrawer;

    posX = 150;
    posY = 130;
    posX = posX * levelX;
    posY = posY * levelY;

    SetVariables();

            printf("Press 1 to view AND gate\t");
            printf("Press 2 to view OR gate\t");
            printf("Press 3 to view NOT gate\t\n");
            printf("Press 4 to view NOT gate\t");
            printf("Press 5 to view NAND gate\t");
            printf("Press 6 to view XOR gate\t");
            printf("Press 7 to view XNOR gate\n");
    printf("Enter Choice:");
    scanf("%d", &choicedrawer);

    if (choicedrawer == 1)
        BdrawAnd();
    else if (choicedrawer == 2)
        BdrawOr();
    else if (choicedrawer == 3)
        BdrawNot();
    else if (choicedrawer == 4)
        BdrawNor();
    else if (choicedrawer == 5)
        BdrawNand();
    else if (choicedrawer == 6)
        drawXor();
    else if (choicedrawer == 7)
        drawXnor();
}

int andGate()
{
    int gd = DETECT, gm, i, x, y;
    initgraph(&gd, &gm, "");
    x = getmaxx() / 3;
    y = getmaxx() / 3;

    setbkcolor(BLACK);
    setcolor(WHITE);
    line(50, 30, 190, 30);
    line(50, 50, 190, 50);
    line(190, 30, 190, 50);
    arc(190, 37, 270, 90, 15);
    getchar();
}

int orGate()
{
    int gd1 = DETECT, gm1, i1, x1, y1;
    initgraph(&gd1, &gm1, "");
    x1 = getmaxx() / 3;
    y1 = getmaxx() / 3;

    setbkcolor(BLACK);
    setcolor(WHITE);
    line(50, 30, 190, 30);
    line(50, 50, 190, 50);
    line(190, 30, 190, 50);
    arc(190, 37, 270, 0, 15);
    arc(190, 37, 0, 90, 15);
    getchar;
}

//#include<graphics.h>

// function to calculate length of string
int strLength(std::string str)
{
    int len = 0;
    while (str[len] != '\0')
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

std::string infixToPostfix(std::string infix)
{
    infix = '(' + infix + ')';
    int l = strLength(infix);
    std::stack<char> char_stack;
    std::string output;

    for (int i = 0; i < l; i++)
    {

        // Checking for operand and adding to stack
        if (isalpha(infix[i]) || isdigit(infix[i]))
            output += infix[i];

        // Pushing all detected '(' to the stack)
        else if (infix[i] == '(')
            char_stack.push('(');

        // Starting popping when ')' is detected until next '('
        else if (infix[i] == ')')
        {
            while (char_stack.top() != '(')
            {
                output += char_stack.top();
                char_stack.pop();
            }

            // Remove '(' from the stack
            char_stack.pop();
        }

        // Operator found
        else
        {
            if (isOperator(char_stack.top()))
            {
                if (infix[i] == '^')
                {
                    while (getPriority(infix[i]) <= getPriority(char_stack.top()))
                    {
                        output += char_stack.top();
                        char_stack.pop();
                    }
                }
                else
                {
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
    while (!char_stack.empty())
    {
        output += char_stack.top();
        char_stack.pop();
    }
    return output;
}

std::string infixToPrefix(std::string infix)
{
    /* Reverse String and replace opening and closing parentheses */
    int l = infix.size();

    // Reverse infix
    for (int i = 0; i < l / 2; i++)
    {
        char temp = infix[i];
        infix[i] = infix[l - i - 1];
        infix[l - i - 1] = temp;
    }

    // Replace ( with ) and vice versa
    for (int i = 0; i < l; i++)
    {

        if (infix[i] == '(')
        {
            infix[i] = ')';
            i++;
        }
        else if (infix[i] == ')')
        {
            infix[i] = '(';
            i++;
        }
    }

    std::string prefix = infixToPostfix(infix);

    // Reverse postfix
    for (int i = 0; i < l / 2; i++)
    {
        char temp = prefix[i];
        prefix[i] = prefix[l - i - 1];
        prefix[l - i - 1] = temp;
    }

    return prefix;
}


int main()
{
    // string inputExp;
    // cout << "enter expression: ";
    // cin >> inputExp;

    // string postfixExp = infixToPostfix(inputExp);
    // cout << "Postfix expression: " << postfixExp << endl;

    // string prefixExp = infixToPrefix(inputExp);
    // cout << "Prefix expression: " << prefixExp << endl;

    // searching for AND and OR operators
    // for (int i = 0; i < inputExp.length(); i++)
    // {
    //     if (inputExp[i] == '+')
    //     {
    //         cout << "AND operator found at position " << i << endl;
    //         // and gate truth table for two variables
    //         andGate();
    //     }
    //     else if (inputExp[i] == '|')
    //     {
    //         cout << "OR operator found at position " << i << endl;
    //         // or gate logic diagram printing
    //         int orGate();
    //     }
    //     else if (inputExp[i] == '^')
    //     {
    //         std::cout << "XOR operator found at position " << i << endl;
    //         // xor gate logic diagram printing
    //     }
    //     else if(inputExp[i] == '!'){
    //         std::cout<<"NOT operator found at position "<<i<<endl;
    //     }
    // }

    // drawAnd();

    // int gd = DETECT, gm;
    // initgraph(&gd, &gm, NULL);
    // int choice;

    //     drawBasics();
    //     delay(500000);
    //     closegraph();

    // int gd = DETECT, gm;
    // initgraph(&gd, &gm, NULL);

    printf("Press 1 to view basic gate circuit diagrams\nPress 2 to generate circuit diagram from expression\t");

    int choice;
    //settextstyle(0, HORIZ_DIR, 1);
    scanf("%d", &choice);

    if (choice == 1)
    {
        int gd = DETECT, gm;
        initgraph(&gd, &gm, NULL);

        drawBasics();

        delay(500000);
        closegraph();
    }

    else if (choice == 2)
    {
        int gd = DETECT, gm;
        initgraph(&gd, &gm, NULL);

        drawFromExpression();

        delay(500000);
        closegraph();
    }

    else if(choice==3){
        getInput();
        initKMap();
        initBinaryMintermsKMap();
        printKMap();
        findImplicant();
        sortImplicants();
        assignInclusionTimes();
        eliminateDupeImplicants();
        getEPrimeImplicant();
        getFinalExpression();

        cout << "Simplified expression: " << finalExpression << endl;
    }

    

    return 0;
}