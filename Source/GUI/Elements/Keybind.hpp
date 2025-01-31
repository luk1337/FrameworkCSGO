#ifndef GUI_ELEMENTS_KEYBIND
#define GUI_ELEMENTS_KEYBIND

#include "imgui.h"

bool IsInputDown(int key, bool _default, bool disableInMenu = true);

namespace ImGui {
	IMGUI_API bool InputSelector(const char* label, int& key, const ImVec2& size = ImVec2(0, 0));
}

#endif
