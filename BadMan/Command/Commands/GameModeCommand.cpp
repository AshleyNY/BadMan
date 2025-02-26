#include "GameModeCommand.h"

GameModeCommand::GameModeCommand() : IMCCommand("gamemode", "Changes the local player's gamemode", "<number>") {
	registerAlias("gm");
}

GameModeCommand::~GameModeCommand() {
}

bool GameModeCommand::execute(std::vector<std::string>* args) {
	assertTrue(Game.getLocalPlayer() != nullptr);
	assertTrue(args->size() > 1);
	int gamemode = assertInt(args->at(1));
	if (gamemode >= 0 && gamemode <= 2) {
		Game.getLocalPlayer()->setGameModeType(gamemode);
		clientMessageF("[%sBadMan%s] %sGameMode changed!", GOLD, WHITE, GREEN);
		return true;
	}

	clientMessageF("[%sBadMan%s] %sInvalid GameMode!", GOLD, WHITE, RED);
	return true;
}
