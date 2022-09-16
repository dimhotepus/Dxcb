// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 1996-2008 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Chapel Hill, North Carolina 27517
// http://www.emergent.net

#ifndef _CBPLAYBACK_H_
#define _CBPLAYBACK_H_

#ifndef CBD3D_PREPROCESSING
#include "CBMemoryBuffer.h"
#include "PREPROCESSED_CBPlayer9.h"
#else

#include "CBMacros.h"

class CBPlayer9
{
public:
    CBPlayer9();
    void Playback(IDirect3DDevice9 *pDevice, CBMemoryBuffer* pCB);
    static DWORD PlaybackNumberArgs[215];

    void DoNULLCall();
    void DoQueryInterface(); 
    void DoAddRef();
    void DoRelease();

    /*** Implemnted IDirect3DDevice9 methods ***/
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
    void DoSetGammaRamp ();
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
    
    /*** IDirect3DDevice methods that cannot be recorded which throw errors *///

    //create methods should not be recorded.
    void DoCreateOffscreenPlainSurface() CBD3D_VOID_NOTIMPLIMENTED;
    void DoCreateStateBlock() CBD3D_VOID_NOTIMPLIMENTED;
    void DoCreateAdditionalSwapChain() CBD3D_VOID_NOTIMPLIMENTED;
    void DoCreateVertexDeclaration() CBD3D_VOID_NOTIMPLIMENTED;
    void DoCreateVertexShader() CBD3D_VOID_NOTIMPLIMENTED;
    void DoCreateQuery() CBD3D_VOID_NOTIMPLIMENTED;
    void DoCreateTexture() CBD3D_VOID_NOTIMPLIMENTED;
    void DoCreateVolumeTexture() CBD3D_VOID_NOTIMPLIMENTED;
    void DoCreateCubeTexture() CBD3D_VOID_NOTIMPLIMENTED;
    void DoCreateVertexBuffer() CBD3D_VOID_NOTIMPLIMENTED;
    void DoCreateIndexBuffer() CBD3D_VOID_NOTIMPLIMENTED;
    void DoCreateRenderTarget() CBD3D_VOID_NOTIMPLIMENTED;
    void DoCreateDepthStencilSurface() CBD3D_VOID_NOTIMPLIMENTED;

    //get methods should not be recorded.
    void DoGetTextureStageState() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetSwapChain() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetRenderTargetData() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetGammaRamp() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetFrontBufferData() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetBackBuffer() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetRasterStatus() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetRenderTarget() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetDeviceCaps() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetDisplayMode() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetCreationParameters() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetDepthStencilSurface() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetTransform() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetViewport() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetMaterial() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetLight() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetLightEnable() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetClipPlane() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetRenderState() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetClipStatus() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetTexture() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetSamplerState() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetPaletteEntries() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetCurrentTexturePalette() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetScissorRect() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetVertexDeclaration() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetFVF() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetVertexShader() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetStreamSource() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetStreamSourceFreq() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetIndices() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetDirect3D() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetVertexShaderConstantF() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetVertexShaderConstantI() CBD3D_VOID_NOTIMPLIMENTED; 
    void DoGetVertexShaderConstantB() CBD3D_VOID_NOTIMPLIMENTED;
    void DoGetPixelShaderConstantF() CBD3D_VOID_NOTIMPLIMENTED; 
    void DoGetPixelShaderConstantI() CBD3D_VOID_NOTIMPLIMENTED; 
    void DoGetPixelShaderConstantB() CBD3D_VOID_NOTIMPLIMENTED; 
    void DoGetPixelShader() CBD3D_VOID_NOTIMPLIMENTED;
    void DoCreatePixelShader() CBD3D_VOID_NOTIMPLIMENTED;


    /*** IDirect3DDevice methods that cannot be recorded which throw errors *///

    STDMETHOD_(UINT, GetAvailableTextureMem)(THIS) CBD3D_UINT_NOTIMPLIMENTED;
    STDMETHOD_(UINT, GetNumberOfSwapChains)(THIS) CBD3D_UINT_NOTIMPLIMENTED;
    STDMETHOD_(BOOL, ShowCursor)( BOOL bShow) CBD3D_BOOL_NOTIMPLIMENTED;
    STDMETHOD_(BOOL, GetSoftwareVertexProcessing)(THIS) CBD3D_BOOL_NOTIMPLIMENTED;
    STDMETHOD_(float, GetNPatchMode)(THIS) CBD3D_FLOAT_NOTIMPLIMENTED;
    STDMETHOD( GetVertexShaderConstantF) (UINT  StartRegister, float*  pConstantData, UINT  Vector4fCount ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetVertexShaderConstantI) (UINT  StartRegister, int*  pConstantData, UINT  Vector4iCount  ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetVertexShaderConstantB) (UINT  StartRegister, BOOL*  pConstantData, UINT  BoolCount  ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetPixelShaderConstantF) (UINT  StartRegister, float*  pConstantData, UINT  Vector4fCount ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetPixelShaderConstantI) (UINT  StartRegister, int*  pConstantData, UINT  Vector4iCount ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetPixelShaderConstantB) (UINT  StartRegister, BOOL*  pConstantData, UINT  BoolCount ) CBD3D_D3DERR_NOTIMPLIMENTED;


    CBMemoryBuffer* m_pCB;
    IDirect3DDevice9* m_pDevice;
};

typedef void (CBPlayer9::*PlayBFuncPTR) ();
 
#endif // CBD3D_PREPROCESSING
#endif