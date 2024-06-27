// Open source.
// See Vincent Scheib rant at
// http://beautifulpixels.blogspot.com/2008/07/parallel-rendering-with-directx-command.html

#ifndef DXCB_CBMACROS_H_
#define DXCB_CBMACROS_H_

#define DXCB_ENABLE_MEMORY_TRACE 0
#define DXCB_ENABLE_VERBOSE_MODE 0

#define DXCB_DEBUG_BREAK() __debugbreak()

//#ifdef __clang__
#define DXCB_FUNCTION
//#else
//#define DXCB_FUNCTION __FUNCTION__
//#endif

#define DXCB_NOT_IMPLEMENTED                                             \
  OutputDebugStringA(                                                    \
      "CBD3D: " DXCB_FUNCTION " not implemented via command buffers.\n"); \
  DXCB_DEBUG_BREAK();
#define DXCB_BOOL_NOT_IMPLEMENTED \
  {                               \
    DXCB_NOT_IMPLEMENTED;         \
    return FALSE;                 \
  }
#define DXCB_D3DERR_NOT_IMPLEMENTED \
  {                                 \
    DXCB_NOT_IMPLEMENTED;           \
    return D3DERR_INVALIDCALL;      \
  }
#define DXCB_FLOAT_NOT_IMPLEMENTED \
  {                                \
    DXCB_NOT_IMPLEMENTED;          \
    return 0.0f;                   \
  }
#define DXCB_LPCSTR_NOT_IMPLEMENTED \
  {                                 \
    DXCB_NOT_IMPLEMENTED;           \
    return nullptr;                 \
  }
#define DXCB_UINT_NOT_IMPLEMENTED \
  {                               \
    DXCB_NOT_IMPLEMENTED;         \
    return 0;                     \
  }
#define DXCB_VOID_NOT_IMPLEMENTED \
  {                               \
    DXCB_NOT_IMPLEMENTED;         \
    return;                       \
  }

#if DXCB_ENABLE_MEMORY_TRACE
#define DXCB_FUNC_DEBUG_TRACE0()                             \
  if (DXCB_TRACE_TARGET) {                                   \
    char temp[300];                                          \
    sprintf_s(temp, DXCB_OPERATION_TYPE __FUNCSIG__ " )\n"); \
    OutputDebugStringA(temp);                                \
  }
#define DXCB_FUNC_DEBUG_TRACE1()                                             \
  if (DXCB_TRACE_TARGET) {                                                   \
    char temp[300];                                                          \
    const size_t *pNext{buffer_->GetNextPtr()};                              \
    sprintf_s(temp, DXCB_OPERATION_TYPE __FUNCSIG__ " 0x%zx )\n", pNext[0]); \
    OutputDebugStringA(temp);                                                \
  }
#define DXCB_FUNC_DEBUG_TRACE2()                                        \
  if (DXCB_TRACE_TARGET) {                                              \
    char temp[300];                                                     \
    const size_t *pNext{buffer_->GetNextPtr()};                         \
    sprintf_s(temp, DXCB_OPERATION_TYPE __FUNCSIG__ " 0x%zx 0x%zx )\n", \
              pNext[0], pNext[1]);                                      \
    OutputDebugStringA(temp);                                           \
  }
#define DXCB_FUNC_DEBUG_TRACE3()                                              \
  if (DXCB_TRACE_TARGET) {                                                    \
    char temp[300];                                                           \
    const size_t *pNext{buffer_->GetNextPtr()};                               \
    sprintf_s(temp, DXCB_OPERATION_TYPE __FUNCSIG__ " 0x%zx 0x%zx 0x%zx )\n", \
              pNext[0], pNext[1], pNext[2]);                                  \
    OutputDebugStringA(temp);                                                 \
  }
#define DXCB_FUNC_DEBUG_TRACE4()                                              \
  if (DXCB_TRACE_TARGET) {                                                    \
    char temp[300];                                                           \
    const size_t *pNext{buffer_->GetNextPtr()};                               \
    sprintf_s(temp,                                                           \
              DXCB_OPERATION_TYPE __FUNCSIG__ " 0x%zx 0x%zx 0x%zx 0x%zx )\n", \
              pNext[0], pNext[1], pNext[2], pNext[3]);                        \
    OutputDebugStringA(temp);                                                 \
  }
#define DXCB_FUNC_DEBUG_TRACE5()                                              \
  if (DXCB_TRACE_TARGET) {                                                    \
    char temp[300];                                                           \
    const size_t *pNext{buffer_->GetNextPtr()};                               \
    sprintf_s(                                                                \
        temp,                                                                 \
        DXCB_OPERATION_TYPE __FUNCSIG__ " 0x%zx 0x%zx 0x%zx 0x%zx 0x%zx )\n", \
        pNext[0], pNext[1], pNext[2], pNext[3], pNext[4]);                    \
    OutputDebugStringA(temp);                                                 \
  }
#define DXCB_FUNC_DEBUG_TRACE6()                                                 \
  if (DXCB_TRACE_TARGET) {                                                       \
    char temp[300];                                                              \
    const size_t *pNext{buffer_->GetNextPtr()};                                  \
    sprintf_s(                                                                \
        temp,                                                                 \
        DXCB_OPERATION_TYPE __FUNCSIG__ " 0x%zx 0x%zx 0x%zx 0x%zx 0x%zx 0x%zx )\n", \
        pNext[0], pNext[1], pNext[2], pNext[3], pNext[4], pNext[5]); \
    OutputDebugStringA(temp);                                                    \
  }
