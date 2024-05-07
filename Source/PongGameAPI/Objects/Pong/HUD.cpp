// ---------------------------------------------------------------------
// RSDK Project: Pong GameAPI
// Object Description: HUD Object
// Object Author: MegAmi
// ---------------------------------------------------------------------

#include "HUD.hpp"
#include "Paddle.hpp"

using namespace RSDK;

namespace GameLogic
{
RSDK_REGISTER_OBJECT(HUD);

void HUD::Update(void) {}
void HUD::LateUpdate(void) {}
void HUD::StaticUpdate(void) {}

void HUD::Draw(void)
{
    // White stripes
    for (int32 i = 0; i < screenInfo->size.y; i += 12) {
        Graphics::DrawRect(screenInfo->center.x - 2, i, 4, 8, 0xFFFFFF, 0xFF, INK_NONE, true);
    }

    RSDK::Vector2 position;
    position.x = TO_FIXED(screenInfo->center.x - 32);
    position.y = TO_FIXED(32);

    this->animator.frameID = RSDK_GET_ENTITY(SLOT_PLAYER1, Paddle)->score;
    this->animator.DrawSprite(&position, true);

    position.x             = TO_FIXED(screenInfo->center.x + 32);
    this->animator.frameID = RSDK_GET_ENTITY(SLOT_PLAYER2, Paddle)->score;
    this->animator.DrawSprite(&position, true);
}

void HUD::Create(void *data)
{
    if (!sceneInfo->inEditor) {
        this->active        = ACTIVE_NORMAL;
        this->visible       = true;
        this->drawGroup     = 1;
        this->animator.SetAnimation(sVars->aniFrames, 0, true, 0);
    }
}

void HUD::StageLoad(void)
{
    // Copy HUD to slot 3
    foreach_all(HUD, spawn)
    {
        HUD *hud = RSDK_GET_ENTITY(SLOT_HUD, HUD);
        spawn->Copy(hud, true);
    }

    sVars->aniFrames.Load("Pong/HUD.bin", SCOPE_STAGE);
}

#if GAME_INCLUDE_EDITOR
void HUD::EditorDraw(void) {}

void HUD::EditorLoad(void) {}
#endif

#if RETRO_REV0U
void HUD::StaticLoad(Static *sVars) { RSDK_INIT_STATIC_VARS(HUD); }
#endif

void HUD::Serialize(void) {}

} // namespace GameLogic
