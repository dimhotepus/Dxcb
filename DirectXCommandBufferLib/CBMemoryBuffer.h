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

#ifndef _CBMEMORYBUFFER_H_
#define _CBMEMORYBUFFER_H_

#ifndef CBD3D_PREPROCESSING
#   include "stdio.h"
#   include <assert.h>
#   include "d3d9.h"
#   include "PREPROCESSED_CBMemoryBuffer.h"
#else

#include "CBMacros.h"

#if MEMTRACE
extern bool g_bMemoryTrace;
extern bool g_bPlaybackAPITrace;
extern bool g_bRecordAPITrace;
#endif

void SetMemoryTrace(bool bval);
void SetCommandBufferPlaybackAPITrace(bool bval);
void SetCommandBufferRecordAPITrace(bool bval);

// This enumeration is used to index into the PlaybackNumberArgs table to obtain the
// number of
namespace CBD3D_COMMANDS
{
    enum
    {
        NULLCALL = 0xD3D00000, // High value to catch command buffer errors
        QueryInterface,
        AddRef,
        Release,
        DrawPrimitive,
        DrawIndexedPrimitive,
        SetStreamSource,
        SetStreamSourceFreq,
        SetVertexDeclaration,
        SetIndices,
        TestCooperativeLevel,
        EvictManagedResources,
        BeginScene,
        EndScene,
        BeginStateBlock,
        SetCursorProperties,
        SetCursorPosition,
        SetDialogBoxMode,
        GetDeviceCaps,
        GetDisplayMode,
        GetCreationParameters,
        CreateAdditionalSwapChain,
        GetSwapChain,
        Reset,
        Present,
        GetBackBuffer,
        GetRasterStatus,
        SetGammaRamp,
        GetGammaRamp,
        CreateTexture,
        CreateVolumeTexture,
        CreateCubeTexture,
        CreateVertexBuffer,
        CreateIndexBuffer,
        CreateRenderTarget,
        CreateDepthStencilSurface,
        UpdateSurface,
        UpdateTexture,
        GetRenderTargetData,
        GetFrontBufferData,
        StretchRect,
        ColorFill,
        CreateOffscreenPlainSurface,
        SetRenderTarget,
        GetRenderTarget,
        SetDepthStencilSurface,
        GetDepthStencilSurface,
        Clear,
        SetTransform,
        GetTransform,
        MultiplyTransform,
        SetViewport,
        GetViewport,
        SetMaterial,
        GetMaterial,
        SetLight,
        GetLight,
        LightEnable,
        GetLightEnable,
        SetClipPlane,
        GetClipPlane,
        SetRenderState,
        GetRenderState,
        CreateStateBlock,
        EndStateBlock,
        SetClipStatus,
        GetClipStatus,
        GetTexture,
        SetTexture,
        GetTextureStageState,
        SetTextureStageState,
        GetSamplerState,
        SetSamplerState,
        ValidateDevice,
        SetPaletteEntries,
        GetPaletteEntries,
        SetCurrentTexturePalette,
        GetCurrentTexturePalette,
        SetScissorRect,
        GetScissorRect,
        SetSoftwareVertexProcessing,
        SetNPatchMode,
        DrawPrimitiveUP,
        DrawIndexedPrimitiveUP,
        ProcessVertices,
        CreateVertexDeclaration,
        GetVertexDeclaration,
        SetFVF,
        GetFVF,
        CreateVertexShader,
        SetVertexShader,
        GetVertexShader,
        SetVertexShaderConstantF,
        GetVertexShaderConstantF,
        SetVertexShaderConstantI,
        GetVertexShaderConstantI,
        SetVertexShaderConstantB,
        GetVertexShaderConstantB,
        GetStreamSource,
        GetStreamSourceFreq,
        GetIndices,
        CreatePixelShader,
        SetPixelShader,
        GetPixelShader,
        SetPixelShaderConstantF,
        GetPixelShaderConstantF,
        SetPixelShaderConstantI,
        GetPixelShaderConstantI,
        SetPixelShaderConstantB,
        GetPixelShaderConstantB,
        DrawRectPatch,
        DrawTriPatch,
        DeletePatch,
        CreateQuery,
        GetDirect3D,
        GetAvailableTextureMem,
        GetNumberOfSwapChains,
        ShowCursor,
        GetSoftwareVertexProcessing,
        GetNPatchMode
    };
}

//disable type conversion errors
#pragma warning( disable : 4312 )
#pragma warning( disable : 4311 )

class CBMemoryBuffer
{
public:

    CBMemoryBuffer();
    void ResetNext();
    void GetCBMemory(DWORD* &pMem, UINT &iNumDWORDs);
    void SetCBMemory(DWORD *pMem,UINT iNumDWORDs);