#define DXCB_FUNC_DEBUG_TRACE7()                                                  \
  if (DXCB_TRACE_TARGET) {                                                        \
    char temp[300];                                                               \
    const size_t *pNext{buffer_->GetNextPtr()};                                   \
    sprintf_s(                                                                 \
        temp,                                                                  \
        DXCB_OPERATION_TYPE __FUNCSIG__ " 0x%zx 0x%zx 0x%zx 0x%zx 0x%zx 0x%zx 0x%zx )\n",   \
        pNext[0], pNext[1], pNext[2], pNext[3], pNext[4], pNext[5], pNext[6]); \
    OutputDebugStringA(temp);                                                     \
  }
#define DXCB_FUNC_DEBUG_TRACE8()                                                 \
  if (DXCB_TRACE_TARGET) {                                                       \
    char temp[300];                                                              \
    const size_t *pNext{buffer_->GetNextPtr()};                                  \
    sprintf_s(                                                                \
        temp,                                                                 \
        DXCB_OPERATION_TYPE __FUNCSIG__ " 0x%zx 0x%zx 0x%zx 0x%zx 0x%zx 0x%zx 0x%zx 0x%zx " \
                                  ")\n",                                      \
        pNext[0], pNext[1], pNext[2], pNext[3], pNext[4], pNext[5], pNext[6], \
        pNext[7]); \
    OutputDebugStringA(temp);                                                    \
  }
#define DXCB_FUNC_DEBUG_TRACE9()                   \
  if (DXCB_TRACE_TARGET) {                         \
    char temp[300];                                \
    const size_t *pNext{buffer_->GetNextPtr()};    \
    sprintf_s(                                  \
        temp,                                   \
        DXCB_OPERATION_TYPE __FUNCSIG__ " 0x%zx 0x%zx 0x%zx 0x%zx 0x%zx 0x%zx 0x%zx 0x%zx " \
            "0x%zx )\n",                                                       \
        pNext[0], pNext[1], pNext[2], pNext[3], pNext[4], pNext[5], pNext[6], \
        pNext[7], pNext[8]); \
    OutputDebugStringA(temp);                      \
  }
#define DXCB_OPERATION_TYPE "recording "
#define DXCB_TRACE_TARGET GetBufferPlayTrace()
#else
#define DXCB_FUNC_DEBUG_TRACE0()
#define DXCB_FUNC_DEBUG_TRACE1()
#define DXCB_FUNC_DEBUG_TRACE2()
#define DXCB_FUNC_DEBUG_TRACE3()
#define DXCB_FUNC_DEBUG_TRACE4()
#define DXCB_FUNC_DEBUG_TRACE5()
#define DXCB_FUNC_DEBUG_TRACE6()
#define DXCB_FUNC_DEBUG_TRACE7()
#define DXCB_FUNC_DEBUG_TRACE8()
#define DXCB_FUNC_DEBUG_TRACE9()
#endif

#define DXCB_DECLSPEC_NOTHROW __declspec(nothrow)

//---------------------------------------------------------------------------
// Recording Macros
// Generated from MacroGenerator_Record.xls, do not modify here -------v
#define DXCB_STD_VOID_METHOD_RECORD0(name)                       \
  void DXCB_DECLSPEC_NOTHROW STDMETHODCALLTYPE name() override { \
    DXCB_FUNC_DEBUG_TRACE0();                                    \
    buffer_->Put(D3d9Commands::name);                            \
  }
#define DXCB_STD_VOID_METHOD_RECORD1(name, type1, arg1)                    \
  void DXCB_DECLSPEC_NOTHROW STDMETHODCALLTYPE name(type1 arg1) override { \
    DXCB_FUNC_DEBUG_TRACE1();                                              \
    buffer_->Put(D3d9Commands::name);                                      \
    buffer_->Put(arg1);                                                    \
  }
#define DXCB_STD_VOID_METHOD_RECORD2(name, type1, arg1, type2, arg2)        \
  void DXCB_DECLSPEC_NOTHROW STDMETHODCALLTYPE name(type1 arg1, type2 arg2) \
      override {                                                            \
    DXCB_FUNC_DEBUG_TRACE2();                                               \
    buffer_->Put(D3d9Commands::name);                                       \
    buffer_->Put(arg1);                                                     \
    buffer_->Put(arg2);                                                     \
  }
#define DXCB_STD_VOID_METHOD_RECORD3(name, type1, arg1, type2, arg2, type3, \
                                     arg3)                                  \
  void DXCB_DECLSPEC_NOTHROW STDMETHODCALLTYPE name(type1 arg1, type2 arg2, \
                                                    type3 arg3) override {  \
    DXCB_FUNC_DEBUG_TRACE3();                                               \
    buffer_->Put(D3d9Commands::name);                                       \
    buffer_->Put(arg1);                                                     \
    buffer_->Put(arg2);                                                     \
    buffer_->Put(arg3);                                                     \
  }
#define DXCB_STD_VOID_METHOD_RECORD4(name, type1, arg1, type2, arg2, type3, \
                                     arg3, type4, arg4)                     \
  void DXCB_DECLSPEC_NOTHROW STDMETHODCALLTYPE name(                        \
      type1 arg1, type2 arg2, type3 arg3, type4 arg4) override {            \
    DXCB_FUNC_DEBUG_TRACE4();                                               \
    buffer_->Put(D3d9Commands::name);                                       \
    buffer_->Put(arg1);                                                     \
    buffer_->Put(arg2);                                                     \
    buffer_->Put(arg3);                                                     \
    buffer_->Put(arg4);                                                     \
  }
