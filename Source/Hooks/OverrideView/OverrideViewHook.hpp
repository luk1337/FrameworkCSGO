#ifndef HOOKS_OVERRIDEVIEW
#define HOOKS_OVERRIDEVIEW

#include "../../SDK/GameClass/CViewSetup.hpp"
#include "../Hooks.hpp"

namespace Hooks::OverrideView {
	inline Hook* hook = nullptr;
	inline CViewSetup lastViewSetup{};
	inline Vector cameraPosition{};

	void Hook();
	void Unhook();
}

#endif
