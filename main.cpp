#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <fstream>

class Char_s
{
    private:
        std::vector <char> Vec;
    public:
        char& operator[] (const char h);
        char& operator<< (const char h);
};

char& Char_s::operator[] (const char h)
{
    return Vec[h];
}

char& Char_s::operator<< (const char h)
{
    for (char h: Vec)
    {
        Vec[h]=Vec[h+1];
    }
}

void Shifr (char n)
{
    std::vector <char> Key;
    for (int i=0; i<64; i++)
    {
        n=rand()%256;
        n=abs(n);
        Key.push_back(n);
    }
}

void Zamena (Char_s Vec, int kolvo_elementov, int g)
{
    Vec[kolvo_elementov]=g;
}

void Cikl (Char_s Vec, int kolvo_elementov)
{
    for (int i=0; i<4; i++)
    {
        int g=Vec[i];
        Vec<<1;
        Zamena (Vec, kolvo_elementov, g);
    }
}

int main()
{
    char n;
    Shifr(n);
    const int dlina = 64;
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
        std::cout << x << " ";
        kolvo_simvolov+=1;
    }
    infile.close();
    int kolvo_blockov=kolvo_simvolov/dlina;
    if (kolvo_simvolov%dlina!=0)
    {
        kolvo_blockov+=1;
    }
    int s=kolvo_simvolov-(kolvo_simvolov%dlina);
    Char_s Block;
    for (int i=0; i<s; i++)
    {
        if (i%dlina==63)
        {
            Block.push_back(Vec[i]);
            for (int h=0; h<dlina; h++)
            {
                Block[h]^Key[h];
            }
            //Block
        }
        else Block.push_back(Vec[i]);
    }
    return 0;
}
