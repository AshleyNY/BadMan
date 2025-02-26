#include "CoordsCommand.h"

CoordsCommand::CoordsCommand() : IMCCommand("coords", "Prints your coordinates", "") {
	registerAlias("pos");
}

CoordsCommand::~CoordsCommand() {
}

bool CoordsCommand::execute(std::vector<std::string>* args) {
	Vec3 *pos = Game.getLocalPlayer()->getPosition();
	float yPos = pos->y - 1.62f;
	clientMessageF("[%sBadMan%s] %sX: %.2f Y: %.2f Z: %.2f", GOLD, WHITE, GREEN, pos->x, yPos /* eye height */, pos->z);
	return true;
}
