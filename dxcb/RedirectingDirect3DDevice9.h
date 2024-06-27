// Open source.
// See Vincent Scheib rant at
// http://beautifulpixels.blogspot.com/2008/07/parallel-rendering-with-directx-command.html

#ifndef DXCB_REDIRECTING_DIRECT3D_DEVICE9_H_
#define DXCB_REDIRECTING_DIRECT3D_DEVICE9_H_

#ifndef DXCB_INVOKE_PREPROCESSOR

#include <d3d9.h>
#include <d3dx9effect.h>

#include <algorithm>
#include <atomic>

#include "PREPROCESSED_RedirectingDirect3DDevice9.h"

#else  // DXCB_INVOKE_PREPROCESSOR

#define DXCB_BUILTIN_TRACE 1

#if DXCB_BUILTIN_TRACE
#define DXCB_TRACE_FUNC9(returntype, methodname, type1, arg1, type2, arg2,    \
                         type3, arg3, type4, arg4, type5, arg5, type6, arg6,  \
                         type7, arg7, type8, arg8, type9, arg9)               \
  if (should_trace_) {                                                        \
    char strTrace[700];                                                       \
    sprintf_s(                                                                \
        strTrace,                                                             \
        "%s %s (%s  0x%zx, %s  0x%zx, %s  0x%zx, %s  0x%zx, %s  0x%zx, %s  "  \
        "0x%zx, %s  0x%zx, %s  0x%zx, %s  0x%zx)\n",                          \
        #returntype, #methodname, #type1, (size_t)arg1, #type2, (size_t)arg2, \
        #type3, (size_t)arg3, #type4, (size_t)arg4, #type5, (size_t)arg5,     \
        #type6, (size_t)arg6, #type7, (size_t)arg7, #type8, (size_t)arg8,     \
        #type9, (size_t)arg9);                                                \
    OutputDebugStringA(strTrace);                                             \
  }

#define DXCB_TRACE_FUNC8(returntype, methodname, type1, arg1, type2, arg2,    \
                         type3, arg3, type4, arg4, type5, arg5, type6, arg6,  \
                         type7, arg7, type8, arg8)                            \
  if (should_trace_) {                                                        \
    char strTrace[700];                                                       \
    sprintf_s(                                                                \
        strTrace,                                                             \
        "%s %s (%s  0x%zx, %s  0x%zx, %s  0x%zx, %s  0x%zx, %s  0x%zx, %s  "  \
        "0x%zx, %s  0x%zx, %s  0x%zx)\n",                                     \
        #returntype, #methodname, #type1, (size_t)arg1, #type2, (size_t)arg2, \
        #type3, (size_t)arg3, #type4, (size_t)arg4, #type5, (size_t)arg5,     \
        #type6, (size_t)arg6, #type7, (size_t)arg7, #type8, (size_t)arg8);    \
    OutputDebugStringA(strTrace);                                             \
  }

#define DXCB_TRACE_FUNC7(returntype, methodname, type1, arg1, type2, arg2,    \
                         type3, arg3, type4, arg4, type5, arg5, type6, arg6,  \
                         type7, arg7)                                         \
  if (should_trace_) {                                                        \
    char strTrace[700];                                                       \
    sprintf_s(                                                                \
        strTrace,                                                             \
        "%s %s (%s  0x%zx, %s  0x%zx, %s  0x%zx, %s  0x%zx, %s  0x%zx, %s  "  \
        "0x%zx, %s  0x%zx)\n",                                                \
        #returntype, #methodname, #type1, (size_t)arg1, #type2, (size_t)arg2, \
        #type3, (size_t)arg3, #type4, (size_t)arg4, #type5, (size_t)arg5,     \
        #type6, (size_t)arg6, #type7, (size_t)arg7);                          \
    OutputDebugStringA(strTrace);                                             \
  }

#define DXCB_TRACE_FUNC6(returntype, methodname, type1, arg1, type2, arg2,    \
                         type3, arg3, type4, arg4, type5, arg5, type6, arg6)  \
  if (should_trace_) {                                                        \
    char strTrace[700];                                                       \
    sprintf_s(                                                                \
        strTrace,                                                             \
        "%s %s (%s  0x%zx, %s  0x%zx, %s  0x%zx, %s  0x%zx, %s  0x%zx, %s  "  \
        "0x%zx)\n",                                                           \
        #returntype, #methodname, #type1, (size_t)arg1, #type2, (size_t)arg2, \
        #type3, (size_t)arg3, #type4, (size_t)arg4, #type5, (size_t)arg5,     \
        #type6, (size_t)arg6);                                                \
    OutputDebugStringA(strTrace);                                             \
  }

#define DXCB_TRACE_FUNC5(returntype, methodname, type1, arg1, type2, arg2,    \
                         type3, arg3, type4, arg4, type5, arg5)               \
  if (should_trace_) {                                                        \
    char strTrace[700];                                                       \
    sprintf_s(                                                                \
        strTrace,                                                             \
        "%s %s (%s  0x%zx, %s  0x%zx, %s  0x%zx, %s  0x%zx, %s  0x%zx)\n",    \
        #returntype, #methodname, #type1, (size_t)arg1, #type2, (size_t)arg2, \
        #type3, (size_t)arg3, #type4, (size_t)arg4, #type5, (size_t)arg5);    \
    OutputDebugStringA(strTrace);                                             \
  }

#define DXCB_TRACE_FUNC4(returntype, methodname, type1, arg1, type2, arg2, \
                         type3, arg3, type4, arg4)                         \
  if (should_trace_) {                                                     \
    char strTrace[700];                                                    \
    sprintf_s(strTrace,                                                    \
              "%s %s (%s  0x%zx, %s  0x%zx, %s  0x%zx, %s  0x%zx)\n",      \
              #returntype, #methodname, #type1, (size_t)arg1, #type2,      \
              (size_t)arg2, #type3, (size_t)arg3, #type4, (size_t)arg4);   \
    OutputDebugStringA(strTrace);                                          \
  }

#define DXCB_TRACE_FUNC3(returntype, methodname, type1, arg1, type2, arg2, \
                         type3, arg3)                                      \
  if (should_trace_) {                                                     \
    char strTrace[700];                                                    \
    sprintf_s(strTrace, "%s %s (%s  0x%zx, %s  0x%zx, %s  0x%zx)\n",       \
              #returntype, #methodname, #type1, (size_t)arg1, #type2,      \
              (size_t)arg2, #type3, (size_t)arg3);                         \
    OutputDebugStringA(strTrace);                                          \
  }

#define DXCB_TRACE_FUNC2(returntype, methodname, type1, arg1, type2, arg2) \
  if (should_trace_) {                                                     \
    char strTrace[700];                                                    \
    sprintf_s(strTrace, "%s %s (%s  0x%zx, %s  0x%zx)\n", #returntype,     \
              #methodname, #type1, (size_t)arg1, #type2, (size_t)arg2);    \
    OutputDebugStringA(strTrace);                                          \
  }

#define DXCB_TRACE_FUNC1(returntype, methodname, type1, arg1)            \
  if (should_trace_) {                                                   \
    char strTrace[700];                                                  \
    sprintf_s(strTrace, "%s %s (%s  0x%zx)\n", #returntype, #methodname, \
              #type1, (size_t)arg1);                                     \
    OutputDebugStringA(strTrace);                                        \
  }

#define DXCB_TRACE_FUNC0(returntype, methodname)                 \
  if (should_trace_) {                                           \
    char strTrace[700];                                          \
    sprintf_s(strTrace, "%s %s ()\n", #returntype, #methodname); \
    OutputDebugStringA(strTrace);                                \
  }
#else
#define DXCB_TRACE_FUNC9(returntype, methodname, type1, arg1, type2, arg2,   \
                         type3, arg3, type4, arg4, type5, arg5, type6, arg6, \
                         type7, arg7, type8, arg8, type9, arg9)              \
  ;
#define DXCB_TRACE_FUNC8(returntype, methodname, type1, arg1, type2, arg2,   \
                         type3, arg3, type4, arg4, type5, arg5, type6, arg6, \
                         type7, arg7, type8, arg8)                           \
  ;
#define DXCB_TRACE_FUNC7(returntype, methodname, type1, arg1, type2, arg2,   \
                         type3, arg3, type4, arg4, type5, arg5, type6, arg6, \
                         type7, arg7)                                        \
  ;
#define DXCB_TRACE_FUNC6(returntype, methodname, type1, arg1, type2, arg2,   \
                         type3, arg3, type4, arg4, type5, arg5, type6, arg6) \
  ;
