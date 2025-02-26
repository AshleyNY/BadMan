#include "ClientInstance.h"

#include <cstdarg>

#include "../Utils/Logger.h"
#include "../Utils/Utils.h"

__int64 MinecraftGame::getServerEntries() {
	return Utils::CallVFunc<30, __int64>(this);
}
void GuiData::displayClientMessage(std::string *a2) {
	using displayClientMessage = void(__thiscall *)(void *, TextHolder &);
	static displayClientMessage displayMessageFunc = reinterpret_cast<displayClientMessage>(FindSignature("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 45 0F B6 E0 4C 8B F9"));

	TextHolder text = TextHolder(*a2);

	if (displayMessageFunc != nullptr)
		displayMessageFunc(this, text);
}
void GuiData::displayClientMessageF(const char *fmt, ...) {
	va_list arg;
	va_start(arg, fmt);
	displayClientMessageVA(fmt, arg);
	va_end(arg);
}
void GuiData::displayClientMessageVA(const char *fmt, va_list lis) {
	auto lengthNeeded = _vscprintf(fmt, lis) + 1;
	if (lengthNeeded >= 300) {
		logF("A message that was %i characters long could not be fitted into the buffer", lengthNeeded);
		return;
	}

	char message[300];
	vsprintf_s(message, 300, fmt, lis);
	std::string msg(message);
	displayClientMessage(&msg);
}
void GuiData::displayClientMessageNoSendF(const char *fmt, ...) {
	va_list arg;
	va_start(arg, fmt);
	displayClientMessageVA(fmt, arg);
	va_end(arg);
}

// Use mce::MaterialPtr::createMaterial
mce::MaterialPtr::MaterialPtr(HashedString materialName, bool switchable) {
	using materialPtrConst_t = void(__fastcall *)(mce::MaterialPtr *, __int64, const HashedString *);
	static materialPtrConst_t materialPtrConst = reinterpret_cast<materialPtrConst_t>(FindSignature("48 89 4C 24 ? ? 48 83 EC ? 4C 8B CA 48 8B D9 ? ? 48 89 01 48 89 41 ? 48 8B 02 49 8B D0 49 8B C9 48 8B 40 ? ? ? ? ? ? ? 4C 8B C0"));

	static __int64 renderGroupBase = 0, switchableRenderGroupBase = 0;

	if (renderGroupBase == 0) {
		auto sig = FindSignature("48 8D 0D ? ? ? ? 48 8B 40 ? ? ? ? ? ? ? 48 8B F8 48 8B 50 ? 48 85 D2") + 3;

		auto off = *reinterpret_cast<int *>(sig);
		renderGroupBase = sig + 4 + off;
	}

	if (switchableRenderGroupBase == 0) {
		auto sig = FindSignature("48 8D 0D ? ? ? ? 48 8B 40 ? ? ? ? ? ? ? 48 8B D8 48 8B 50 ? 48 85 D2 74") + 3;

		auto off = *reinterpret_cast<int *>(sig);
		renderGroupBase = sig + 4 + off;
	}

	__int64 useRenderGroupBase = switchable ? switchableRenderGroupBase : renderGroupBase;

	//HashedString hashedStr(materialName);
	materialPtrConst(this, useRenderGroupBase, &materialName);
}

mce::MaterialPtr* mce::MaterialPtr::createMaterial(HashedString materialName) {
	static __int64 *materialCreator = nullptr;

	if (materialCreator == nullptr) {
		// Sig returns 6 addresses, all of them point to the same offset
		uintptr_t sigOffset = FindSignature("48 8B 05 ? ? ? ? 48 8D 55 ? 48 8D 0D ? ? ? ? 48 8B 40 ? FF 15 ? ? ? ? 48 8B F8");
		int offset = *reinterpret_cast<int *>(sigOffset + 3);
		materialCreator = reinterpret_cast<__int64 *>(sigOffset + offset + 7);
	}

	return Utils::CallVFunc<1, mce::MaterialPtr *, const HashedString *>(materialCreator, &materialName);
}

void mce::Mesh::renderMesh(__int64 screenContext, mce::MaterialPtr *material, size_t numTextures, __int64 **textureArray) {
	struct TextureData {
		size_t numTextures;
		__int64 **texturePtr;
	} data;
	using renderMesh_t = __int64 (*)(mce::Mesh *, __int64, mce::MaterialPtr *, TextureData *);
	static renderMesh_t renderMesh = reinterpret_cast<renderMesh_t>(FindSignature("40 53 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ?? ?? ?? ?? 48 C7 44 24 ?? ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 84 24 ?? ?? ?? ?? 49 8B F1 4D 8B E0 4C"));

	data.numTextures = numTextures;
	data.texturePtr = textureArray;

	renderMesh(this, screenContext + 0x10, material, &data);
}