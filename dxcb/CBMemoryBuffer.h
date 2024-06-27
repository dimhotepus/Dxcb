// Open source.
// See Vincent Scheib rant at
// http://beautifulpixels.blogspot.com/2008/07/parallel-rendering-with-directx-command.html

#ifndef DXCB_CBMEMORYBUFFER_H_
#define DXCB_CBMEMORYBUFFER_H_

#ifndef DXCB_INVOKE_PREPROCESSOR

#include <d3d9.h>

#include <cassert>
#include <cstdio>
#include <type_traits>

#include "PREPROCESSED_CBMemoryBuffer.h"

#else

#include "CBMacros.h"

#if DXCB_ENABLE_MEMORY_TRACE
namespace dxcb {

bool GetMemoryTrace();
void SetMemoryTrace(bool on);

bool GetBufferRecordTrace();
void SetBufferRecordTrace(bool on);

bool GetBufferPlayTrace();
void SetBufferPlayTrace(bool on);

}  // namespace dxcb
#endif

namespace dxcb {

// This enumeration is used to index into the PlaybackNumberArgs table to obtain
// the number of.
namespace D3d9Commands {
enum : unsigned {
  // High value to catch command buffer errors.
  Null = 0xD3D00000U,
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
}  // namespace D3d9Commands

class CBMemoryBuffer {
 public:
  CBMemoryBuffer() : memory_{nullptr}, memory_size_{0}, next_memory_{nullptr} {}

  CBMemoryBuffer(CBMemoryBuffer&) = delete;
  CBMemoryBuffer(CBMemoryBuffer&&) = delete;
  CBMemoryBuffer& operator=(CBMemoryBuffer&) = delete;
  CBMemoryBuffer& operator=(CBMemoryBuffer&&) = delete;

  void ResetNext() { next_memory_ = memory_; }

  void GetMemory(size_t*& memory, size_t& count) const;
  void SetMemory(size_t* memory, size_t count);

  const size_t* GetNextPtr() const { return next_memory_; }

  template <typename T>
  T Gets() {
    static_assert(sizeof(T) <= sizeof(size_t));

    assert(next_memory_ >= memory_);
    assert(next_memory_ < memory_ + memory_size_);

#if DXCB_ENABLE_MEMORY_TRACE && DXCB_ENABLE_VERBOSE_MODE
    size_t* next{next_memory_};
#endif

    alignas(DXCB_MAX(sizeof(T), sizeof(size_t))) const size_t ret{*next_memory_};

    next_memory_++;

#if DXCB_ENABLE_MEMORY_TRACE
    DXCB_DEBUG_GET("CBMemoryBuffer::Gets", ret, next, next_memory_)
#endif

    return (T)ret;
  }

  template <typename T, size_t size>
  T* Gets() {
    // Number of size_t required to store size, round up.
    constexpr size_t size_in_sizet{(size + sizeof(size_t) - 1) /
                                   sizeof(size_t)};

    static_assert(sizeof(T) <= size);
    assert(next_memory_ >= memory_);
    assert(next_memory_ + size_in_sizet - 1 < memory_ + memory_size_);

#if DXCB_ENABLE_MEMORY_TRACE && DXCB_ENABLE_VERBOSE_MODE
    size_t* next{next_memory_};
#endif

    const size_t val{*next_memory_};

    next_memory_++;

    alignas(T*) size_t* ret{next_memory_};

    if (val != 0) {
      next_memory_ += size_in_sizet;
    } else {
      ret = nullptr;
    }

#if DXCB_ENABLE_MEMORY_TRACE
    DXCB_DEBUG_GET("CBMemoryBuffer::Gets", ret, next, next_memory_)
#endif

    return reinterpret_cast<T*>(ret);
  }

  // Size known only in runtime.
  template <typename T>
  T* Gets(size_t size) {
    // Number of size_t required to store size, round up.
    const size_t size_in_sizet{(size + sizeof(size_t) - 1) / sizeof(size_t)};

    assert(sizeof(T) <= size);
    assert(next_memory_ >= memory_);
    assert(next_memory_ + size_in_sizet - 1 < memory_ + memory_size_);

#if DXCB_ENABLE_MEMORY_TRACE && DXCB_ENABLE_VERBOSE_MODE
    size_t* next{next_memory_};
#endif

    const size_t val{*next_memory_};

    next_memory_++;

    alignas(T*) size_t* ret{next_memory_};

    if (val != 0) {
      next_memory_ += size_in_sizet;
    } else {
      ret = nullptr;
    }

#if DXCB_ENABLE_MEMORY_TRACE
    DXCB_DEBUG_GET("CBMemoryBuffer::Gets", ret, next, next_memory_)
#endif

    return reinterpret_cast<T*>(ret);
  }

  template <typename T>
  void Puts(T val) {
    static_assert(sizeof(T) <= sizeof(size_t));

    assert(next_memory_ >= memory_);
    assert(next_memory_ < memory_ + memory_size_);

#if DXCB_ENABLE_MEMORY_TRACE && DXCB_ENABLE_VERBOSE_MODE
    size_t* next{next_memory_};
#endif

    memcpy(next_memory_, &val, sizeof(val));

    ++next_memory_;

#if DXCB_ENABLE_MEMORY_TRACE
    DXCB_DEBUG_PUT("CBMemoryBuffer::Puts", val, next, next_memory_)
#endif
  }

