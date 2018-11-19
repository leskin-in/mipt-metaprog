#include <iostream>

#include "TypeList.h"
#include "GenScatterF.h"
#include "InheritanceContainer.h"


using namespace std;


int main() {
    cout << "Compilation successful" << endl;

    typedef TypeList<short, TypeList<short, TypeNull> > MonsterDefinition;

    typedef GenScatterF<MonsterDefinition, InheritanceContainer> MonsterType;

    MonsterType monster;

    return 0;
}
