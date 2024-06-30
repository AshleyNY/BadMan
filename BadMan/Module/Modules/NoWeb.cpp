#include "NoWeb.h"

NoWeb::NoWeb() : IModule(0, Category::MOVEMENT, "Ignore cobwebs slowdown.") {
}

NoWeb ::~NoWeb() {
}

const char* NoWeb::getModuleName() {
	return ("NoWeb");
}

void NoWeb::onTick(GameMode* gm) {
	gm->player->resetBlockMovementSlowdownMultiplier();
}