#define DXCB_STD_VOID_METHOD_RECORD5(name, type1, arg1, type2, arg2, type3,  \
                                     arg3, type4, arg4, type5, arg5)         \
  void DXCB_DECLSPEC_NOTHROW STDMETHODCALLTYPE name(                         \
      type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5) override { \
    DXCB_FUNC_DEBUG_TRACE5();                                                \
    buffer_->Put(D3d9Commands::name);                                        \
    buffer_->Put(arg1);                                                      \
    buffer_->Put(arg2);                                                      \
    buffer_->Put(arg3);                                                      \
    buffer_->Put(arg4);                                                      \
    buffer_->Put(arg5);                                                      \
  }
#define DXCB_STD_VOID_METHOD_RECORD6(name, type1, arg1, type2, arg2, type3,   \
                                     arg3, type4, arg4, type5, arg5, type6,   \
                                     arg6)                                    \
  void DXCB_DECLSPEC_NOTHROW STDMETHODCALLTYPE name(                          \
      type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, type6 arg6) \
      override {                                                              \
    DXCB_FUNC_DEBUG_TRACE6();                                                 \
    buffer_->Put(D3d9Commands::name);                                         \
    buffer_->Put(arg1);                                                       \
    buffer_->Put(arg2);                                                       \
    buffer_->Put(arg3);                                                       \
    buffer_->Put(arg4);                                                       \
    buffer_->Put(arg5);                                                       \
    buffer_->Put(arg6);                                                       \
  }
#define DXCB_STD_VOID_METHOD_RECORD7(name, type1, arg1, type2, arg2, type3,   \
                                     arg3, type4, arg4, type5, arg5, type6,   \
                                     arg6, type7, arg7)                       \
  void DXCB_DECLSPEC_NOTHROW STDMETHODCALLTYPE name(                          \
      type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, type6 arg6, \
      type7 arg7) override {                                                  \
    DXCB_FUNC_DEBUG_TRACE7();                                                 \
    buffer_->Put(D3d9Commands::name);                                         \
    buffer_->Put(arg1);                                                       \
    buffer_->Put(arg2);                                                       \
    buffer_->Put(arg3);                                                       \
    buffer_->Put(arg4);                                                       \
    buffer_->Put(arg5);                                                       \
    buffer_->Put(arg6);                                                       \
    buffer_->Put(arg7);                                                       \
  }
#define DXCB_STD_VOID_METHOD_RECORD8(name, type1, arg1, type2, arg2, type3,   \
                                     arg3, type4, arg4, type5, arg5, type6,   \
                                     arg6, type7, arg7, type8, arg8)          \
  void DXCB_DECLSPEC_NOTHROW STDMETHODCALLTYPE name(                          \
      type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, type6 arg6, \
      type7 arg7, type8 arg8) override {                                      \
    DXCB_FUNC_DEBUG_TRACE8();                                                 \
    buffer_->Put(D3d9Commands::name);                                         \
    buffer_->Put(arg1);                                                       \
    buffer_->Put(arg2);                                                       \
    buffer_->Put(arg3);                                                       \
    buffer_->Put(arg4);                                                       \
    buffer_->Put(arg5);                                                       \
    buffer_->Put(arg6);                                                       \
    buffer_->Put(arg7);                                                       \
    buffer_->Put(arg8);                                                       \
  }
#define DXCB_STD_VOID_METHOD_RECORD9(                                         \
    name, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5,    \
    type6, arg6, type7, arg7, type8, arg8, type9, arg9)                       \
  void DXCB_DECLSPEC_NOTHROW STDMETHODCALLTYPE name(                          \
      type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, type6 arg6, \
      type7 arg7, type8 arg8, type9 arg9) override {                          \
    DXCB_FUNC_DEBUG_TRACE9();                                                 \
    buffer_->Put(D3d9Commands::name);                                         \
    buffer_->Put(arg1);                                                       \
    buffer_->Put(arg2);                                                       \
    buffer_->Put(arg3);                                                       \
    buffer_->Put(arg4);                                                       \
    buffer_->Put(arg5);                                                       \
    buffer_->Put(arg6);                                                       \
    buffer_->Put(arg7);                                                       \
    buffer_->Put(arg8);                                                       \
    buffer_->Put(arg9);                                                       \
  }
#define DXCB_STD_METHOD_RECORD0(name)                               \
  HRESULT DXCB_DECLSPEC_NOTHROW STDMETHODCALLTYPE name() override { \
    DXCB_FUNC_DEBUG_TRACE0();                                       \
    buffer_->Put(D3d9Commands::name);                               \
    return D3D_OK;                                                  \
  }
#define DXCB_STD_METHOD_RECORD1(name, type1, arg1)                            \
  HRESULT DXCB_DECLSPEC_NOTHROW STDMETHODCALLTYPE name(type1 arg1) override { \
    DXCB_FUNC_DEBUG_TRACE1();                                                 \
    buffer_->Put(D3d9Commands::name);                                         \
    buffer_->Put(arg1);                                                       \
    return D3D_OK;                                                            \
  }
#define DXCB_STD_METHOD_RECORD2(name, type1, arg1, type2, arg2)                \
  HRESULT DXCB_DECLSPEC_NOTHROW STDMETHODCALLTYPE name(type1 arg1, type2 arg2) \
      override {                                                               \
    DXCB_FUNC_DEBUG_TRACE2();                                                  \
    buffer_->Put(D3d9Commands::name);                                          \
    buffer_->Put(arg1);                                                        \
    buffer_->Put(arg2);                                                        \
    return D3D_OK;                                                             \
  }
