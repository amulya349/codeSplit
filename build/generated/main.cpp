#include <iostream>
#include <conio.h>
#include "RandGenAnsi.h"
#include "RandGenParkMiller.h"
#include "PiCalculator.h"

using namespace std;


int main(int argc, char *argv[])
{
    const long SEED = 12345678L;
    const int N_POINTS = 1e4;

    RandGenAnsi rAnsi;
    rAnsi.init(SEED);

    PiCalculator c(&rAnsi, N_POINTS);
    cout << "ansi-pi: " << c.calc() << endl;

    RandGenParkMiller rPark;
    rPark.init(SEED);
    PiCalculator cPark(&rPark, N_POINTS);
    cout << "park and miller-pi: " << cPark.calc() << endl;
	getch();
    return 0;
}


