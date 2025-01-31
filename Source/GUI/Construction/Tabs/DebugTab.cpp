#include "../Settings.hpp"

#include "imgui.h"
#include "xorstr.hpp"

#include "../../ImGuiMacros.hpp"

#include "../../../Interfaces.hpp"

void Gui::Construction::SetupDebug()
{
	TABBAR(xorstr_("#Debug settings"), []() {
		TABITEM(xorstr_("Netvars"), Netvars::SetupGUI);
		TABITEM(xorstr_("Interfaces"), Interfaces::SetupGUI);
	})
}