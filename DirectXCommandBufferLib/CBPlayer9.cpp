// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
// Open source.
// See Vincent Scheib rant at http://beautifulpixels.blogspot.com/2008/07/parallel-rendering-with-directx-command.html

#ifndef CBD3D_PREPROCESSING

#include <cstdio>
#include <cassert>
#include <type_traits>
#include <d3d9.h>
#include "PREPROCESSED_CBPlayer9.cpp"

#else

#include "CBMacros.h"
#include "CBMemoryBuffer.h"
#include "CBPlayer9.h"

// Must access by an (enum - CBD3D_COMMANDS::NULLCALL)
PlayBFuncPTR PlaybackFunctionTable[] =
{
    &CBPlayer9::DoNULLCall,
    &CBPlayer9::DoQueryInterface,
    &CBPlayer9::DoAddRef,
    &CBPlayer9::DoRelease,
    &CBPlayer9::DoDrawPrimitive,
    &CBPlayer9::DoDrawIndexedPrimitive,
    &CBPlayer9::DoSetStreamSource,
    &CBPlayer9::DoSetStreamSourceFreq,
    &CBPlayer9::DoSetVertexDeclaration,
    &CBPlayer9::DoSetIndices,
    &CBPlayer9::DoTestCooperativeLevel,
    &CBPlayer9::DoEvictManagedResources,
    &CBPlayer9::DoBeginScene,
    &CBPlayer9::DoEndScene,
    &CBPlayer9::DoBeginStateBlock,
    &CBPlayer9::DoSetCursorProperties,
    &CBPlayer9::DoSetCursorPosition,
    &CBPlayer9::DoSetDialogBoxMode,
    &CBPlayer9::DoGetDeviceCaps,
    &CBPlayer9::DoGetDisplayMode,
    &CBPlayer9::DoGetCreationParameters,
    &CBPlayer9::DoCreateAdditionalSwapChain,
    &CBPlayer9::DoGetSwapChain,
    &CBPlayer9::DoReset,
    &CBPlayer9::DoPresent,
    &CBPlayer9::DoGetBackBuffer,
    &CBPlayer9::DoGetRasterStatus,
    &CBPlayer9::DoSetGammaRamp,
    &CBPlayer9::DoGetGammaRamp,
    &CBPlayer9::DoCreateTexture,
    &CBPlayer9::DoCreateVolumeTexture,
    &CBPlayer9::DoCreateCubeTexture,
    &CBPlayer9::DoCreateVertexBuffer,
    &CBPlayer9::DoCreateIndexBuffer,
    &CBPlayer9::DoCreateRenderTarget,
    &CBPlayer9::DoCreateDepthStencilSurface,
    &CBPlayer9::DoUpdateSurface,
    &CBPlayer9::DoUpdateTexture,
    &CBPlayer9::DoGetRenderTargetData,
    &CBPlayer9::DoGetFrontBufferData,
    &CBPlayer9::DoStretchRect,
    &CBPlayer9::DoColorFill,
    &CBPlayer9::DoCreateOffscreenPlainSurface,
    &CBPlayer9::DoSetRenderTarget,
    &CBPlayer9::DoGetRenderTarget,
    &CBPlayer9::DoSetDepthStencilSurface,
    &CBPlayer9::DoGetDepthStencilSurface,
    &CBPlayer9::DoClear,
    &CBPlayer9::DoSetTransform,
    &CBPlayer9::DoGetTransform,
    &CBPlayer9::DoMultiplyTransform,
    &CBPlayer9::DoSetViewport,
    &CBPlayer9::DoGetViewport,
    &CBPlayer9::DoSetMaterial,
    &CBPlayer9::DoGetMaterial,
    &CBPlayer9::DoSetLight,
    &CBPlayer9::DoGetLight,
    &CBPlayer9::DoLightEnable,
    &CBPlayer9::DoGetLightEnable,
    &CBPlayer9::DoSetClipPlane,
    &CBPlayer9::DoGetClipPlane,
    &CBPlayer9::DoSetRenderState,
    &CBPlayer9::DoGetRenderState,
    &CBPlayer9::DoCreateStateBlock,
    &CBPlayer9::DoEndStateBlock,
    &CBPlayer9::DoSetClipStatus,
    &CBPlayer9::DoGetClipStatus,
    &CBPlayer9::DoGetTexture,
    &CBPlayer9::DoSetTexture,
    &CBPlayer9::DoGetTextureStageState,
    &CBPlayer9::DoSetTextureStageState,
    &CBPlayer9::DoGetSamplerState,
    &CBPlayer9::DoSetSamplerState,
    &CBPlayer9::DoValidateDevice,
    &CBPlayer9::DoSetPaletteEntries,
    &CBPlayer9::DoGetPaletteEntries,
    &CBPlayer9::DoSetCurrentTexturePalette,
    &CBPlayer9::DoGetCurrentTexturePalette,
    &CBPlayer9::DoSetScissorRect,
    &CBPlayer9::DoGetScissorRect,
    &CBPlayer9::DoSetSoftwareVertexProcessing,
    &CBPlayer9::DoSetNPatchMode,
    &CBPlayer9::DoDrawPrimitiveUP,
    &CBPlayer9::DoDrawIndexedPrimitiveUP,
    &CBPlayer9::DoProcessVertices,
    &CBPlayer9::DoCreateVertexDeclaration,
    &CBPlayer9::DoGetVertexDeclaration,
    &CBPlayer9::DoSetFVF,
    &CBPlayer9::DoGetFVF,
    &CBPlayer9::DoCreateVertexShader,
    &CBPlayer9::DoSetVertexShader,
    &CBPlayer9::DoGetVertexShader,
    &CBPlayer9::DoSetVertexShaderConstantF,
    &CBPlayer9::DoGetVertexShaderConstantF,
    &CBPlayer9::DoSetVertexShaderConstantI,
    &CBPlayer9::DoGetVertexShaderConstantI,
    &CBPlayer9::DoSetVertexShaderConstantB,
    &CBPlayer9::DoGetVertexShaderConstantB,
    &CBPlayer9::DoGetStreamSource,
    &CBPlayer9::DoGetStreamSourceFreq,
    &CBPlayer9::DoGetIndices,
    &CBPlayer9::DoCreatePixelShader,
    &CBPlayer9::DoSetPixelShader,
    &CBPlayer9::DoGetPixelShader,
    &CBPlayer9::DoSetPixelShaderConstantF,
    &CBPlayer9::DoGetPixelShaderConstantF,
    &CBPlayer9::DoSetPixelShaderConstantI,
    &CBPlayer9::DoGetPixelShaderConstantI,
    &CBPlayer9::DoSetPixelShaderConstantB,
    &CBPlayer9::DoGetPixelShaderConstantB,
    &CBPlayer9::DoDrawRectPatch,
    &CBPlayer9::DoDrawTriPatch,
    &CBPlayer9::DoDeletePatch,
    &CBPlayer9::DoCreateQuery,
    &CBPlayer9::DoGetDirect3D, // Last supported func, if changed must fix CBPlayer9::Playback logic

    //not implemented
    (PlayBFuncPTR) & CBPlayer9::GetAvailableTextureMem,
    (PlayBFuncPTR) & CBPlayer9::GetNumberOfSwapChains,
    (PlayBFuncPTR) & CBPlayer9::ShowCursor,
    (PlayBFuncPTR) & CBPlayer9::GetSoftwareVertexProcessing,
    (PlayBFuncPTR) & CBPlayer9::GetNPatchMode
};

