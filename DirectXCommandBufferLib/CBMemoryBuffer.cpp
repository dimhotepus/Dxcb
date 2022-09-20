// Open source.
// See Vincent Scheib rant at http://beautifulpixels.blogspot.com/2008/07/parallel-rendering-with-directx-command.html

#include "stdio.h"
#include "d3d9.h" // required for CBMacros.h
#include "CBMacros.h" // for MEMTRACE
#include "CBMemoryBuffer.h"

#if MEMTRACE
bool g_bMemoryTrace = false;
bool g_bPlaybackAPITrace = false;
bool g_bRecordAPITrace = false;
#endif


void SetMemoryTrace([[maybe_unused]] bool bval)
{
#if MEMTRACE
    g_bMemoryTrace = bval; 
#endif
}

void SetCommandBufferPlaybackAPITrace([[maybe_unused]] bool bval)
{ 
#if MEMTRACE
    g_bPlaybackAPITrace = bval; 
#endif
}

void SetCommandBufferRecordAPITrace([[maybe_unused]] bool bval)
{ 
#if MEMTRACE
    g_bRecordAPITrace = bval; 
#endif
}

char *CBMemoryBuffer::strFuncNames[120] = {
        "NULLCALL",
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
        "GetNPatchMode"
        };


CBMemoryBuffer::CBMemoryBuffer() : 
    m_pMem(nullptr),
    m_iSize(0),
    m_pNext(nullptr)
{
}

void CBMemoryBuffer::ResetNext()
{
    m_pNext = m_pMem;
}

void CBMemoryBuffer::GetCBMemory( DWORD* &pMem, UINT &iNumDWORDs )
{
    pMem = m_pMem; 
    iNumDWORDs = m_iSize;
}

void CBMemoryBuffer::SetCBMemory( DWORD *pMem,UINT iNumDWORDs )
{
    m_pMem = pMem; 
    m_iSize = iNumDWORDs; 
    m_pNext = pMem;
}
