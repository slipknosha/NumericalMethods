#include <iostream>

using namespace std;

#define LEFT -10
#define RIGHT 10
#define STEP 1

class Methode
{
    double argument;
    double value[5];

private:
    void PrintFunk()
    {
        printf("F (x) = x⁴ - x³ + 2x - 5 = %.2lf\n", value[0]);
    }
    void PrintF0()
    {
        printf("f₀(x) = 4x³ - 3x² + 2 = %.2lf\n", value[1]);
    }
    void PrintF1()
    {
        printf("f₁(x) = 3x² - 24x + 78 = %.2lf\n", value[2]);
    }
    void PrintF2()
    {
        printf("f₂(x) = -8x + 47 = %.2lf\n", value[3]);
    }
    void PrintF3()
    {
        printf("f₃(x) = -1\n");
    }

public:
    Methode(double argument)
    {
        this->argument = argument;
        Funk(argument);
        f0(argument);
        f1(argument);
        f2(argument);
        f3(argument);
    }
    void set_x(double argument)
    {
        this->argument = argument;
        Funk(argument);
        f0(argument);
        f1(argument);
        f2(argument);
        f3(argument);
    }

    void Funk(double x)
    {
        value[0] = x * x * x * x - x * x * x + 2 * x - 5;
    }
    void f0(double x)
    {
        value[1] = 4 * x * x * x - 3 * x * x + 2;
    }
    void f1(double x)
    {
        value[2] = 3 * x * x - 24 * x + 78;
    }
    void f2(double x)
    {
        value[3] = -8 * x + 47;
    }
    void f3(double x)
    {
        value[4] = -1;
    }
    int CalculateMinuses()
    {
        int acquaintance = 0;
        for (int i = 0; i < 4; ++i)
        {
            if ((value[i] > 0) ^ (value[i + 1] > 0))
            {
                ++acquaintance;
            }
        }
        return acquaintance;
    }
    double GetValue(int i)
    {
        return value[i];
    }

    void Print()
    {
        puts("----------------------------------------");
        printf("x = %.2lf\n", argument);
        PrintFunk();
        PrintF0();
        PrintF1();
        PrintF2();
        PrintF3();
    }
};

class Interval
{
    double left;
    double right;

public:
    Interval(double left, double right)
    {
        this->left = left;
        this->right = right;
    }
    void SetNextForward()
    {
        left = right;
        right += STEP;
    }
    void SetNextBackward()
    {
        right = left;
        left -= STEP;
    }
    double GetLeft()
    {
        return left;
    }
    double GetRight()
    {
        return right;
    }
    void ShowAcquaintanceTable(Methode* left, Methode* right)
    {
        puts("------------------------------------------------------");
        printf("|%7c|\t F(x)|\tF₀(x)|\tF₁(x)|\tF₂(x)|\tF₃(x)|\n", 'x');
        printf("|%7.2lf|", this->left);
        PrintTablePart(left);
        printf("\n|%7.2lf|", this->right);
        PrintTablePart(right);
        puts("");
        puts("------------------------------------------------------");
    }

private:
    void PrintTablePart(Methode* m)
    {
        for (int i = 0; i < 5; ++i)
        {
            char c;
            if (m->GetValue(i))
            {
                c = m->GetValue(i) > 0 ? '+' : '-';
            }
            else
                c = '0';

            printf("\t%5c|", c);
        }
    }
};

int main(void)
{
    Interval* interval = new Interval(LEFT, LEFT + 1L);
    Methode* left = new Methode(interval->GetLeft());
    Methode* right = new Methode(interval->GetRight());
    puts("Корінь/-ені рівняння x⁴ - x³ + 2x - 5 = 0"
        "\nзнаходяться у заданому інтервалі/-ах:");
    for (int i = 0; i < RIGHT - LEFT; ++i)
    {
        left->set_x(interval->GetLeft());
        right->set_x(interval->GetRight());
        if (right->CalculateMinuses() - left->CalculateMinuses())
        {
            printf("\n\tІнтервал: (%.2lf; %.2lf)\n", interval->GetLeft(), interval->GetRight());
            left->Print();
            right->Print();
            interval->ShowAcquaintanceTable(left, right);
        }
        interval->SetNextForward();
    }
    delete interval;
    delete left;
    delete right;
    return 0;
}
