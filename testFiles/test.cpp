#include "../Enemy.h"
#include "../Global.h"
#include "../Menu.h"
#include "../Player.h"
#include "../PowerUp.h"
#include "../SpecialEnemy.h"
#include "../bullet.h"
#include "../entity.h"
#include "test.h"
#include <SFML/Graphics/Rect.hpp>

#include "iostream"

using namespace std;

int main() {
  int numPlayerPass = playerTests();
  int numEnemyPass = enemyTests();

  if (numPlayerPass == 3) {
    cout << "SUCCESS: all player tests passed." << endl;
  } else {
    cout << numPlayerPass << " out of 3 player tests have passed." << endl;
  }

  if (numEnemyPass == 3) {
    cout << "SUCCESS: all enemy tests passed.";
  } else {
    cout << numEnemyPass << " out of 3 enemy tests have passed." << endl;
  }

  return 0;
}