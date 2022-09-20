// Open source.
// See Vincent Scheib rant at http://beautifulpixels.blogspot.com/2008/07/parallel-rendering-with-directx-command.html

#pragma once

#ifndef CBD3D_PREPROCESSING

#include <d3d9.h>
#include "d3dx9effect.h"
#include "PREPROCESSED_RedirectingDirect3DDevice9.h"

#else // CBD3D_PREPROCESSING is defined

 
////////////////////////////////////Redirecting Macros/////////////////////////////////////////////////////////////////////////
#define BUILDINTRACE    1

#if BUILDINTRACE
#define TRACEFUNC9(returntype, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6, type7, arg7, type8, arg8, type9, arg9)    \
    if( bTrace ) { char strTrace[700]; sprintf_s(strTrace,699,                                                                                                             \
    "%s %s ( %s  0x%x, %s  0x%x, %s  0x%x, %s  0x%x, %s  0x%x, %s  0x%x, %s  0x%x, %s  0x%x, %s  0x%x)\n",                        \
    #returntype, #methodname, #type1, (DWORD) arg1, #type2, (DWORD) arg2, #type3, (DWORD) arg3, #type4, (DWORD) arg4, #type5, (DWORD) arg5, #type6, (DWORD) arg6, #type7, (DWORD) arg7, #type8, (DWORD) arg8, #type9, (DWORD) arg9);OutputDebugStringA(strTrace); }

#define TRACEFUNC8(returntype, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6, type7, arg7, type8, arg8)                  \
    if( bTrace ) { char strTrace[700]; sprintf_s(strTrace,699,                                                                                                              \
    "%s %s ( %s  0x%x, %s  0x%x, %s  0x%x, %s  0x%x, %s  0x%x, %s  0x%x, %s  0x%x, %s  0x%x)\n",                                      \
    #returntype, #methodname, #type1, (DWORD) arg1, #type2, (DWORD) arg2, #type3, (DWORD) arg3, #type4, (DWORD) arg4, #type5, (DWORD) arg5, #type6, (DWORD) arg6, #type7, (DWORD) arg7, #type8, (DWORD) arg8);OutputDebugStringA(strTrace); }

#define TRACEFUNC7(returntype, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6, type7, arg7)                               \
    if( bTrace ) { char strTrace[700]; sprintf_s(strTrace,699,                                                                                                              \
    "%s %s ( %s  0x%x, %s  0x%x, %s  0x%x, %s  0x%x, %s  0x%x, %s  0x%x, %s  0x%x)\n",                                                   \
    #returntype, #methodname, #type1, (DWORD) arg1, #type2, (DWORD) arg2, #type3, (DWORD) arg3, #type4, (DWORD) arg4, #type5, (DWORD) arg5, #type6, (DWORD) arg6, #type7, (DWORD) arg7);OutputDebugStringA(strTrace); }

#define TRACEFUNC6(returntype, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6)                                            \
    if( bTrace ) { char strTrace[700]; sprintf_s(strTrace,699,                                                                                                              \
    "%s %s ( %s  0x%x, %s  0x%x, %s  0x%x, %s  0x%x, %s  0x%x, %s  0x%x)\n",                                                                \
    #returntype, #methodname, #type1, (DWORD) arg1, #type2, (DWORD) arg2, #type3, (DWORD) arg3, #type4, (DWORD) arg4, #type5, (DWORD) arg5, #type6, (DWORD) arg6);OutputDebugStringA(strTrace); }

#define TRACEFUNC5(returntype, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5)                                                         \
    if( bTrace ) { char strTrace[700]; sprintf_s(strTrace,699,                                                                                                              \
    "%s %s ( %s  0x%x, %s  0x%x, %s  0x%x, %s  0x%x, %s  0x%x)\n",                                                                             \
    #returntype, #methodname, #type1, (DWORD) arg1, #type2, (DWORD) arg2, #type3, (DWORD) arg3, #type4, (DWORD) arg4, #type5, (DWORD) arg5);OutputDebugStringA(strTrace); }

#define TRACEFUNC4(returntype, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4)                                                                      \
    if( bTrace ) { char strTrace[700]; sprintf_s(strTrace,699,                                                                                                              \
    "%s %s ( %s  0x%x, %s  0x%x, %s  0x%x, %s  0x%x)\n",                                                                                          \
    #returntype, #methodname, #type1, (DWORD) arg1, #type2, (DWORD) arg2, #type3, (DWORD) arg3, #type4, (DWORD) arg4);OutputDebugStringA(strTrace); }

#define TRACEFUNC3(returntype, methodname, type1, arg1, type2, arg2, type3, arg3)                                                                                   \
    if( bTrace ) { char strTrace[700]; sprintf_s(strTrace,699,                                                                                                              \
    "%s %s ( %s  0x%x, %s  0x%x, %s  0x%x)\n",                                                                                                       \
    #returntype, #methodname, #type1, (DWORD) arg1, #type2, (DWORD) arg2, #type3, (DWORD) arg3);OutputDebugStringA(strTrace); }

#define TRACEFUNC2(returntype, methodname, type1, arg1, type2, arg2)                                                                                                \
    if( bTrace ) { char strTrace[700]; sprintf_s(strTrace,699,                                                                                                              \
    "%s %s ( %s  0x%x, %s  0x%x)\n",                                                                                                                    \
    #returntype, #methodname, #type1, (DWORD) arg1, #type2, (DWORD) arg2);OutputDebugStringA(strTrace); }

#define TRACEFUNC1(returntype, methodname, type1, arg1)                                                                                                             \
    if( bTrace ) { char strTrace[700]; sprintf_s(strTrace,699,                                                                                                              \
    "%s %s ( %s  0x%x)\n",                                                                                                                                 \
    #returntype, #methodname, #type1, (DWORD) arg1);OutputDebugStringA(strTrace); }

#define TRACEFUNC0(returntype, methodname)                                                                                                                          \
    if( bTrace ) { char strTrace[700]; sprintf_s(strTrace,699,                                                                                                              \
    "%s %s ( )\n",                                                                                                                                             \
    #returntype, #methodname);OutputDebugStringA(strTrace); }
#else
#define TRACEFUNC9(returntype, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6, type7, arg7, type8, arg8, type9, arg9) ;
#define TRACEFUNC8(returntype, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6, type7, arg7, type8, arg8)              ;
#define TRACEFUNC7(returntype, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6, type7, arg7)                           ;
#define TRACEFUNC6(returntype, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6)                                        ;
#define TRACEFUNC5(returntype, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5)                                                     ;
#define TRACEFUNC4(returntype, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4)                                                                  ;
#define TRACEFUNC3(returntype, methodname, type1, arg1, type2, arg2, type3, arg3)                                                                               ;
#define TRACEFUNC2(returntype, methodname, type1, arg1, type2, arg2)                                                                                            ;
#define TRACEFUNC1(returntype, methodname, type1, arg1)                                                                                                         ;
#define TRACEFUNC0(returntype, methodname)                                                                                                                      ;
#endif


#define REDIRFUNC0(returntype, methodname)    \
    STDMETHOD_(returntype,methodname)(   )    \
    { TRACEFUNC0 ( returntype, methodname)    \
    return pCurrentDevice->methodname(        ); }

#define REDIRFUNC1(returntype, methodname, type1, arg1)    \
    STDMETHOD_(returntype,methodname)(     type1  arg1)    \
    { TRACEFUNC1 ( returntype, methodname, type1, arg1)    \
    return pCurrentDevice->methodname(          arg1); }

#define REDIRFUNC2(returntype, methodname, type1, arg1, type2, arg2)    \
    STDMETHOD_(returntype,methodname)(     type1  arg1, type2  arg2)    \
    { TRACEFUNC2 ( returntype, methodname, type1, arg1, type2, arg2)    \
    return pCurrentDevice->methodname(          arg1,        arg2); }

#define REDIRFUNC3(returntype, methodname, type1, arg1, type2, arg2, type3, arg3)    \
    STDMETHOD_(returntype,methodname)(     type1  arg1, type2  arg2, type3  arg3)    \
    { TRACEFUNC3 ( returntype, methodname, type1, arg1, type2, arg2, type3, arg3)    \
    return pCurrentDevice->methodname(          arg1,        arg2,        arg3); }

#define REDIRFUNC4(returntype, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4)    \
    STDMETHOD_(returntype,methodname)(     type1  arg1, type2  arg2, type3  arg3, type4  arg4)    \
    { TRACEFUNC4 ( returntype, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4)    \
    return pCurrentDevice->methodname(          arg1,        arg2,        arg3,        arg4); }

#define REDIRFUNC5(returntype, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5)    \
    STDMETHOD_(returntype,methodname)(     type1  arg1, type2  arg2, type3  arg3, type4  arg4, type5  arg5)    \
    { TRACEFUNC5 ( returntype, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5)    \
    return pCurrentDevice->methodname(          arg1,        arg2,        arg3,        arg4,        arg5); }

#define REDIRFUNC6(returntype, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6)    \
    STDMETHOD_(returntype,methodname)(     type1  arg1, type2  arg2, type3  arg3, type4  arg4, type5  arg5, type6  arg6)    \
    { TRACEFUNC6 ( returntype, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6)    \
    return pCurrentDevice->methodname(          arg1,        arg2,        arg3,        arg4,        arg5,        arg6); }

#define REDIRFUNC7(returntype, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6, type7, arg7)    \
    STDMETHOD_(returntype,methodname)(     type1  arg1, type2  arg2, type3  arg3, type4  arg4, type5  arg5, type6  arg6, type7  arg7)    \
    { TRACEFUNC7 ( returntype, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6, type7, arg7)    \
    return pCurrentDevice->methodname(          arg1,        arg2,        arg3,        arg4,        arg5,        arg6,        arg7); }

#define REDIRFUNC8(returntype, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6, type7, arg7, type8, arg8)    \
    STDMETHOD_(returntype,methodname)(     type1  arg1, type2  arg2, type3  arg3, type4  arg4, type5  arg5, type6  arg6, type7  arg7, type8  arg8)    \
    { TRACEFUNC8 ( returntype, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6, type7, arg7, type8, arg8)    \
    return pCurrentDevice->methodname(          arg1,        arg2,        arg3,        arg4,        arg5,        arg6,        arg7,        arg8); }

#define REDIRFUNC9(returntype, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6, type7, arg7, type8, arg8, type9, arg9)    \
    STDMETHOD_(returntype,methodname)(     type1  arg1, type2  arg2, type3  arg3, type4  arg4, type5  arg5, type6  arg6, type7  arg7, type8  arg8, type9  arg9)    \
    { TRACEFUNC9 ( returntype, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6, type7, arg7, type8, arg8, type9, arg9)    \
    return pCurrentDevice->methodname(          arg1,        arg2,        arg3,        arg4,        arg5,        arg6,        arg7,        arg8,        arg9); }

#define OTHERREDIRFUNC0( returntype, methodname)\
    REDIRFUNC0(ULONG, methodname)
#define STDREDIRFUNC0(  methodname) \
    REDIRFUNC0(HRESULT, methodname)
#define STDREDIRFUNC1(  methodname, type1, arg1) \
    REDIRFUNC1(HRESULT, methodname, type1, arg1)
#define STDREDIRFUNC2(  methodname, type1, arg1, type2, arg2) \
    REDIRFUNC2(HRESULT, methodname, type1, arg1, type2, arg2)
#define STDREDIRFUNC3(  methodname, type1, arg1, type2, arg2, type3, arg3) \
    REDIRFUNC3(HRESULT, methodname, type1, arg1, type2, arg2, type3, arg3)
#define STDREDIRFUNC4(  methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4) \
    REDIRFUNC4(HRESULT, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4)
#define STDREDIRFUNC5(  methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5) \
    REDIRFUNC5(HRESULT, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5)
#define STDREDIRFUNC6(  methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6) \
    REDIRFUNC6(HRESULT, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6)
#define STDREDIRFUNC7(  methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6, type7, arg7) \
    REDIRFUNC7(HRESULT, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6, type7, arg7)
#define STDREDIRFUNC8(  methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6, type7, arg7, type8, arg8) \
    REDIRFUNC8(HRESULT, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6, type7, arg7, type8, arg8)
#define STDREDIRFUNC9(  methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6, type7, arg7, type8, arg8, type9, arg9) \
    REDIRFUNC9(HRESULT, methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6, type7, arg7, type8, arg8, type9, arg9)


class RedirectingDirect3DDevice9 : public IDirect3DDevice9
 {
 public:
    IDirect3D9 *pRealDirect3D9;
	IDirect3DDevice9 *pCurrentDevice;
	IDirect3DDevice9 *pRealDevice;
    bool bIsReal;
    bool bTrace;


     RedirectingDirect3DDevice9()
     { 
	    pCurrentDevice = NULL;
        pRealDirect3D9 = NULL;
        pRealDevice = NULL;
        bIsReal = false;
        bTrace = false;
     }
     ~RedirectingDirect3DDevice9(){}

    void SetTrace(bool bval)
    {
        bTrace = bval; 
    }

    bool GetTrace()
    {
        return bTrace; 
    }

    void ReplaceCurrentDevice(IDirect3DDevice9 *pNewDevice)
    {
        pCurrentDevice = pNewDevice;
        bIsReal = false;
    }

    void RestoreCurrentDevice()
    {
        pCurrentDevice = pRealDevice;
        bIsReal = true;
    }

    IDirect3DDevice9 *GetCurrentDevice()
    {
        return pCurrentDevice;
    }
    IDirect3DDevice9 *GetRealDevice()
    {
        return pRealDevice;
    }
    bool IsCurrentDeviceReal(){ return bIsReal; }
    

    /*** IUnknown methods ***/
//#if !BUILDTRACE
//     STDREDIRFUNC2( QueryInterface, REFIID, riid, void**, ppvObj);
//#else
	STDMETHOD_ (HRESULT, QueryInterface) (REFIID riid, void **ppvObj)
	{
		if(bTrace)
		{
			char	strTrace[700];
			sprintf_s
				(
					strTrace, 699, "%s %s ( %s  0x%x)\n", "HRESULT", "QueryInterface", "void**", (DWORD) ppvObj
				);
			OutputDebugStringA(strTrace);
		}
		return pCurrentDevice->QueryInterface(riid, ppvObj);
	};
//#endif

     OTHERREDIRFUNC0( ULONG, AddRef );
     OTHERREDIRFUNC0( ULONG, Release );

     /*** Implemnted IDirect3DDevice9 methods ***/
     /* Note that it is assumed that input values will be valid a record time. */
     /* Also there is no mechnism to retain returned values during playback     */
 
 
     STDREDIRFUNC3( DrawPrimitive, D3DPRIMITIVETYPE, PrimitiveType, UINT, StartVertex, UINT, PrimitiveCount);
     STDREDIRFUNC6( DrawIndexedPrimitive, D3DPRIMITIVETYPE, PrimitiveType, INT, BaseVertexIndex, UINT, MinVertexIndex, UINT, NumVertices, UINT, startIndex ,UINT, primCount );
     STDREDIRFUNC4( SetStreamSource, UINT, StreamNumber, IDirect3DVertexBuffer9*, pStreamData, UINT, OffsetInBytes, UINT, Stride );
     STDREDIRFUNC2( SetStreamSourceFreq, UINT, StreamNumber, UINT, Divider );
     STDREDIRFUNC1( SetVertexDeclaration, IDirect3DVertexDeclaration9*, pDecl );
     STDREDIRFUNC1( SetIndices, IDirect3DIndexBuffer9*, pIndexData );
     STDREDIRFUNC0( TestCooperativeLevel );
     STDREDIRFUNC0( EvictManagedResources );
     STDREDIRFUNC0( BeginScene );
     STDREDIRFUNC0( EndScene );
     STDREDIRFUNC0( BeginStateBlock );
     STDREDIRFUNC1( EndStateBlock, IDirect3DStateBlock9**, ppSB );
     STDREDIRFUNC1( GetDirect3D, IDirect3D9**, ppD3D9 );
     /*** These methods can be recorded but without a way to retain the return value I do not see why your would use them */
     STDREDIRFUNC3( SetCursorProperties, UINT, XHotSpot, UINT, YHotSpot, IDirect3DSurface9*, pCursorBitmap );
     REDIRFUNC3(void, SetCursorPosition, int, X, int, Y, DWORD, Flags);
     STDREDIRFUNC1( SetDialogBoxMode, BOOL, bEnableDialogs );
     STDREDIRFUNC1( GetDeviceCaps, D3DCAPS9*, pCaps );
     STDREDIRFUNC2( GetDisplayMode, UINT, iSwapChain, D3DDISPLAYMODE*, pMode );
     STDREDIRFUNC1( GetCreationParameters, D3DDEVICE_CREATION_PARAMETERS*, pParameters );
     STDREDIRFUNC2( CreateAdditionalSwapChain, D3DPRESENT_PARAMETERS*, pPresentationParameters, IDirect3DSwapChain9**,  pSwapChain );
     STDREDIRFUNC2( GetSwapChain, UINT, iSwapChain, IDirect3DSwapChain9**,  pSwapChain );
     STDREDIRFUNC1( Reset, D3DPRESENT_PARAMETERS*, pPresentationParameters );
     STDREDIRFUNC4( Present, CONST RECT*, pSourceRect, CONST RECT*, pDestRect, HWND, hDestWindowOverride, CONST RGNDATA*, pDirtyRegion );
     STDREDIRFUNC4( GetBackBuffer, UINT, iSwapChain, UINT, iBackBuffer, D3DBACKBUFFER_TYPE, Type, IDirect3DSurface9**, ppBackBuffer );
     STDREDIRFUNC2( GetRasterStatus, UINT, iSwapChain, D3DRASTER_STATUS*, pRasterStatus );
     REDIRFUNC3(void, SetGammaRamp, UINT, iSwapChain, DWORD, Flags, CONST D3DGAMMARAMP*, pRamp);
     REDIRFUNC2(void, GetGammaRamp, UINT, iSwapChain, D3DGAMMARAMP*, pRamp);
     STDREDIRFUNC8( CreateTexture, UINT, Width, UINT, Height, UINT, Levels, DWORD, Usage, D3DFORMAT, Format, D3DPOOL, Pool, IDirect3DTexture9**,  ppTexture, HANDLE*, pSharedHandle );
     STDREDIRFUNC9( CreateVolumeTexture, UINT, Width, UINT, Height, UINT, Depth, UINT, Levels, DWORD, Usage,D3DFORMAT, Format, D3DPOOL, Pool, IDirect3DVolumeTexture9**, ppVolumeTexture, HANDLE*, pSharedHandle );
     STDREDIRFUNC7( CreateCubeTexture, UINT, EdgeLength, UINT, Levels, DWORD, Usage, D3DFORMAT, Format, D3DPOOL, Pool, IDirect3DCubeTexture9**,  ppCubeTexture, HANDLE*, pSharedHandle );
     STDREDIRFUNC6( CreateVertexBuffer, UINT, Length, DWORD, Usage, DWORD, FVF, D3DPOOL, Pool, IDirect3DVertexBuffer9**, ppVertexBuffer, HANDLE*, pSharedHandle );
     STDREDIRFUNC6( CreateIndexBuffer, UINT, Length, DWORD, Usage, D3DFORMAT, Format, D3DPOOL, Pool, IDirect3DIndexBuffer9**, ppIndexBuffer, HANDLE*, pSharedHandle );
     STDREDIRFUNC8( CreateRenderTarget, UINT, Width, UINT, Height, D3DFORMAT, Format, D3DMULTISAMPLE_TYPE, MultiSample, DWORD, MultisampleQuality, BOOL, Lockable, IDirect3DSurface9**, ppSurface, HANDLE*, pSharedHandle );
     STDREDIRFUNC8( CreateDepthStencilSurface, UINT, Width, UINT, Height, D3DFORMAT, Format, D3DMULTISAMPLE_TYPE, MultiSample, DWORD, MultisampleQuality, BOOL, Discard, IDirect3DSurface9**, ppSurface, HANDLE*, pSharedHandle );
     STDREDIRFUNC4( UpdateSurface, IDirect3DSurface9*, pSourceSurface, CONST RECT*, pSourceRect, IDirect3DSurface9*, pDestinationSurface, CONST POINT*, pDestPoint );
     STDREDIRFUNC2( UpdateTexture, IDirect3DBaseTexture9*, pSourceTexture, IDirect3DBaseTexture9*, pDestinationTexture );
     STDREDIRFUNC2( GetRenderTargetData, IDirect3DSurface9*, pRenderTarget, IDirect3DSurface9*, pDestSurface );
     STDREDIRFUNC2( GetFrontBufferData, UINT, iSwapChain, IDirect3DSurface9*, pDestSurface );
     STDREDIRFUNC5( StretchRect, IDirect3DSurface9*, pSourceSurface, CONST RECT*, pSourceRect, IDirect3DSurface9*, pDestSurface, CONST RECT*, pDestRect, D3DTEXTUREFILTERTYPE, Filter );
     STDREDIRFUNC3( ColorFill, IDirect3DSurface9*, pSurface, CONST RECT*, pRect, D3DCOLOR, color );
     STDREDIRFUNC6( CreateOffscreenPlainSurface, UINT, Width, UINT, Height, D3DFORMAT, Format, D3DPOOL, Pool, IDirect3DSurface9**, ppSurface, HANDLE*, pSharedHandle );
     STDREDIRFUNC2( SetRenderTarget, DWORD, RenderTargetIndex, IDirect3DSurface9*, pRenderTarget );
     STDREDIRFUNC2( GetRenderTarget, DWORD, RenderTargetIndex, IDirect3DSurface9**, ppRenderTarget );
     STDREDIRFUNC1( SetDepthStencilSurface, IDirect3DSurface9*, pNewZStencil );
     STDREDIRFUNC1( GetDepthStencilSurface, IDirect3DSurface9**,  ppZStencilSurface );
     STDREDIRFUNC6( Clear, DWORD, Count, CONST D3DRECT*, pRects, DWORD, Flags, D3DCOLOR, Color, float, Z, DWORD, Stencil );
     STDREDIRFUNC2( SetTransform, D3DTRANSFORMSTATETYPE, State, CONST D3DMATRIX*, pMatrix );
     STDREDIRFUNC2( GetTransform, D3DTRANSFORMSTATETYPE, State,D3DMATRIX*, pMatrix );
     STDREDIRFUNC2( MultiplyTransform, D3DTRANSFORMSTATETYPE,  type, CONST D3DMATRIX*, pMatrix );
     STDREDIRFUNC1( SetViewport, CONST D3DVIEWPORT9*, pViewport );
     STDREDIRFUNC1( GetViewport, D3DVIEWPORT9*, pViewport );
     STDREDIRFUNC1( SetMaterial, CONST D3DMATERIAL9*, pMaterial );
     STDREDIRFUNC1( GetMaterial, D3DMATERIAL9*, pMaterial );
     STDREDIRFUNC2( SetLight, DWORD, Index ,CONST D3DLIGHT9*, pLight );
     STDREDIRFUNC2( GetLight, DWORD, Index, D3DLIGHT9*, pLight );
     STDREDIRFUNC2( LightEnable, DWORD, Index, BOOL, Enable );
     STDREDIRFUNC2( GetLightEnable, DWORD, Index, BOOL*, pEnable );
     STDREDIRFUNC2( SetClipPlane, DWORD, Index, CONST float*, pPlane );
     STDREDIRFUNC2( GetClipPlane, DWORD, Index, float*, pPlane );
     STDREDIRFUNC2( SetRenderState, D3DRENDERSTATETYPE, State, DWORD, Value );
     STDREDIRFUNC2( GetRenderState, D3DRENDERSTATETYPE, State, DWORD*, pValue );
     STDREDIRFUNC2( CreateStateBlock, D3DSTATEBLOCKTYPE, Type, IDirect3DStateBlock9**,  ppSB );
     STDREDIRFUNC1( SetClipStatus, CONST D3DCLIPSTATUS9*, pClipStatus );
     STDREDIRFUNC1( GetClipStatus, D3DCLIPSTATUS9*, pClipStatus );
     STDREDIRFUNC2( GetTexture, DWORD, Stage, IDirect3DBaseTexture9**,  ppTexture );
     STDREDIRFUNC2( SetTexture, DWORD, Stage, IDirect3DBaseTexture9*, pTexture );
     STDREDIRFUNC3( GetTextureStageState, DWORD, Stage, D3DTEXTURESTAGESTATETYPE, Type, DWORD*, pValue );
     STDREDIRFUNC3( SetTextureStageState, DWORD, Stage, D3DTEXTURESTAGESTATETYPE, Type, DWORD, Value );
     STDREDIRFUNC3( GetSamplerState, DWORD, Sampler, D3DSAMPLERSTATETYPE, Type, DWORD*, pValue );
     STDREDIRFUNC3( SetSamplerState, DWORD, Sampler, D3DSAMPLERSTATETYPE, Type, DWORD, Value );
     STDREDIRFUNC1( ValidateDevice, DWORD*, pNumPasses );
     STDREDIRFUNC2( SetPaletteEntries, UINT, PaletteNumber, CONST PALETTEENTRY*, pEntries );
     STDREDIRFUNC2( GetPaletteEntries, UINT, PaletteNumber, PALETTEENTRY*, pEntries );
     STDREDIRFUNC1( SetCurrentTexturePalette, UINT, PaletteNumber );
     STDREDIRFUNC1( GetCurrentTexturePalette, UINT*, PaletteNumber );
     STDREDIRFUNC1( SetScissorRect, CONST RECT*, pRect );
     STDREDIRFUNC1( GetScissorRect, RECT*, pRect );
     STDREDIRFUNC1( SetSoftwareVertexProcessing, BOOL, bSoftware );
     STDREDIRFUNC1( SetNPatchMode, float, nSegments);
     STDREDIRFUNC4( DrawPrimitiveUP, D3DPRIMITIVETYPE, PrimitiveType, UINT, PrimitiveCount, CONST void*, pVertexStreamZeroData, UINT, VertexStreamZeroStride );
     STDREDIRFUNC8( DrawIndexedPrimitiveUP, D3DPRIMITIVETYPE, PrimitiveType, UINT, MinVertexIndex, UINT, NumVertices, UINT, PrimitiveCount, CONST void*, pIndexData, D3DFORMAT, IndexDataFormat, CONST void*, pVertexStreamZeroData, UINT, VertexStreamZeroStride );
     STDREDIRFUNC6( ProcessVertices, UINT, SrcStartIndex, UINT, DestIndex, UINT, VertexCount, IDirect3DVertexBuffer9*, pDestBuffer, IDirect3DVertexDeclaration9*, pVertexDecl, DWORD, Flags );
     STDREDIRFUNC2( CreateVertexDeclaration, CONST D3DVERTEXELEMENT9*, pVertexElements, IDirect3DVertexDeclaration9**,  ppDecl );
     STDREDIRFUNC1( GetVertexDeclaration, IDirect3DVertexDeclaration9**,  ppDecl );
     STDREDIRFUNC1( SetFVF, DWORD, FVF );
     STDREDIRFUNC1( GetFVF, DWORD*, pFVF );
     STDREDIRFUNC2( CreateVertexShader, CONST DWORD*, pFunction, IDirect3DVertexShader9**,  ppShader );
     STDREDIRFUNC1( SetVertexShader, IDirect3DVertexShader9*, pShader );
     STDREDIRFUNC1( GetVertexShader, IDirect3DVertexShader9**,  ppShader );
     STDREDIRFUNC3( SetVertexShaderConstantF, UINT, StartRegister, CONST float*, pConstantData, UINT, Vector4fCount );
     STDREDIRFUNC3( GetVertexShaderConstantF, UINT, StartRegister, float*, pConstantData, UINT, Vector4fCount );
     STDREDIRFUNC3( SetVertexShaderConstantI, UINT, StartRegister, CONST int*, pConstantData, UINT, Vector4iCount );
     STDREDIRFUNC3( GetVertexShaderConstantI, UINT, StartRegister, int*, pConstantData, UINT, Vector4iCount );
     STDREDIRFUNC3( SetVertexShaderConstantB, UINT, StartRegister, CONST BOOL*, pConstantData, UINT, BoolCount );
     STDREDIRFUNC3( GetVertexShaderConstantB, UINT, StartRegister, BOOL*, pConstantData, UINT, BoolCount );
     STDREDIRFUNC4( GetStreamSource, UINT, StreamNumber, IDirect3DVertexBuffer9**, ppStreamData, UINT*, OffsetInBytes, UINT*, pStride );
     STDREDIRFUNC2( GetStreamSourceFreq, UINT, StreamNumber, UINT*, Divider );
     STDREDIRFUNC1( GetIndices, IDirect3DIndexBuffer9**, ppIndexData );
     STDREDIRFUNC2( CreatePixelShader, CONST DWORD*, pFunction, IDirect3DPixelShader9**, ppShader );
     STDREDIRFUNC1( SetPixelShader, IDirect3DPixelShader9*, pShader );
     STDREDIRFUNC1( GetPixelShader, IDirect3DPixelShader9**, ppShader );
     STDREDIRFUNC3( SetPixelShaderConstantF, UINT, StartRegister, CONST float*, pConstantData, UINT, Vector4fCount );
     STDREDIRFUNC3( GetPixelShaderConstantF, UINT, StartRegister, float*, pConstantData, UINT, Vector4fCount );
     STDREDIRFUNC3( SetPixelShaderConstantI, UINT, StartRegister, CONST int*, pConstantData, UINT, Vector4iCount );
     STDREDIRFUNC3( GetPixelShaderConstantI, UINT, StartRegister, int*, pConstantData, UINT, Vector4iCount );
     STDREDIRFUNC3( SetPixelShaderConstantB, UINT, StartRegister ,CONST BOOL*, pConstantData, UINT, BoolCount );
     STDREDIRFUNC3( GetPixelShaderConstantB, UINT, StartRegister ,BOOL*, pConstantData, UINT, BoolCount );
     STDREDIRFUNC3( DrawRectPatch, UINT, Handle, CONST float*, pNumSegs, CONST D3DRECTPATCH_INFO*, pRectPatchInfo );
     STDREDIRFUNC3( DrawTriPatch, UINT, Handle, CONST float*, pNumSegs, CONST D3DTRIPATCH_INFO*, pTriPatchInfo );
     STDREDIRFUNC1( DeletePatch, UINT, Handle );
     STDREDIRFUNC2( CreateQuery, D3DQUERYTYPE, Type, IDirect3DQuery9**, ppQuery );
    
     /*** IDirect3DDevice methods that cannot be recorded which throw errors */
     REDIRFUNC0(UINT, GetAvailableTextureMem);
     REDIRFUNC0(UINT, GetNumberOfSwapChains);
     REDIRFUNC1(BOOL, ShowCursor, BOOL, bShow);
     REDIRFUNC0(BOOL, GetSoftwareVertexProcessing);
     REDIRFUNC0(float, GetNPatchMode);
 
     /*** Unimplemented IDirect3DDevice9 methods ***/
 };

 
//----------------------------------------------------------------------------
// ID3DXEffectStateManager:
// ------------------------
// This is a user implemented interface that can be used to manage device 
// state changes made by an Effect.
//----------------------------------------------------------------------------

//typedef interface ID3DXEffectStateManager ID3DXEffectStateManager;
//typedef interface ID3DXEffectStateManager *LPD3DXEFFECTSTATEMANAGER;


class RedirectingEffectStateManager : public ID3DXEffectStateManager
{
public:
    // The user must correctly implement QueryInterface, AddRef, and Release.
    RedirectingEffectStateManager(IDirect3DDevice9 *pDevice){ pCurrentDevice = pDevice; dwRefCount= 1; bTrace = false; }
    ~RedirectingEffectStateManager(){ Release(); }
    IDirect3DDevice9 *pCurrentDevice;
    bool bTrace;

    DWORD dwRefCount;
    void SetTrace(bool bval)
    {
        bTrace = bval; 
    }
    // IUnknown
    HRESULT __stdcall QueryInterface( REFIID iid, LPVOID *ppv){ return pCurrentDevice->QueryInterface(iid,ppv); } 
    ULONG __stdcall AddRef() 
    { 
        dwRefCount++;
        ULONG ret = max( 0 , dwRefCount );
        return ret;
    }
    ULONG __stdcall Release() 
    { 
        dwRefCount--;
        ULONG ret = max( 0 , dwRefCount );
        return ret;
    }

    // The following methods are called by the Effect when it wants to make 
    // the corresponding device call.  Note that:
    // 1. Users manage the state and are therefore responsible for making the 
    //    the corresponding device calls themselves inside their callbacks.  
    // 2. Effects pay attention to the return values of the callbacks, and so 
    //    users must pay attention to what they return in their callbacks.

    STDREDIRFUNC2(SetTransform, D3DTRANSFORMSTATETYPE, State, CONST D3DMATRIX*, pMatrix);
    STDREDIRFUNC1(SetMaterial, CONST D3DMATERIAL9 *, pMaterial);
    STDREDIRFUNC2(SetLight, DWORD, Index, CONST D3DLIGHT9*, pLight);
    STDREDIRFUNC2(LightEnable, DWORD, Index, BOOL, Enable);
    STDREDIRFUNC2(SetRenderState, D3DRENDERSTATETYPE, State, DWORD, Value);
    STDREDIRFUNC2(SetTexture, DWORD, Stage, LPDIRECT3DBASETEXTURE9, pTexture);
    STDREDIRFUNC3(SetTextureStageState, DWORD, Stage, D3DTEXTURESTAGESTATETYPE, Type, DWORD, Value);
    STDREDIRFUNC3(SetSamplerState, DWORD, Sampler, D3DSAMPLERSTATETYPE, Type, DWORD, Value);
    STDREDIRFUNC1(SetNPatchMode, FLOAT, NumSegments);
    STDREDIRFUNC1(SetFVF, DWORD, FVF);
    STDREDIRFUNC1(SetVertexShader, LPDIRECT3DVERTEXSHADER9, pShader);
    STDREDIRFUNC3(SetVertexShaderConstantF, UINT, RegisterIndex, CONST FLOAT*, pConstantData, UINT, RegisterCount);
    STDREDIRFUNC3(SetVertexShaderConstantI, UINT, RegisterIndex, CONST INT*, pConstantData, UINT, RegisterCount);
    STDREDIRFUNC3(SetVertexShaderConstantB, UINT, RegisterIndex, CONST BOOL*, pConstantData, UINT, RegisterCount);
    STDREDIRFUNC1(SetPixelShader, LPDIRECT3DPIXELSHADER9, pShader);
    STDREDIRFUNC3(SetPixelShaderConstantF, UINT, RegisterIndex, CONST FLOAT*, pConstantData, UINT, RegisterCount);
    STDREDIRFUNC3(SetPixelShaderConstantI, UINT, RegisterIndex, CONST INT*, pConstantData, UINT, RegisterCount);
    STDREDIRFUNC3(SetPixelShaderConstantB, UINT, RegisterIndex, CONST BOOL*, pConstantData, UINT, RegisterCount);
};

#endif
