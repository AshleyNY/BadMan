#pragma once

#include "Module.h"
#include <set>

class NameTags : public IModule {
public:
	std::set<std::string> nameTags;
	bool displayArmor = false;
	bool underline = true;
	bool mynametag = false;
	float opacity = 0.2f;
	NameTags();
	~NameTags();

	bool* ingameNametagSetting = nullptr;
	bool lastSetting = true;
	bool gotPrevSetting = false;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPreRender(MinecraftUIRenderContext* renderCtx) override;
	virtual void onDisable() override;
};