#define DXCB_STD_METHOD_RECORD3(name, type1, arg1, type2, arg2, type3, arg3)   \
  HRESULT DXCB_DECLSPEC_NOTHROW STDMETHODCALLTYPE name(type1 arg1, type2 arg2, \
                                                       type3 arg3) override {  \
    DXCB_FUNC_DEBUG_TRACE3();                                                  \
    buffer_->Put(D3d9Commands::name);                                          \
    buffer_->Put(arg1);                                                        \
    buffer_->Put(arg2);                                                        \
    buffer_->Put(arg3);                                                        \
    return D3D_OK;                                                             \
  }
#define DXCB_STD_METHOD_RECORD4(name, type1, arg1, type2, arg2, type3, arg3, \
                                type4, arg4)                                 \
  HRESULT DXCB_DECLSPEC_NOTHROW STDMETHODCALLTYPE name(                      \
      type1 arg1, type2 arg2, type3 arg3, type4 arg4) override {             \
    DXCB_FUNC_DEBUG_TRACE4();                                                \
    buffer_->Put(D3d9Commands::name);                                        \
    buffer_->Put(arg1);                                                      \
    buffer_->Put(arg2);                                                      \
    buffer_->Put(arg3);                                                      \
    buffer_->Put(arg4);                                                      \
    return D3D_OK;                                                           \
  }
#define DXCB_STD_METHOD_RECORD5(name, type1, arg1, type2, arg2, type3, arg3, \
                                type4, arg4, type5, arg5)                    \
  HRESULT DXCB_DECLSPEC_NOTHROW STDMETHODCALLTYPE name(                      \
      type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5) override { \
    DXCB_FUNC_DEBUG_TRACE5();                                                \
    buffer_->Put(D3d9Commands::name);                                        \
    buffer_->Put(arg1);                                                      \
    buffer_->Put(arg2);                                                      \
    buffer_->Put(arg3);                                                      \
    buffer_->Put(arg4);                                                      \
    buffer_->Put(arg5);                                                      \
    return D3D_OK;                                                           \
  }
#define DXCB_STD_METHOD_RECORD6(name, type1, arg1, type2, arg2, type3, arg3,  \
                                type4, arg4, type5, arg5, type6, arg6)        \
  HRESULT DXCB_DECLSPEC_NOTHROW STDMETHODCALLTYPE name(                       \
      type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, type6 arg6) \
      override {                                                              \
    DXCB_FUNC_DEBUG_TRACE6();                                                 \
    buffer_->Put(D3d9Commands::name);                                         \
    buffer_->Put(arg1);                                                       \
    buffer_->Put(arg2);                                                       \
    buffer_->Put(arg3);                                                       \
    buffer_->Put(arg4);                                                       \
    buffer_->Put(arg5);                                                       \
    buffer_->Put(arg6);                                                       \
    return D3D_OK;                                                            \
  }
#define DXCB_STD_METHOD_RECORD7(name, type1, arg1, type2, arg2, type3, arg3,  \
                                type4, arg4, type5, arg5, type6, arg6, type7, \
                                arg7)                                         \
  HRESULT DXCB_DECLSPEC_NOTHROW STDMETHODCALLTYPE name(                       \
      type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, type6 arg6, \
      type7 arg7) override {                                                  \
    DXCB_FUNC_DEBUG_TRACE7();                                                 \
    buffer_->Put(D3d9Commands::name);                                         \
    buffer_->Put(arg1);                                                       \
    buffer_->Put(arg2);                                                       \
    buffer_->Put(arg3);                                                       \
    buffer_->Put(arg4);                                                       \
    buffer_->Put(arg5);                                                       \
    buffer_->Put(arg6);                                                       \
    buffer_->Put(arg7);                                                       \
    return D3D_OK;                                                            \
  }
#define DXCB_STD_METHOD_RECORD8(name, type1, arg1, type2, arg2, type3, arg3,  \
                                type4, arg4, type5, arg5, type6, arg6, type7, \
                                arg7, type8, arg8)                            \
  HRESULT DXCB_DECLSPEC_NOTHROW STDMETHODCALLTYPE name(                       \
      type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, type6 arg6, \
      type7 arg7, type8 arg8) override {                                      \
    DXCB_FUNC_DEBUG_TRACE8();                                                 \
    buffer_->Put(D3d9Commands::name);                                         \
    buffer_->Put(arg1);                                                       \
    buffer_->Put(arg2);                                                       \
    buffer_->Put(arg3);                                                       \
    buffer_->Put(arg4);                                                       \
    buffer_->Put(arg5);                                                       \
    buffer_->Put(arg6);                                                       \
    buffer_->Put(arg7);                                                       \
    buffer_->Put(arg8);                                                       \
    return D3D_OK;                                                            \
  }
#define DXCB_STD_METHOD_RECORD9(name, type1, arg1, type2, arg2, type3, arg3,  \
                                type4, arg4, type5, arg5, type6, arg6, type7, \
                                arg7, type8, arg8, type9, arg9)               \
  HRESULT DXCB_DECLSPEC_NOTHROW STDMETHODCALLTYPE name(                       \
      type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, type6 arg6, \
      type7 arg7, type8 arg8, type9 arg9) override {                          \
    DXCB_FUNC_DEBUG_TRACE9();                                                 \
    buffer_->Put(D3d9Commands::name);                                         \
    buffer_->Put(arg1);                                                       \
    buffer_->Put(arg2);                                                       \
    buffer_->Put(arg3);                                                       \
    buffer_->Put(arg4);                                                       \
    buffer_->Put(arg5);                                                       \
    buffer_->Put(arg6);                                                       \
    buffer_->Put(arg7);                                                       \
    buffer_->Put(arg8);                                                       \
    buffer_->Put(arg9);                                                       \
    return D3D_OK;                                                            \
  }
