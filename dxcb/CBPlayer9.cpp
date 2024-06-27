// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
// Open source.
// See Vincent Scheib rant at
// http://beautifulpixels.blogspot.com/2008/07/parallel-rendering-with-directx-command.html

#ifndef DXCB_INVOKE_PREPROCESSOR

#include <d3d9.h>

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <type_traits>

#include "PREPROCESSED_CBPlayer9.cpp"

#else

#include "CBMacros.h"
#include "CBMemoryBuffer.h"
#include "CBPlayer9.h"

namespace {

// Must access by an (enum - D3d9Commands::Null)
const dxcb::PlayerMemberPtr PlaybackFunctionTable[] = {
    &dxcb::CBPlayer9::DoNULLCall, &dxcb::CBPlayer9::DoQueryInterface,
    &dxcb::CBPlayer9::DoAddRef, &dxcb::CBPlayer9::DoRelease,
    &dxcb::CBPlayer9::DoDrawPrimitive, &dxcb::CBPlayer9::DoDrawIndexedPrimitive,
    &dxcb::CBPlayer9::DoSetStreamSource,
    &dxcb::CBPlayer9::DoSetStreamSourceFreq,
    &dxcb::CBPlayer9::DoSetVertexDeclaration, &dxcb::CBPlayer9::DoSetIndices,
    &dxcb::CBPlayer9::DoTestCooperativeLevel,
    &dxcb::CBPlayer9::DoEvictManagedResources, &dxcb::CBPlayer9::DoBeginScene,
    &dxcb::CBPlayer9::DoEndScene, &dxcb::CBPlayer9::DoBeginStateBlock,
    &dxcb::CBPlayer9::DoSetCursorProperties,
    &dxcb::CBPlayer9::DoSetCursorPosition, &dxcb::CBPlayer9::DoSetDialogBoxMode,
    &dxcb::CBPlayer9::DoGetDeviceCaps, &dxcb::CBPlayer9::DoGetDisplayMode,
    &dxcb::CBPlayer9::DoGetCreationParameters,
    &dxcb::CBPlayer9::DoCreateAdditionalSwapChain,
    &dxcb::CBPlayer9::DoGetSwapChain, &dxcb::CBPlayer9::DoReset,
    &dxcb::CBPlayer9::DoPresent, &dxcb::CBPlayer9::DoGetBackBuffer,
    &dxcb::CBPlayer9::DoGetRasterStatus, &dxcb::CBPlayer9::DoSetGammaRamp,
    &dxcb::CBPlayer9::DoGetGammaRamp, &dxcb::CBPlayer9::DoCreateTexture,
    &dxcb::CBPlayer9::DoCreateVolumeTexture,
    &dxcb::CBPlayer9::DoCreateCubeTexture,
    &dxcb::CBPlayer9::DoCreateVertexBuffer,
    &dxcb::CBPlayer9::DoCreateIndexBuffer,
    &dxcb::CBPlayer9::DoCreateRenderTarget,
    &dxcb::CBPlayer9::DoCreateDepthStencilSurface,
    &dxcb::CBPlayer9::DoUpdateSurface, &dxcb::CBPlayer9::DoUpdateTexture,
    &dxcb::CBPlayer9::DoGetRenderTargetData,
    &dxcb::CBPlayer9::DoGetFrontBufferData, &dxcb::CBPlayer9::DoStretchRect,
    &dxcb::CBPlayer9::DoColorFill,
    &dxcb::CBPlayer9::DoCreateOffscreenPlainSurface,
    &dxcb::CBPlayer9::DoSetRenderTarget, &dxcb::CBPlayer9::DoGetRenderTarget,
    &dxcb::CBPlayer9::DoSetDepthStencilSurface,
    &dxcb::CBPlayer9::DoGetDepthStencilSurface, &dxcb::CBPlayer9::DoClear,
    &dxcb::CBPlayer9::DoSetTransform, &dxcb::CBPlayer9::DoGetTransform,
    &dxcb::CBPlayer9::DoMultiplyTransform, &dxcb::CBPlayer9::DoSetViewport,
    &dxcb::CBPlayer9::DoGetViewport, &dxcb::CBPlayer9::DoSetMaterial,
    &dxcb::CBPlayer9::DoGetMaterial, &dxcb::CBPlayer9::DoSetLight,
    &dxcb::CBPlayer9::DoGetLight, &dxcb::CBPlayer9::DoLightEnable,
    &dxcb::CBPlayer9::DoGetLightEnable, &dxcb::CBPlayer9::DoSetClipPlane,
    &dxcb::CBPlayer9::DoGetClipPlane, &dxcb::CBPlayer9::DoSetRenderState,
    &dxcb::CBPlayer9::DoGetRenderState, &dxcb::CBPlayer9::DoCreateStateBlock,
    &dxcb::CBPlayer9::DoEndStateBlock, &dxcb::CBPlayer9::DoSetClipStatus,
    &dxcb::CBPlayer9::DoGetClipStatus, &dxcb::CBPlayer9::DoGetTexture,
    &dxcb::CBPlayer9::DoSetTexture, &dxcb::CBPlayer9::DoGetTextureStageState,
    &dxcb::CBPlayer9::DoSetTextureStageState,
    &dxcb::CBPlayer9::DoGetSamplerState, &dxcb::CBPlayer9::DoSetSamplerState,
    &dxcb::CBPlayer9::DoValidateDevice, &dxcb::CBPlayer9::DoSetPaletteEntries,
    &dxcb::CBPlayer9::DoGetPaletteEntries,
    &dxcb::CBPlayer9::DoSetCurrentTexturePalette,
    &dxcb::CBPlayer9::DoGetCurrentTexturePalette,
    &dxcb::CBPlayer9::DoSetScissorRect, &dxcb::CBPlayer9::DoGetScissorRect,
    &dxcb::CBPlayer9::DoSetSoftwareVertexProcessing,
    &dxcb::CBPlayer9::DoSetNPatchMode, &dxcb::CBPlayer9::DoDrawPrimitiveUP,
    &dxcb::CBPlayer9::DoDrawIndexedPrimitiveUP,
    &dxcb::CBPlayer9::DoProcessVertices,
    &dxcb::CBPlayer9::DoCreateVertexDeclaration,
    &dxcb::CBPlayer9::DoGetVertexDeclaration, &dxcb::CBPlayer9::DoSetFVF,
    &dxcb::CBPlayer9::DoGetFVF, &dxcb::CBPlayer9::DoCreateVertexShader,
    &dxcb::CBPlayer9::DoSetVertexShader, &dxcb::CBPlayer9::DoGetVertexShader,
    &dxcb::CBPlayer9::DoSetVertexShaderConstantF,
    &dxcb::CBPlayer9::DoGetVertexShaderConstantF,
    &dxcb::CBPlayer9::DoSetVertexShaderConstantI,
    &dxcb::CBPlayer9::DoGetVertexShaderConstantI,
    &dxcb::CBPlayer9::DoSetVertexShaderConstantB,
    &dxcb::CBPlayer9::DoGetVertexShaderConstantB,
    &dxcb::CBPlayer9::DoGetStreamSource,
    &dxcb::CBPlayer9::DoGetStreamSourceFreq, &dxcb::CBPlayer9::DoGetIndices,
    &dxcb::CBPlayer9::DoCreatePixelShader, &dxcb::CBPlayer9::DoSetPixelShader,
    &dxcb::CBPlayer9::DoGetPixelShader,
    &dxcb::CBPlayer9::DoSetPixelShaderConstantF,
    &dxcb::CBPlayer9::DoGetPixelShaderConstantF,
    &dxcb::CBPlayer9::DoSetPixelShaderConstantI,
    &dxcb::CBPlayer9::DoGetPixelShaderConstantI,
    &dxcb::CBPlayer9::DoSetPixelShaderConstantB,
    &dxcb::CBPlayer9::DoGetPixelShaderConstantB,
    &dxcb::CBPlayer9::DoDrawRectPatch, &dxcb::CBPlayer9::DoDrawTriPatch,
    &dxcb::CBPlayer9::DoDeletePatch, &dxcb::CBPlayer9::DoCreateQuery,
    // Last supported func, if changed must fix CBPlayer9::Playback logic.
    &dxcb::CBPlayer9::DoGetDirect3D,

    // not implemented
    (dxcb::PlayerMemberPtr)&dxcb::CBPlayer9::GetAvailableTextureMem,
    (dxcb::PlayerMemberPtr)&dxcb::CBPlayer9::GetNumberOfSwapChains,
    (dxcb::PlayerMemberPtr)&dxcb::CBPlayer9::ShowCursor,
    (dxcb::PlayerMemberPtr)&dxcb::CBPlayer9::GetSoftwareVertexProcessing,
    (dxcb::PlayerMemberPtr)&dxcb::CBPlayer9::GetNPatchMode};
}  // namespace

