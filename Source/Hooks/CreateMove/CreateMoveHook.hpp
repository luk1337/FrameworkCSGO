#ifndef HOOKS_CREATEMOVE
#define HOOKS_CREATEMOVE

#include "../../SDK/GameClass/CUserCmd.hpp"
#include "../Hooks.hpp"

namespace Hooks::CreateMove {
	inline Hook* hook = nullptr;
	inline CUserCmd lastCmd{};

	void Hook();
	void Unhook();
}

#endif
