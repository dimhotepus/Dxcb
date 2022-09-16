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

#include "stdio.h"
#include "d3d9.h" // required for CBMacros.h
#include "CBMacros.h" // for MEMTRACE
#include "CBMemoryBuffer.h"

#if MEMTRACE
bool g_bMemoryTrace = false;
bool g_bPlaybackAPITrace = false;
bool g_bRecordAPITrace = false;
#endif


void SetMemoryTrace(bool bval)
{
#if MEMTRACE
    g_bMemoryTrace = bval; 
#endif
}

void SetCommandBufferPlaybackAPITrace(bool bval)
{ 
#if MEMTRACE
    g_bPlaybackAPITrace = bval; 
#endif
}

void SetCommandBufferRecordAPITrace(bool bval)
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
m_pMem(NULL),
m_iSize(0),
m_pNext(NULL)
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