CBPlayer9::CBPlayer9() : m_pCB(NULL), m_pDevice(NULL)
{
}

void CBPlayer9::Playback(IDirect3DDevice9 *pDevice, CBMemoryBuffer* pCB)
{
    m_pDevice = pDevice;
    m_pCB = pCB;
    bool target = false;
    
    m_pCB->ResetNext();

    DWORD dwLastToken = 0;
    DWORD dwLastFuncToken = 0;
    DWORD dwInstructionCount = 0;

    bool bParsingCommand = true;
    while(bParsingCommand && m_pCB->GetAvailableMemorySize()>0)
    {
        DWORD dwFunc = m_pCB->DoGetDWORD();
        if(dwFunc == CBD3D_COMMANDS::NULLCALL)            
        {
            m_pCB->ResetNext();
            bParsingCommand = false;
        }
        else if (dwFunc < CBD3D_COMMANDS::NULLCALL
            || dwFunc > CBD3D_COMMANDS::GetDirect3D)
        {
            //this allows you to recover from buffer corruption.
            m_pCB->ResetNext();
            bParsingCommand = false;
            //OutputDebugStringA(__FUNCTION__ ": Invalid function token in command buffer, buffer must be corrupt\n");
            //CBD3D_BREAK();
        }
        else
        {
            target = false;
            static bool bGo = false;
            if(bGo && dwFunc == CBD3D_COMMANDS::SetTextureStageState)
            {
                target = true;
                char    temp[300];
                DWORD *pNext = m_pCB->DoGetDWORDPTR();
                sprintf_s(temp, 299, "%s  ( %lu %lu %lu ) \n", CBMemoryBuffer::Index2FunctionName(dwFunc),pNext[0],pNext[2],pNext[3]);
                OutputDebugStringA(temp);
            }
#if MEMTRACE
            if(g_bMemoryTrace)
            {
                char    temp[300];

                sprintf_s(temp, 299, "%s  %lu \n", CBMemoryBuffer::Index2FunctionName(dwFunc),dwFunc);
                OutputDebugStringA(temp);
            }
#endif
            (this->*PlaybackFunctionTable[dwFunc - CBD3D_COMMANDS::NULLCALL]) ();
            dwLastFuncToken = dwFunc;
        }
        dwLastToken = dwFunc;
        dwInstructionCount++;
    }

    m_pDevice = NULL;
#ifdef MARKMEMORYBUFFERS
    DWORD* pMem;
    UINT iNumDWORDs;
    m_pCB->GetCBMemory(pMem,iNumDWORDs);
    *pMem = 0x0;
    //memset(pMem,0x0,iNumDWORDs*4);
#endif
    m_pCB = NULL;
}

