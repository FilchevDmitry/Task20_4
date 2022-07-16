#include <iostream>
#include<fstream>
#include<cstdlib>

int main()
{
    int number;
    int rub[] = { 0,0,0,0,0,0};
    int cup[] = { 5000,2000,1000,500,200,100 };
    int breakdown[] = { 0,0,0,0,0,0 };
    char simbol;
    int sum = 0;
    int num = 0;
    std::cout << "To withdraw cash, enter '-', to deposit '+' : ";
    std::cin >> simbol;
    
    if (simbol == '+')
    {
        std::ifstream bank("bank.bin", std::ios::binary);
            if (!bank.is_open())
            {
                std::cout << "File not open" << std::endl;
            }
            else
            {
                for (int i = 0; i < 6; i++)
                {
                    bank.read((char*)&rub[i], sizeof(rub[i]));
                        num += rub[i];
                }
            }
        bank.close();

        std::ofstream bankIn("bank.bin", std::ios::binary);

        for (int i = 0; i < 6; i++)
        {
            rub[i] = rand() % (1001 - num);
            num += rub[i];
            bankIn.write((char*)&rub[i], sizeof(rub[i]));
            if (i == 5 && num < 1001)
            {
                rub[rand() % 6] += 1000 - num;
            }
        }
        bankIn.close();
    }
    else if (simbol =='-')
    {
        std::cout << "Enter the amount : ";
        std::cin >> sum;
        std::ifstream bank("bank.bin", std::ios::binary);
        if (!bank.is_open())
        {
            std::cout << "File not open" << std::endl;
        }
        else
        {
            for (int i = 0; i < 6; i++)
            {
                bank.read((char*)&rub[i], sizeof(rub[i]));
            }
            for (int i = 0; i < 6; i++)
            {
                breakdown[i] += (sum / cup[i]);
                sum = sum % cup[i];
            }

        }
        bank.close();
        std::ofstream bankOut("bank.bin", std::ios::binary);
        for (int i = 0; i < 6; i++)
        {
            if((rub[i] -= breakdown[i])<0);
        }


    }

}