    //put or get DWORD sized tokens
    inline DWORD DoGetDWORD();
    inline DWORD* DoGetDWORDPTR(); //peek at the next token

    //memsize is size in bytes
    inline DWORD* DoGetMem(DWORD memsize);

    static char *strFuncNames[120];
    static char* Index2FunctionName(unsigned int index) { return CBMemoryBuffer::strFuncNames[ index-CBD3D_COMMANDS::NULLCALL ]; }
    template< class TYPE >
    void DoPutDWORD(TYPE val)
    {
        assert(sizeof(TYPE) <= sizeof(DWORD));
        assert(m_pNext >= m_pMem);
        assert(m_pNext < (m_pMem+m_iSize));
#if MEMTRACE
        DWORD *pNext = m_pNext;
#endif
        *m_pNext = (DWORD) val;
        m_pNext++;
        DEBUGPUT( "CBMemoryBuffer::DoPutDWORD", val , pNext, m_pNext );
    }

    template< class TYPE >
    void DoPutMem(TYPE *val,DWORD memsize)
    {
        int memsize_in_DWORDs = (memsize+3)/4; // Number of DWORDs required to store memsize, round up
        assert(m_pNext >= m_pMem);
        assert((m_pNext+memsize_in_DWORDs-1) < (m_pMem+m_iSize));
#if MEMTRACE
        DWORD *pNext = m_pNext;
#endif
        if(val==NULL)
            *m_pNext = 0;
        else
            *m_pNext = 1;
        m_pNext++;
        if(val!=NULL)
        {
            memcpy((void*)m_pNext,(const void*)val,memsize);
            m_pNext += memsize_in_DWORDs;
        }
        DEBUGPUT( "CBMemoryBuffer::DoPutDWORD", val , pNext, m_pNext );
    }


    //types of size > DWORD
    GET_AND_PUT_OBJ( D3DCAPS9 );
    GET_AND_PUT_OBJ( D3DDEVICE_CREATION_PARAMETERS );
    GET_AND_PUT_OBJ( D3DPRESENT_PARAMETERS );
    GET_AND_PUT_OBJ( CONST RECT );
    GET_AND_PUT_OBJ( CONST RGNDATA );
    GET_AND_PUT_OBJ( CONST D3DGAMMARAMP );
    GET_AND_PUT_OBJ( D3DGAMMARAMP );
    GET_AND_PUT_OBJ( D3DRASTER_STATUS );
    GET_AND_PUT_OBJ( CONST POINT );
    GET_AND_PUT_OBJ( CONST D3DRECT );
    GET_AND_PUT_OBJ( CONST D3DMATRIX );
    GET_AND_PUT_OBJ( D3DMATRIX );
    GET_AND_PUT_OBJ( CONST D3DVIEWPORT9 );
    GET_AND_PUT_OBJ( D3DVIEWPORT9 );
    GET_AND_PUT_OBJ( CONST D3DMATERIAL9 );
    GET_AND_PUT_OBJ( D3DMATERIAL9 );
    GET_AND_PUT_OBJ( CONST D3DLIGHT9 );
    GET_AND_PUT_OBJ( D3DLIGHT9 );
    GET_AND_PUT_OBJ( CONST PALETTEENTRY );
    GET_AND_PUT_OBJ( PALETTEENTRY );
    GET_AND_PUT_OBJ( RECT );
    GET_AND_PUT_OBJ( CONST D3DVERTEXELEMENT9 );
    GET_AND_PUT_OBJ( CONST D3DCLIPSTATUS9 );
    GET_AND_PUT_OBJ( D3DCLIPSTATUS9 );
    GET_AND_PUT_OBJ( CONST D3DRECTPATCH_INFO );
    GET_AND_PUT_OBJ( CONST D3DTRIPATCH_INFO  );




    GET_AND_PUT_DWORD( D3DDISPLAYMODE* );
    GET_AND_PUT_DWORD( BOOL* );
    GET_AND_PUT_DWORD( CONST float* );
    GET_AND_PUT_DWORD( float* );
    GET_AND_PUT_DWORD( DWORD* );
    GET_AND_PUT_DWORD( CONST void* );
    GET_AND_PUT_DWORD( CONST DWORD* );
    GET_AND_PUT_DWORD( CONST int* );
    GET_AND_PUT_DWORD( LPUINT );

