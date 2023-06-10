#include <iostream>
#include <fstream>
using namespace std;

int main() {

    std::ifstream file("human.txt"); 

    if (!file) {
        std::cout << "Error opening file." << std::endl;
        return 1;
    }
    file.seekg(0, std::ios::end);
    int fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

   
    char* content = new char[fileSize];

    file.read(content, fileSize);

    file.close();

    std::cout << content << std::endl;

    delete[] content;

    return 0;
}
