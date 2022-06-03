#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int ROWS = 2, COLUMNS = 4;

int numOfMinterms = 0;
int decimalMinterms[7];

struct kMapElements
{
    int state;            // assigns a state of 0 or 1 to kmap cells
    int decimalMinterm;   // associates a minterm decimal expression to every cell
    int inclusion = 0;    // keeping count of every group that is selected
    string binaryMinterm; // binary expression of assigned decimal minterms
};

struct Implicant
{
    vector<kMapElements> minterms;
    int Size;
};

kMapElements Kmap[ROWS][COLUMNS]; // creates a 2D array with 4 supported value types
vector<kMapElements> V1, V2, V3, V4, V5, V6, allElementsInImplicant;
vector<Implicant> allImplicants;

string finalExpression;
void getInput();
void initKMap(), initBinaryMintermsKMap();
void printKMap();
void findImplicant();
vector<kMapElements> getMaxSizeVector(vector<kMapElements> V1, vector<kMapElements> V2, vector<kMapElements> V3, vector<kMapElements> V4, vector<kMapElements> V5);
void sortImplicants();
void assignInclusionTimes();
void eliminateDupeImplicants();
void decrementInclusionOfDeletedImplicant(int i);
void getEPrimeImplicant();
void getFinalExpression();

// int main()
// {
//     getInput();
//     initKMap();
//     initBinaryMintermsKMap();
//     printKMap();
//     findImplicant();
//     sortImplicants();
//     assignInclusionTimes();
//     eliminateDupeImplicants();
//     getEPrimeImplicant();
//     getFinalExpression();

//     cout << "Simplified expression: " << finalExpression << endl;
// }

void getInput()
{
    cout << "Enter number of minterms" << endl;
    cin >> numOfMinterms;

    cout << "Enter Minterms " << endl;
    int i = 0, validityCheck;
    do
    {
        do
        {
            cin >> validityCheck;
        } while (validityCheck > 7 || validityCheck < 0);
        decimalMinterms[i] = validityCheck;
        i++;

    } while (i < numOfMinterms);
}

void initKMap()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            Kmap[i][j].state = 0;
        }
    }
    Kmap[0][0].decimalMinterm = 0;
    Kmap[0][1].decimalMinterm = 1;
    Kmap[0][2].decimalMinterm = 3;
    Kmap[0][3].decimalMinterm = 2;
    Kmap[1][0].decimalMinterm = 4;
    Kmap[1][1].decimalMinterm = 5;
    Kmap[1][2].decimalMinterm = 7;
    Kmap[1][3].decimalMinterm = 6;

    for (int i = 0; i < numOfMinterms; i++)
    {
        if (decimalMinterms[i] == 0)
            Kmap[0][0].state = 1;
        else if (decimalMinterms[i] == 1)
            Kmap[0][1].state = 1;
        else if (decimalMinterms[i] == 3)
            Kmap[0][2].state = 1;
        else if (decimalMinterms[i] == 2)
            Kmap[0][3].state = 1;
        else if (decimalMinterms[i] == 4)
            Kmap[1][0].state = 1;
        else if (decimalMinterms[i] == 5)
            Kmap[1][1].state = 1;
        else if (decimalMinterms[i] == 7)
            Kmap[1][2].state = 1;
        else if (decimalMinterms[i] == 6)
            Kmap[1][3].state = 1;
    }
}

void initBinaryMintermsKMap()
{
    Kmap[0][0].binaryMinterm = "000";
    Kmap[0][1].binaryMinterm = "001";
    Kmap[0][2].binaryMinterm = "011";
    Kmap[0][3].binaryMinterm = "010";
    Kmap[1][0].binaryMinterm = "100";
    Kmap[1][1].binaryMinterm = "101";
    Kmap[1][2].binaryMinterm = "111";
    Kmap[1][3].binaryMinterm = "110";
}

void printKMap()
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << Kmap[i][j].state << " ";
        }
        cout << endl;
    }
}