// Generated from MacroGenerator_Record.xls, do not modify here -------^

#define DXCB_STD_RETURN_METHOD_RECORD0(rettype, retval, name)       \
  rettype DXCB_DECLSPEC_NOTHROW STDMETHODCALLTYPE name() override { \
    DXCB_FUNC_DEBUG_TRACE0();                                       \
    buffer_->Put(D3d9Commands::name);                               \
    return retval;                                                  \
  }

// required for setting constants.
#define DXCB_STD_METHOD_RECORD_CONSTS(name, type0, arg0, type1, arg1, type2,   \
                                      arg2, array_type)                        \
  HRESULT DXCB_DECLSPEC_NOTHROW STDMETHODCALLTYPE name(type0 arg0, type1 arg1, \
                                                       type2 arg2) override {  \
    DXCB_FUNC_DEBUG_TRACE2()                                                   \
    buffer_->Put(D3d9Commands::name);                                          \
    buffer_->Put(arg0);                                                        \
    buffer_->Put(arg2);                                                        \
    buffer_->Puts(arg1, arg2 * 4 * sizeof(array_type));                        \
    return D3D_OK;                                                             \
  }

#if DXCB_ENABLE_MEMORY_TRACE
#undef DXCB_OPERATION_TYPE
#undef DXCB_TRACE_TARGET

#define DXCB_OPERATION_TYPE "playing "
#define DXCB_TRACE_TARGET GetBufferRecordTrace()
#endif

//---------------------------------------------------------------------------
// Playback Macros
// Generated from MacroGenerator_Playback.xls, do not modify here
// -------v
#define DXCB_STD_VOID_METHOD_PLAY0(func, name) \
  void func() {                                \
    DXCB_FUNC_DEBUG_TRACE0();                  \
    d3d9_device_->name();                      \
  }
#define DXCB_STD_VOID_METHOD_PLAY1(func, name, type1) \
  void func() {                                       \
    DXCB_FUNC_DEBUG_TRACE1();                         \
    type1 arg1;                                       \
    buffer_->Get(&arg1);                              \
    d3d9_device_->name(arg1);                         \
  }
#define DXCB_STD_VOID_METHOD_PLAY2(func, name, type1, type2) \
  void func() {                                              \
    DXCB_FUNC_DEBUG_TRACE2();                                \
    type1 arg1;                                              \
    buffer_->Get(&arg1);                                     \
    type2 arg2;                                              \
    buffer_->Get(&arg2);                                     \
    d3d9_device_->name(arg1, arg2);                          \
  }
#define DXCB_STD_VOID_METHOD_PLAY3(func, name, type1, type2, type3) \
  void func() {                                                     \
    DXCB_FUNC_DEBUG_TRACE3();                                       \
    type1 arg1;                                                     \
    buffer_->Get(&arg1);                                            \
    type2 arg2;                                                     \
    buffer_->Get(&arg2);                                            \
    type3 arg3;                                                     \
    buffer_->Get(&arg3);                                            \
    d3d9_device_->name(arg1, arg2, arg3);                           \
  }
#define DXCB_STD_VOID_METHOD_PLAY4(func, name, type1, type2, type3, type4) \
  void func() {                                                            \
    DXCB_FUNC_DEBUG_TRACE4();                                              \
    type1 arg1;                                                            \
    buffer_->Get(&arg1);                                                   \
    type2 arg2;                                                            \
    buffer_->Get(&arg2);                                                   \
    type3 arg3;                                                            \
    buffer_->Get(&arg3);                                                   \
    type4 arg4;                                                            \
    buffer_->Get(&arg4);                                                   \
    d3d9_device_->name(arg1, arg2, arg3, arg4);                            \
  }
#define DXCB_STD_VOID_METHOD_PLAY5(func, name, type1, type2, type3, type4, \
                                   type5)                                  \
  void func() {                                                            \
    DXCB_FUNC_DEBUG_TRACE5();                                              \
    type1 arg1;                                                            \
    buffer_->Get(&arg1);                                                   \
    type2 arg2;                                                            \
    buffer_->Get(&arg2);                                                   \
    type3 arg3;                                                            \
    buffer_->Get(&arg3);                                                   \
    type4 arg4;                                                            \
    buffer_->Get(&arg4);                                                   \
    type5 arg5;                                                            \
    buffer_->Get(&arg5);                                                   \
    d3d9_device_->name(arg1, arg2, arg3, arg4, arg5);                      \
  }
#define DXCB_STD_VOID_METHOD_PLAY6(func, name, type1, type2, type3, type4, \
                                   type5, type6)                           \
  void func() {                                                            \
    DXCB_FUNC_DEBUG_TRACE6();                                              \
    type1 arg1;                                                            \
    buffer_->Get(&arg1);                                                   \
    type2 arg2;                                                            \
    buffer_->Get(&arg2);                                                   \
    type3 arg3;                                                            \
    buffer_->Get(&arg3);                                                   \
    type4 arg4;                                                            \
    buffer_->Get(&arg4);                                                   \
    type5 arg5;                                                            \
    buffer_->Get(&arg5);                                                   \
    type6 arg6;                                                            \
    buffer_->Get(&arg6);                                                   \
    d3d9_device_->name(arg1, arg2, arg3, arg4, arg5, arg6);                \
  }
