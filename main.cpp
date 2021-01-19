#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <bitset>

struct Block
{
    unsigned long long block = 0;
    Block operator=(int(x)) //обнуление блока
    {
        block = x;
        return *this;
    }
};

std::ostream& operator<< (std::ofstream& output, Block& block) //вывод
{
    char simvol;
    for (int h = 0; h < 8; h++)
    {
        simvol = static_cast<char> (block.block >> (8 * (7 - h)));
        output << simvol;
    }
    return output;
}

Block operator^ (Block block, unsigned long long key) //побитовое исключающее или
{
    block.block = block.block ^ key;
    return block;
}

Block operator+ (Block block, char simvol)
{
    block.block = block.block + simvol;
    //std::cout << std::bitset<sizeof(simvol) * 8>(simvol);
    return block;
}

Block operator| (Block block, Block container)
{
    block.block = block.block | container.block;
    return block;
}

Block operator<< (Block block, int n) //побитовый сдвиг влево
{
    block.block = block.block << n;
    return block;
}

Block operator>> (Block block, int n) //побитовый сдвиг вправо
{
    block.block = block.block >> n;
    return block;
}

Block operator<<= (Block block, int n) //побитовый циклический сдвиг влево
{
    Block container = block >> (64 - n);
    block = block << n;
    block = block | container;
    return block;
}

Block operator>>= (Block block, int n) //побитовый циклический сдвиг вправо
{
    Block container = block << (64 - n);
    block = block >> n;
    block = block | container;
    return block;
}

void Key_generation(unsigned long long& key) //т.к. rand генерирует только 15 битов
{
    key = std::rand();
    key = key << 16;
    key += std::rand();
    key = key << 16;
    key += std::rand();
    key = key << 16;
    key += std::rand();
}

void Shifr(std::string& input_file, std::string& output_file, std::string& text, unsigned long long& key)
{
    Block block;
    std::ofstream outfile(output_file);
    std::ofstream outfile_key("keys.txt");
    for (int h = 0; h < text.length(); h++)
    {
        if ((h % 8 == 7) || (h == (text.length() - 1)))
        {
            block = block + text[h];
            //std::cout << "\n" << std::bitset<sizeof(block.block) * 8>(block.block) << "\n";
            Key_generation(key);
            //std::cout << std::bitset<sizeof(key) * 8>(key) << "\n";
            block = block ^ key;
            //std::cout << std::bitset<sizeof(block.block) * 8>(block.block) << "\n";
            block = block <<= 5;
            //std::cout << std::bitset<sizeof(block.block) * 8>(block.block) << "\n";
            outfile_key << key; //<< "\n" << std::bitset<sizeof(key) * 8>(key) << "\n";
            outfile << block;
            block = 0;//обнуление блока
        }
        else
        {
            block = block + text[h];
            block = block << 8;
        }
    }
    outfile.close();
    outfile_key.close();
}

void Deshifr(std::string& input_file, std::string& output_file, std::string& text, unsigned long long& key)
{
    Block block;
    std::ofstream outfile(output_file);
    for (int h = 0; h < text.length(); h++)
    {
        if (h % 8 == 7)
        {
            block = block + text[h];
            //std::cout << "\n" <<std::bitset<sizeof(block.block) * 8>(block.block) << "\n";
            block = block >>= 5;
            //std::cout << std::bitset<sizeof(block.block) * 8>(block.block) << "\n";
            //std::cout << key << "\n" << std::bitset<sizeof(key) * 8>(key) << "\n";
            block = block ^ key;
            //std::cout << std::bitset<sizeof(block.block) * 8>(block.block) << "\n";
            outfile << block;
            block = 0;
            //std::cout << std::bitset<sizeof(block.block) * 8>(block.block) << "\n";
        }
        else
        {
            block = block + text[h];
            block = block << 8;
        }
    }
}


int main(int argc, char* argv[])
{
    std::srand(std::time(nullptr));
    std::cout << "The meanings of arguments:\n1: working mode:\n\t0 = cryption;\n\t1 = decryption;\n2: input file;\n3: output file;\n4: key.\n";
    int working_mode = std::stoi(argv[1]);
    std::string input_file = argv[2];
    std::string output_file = argv[3];
    unsigned long long key;
    std::string text;
    std::ifstream infile(input_file);
    char ch;
    while (infile.get(ch))
    {
        text += ch;
    }
    infile.close();
    //std::cout << text << "\n";
    if (working_mode == 0)
    {
        key = 0;
        Shifr(input_file, output_file, text, key);
    }
    else
    {
        key = std::stoull(argv[4]);
        Deshifr(input_file, output_file, text, key);
    }
    return 0;
}
