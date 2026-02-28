#pragma once
#include <string>

using namespace std;

typedef enum class programTypes_e {
    vertex = 0,
    fragment = 1
} programTypes_e;

class Program
{
    protected:
        programTypes_e type;
        std::string fileName;
        unsigned int idProgram;

    public:
        // Constructor
        Program(const std::string& fileName);

        // Destructor
        virtual ~Program();

        // Getters
        programTypes_e getType() const { return type; }
        unsigned int getID() const { return idProgram; }
        const std::string& getFileName() const { return fileName; }

        // Métodos
        virtual void readFile() = 0;
        virtual void compile() = 0;
        virtual void checkErrors() = 0;

};

