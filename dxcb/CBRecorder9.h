// Open source.
// See Vincent Scheib rant at
// http://beautifulpixels.blogspot.com/2008/07/parallel-rendering-with-directx-command.html

#pragma once

#ifndef CBD3D_PREPROCESSING

#include "CBMemoryBuffer.h"
#include "PREPROCESSED_CBRecorder9.h"

#else  // CBD3D_PREPROCESSING

#include "CBMacros.h"

namespace dxcb {

class CBRecorder9 : public IDirect3DDevice9 {
 public:
  CBRecorder9() : buffer_{nullptr} {}

  CBRecorder9(CBRecorder9&) = delete;
  CBRecorder9(CBRecorder9&&) = delete;
  CBRecorder9& operator=(CBRecorder9&) = delete;
  CBRecorder9& operator=(CBRecorder9&&) = delete;

  void SetCommandBuffer(CBMemoryBuffer* buffer) { buffer_ = buffer; }

  HRESULT BeginCommandBuffer() {
    buffer_->ResetNext();
    return D3D_OK;
  }

  HRESULT EndCommandBuffer() {
    if (buffer_->CheckAvailableMemorySize(1)) {
      buffer_->Put(D3d9Commands::Null);
      return D3D_OK;
    }

    return E_OUTOFMEMORY;
  }

  /*** IUnknown methods ***/
  STDMETHOD(QueryInterface)
  (REFIID riid, void** ppvObj) DXCB_D3DERR_NOT_IMPLEMENTED;
  DXCB_STD_RETURN_METHOD_RECORD0(ULONG, 1, AddRef)
  DXCB_STD_RETURN_METHOD_RECORD0(ULONG, 1, Release)

  /*** Implemented IDirect3DDevice9 methods ***/
  /* Note that it is assumed that input values will be valid a record time. */
  /* Also there is no mechnism to retain returned values during playback     */