#define DXCB_TRACE_FUNC5(returntype, methodname, type1, arg1, type2, arg2, \
                         type3, arg3, type4, arg4, type5, arg5)            \
  ;
#define DXCB_TRACE_FUNC4(returntype, methodname, type1, arg1, type2, arg2, \
                         type3, arg3, type4, arg4)                         \
  ;
#define DXCB_TRACE_FUNC3(returntype, methodname, type1, arg1, type2, arg2, \
                         type3, arg3)                                      \
  ;
#define DXCB_TRACE_FUNC2(returntype, methodname, type1, arg1, type2, arg2) ;
#define DXCB_TRACE_FUNC1(returntype, methodname, type1, arg1) ;
#define DXCB_TRACE_FUNC0(returntype, methodname) ;
#endif

#define DXCB_REDIRECTION_FUNC0(returntype, methodname) \
  STDMETHOD_(returntype, methodname)() {               \
    DXCB_TRACE_FUNC0(returntype, methodname)           \
    return current_d3d9_device_->methodname();         \
  }

#define DXCB_REDIRECTION_FUNC1(returntype, methodname, type1, arg1) \
  STDMETHOD_(returntype, methodname)(type1 arg1) {                  \
    DXCB_TRACE_FUNC1(returntype, methodname, type1, arg1)           \
    return current_d3d9_device_->methodname(arg1);                  \
  }

#define DXCB_REDIRECTION_FUNC2(returntype, methodname, type1, arg1, type2, \
                               arg2)                                       \
  STDMETHOD_(returntype, methodname)(type1 arg1, type2 arg2) {             \
    DXCB_TRACE_FUNC2(returntype, methodname, type1, arg1, type2, arg2)     \
    return current_d3d9_device_->methodname(arg1, arg2);                   \
  }

#define DXCB_REDIRECTION_FUNC3(returntype, methodname, type1, arg1, type2,    \
                               arg2, type3, arg3)                             \
  STDMETHOD_(returntype, methodname)(type1 arg1, type2 arg2, type3 arg3) {    \
    DXCB_TRACE_FUNC3(returntype, methodname, type1, arg1, type2, arg2, type3, \
                     arg3)                                                    \
    return current_d3d9_device_->methodname(arg1, arg2, arg3);                \
  }

#define DXCB_REDIRECTION_FUNC4(returntype, methodname, type1, arg1, type2,    \
                               arg2, type3, arg3, type4, arg4)                \
  STDMETHOD_(returntype, methodname)                                          \
  (type1 arg1, type2 arg2, type3 arg3, type4 arg4) {                          \
    DXCB_TRACE_FUNC4(returntype, methodname, type1, arg1, type2, arg2, type3, \
                     arg3, type4, arg4)                                       \
    return current_d3d9_device_->methodname(arg1, arg2, arg3, arg4);          \
  }

