#include "system.h"
#include <iostream.h>

extern int userMain(int argc, char* argv[]);

int main(int argc, char* argv[]) {

	//cout<<"EJ BRE, ALO BRE"<<endl;

	int x;
	System::prepare();
	//cout<<"Misa burek"<<endl;
	x = userMain(argc, argv);
	System::end();
	//cout<<x<<endl;
	return x;
}




