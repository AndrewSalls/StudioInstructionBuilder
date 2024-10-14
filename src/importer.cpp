#include "importer.hpp"
#include <fstream>

static std::vector<Mesh3D>* readFile(std::string ldrPath, std::string templateLDRFolder) {
    std::ifstream file;
    file.open(ldrPath);
    std::string line; 

    std::vector<Mesh3D>* output = new std::vector<Mesh3D>();
  
    if (file.is_open()) { 
        while (getline(file, line)) {
            if(line.length() > 0 && line.at(0) != '0')
            output->push_back(parseLine(line, templateLDRFolder));
        } 
  
        file.close();
        return output; 
    } 
    else {
        return NULL;
    } 
}

static Mesh3D parseLine(std::string ldrLine, std::string templateLDRFolder) {

}