#define DXCB_REDIRECTION_FUNC5(returntype, methodname, type1, arg1, type2,    \
                               arg2, type3, arg3, type4, arg4, type5, arg5)   \
  STDMETHOD_(returntype, methodname)                                          \
  (type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5) {              \
    DXCB_TRACE_FUNC5(returntype, methodname, type1, arg1, type2, arg2, type3, \
                     arg3, type4, arg4, type5, arg5)                          \
    return current_d3d9_device_->methodname(arg1, arg2, arg3, arg4, arg5);    \
  }

#define DXCB_REDIRECTION_FUNC6(returntype, methodname, type1, arg1, type2,    \
                               arg2, type3, arg3, type4, arg4, type5, arg5,   \
                               type6, arg6)                                   \
  STDMETHOD_(returntype, methodname)                                          \
  (type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, type6 arg6) {  \
    DXCB_TRACE_FUNC6(returntype, methodname, type1, arg1, type2, arg2, type3, \
                     arg3, type4, arg4, type5, arg5, type6, arg6)             \
    return current_d3d9_device_->methodname(arg1, arg2, arg3, arg4, arg5,     \
                                            arg6);                            \
  }

#define DXCB_REDIRECTION_FUNC7(returntype, methodname, type1, arg1, type2,     \
                               arg2, type3, arg3, type4, arg4, type5, arg5,    \
                               type6, arg6, type7, arg7)                       \
  STDMETHOD_(returntype, methodname)                                           \
  (type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, type6 arg6,     \
   type7 arg7) {                                                               \
    DXCB_TRACE_FUNC7(returntype, methodname, type1, arg1, type2, arg2, type3,  \
                     arg3, type4, arg4, type5, arg5, type6, arg6, type7, arg7) \
    return current_d3d9_device_->methodname(arg1, arg2, arg3, arg4, arg5,      \
                                            arg6, arg7);                       \
  }

#define DXCB_REDIRECTION_FUNC8(returntype, methodname, type1, arg1, type2,     \
                               arg2, type3, arg3, type4, arg4, type5, arg5,    \
                               type6, arg6, type7, arg7, type8, arg8)          \
  STDMETHOD_(returntype, methodname)                                           \
  (type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, type6 arg6,     \
   type7 arg7, type8 arg8) {                                                   \
    DXCB_TRACE_FUNC8(returntype, methodname, type1, arg1, type2, arg2, type3,  \
                     arg3, type4, arg4, type5, arg5, type6, arg6, type7, arg7, \
                     type8, arg8)                                              \
    return current_d3d9_device_->methodname(arg1, arg2, arg3, arg4, arg5,      \
                                            arg6, arg7, arg8);                 \
  }

#define DXCB_REDIRECTION_FUNC9(                                                \
    returntype, methodname, type1, arg1, type2, arg2, type3, arg3, type4,      \
    arg4, type5, arg5, type6, arg6, type7, arg7, type8, arg8, type9, arg9)     \
  STDMETHOD_(returntype, methodname)                                           \
  (type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, type6 arg6,     \
   type7 arg7, type8 arg8, type9 arg9) {                                       \
    DXCB_TRACE_FUNC9(returntype, methodname, type1, arg1, type2, arg2, type3,  \
                     arg3, type4, arg4, type5, arg5, type6, arg6, type7, arg7, \
                     type8, arg8, type9, arg9)                                 \
    return current_d3d9_device_->methodname(arg1, arg2, arg3, arg4, arg5,      \
                                            arg6, arg7, arg8, arg9);           \
  }                                                                            \

#define DXCB_OTHER_REDIRECTION_FUNC0(returntype, methodname) \
  DXCB_REDIRECTION_FUNC0(ULONG, methodname)

#define DXCB_STD_REDIRECTION_FUNC0(methodname) \
  DXCB_REDIRECTION_FUNC0(HRESULT, methodname)

#define DXCB_STD_REDIRECTION_FUNC1(methodname, type1, arg1) \
  DXCB_REDIRECTION_FUNC1(HRESULT, methodname, type1, arg1)

#define DXCB_STD_REDIRECTION_FUNC2(methodname, type1, arg1, type2, arg2) \
  DXCB_REDIRECTION_FUNC2(HRESULT, methodname, type1, arg1, type2, arg2)

#define DXCB_STD_REDIRECTION_FUNC3(methodname, type1, arg1, type2, arg2,       \
                                   type3, arg3)                                \
  DXCB_REDIRECTION_FUNC3(HRESULT, methodname, type1, arg1, type2, arg2, type3, \
                         arg3)

#define DXCB_STD_REDIRECTION_FUNC4(methodname, type1, arg1, type2, arg2,       \
                                   type3, arg3, type4, arg4)                   \
  DXCB_REDIRECTION_FUNC4(HRESULT, methodname, type1, arg1, type2, arg2, type3, \
                         arg3, type4, arg4)

#define DXCB_STD_REDIRECTION_FUNC5(methodname, type1, arg1, type2, arg2,       \
                                   type3, arg3, type4, arg4, type5, arg5)      \
  DXCB_REDIRECTION_FUNC5(HRESULT, methodname, type1, arg1, type2, arg2, type3, \
                         arg3, type4, arg4, type5, arg5)

#define DXCB_STD_REDIRECTION_FUNC6(methodname, type1, arg1, type2, arg2,       \
                                   type3, arg3, type4, arg4, type5, arg5,      \
                                   type6, arg6)                                \
  DXCB_REDIRECTION_FUNC6(HRESULT, methodname, type1, arg1, type2, arg2, type3, \
                         arg3, type4, arg4, type5, arg5, type6, arg6)

#define DXCB_STD_REDIRECTION_FUNC7(methodname, type1, arg1, type2, arg2,       \
                                   type3, arg3, type4, arg4, type5, arg5,      \
                                   type6, arg6, type7, arg7)                   \
  DXCB_REDIRECTION_FUNC7(HRESULT, methodname, type1, arg1, type2, arg2, type3, \
                         arg3, type4, arg4, type5, arg5, type6, arg6, type7,   \
                         arg7)

