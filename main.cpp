#include "bank.h"
#include "Account.h"

#include "pthread.h"
#include <vector>

using namespace std;

int main(int ATMnum, char* input[])
{
    //Break down input arguments to strings.
	bank b;
	b.newAccount(1, 1234, 1155, 200, true);
	b.newAccount(1, 1234, 1155, 200, true);


	return 0;
}
