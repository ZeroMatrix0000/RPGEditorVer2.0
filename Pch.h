/*
 * FileName:     Pch.h
 * Author:       Takao Hayata
 * Last Updated: 2026/06/30
 * 
 * プリコンパイル済みヘッダファイル
 */

#pragma once

 // 型チェックを厳密に
#define STRICT
// あまり使われない関数を省く
#define WIN32_LEAN_AND_MEAN

// WindowsAPI
#include <Windows.h>
// ComPtr
#include <wrl/client.h>

// Direct3D 11
#include <d3d11_4.h>
// DXGI
#include <dxgi1_6.h>
// Direct2D
#include <d2d1_3.h>
// DirectWrite
#include <dwrite_3.h>

// 文字列
#include <string>
// スマートポインタ
#include <memory>
// 可変長配列
#include <vector>
// 配列
#include <array>
// キュー
#include <queue>
// マップ
#include <unordered_map>
// 集合
#include <unordered_set>
// 便利
#include <utility>
// 関数
#include <functional>
// インデックス型
#include <typeindex>

// DirectXTK
#include "BufferHelpers.h"
#include "CommonStates.h"
#include "DDSTextureLoader.h"
#include "DirectXHelpers.h"
#include "Effects.h"
#include "GamePad.h"
#include "GeometricPrimitive.h"
#include "GraphicsMemory.h"
#include "Keyboard.h"
#include "Model.h"
#include "Mouse.h"
#include "PostProcess.h"
#include "PrimitiveBatch.h"
#include "ScreenGrab.h"
#include "SimpleMath.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "VertexTypes.h"
#include "WICTextureLoader.h"

#include "Audio.h"

// TがUを継承しているかどうか
template<typename T, typename U>
concept IsDerived = std::derived_from<T, U> && !std::same_as<T, U>;
