#pragma once

#include <iostream>
#include <string>
#include <sstream>

#include<functional>
#include <memory>
#include <utility>
#include <algorithm>

#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Phanes/Log/Log.h"

#ifdef PN_PLATFORMS_WINDOWS
    #include <Windows.h>
#endif

#ifdef _MSC_VER
    #pragma warning(disable : 4251) // make error C4251 shut up
#endif