#define DXCB_STD_VOID_METHOD_PLAY7(func, name, type1, type2, type3, type4, \
                                   type5, type6, type7)                    \
  void func() {                                                            \
    DXCB_FUNC_DEBUG_TRACE7();                                              \
    type1 arg1;                                                            \
    buffer_->Get(&arg1);                                                   \
    type2 arg2;                                                            \
    buffer_->Get(&arg2);                                                   \
    type3 arg3;                                                            \
    buffer_->Get(&arg3);                                                   \
    type4 arg4;                                                            \
    buffer_->Get(&arg4);                                                   \
    type5 arg5;                                                            \
    buffer_->Get(&arg5);                                                   \
    type6 arg6;                                                            \
    buffer_->Get(&arg6);                                                   \
    type7 arg7;                                                            \
    buffer_->Get(&arg7);                                                   \
    d3d9_device_->name(arg1, arg2, arg3, arg4, arg5, arg6, arg7);          \
  }
#define DXCB_STD_VOID_METHOD_PLAY8(func, name, type1, type2, type3, type4, \
                                   type5, type6, type7, type8)             \
  void func() {                                                            \
    DXCB_FUNC_DEBUG_TRACE8();                                              \
    type1 arg1;                                                            \
    buffer_->Get(&arg1);                                                   \
    type2 arg2;                                                            \
    buffer_->Get(&arg2);                                                   \
    type3 arg3;                                                            \
    buffer_->Get(&arg3);                                                   \
    type4 arg4;                                                            \
    buffer_->Get(&arg4);                                                   \
    type5 arg5;                                                            \
    buffer_->Get(&arg5);                                                   \
    type6 arg6;                                                            \
    buffer_->Get(&arg6);                                                   \
    type7 arg7;                                                            \
    buffer_->Get(&arg7);                                                   \
    type8 arg8;                                                            \
    buffer_->Get(&arg8);                                                   \
    d3d9_device_->name(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);    \
  }
#define DXCB_STD_VOID_METHOD_PLAY9(func, name, type1, type2, type3, type4,    \
                                   type5, type6, type7, type8, type9)         \
  void func() {                                                               \
    DXCB_FUNC_DEBUG_TRACE9();                                                 \
    type1 arg1;                                                               \
    buffer_->Get(&arg1);                                                      \
    type2 arg2;                                                               \
    buffer_->Get(&arg2);                                                      \
    type3 arg3;                                                               \
    buffer_->Get(&arg3);                                                      \
    type4 arg4;                                                               \
    buffer_->Get(&arg4);                                                      \
    type5 arg5;                                                               \
    buffer_->Get(&arg5);                                                      \
    type6 arg6;                                                               \
    buffer_->Get(&arg6);                                                      \
    type7 arg7;                                                               \
    buffer_->Get(&arg7);                                                      \
    type8 arg8;                                                               \
    buffer_->Get(&arg8);                                                      \
    type9 arg9;                                                               \
    buffer_->Get(&arg9);                                                      \
    d3d9_device_->name(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9); \
  }
#define DXCB_STD_METHOD_PLAY0(func, name)                       \
  void func() {                                                 \
    DXCB_FUNC_DEBUG_TRACE0();                                   \
    if (FAILED(d3d9_device_->name()))                           \
      OutputDebugStringA(DXCB_FUNCTION " failed in playback\n"); \
  }
#define DXCB_STD_METHOD_PLAY1(func, name, type1)                \
  void func() {                                                 \
    DXCB_FUNC_DEBUG_TRACE1();                                   \
    type1 arg1;                                                 \
    buffer_->Get(&arg1);                                        \
    if (FAILED(d3d9_device_->name(arg1)))                       \
      OutputDebugStringA(DXCB_FUNCTION " failed in playback\n"); \
  }
#define DXCB_STD_METHOD_PLAY2(func, name, type1, type2)         \
  void func() {                                                 \
    DXCB_FUNC_DEBUG_TRACE2();                                   \
    type1 arg1;                                                 \
    buffer_->Get(&arg1);                                        \
    type2 arg2;                                                 \
    buffer_->Get(&arg2);                                        \
    if (FAILED(d3d9_device_->name(arg1, arg2)))                 \
      OutputDebugStringA(DXCB_FUNCTION " failed in playback\n"); \
  }
#define DXCB_STD_METHOD_PLAY3(func, name, type1, type2, type3)  \
  void func() {                                                 \
    DXCB_FUNC_DEBUG_TRACE3();                                   \
    type1 arg1;                                                 \
    buffer_->Get(&arg1);                                        \
    type2 arg2;                                                 \
    buffer_->Get(&arg2);                                        \
    type3 arg3;                                                 \
    buffer_->Get(&arg3);                                        \
    if (FAILED(d3d9_device_->name(arg1, arg2, arg3)))           \
      OutputDebugStringA(DXCB_FUNCTION " failed in playback\n"); \
  }
#define DXCB_STD_METHOD_PLAY4(func, name, type1, type2, type3, type4) \
  void func() {                                                       \
    DXCB_FUNC_DEBUG_TRACE4();                                         \
    type1 arg1;                                                       \
    buffer_->Get(&arg1);                                              \
    type2 arg2;                                                       \
    buffer_->Get(&arg2);                                              \
    type3 arg3;                                                       \
    buffer_->Get(&arg3);                                              \
    type4 arg4;                                                       \
    buffer_->Get(&arg4);                                              \
    if (FAILED(d3d9_device_->name(arg1, arg2, arg3, arg4)))           \
      OutputDebugStringA(DXCB_FUNCTION " failed in playback\n");       \
  }
