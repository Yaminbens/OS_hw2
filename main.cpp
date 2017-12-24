#include "bank.h"
#include "Account.h"
#include "locker.h"
#include "logs.h"
#include "ATM.h"
#include <pthread.h>
#include <vector>

#define MAXLINE 100
using namespace std;

int main(int argc, char* input[])
{

//Break down input arguments to strings.
	bank myBank;
/* MAYA: I wrote this to chack..
    myBank.newAccount(1, 1234, 1155, 200, true);
	myBank.newAccount(1, 1234, 1155, 200, true);
*/

//    vector<string> cmds;
//    int ATMnum = atoi(input[1]);
//    for(int i=1; i <= ATMnum; i++)
//	{
//    	char* dest[MAXLINE];
//    	strcpy(dest,input[i+1]);
//    	cmds.push_back(input[i+1]);
//	}
//	int ATMnum = atoi(input[1]);
    std::vector<std::string> cmds(input + 1, input + argc);

    vector<Thread> args(atoi(cmds[0].c_str()));

    for(int i=0; i<atoi(cmds[0].c_str()); i++)
    {
    	args[i].myBank = &myBank;
     	args[i].id = (i+1);
     	args[i].src = cmds.at(i+1);
    }
	pthread_t ATMs[atoi(cmds[0].c_str())];
	pthread_t commThr;
	pthread_t detailsThr;

	for (int i = 0; i<atoi(cmds[0].c_str()); i++)
	{
		pthread_create(&ATMs[i], NULL, &atmForThread, &args[i]);
	}

	pthread_create(&(commThr), NULL, myBank.commForThread, &myBank);
    pthread_create(&(detailsThr),NULL, myBank.statusForThread,&myBank);

    for(int i=0; i<atoi(cmds[0].c_str()); i++)
    {
        pthread_join(ATMs[i],NULL);
    }

    myBank.finishedFlag = true;
    pthread_join(commThr,NULL);


    pthread_join(detailsThr,NULL);




	return 0;
}
