#include "./lib/liesel.h"

int main() {
	Liesel newPlayer;
	
	newPlayer.updateExp(500);
	std::cout << "Player:" << std::endl;
	std::cout << newPlayer.getExp() << std::endl;
	std::cout << newPlayer.getLevel() << std::endl;

	newPlayer.fireSkill.updateExp(100);
	std::cout << "Fire ball:" << std::endl;
	std::cout << newPlayer.fireSkill.getLevelUp() << std::endl;
	std::cout << newPlayer.fireSkill.getLevel() << std::endl;
	std::cout << newPlayer.fireSkill.getExp() << std::endl;
	std::cout << newPlayer.fireSkill.skillEffect() << std::endl;

	std::cout << "Destruction aura:" << std::endl;
	newPlayer.destructionSkill.updateExp(100);
	std::cout << newPlayer.destructionSkill.getLevelUp() << std::endl;
	std::cout << newPlayer.destructionSkill.getLevel() << std::endl;
	std::cout << newPlayer.destructionSkill.getExp() << std::endl;
	std::cout << newPlayer.destructionSkill.getCurrDoT() << std::endl;

	return 0;
}