#define DXCB_STD_REDIRECTION_FUNC8(methodname, type1, arg1, type2, arg2,       \
                                   type3, arg3, type4, arg4, type5, arg5,      \
                                   type6, arg6, type7, arg7, type8, arg8)      \
  DXCB_REDIRECTION_FUNC8(HRESULT, methodname, type1, arg1, type2, arg2, type3, \
                         arg3, type4, arg4, type5, arg5, type6, arg6, type7,   \
                         arg7, type8, arg8)

#define DXCB_STD_REDIRECTION_FUNC9(                                            \
    methodname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5,     \
    arg5, type6, arg6, type7, arg7, type8, arg8, type9, arg9)                  \
  DXCB_REDIRECTION_FUNC9(HRESULT, methodname, type1, arg1, type2, arg2, type3, \
                         arg3, type4, arg4, type5, arg5, type6, arg6, type7,   \
                         arg7, type8, arg8, type9, arg9)

namespace dxcb {

class RedirectingDirect3DDevice9 : public IDirect3DDevice9 {
 public:
  RedirectingDirect3DDevice9()
      : current_d3d9_device_{nullptr},
        real_d3d9_device_{nullptr},
        should_trace_{false} {}
  ~RedirectingDirect3DDevice9() = default;

  RedirectingDirect3DDevice9(RedirectingDirect3DDevice9 &) = delete;
  RedirectingDirect3DDevice9(RedirectingDirect3DDevice9 &&) = delete;
  RedirectingDirect3DDevice9 &operator=(RedirectingDirect3DDevice9 &) = delete;
  RedirectingDirect3DDevice9 &operator=(RedirectingDirect3DDevice9 &&) = delete;

  void SetTrace(bool bval) { should_trace_ = bval; }
  bool GetTrace() const { return should_trace_; }

  void ReplaceCurrentDevice(IDirect3DDevice9 *new_device) {
    current_d3d9_device_ = new_device;
  }

  void RestoreCurrentDevice() { current_d3d9_device_ = real_d3d9_device_; }

  IDirect3DDevice9 *GetCurrentDevice() { return current_d3d9_device_; }
  IDirect3DDevice9 *GetRealDevice() { return real_d3d9_device_; }
  bool IsCurrentDeviceReal() const {
    return current_d3d9_device_ == real_d3d9_device_;
  }

  /*** IUnknown methods ***/
  // #if !BUILDTRACE
  //      DXCB_STD_REDIRECTION_FUNC2( QueryInterface, REFIID, riid, void**,
  //      ppvObj);
  // #else
  STDMETHOD_(HRESULT, QueryInterface)(REFIID riid, void **ppvObj) {
    if (should_trace_) {
      char strTrace[256];
      sprintf_s(strTrace, "HRESULT QueryInterface(void** 0x%p)\n", ppvObj);
      OutputDebugStringA(strTrace);
    }
    return current_d3d9_device_->QueryInterface(riid, ppvObj);
  };
  // #endif

  DXCB_OTHER_REDIRECTION_FUNC0(ULONG, AddRef);
  DXCB_OTHER_REDIRECTION_FUNC0(ULONG, Release);

  /*** Implemnted IDirect3DDevice9 methods ***/
  /* Note that it is assumed that input values will be valid a record time. */
  /* Also there is no mechnism to retain returned values during playback     */

