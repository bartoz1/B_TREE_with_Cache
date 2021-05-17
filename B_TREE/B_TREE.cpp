#include <iostream>
#include <string>
//#include "bTNode.h"
// b tree without cache
#include "bTree.h"

using namespace std;

int main() {
    
    bTree* drzewo = nullptr;
    
    /*string odp;
    while (std::cin >> odp) {
        std::cout << odp << "\n";
    }*/


    
    int w;
    string odp;
    //std::cin >> odp;
    
    while (std::cin >>odp) {
        if (odp == "I") {
            std::cin >> w;
            drzewo = new bTree(w);
        }
        else if (odp == "A") {
            std::cin >> w;
            drzewo->add(w);

        }
        else if (odp == "?") {
            std::cin >> w;
            drzewo->search(w);
        }
        else if (odp == "L") {
            std::cin >> w;
            drzewo = new bTree(w);
            drzewo->loadTree();
        }
        else if (odp == "C") {
            drzewo->searchWithCache();
        }
        else if (odp == "S") {
            drzewo->printTree();
        } 
        else if (odp == "P") {
            drzewo->printValues();
        }
        else if (odp == "X")
            break;
    }
    
}
