#include "Program.h"
#include "Common.h"

Program::Program(const std::string& fileName): type(programTypes_e::vertex),fileName(fileName),idProgram(-1)
{
	if (fileName.ends_with(".vert"))
	{
		type = programTypes_e::vertex;
	}
	if (fileName.ends_with(".frag")) 
	{
		type = programTypes_e::fragment;
	}
}

Program::~Program()
{}
