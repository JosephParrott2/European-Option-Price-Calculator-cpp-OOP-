#include "vanilla_option.h"
#include <cmath>
#include <iostream>

using namespace std;

int main() {

	VanillaOption Object_Test(285, 0.04, 2, 315, 0.125);

	cout << Object_Test.calc_put_price();

}