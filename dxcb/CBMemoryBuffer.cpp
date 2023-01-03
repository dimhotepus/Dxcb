// Open source.
// See Vincent Scheib rant at
// http://beautifulpixels.blogspot.com/2008/07/parallel-rendering-with-directx-command.html

#include "CBMemoryBuffer.h"

#include <d3d9.h>  // required for CBMacros.h

#include <cstdio>

#include "CBMacros.h"  // for DXCB_ENABLE_MEMORY_TRACE

#if DXCB_ENABLE_MEMORY_TRACE
namespace {

bool use_memory_trace;
bool use_buffer_playback_trace;
bool use_buffer_record_trace;

}  // namespace

namespace dxcb {

bool GetMemoryTrace() { return use_memory_trace; }
void SetMemoryTrace(bool on) { use_memory_trace = on; }

bool GetBufferRecordTrace() { return use_buffer_playback_trace; }
void SetBufferRecordTrace(bool on) { use_buffer_playback_trace = on; }

bool GetBufferPlayTrace() { return use_buffer_record_trace; }
void SetBufferPlayTrace(bool on) { use_buffer_record_trace = on; }

}  // namespace dxcb
#endif

namespace dxcb {

const char *CBMemoryBuffer::func_names_[120] = {"Null",
                                                "QueryInterface",
                                                "AddRef",
                                                "Release",
                                                "DrawPrimitive",
                                                "DrawIndexedPrimitive",
                                                "SetStreamSource",
                                                "SetStreamSourceFreq",
                                                "SetVertexDeclaration",
                                                "SetIndices",
                                                "TestCooperativeLevel",
                                                "EvictManagedResources",
                                                "BeginScene",
                                                "EndScene",
                                                "BeginStateBlock",
                                                "SetCursorProperties",
                                                "SetCursorPosition",
                                                "SetDialogBoxMode",
                                                "GetDeviceCaps",
                                                "GetDisplayMode",
                                                "GetCreationParameters",
                                                "CreateAdditionalSwapChain",
                                                "GetSwapChain",
                                                "Reset",
                                                "Present",
                                                "GetBackBuffer",
                                                "GetRasterStatus",
                                                "SetGammaRamp",
                                                "GetGammaRamp",
                                                "CreateTexture",
                                                "CreateVolumeTexture",
                                                "CreateCubeTexture",
                                                "CreateVertexBuffer",
                                                "CreateIndexBuffer",
                                                "CreateRenderTarget",
                                                "CreateDepthStencilSurface",
                                                "UpdateSurface",
                                                "UpdateTexture",
                                                "GetRenderTargetData",
                                                "GetFrontBufferData",
                                                "StretchRect",
                                                "ColorFill",
                                                "CreateOffscreenPlainSurface",
                                                "SetRenderTarget",
                                                "GetRenderTarget",
                                                "SetDepthStencilSurface",
                                                "GetDepthStencilSurface",
                                                "Clear",
                                                "SetTransform",
                                                "GetTransform",
                                                "MultiplyTransform",
                                                "SetViewport",
                                                "GetViewport",
                                                "SetMaterial",
                                                "GetMaterial",
                                                "SetLight",
                                                "GetLight",
                                                "LightEnable",
                                                "GetLightEnable",
                                                "SetClipPlane",
                                                "GetClipPlane",
                                                "SetRenderState",
                                                "GetRenderState",
                                                "CreateStateBlock",
                                                "EndStateBlock",
                                                "SetClipStatus",
                                                "GetClipStatus",
                                                "GetTexture",
                                                "SetTexture",
                                                "GetTextureStageState",
                                                "SetTextureStageState",
                                                "GetSamplerState",
                                                "SetSamplerState",
                                                "ValidateDevice",
                                                "SetPaletteEntries",
                                                "GetPaletteEntries",
                                                "SetCurrentTexturePalette",
                                                "GetCurrentTexturePalette",
                                                "SetScissorRect",
                                                "GetScissorRect",
                                                "SetSoftwareVertexProcessing",
                                                "SetNPatchMode",
                                                "DrawPrimitiveUP",
                                                "DrawIndexedPrimitiveUP",
                                                "ProcessVertices",
                                                "CreateVertexDeclaration",
                                                "GetVertexDeclaration",
                                                "SetFVF",
                                                "GetFVF",
                                                "CreateVertexShader",
                                                "SetVertexShader",
                                                "GetVertexShader",
                                                "SetVertexShaderConstantF",
                                                "GetVertexShaderConstantF",
                                                "SetVertexShaderConstantI",
                                                "GetVertexShaderConstantI",
                                                "SetVertexShaderConstantB",
                                                "GetVertexShaderConstantB",
                                                "GetStreamSource",
                                                "GetStreamSourceFreq",
                                                "GetIndices",
                                                "CreatePixelShader",
                                                "SetPixelShader",
                                                "GetPixelShader",
                                                "SetPixelShaderConstantF",
                                                "GetPixelShaderConstantF",
                                                "SetPixelShaderConstantI",
                                                "GetPixelShaderConstantI",
                                                "SetPixelShaderConstantB",
                                                "GetPixelShaderConstantB",
                                                "DrawRectPatch",
                                                "DrawTriPatch",
                                                "DeletePatch",
                                                "CreateQuery",
                                                "GetDirect3D",
                                                "GetAvailableTextureMem",
                                                "GetNumberOfSwapChains",
                                                "ShowCursor",
                                                "GetSoftwareVertexProcessing",
                                                "GetNPatchMode"};

void CBMemoryBuffer::GetMemory(size_t *&memory, size_t &count) const {
  memory = memory_;
  count = memory_size_;
}

void CBMemoryBuffer::SetMemory(size_t *memory, size_t count) {
  memory_ = memory;
  memory_size_ = count;
  next_memory_ = memory;
}

}  // namespace dxcb