  template <typename TYPE, size_t size>
  void Puts(TYPE* val) {
    // Number of size_t required to store size, round up
    constexpr size_t size_in_sizet{(size + sizeof(size_t) - 1) /
                                   sizeof(size_t)};

    assert(next_memory_ >= memory_);
    assert(next_memory_ + size_in_sizet - 1 < memory_ + memory_size_);

#if DXCB_ENABLE_MEMORY_TRACE && DXCB_ENABLE_VERBOSE_MODE
    size_t* next{next_memory_};
#endif

    *next_memory_ = val != nullptr ? 1 : 0;
    next_memory_++;

    if (val != nullptr) {
      memcpy(next_memory_, val, size);

      next_memory_ += size_in_sizet;
    }

#if DXCB_ENABLE_MEMORY_TRACE
    DXCB_DEBUG_PUT("CBMemoryBuffer::Puts", val, next, next_memory_)
#endif
  }

  // Size known only in runtime.
  template <typename TYPE>
  void Puts(TYPE* val, size_t size) {
    // Number of size_t required to store size, round up
    const size_t size_in_sizet{(size + sizeof(size_t) - 1) / sizeof(size_t)};

    assert(next_memory_ >= memory_);
    assert(next_memory_ + size_in_sizet - 1 < memory_ + memory_size_);

#if DXCB_ENABLE_MEMORY_TRACE && DXCB_ENABLE_VERBOSE_MODE
    size_t* next{next_memory_};
#endif

    *next_memory_ = val != nullptr ? 1 : 0;
    next_memory_++;

    if (val != nullptr) {
      memcpy(next_memory_, val, size);

      next_memory_ += size_in_sizet;
    }

#if DXCB_ENABLE_MEMORY_TRACE
    DXCB_DEBUG_PUT("CBMemoryBuffer::Puts", val, next, next_memory_)
#endif
  }

  // Types of size > size_t.
  DXCB_GET_AND_PUT_OBJECT(D3DCAPS9);
  DXCB_GET_AND_PUT_OBJECT(D3DDEVICE_CREATION_PARAMETERS);
  DXCB_GET_AND_PUT_OBJECT(D3DPRESENT_PARAMETERS);
  DXCB_GET_AND_PUT_OBJECT(CONST RECT);
  DXCB_GET_AND_PUT_OBJECT(CONST RGNDATA);
  DXCB_GET_AND_PUT_OBJECT(CONST D3DGAMMARAMP);
  DXCB_GET_AND_PUT_OBJECT(D3DGAMMARAMP);
  DXCB_GET_AND_PUT_OBJECT(D3DRASTER_STATUS);
  DXCB_GET_AND_PUT_OBJECT(CONST POINT);
  DXCB_GET_AND_PUT_OBJECT(CONST D3DRECT);
  DXCB_GET_AND_PUT_OBJECT(CONST D3DMATRIX);
  DXCB_GET_AND_PUT_OBJECT(D3DMATRIX);
  DXCB_GET_AND_PUT_OBJECT(CONST D3DVIEWPORT9);
  DXCB_GET_AND_PUT_OBJECT(D3DVIEWPORT9);
  DXCB_GET_AND_PUT_OBJECT(CONST D3DMATERIAL9);
  DXCB_GET_AND_PUT_OBJECT(D3DMATERIAL9);
  DXCB_GET_AND_PUT_OBJECT(CONST D3DLIGHT9);
  DXCB_GET_AND_PUT_OBJECT(D3DLIGHT9);
  DXCB_GET_AND_PUT_OBJECT(CONST PALETTEENTRY);
  DXCB_GET_AND_PUT_OBJECT(PALETTEENTRY);
  DXCB_GET_AND_PUT_OBJECT(RECT);
  DXCB_GET_AND_PUT_OBJECT(CONST D3DVERTEXELEMENT9);
  DXCB_GET_AND_PUT_OBJECT(CONST D3DCLIPSTATUS9);
  DXCB_GET_AND_PUT_OBJECT(D3DCLIPSTATUS9);
  DXCB_GET_AND_PUT_OBJECT(CONST D3DRECTPATCH_INFO);
  DXCB_GET_AND_PUT_OBJECT(CONST D3DTRIPATCH_INFO);