void findImplicant()
{
    if (numOfMinterms == 8)
        finalExpression = "1";
    else if (numOfMinterms == 0)
        finalExpression = "0";

    else
    {
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLUMNS; j++)
            {
                int numOfImplicants = 0;
                if (Kmap[i][j].state == 1)
                {
                    V1.push_back(Kmap[i][j]);
                    if (Kmap[i][(j + 1) % COLUMNS].state == 1)
                    {
                        V2.push_back(Kmap[i][j]);
                        V2.push_back(Kmap[i][(j + 1) % COLUMNS]);
                    }
                    if (Kmap[(i + 1) % ROWS][j].state == 1)
                    {
                        V3.push_back(Kmap[i][j]);
                        V3.push_back(Kmap[(i + 1) % ROWS][j]);
                    }
                    if (Kmap[i][(j + 1) % COLUMNS].state == 1 && Kmap[(i + 1) % ROWS][j].state == 1 && Kmap[(i + 1) % ROWS][(j + 1) % COLUMNS].state == 1)
                    {
                        V4.push_back(Kmap[i][j]);
                        V4.push_back(Kmap[i][(j + 1) % COLUMNS]);
                        V4.push_back(Kmap[(i + 1) % ROWS][j]);
                        V4.push_back(Kmap[(i + 1) % ROWS][(j + 1) % COLUMNS]);
                    }
                    if (Kmap[i][(j + 1) % COLUMNS].state == 1 && Kmap[i][(j + 2) % COLUMNS].state == 1 && Kmap[i][(j + 3) % COLUMNS].state == 1)
                    {
                        V5.push_back(Kmap[i][j]);
                        V5.push_back(Kmap[i][(j + 1) % COLUMNS]);
                        V5.push_back(Kmap[i][(j + 2) % COLUMNS]);
                        V5.push_back(Kmap[i][(j + 3) % COLUMNS]);
                    }
                    allElementsInImplicant = getMaxSizeVector(V1, V2, V3, V4, V5);
                    for (int m = 0; m < allElementsInImplicant.size(); m++)
                    {
                        if (allElementsInImplicant[m].decimalMinterm == 0)
                            Kmap[0][0].inclusion = Kmap[0][0].inclusion + 1;
                        else if (allElementsInImplicant[m].decimalMinterm == 1)
                            Kmap[0][1].inclusion = Kmap[0][1].inclusion + 1;
                        else if (allElementsInImplicant[m].decimalMinterm == 2)
                            Kmap[0][3].inclusion = Kmap[0][3].inclusion + 1;
                        else if (allElementsInImplicant[m].decimalMinterm == 3)
                            Kmap[0][2].inclusion = Kmap[0][2].inclusion + 1;
                        else if (allElementsInImplicant[m].decimalMinterm == 4)
                            Kmap[1][0].inclusion = Kmap[1][0].inclusion + 1;
                        else if (allElementsInImplicant[m].decimalMinterm == 5)
                            Kmap[1][1].inclusion = Kmap[1][1].inclusion + 1;
                        else if (allElementsInImplicant[m].decimalMinterm == 6)
                            Kmap[1][3].inclusion = Kmap[1][3].inclusion + 1;
                        else if (allElementsInImplicant[m].decimalMinterm == 7)
                            Kmap[1][2].inclusion = Kmap[1][2].inclusion + 1;
                    }
                    Implicant A;
                    for (int m = 0; m < allElementsInImplicant.size(); m++)
                    {
                        A.minterms.push_back(allElementsInImplicant[m]);
                        // cout<<allElementsInImplicant[m].binaryMinterm<<" ";
                    }
                    // cout<<endl<<"All elements in Implicant done."<<endl;
                    A.Size = allElementsInImplicant.size();
                    allImplicants.push_back(A);
                    A.minterms.clear();
                    A.Size = 0;

                    numOfImplicants++;
                }
                V1.clear();
                V2.clear();
                V3.clear();
                V4.clear();
                V5.clear();
            }
        }
    }
}

