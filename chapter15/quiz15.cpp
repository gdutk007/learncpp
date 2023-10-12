#include <iostream>
#include <string>
using namespace std;


class Monster {

   
   string name{};

   string roar{};

   int hitPoints{0};

   public:

   enum MonsterType {
      Dragon,
      Goblin,
      Ogre,
      Orc,
      Skeleton,
      Troll,
      Vampire,
      Zombie,
      max_monster_type
   };

   MonsterType type{max_monster_type};

   Monster() = default;

   Monster(MonsterType t ,string n, string r): 
                type{t},
                name{n},
                roar{r} {}

   Monster(MonsterType t ,string n, string r, int hp): 
                type{t},
                name{n},
                roar{r},
                hitPoints{hp} {}

   Monster(string n, string r): 
               name{n}, roar{r} {}

   string getTypeString(){
      string typestr = "";
      switch (type)
      {
         case Dragon: typestr = "dragon"; break;
         case Goblin:          typestr = "Goblin"; break;
         case Ogre:            typestr = "Ogre"; break;
         case Orc:             typestr = "Orc"; break;
         case Skeleton:        typestr = "Skeleton"; break;
         case Troll:           typestr = "Troll"; break;
         case Vampire:         typestr = "Vampire"; break;
         case Zombie:          typestr = "Zombie"; break;
         default:              typestr = "default"; break;
      }
      return typestr;
   }

   void print(){
      cout << name << " the " << getTypeString() << " has " << hitPoints << " hp and says " << roar << "\n";
   }


};

int main(){
   Monster skeleton{Monster::Skeleton,"Bones", "*rattle*",4};
   skeleton.print();
   return 0;
}