  DXCB_STD_METHOD_RECORD3(DrawPrimitive, D3DPRIMITIVETYPE, PrimitiveType, UINT,
                          StartVertex, UINT, PrimitiveCount)
  DXCB_STD_METHOD_RECORD6(DrawIndexedPrimitive, D3DPRIMITIVETYPE, PrimitiveType,
                          INT, BaseVertexIndex, UINT, MinVertexIndex, UINT,
                          NumVertices, UINT, startIndex, UINT, primCount)
  DXCB_STD_METHOD_RECORD4(SetStreamSource, UINT, StreamNumber,
                          IDirect3DVertexBuffer9*, pStreamData, UINT,
                          OffsetInBytes, UINT, Stride);
  DXCB_STD_METHOD_RECORD2(SetStreamSourceFreq, UINT, StreamNumber, UINT,
                          Divider);
  DXCB_STD_METHOD_RECORD1(SetVertexDeclaration, IDirect3DVertexDeclaration9*,
                          pDecl)
  DXCB_STD_METHOD_RECORD1(SetIndices, IDirect3DIndexBuffer9*, pIndexData)
  DXCB_STD_METHOD_RECORD0(TestCooperativeLevel)
  DXCB_STD_METHOD_RECORD0(EvictManagedResources)
  DXCB_STD_METHOD_RECORD0(BeginScene)
  DXCB_STD_METHOD_RECORD0(EndScene)
  DXCB_STD_METHOD_RECORD0(BeginStateBlock)
  DXCB_STD_METHOD_RECORD3(SetCursorProperties, UINT, XHotSpot, UINT, YHotSpot,
                          IDirect3DSurface9*, pCursorBitmap)
  DXCB_STD_METHOD_RECORD1(SetDialogBoxMode, BOOL, bEnableDialogs)
  DXCB_STD_METHOD_RECORD1(Reset, D3DPRESENT_PARAMETERS*,
                          pPresentationParameters)
  DXCB_STD_METHOD_RECORD4(Present, CONST RECT*, pSourceRect, CONST RECT*,
                          pDestRect, HWND, hDestWindowOverride, CONST RGNDATA*,
                          pDirtyRegion)
  DXCB_STD_METHOD_RECORD4(UpdateSurface, IDirect3DSurface9*, pSourceSurface,
                          CONST RECT*, pSourceRect, IDirect3DSurface9*,
                          pDestinationSurface, CONST POINT*, pDestPoint)
  DXCB_STD_METHOD_RECORD2(UpdateTexture, IDirect3DBaseTexture9*, pSourceTexture,
                          IDirect3DBaseTexture9*, pDestinationTexture)
  DXCB_STD_METHOD_RECORD5(StretchRect, IDirect3DSurface9*, pSourceSurface,
                          CONST RECT*, pSourceRect, IDirect3DSurface9*,
                          pDestSurface, CONST RECT*, pDestRect,
                          D3DTEXTUREFILTERTYPE, Filter)
  DXCB_STD_METHOD_RECORD3(ColorFill, IDirect3DSurface9*, pSurface, CONST RECT*,
                          pRect, D3DCOLOR, color)
  DXCB_STD_METHOD_RECORD2(SetRenderTarget, DWORD, RenderTargetIndex,
                          IDirect3DSurface9*, pRenderTarget)
  DXCB_STD_METHOD_RECORD1(SetDepthStencilSurface, IDirect3DSurface9*,
                          pNewZStencil)
  DXCB_STD_METHOD_RECORD6(Clear, DWORD, Count, CONST D3DRECT*, pRects, DWORD,
                          Flags, D3DCOLOR, Color, float, Z, DWORD, Stencil)
  DXCB_STD_METHOD_RECORD2(SetTransform, D3DTRANSFORMSTATETYPE, State,
                          CONST D3DMATRIX*, pMatrix)
  DXCB_STD_METHOD_RECORD2(MultiplyTransform, D3DTRANSFORMSTATETYPE, type,
                          CONST D3DMATRIX*, pMatrix)
  DXCB_STD_METHOD_RECORD1(SetViewport, CONST D3DVIEWPORT9*, pViewport)
  DXCB_STD_METHOD_RECORD1(SetMaterial, CONST D3DMATERIAL9*, pMaterial)
  DXCB_STD_METHOD_RECORD2(SetLight, DWORD, Index, CONST D3DLIGHT9*, pLight)
  DXCB_STD_METHOD_RECORD2(LightEnable, DWORD, Index, BOOL, Enable)
  DXCB_STD_METHOD_RECORD2(SetClipPlane, DWORD, Index, CONST float*, pPlane)
  DXCB_STD_METHOD_RECORD2(SetRenderState, D3DRENDERSTATETYPE, State, DWORD,
                          Value)
  DXCB_STD_METHOD_RECORD1(EndStateBlock, IDirect3DStateBlock9**, ppSB)
  DXCB_STD_METHOD_RECORD1(SetClipStatus, CONST D3DCLIPSTATUS9*, pClipStatus)
  DXCB_STD_METHOD_RECORD2(SetTexture, DWORD, Stage, IDirect3DBaseTexture9*,
                          pTexture)
  DXCB_STD_METHOD_RECORD3(SetTextureStageState, DWORD, Stage,
                          D3DTEXTURESTAGESTATETYPE, Type, DWORD, Value)
  DXCB_STD_METHOD_RECORD3(SetSamplerState, DWORD, Sampler, D3DSAMPLERSTATETYPE,
                          Type, DWORD, Value)
  DXCB_STD_METHOD_RECORD1(ValidateDevice, DWORD*, pNumPasses)
  DXCB_STD_METHOD_RECORD2(SetPaletteEntries, UINT, PaletteNumber,
                          CONST PALETTEENTRY*, pEntries)
  DXCB_STD_METHOD_RECORD1(SetCurrentTexturePalette, UINT, PaletteNumber)
  DXCB_STD_METHOD_RECORD1(SetScissorRect, CONST RECT*, pRect)
  DXCB_STD_METHOD_RECORD1(SetSoftwareVertexProcessing, BOOL, bSoftware)
  DXCB_STD_METHOD_RECORD1(SetNPatchMode, float, nSegments)
  DXCB_STD_METHOD_RECORD4(DrawPrimitiveUP, D3DPRIMITIVETYPE, PrimitiveType,
                          UINT, PrimitiveCount, CONST void*,
                          pVertexStreamZeroData, UINT, VertexStreamZeroStride)
  DXCB_STD_METHOD_RECORD8(DrawIndexedPrimitiveUP, D3DPRIMITIVETYPE,
                          PrimitiveType, UINT, MinVertexIndex, UINT,
                          NumVertices, UINT, PrimitiveCount, CONST void*,
                          pIndexData, D3DFORMAT, IndexDataFormat, CONST void*,
                          pVertexStreamZeroData, UINT, VertexStreamZeroStride)
  DXCB_STD_METHOD_RECORD6(ProcessVertices, UINT, SrcStartIndex, UINT, DestIndex,
                          UINT, VertexCount, IDirect3DVertexBuffer9*,
                          pDestBuffer, IDirect3DVertexDeclaration9*,
                          pVertexDecl, DWORD, Flags)
  DXCB_STD_METHOD_RECORD1(SetFVF, DWORD, FVF)
  DXCB_STD_METHOD_RECORD1(SetVertexShader, IDirect3DVertexShader9*, pShader)
  DXCB_STD_METHOD_RECORD1(SetPixelShader, IDirect3DPixelShader9*, pShader)
  DXCB_STD_METHOD_RECORD3(DrawRectPatch, UINT, Handle, CONST float*, pNumSegs,
                          CONST D3DRECTPATCH_INFO*, pRectPatchInfo)
  DXCB_STD_METHOD_RECORD3(DrawTriPatch, UINT, Handle, CONST float*, pNumSegs,
                          CONST D3DTRIPATCH_INFO*, pTriPatchInfo)
  DXCB_STD_METHOD_RECORD1(DeletePatch, UINT, Handle)
  DXCB_STD_VOID_METHOD_RECORD3(SetGammaRamp, UINT, iSwapChain, DWORD, Flags,
                               CONST D3DGAMMARAMP*, pRamp)
  DXCB_STD_VOID_METHOD_RECORD3(SetCursorPosition, int, X, int, Y, DWORD, Flags)