vector<kMapElements> getMaxSizeVector(vector<kMapElements> V1, vector<kMapElements> V2, vector<kMapElements> V3, vector<kMapElements> V4, vector<kMapElements> V5)
{
    int Sizes[5];
    Sizes[0] = V1.size();
    Sizes[1] = V2.size();
    Sizes[2] = V3.size();
    Sizes[3] = V4.size();
    Sizes[4] = V5.size();

    int max = -1;
    int vectorNumber;
    for (int i = 0; i < 5; i++)
    {
        if (Sizes[i] > max)
        {
            max = Sizes[i];
            vectorNumber = i + 1;
        }
    }

    if (vectorNumber == 1)
        return V1;
    else if (vectorNumber == 2)
        return V2;
    else if (vectorNumber == 3)
        return V3;
    else if (vectorNumber == 4)
        return V4;
    else if (vectorNumber == 5)
        return V5;
}

void sortImplicants()
{
    int i, j;
    for (i = 0; i < allImplicants.size() - 1; i++)
    {
        for (j = 0; j < allImplicants.size() - i - 1; j++)
            if (allImplicants[j].Size > allImplicants[j + 1].Size)
            {
                Implicant temp = allImplicants[j];
                allImplicants[j] = allImplicants[j + 1];
                allImplicants[j + 1] = temp;
            }
    }

    for (i = 0; i < allImplicants.size(); i++)
    {
        // cout<<"After sorting: "<<i<<" ";
        for (j = 0; j < allImplicants[i].minterms.size(); j++)
        {
            // cout<<allImplicants[i].minterms[j].binaryMinterm<<" ";
        }
        // cout<<endl;
    }
}

void assignInclusionTimes()
{
    int i, j;
    for (i = 0; i < allImplicants.size(); i++)
    {
        for (j = 0; j < allImplicants[i].minterms.size(); j++)
        {
            if (allImplicants[i].minterms[j].decimalMinterm == 0)
            {
                allImplicants[i].minterms[j].inclusion = Kmap[0][0].inclusion;
            }
            else if (allImplicants[i].minterms[j].decimalMinterm == 1)
            {
                allImplicants[i].minterms[j].inclusion = Kmap[0][1].inclusion;
            }
            else if (allImplicants[i].minterms[j].decimalMinterm == 2)
            {
                allImplicants[i].minterms[j].inclusion = Kmap[0][3].inclusion;
            }
            else if (allImplicants[i].minterms[j].decimalMinterm == 3)
            {
                allImplicants[i].minterms[j].inclusion = Kmap[0][2].inclusion;
            }
            else if (allImplicants[i].minterms[j].decimalMinterm == 4)
            {
                allImplicants[i].minterms[j].inclusion = Kmap[1][0].inclusion;
            }
            else if (allImplicants[i].minterms[j].decimalMinterm == 5)
            {
                allImplicants[i].minterms[j].inclusion = Kmap[1][1].inclusion;
            }
            else if (allImplicants[i].minterms[j].decimalMinterm == 6)
            {
                allImplicants[i].minterms[j].inclusion = Kmap[1][3].inclusion;
            }
            else if (allImplicants[i].minterms[j].decimalMinterm == 7)
            {
                allImplicants[i].minterms[j].inclusion = Kmap[1][2].inclusion;
            }
        }
    }
}

void eliminateDupeImplicants()
{
    int checkEqual = 0;
    for (int i = 0; i < allImplicants.size(); i++)
    {
        for (int j = 0; j < allImplicants.size() - 1; j++)
        {
            for (int k = 0; k < allImplicants[i].minterms.size(); k++)
            {
                for (int L = 0; L < allImplicants[j].minterms.size(); L++)
                {
                    if (allImplicants[i].minterms[k].binaryMinterm == allImplicants[j].minterms[L].binaryMinterm)
                    {
                        checkEqual++;
                    }
                }
                if (checkEqual == allImplicants[i].minterms.size() && allImplicants[i].Size == allImplicants[j].Size)
                {
                    decrementInclusionOfDeletedImplicant(i);
                    allImplicants.erase(allImplicants.begin() + i);
                }
                checkEqual = 0;
            }
        }
    }
}

