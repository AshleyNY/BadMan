#include "AirSwim.h"

AirSwim::AirSwim() : IModule(0, Category::MOVEMENT, "Swim in Air.") {
}

AirSwim::~AirSwim() {
}

const char* AirSwim::getModuleName() {
	return ("AirSwim");
}

void AirSwim::onEnable() {
	if (Game.getLocalPlayer() == nullptr)
		return;
	Game.getLocalPlayer()->startSwimming();
}

void AirSwim::onTick(GameMode* gm) {
	Game.getLocalPlayer()->doWaterSplashEffect();
	Game.getLocalPlayer()->startSwimming();
}

void AirSwim::onDisable() {
	if (Game.getLocalPlayer() == nullptr)
		return;
	Game.getLocalPlayer()->stopSwimming();
}