#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <fstream>
#include <bitset>
#include <climits>

#define BIT_NUMBER 8

class Char_s
{
    private:
        std::vector <char> Vec;
    public:
        char& operator[] (const char h);
};

char& Char_s::operator[] (const char h)
{
    return Vec[h];
}

std::vector<char> Key_generation (char n)
{
    std::vector <char> Key;
    for (int i=0; i<n; i++)
    {
        int x=rand()%256;
        x=abs(x);
        Key.push_back(x);
    }
    return Key;
}

void cyclicShiftLeft(std::vector<char> &vec,int n)
{
    size_t container=0;
    for (int i=0;i<vec.size();i++){ // vec.size() == 8
        container=(container|((long(vec[i]))<<(BIT_NUMBER*i)));
    }
    const int bits_in_long=BIT_NUMBER*sizeof(long);
    long dest=(0|(container>>(bits_in_long-n)));
    container<<=n;
    container|=dest;
    for (int i=0;i<vec.size();i++){
        vec[i]=char(container>>(BIT_NUMBER*i));
    }
}

void cyclicShiftRight(std::vector<char> &vec,int n)
{
    size_t container=0;
    for (int i=0;i<vec.size();i++){ // vec.size() == 8
        container=(container|((long(vec[i]))<<(BIT_NUMBER*i)));
    }
    const int bits_in_long=BIT_NUMBER*sizeof(long);
    long dest=(0|(container<<(bits_in_long-n+1)));
    container>>=n;
    container|=dest;
    for (int i=0;i<vec.size();i++){
        vec[i]=char(container>>(BIT_NUMBER*i));
    }
}

void Shifr()
{
    const int dlina = 8;
    std::ifstream infile("input.txt");
    std::vector <char> Vec;
    char ch;
    int kolvo_simvolov=0;
    while (infile.get(ch))
    {
        Vec.push_back(ch);
    }
    for (int x: Vec)
    {
        kolvo_simvolov+=1;
    }
    infile.close();
    int kolvo_blockov=kolvo_simvolov/dlina;
    if (kolvo_simvolov%dlina!=0)
    {
        kolvo_blockov+=1;
    }
    int s=kolvo_simvolov;
    Char_s Block;
    std::ofstream outfile("output.txt");
    for (char i=0; i<s; i++)
    {
        if ((i%dlina==7) || (i==(s-1)))
        {
            Block[i%dlina] = Vec[i];
            std::vector <char> Key = Key_generation(dlina);
            for (int h=0; h<dlina; h++)
            {
                Key[h]^=Block[h];
            }
            cyclicShiftLeft(Key,5);
            for (char h: Key)
            {
                outfile << h;
            }
        }
        else Block[i%dlina] = Vec[i];
    }
    outfile.close();
}

void Deshifr()
{
    const int dlina = 8;
    std::ifstream infile("input.txt");
    std::vector <char> Vec;
    char ch;
    int kolvo_simvolov=0;
    while (infile.get(ch))
    {
        Vec.push_back(ch);
    }
    for (int x: Vec)
    {
        kolvo_simvolov+=1;
    }
    infile.close();
    int kolvo_blockov=kolvo_simvolov/dlina;
    if (kolvo_simvolov%dlina!=0)
    {
        kolvo_blockov+=1;
    }
    int s=kolvo_simvolov;
    Char_s Block;
    std::ofstream outfile("output.txt");
    for (char i=0; i<s; i++)
    {
        if ((i%dlina==7) || (i==(s-1)))
        {
            Block[i%dlina] = Vec[i];
            std::vector <char> Key = Key_generation(dlina);
            for (int h=0; h<dlina; h++)
            {
                Key[h]^=Block[h];
            }
            cyclicShiftRight(Key,5);
            for (char h: Key)
            {
                outfile << h;
            }
        }
        else Block[i%dlina] = Vec[i];
    }
    outfile.close();
}

int main(int argc, char *argv[])
{
    bool t;
    std::cout << "Code cryption is 0, code decryption is 1.\n";
    std::cin >> t;
    if (t==0) Shifr();
    else Deshifr();
    return 0;
}
