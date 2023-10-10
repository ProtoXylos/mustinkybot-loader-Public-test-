#ifndef PCH_H
#define PCH_H

// Windows headers
#include <Windows.h>
#include <tchar.h>

// Standard C++ headers
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

// COM and WMI headers
#include <comutil.h> 
#include <wbemidl.h>

// DirectX headers
#include "d3d9.h"
#include "d3d11.h"

// ImGui headers
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

// libcurl headers
#define CURL_STATICLIB
#include "curl/curl.h"

// Linking to libraries
#pragma comment(lib, "comsuppw.lib") 
#pragma comment(lib, "wbemuuid.lib")

// Project-specific headers
#include "drawing/Drawing.h"
#include "utility/login/login.h"
#include "utility/hwid/hwid.h"
#include "utility/cheat/cheat.h"
#include "utility/directory/directory.h"
#include "utility/notifications/notification.h"
#include "utility/flux/flux.hpp"

#endif