  // Types that can be cast as size_t.
  DXCB_GET_AND_PUT_ARCH_WORD(D3DDISPLAYMODE*);
  DXCB_GET_AND_PUT_ARCH_WORD(BOOL*);
  DXCB_GET_AND_PUT_ARCH_WORD(CONST float*);
  DXCB_GET_AND_PUT_ARCH_WORD(float*);
  DXCB_GET_AND_PUT_ARCH_WORD(DWORD*);
  DXCB_GET_AND_PUT_ARCH_WORD(CONST void*);
  DXCB_GET_AND_PUT_ARCH_WORD(CONST DWORD*);
  DXCB_GET_AND_PUT_ARCH_WORD(CONST int*);
  DXCB_GET_AND_PUT_ARCH_WORD(LPUINT);
  DXCB_GET_AND_PUT_ARCH_WORD(void**);
  DXCB_GET_AND_PUT_ARCH_WORD(IDirect3DVertexBuffer9*);
  DXCB_GET_AND_PUT_ARCH_WORD(IDirect3DVertexDeclaration9*);
  DXCB_GET_AND_PUT_ARCH_WORD(IDirect3DIndexBuffer9*);
  DXCB_GET_AND_PUT_ARCH_WORD(IDirect3DSurface9*);
  DXCB_GET_AND_PUT_ARCH_WORD(IDirect3DSwapChain9**);
  DXCB_GET_AND_PUT_ARCH_WORD(HWND);
  DXCB_GET_AND_PUT_ARCH_WORD(IDirect3DSurface9**);
  DXCB_GET_AND_PUT_ARCH_WORD(IDirect3DTexture9**);
  DXCB_GET_AND_PUT_ARCH_WORD(IDirect3DVolumeTexture9**);
  DXCB_GET_AND_PUT_ARCH_WORD(IDirect3DCubeTexture9**);
  DXCB_GET_AND_PUT_ARCH_WORD(IDirect3DVertexBuffer9**);
  DXCB_GET_AND_PUT_ARCH_WORD(IDirect3DIndexBuffer9**);
  DXCB_GET_AND_PUT_ARCH_WORD(IDirect3DBaseTexture9*);
  DXCB_GET_AND_PUT_ARCH_WORD(IDirect3DStateBlock9**);
  DXCB_GET_AND_PUT_ARCH_WORD(IDirect3DBaseTexture9**);
  DXCB_GET_AND_PUT_ARCH_WORD(IDirect3DVertexDeclaration9**);
  DXCB_GET_AND_PUT_ARCH_WORD(IDirect3DVertexShader9**);
  DXCB_GET_AND_PUT_ARCH_WORD(IDirect3DVertexShader9*);
  DXCB_GET_AND_PUT_ARCH_WORD(IDirect3DPixelShader9**);
  DXCB_GET_AND_PUT_ARCH_WORD(IDirect3DPixelShader9*);
  DXCB_GET_AND_PUT_ARCH_WORD(IDirect3DQuery9**);
  DXCB_GET_AND_PUT_ARCH_WORD(IDirect3D9**);

  // Types that can be cast as size_ts.
  DXCB_GET_AND_PUT_ARCH_WORD(D3DPRIMITIVETYPE);
  DXCB_GET_AND_PUT_ARCH_WORD(UINT);
  DXCB_GET_AND_PUT_ARCH_WORD(INT);
  DXCB_GET_AND_PUT_ARCH_WORD(DWORD);
  DXCB_GET_AND_PUT_ARCH_WORD(D3DBACKBUFFER_TYPE);
  DXCB_GET_AND_PUT_ARCH_WORD(D3DFORMAT);
  DXCB_GET_AND_PUT_ARCH_WORD(D3DPOOL);
  DXCB_GET_AND_PUT_ARCH_WORD(D3DMULTISAMPLE_TYPE);
  DXCB_GET_AND_PUT_ARCH_WORD(D3DTEXTUREFILTERTYPE);
  DXCB_GET_AND_PUT_ARCH_WORD(float);
  DXCB_GET_AND_PUT_ARCH_WORD(D3DTRANSFORMSTATETYPE);
  DXCB_GET_AND_PUT_ARCH_WORD(D3DRENDERSTATETYPE);
  DXCB_GET_AND_PUT_ARCH_WORD(D3DSTATEBLOCKTYPE);
  DXCB_GET_AND_PUT_ARCH_WORD(D3DTEXTURESTAGESTATETYPE);
  DXCB_GET_AND_PUT_ARCH_WORD(D3DSAMPLERSTATETYPE);
  DXCB_GET_AND_PUT_ARCH_WORD(D3DQUERYTYPE);

  // Get the unread or unwritten memory size.
  size_t GetAvailableMemorySize() const {
    const size_t ret =
        memory_size_ - static_cast<size_t>(next_memory_ - memory_);
    return ret;
  }

  // Check if there is size size_ts left.
  bool CheckAvailableMemorySize(size_t size) const {
    const size_t available_memory{GetAvailableMemorySize()};

    DXCB_CHECK_MEMORY_SIZE(available_memory, size)

    return size <= available_memory;
  }

 private:
  // Pointer to memory given to us by app.
  size_t* memory_;
  // Size of memory in size_t.
  size_t memory_size_;
  // Pointer to current token position in memory.
  size_t* next_memory_;

  static const char* func_names_[120];
  static const char* Index2FunctionName(unsigned index) {
    return func_names_[index - static_cast<unsigned>(D3d9Commands::Null)];
  }
};

}  // namespace dxcb

#endif  // DXCB_INVOKE_PREPROCESSOR
#endif  // DXCB_CBMEMORYBUFFER_H_