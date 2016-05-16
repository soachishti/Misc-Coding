/*
Name:           Syed Owais Ali Chishti
Roll no:        P146011
Sec:            A
Description:    First assignment implement multiplication using divide and conquor rule.
*/

#include <iostream>
#include <string>
#include <math.h>
#include <cstdlib>
using namespace std;

int ToInt(double x)
{
   double dx = x < 0.0 ? -0.5 : 0.5;
   return static_cast<int>(x + dx);
}

int multiplyPoly(string ValA, string ValB, int split) {
	int result = 0;
	int IntB = atoi(ValB.c_str());
	for (int i = 0; i < ValB.length(); i += split) {
		int PartB = IntB % ToInt(pow(10, split));
		IntB /= ToInt(pow(10, split));
		int resultT = 0;
		int IntA = atoi(ValA.c_str());        
		for (int j = 0; j < ValA.length(); j += split) {
	        int ShiftVal = ToInt(pow(10, j + i));
            int TmpRes = PartB * (IntA % ToInt(pow(10, split))) * ShiftVal;
			resultT += TmpRes;
			cout << PartB << " x " << (IntA % ToInt(pow(10, split))) << " = " << TmpRes << "    " << endl;
            IntA /= ToInt(pow(10, split));
		}
		result += resultT;
	}
	return result;
}

int main() {
	cout << multiplyPoly("123456", "2345", 2) << endl;
	cout << 123456 * 2345;
    return 0;
}