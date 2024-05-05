#include "PongGameAPI.hpp"

using namespace RSDK;

#if RETRO_USE_MOD_LOADER
extern "C" {
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
}

const char *modID = "PongGameAPI";
#endif

GlobalVariables::Constructor c;
GlobalVariables *globals = nullptr;

void GlobalVariables::Init(void *g)
{
    GlobalVariables *globals = (GlobalVariables *)g;
    memset(globals, 0, sizeof(GlobalVariables));
}

void InitModAPI(void) {}

#if RETRO_USE_MOD_LOADER
#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))

void InitModAPI(void);
#endif