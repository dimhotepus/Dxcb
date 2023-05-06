// Open source.
// See Vincent Scheib rant at
// http://beautifulpixels.blogspot.com/2008/07/parallel-rendering-with-directx-command.html

#ifndef DXCB_CBPLAYER9_H_
#define DXCB_CBPLAYER9_H_

#ifndef DXCB_INVOKE_PREPROCESSOR
#include "CBMemoryBuffer.h"
#include "PREPROCESSED_CBPlayer9.h"
#else

#include "CBMacros.h"

namespace dxcb {

class CBPlayer9 {
 public:
  CBPlayer9() : buffer_{nullptr}, d3d9_device_{nullptr} {}

  CBPlayer9(CBPlayer9&) = delete;
  CBPlayer9(CBPlayer9&&) = delete;
  CBPlayer9& operator=(CBPlayer9&) = delete;
  CBPlayer9& operator=(CBPlayer9&&) = delete;

  void Playback(IDirect3DDevice9* device, CBMemoryBuffer* buffer);

  void DoNULLCall();
  void DoQueryInterface();
  void DoAddRef();
  void DoRelease();

  /*** Implemented IDirect3DDevice9 methods ***/
  /* Note that it is assumed that input values will be valid a record time. */
  /* Also there is no mechnism to retain returned values during playback     */

  void DoDrawPrimitive();
  void DoDrawIndexedPrimitive();
  void DoSetStreamSource();
  void DoSetStreamSourceFreq();
  void DoSetVertexDeclaration();
  void DoSetIndices();
  void DoTestCooperativeLevel();
  void DoEvictManagedResources();
  void DoBeginScene();
  void DoEndScene();
  void DoBeginStateBlock();
  void DoSetCursorProperties();
  void DoSetCursorPosition();
  void DoSetDialogBoxMode();
  void DoReset();
  void DoPresent();
  void DoSetGammaRamp();
  void DoUpdateSurface();
  void DoUpdateTexture();
  void DoStretchRect();
  void DoColorFill();
  void DoSetRenderTarget();
  void DoSetDepthStencilSurface();
  void DoClear();
  void DoSetTransform();
  void DoMultiplyTransform();
  void DoSetViewport();
  void DoSetMaterial();
  void DoLightEnable();
  void DoSetClipPlane();
  void DoSetRenderState();
  void DoEndStateBlock();
  void DoSetClipStatus();
  void DoSetTexture();
  void DoSetTextureStageState();
  void DoSetSamplerState();
  void DoValidateDevice();
  void DoSetPaletteEntries();
  void DoSetCurrentTexturePalette();
  void DoSetScissorRect();
  void DoSetSoftwareVertexProcessing();
  void DoSetNPatchMode();
  void DoDrawPrimitiveUP();
  void DoDrawIndexedPrimitiveUP();
  void DoProcessVertices();
  void DoSetFVF();
  void DoSetVertexShader();
  void DoSetPixelShader();
  void DoDrawRectPatch();
  void DoDrawTriPatch();
  void DoDeletePatch();
  void DoSetLight();
  void DoSetVertexShaderConstantF();
  void DoSetVertexShaderConstantI();
  void DoSetVertexShaderConstantB();
  void DoSetPixelShaderConstantF();
  void DoSetPixelShaderConstantI();
  void DoSetPixelShaderConstantB();

  /*** IDirect3DDevice methods that cannot be recorded which throw errors */  //

  // create methods should not be recorded.
  void DoCreateOffscreenPlainSurface() DXCB_VOID_NOT_IMPLEMENTED;
  void DoCreateStateBlock() DXCB_VOID_NOT_IMPLEMENTED;
  void DoCreateAdditionalSwapChain() DXCB_VOID_NOT_IMPLEMENTED;
  void DoCreateVertexDeclaration() DXCB_VOID_NOT_IMPLEMENTED;
  void DoCreateVertexShader() DXCB_VOID_NOT_IMPLEMENTED;
  void DoCreateQuery() DXCB_VOID_NOT_IMPLEMENTED;
  void DoCreateTexture() DXCB_VOID_NOT_IMPLEMENTED;
  void DoCreateVolumeTexture() DXCB_VOID_NOT_IMPLEMENTED;
  void DoCreateCubeTexture() DXCB_VOID_NOT_IMPLEMENTED;
  void DoCreateVertexBuffer() DXCB_VOID_NOT_IMPLEMENTED;
  void DoCreateIndexBuffer() DXCB_VOID_NOT_IMPLEMENTED;
  void DoCreateRenderTarget() DXCB_VOID_NOT_IMPLEMENTED;
  void DoCreateDepthStencilSurface() DXCB_VOID_NOT_IMPLEMENTED;