// The functions below are helpers that use the STDPLAYFUNC macros.;
void CBPlayer9::DoNULLCall() CBD3D_VOID_NOTIMPLIMENTED;
void CBPlayer9::DoQueryInterface() CBD3D_VOID_NOTIMPLIMENTED;

STDPLAYFUNC0(CBPlayer9::DoAddRef, AddRef);
STDPLAYFUNC0(CBPlayer9::DoRelease, Release);
STDPLAYFUNC3(CBPlayer9::DoDrawPrimitive, DrawPrimitive, D3DPRIMITIVETYPE, UINT, UINT);
STDPLAYFUNC6(CBPlayer9::DoDrawIndexedPrimitive, DrawIndexedPrimitive, D3DPRIMITIVETYPE, INT, UINT, UINT, UINT, UINT);
STDPLAYFUNC4(CBPlayer9::DoSetStreamSource, SetStreamSource, UINT, IDirect3DVertexBuffer9 *, UINT, UINT);
STDPLAYFUNC2(CBPlayer9::DoSetStreamSourceFreq, SetStreamSourceFreq, UINT, UINT);
STDPLAYFUNC1(CBPlayer9::DoSetVertexDeclaration, SetVertexDeclaration, IDirect3DVertexDeclaration9 *);
STDPLAYFUNC1(CBPlayer9::DoSetIndices, SetIndices, IDirect3DIndexBuffer9 *);
STDPLAYFUNC0(CBPlayer9::DoTestCooperativeLevel, TestCooperativeLevel);
STDPLAYFUNC0(CBPlayer9::DoEvictManagedResources, EvictManagedResources);
STDPLAYFUNC0(CBPlayer9::DoBeginScene, BeginScene);
STDPLAYFUNC0(CBPlayer9::DoEndScene, EndScene);
STDPLAYFUNC0(CBPlayer9::DoBeginStateBlock, BeginStateBlock);
STDPLAYFUNC3(CBPlayer9::DoSetCursorProperties, SetCursorProperties, UINT, UINT, IDirect3DSurface9 *);
STDPLAYVOIDFUNC3(CBPlayer9::DoSetCursorPosition, SetCursorPosition, int, int, DWORD)
STDPLAYFUNC1(CBPlayer9::DoSetDialogBoxMode, SetDialogBoxMode, BOOL);
STDPLAYFUNC1(CBPlayer9::DoReset, Reset, D3DPRESENT_PARAMETERS *);
STDPLAYFUNC4(CBPlayer9::DoPresent, Present, CONST RECT *, CONST RECT *, HWND, CONST RGNDATA *);
STDPLAYVOIDFUNC3( CBPlayer9::DoSetGammaRamp , SetGammaRamp , UINT , DWORD , CONST D3DGAMMARAMP* )    
STDPLAYFUNC4( CBPlayer9::DoUpdateSurface , UpdateSurface , IDirect3DSurface9* , CONST RECT* , IDirect3DSurface9* , CONST POINT* )                    ;
STDPLAYFUNC2( CBPlayer9::DoUpdateTexture , UpdateTexture , IDirect3DBaseTexture9* , IDirect3DBaseTexture9* )                    ;
STDPLAYFUNC5( CBPlayer9::DoStretchRect , StretchRect , IDirect3DSurface9* , CONST RECT* , IDirect3DSurface9* , CONST RECT* , D3DTEXTUREFILTERTYPE )                    ;
STDPLAYFUNC3( CBPlayer9::DoColorFill , ColorFill , IDirect3DSurface9* , CONST RECT* , D3DCOLOR )                    ;
STDPLAYFUNC2( CBPlayer9::DoSetRenderTarget , SetRenderTarget , DWORD , IDirect3DSurface9* )                    ;
STDPLAYFUNC1( CBPlayer9::DoSetDepthStencilSurface , SetDepthStencilSurface , IDirect3DSurface9* )                    ;
STDPLAYFUNC6(CBPlayer9::DoClear, Clear, DWORD, CONST D3DRECT *, DWORD, D3DCOLOR, float, DWORD);
STDPLAYFUNC2(CBPlayer9::DoSetTransform, SetTransform, D3DTRANSFORMSTATETYPE, CONST D3DMATRIX *);
STDPLAYFUNC2(CBPlayer9::DoMultiplyTransform, MultiplyTransform, D3DTRANSFORMSTATETYPE, CONST D3DMATRIX *);
STDPLAYFUNC1(CBPlayer9::DoSetViewport, SetViewport, CONST D3DVIEWPORT9 *);
STDPLAYFUNC1(CBPlayer9::DoSetMaterial, SetMaterial, CONST D3DMATERIAL9 *);
STDPLAYFUNC2(CBPlayer9::DoSetLight, SetLight, DWORD, CONST D3DLIGHT9 *);
STDPLAYFUNC2(CBPlayer9::DoLightEnable, LightEnable, DWORD, BOOL);
STDPLAYFUNC2(CBPlayer9::DoSetClipPlane, SetClipPlane, DWORD, CONST float *);
STDPLAYFUNC2(CBPlayer9::DoSetRenderState, SetRenderState, D3DRENDERSTATETYPE, DWORD);
STDPLAYFUNC1(CBPlayer9::DoEndStateBlock, EndStateBlock, IDirect3DStateBlock9 **);
STDPLAYFUNC1(CBPlayer9::DoSetClipStatus, SetClipStatus, CONST D3DCLIPSTATUS9 *);
STDPLAYFUNC2(CBPlayer9::DoSetTexture, SetTexture, DWORD, IDirect3DBaseTexture9 *);
STDPLAYFUNC3(CBPlayer9::DoSetTextureStageState, SetTextureStageState, DWORD, D3DTEXTURESTAGESTATETYPE, DWORD);
STDPLAYFUNC3(CBPlayer9::DoSetSamplerState, SetSamplerState, DWORD, D3DSAMPLERSTATETYPE, DWORD);
STDPLAYFUNC1(CBPlayer9::DoValidateDevice, ValidateDevice, DWORD *);
STDPLAYFUNC2(CBPlayer9::DoSetPaletteEntries, SetPaletteEntries, UINT, CONST PALETTEENTRY *);
STDPLAYFUNC1(CBPlayer9::DoSetCurrentTexturePalette, SetCurrentTexturePalette, UINT);
STDPLAYFUNC1(CBPlayer9::DoSetScissorRect, SetScissorRect, CONST RECT *);
STDPLAYFUNC1(CBPlayer9::DoSetSoftwareVertexProcessing, SetSoftwareVertexProcessing, BOOL);
STDPLAYFUNC1(CBPlayer9::DoSetNPatchMode, SetNPatchMode, float);
STDPLAYFUNC4(CBPlayer9::DoDrawPrimitiveUP, DrawPrimitiveUP, D3DPRIMITIVETYPE, UINT, CONST void *, UINT);
STDPLAYFUNC8( CBPlayer9::DoDrawIndexedPrimitiveUP , DrawIndexedPrimitiveUP , D3DPRIMITIVETYPE , UINT , UINT , UINT  , CONST void* , D3DFORMAT , CONST void* , UINT )                    ;
STDPLAYFUNC6( CBPlayer9::DoProcessVertices , ProcessVertices , UINT , UINT , UINT , IDirect3DVertexBuffer9* , IDirect3DVertexDeclaration9* , DWORD )                    ;
STDPLAYFUNC1(CBPlayer9::DoSetFVF, SetFVF, DWORD);
STDPLAYFUNC1(CBPlayer9::DoSetVertexShader, SetVertexShader, IDirect3DVertexShader9 *);
STDPLAYFUNC1(CBPlayer9::DoSetPixelShader, SetPixelShader, IDirect3DPixelShader9 *);
STDPLAYFUNC3(CBPlayer9::DoDrawRectPatch, DrawRectPatch, UINT, CONST float *, CONST D3DRECTPATCH_INFO *);
STDPLAYFUNC3(CBPlayer9::DoDrawTriPatch, DrawTriPatch, UINT, CONST float *, CONST D3DTRIPATCH_INFO *);
STDPLAYFUNC1(CBPlayer9::DoDeletePatch, DeletePatch, UINT);
STDPLAYSETCONSTS(CBPlayer9::DoSetVertexShaderConstantF, SetVertexShaderConstantF, UINT, CONST float *, UINT, float)
STDPLAYSETCONSTS(CBPlayer9::DoSetVertexShaderConstantI, SetVertexShaderConstantI, UINT, CONST int *, UINT, int)
STDPLAYSETCONSTS(CBPlayer9::DoSetVertexShaderConstantB, SetVertexShaderConstantB, UINT, CONST BOOL *, UINT, BOOL)
STDPLAYSETCONSTS(CBPlayer9::DoSetPixelShaderConstantF, SetPixelShaderConstantF, UINT, CONST float *, UINT, float)
STDPLAYSETCONSTS(CBPlayer9::DoSetPixelShaderConstantI, SetPixelShaderConstantI, UINT, CONST int *, UINT, int)
STDPLAYSETCONSTS(CBPlayer9::DoSetPixelShaderConstantB, SetPixelShaderConstantB, UINT, CONST BOOL *, UINT, BOOL)
#endif
