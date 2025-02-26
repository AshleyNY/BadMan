#include "FriendListCommand.h"
#include "../../FriendList/FriendsManager.h"

FriendListCommand::FriendListCommand() : IMCCommand("friend", "Add/Remove friendly players", "<add/remove>") {
	registerAlias("friendlist");
}

FriendListCommand::~FriendListCommand() {
}

bool FriendListCommand::execute(std::vector<std::string>* args) {
	assertTrue(args->size() >= 3);
	std::string subcommand = args->at(1);
	std::transform(subcommand.begin(), subcommand.end(), subcommand.begin(), ::tolower);
	std::string searchedName = args->at(2);                                                     // Friend to add/remove
	std::transform(searchedName.begin(), searchedName.end(), searchedName.begin(), ::tolower);  // tolower

	EntityList* entList = Game.getEntityList();
	size_t listSize = entList->getListSize();

	if (listSize > 10000) {
		return true;
	}

	std::string playerName;
	//Loop through all our players and retrieve their information
	for (size_t i = 0; i < listSize; i++) {
		Entity* currentEntity = entList->get(i);

		std::string currentEntityName(currentEntity->getNameTag()->getText());

		std::transform(currentEntityName.begin(), currentEntityName.end(), currentEntityName.begin(), ::tolower);  // tolower

		if (currentEntity == 0)
			break;

		if (currentEntity == Game.getLocalPlayer())  // Skip Local player
			continue;

		if (currentEntityName.find(searchedName) == std::string::npos)  // Continue if name not found
			continue;

		playerName = currentEntity->getNameTag()->getText();
		break;
	}
	if (playerName.size() <= 1) {
		clientMessageF("[%sBadMan%s] %sCouldn't find player: %s!", GOLD, WHITE, RED, searchedName.c_str());
		return true;
	}
	if (subcommand == "add") {
		FriendsManager::addFriendToList(playerName);
		clientMessageF("[%sBadMan%s] %s%s is now your friend!", GOLD, WHITE, GREEN, playerName.c_str());
		return true;

	} else if (subcommand == "remove") {
		if (FriendsManager::removeFriend(searchedName)) {
			clientMessageF("[%sBadMan%s] %s%s has been removed from your friendlist!", GOLD, WHITE, GREEN, searchedName.c_str());
			return true;
		} else {
			clientMessageF("[%sBadMan%s] %s%s was not in your friendlist!", GOLD, WHITE, GREEN, searchedName.c_str());
			return true;
		}
	}
	return true;
}
