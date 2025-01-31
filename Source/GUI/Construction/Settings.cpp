#include "Settings.hpp"

#include "xorstr.hpp"

#include "../../Features/Features.hpp"
#include "../ImGuiMacros.hpp"

void Gui::Construction::SetupConstruction()
{
	Features::SetupGUI();
	TABBAR(xorstr_("#Settings"), []() {
		TABITEM(xorstr_("Debug"), Gui::Construction::SetupDebug);
	})
}