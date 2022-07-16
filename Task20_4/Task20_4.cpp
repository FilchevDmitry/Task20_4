#include <iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>

int main()
{
    int number;
    int rub[] = { 0,0,0,0,0,0};
    int cup[] = { 5000,2000,1000,500,200,100 };
    int breakdown[] = { 0,0,0,0,0,0 };
    char simbol;
    int sum = 0;
    int num = 0;
    bool ok = true;
    std::srand(std::time(nullptr));
    std::cout << "To withdraw cash, enter '-', to deposit '+' : ";
    std::cin >> simbol;
    
    if (simbol == '+')
    {
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
        std::cout << "ATM is full\n";
        bankIn.close();
    }
    else if (simbol =='-')
    {
        std::cout << "Enter the amount : ";
        std::cin >> sum;
        if (sum % 100 == 0)
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
                }
                bank.close();
                std::ofstream bankOut("bank.bin", std::ios::binary);
                for (int i = 0; i < 6; i++)
                {
                    breakdown[i] += (sum / cup[i]);
                    sum = sum % cup[i];
                    if (rub[i] - breakdown[i] < 0)
                    {
                        int t = breakdown[i] - rub[i];
                        breakdown[i] -= t;
                        sum += (t * cup[i]);
                    }
                    if (i == 5 && sum > 0)
                    {
                        std::cout << "This amount cannot be issued!!!!\n";
                        rub[i] += breakdown[i];
                        ok = false;
                    }
                    rub[i] -= breakdown[i];
                    bankOut.write((char*)&rub[i], sizeof(rub[i]));
                }
                if (ok)
                {
                    std::cout << "Amount issued\n";
                    for (int i = 0; i < 6; i++)
                    {
                        if (breakdown[i] != 0)
                        {
                            std::cout << breakdown[i] << " banknotes in face value " << cup[i] << std::endl;
                        }
                    }
                }
                bankOut.close();
            }
        }
        else
            std::cout << "The amount must be a multiple of 100\n";
    }
}