  DXCB_STD_REDIRECTION_FUNC3(DrawPrimitive, D3DPRIMITIVETYPE, PrimitiveType,
                             UINT, StartVertex, UINT, PrimitiveCount);
  DXCB_STD_REDIRECTION_FUNC6(DrawIndexedPrimitive, D3DPRIMITIVETYPE,
                             PrimitiveType, INT, BaseVertexIndex, UINT,
                             MinVertexIndex, UINT, NumVertices, UINT,
                             startIndex, UINT, primCount);
  DXCB_STD_REDIRECTION_FUNC4(SetStreamSource, UINT, StreamNumber,
                             IDirect3DVertexBuffer9 *, pStreamData, UINT,
                             OffsetInBytes, UINT, Stride);
  DXCB_STD_REDIRECTION_FUNC2(SetStreamSourceFreq, UINT, StreamNumber, UINT,
                             Divider);
  DXCB_STD_REDIRECTION_FUNC1(SetVertexDeclaration,
                             IDirect3DVertexDeclaration9 *, pDecl);
  DXCB_STD_REDIRECTION_FUNC1(SetIndices, IDirect3DIndexBuffer9 *, pIndexData);
  DXCB_STD_REDIRECTION_FUNC0(TestCooperativeLevel);
  DXCB_STD_REDIRECTION_FUNC0(EvictManagedResources);
  DXCB_STD_REDIRECTION_FUNC0(BeginScene);
  DXCB_STD_REDIRECTION_FUNC0(EndScene);
  DXCB_STD_REDIRECTION_FUNC0(BeginStateBlock);
  DXCB_STD_REDIRECTION_FUNC1(EndStateBlock, IDirect3DStateBlock9 **, ppSB);
  DXCB_STD_REDIRECTION_FUNC1(GetDirect3D, IDirect3D9 **, ppD3D9);
  /*** These methods can be recorded but without a way to retain the return
   * value I do not see why your would use them */
  DXCB_STD_REDIRECTION_FUNC3(SetCursorProperties, UINT, XHotSpot, UINT,
                             YHotSpot, IDirect3DSurface9 *, pCursorBitmap);
  DXCB_REDIRECTION_FUNC3(void, SetCursorPosition, int, X, int, Y, DWORD, Flags);
  DXCB_STD_REDIRECTION_FUNC1(SetDialogBoxMode, BOOL, bEnableDialogs);
  DXCB_STD_REDIRECTION_FUNC1(GetDeviceCaps, D3DCAPS9 *, pCaps);
  DXCB_STD_REDIRECTION_FUNC2(GetDisplayMode, UINT, iSwapChain, D3DDISPLAYMODE *,
                             pMode);
  DXCB_STD_REDIRECTION_FUNC1(GetCreationParameters,
                             D3DDEVICE_CREATION_PARAMETERS *, pParameters);
  DXCB_STD_REDIRECTION_FUNC2(CreateAdditionalSwapChain, D3DPRESENT_PARAMETERS *,
                             pPresentationParameters, IDirect3DSwapChain9 **,
                             pSwapChain);
  DXCB_STD_REDIRECTION_FUNC2(GetSwapChain, UINT, iSwapChain,
                             IDirect3DSwapChain9 **, pSwapChain);
  DXCB_STD_REDIRECTION_FUNC1(Reset, D3DPRESENT_PARAMETERS *,
                             pPresentationParameters);
  DXCB_STD_REDIRECTION_FUNC4(Present, CONST RECT *, pSourceRect, CONST RECT *,
                             pDestRect, HWND, hDestWindowOverride,
                             CONST RGNDATA *, pDirtyRegion);
  DXCB_STD_REDIRECTION_FUNC4(GetBackBuffer, UINT, iSwapChain, UINT, iBackBuffer,
                             D3DBACKBUFFER_TYPE, Type, IDirect3DSurface9 **,
                             ppBackBuffer);
  DXCB_STD_REDIRECTION_FUNC2(GetRasterStatus, UINT, iSwapChain,
                             D3DRASTER_STATUS *, pRasterStatus);
  DXCB_REDIRECTION_FUNC3(void, SetGammaRamp, UINT, iSwapChain, DWORD, Flags,
                         CONST D3DGAMMARAMP *, pRamp);
  DXCB_REDIRECTION_FUNC2(void, GetGammaRamp, UINT, iSwapChain, D3DGAMMARAMP *,
                         pRamp);
  DXCB_STD_REDIRECTION_FUNC8(CreateTexture, UINT, Width, UINT, Height, UINT,
                             Levels, DWORD, Usage, D3DFORMAT, Format, D3DPOOL,
                             Pool, IDirect3DTexture9 **, ppTexture, HANDLE *,
                             pSharedHandle);
  DXCB_STD_REDIRECTION_FUNC9(CreateVolumeTexture, UINT, Width, UINT, Height,
                             UINT, Depth, UINT, Levels, DWORD, Usage, D3DFORMAT,
                             Format, D3DPOOL, Pool, IDirect3DVolumeTexture9 **,
                             ppVolumeTexture, HANDLE *, pSharedHandle);
  DXCB_STD_REDIRECTION_FUNC7(CreateCubeTexture, UINT, EdgeLength, UINT, Levels,
                             DWORD, Usage, D3DFORMAT, Format, D3DPOOL, Pool,
                             IDirect3DCubeTexture9 **, ppCubeTexture, HANDLE *,
                             pSharedHandle);
  DXCB_STD_REDIRECTION_FUNC6(CreateVertexBuffer, UINT, Length, DWORD, Usage,
                             DWORD, Fvf, D3DPOOL, Pool,
                             IDirect3DVertexBuffer9 **, ppVertexBuffer,
                             HANDLE *, pSharedHandle);
  DXCB_STD_REDIRECTION_FUNC6(CreateIndexBuffer, UINT, Length, DWORD, Usage,
                             D3DFORMAT, Format, D3DPOOL, Pool,
                             IDirect3DIndexBuffer9 **, ppIndexBuffer, HANDLE *,
                             pSharedHandle);
  DXCB_STD_REDIRECTION_FUNC8(CreateRenderTarget, UINT, Width, UINT, Height,
                             D3DFORMAT, Format, D3DMULTISAMPLE_TYPE,
                             MultiSample, DWORD, MultisampleQuality, BOOL,
                             Lockable, IDirect3DSurface9 **, ppSurface,
                             HANDLE *, pSharedHandle);
  DXCB_STD_REDIRECTION_FUNC8(CreateDepthStencilSurface, UINT, Width, UINT,
                             Height, D3DFORMAT, Format, D3DMULTISAMPLE_TYPE,
                             MultiSample, DWORD, MultisampleQuality, BOOL,
                             Discard, IDirect3DSurface9 **, ppSurface, HANDLE *,
                             pSharedHandle);
  DXCB_STD_REDIRECTION_FUNC4(UpdateSurface, IDirect3DSurface9 *, pSourceSurface,
                             CONST RECT *, pSourceRect, IDirect3DSurface9 *,
                             pDestinationSurface, CONST POINT *, pDestPoint);
  DXCB_STD_REDIRECTION_FUNC2(UpdateTexture, IDirect3DBaseTexture9 *,
                             pSourceTexture, IDirect3DBaseTexture9 *,
                             pDestinationTexture);
  DXCB_STD_REDIRECTION_FUNC2(GetRenderTargetData, IDirect3DSurface9 *,
                             pRenderTarget, IDirect3DSurface9 *, pDestSurface);
  DXCB_STD_REDIRECTION_FUNC2(GetFrontBufferData, UINT, iSwapChain,
                             IDirect3DSurface9 *, pDestSurface);
  DXCB_STD_REDIRECTION_FUNC5(StretchRect, IDirect3DSurface9 *, pSourceSurface,
                             CONST RECT *, pSourceRect, IDirect3DSurface9 *,
                             pDestSurface, CONST RECT *, pDestRect,
                             D3DTEXTUREFILTERTYPE, Filter);
  DXCB_STD_REDIRECTION_FUNC3(ColorFill, IDirect3DSurface9 *, pSurface,
                             CONST RECT *, pRect, D3DCOLOR, color);
  DXCB_STD_REDIRECTION_FUNC6(CreateOffscreenPlainSurface, UINT, Width, UINT,
                             Height, D3DFORMAT, Format, D3DPOOL, Pool,
                             IDirect3DSurface9 **, ppSurface, HANDLE *,
                             pSharedHandle);
  DXCB_STD_REDIRECTION_FUNC2(SetRenderTarget, DWORD, RenderTargetIndex,
                             IDirect3DSurface9 *, pRenderTarget);
  DXCB_STD_REDIRECTION_FUNC2(GetRenderTarget, DWORD, RenderTargetIndex,
                             IDirect3DSurface9 **, ppRenderTarget);
  DXCB_STD_REDIRECTION_FUNC1(SetDepthStencilSurface, IDirect3DSurface9 *,
                             pNewZStencil);
  DXCB_STD_REDIRECTION_FUNC1(GetDepthStencilSurface, IDirect3DSurface9 **,
                             ppZStencilSurface);
  DXCB_STD_REDIRECTION_FUNC6(Clear, DWORD, Count, CONST D3DRECT *, pRects,
                             DWORD, Flags, D3DCOLOR, Color, float, Z, DWORD,
                             Stencil);
  DXCB_STD_REDIRECTION_FUNC2(SetTransform, D3DTRANSFORMSTATETYPE, State,
                             CONST D3DMATRIX *, pMatrix);
  DXCB_STD_REDIRECTION_FUNC2(GetTransform, D3DTRANSFORMSTATETYPE, State,
                             D3DMATRIX *, pMatrix);
  DXCB_STD_REDIRECTION_FUNC2(MultiplyTransform, D3DTRANSFORMSTATETYPE, type,
                             CONST D3DMATRIX *, pMatrix);
  DXCB_STD_REDIRECTION_FUNC1(SetViewport, CONST D3DVIEWPORT9 *, pViewport);
  DXCB_STD_REDIRECTION_FUNC1(GetViewport, D3DVIEWPORT9 *, pViewport);
  DXCB_STD_REDIRECTION_FUNC1(SetMaterial, CONST D3DMATERIAL9 *, pMaterial);
  DXCB_STD_REDIRECTION_FUNC1(GetMaterial, D3DMATERIAL9 *, pMaterial);
  DXCB_STD_REDIRECTION_FUNC2(SetLight, DWORD, Index, CONST D3DLIGHT9 *, pLight);
  DXCB_STD_REDIRECTION_FUNC2(GetLight, DWORD, Index, D3DLIGHT9 *, pLight);
  DXCB_STD_REDIRECTION_FUNC2(LightEnable, DWORD, Index, BOOL, Enable);
  DXCB_STD_REDIRECTION_FUNC2(GetLightEnable, DWORD, Index, BOOL *, pEnable);
  DXCB_STD_REDIRECTION_FUNC2(SetClipPlane, DWORD, Index, CONST float *, pPlane);
  DXCB_STD_REDIRECTION_FUNC2(GetClipPlane, DWORD, Index, float *, pPlane);
  DXCB_STD_REDIRECTION_FUNC2(SetRenderState, D3DRENDERSTATETYPE, State, DWORD,
                             Value);
  DXCB_STD_REDIRECTION_FUNC2(GetRenderState, D3DRENDERSTATETYPE, State, DWORD *,
                             pValue);
  DXCB_STD_REDIRECTION_FUNC2(CreateStateBlock, D3DSTATEBLOCKTYPE, Type,
                             IDirect3DStateBlock9 **, ppSB);
  DXCB_STD_REDIRECTION_FUNC1(SetClipStatus, CONST D3DCLIPSTATUS9 *,
                             pClipStatus);
  DXCB_STD_REDIRECTION_FUNC1(GetClipStatus, D3DCLIPSTATUS9 *, pClipStatus);
  DXCB_STD_REDIRECTION_FUNC2(GetTexture, DWORD, Stage, IDirect3DBaseTexture9 **,
                             ppTexture);
  DXCB_STD_REDIRECTION_FUNC2(SetTexture, DWORD, Stage, IDirect3DBaseTexture9 *,
                             pTexture);
  DXCB_STD_REDIRECTION_FUNC3(GetTextureStageState, DWORD, Stage,
                             D3DTEXTURESTAGESTATETYPE, Type, DWORD *, pValue);
  DXCB_STD_REDIRECTION_FUNC3(SetTextureStageState, DWORD, Stage,
                             D3DTEXTURESTAGESTATETYPE, Type, DWORD, Value);
  DXCB_STD_REDIRECTION_FUNC3(GetSamplerState, DWORD, Sampler,
                             D3DSAMPLERSTATETYPE, Type, DWORD *, pValue);
  DXCB_STD_REDIRECTION_FUNC3(SetSamplerState, DWORD, Sampler,
                             D3DSAMPLERSTATETYPE, Type, DWORD, Value);
  DXCB_STD_REDIRECTION_FUNC1(ValidateDevice, DWORD *, pNumPasses);
  DXCB_STD_REDIRECTION_FUNC2(SetPaletteEntries, UINT, PaletteNumber,
                             CONST PALETTEENTRY *, pEntries);
  DXCB_STD_REDIRECTION_FUNC2(GetPaletteEntries, UINT, PaletteNumber,
                             PALETTEENTRY *, pEntries);
  DXCB_STD_REDIRECTION_FUNC1(SetCurrentTexturePalette, UINT, PaletteNumber);
  DXCB_STD_REDIRECTION_FUNC1(GetCurrentTexturePalette, UINT *, PaletteNumber);
  DXCB_STD_REDIRECTION_FUNC1(SetScissorRect, CONST RECT *, pRect);
  DXCB_STD_REDIRECTION_FUNC1(GetScissorRect, RECT *, pRect);
  DXCB_STD_REDIRECTION_FUNC1(SetSoftwareVertexProcessing, BOOL, bSoftware);
  DXCB_STD_REDIRECTION_FUNC1(SetNPatchMode, float, nSegments);
  DXCB_STD_REDIRECTION_FUNC4(DrawPrimitiveUP, D3DPRIMITIVETYPE, PrimitiveType,
                             UINT, PrimitiveCount, CONST void *,
                             pVertexStreamZeroData, UINT,
                             VertexStreamZeroStride);
  DXCB_STD_REDIRECTION_FUNC8(DrawIndexedPrimitiveUP, D3DPRIMITIVETYPE,
                             PrimitiveType, UINT, MinVertexIndex, UINT,
                             NumVertices, UINT, PrimitiveCount, CONST void *,
                             pIndexData, D3DFORMAT, IndexDataFormat,
                             CONST void *, pVertexStreamZeroData, UINT,
                             VertexStreamZeroStride);
  DXCB_STD_REDIRECTION_FUNC6(ProcessVertices, UINT, SrcStartIndex, UINT,
                             DestIndex, UINT, VertexCount,
                             IDirect3DVertexBuffer9 *, pDestBuffer,
                             IDirect3DVertexDeclaration9 *, pVertexDecl, DWORD,
                             Flags);
  DXCB_STD_REDIRECTION_FUNC2(CreateVertexDeclaration, CONST D3DVERTEXELEMENT9 *,
                             pVertexElements, IDirect3DVertexDeclaration9 **,
                             ppDecl);
  DXCB_STD_REDIRECTION_FUNC1(GetVertexDeclaration,
                             IDirect3DVertexDeclaration9 **, ppDecl);
  DXCB_STD_REDIRECTION_FUNC1(SetFVF, DWORD, Fvf);
  DXCB_STD_REDIRECTION_FUNC1(GetFVF, DWORD *, pFVF);
  DXCB_STD_REDIRECTION_FUNC2(CreateVertexShader, CONST DWORD *, pFunction,
                             IDirect3DVertexShader9 **, ppShader);
  DXCB_STD_REDIRECTION_FUNC1(SetVertexShader, IDirect3DVertexShader9 *,
                             pShader);
  DXCB_STD_REDIRECTION_FUNC1(GetVertexShader, IDirect3DVertexShader9 **,
                             ppShader);
  DXCB_STD_REDIRECTION_FUNC3(SetVertexShaderConstantF, UINT, StartRegister,
                             CONST float *, pConstantData, UINT, Vector4fCount);
  DXCB_STD_REDIRECTION_FUNC3(GetVertexShaderConstantF, UINT, StartRegister,
                             float *, pConstantData, UINT, Vector4fCount);
  DXCB_STD_REDIRECTION_FUNC3(SetVertexShaderConstantI, UINT, StartRegister,
                             CONST int *, pConstantData, UINT, Vector4iCount);
  DXCB_STD_REDIRECTION_FUNC3(GetVertexShaderConstantI, UINT, StartRegister,
                             int *, pConstantData, UINT, Vector4iCount);
  DXCB_STD_REDIRECTION_FUNC3(SetVertexShaderConstantB, UINT, StartRegister,
                             CONST BOOL *, pConstantData, UINT, BoolCount);
  DXCB_STD_REDIRECTION_FUNC3(GetVertexShaderConstantB, UINT, StartRegister,
                             BOOL *, pConstantData, UINT, BoolCount);
  DXCB_STD_REDIRECTION_FUNC4(GetStreamSource, UINT, StreamNumber,
                             IDirect3DVertexBuffer9 **, ppStreamData, UINT *,
                             OffsetInBytes, UINT *, pStride);
  DXCB_STD_REDIRECTION_FUNC2(GetStreamSourceFreq, UINT, StreamNumber, UINT *,
                             Divider);
  DXCB_STD_REDIRECTION_FUNC1(GetIndices, IDirect3DIndexBuffer9 **, ppIndexData);
  DXCB_STD_REDIRECTION_FUNC2(CreatePixelShader, CONST DWORD *, pFunction,
                             IDirect3DPixelShader9 **, ppShader);
  DXCB_STD_REDIRECTION_FUNC1(SetPixelShader, IDirect3DPixelShader9 *, pShader);
  DXCB_STD_REDIRECTION_FUNC1(GetPixelShader, IDirect3DPixelShader9 **,
                             ppShader);
  DXCB_STD_REDIRECTION_FUNC3(SetPixelShaderConstantF, UINT, StartRegister,
                             CONST float *, pConstantData, UINT, Vector4fCount);
  DXCB_STD_REDIRECTION_FUNC3(GetPixelShaderConstantF, UINT, StartRegister,
                             float *, pConstantData, UINT, Vector4fCount);
  DXCB_STD_REDIRECTION_FUNC3(SetPixelShaderConstantI, UINT, StartRegister,
                             CONST int *, pConstantData, UINT, Vector4iCount);
  DXCB_STD_REDIRECTION_FUNC3(GetPixelShaderConstantI, UINT, StartRegister,
                             int *, pConstantData, UINT, Vector4iCount);
  DXCB_STD_REDIRECTION_FUNC3(SetPixelShaderConstantB, UINT, StartRegister,
                             CONST BOOL *, pConstantData, UINT, BoolCount);
  DXCB_STD_REDIRECTION_FUNC3(GetPixelShaderConstantB, UINT, StartRegister,
                             BOOL *, pConstantData, UINT, BoolCount);
  DXCB_STD_REDIRECTION_FUNC3(DrawRectPatch, UINT, Handle, CONST float *,
                             pNumSegs, CONST D3DRECTPATCH_INFO *,
                             pRectPatchInfo);
  DXCB_STD_REDIRECTION_FUNC3(DrawTriPatch, UINT, Handle, CONST float *,
                             pNumSegs, CONST D3DTRIPATCH_INFO *, pTriPatchInfo);
  DXCB_STD_REDIRECTION_FUNC1(DeletePatch, UINT, Handle);
  DXCB_STD_REDIRECTION_FUNC2(CreateQuery, D3DQUERYTYPE, Type,
                             IDirect3DQuery9 **, ppQuery);

