#define GLAD_BIN
#include "mapi/common.h"
#include "GLFWKeyManager.h"
#include "System.h"
#include "BillBoard.h"

using namespace std;


int main(int argc, char** argv)
{
	
		//bucle principal
		System::init();
		System::render->mainLoop();
	return 0;

}