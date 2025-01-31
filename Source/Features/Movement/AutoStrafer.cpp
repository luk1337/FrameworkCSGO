#include "../Movement.hpp"

#include "imgui.h"

#include "../General.hpp"

#include "../../SDK/Definitions/InputFlags.hpp"
#include "../../SDK/Definitions/StateFlags.hpp"
#include "../../SDK/GameClass/CBasePlayer.hpp"

#include "../../GameCache.hpp"
#include "../../Hooks/CreateMove/CreateMoveHook.hpp"
#include "../../Utils/Trigonometry.hpp"

#include <optional>

static bool enabled = false;
static bool directional = true;
static bool allowHardTurns = false;
static float hardTurnThreshold = 135.0f;
static bool onlyWhenIdle = false;

static std::optional<float> lastWishDirection = 0.0f;

void AdjustButtons(CUserCmd* cmd)
{
	// Technically not needed
	if (cmd->forwardmove > 0) {
		cmd->buttons |= IN_FORWARD;
		cmd->buttons &= ~IN_BACK;
	} else if (cmd->forwardmove < 0) {
		cmd->buttons |= IN_BACK;
		cmd->buttons &= ~IN_FORWARD;
	}
	if (cmd->sidemove < 0) {
		cmd->buttons |= IN_MOVELEFT;
		cmd->buttons &= ~IN_MOVERIGHT;
	} else if (cmd->sidemove > 0) {
		cmd->buttons |= IN_MOVERIGHT;
		cmd->buttons &= ~IN_MOVELEFT;
	}
}

void Features::Movement::AutoStrafer::CreateMove(CUserCmd* cmd)
{
	if (!enabled)
		return;

	CBasePlayer* localPlayer = GameCache::GetLocalPlayer();
	if (!localPlayer || !localPlayer->IsAlive())
		return;

	if (localPlayer->GetMoveType() == MOVETYPE_NOCLIP || localPlayer->GetMoveType() == MOVETYPE_LADDER)
		return;

	if (*localPlayer->Flags() & FL_ONGROUND && (!Features::General::EnginePrediction::enabled || Features::General::EnginePrediction::prePredictionFlags & FL_ONGROUND)) {
		// Only abort if we are not going to be in air again (if bhopping don't abort)
		if (cmd->forwardmove == 0.0f && cmd->sidemove == 0.0f)
			lastWishDirection.reset(); // We have no direction to move to.
		else
			lastWishDirection = atan2f(-cmd->sidemove, cmd->forwardmove);
		return;
	}

	Vector velocity = *localPlayer->Velocity();
	float speed = velocity.HorizontalLength();

	if (speed < 5.0f)
		return;

	float term = ConVarStorage::sv_air_max_wishspeed()->GetFloat() / ConVarStorage::sv_airaccelerate()->GetFloat() / ConVarStorage::sv_maxspeed()->GetFloat() * 100.0f / speed;

	if (term <= -1.0f || term >= 1.0f)
		return;

	float perfectDelta = acosf(term);

	if (directional) {
		// https://github.com/degeneratehyperbola/NEPS/blob/7e41ae811cf4ae136203093a059e137c8a10796f/NEPS/Hacks/Misc.cpp#L830
		float yaw = DEG2RAD(cmd->viewangles.y);
		float realDirection = atan2f(velocity.y, velocity.x) - yaw;
		float wishDirection;
		if (cmd->forwardmove != 0.0f || cmd->sidemove != 0.0f)
			wishDirection = atan2f(-cmd->sidemove, cmd->forwardmove);
		else if (lastWishDirection.has_value())
			wishDirection = lastWishDirection.value(); // If we release all keys go to the last known direction
		else
			return;
		lastWishDirection = wishDirection;

		float delta = std::remainderf(wishDirection - realDirection, 2.0f * M_PI);

		float newDirection;
		if (allowHardTurns && abs(delta) >= DEG2RAD(hardTurnThreshold))
			newDirection = realDirection + delta; // User wants to make a hard turn, don't smooth it, he might jump into the line of sight of an enemy
		else {
			newDirection = realDirection + (delta > 0.0 ? perfectDelta : -perfectDelta);
		}

		cmd->forwardmove = cosf(newDirection) * 450.0f;
		cmd->sidemove = -sinf(newDirection) * 450.0f;
		AdjustButtons(cmd);
	} else {
		float oldYaw = Hooks::CreateMove::lastCmd.viewangles.y;
		float newYaw = cmd->viewangles.y;

		float change = std::remainderf(newYaw - oldYaw, 360.0f);
		if (!onlyWhenIdle || (cmd->sidemove == 0.0f && cmd->forwardmove == 0.0f)) {
			cmd->forwardmove = 0.0f;
			if (change < 0.0)
				cmd->sidemove = 450.0f;
			else if (change > 0.0)
				cmd->sidemove = -450.0f;
			else
				cmd->sidemove = 0;
			AdjustButtons(cmd);
		}
	}
}

void Features::Movement::AutoStrafer::SetupGUI()
{
	Features::General::EnginePrediction::ImGuiWarning();
	ImGui::Checkbox(xorstr_("Enabled"), &enabled);
	ImGui::Checkbox(xorstr_("Directional"), &directional);
	if (directional) {
		ImGui::Checkbox(xorstr_("Allow hard turns"), &allowHardTurns);
		if (allowHardTurns)
			ImGui::SliderFloat(xorstr_("Hard turn threshold"), &hardTurnThreshold, 0.0f, 180.0f, xorstr_("%.2f"));
	} else {
		ImGui::Checkbox(xorstr_("Only when idle"), &onlyWhenIdle);
	}
}

BEGIN_SERIALIZED_STRUCT(Features::Movement::AutoStrafer::Serializer)
SERIALIZED_TYPE(xorstr_("Enabled"), enabled)
SERIALIZED_TYPE(xorstr_("Directional"), directional)
SERIALIZED_TYPE(xorstr_("Allow hard turns"), allowHardTurns)
SERIALIZED_TYPE(xorstr_("Hard turn threshold"), hardTurnThreshold)
SERIALIZED_TYPE(xorstr_("Only when idle"), onlyWhenIdle)
END_SERIALIZED_STRUCT
