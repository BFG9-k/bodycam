#pragma once
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <thread>
#include <memory>
#include <algorithm>

#include "core/utils/logger/logger.h"
#include "core/bootstrap_cheat.h"

#include "core/thirdparty/minhook/minhook.h"

#include "game/sdk/SDK/Basic.hpp"
#include "game/sdk/SDK/Engine_classes.hpp"
#include "game/sdk/SDK/Bodycam_Player_classes.hpp"

#include "game/hooked/hooked.h"

#include "game/features/features.h"