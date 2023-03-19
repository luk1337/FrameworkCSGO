#include "GUI.hpp"

#include <algorithm>
#include <mutex>

#include "imgui.h"
#include "xorstr.hpp"

#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"

#include "../Hooks/SDL/SDLHook.hpp"

#include "../Features/General.hpp"
#include "../Features/Legit.hpp"

#include "Construction/Settings.hpp"

bool Gui::visible = true;

void Gui::Create()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	// Might not work on certain distros/configurations
	io.Fonts->AddFontFromFileTTF(xorstr_("/usr/share/fonts/noto/NotoSans-Regular.ttf"), 24.0f);

	io.IniFilename = nullptr;
	io.LogFilename = nullptr;
}

void Gui::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void Gui::SwapWindow(SDL_Window* window)
{
	static std::once_flag init;
	std::call_once(init, [&]() {
		ImGui_ImplSDL2_InitForOpenGL(window, nullptr);
		ImGui_ImplOpenGL3_Init();
	});

	ImGuiIO& io = ImGui::GetIO();
	io.SetPlatformImeDataFn = nullptr;

	int width {}, height {};
	SDL_GetWindowSize(window, &width, &height);

	io.DisplaySize = ImVec2((float)width, (float)height);
	io.MousePos = ImVec2(std::clamp(io.MousePos.x, 0.0F, (float)width), std::clamp(io.MousePos.y, 0.0F, (float)height));

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(window);
	ImGui::NewFrame();

	Features::General::Menu::ImGuiLoop(); // Will take care of the menu key

	if (visible) {
		const ImVec2 size(800, 600);
		ImGui::SetNextWindowSize(size, ImGuiCond_Once);
		ImGui::SetNextWindowPos(ImVec2(static_cast<float>(width) / 2.0F - size.x / 2.0F, static_cast<float>(height) / 2.0F - size.y / 2.0F), ImGuiCond_Once);

		ImGui::Begin(xorstr_("Framework"));

		ImGui::SetWindowSize(ImVec2(400, 300), ImGuiCond_Once);

		Construction::SetupConstruction();

		ImGui::End();
	}

	Features::General::Watermark::ImGuiRender(ImGui::GetBackgroundDrawList());
	Features::General::EventLog::ImGuiRender(ImGui::GetBackgroundDrawList());

	Features::Legit::Esp::ImGuiRender(ImGui::GetBackgroundDrawList());
	Features::Legit::SpectatorList::ImGuiRender(ImGui::GetBackgroundDrawList());

	io.MouseDrawCursor = visible;
	io.WantCaptureMouse = visible;
	io.WantCaptureKeyboard = visible;

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// I don't even want to know why I have to do this
unsigned int lastTextInput;

void Gui::PollEvent(SDL_Event* event)
{
	if (event->type == SDL_TEXTINPUT && lastTextInput >= event->text.timestamp)
		return;

	ImGuiIO& io = ImGui::GetIO();
	// Emulate these 2 events, because ImGui is broken... :c
	if (event->type == SDL_MOUSEMOTION) {
		io.MousePos.x += (float)event->motion.xrel;
		io.MousePos.y += (float)event->motion.yrel;
	} else if (event->type == SDL_MOUSEWHEEL) {
		io.MouseWheelH += (float)event->wheel.x;
		io.MouseWheel += (float)event->wheel.y;
	} else
		ImGui_ImplSDL2_ProcessEvent(event);

	if (event->type == SDL_MOUSEBUTTONUP)
		reinterpret_cast<void (*)(SDL_Window*, int, int)>(Hooks::SDL::warpMouseInWindow->proxy)(Hooks::SDL::windowPtr, (int)io.MousePos.x, (int)io.MousePos.y);

	if (event->type == SDL_TEXTINPUT)
		lastTextInput = event->text.timestamp;

	if (visible)
		event->type = -1; // Change type to an invalid event to make the game ignore it.
}

bool Gui::WarpMouseInWindow()
{
	// lol no
	return visible;
}
