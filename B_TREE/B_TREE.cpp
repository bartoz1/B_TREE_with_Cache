#include <iostream>
#include <string>
#include "bTree.h"

using namespace std;

int main() {
    
    bTree* drzewo = nullptr;
    
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
        else if (odp == "R") {
            std::cin >> w;
            drzewo->delKey(w);
        }
        else if (odp == "L") {
            std::cin >> w;
            drzewo = new bTree(w);
            drzewo->loadTree();
        }
        else if (odp == "C") {
            drzewo->searchWithCache();
        }
        else if (odp == "SC") {
            drzewo->searchWithSuperCache();
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
