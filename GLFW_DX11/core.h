#pragma once
#include <spdlog\spdlog.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <shellapi.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <memory>
#include <vector>
#include <string>
#include <wrl.h>
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <functional>
#include <assimp\scene.h>
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>

#include "Keyborad.h"
#include "Mouse.h"
#include "Timer.h"
#include "Config.h"
#include "stb_image.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_dx11.h"
#include "imgui\imgui_impl_win32.h"

using Microsoft::WRL::ComPtr;
using std::vector;
using std::unique_ptr;
using std::make_unique;
using spdlog::info;
using spdlog::critical;
using std::string;

namespace dx = DirectX;