  /*** IDirect3DDevice methods that cannot be recorded which throw errors */
  DXCB_REDIRECTION_FUNC0(UINT, GetAvailableTextureMem);
  DXCB_REDIRECTION_FUNC0(UINT, GetNumberOfSwapChains);
  DXCB_REDIRECTION_FUNC1(BOOL, ShowCursor, BOOL, bShow);
  DXCB_REDIRECTION_FUNC0(BOOL, GetSoftwareVertexProcessing);
  DXCB_REDIRECTION_FUNC0(float, GetNPatchMode);

  /*** Unimplemented IDirect3DDevice9 methods ***/
 private:
  IDirect3D9 *real_d3d9_;
  IDirect3DDevice9 *current_d3d9_device_;
  IDirect3DDevice9 *real_d3d9_device_;
  bool should_trace_;
};

//----------------------------------------------------------------------------
// ID3DXEffectStateManager:
// ------------------------
// This is a user implemented interface that can be used to manage device
// state changes made by an Effect.
//----------------------------------------------------------------------------

// typedef interface ID3DXEffectStateManager ID3DXEffectStateManager;
// typedef interface ID3DXEffectStateManager *LPD3DXEFFECTSTATEMANAGER;

class RedirectingEffectStateManager : public ID3DXEffectStateManager {
 public:
  // The user must correctly implement QueryInterface, AddRef, and Release.
  RedirectingEffectStateManager(IDirect3DDevice9 *device)
      : current_d3d9_device_{device}, ref_counter_{1}, should_trace_{false} {}
  ~RedirectingEffectStateManager() { Release(); }