  /*** IDirect3DDevice methods that cannot be recorded which throw errors */  //

  STDMETHOD_(BOOL, ShowCursor)(BOOL bShow) DXCB_BOOL_NOT_IMPLEMENTED;
  STDMETHOD_(UINT, GetAvailableTextureMem)(THIS) DXCB_UINT_NOT_IMPLEMENTED;
  STDMETHOD_(UINT, GetNumberOfSwapChains)(THIS) DXCB_UINT_NOT_IMPLEMENTED;
  STDMETHOD_(BOOL, GetSoftwareVertexProcessing)(THIS) DXCB_BOOL_NOT_IMPLEMENTED;
  STDMETHOD_(float, GetNPatchMode)(THIS) DXCB_FLOAT_NOT_IMPLEMENTED;
  STDMETHOD_(void, GetGammaRamp)
  (UINT iSwapChain, D3DGAMMARAMP* pRamp) DXCB_VOID_NOT_IMPLEMENTED;
  STDMETHOD(GetSwapChain)
  (UINT iSwapChain,
   IDirect3DSwapChain9** pSwapChain) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetDeviceCaps)(LPD3DCAPS9 pCaps) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetDisplayMode)
  (UINT iSwapChain, D3DDISPLAYMODE* pMode) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetCreationParameters)
  (D3DDEVICE_CREATION_PARAMETERS* pParameters) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetBackBuffer)
  (UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type,
   IDirect3DSurface9** ppBackBuffer) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetRasterStatus)
  (UINT iSwapChain,
   D3DRASTER_STATUS* pRasterStatus) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetPaletteEntries)
  (UINT PaletteNumber, PALETTEENTRY* pEntries) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetRenderTargetData)
  (IDirect3DSurface9* pRenderTarget,
   IDirect3DSurface9* pDestSurface) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetFrontBufferData)
  (UINT iSwapChain,
   IDirect3DSurface9* pDestSurface) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetRenderTarget)
  (DWORD RenderTargetIndex,
   IDirect3DSurface9** ppRenderTarget) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetDepthStencilSurface)
  (IDirect3DSurface9** ppZStencilSurface) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetTransform)
  (D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetViewport)(D3DVIEWPORT9* pViewport) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetMaterial)(D3DMATERIAL9* pMaterial) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetLightEnable)
  (DWORD Index, BOOL* pEnable) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetLight)
  (DWORD Index, D3DLIGHT9* pLight) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetClipPlane)
  (DWORD Index, float* pPlane) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetRenderState)
  (D3DRENDERSTATETYPE State, DWORD* pValue) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetClipStatus)
  (D3DCLIPSTATUS9* pClipStatus) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetTexture)
  (DWORD Stage, IDirect3DBaseTexture9** ppTexture) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetTextureStageState)
  (DWORD Stage, D3DTEXTURESTAGESTATETYPE Type,
   DWORD* pValue) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetSamplerState)
  (DWORD Sampler, D3DSAMPLERSTATETYPE Type,
   DWORD* pValue) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetCurrentTexturePalette)
  (UINT* PaletteNumber) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetScissorRect)(RECT* pRect) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetVertexDeclaration)
  (IDirect3DVertexDeclaration9** ppDecl) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetFVF)(DWORD* pFVF) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetPixelShader)
  (IDirect3DPixelShader9** ppShader) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetVertexShader)
  (IDirect3DVertexShader9** ppShader) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetStreamSource)
  (UINT StreamNumber, IDirect3DVertexBuffer9** ppStreamData,
   LPUINT OffsetInBytes, LPUINT pStride) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetStreamSourceFreq)
  (UINT StreamNumber, LPUINT Divider) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetIndices)
  (IDirect3DIndexBuffer9** ppIndexData) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(CreateQuery)
  (D3DQUERYTYPE Type, IDirect3DQuery9** ppQuery) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetDirect3D)(IDirect3D9** ppD3D9) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetVertexShaderConstantF)
  (UINT StartRegister, float* pConstantData,
   UINT Vector4fCount) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetVertexShaderConstantI)
  (UINT StartRegister, int* pConstantData,
   UINT Vector4iCount) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetVertexShaderConstantB)
  (UINT StartRegister, BOOL* pConstantData,
   UINT BoolCount) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetPixelShaderConstantF)
  (UINT StartRegister, float* pConstantData,
   UINT Vector4fCount) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetPixelShaderConstantI)
  (UINT StartRegister, int* pConstantData,
   UINT Vector4iCount) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(GetPixelShaderConstantB)
  (UINT StartRegister, BOOL* pConstantData,
   UINT BoolCount) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(CreateAdditionalSwapChain)
  (D3DPRESENT_PARAMETERS* pPresentationParameters,
   IDirect3DSwapChain9** pSwapChain) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(CreateTexture)
  (UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format,
   D3DPOOL Pool, IDirect3DTexture9** ppTexture,
   HANDLE* pSharedHandle) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(CreateVolumeTexture)
  (UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage,
   D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9** ppVolumeTexture,
   HANDLE* pSharedHandle) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(CreateCubeTexture)
  (UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool,
   IDirect3DCubeTexture9** ppCubeTexture,
   HANDLE* pSharedHandle) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(CreateVertexBuffer)
  (UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool,
   IDirect3DVertexBuffer9** ppVertexBuffer,
   HANDLE* pSharedHandle) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(CreateIndexBuffer)
  (UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool,
   IDirect3DIndexBuffer9** ppIndexBuffer,
   HANDLE* pSharedHandle) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(CreateRenderTarget)
  (UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample,
   DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9** ppSurface,
   HANDLE* pSharedHandle) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(CreateDepthStencilSurface)
  (UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample,
   DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9** ppSurface,
   HANDLE* pSharedHandle) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(CreateOffscreenPlainSurface)
  (UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool,
   IDirect3DSurface9** ppSurface,
   HANDLE* pSharedHandle) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(CreateStateBlock)
  (D3DSTATEBLOCKTYPE Type,
   IDirect3DStateBlock9** ppSB) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(CreateVertexDeclaration)
  (CONST D3DVERTEXELEMENT9* pVertexElements,
   IDirect3DVertexDeclaration9** ppDecl) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(CreateVertexShader)
  (CONST DWORD* pFunction,
   IDirect3DVertexShader9** ppShader) DXCB_D3DERR_NOT_IMPLEMENTED;
  STDMETHOD(CreatePixelShader)
  (CONST DWORD* pFunction,
   IDirect3DPixelShader9** ppShader) DXCB_D3DERR_NOT_IMPLEMENTED;

  /***IDirect3DDevice9 methods that write variable sized objects***/

  DXCB_STD_METHOD_RECORD_CONSTS(SetVertexShaderConstantF, UINT, StartRegister,
                                CONST float*, pConstantData, UINT,
                                Vector4fCount, float)
  DXCB_STD_METHOD_RECORD_CONSTS(SetVertexShaderConstantI, UINT, StartRegister,
                                CONST int*, pConstantData, UINT, Vector4iCount,
                                int)
  DXCB_STD_METHOD_RECORD_CONSTS(SetVertexShaderConstantB, UINT, StartRegister,
                                CONST BOOL*, pConstantData, UINT, BoolCount,
                                BOOL)
  DXCB_STD_METHOD_RECORD_CONSTS(SetPixelShaderConstantF, UINT, StartRegister,
                                CONST float*, pConstantData, UINT,
                                Vector4fCount, float)
  DXCB_STD_METHOD_RECORD_CONSTS(SetPixelShaderConstantI, UINT, StartRegister,
                                CONST int*, pConstantData, UINT, Vector4iCount,
                                int)
  DXCB_STD_METHOD_RECORD_CONSTS(SetPixelShaderConstantB, UINT, StartRegister,
                                CONST BOOL*, pConstantData, UINT, BoolCount,
                                BOOL)

 protected:
  CBMemoryBuffer* buffer_;
};

}  // namespace dxcb

#endif  // CBD3D_PREPROCESSING is defined