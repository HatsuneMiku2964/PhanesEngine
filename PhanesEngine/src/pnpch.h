#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <functional>
#include <memory>
#include <utility>
#include <algorithm>

#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>

#include <glm/glm.hpp>

#include "Phanes/Core/Core.h"

#include "Phanes/Core/TimeStep/TimeStep.h"

#include "Phanes/Core/Renderer/Renderer/Renderer.h"

#include "Phanes/Core/Debugging/Log/Log.h"
#include "Phanes/Core/Debugging/Benchmark/Instrumentation.h"

#include "Phanes/Core/Transform/Transform.h"

#ifdef PN_PLATFORMS_WINDOWS
    #include <Windows.h>
#endif

#ifdef _MSC_VER
    #pragma warning(disable : 4251) // make error C4251 shut up
#endif