  // get methods should not be recorded.
  void DoGetTextureStageState() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetSwapChain() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetRenderTargetData() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetGammaRamp() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetFrontBufferData() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetBackBuffer() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetRasterStatus() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetRenderTarget() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetDeviceCaps() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetDisplayMode() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetCreationParameters() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetDepthStencilSurface() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetTransform() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetViewport() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetMaterial() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetLight() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetLightEnable() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetClipPlane() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetRenderState() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetClipStatus() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetTexture() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetSamplerState() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetPaletteEntries() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetCurrentTexturePalette() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetScissorRect() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetVertexDeclaration() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetFVF() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetVertexShader() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetStreamSource() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetStreamSourceFreq() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetIndices() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetDirect3D() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetVertexShaderConstantF() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetVertexShaderConstantI() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetVertexShaderConstantB() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetPixelShaderConstantF() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetPixelShaderConstantI() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetPixelShaderConstantB() DXCB_VOID_NOT_IMPLEMENTED;
  void DoGetPixelShader() DXCB_VOID_NOT_IMPLEMENTED;
  void DoCreatePixelShader() DXCB_VOID_NOT_IMPLEMENTED;

  /*** IDirect3DDevice methods that cannot be recorded which throw errors */  //

  STDMETHOD_(UINT, GetAvailableTextureMem)(THIS) DXCB_UINT_NOT_IMPLEMENTED;
  STDMETHOD_(UINT, GetNumberOfSwapChains)(THIS) DXCB_UINT_NOT_IMPLEMENTED;
  STDMETHOD_(BOOL, ShowCursor)
  ([[maybe_unused]] BOOL bShow) DXCB_BOOL_NOT_IMPLEMENTED;
  STDMETHOD_(BOOL, GetSoftwareVertexProcessing)(THIS) DXCB_BOOL_NOT_IMPLEMENTED;
  STDMETHOD_(float, GetNPatchMode)(THIS) DXCB_FLOAT_NOT_IMPLEMENTED;
  STDMETHOD(GetVertexShaderConstantF)
  ([[maybe_unused]] UINT StartRegister, [[maybe_unused]] float* pConstantData,
   [[maybe_unused]] UINT Vector4fCount) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetVertexShaderConstantI)
  ([[maybe_unused]] UINT StartRegister, [[maybe_unused]] int* pConstantData,
   [[maybe_unused]] UINT Vector4iCount) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetVertexShaderConstantB)
  ([[maybe_unused]] UINT StartRegister, [[maybe_unused]] BOOL* pConstantData,
   [[maybe_unused]] UINT BoolCount) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetPixelShaderConstantF)
  ([[maybe_unused]] UINT StartRegister, [[maybe_unused]] float* pConstantData,
   [[maybe_unused]] UINT Vector4fCount) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetPixelShaderConstantI)
  ([[maybe_unused]] UINT StartRegister, [[maybe_unused]] int* pConstantData,
   [[maybe_unused]] UINT Vector4iCount) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetPixelShaderConstantB)
  ([[maybe_unused]] UINT StartRegister, [[maybe_unused]] BOOL* pConstantData,
   [[maybe_unused]] UINT BoolCount) DXCB_D3DERR_NOT_IMPLEMENTED;

 private:
  CBMemoryBuffer* buffer_;
  IDirect3DDevice9* d3d9_device_;
};

using PlayerMemberPtr = void (CBPlayer9::*)();

}  // namespace dxcb

#endif  // DXCB_INVOKE_PREPROCESSOR

#endif  // DXCB_CBPLAYER9_H_