  void SetTrace(bool bval) { should_trace_ = bval; }

  // IUnknown
  HRESULT __declspec(nothrow) __stdcall QueryInterface(REFIID iid,
                                                       LPVOID *ppv) {
    return current_d3d9_device_->QueryInterface(iid, ppv);
  }
  ULONG __declspec(nothrow) __stdcall AddRef() { return ++ref_counter_; }
  ULONG __declspec(nothrow) __stdcall Release() { return --ref_counter_; }

  // The following methods are called by the Effect when it wants to make
  // the corresponding device call.  Note that:
  // 1. Users manage the state and are therefore responsible for making the
  //    the corresponding device calls themselves inside their callbacks.
  // 2. Effects pay attention to the return values of the callbacks, and so
  //    users must pay attention to what they return in their callbacks.

  DXCB_STD_REDIRECTION_FUNC2(SetTransform, D3DTRANSFORMSTATETYPE, State,
                             CONST D3DMATRIX *, pMatrix);
  DXCB_STD_REDIRECTION_FUNC1(SetMaterial, CONST D3DMATERIAL9 *, pMaterial);
  DXCB_STD_REDIRECTION_FUNC2(SetLight, DWORD, Index, CONST D3DLIGHT9 *, pLight);
  DXCB_STD_REDIRECTION_FUNC2(LightEnable, DWORD, Index, BOOL, Enable);
  DXCB_STD_REDIRECTION_FUNC2(SetRenderState, D3DRENDERSTATETYPE, State, DWORD,
                             Value);
  DXCB_STD_REDIRECTION_FUNC2(SetTexture, DWORD, Stage, LPDIRECT3DBASETEXTURE9,
                             pTexture);
  DXCB_STD_REDIRECTION_FUNC3(SetTextureStageState, DWORD, Stage,
                             D3DTEXTURESTAGESTATETYPE, Type, DWORD, Value);
  DXCB_STD_REDIRECTION_FUNC3(SetSamplerState, DWORD, Sampler,
                             D3DSAMPLERSTATETYPE, Type, DWORD, Value);
  DXCB_STD_REDIRECTION_FUNC1(SetNPatchMode, FLOAT, NumSegments);
  DXCB_STD_REDIRECTION_FUNC1(SetFVF, DWORD, Fvf);
  DXCB_STD_REDIRECTION_FUNC1(SetVertexShader, LPDIRECT3DVERTEXSHADER9, pShader);
  DXCB_STD_REDIRECTION_FUNC3(SetVertexShaderConstantF, UINT, RegisterIndex,
                             CONST FLOAT *, pConstantData, UINT, RegisterCount);
  DXCB_STD_REDIRECTION_FUNC3(SetVertexShaderConstantI, UINT, RegisterIndex,
                             CONST INT *, pConstantData, UINT, RegisterCount);
  DXCB_STD_REDIRECTION_FUNC3(SetVertexShaderConstantB, UINT, RegisterIndex,
                             CONST BOOL *, pConstantData, UINT, RegisterCount);
  DXCB_STD_REDIRECTION_FUNC1(SetPixelShader, LPDIRECT3DPIXELSHADER9, pShader);
  DXCB_STD_REDIRECTION_FUNC3(SetPixelShaderConstantF, UINT, RegisterIndex,
                             CONST FLOAT *, pConstantData, UINT, RegisterCount);
  DXCB_STD_REDIRECTION_FUNC3(SetPixelShaderConstantI, UINT, RegisterIndex,
                             CONST INT *, pConstantData, UINT, RegisterCount);
  DXCB_STD_REDIRECTION_FUNC3(SetPixelShaderConstantB, UINT, RegisterIndex,
                             CONST BOOL *, pConstantData, UINT, RegisterCount);

 private:
  IDirect3DDevice9 *current_d3d9_device_;
  std::atomic_ulong ref_counter_;
  bool should_trace_;
};

}  // namespace dxcb

#endif  // DXCB_INVOKE_PREPROCESSOR

#endif  // DXCB_REDIRECTING_DIRECT3D_DEVICE9_H_