    //types that can be cast as DWORDs
    GET_AND_PUT_DWORD( void** );
    GET_AND_PUT_DWORD( D3DPRIMITIVETYPE );
    GET_AND_PUT_DWORD( UINT );
    GET_AND_PUT_DWORD( INT );
    GET_AND_PUT_DWORD( IDirect3DVertexBuffer9* );
    GET_AND_PUT_DWORD( IDirect3DVertexDeclaration9* );
    GET_AND_PUT_DWORD( IDirect3DIndexBuffer9* );
    GET_AND_PUT_DWORD( IDirect3DSurface9* );
    GET_AND_PUT_DWORD( DWORD );
    GET_AND_PUT_DWORD( IDirect3DSwapChain9** );
    GET_AND_PUT_DWORD( HWND );
    GET_AND_PUT_DWORD( D3DBACKBUFFER_TYPE );
    GET_AND_PUT_DWORD( IDirect3DSurface9** );
    GET_AND_PUT_DWORD( D3DFORMAT );
    GET_AND_PUT_DWORD( D3DPOOL );
    GET_AND_PUT_DWORD( IDirect3DTexture9** );
    GET_AND_PUT_DWORD( IDirect3DVolumeTexture9** );
    GET_AND_PUT_DWORD( IDirect3DCubeTexture9** );
    GET_AND_PUT_DWORD( IDirect3DVertexBuffer9** );
    GET_AND_PUT_DWORD( IDirect3DIndexBuffer9** );
    GET_AND_PUT_DWORD( D3DMULTISAMPLE_TYPE );
    GET_AND_PUT_DWORD( IDirect3DBaseTexture9* );
    GET_AND_PUT_DWORD( D3DTEXTUREFILTERTYPE );
    GET_AND_PUT_DWORD( float );
    GET_AND_PUT_DWORD( D3DTRANSFORMSTATETYPE );
    GET_AND_PUT_DWORD( D3DRENDERSTATETYPE );
    GET_AND_PUT_DWORD( D3DSTATEBLOCKTYPE );
    GET_AND_PUT_DWORD( IDirect3DStateBlock9** );
    GET_AND_PUT_DWORD( IDirect3DBaseTexture9** );
    GET_AND_PUT_DWORD( D3DTEXTURESTAGESTATETYPE );
    GET_AND_PUT_DWORD( D3DSAMPLERSTATETYPE );
    GET_AND_PUT_DWORD( IDirect3DVertexDeclaration9** );
    GET_AND_PUT_DWORD( IDirect3DVertexShader9** );
    GET_AND_PUT_DWORD( IDirect3DVertexShader9* );
    GET_AND_PUT_DWORD( IDirect3DPixelShader9** );
    GET_AND_PUT_DWORD( IDirect3DPixelShader9* );
    GET_AND_PUT_DWORD( D3DQUERYTYPE );
    GET_AND_PUT_DWORD( IDirect3DQuery9** );
    GET_AND_PUT_DWORD( IDirect3D9** );



    //Get the unread or unwritten meory size
    int GetAvailableMemorySize()
    {
        int ret = (m_iSize - (m_pNext - m_pMem));
        return ret ;
    }
    //check if there is iSize DWORDs left
    bool CheckAvailableMemorySize(int iSize)
    {
        int AvailableMemory = GetAvailableMemorySize();
        MEMSIZECHECK(AvailableMemory,iSize);
        return (iSize<=AvailableMemory);
    }

    // pointer to memory given to us by app
    DWORD    *m_pMem;
    // size of memory in DWORDs.
    UINT    m_iSize;
    // pointer to current token position in memory
    DWORD    *m_pNext;
}; // class CBMemoryBuffer

//---------------------------------------------------------------------------
// Inline Functions

inline DWORD* CBMemoryBuffer::DoGetDWORDPTR()
{
    return m_pNext;
}

inline DWORD CBMemoryBuffer::DoGetDWORD()
{
    assert(m_pNext >= m_pMem);
    assert(m_pNext < (m_pMem+m_iSize));
#if MEMTRACE
    DWORD *pNext = m_pNext;
#endif
    DWORD ret = *m_pNext;
    m_pNext++;
    DEBUGGET( "CBMemoryBuffer::DoGetDWORD", ret, pNext, m_pNext );
    return ret;
}

inline DWORD* CBMemoryBuffer::DoGetMem( DWORD memsize )
{
    int memsize_in_DWORDs = (memsize+3)/4; // Number of DWORDs required to store memsize, round up
    assert(m_pNext >= m_pMem);
    assert((m_pNext+memsize_in_DWORDs-1) < (m_pMem+m_iSize));
#if MEMTRACE
    DWORD *pNext = m_pNext;
#endif
    DWORD val = *m_pNext;
    m_pNext++;
    DWORD* ret = m_pNext;
    if(val != 0)
    {
        m_pNext += memsize_in_DWORDs;
    }
    else
    {
        ret = NULL;
    }
    DEBUGGET( "CBMemoryBuffer::DoGetMem", ret, pNext,  m_pNext );
    return ret;
}

#endif // CBD3D_PREPROCESSING
#endif // _CBMEMORYBUFFER_H_