#define DXCB_STD_METHOD_PLAY5(func, name, type1, type2, type3, type4, type5) \
  void func() {                                                              \
    DXCB_FUNC_DEBUG_TRACE5();                                                \
    type1 arg1;                                                              \
    buffer_->Get(&arg1);                                                     \
    type2 arg2;                                                              \
    buffer_->Get(&arg2);                                                     \
    type3 arg3;                                                              \
    buffer_->Get(&arg3);                                                     \
    type4 arg4;                                                              \
    buffer_->Get(&arg4);                                                     \
    type5 arg5;                                                              \
    buffer_->Get(&arg5);                                                     \
    if (FAILED(d3d9_device_->name(arg1, arg2, arg3, arg4, arg5)))            \
      OutputDebugStringA(DXCB_FUNCTION " failed in playback\n");              \
  }
#define DXCB_STD_METHOD_PLAY6(func, name, type1, type2, type3, type4, type5, \
                              type6)                                         \
  void func() {                                                              \
    DXCB_FUNC_DEBUG_TRACE6();                                                \
    type1 arg1;                                                              \
    buffer_->Get(&arg1);                                                     \
    type2 arg2;                                                              \
    buffer_->Get(&arg2);                                                     \
    type3 arg3;                                                              \
    buffer_->Get(&arg3);                                                     \
    type4 arg4;                                                              \
    buffer_->Get(&arg4);                                                     \
    type5 arg5;                                                              \
    buffer_->Get(&arg5);                                                     \
    type6 arg6;                                                              \
    buffer_->Get(&arg6);                                                     \
    if (FAILED(d3d9_device_->name(arg1, arg2, arg3, arg4, arg5, arg6)))      \
      OutputDebugStringA(DXCB_FUNCTION " failed in playback\n");              \
  }
#define DXCB_STD_METHOD_PLAY7(func, name, type1, type2, type3, type4, type5,  \
                              type6, type7)                                   \
  void func() {                                                               \
    DXCB_FUNC_DEBUG_TRACE7();                                                 \
    type1 arg1;                                                               \
    buffer_->Get(&arg1);                                                      \
    type2 arg2;                                                               \
    buffer_->Get(&arg2);                                                      \
    type3 arg3;                                                               \
    buffer_->Get(&arg3);                                                      \
    type4 arg4;                                                               \
    buffer_->Get(&arg4);                                                      \
    type5 arg5;                                                               \
    buffer_->Get(&arg5);                                                      \
    type6 arg6;                                                               \
    buffer_->Get(&arg6);                                                      \
    type7 arg7;                                                               \
    buffer_->Get(&arg7);                                                      \
    if (FAILED(d3d9_device_->name(arg1, arg2, arg3, arg4, arg5, arg6, arg7))) \
      OutputDebugStringA(DXCB_FUNCTION " failed in playback\n");               \
  }
#define DXCB_STD_METHOD_PLAY8(func, name, type1, type2, type3, type4, type5, \
                              type6, type7, type8)                           \
  void func() {                                                              \
    DXCB_FUNC_DEBUG_TRACE8();                                                \
    type1 arg1;                                                              \
    buffer_->Get(&arg1);                                                     \
    type2 arg2;                                                              \
    buffer_->Get(&arg2);                                                     \
    type3 arg3;                                                              \
    buffer_->Get(&arg3);                                                     \
    type4 arg4;                                                              \
    buffer_->Get(&arg4);                                                     \
    type5 arg5;                                                              \
    buffer_->Get(&arg5);                                                     \
    type6 arg6;                                                              \
    buffer_->Get(&arg6);                                                     \
    type7 arg7;                                                              \
    buffer_->Get(&arg7);                                                     \
    type8 arg8;                                                              \
    buffer_->Get(&arg8);                                                     \
    if (FAILED(d3d9_device_->name(arg1, arg2, arg3, arg4, arg5, arg6, arg7,  \
                                  arg8)))                                    \
      OutputDebugStringA(DXCB_FUNCTION " failed in playback\n");              \
  }
#define DXCB_STD_METHOD_PLAY9(func, name, type1, type2, type3, type4, type5, \
                              type6, type7, type8, type9)                    \
  void func() {                                                              \
    DXCB_FUNC_DEBUG_TRACE9();                                                \
    type1 arg1;                                                              \
    buffer_->Get(&arg1);                                                     \
    type2 arg2;                                                              \
    buffer_->Get(&arg2);                                                     \
    type3 arg3;                                                              \
    buffer_->Get(&arg3);                                                     \
    type4 arg4;                                                              \
    buffer_->Get(&arg4);                                                     \
    type5 arg5;                                                              \
    buffer_->Get(&arg5);                                                     \
    type6 arg6;                                                              \
    buffer_->Get(&arg6);                                                     \
    type7 arg7;                                                              \
    buffer_->Get(&arg7);                                                     \
    type8 arg8;                                                              \
    buffer_->Get(&arg8);                                                     \
    type9 arg9;                                                              \
    buffer_->Get(&arg9);                                                     \
    if (FAILED(d3d9_device_->name(arg1, arg2, arg3, arg4, arg5, arg6, arg7,  \
                                  arg8, arg9)))                              \
      OutputDebugStringA(DXCB_FUNCTION " failed in playback\n");              \
  }
#define DXCB_ULONG_METHOD_PLAY0(func, name) \
  void func() {                             \
    DXCB_FUNC_DEBUG_TRACE0();               \
    d3d9_device_->name();                   \
  }
// Generated from MacroGenerator_Playback.xls, do not modify here
// -------^

