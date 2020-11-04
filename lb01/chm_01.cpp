
#include <iostream>
#include <cmath>

using namespace std;

class Function
{
    private:
        double x, y, z;

    public:
        Function()
        {
            x = 0;
            z = 0;
            y = 0;
        }

        void Set(double x_, double y_, double z_)
        {
            x = x_;
            y = y_;
            z = z_;
        }

        double Value()
        {
            return 2 * x * x + 3 * y * y + z * z + 4 * x * y - 3 * z + cos(y - x);
        }
};

class Differential
{
    private:
        double x, y, z; //arguments

    public:
        Differential()
        {
            x = 0;
            y = 0;
            z = 0;
        }

        void Set(double x_, double y_, double z_)
        {
            x = x_;
            y = y_;
            z = z_;
        }

        double XDerivative()
        {
            return 4 * x + 4 * y + sin(y - x);
        }

        double YDerivative()
        {
            return 6 * y + 4 * x - sin(y - x);
        }

        double ZDerivative()
        {
            return 2 * z - 3;
        }
};

class Inaccuracies
{
    private:
        double x, y, z, absIn;
        double exactNumberX, exactNumberY, exactNumberZ;
        char mode;
        Function fun;
        Differential diff;

    public:
        Inaccuracies(double x_, double y_, double z_, double absIn_, double eNx, double eNy, double eNz, char m)
        {
            x = x_;
            y = y_;
            z = z_;
            absIn = absIn_;
            exactNumberX = eNx;
            exactNumberY = eNy;
            exactNumberZ = eNz;
            mode = m;
            fun.Set(x, y, z);
            diff.Set(x, y, z);
        }

        double AbsoluteValueInaccuries(double exNum, double val)
        {
            int senior = 0;
            double cpy = val;
            if (cpy < 0) {
                cpy = -cpy;
            }
            if (cpy > 1) {
                while ((int)cpy > 0) {
                    senior = (int)cpy;
                    cpy /= 10;
                }
            }
            else {
                while ((int)cpy == 0) {
                    cpy *= 10;
                    senior = (int)cpy;
                }
            }
            double multiplier = 1;
            if (exNum != 1)
                multiplier = 0.1;
            for (int i = 1; i < exNum; ++i) {
                multiplier *= multiplier;
            }
            return (1 / (double)senior) * multiplier * val;
        }

        double AbsoluteFunctionInaccuracies()
        {
            if (mode == 'a') {
                return abs(diff.XDerivative()) * AbsoluteValueInaccuries(exactNumberX, x) + abs(diff.YDerivative()) * AbsoluteValueInaccuries(exactNumberY, y) + abs(diff.ZDerivative()) * AbsoluteValueInaccuries(exactNumberZ, z);
            }
            else if (mode == 'b') {
                return abs(diff.XDerivative()) * absIn + abs(diff.YDerivative()) * absIn + abs(diff.ZDerivative()) * absIn;
            }
            
        }

        double RelativeFunctionInaccuracies()
        {
            return AbsoluteFunctionInaccuracies() / fun.Value();
        }


};

int main()
{
    cout << "Bobrykov Vladyslav KN-201 lab01 variant 1" << endl;
    cout << "F = 2x1^2 + 3x2^2 + x3^2 + 4x1x2 - 3x3 + cos(x2 - x1)" << endl;
    cout << "N = 1, delta = 1 * 10^-3 = 0.001" << endl;
    double x, y, z;
    double exNumX, exNumY, exNumZ;
    cout << "Enter x1: ";
    cin >> x;
    cout << "Enter x2: ";
    cin >> y;
    cout << "Enter x3: ";
    cin >> z;
    cout << "Enter the exact numbers for argument x1: ";
    cin >> exNumX;
    cout << "Enter the exact numbers for argument x2: ";
    cin >> exNumY;
    cout << "Enter the exact numbers for argument x3: ";
    cin >> exNumZ;

    Inaccuracies obj1(x, y, z, 0.001, 0, 0, 0, 'b');
    Inaccuracies obj2(x, y, z, 0, exNumX, exNumY, exNumZ, 'a');

    cout << "Absolute function inaccuracies for task a: " << obj2.AbsoluteFunctionInaccuracies() << endl;
    cout << "Relative function inaccuracies for task a: " << obj2.RelativeFunctionInaccuracies() << endl;
    cout << "Absolute function inaccuracies for task b: " << obj1.AbsoluteFunctionInaccuracies() << endl;
    cout << "Relative function inaccuracies for task b: " << obj1.RelativeFunctionInaccuracies() << endl;

}