void decrementInclusionOfDeletedImplicant(int i)
{
    int *decimalMintermptr = new int[allImplicants[i].minterms.size()];
    for (int j = 0; j < allImplicants[i].minterms.size(); j++)
    {
        decimalMintermptr[j] = allImplicants[i].minterms[j].decimalMinterm;
    }

    for (int k = 0; k < allImplicants.size(); k++)
    {
        for (int L = 0; L < allImplicants[k].minterms.size(); L++)
        {
            for (int M = 0; M < allImplicants[i].minterms.size(); M++)
            {
                if (allImplicants[k].minterms[L].binaryMinterm == allImplicants[i].minterms[M].binaryMinterm)
                {
                    allImplicants[k].minterms[L].inclusion =allImplicants[k].minterms[L].inclusion - 1;
                }
            }
        }
    }
}

void getEPrimeImplicant()
{
    //cout << "After removing dupe implicants " << endl;
    // for (int i = 0; i < allImplicants.size(); i++)
    // {
    //     cout << "Implicant " << i << " with minterms";
    //     for (int j = 0; j < allImplicants[i].minterms.size(); j++)
    //         cout << allImplicants[i].minterms[j].binaryMinterm << " ";
    //     cout << endl;
    // }

    int numOfMintermRepeats = 0;
    for (int i = 0; i < allImplicants.size(); i++)
    {
        numOfMintermRepeats = 0;
        for (int j = 0; j < allImplicants[i].minterms.size(); j++)
        {
            //cout << "inclusion of minterm " << j << "is " << allImplicants[i].minterms[j].inclusion << " in implicant " << i << endl;
            if (allImplicants[i].minterms[j].inclusion > 1)
                numOfMintermRepeats++;
        }

        if (numOfMintermRepeats == allImplicants[i].Size)
        {
            decrementInclusionOfDeletedImplicant(i);
            allImplicants.erase(allImplicants.begin() + i);
            --i;
            //cout << "erase" << endl;
        }
    }
    //cout << "after deletion" << endl;
    for (int i = 0; i < allImplicants.size(); i++)
    {
        for (int j = 0; j < allImplicants[i].minterms.size(); j++)
        {
            string minterm = allImplicants[i].minterms[j].binaryMinterm;
            //cout << minterm << " ";
        }
        //cout << i << endl;
    }
}

void getFinalExpression()
{
    string *mintermsinPI;
    string PI = "";
    int numOfMinterms;
    for (int i = 0; i < allImplicants.size(); i++)
    {
        numOfMinterms = allImplicants[i].minterms.size();
        mintermsinPI = new string[allImplicants[i].minterms.size()];
        for (int j = 0; j < allImplicants[i].minterms.size(); j++)
        {
            mintermsinPI[j] = allImplicants[i].minterms[j].binaryMinterm;
            //cout << mintermsinPI[j];
        }

        int noChange = 0;
        for (int k = 0; k < 3; k++)
        {
            int m = 0;
            for (int L = 1; L < numOfMinterms; L++)
            {
                //cout << endl<< "MintermsinPI[m][k]==mintermsinPI[L][k}" << mintermsinPI[m][k] << " " << mintermsinPI[L][k] << endl;
                if (mintermsinPI[m][k] == mintermsinPI[L][k])
                    noChange++;
            }
            //cout << "No change" << noChange << endl;

            if (noChange == numOfMinterms - 1)
            {
                if (mintermsinPI[0][k] == '0')
                {
                    PI += "(!";
                    PI += char(k + 65);
                    PI += ")";
                }
                else if (mintermsinPI[0][k] == '1')
                {
                    PI += "(";
                    PI += char(k + 65);
                    PI += ")";
                }
            }
            noChange = 0;
        }
        PI += " + ";
    }
    finalExpression = PI;
    finalExpression = finalExpression.erase(finalExpression.size() - 2);
}