// this is used primarily to read from memory buffer and play shader
// constant set calls.
#define DXCB_STD_METHOD_PLAY_CONSTS(func, name, type0, type1, type2, \
                                    array_type)                      \
  void func() {                                                      \
    DXCB_FUNC_DEBUG_TRACE2()                                         \
    type0 arg0;                                                      \
    buffer_->Get(&arg0);                                             \
    type2 arg2;                                                      \
    buffer_->Get(&arg2);                                             \
    const size_t iSize{arg2 * 4 * sizeof(array_type)};               \
    type1 arg1{buffer_->Gets<std::remove_pointer_t<type1>>(iSize)};  \
    if (FAILED(d3d9_device_->name(arg0, arg1, arg2)))                \
      OutputDebugStringA(DXCB_FUNCTION " failed in playback\n");      \
  }

//---------------------------------------------------------------------------
// Get and Put macros
#define DXCB_PUT_ARCH_WORD(type0) \
  void Put(type0 arg) { Puts(arg); }
#define DXCB_PUT_OBJECT(type0) \
  void Put(type0 *arg) { Puts<type0, sizeof(type0)>(arg); }
#define DXCB_GET_ARCH_WORD(type0) \
  void Get(type0 *arg) { *arg = Gets<type0>(); }
#define DXCB_GET_OBJECT(type0) \
  void Get(type0 **arg) { *arg = Gets<type0, sizeof(type0)>(); }
#define DXCB_GET_AND_PUT_OBJECT(type0) \
  DXCB_GET_OBJECT(type0) DXCB_PUT_OBJECT(type0)
#define DXCB_GET_AND_PUT_ARCH_WORD(type0) \
  DXCB_GET_ARCH_WORD(type0) DXCB_PUT_ARCH_WORD(type0)

#if DXCB_ENABLE_MEMORY_TRACE
#if DXCB_ENABLE_VERBOSE_MODE
#define DXCB_DEBUG_GET(fname, returnvalue, originalnextptr, nextptr)       \
  {                                                                        \
    if (GetMemoryTrace()) {                                                \
      char temp[256];                                                      \
      sprintf_s(                                                           \
          temp,                                                            \
          "%s returned %zx, this token at 0x%p, next token at 0x%p, diff " \
          "= %td\n",                                                       \
          fname,                                                           \
          (std::is_pointer_v<decltype(returnvalue)> ||                     \
           sizeof(returnvalue) <= sizeof(size_t))                          \
              ? (size_t)returnvalue                                        \
              : (size_t)&returnvalue,                                      \
          originalnextptr, nextptr, (nextptr - originalnextptr));          \
      OutputDebugStringA(temp);                                            \
    }                                                                      \
  }
#define DXCB_DEBUG_PUT(fname, returnvalue, originalnextptr, nextptr)       \
  {                                                                        \
    if (GetMemoryTrace()) {                                                \
      char temp[256];                                                      \
      sprintf_s(                                                           \
          temp,                                                            \
          "%s returned %zx, this token at 0x%p, next token at 0x%p, diff " \
          "= %td\n",                                                       \
          fname,                                                           \
          (std::is_pointer_v<decltype(returnvalue)> ||                     \
           sizeof(returnvalue) <= sizeof(size_t))                          \
              ? (size_t)returnvalue                                        \
              : (size_t)&returnvalue,                                      \
          originalnextptr, nextptr, (nextptr - originalnextptr));          \
      OutputDebugStringA(temp);                                            \
    }                                                                      \
  }
#else
#define DXCB_DEBUG_GET(fname, returnvalue, originalnextptr, nextptr) \
  {                                                                  \
    if (GetMemoryTrace()) {                                          \
      char temp[32];                                                 \
      sprintf_s(temp, " 0x%zx\n ",                                   \
                (std::is_pointer_v<decltype(returnvalue)> ||         \
                 sizeof(returnvalue) <= sizeof(size_t))              \
                    ? (size_t)returnvalue                            \
                    : (size_t)&returnvalue);                         \
      OutputDebugStringA(temp);                                      \
    }                                                                \
  }
#define DXCB_DEBUG_PUT(fname, returnvalue, originalnextptr, nextptr) \
  {                                                                  \
    if (GetMemoryTrace()) {                                          \
      char temp[32];                                                 \
      sprintf_s(temp, " 0x%zx ",                                     \
                (std::is_pointer_v<decltype(returnvalue)> ||         \
                 sizeof(returnvalue) <= sizeof(size_t))              \
                    ? (size_t)returnvalue                            \
                    : (size_t)&returnvalue);                         \
      OutputDebugStringA(temp);                                      \
    }                                                                \
  }
#endif
#define DXCB_CHECK_MEMORY_SIZE(AvailableMemory, iSize)               \
  {                                                                  \
    if (GetMemoryTrace()) {                                          \
      char temp[128];                                                \
      sprintf_s(temp, "%zu available memory checked for size %zu\n", \
                AvailableMemory, iSize);                             \
      OutputDebugStringA(temp);                                      \
    }                                                                \
  }
#else
#define DXCB_DEBUG_GET(fname, returnvalue, originalnextptr, nextptr)
#define DXCB_DEBUG_PUT(fname, returnvalue, originalnextptr, nextptr)
#define DXCB_CHECK_MEMORY_SIZE(AvailableMemory, iSize)
#endif

using LPUINT = unsigned *;
using LPD3DCAPS9 = struct _D3DCAPS9 *;

#define DXCB_MIN(a, b) (((a) < (b)) ? (a) : (b))
#define DXCB_MAX(a, b) (((a) > (b)) ? (a) : (b))

#endif  // DXCB_CBMACROS_H_