namespace dxcb {

void CBPlayer9::Playback(IDirect3DDevice9 *device, CBMemoryBuffer *buffer) {
  d3d9_device_ = device;
  buffer_ = buffer;

  buffer_->ResetNext();

  using D3d9Command = decltype(D3d9Commands::Null);

  [[maybe_unused]] D3d9Command last_command{D3d9Commands::Null};
  [[maybe_unused]] D3d9Command last_command2{D3d9Commands::Null};
  [[maybe_unused]] size_t commands_count{0};

  bool is_parsing_command{true};
  while (is_parsing_command && buffer_->GetAvailableMemorySize() > 0) {
    const D3d9Command command{buffer_->Gets<D3d9Command>()};

    if (command == D3d9Commands::Null) {
      buffer_->ResetNext();

      is_parsing_command = false;
    } else if (command < D3d9Commands::Null ||
               command > D3d9Commands::GetDirect3D) {
      // this allows you to recover from buffer corruption.
      buffer_->ResetNext();

      is_parsing_command = false;
      // OutputDebugStringA(__FUNCTION__ ": Invalid function token in command
      // buffer, buffer must be corrupt\n"); DXCB_DEBUG_BREAK();
    } else {
      (this->*PlaybackFunctionTable[static_cast<unsigned>(command) -
                                    static_cast<unsigned>(
                                        D3d9Commands::Null)])();

      last_command2 = command;
    }

    last_command = command;
    ++commands_count;
  }

  d3d9_device_ = nullptr;
  buffer_ = nullptr;
}

// The functions below are helpers that use the STDPLAYFUNC macros.;
void CBPlayer9::DoNULLCall() DXCB_VOID_NOT_IMPLEMENTED;
void CBPlayer9::DoQueryInterface() DXCB_VOID_NOT_IMPLEMENTED;

DXCB_ULONG_METHOD_PLAY0(CBPlayer9::DoAddRef, AddRef);
DXCB_ULONG_METHOD_PLAY0(CBPlayer9::DoRelease, Release);

DXCB_STD_METHOD_PLAY3(CBPlayer9::DoDrawPrimitive, DrawPrimitive,
                      D3DPRIMITIVETYPE, UINT, UINT);
DXCB_STD_METHOD_PLAY6(CBPlayer9::DoDrawIndexedPrimitive, DrawIndexedPrimitive,
                      D3DPRIMITIVETYPE, INT, UINT, UINT, UINT, UINT);
DXCB_STD_METHOD_PLAY4(CBPlayer9::DoSetStreamSource, SetStreamSource, UINT,
                      IDirect3DVertexBuffer9 *, UINT, UINT);
DXCB_STD_METHOD_PLAY2(CBPlayer9::DoSetStreamSourceFreq, SetStreamSourceFreq,
                      UINT, UINT);
DXCB_STD_METHOD_PLAY1(CBPlayer9::DoSetVertexDeclaration, SetVertexDeclaration,
                      IDirect3DVertexDeclaration9 *);
DXCB_STD_METHOD_PLAY1(CBPlayer9::DoSetIndices, SetIndices,
                      IDirect3DIndexBuffer9 *);
DXCB_STD_METHOD_PLAY0(CBPlayer9::DoTestCooperativeLevel, TestCooperativeLevel);
DXCB_STD_METHOD_PLAY0(CBPlayer9::DoEvictManagedResources,
                      EvictManagedResources);
DXCB_STD_METHOD_PLAY0(CBPlayer9::DoBeginScene, BeginScene);
DXCB_STD_METHOD_PLAY0(CBPlayer9::DoEndScene, EndScene);
DXCB_STD_METHOD_PLAY0(CBPlayer9::DoBeginStateBlock, BeginStateBlock);
DXCB_STD_METHOD_PLAY3(CBPlayer9::DoSetCursorProperties, SetCursorProperties,
                      UINT, UINT, IDirect3DSurface9 *);
DXCB_STD_VOID_METHOD_PLAY3(CBPlayer9::DoSetCursorPosition, SetCursorPosition,
                           int, int, DWORD)
DXCB_STD_METHOD_PLAY1(CBPlayer9::DoSetDialogBoxMode, SetDialogBoxMode, BOOL);
DXCB_STD_METHOD_PLAY1(CBPlayer9::DoReset, Reset, D3DPRESENT_PARAMETERS *);
DXCB_STD_METHOD_PLAY4(CBPlayer9::DoPresent, Present, CONST RECT *, CONST RECT *,
                      HWND, CONST RGNDATA *);
DXCB_STD_VOID_METHOD_PLAY3(CBPlayer9::DoSetGammaRamp, SetGammaRamp, UINT, DWORD,
                           CONST D3DGAMMARAMP *)
DXCB_STD_METHOD_PLAY4(CBPlayer9::DoUpdateSurface, UpdateSurface,
                      IDirect3DSurface9 *, CONST RECT *, IDirect3DSurface9 *,
                      CONST POINT *);
DXCB_STD_METHOD_PLAY2(CBPlayer9::DoUpdateTexture, UpdateTexture,
                      IDirect3DBaseTexture9 *, IDirect3DBaseTexture9 *);
DXCB_STD_METHOD_PLAY5(CBPlayer9::DoStretchRect, StretchRect,
                      IDirect3DSurface9 *, CONST RECT *, IDirect3DSurface9 *,
                      CONST RECT *, D3DTEXTUREFILTERTYPE);
DXCB_STD_METHOD_PLAY3(CBPlayer9::DoColorFill, ColorFill, IDirect3DSurface9 *,
                      CONST RECT *, D3DCOLOR);
DXCB_STD_METHOD_PLAY2(CBPlayer9::DoSetRenderTarget, SetRenderTarget, DWORD,
                      IDirect3DSurface9 *);
DXCB_STD_METHOD_PLAY1(CBPlayer9::DoSetDepthStencilSurface,
                      SetDepthStencilSurface, IDirect3DSurface9 *);
DXCB_STD_METHOD_PLAY6(CBPlayer9::DoClear, Clear, DWORD, CONST D3DRECT *, DWORD,
                      D3DCOLOR, float, DWORD);
DXCB_STD_METHOD_PLAY2(CBPlayer9::DoSetTransform, SetTransform,
                      D3DTRANSFORMSTATETYPE, CONST D3DMATRIX *);
DXCB_STD_METHOD_PLAY2(CBPlayer9::DoMultiplyTransform, MultiplyTransform,
                      D3DTRANSFORMSTATETYPE, CONST D3DMATRIX *);
DXCB_STD_METHOD_PLAY1(CBPlayer9::DoSetViewport, SetViewport,
                      CONST D3DVIEWPORT9 *);
DXCB_STD_METHOD_PLAY1(CBPlayer9::DoSetMaterial, SetMaterial,
                      CONST D3DMATERIAL9 *);
DXCB_STD_METHOD_PLAY2(CBPlayer9::DoSetLight, SetLight, DWORD,
                      CONST D3DLIGHT9 *);
DXCB_STD_METHOD_PLAY2(CBPlayer9::DoLightEnable, LightEnable, DWORD, BOOL);
DXCB_STD_METHOD_PLAY2(CBPlayer9::DoSetClipPlane, SetClipPlane, DWORD,
                      CONST float *);
DXCB_STD_METHOD_PLAY2(CBPlayer9::DoSetRenderState, SetRenderState,
                      D3DRENDERSTATETYPE, DWORD);
DXCB_STD_METHOD_PLAY1(CBPlayer9::DoEndStateBlock, EndStateBlock,
                      IDirect3DStateBlock9 **);
DXCB_STD_METHOD_PLAY1(CBPlayer9::DoSetClipStatus, SetClipStatus,
                      CONST D3DCLIPSTATUS9 *);
DXCB_STD_METHOD_PLAY2(CBPlayer9::DoSetTexture, SetTexture, DWORD,
                      IDirect3DBaseTexture9 *);
DXCB_STD_METHOD_PLAY3(CBPlayer9::DoSetTextureStageState, SetTextureStageState,
                      DWORD, D3DTEXTURESTAGESTATETYPE, DWORD);
DXCB_STD_METHOD_PLAY3(CBPlayer9::DoSetSamplerState, SetSamplerState, DWORD,
                      D3DSAMPLERSTATETYPE, DWORD);
DXCB_STD_METHOD_PLAY1(CBPlayer9::DoValidateDevice, ValidateDevice, DWORD *);
DXCB_STD_METHOD_PLAY2(CBPlayer9::DoSetPaletteEntries, SetPaletteEntries, UINT,
                      CONST PALETTEENTRY *);
DXCB_STD_METHOD_PLAY1(CBPlayer9::DoSetCurrentTexturePalette,
                      SetCurrentTexturePalette, UINT);
DXCB_STD_METHOD_PLAY1(CBPlayer9::DoSetScissorRect, SetScissorRect,
                      CONST RECT *);
DXCB_STD_METHOD_PLAY1(CBPlayer9::DoSetSoftwareVertexProcessing,
                      SetSoftwareVertexProcessing, BOOL);
DXCB_STD_METHOD_PLAY1(CBPlayer9::DoSetNPatchMode, SetNPatchMode, float);
DXCB_STD_METHOD_PLAY4(CBPlayer9::DoDrawPrimitiveUP, DrawPrimitiveUP,
                      D3DPRIMITIVETYPE, UINT, CONST void *, UINT);
DXCB_STD_METHOD_PLAY8(CBPlayer9::DoDrawIndexedPrimitiveUP,
                      DrawIndexedPrimitiveUP, D3DPRIMITIVETYPE, UINT, UINT,
                      UINT, CONST void *, D3DFORMAT, CONST void *, UINT);
DXCB_STD_METHOD_PLAY6(CBPlayer9::DoProcessVertices, ProcessVertices, UINT, UINT,
                      UINT, IDirect3DVertexBuffer9 *,
                      IDirect3DVertexDeclaration9 *, DWORD);
DXCB_STD_METHOD_PLAY1(CBPlayer9::DoSetFVF, SetFVF, DWORD);
DXCB_STD_METHOD_PLAY1(CBPlayer9::DoSetVertexShader, SetVertexShader,
                      IDirect3DVertexShader9 *);
DXCB_STD_METHOD_PLAY1(CBPlayer9::DoSetPixelShader, SetPixelShader,
                      IDirect3DPixelShader9 *);
DXCB_STD_METHOD_PLAY3(CBPlayer9::DoDrawRectPatch, DrawRectPatch, UINT,
                      CONST float *, CONST D3DRECTPATCH_INFO *);
DXCB_STD_METHOD_PLAY3(CBPlayer9::DoDrawTriPatch, DrawTriPatch, UINT,
                      CONST float *, CONST D3DTRIPATCH_INFO *);
DXCB_STD_METHOD_PLAY1(CBPlayer9::DoDeletePatch, DeletePatch, UINT);
DXCB_STD_METHOD_PLAY_CONSTS(CBPlayer9::DoSetVertexShaderConstantF,
                            SetVertexShaderConstantF, UINT, CONST float *, UINT,
                            float)
DXCB_STD_METHOD_PLAY_CONSTS(CBPlayer9::DoSetVertexShaderConstantI,
                            SetVertexShaderConstantI, UINT, CONST int *, UINT,
                            int)
DXCB_STD_METHOD_PLAY_CONSTS(CBPlayer9::DoSetVertexShaderConstantB,
                            SetVertexShaderConstantB, UINT, CONST BOOL *, UINT,
                            BOOL)
DXCB_STD_METHOD_PLAY_CONSTS(CBPlayer9::DoSetPixelShaderConstantF,
                            SetPixelShaderConstantF, UINT, CONST float *, UINT,
                            float)
DXCB_STD_METHOD_PLAY_CONSTS(CBPlayer9::DoSetPixelShaderConstantI,
                            SetPixelShaderConstantI, UINT, CONST int *, UINT,
                            int)
DXCB_STD_METHOD_PLAY_CONSTS(CBPlayer9::DoSetPixelShaderConstantB,
                            SetPixelShaderConstantB, UINT, CONST BOOL *, UINT,
                            BOOL)

}  // namespace dxcb

#endif  // DXCB_INVOKE_PREPROCESSOR
