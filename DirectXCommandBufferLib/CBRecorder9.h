// Open source.
// See Vincent Scheib rant at http://beautifulpixels.blogspot.com/2008/07/parallel-rendering-with-directx-command.html

#pragma once

#ifndef CBD3D_PREPROCESSING

#include "CBMemoryBuffer.h"
#include "PREPROCESSED_CBRecorder9.h"

#else // CBD3D_PREPROCESSING is defined

#include "CBMacros.h"

class CBRecorder9 : public IDirect3DDevice9
{
public:
    CBRecorder9(): m_pCB(nullptr) {}

    void SetCommandBuffer(CBMemoryBuffer* pCB) { m_pCB = pCB; }

    HRESULT BeginCommandBuffer()
    {
#if MARKMEMORYBUFFERS
        DWORD* pMem;
        UINT iNumDWORDs;
        m_pCB->GetCBMemory(pMem,iNumDWORDs);

        if(*pMem != 0)
        {
            OutputDebugStringA("ERROR a memory buffer in use is being recorded!\n");
            return E_FAIL;
        }
#endif
        m_pCB->ResetNext();
        return D3D_OK;
    }

    HRESULT EndCommandBuffer()
    {
        if(m_pCB->CheckAvailableMemorySize(1))
        {
            m_pCB->PutDWORD(CBD3D_COMMANDS::NULLCALL);
            return D3D_OK;
        }

        return E_OUTOFMEMORY;
    }

    
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)( REFIID riid, void** ppvObj) CBD3D_D3DERR_NOTIMPLIMENTED; 
    STDRECORDWITHRETURNFUNC0( ULONG , 1 , AddRef  )
    STDRECORDWITHRETURNFUNC0( ULONG , 1 , Release  )

    /*** Implemnted IDirect3DDevice9 methods ***/
    /* Note that it is assumed that input values will be valid a record time. */
    /* Also there is no mechnism to retain returned values during playback     */  

    
    STDRECORDFUNC3( DrawPrimitive , D3DPRIMITIVETYPE , PrimitiveType, UINT , StartVertex , UINT , PrimitiveCount)
    STDRECORDFUNC6( DrawIndexedPrimitive , D3DPRIMITIVETYPE , PrimitiveType , INT , BaseVertexIndex , UINT , MinVertexIndex , UINT , NumVertices , UINT, startIndex ,UINT , primCount )
    STDRECORDFUNC4( SetStreamSource , UINT , StreamNumber , IDirect3DVertexBuffer9* , pStreamData , UINT , OffsetInBytes , UINT , Stride );  
    STDRECORDFUNC2( SetStreamSourceFreq , UINT , StreamNumber, UINT , Divider );
    STDRECORDFUNC1( SetVertexDeclaration , IDirect3DVertexDeclaration9* , pDecl )
    STDRECORDFUNC1( SetIndices , IDirect3DIndexBuffer9* , pIndexData )
    STDRECORDFUNC0( TestCooperativeLevel  )
    STDRECORDFUNC0( EvictManagedResources  )
    STDRECORDFUNC0( BeginScene  )
    STDRECORDFUNC0( EndScene  )
    STDRECORDFUNC0( BeginStateBlock  )
    STDRECORDFUNC3( SetCursorProperties , UINT , XHotSpot , UINT , YHotSpot , IDirect3DSurface9* , pCursorBitmap )
    STDRECORDFUNC1( SetDialogBoxMode , BOOL , bEnableDialogs )
    STDRECORDFUNC1( Reset , D3DPRESENT_PARAMETERS* , pPresentationParameters )
    STDRECORDFUNC4( Present , CONST RECT* , pSourceRect , CONST RECT* , pDestRect , HWND , hDestWindowOverride , CONST RGNDATA* , pDirtyRegion )
    STDRECORDFUNC4( UpdateSurface , IDirect3DSurface9* , pSourceSurface , CONST RECT* , pSourceRect, IDirect3DSurface9* , pDestinationSurface , CONST POINT* , pDestPoint )
    STDRECORDFUNC2( UpdateTexture , IDirect3DBaseTexture9* , pSourceTexture , IDirect3DBaseTexture9* , pDestinationTexture )
    STDRECORDFUNC5( StretchRect , IDirect3DSurface9* , pSourceSurface , CONST RECT* , pSourceRect , IDirect3DSurface9* , pDestSurface , CONST RECT* , pDestRect , D3DTEXTUREFILTERTYPE , Filter )
    STDRECORDFUNC3( ColorFill , IDirect3DSurface9* , pSurface , CONST RECT* , pRect , D3DCOLOR , color )
    STDRECORDFUNC2( SetRenderTarget , DWORD , RenderTargetIndex , IDirect3DSurface9* , pRenderTarget )
    STDRECORDFUNC1( SetDepthStencilSurface , IDirect3DSurface9* , pNewZStencil )
    STDRECORDFUNC6( Clear , DWORD , Count , CONST D3DRECT* , pRects , DWORD , Flags , D3DCOLOR , Color , float , Z , DWORD , Stencil )
    STDRECORDFUNC2( SetTransform , D3DTRANSFORMSTATETYPE , State , CONST D3DMATRIX* , pMatrix )
    STDRECORDFUNC2( MultiplyTransform , D3DTRANSFORMSTATETYPE,  type , CONST D3DMATRIX*, pMatrix )
    STDRECORDFUNC1( SetViewport , CONST D3DVIEWPORT9* , pViewport )
    STDRECORDFUNC1( SetMaterial , CONST D3DMATERIAL9* , pMaterial )
    STDRECORDFUNC2( SetLight , DWORD , Index ,CONST D3DLIGHT9* , pLight )
    STDRECORDFUNC2( LightEnable , DWORD , Index , BOOL , Enable )
    STDRECORDFUNC2( SetClipPlane , DWORD , Index , CONST float* , pPlane )
    STDRECORDFUNC2( SetRenderState , D3DRENDERSTATETYPE , State , DWORD , Value )
    STDRECORDFUNC1( EndStateBlock , IDirect3DStateBlock9** , ppSB )
    STDRECORDFUNC1( SetClipStatus , CONST D3DCLIPSTATUS9* , pClipStatus )
    STDRECORDFUNC2( SetTexture , DWORD , Stage , IDirect3DBaseTexture9* , pTexture )
    STDRECORDFUNC3( SetTextureStageState , DWORD , Stage , D3DTEXTURESTAGESTATETYPE , Type , DWORD  , Value )
    STDRECORDFUNC3( SetSamplerState , DWORD , Sampler , D3DSAMPLERSTATETYPE , Type , DWORD , Value )
    STDRECORDFUNC1( ValidateDevice , DWORD* , pNumPasses )
    STDRECORDFUNC2( SetPaletteEntries , UINT , PaletteNumber , CONST PALETTEENTRY* , pEntries )
    STDRECORDFUNC1( SetCurrentTexturePalette , UINT , PaletteNumber )
    STDRECORDFUNC1( SetScissorRect , CONST RECT* , pRect )
    STDRECORDFUNC1( SetSoftwareVertexProcessing , BOOL , bSoftware )
    STDRECORDFUNC1( SetNPatchMode , float , nSegments)
    STDRECORDFUNC4( DrawPrimitiveUP , D3DPRIMITIVETYPE , PrimitiveType , UINT , PrimitiveCount , CONST void* , pVertexStreamZeroData , UINT , VertexStreamZeroStride )
    STDRECORDFUNC8( DrawIndexedPrimitiveUP , D3DPRIMITIVETYPE , PrimitiveType, UINT , MinVertexIndex, UINT , NumVertices, UINT , PrimitiveCount , CONST void* , pIndexData , D3DFORMAT , IndexDataFormat , CONST void* , pVertexStreamZeroData , UINT , VertexStreamZeroStride )
    STDRECORDFUNC6( ProcessVertices , UINT , SrcStartIndex , UINT , DestIndex, UINT , VertexCount , IDirect3DVertexBuffer9* , pDestBuffer , IDirect3DVertexDeclaration9* , pVertexDecl , DWORD , Flags )
    STDRECORDFUNC1( SetFVF , DWORD , FVF )
    STDRECORDFUNC1( SetVertexShader , IDirect3DVertexShader9* , pShader )
    STDRECORDFUNC1( SetPixelShader , IDirect3DPixelShader9* , pShader )
    STDRECORDFUNC3( DrawRectPatch , UINT , Handle , CONST float* , pNumSegs , CONST D3DRECTPATCH_INFO* , pRectPatchInfo )
    STDRECORDFUNC3( DrawTriPatch , UINT , Handle , CONST float* , pNumSegs , CONST D3DTRIPATCH_INFO* , pTriPatchInfo )
    STDRECORDFUNC1( DeletePatch , UINT , Handle )
    STDRECORDVOIDFUNC3( SetGammaRamp , UINT , iSwapChain , DWORD , Flags , CONST D3DGAMMARAMP* , pRamp)
    STDRECORDVOIDFUNC3( SetCursorPosition , int , X , int , Y , DWORD , Flags)


    /*** IDirect3DDevice methods that cannot be recorded which throw errors *///


    STDMETHOD_(BOOL , ShowCursor ) ( BOOL  bShow )CBD3D_BOOL_NOTIMPLIMENTED;
    STDMETHOD_(UINT, GetAvailableTextureMem)(THIS) CBD3D_UINT_NOTIMPLIMENTED;
    STDMETHOD_(UINT, GetNumberOfSwapChains)(THIS) CBD3D_UINT_NOTIMPLIMENTED;
    STDMETHOD_(BOOL, GetSoftwareVertexProcessing)(THIS) CBD3D_BOOL_NOTIMPLIMENTED;
    STDMETHOD_(float, GetNPatchMode)(THIS) CBD3D_FLOAT_NOTIMPLIMENTED;
    STDMETHOD_(void, GetGammaRamp)( UINT iSwapChain , D3DGAMMARAMP* pRamp) CBD3D_VOID_NOTIMPLIMENTED;
    STDMETHOD( GetSwapChain ) (  UINT iSwapChain , IDirect3DSwapChain9**  pSwapChain ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetDeviceCaps ) (  LPD3DCAPS9  pCaps ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetDisplayMode ) (  UINT iSwapChain , D3DDISPLAYMODE* pMode ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetCreationParameters ) (  D3DDEVICE_CREATION_PARAMETERS* pParameters ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetBackBuffer ) (  UINT iSwapChain , UINT iBackBuffer , D3DBACKBUFFER_TYPE Type , IDirect3DSurface9** ppBackBuffer ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetRasterStatus ) (  UINT iSwapChain , D3DRASTER_STATUS* pRasterStatus ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetPaletteEntries ) (  UINT PaletteNumber , PALETTEENTRY* pEntries ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetRenderTargetData ) (  IDirect3DSurface9* pRenderTarget , IDirect3DSurface9* pDestSurface ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetFrontBufferData ) (  UINT iSwapChain , IDirect3DSurface9* pDestSurface ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetRenderTarget ) (  DWORD RenderTargetIndex , IDirect3DSurface9** ppRenderTarget ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetDepthStencilSurface ) (  IDirect3DSurface9**  ppZStencilSurface ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetTransform ) (  D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetViewport ) (  D3DVIEWPORT9* pViewport ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetMaterial ) (  D3DMATERIAL9* pMaterial ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetLightEnable ) (  DWORD Index , BOOL* pEnable ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetLight ) (  DWORD Index , D3DLIGHT9* pLight ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetClipPlane ) (  DWORD Index , float* pPlane ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetRenderState ) (  D3DRENDERSTATETYPE State , DWORD* pValue ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetClipStatus ) (  D3DCLIPSTATUS9* pClipStatus ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetTexture ) (  DWORD Stage , IDirect3DBaseTexture9**  ppTexture ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetTextureStageState ) (  DWORD Stage , D3DTEXTURESTAGESTATETYPE Type , DWORD* pValue ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetSamplerState ) (  DWORD Sampler , D3DSAMPLERSTATETYPE Type , DWORD* pValue ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetCurrentTexturePalette ) (  UINT *PaletteNumber ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetScissorRect ) (  RECT* pRect ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetVertexDeclaration ) (  IDirect3DVertexDeclaration9**  ppDecl ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetFVF ) (  DWORD* pFVF ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetPixelShader ) (  IDirect3DPixelShader9** ppShader ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetVertexShader ) (  IDirect3DVertexShader9**  ppShader ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetStreamSource ) (  UINT StreamNumber , IDirect3DVertexBuffer9** ppStreamData , LPUINT  OffsetInBytes , LPUINT  pStride ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetStreamSourceFreq ) (  UINT StreamNumber , LPUINT  Divider ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetIndices ) (  IDirect3DIndexBuffer9** ppIndexData ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( CreateQuery ) (  D3DQUERYTYPE Type , IDirect3DQuery9** ppQuery ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetDirect3D ) (  IDirect3D9** ppD3D9 ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD(GetVertexShaderConstantF) ( UINT  StartRegister, float*  pConstantData , UINT  Vector4fCount ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetVertexShaderConstantI) ( UINT  StartRegister, int*  pConstantData , UINT  Vector4iCount  ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetVertexShaderConstantB) (UINT  StartRegister, BOOL*  pConstantData , UINT  BoolCount  ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetPixelShaderConstantF) (UINT  StartRegister , float*  pConstantData, UINT  Vector4fCount ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetPixelShaderConstantI) (UINT  StartRegister , int*  pConstantData , UINT  Vector4iCount ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( GetPixelShaderConstantB) (UINT  StartRegister ,BOOL*  pConstantData , UINT  BoolCount ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( CreateAdditionalSwapChain ) (  D3DPRESENT_PARAMETERS* pPresentationParameters , IDirect3DSwapChain9**  pSwapChain ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( CreateTexture ) (  UINT Width, UINT Height, UINT Levels , DWORD Usage , D3DFORMAT Format , D3DPOOL Pool , IDirect3DTexture9**  ppTexture , HANDLE* pSharedHandle ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( CreateVolumeTexture ) (  UINT Width , UINT Height , UINT Depth , UINT Levels , DWORD Usage , D3DFORMAT Format , D3DPOOL Pool , IDirect3DVolumeTexture9** ppVolumeTexture , HANDLE* pSharedHandle ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( CreateCubeTexture ) (  UINT EdgeLength , UINT Levels , DWORD Usage , D3DFORMAT Format , D3DPOOL Pool , IDirect3DCubeTexture9**  ppCubeTexture , HANDLE* pSharedHandle ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( CreateVertexBuffer ) (  UINT Length , DWORD Usage , DWORD FVF , D3DPOOL Pool , IDirect3DVertexBuffer9** ppVertexBuffer , HANDLE* pSharedHandle ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( CreateIndexBuffer ) (  UINT Length , DWORD Usage , D3DFORMAT Format , D3DPOOL Pool , IDirect3DIndexBuffer9** ppIndexBuffer , HANDLE* pSharedHandle ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( CreateRenderTarget ) (  UINT Width, UINT Height , D3DFORMAT Format , D3DMULTISAMPLE_TYPE MultiSample , DWORD MultisampleQuality , BOOL Lockable , IDirect3DSurface9** ppSurface , HANDLE* pSharedHandle ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( CreateDepthStencilSurface ) (  UINT Width , UINT Height , D3DFORMAT Format , D3DMULTISAMPLE_TYPE MultiSample , DWORD MultisampleQuality , BOOL Discard , IDirect3DSurface9** ppSurface , HANDLE* pSharedHandle ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( CreateOffscreenPlainSurface ) (  UINT Width , UINT Height , D3DFORMAT Format , D3DPOOL Pool , IDirect3DSurface9** ppSurface , HANDLE* pSharedHandle ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( CreateStateBlock ) (  D3DSTATEBLOCKTYPE Type , IDirect3DStateBlock9**  ppSB ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( CreateVertexDeclaration ) (  CONST D3DVERTEXELEMENT9* pVertexElements , IDirect3DVertexDeclaration9**  ppDecl ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( CreateVertexShader ) (  CONST DWORD* pFunction , IDirect3DVertexShader9**  ppShader ) CBD3D_D3DERR_NOTIMPLIMENTED;
    STDMETHOD( CreatePixelShader ) (  CONST DWORD* pFunction , IDirect3DPixelShader9** ppShader ) CBD3D_D3DERR_NOTIMPLIMENTED;


    /***IDirect3DDevice9 methods that write variable sized objects***/

    STDRECORDSETCONSTS( SetVertexShaderConstantF , UINT , StartRegister , CONST float* , pConstantData , UINT , Vector4fCount , float )
    STDRECORDSETCONSTS( SetVertexShaderConstantI , UINT , StartRegister, CONST int* , pConstantData , UINT , Vector4iCount , int )
    STDRECORDSETCONSTS( SetVertexShaderConstantB , UINT , StartRegister, CONST BOOL* , pConstantData , UINT , BoolCount , BOOL )
    STDRECORDSETCONSTS( SetPixelShaderConstantF , UINT , StartRegister , CONST float* , pConstantData , UINT , Vector4fCount , float )
    STDRECORDSETCONSTS( SetPixelShaderConstantI , UINT , StartRegister , CONST int* , pConstantData , UINT , Vector4iCount , int )
    STDRECORDSETCONSTS( SetPixelShaderConstantB , UINT , StartRegister ,CONST BOOL* , pConstantData , UINT , BoolCount , BOOL )

protected:
    CBMemoryBuffer* m_pCB;
};
#endif // CBD3D_PREPROCESSING is defined