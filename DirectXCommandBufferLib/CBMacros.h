// Open source.
// See Vincent Scheib rant at http://beautifulpixels.blogspot.com/2008/07/parallel-rendering-with-directx-command.html

#ifndef DIRECTX_COMMAND_BUFFER_CBMACROS_H_
#define DIRECTX_COMMAND_BUFFER_CBMACROS_H_

#define MEMTRACE 0
#define VERBOSE 0

#define CBD3D_BREAK() __debugbreak()

#define CBD3D_NOTIMPLIMENTED OutputDebugStringA("CBD3D: " __FUNCTION__ " not implemented via command buffers.\n"); CBD3D_BREAK();
#define CBD3D_BOOL_NOTIMPLIMENTED    { CBD3D_NOTIMPLIMENTED; return FALSE; }
#define CBD3D_D3DERR_NOTIMPLIMENTED  { CBD3D_NOTIMPLIMENTED; return D3DERR_INVALIDCALL; }
#define CBD3D_FLOAT_NOTIMPLIMENTED   { CBD3D_NOTIMPLIMENTED; return 0.0f; }
#define CBD3D_LPCSTR_NOTIMPLIMENTED  { CBD3D_NOTIMPLIMENTED; return NULL; }
#define CBD3D_UINT_NOTIMPLIMENTED    { CBD3D_NOTIMPLIMENTED; return 0; }
#define CBD3D_VOID_NOTIMPLIMENTED    { CBD3D_NOTIMPLIMENTED; return; }


#if MEMTRACE
#define FUNCTIONNAME_DEBUG_TRACE()   if( TRACETARGET ) { char temp[300]; DWORD *pNext = m_pCB->m_pNext; sprintf_s(temp,299, OPERATIONTYPE __FUNCSIG__ " )\n" ); OutputDebugStringA(temp); }
#define FUNCTIONNAME_DEBUG_TRACE0()  if( TRACETARGET ) { char temp[300]; DWORD *pNext = m_pCB->m_pNext; sprintf_s(temp,299, OPERATIONTYPE __FUNCSIG__ " )\n" ); OutputDebugStringA(temp); }
#define FUNCTIONNAME_DEBUG_TRACE1()  if( TRACETARGET ) { char temp[300]; DWORD *pNext = m_pCB->m_pNext; sprintf_s(temp,299, OPERATIONTYPE __FUNCSIG__ " 0x%x )\n",pNext[0] ); OutputDebugStringA(temp); }
#define FUNCTIONNAME_DEBUG_TRACE2()  if( TRACETARGET ) { char temp[300]; DWORD *pNext = m_pCB->m_pNext; sprintf_s(temp,299, OPERATIONTYPE __FUNCSIG__ " 0x%x )\n",pNext[0],pNext[1] ); OutputDebugStringA(temp); }
#define FUNCTIONNAME_DEBUG_TRACE3()  if( TRACETARGET ) { char temp[300]; DWORD *pNext = m_pCB->m_pNext; sprintf_s(temp,299, OPERATIONTYPE __FUNCSIG__ " 0x%x 0x%x 0x%x )\n",pNext[0],pNext[1],pNext[2] ); OutputDebugStringA(temp); }
#define FUNCTIONNAME_DEBUG_TRACE4()  if( TRACETARGET ) { char temp[300]; DWORD *pNext = m_pCB->m_pNext; sprintf_s(temp,299, OPERATIONTYPE __FUNCSIG__ " 0x%x 0x%x 0x%x 0x%x )\n",pNext[0],pNext[1],pNext[2],pNext[3] ); OutputDebugStringA(temp); }
#define FUNCTIONNAME_DEBUG_TRACE5()  if( TRACETARGET ) { char temp[300]; DWORD *pNext = m_pCB->m_pNext; sprintf_s(temp,299, OPERATIONTYPE __FUNCSIG__ " 0x%x 0x%x 0x%x 0x%x 0x%x )\n",pNext[0],pNext[1],pNext[2],pNext[3],pNext[4] ); OutputDebugStringA(temp); }
#define FUNCTIONNAME_DEBUG_TRACE6()  if( TRACETARGET ) { char temp[300]; DWORD *pNext = m_pCB->m_pNext; sprintf_s(temp,299, OPERATIONTYPE __FUNCSIG__ " 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x )\n",pNext[0],pNext[1],pNext[2],pNext[3],pNext[4],pNext[5] ); OutputDebugStringA(temp); }
#define FUNCTIONNAME_DEBUG_TRACE7()  if( TRACETARGET ) { char temp[300]; DWORD *pNext = m_pCB->m_pNext; sprintf_s(temp,299, OPERATIONTYPE __FUNCSIG__ " 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x )\n",pNext[0],pNext[1],pNext[2],pNext[3],pNext[4],pNext[5],pNext[6] ); OutputDebugStringA(temp); }
#define FUNCTIONNAME_DEBUG_TRACE8()  if( TRACETARGET ) { char temp[300]; DWORD *pNext = m_pCB->m_pNext; sprintf_s(temp,299, OPERATIONTYPE __FUNCSIG__ " 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x )\n",pNext[0],pNext[1],pNext[2],pNext[3],pNext[4],pNext[5],pNext[6],pNext[7] ); OutputDebugStringA(temp); }
#define FUNCTIONNAME_DEBUG_TRACE9()  if( TRACETARGET ) { char temp[300]; DWORD *pNext = m_pCB->m_pNext; sprintf_s(temp,299, OPERATIONTYPE __FUNCSIG__ " 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x  0x%x 0x%x 0x%x )\n",pNext[0],pNext[1],pNext[2],pNext[3],pNext[4],pNext[5],pNext[6],pNext[7],pNext[8] ); OutputDebugStringA(temp); }
#define OPERATIONTYPE   "recording "
#define TRACETARGET g_bRecordAPITrace
#else
#define FUNCTIONNAME_DEBUG_TRACE()   
#define FUNCTIONNAME_DEBUG_TRACE0()  
#define FUNCTIONNAME_DEBUG_TRACE1()  
#define FUNCTIONNAME_DEBUG_TRACE2()  
#define FUNCTIONNAME_DEBUG_TRACE3()  
#define FUNCTIONNAME_DEBUG_TRACE4()  
#define FUNCTIONNAME_DEBUG_TRACE5()  
#define FUNCTIONNAME_DEBUG_TRACE6()  
#define FUNCTIONNAME_DEBUG_TRACE7()  
#define FUNCTIONNAME_DEBUG_TRACE8()  
#define FUNCTIONNAME_DEBUG_TRACE9()  
#endif




//---------------------------------------------------------------------------
// Recording Macros
// Generated from MacroGenerator_Record.xls, do not modify here -------v
#define STDRECORDVOIDFUNC0(name) virtual void STDMETHODCALLTYPE name () {FUNCTIONNAME_DEBUG_TRACE0();m_pCB->PutDWORD(CBD3D_COMMANDS::name);}
#define STDRECORDVOIDFUNC1(name, type1, arg1) virtual void STDMETHODCALLTYPE name (type1 arg1) {FUNCTIONNAME_DEBUG_TRACE1();m_pCB->PutDWORD(CBD3D_COMMANDS::name);m_pCB->PutDWORD(arg1);}
#define STDRECORDVOIDFUNC2(name, type1, arg1, type2, arg2) virtual void STDMETHODCALLTYPE name (type1 arg1, type2 arg2) {FUNCTIONNAME_DEBUG_TRACE2();m_pCB->PutDWORD(CBD3D_COMMANDS::name);m_pCB->PutDWORD(arg1);m_pCB->PutDWORD(arg2);}
#define STDRECORDVOIDFUNC3(name, type1, arg1, type2, arg2, type3, arg3) virtual void STDMETHODCALLTYPE name (type1 arg1, type2 arg2, type3 arg3) {FUNCTIONNAME_DEBUG_TRACE3();m_pCB->PutDWORD(CBD3D_COMMANDS::name);m_pCB->PutDWORD(arg1);m_pCB->PutDWORD(arg2);m_pCB->PutDWORD(arg3);}
#define STDRECORDVOIDFUNC4(name, type1, arg1, type2, arg2, type3, arg3, type4, arg4) virtual void STDMETHODCALLTYPE name (type1 arg1, type2 arg2, type3 arg3, type4 arg4) {FUNCTIONNAME_DEBUG_TRACE4();m_pCB->PutDWORD(CBD3D_COMMANDS::name);m_pCB->PutDWORD(arg1);m_pCB->PutDWORD(arg2);m_pCB->PutDWORD(arg3);m_pCB->PutDWORD(arg4);}
#define STDRECORDVOIDFUNC5(name, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5) virtual void STDMETHODCALLTYPE name (type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5) {FUNCTIONNAME_DEBUG_TRACE5();m_pCB->PutDWORD(CBD3D_COMMANDS::name);m_pCB->PutDWORD(arg1);m_pCB->PutDWORD(arg2);m_pCB->PutDWORD(arg3);m_pCB->PutDWORD(arg4);m_pCB->PutDWORD(arg5);}
#define STDRECORDVOIDFUNC6(name, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6) virtual void STDMETHODCALLTYPE name (type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, type6 arg6) {FUNCTIONNAME_DEBUG_TRACE6();m_pCB->PutDWORD(CBD3D_COMMANDS::name);m_pCB->PutDWORD(arg1);m_pCB->PutDWORD(arg2);m_pCB->PutDWORD(arg3);m_pCB->PutDWORD(arg4);m_pCB->PutDWORD(arg5);m_pCB->PutDWORD(arg6);}
#define STDRECORDVOIDFUNC7(name, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6, type7, arg7) virtual void STDMETHODCALLTYPE name (type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, type6 arg6, type7 arg7) {FUNCTIONNAME_DEBUG_TRACE7();m_pCB->PutDWORD(CBD3D_COMMANDS::name);m_pCB->PutDWORD(arg1);m_pCB->PutDWORD(arg2);m_pCB->PutDWORD(arg3);m_pCB->PutDWORD(arg4);m_pCB->PutDWORD(arg5);m_pCB->PutDWORD(arg6);m_pCB->PutDWORD(arg7);}
#define STDRECORDVOIDFUNC8(name, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6, type7, arg7, type8, arg8) virtual void STDMETHODCALLTYPE name (type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, type6 arg6, type7 arg7, type8 arg8) {FUNCTIONNAME_DEBUG_TRACE8();m_pCB->PutDWORD(CBD3D_COMMANDS::name);m_pCB->PutDWORD(arg1);m_pCB->PutDWORD(arg2);m_pCB->PutDWORD(arg3);m_pCB->PutDWORD(arg4);m_pCB->PutDWORD(arg5);m_pCB->PutDWORD(arg6);m_pCB->PutDWORD(arg7);m_pCB->PutDWORD(arg8);}
#define STDRECORDVOIDFUNC9(name, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6, type7, arg7, type8, arg8, type9, arg9) virtual void STDMETHODCALLTYPE name (type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, type6 arg6, type7 arg7, type8 arg8, type9 arg9) {FUNCTIONNAME_DEBUG_TRACE9();m_pCB->PutDWORD(CBD3D_COMMANDS::name);m_pCB->PutDWORD(arg1);m_pCB->PutDWORD(arg2);m_pCB->PutDWORD(arg3);m_pCB->PutDWORD(arg4);m_pCB->PutDWORD(arg5);m_pCB->PutDWORD(arg6);m_pCB->PutDWORD(arg7);m_pCB->PutDWORD(arg8);m_pCB->PutDWORD(arg9);}
#define STDRECORDFUNC0(name) virtual HRESULT STDMETHODCALLTYPE name () {FUNCTIONNAME_DEBUG_TRACE0();m_pCB->PutDWORD(CBD3D_COMMANDS::name);return D3D_OK; }
#define STDRECORDFUNC1(name, type1, arg1) virtual HRESULT STDMETHODCALLTYPE name (type1 arg1) {FUNCTIONNAME_DEBUG_TRACE1();m_pCB->PutDWORD(CBD3D_COMMANDS::name);m_pCB->PutDWORD(arg1);return D3D_OK; }
#define STDRECORDFUNC2(name, type1, arg1, type2, arg2) virtual HRESULT STDMETHODCALLTYPE name (type1 arg1, type2 arg2) {FUNCTIONNAME_DEBUG_TRACE2();m_pCB->PutDWORD(CBD3D_COMMANDS::name);m_pCB->PutDWORD(arg1);m_pCB->PutDWORD(arg2);return D3D_OK; }
#define STDRECORDFUNC3(name, type1, arg1, type2, arg2, type3, arg3) virtual HRESULT STDMETHODCALLTYPE name (type1 arg1, type2 arg2, type3 arg3) {FUNCTIONNAME_DEBUG_TRACE3();m_pCB->PutDWORD(CBD3D_COMMANDS::name);m_pCB->PutDWORD(arg1);m_pCB->PutDWORD(arg2);m_pCB->PutDWORD(arg3);return D3D_OK; }
#define STDRECORDFUNC4(name, type1, arg1, type2, arg2, type3, arg3, type4, arg4) virtual HRESULT STDMETHODCALLTYPE name (type1 arg1, type2 arg2, type3 arg3, type4 arg4) {FUNCTIONNAME_DEBUG_TRACE4();m_pCB->PutDWORD(CBD3D_COMMANDS::name);m_pCB->PutDWORD(arg1);m_pCB->PutDWORD(arg2);m_pCB->PutDWORD(arg3);m_pCB->PutDWORD(arg4);return D3D_OK; }
#define STDRECORDFUNC5(name, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5) virtual HRESULT STDMETHODCALLTYPE name (type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5) {FUNCTIONNAME_DEBUG_TRACE5();m_pCB->PutDWORD(CBD3D_COMMANDS::name);m_pCB->PutDWORD(arg1);m_pCB->PutDWORD(arg2);m_pCB->PutDWORD(arg3);m_pCB->PutDWORD(arg4);m_pCB->PutDWORD(arg5);return D3D_OK; }
#define STDRECORDFUNC6(name, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6) virtual HRESULT STDMETHODCALLTYPE name (type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, type6 arg6) {FUNCTIONNAME_DEBUG_TRACE6();m_pCB->PutDWORD(CBD3D_COMMANDS::name);m_pCB->PutDWORD(arg1);m_pCB->PutDWORD(arg2);m_pCB->PutDWORD(arg3);m_pCB->PutDWORD(arg4);m_pCB->PutDWORD(arg5);m_pCB->PutDWORD(arg6);return D3D_OK; }
#define STDRECORDFUNC7(name, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6, type7, arg7) virtual HRESULT STDMETHODCALLTYPE name (type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, type6 arg6, type7 arg7) {FUNCTIONNAME_DEBUG_TRACE7();m_pCB->PutDWORD(CBD3D_COMMANDS::name);m_pCB->PutDWORD(arg1);m_pCB->PutDWORD(arg2);m_pCB->PutDWORD(arg3);m_pCB->PutDWORD(arg4);m_pCB->PutDWORD(arg5);m_pCB->PutDWORD(arg6);m_pCB->PutDWORD(arg7);return D3D_OK; }
#define STDRECORDFUNC8(name, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6, type7, arg7, type8, arg8) virtual HRESULT STDMETHODCALLTYPE name (type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, type6 arg6, type7 arg7, type8 arg8) {FUNCTIONNAME_DEBUG_TRACE8();m_pCB->PutDWORD(CBD3D_COMMANDS::name);m_pCB->PutDWORD(arg1);m_pCB->PutDWORD(arg2);m_pCB->PutDWORD(arg3);m_pCB->PutDWORD(arg4);m_pCB->PutDWORD(arg5);m_pCB->PutDWORD(arg6);m_pCB->PutDWORD(arg7);m_pCB->PutDWORD(arg8);return D3D_OK; }
#define STDRECORDFUNC9(name, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6, type7, arg7, type8, arg8, type9, arg9) virtual HRESULT STDMETHODCALLTYPE name (type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, type6 arg6, type7 arg7, type8 arg8, type9 arg9) {FUNCTIONNAME_DEBUG_TRACE9();m_pCB->PutDWORD(CBD3D_COMMANDS::name);m_pCB->PutDWORD(arg1);m_pCB->PutDWORD(arg2);m_pCB->PutDWORD(arg3);m_pCB->PutDWORD(arg4);m_pCB->PutDWORD(arg5);m_pCB->PutDWORD(arg6);m_pCB->PutDWORD(arg7);m_pCB->PutDWORD(arg8);m_pCB->PutDWORD(arg9);return D3D_OK; }
// Generated from MacroGenerator_Record.xls, do not modify here -------^

#define STDRECORDWITHRETURNFUNC0(rettype, retval, name) virtual rettype STDMETHODCALLTYPE  name ( )\
{\
    FUNCTIONNAME_DEBUG_TRACE();\
    m_pCB->PutDWORD( CBD3D_COMMANDS::name);\
    return retval;\
}

//required for setting constants.
#define STDRECORDSETCONSTS(name, type0, arg0, type1, arg1, type2, arg2, arraytype) virtual HRESULT STDMETHODCALLTYPE  name ( type0 arg0, type1 arg1, type2 arg2 )\
{\
    FUNCTIONNAME_DEBUG_TRACE2()\
    m_pCB->PutDWORD(CBD3D_COMMANDS::name);\
    m_pCB->PutDWORD(arg0);\
    m_pCB->PutDWORD(arg2);\
    m_pCB->DoPutMem((DWORD*)arg1,arg2*4*sizeof(arraytype));\
    return D3D_OK;\
}

#if MEMTRACE
#undef OPERATIONTYPE
#undef TRACETARGET
#define OPERATIONTYPE   "playing "
#define TRACETARGET g_bPlaybackAPITrace
#endif

//---------------------------------------------------------------------------
// Playback Macros
// Generated from MacroGenerator_Playback.xls, do not modify here -------v
#define STDPLAYVOIDFUNC0(func, name) void func () {FUNCTIONNAME_DEBUG_TRACE0();m_pDevice->name();}
#define STDPLAYVOIDFUNC1(func, name, type1) void func () {FUNCTIONNAME_DEBUG_TRACE1();type1 arg1; m_pCB->GetDWORD( &arg1 );m_pDevice->name(arg1);}
#define STDPLAYVOIDFUNC2(func, name, type1, type2) void func () {FUNCTIONNAME_DEBUG_TRACE2();type1 arg1; m_pCB->GetDWORD( &arg1 );type2 arg2; m_pCB->GetDWORD( &arg2 );m_pDevice->name(arg1, arg2);}
#define STDPLAYVOIDFUNC3(func, name, type1, type2, type3) void func () {FUNCTIONNAME_DEBUG_TRACE3();type1 arg1; m_pCB->GetDWORD( &arg1 );type2 arg2; m_pCB->GetDWORD( &arg2 );type3 arg3; m_pCB->GetDWORD( &arg3 );m_pDevice->name(arg1, arg2, arg3);}
#define STDPLAYVOIDFUNC4(func, name, type1, type2, type3, type4) void func () {FUNCTIONNAME_DEBUG_TRACE4();type1 arg1; m_pCB->GetDWORD( &arg1 );type2 arg2; m_pCB->GetDWORD( &arg2 );type3 arg3; m_pCB->GetDWORD( &arg3 );type4 arg4; m_pCB->GetDWORD( &arg4 );m_pDevice->name(arg1, arg2, arg3, arg4);}
#define STDPLAYVOIDFUNC5(func, name, type1, type2, type3, type4, type5) void func () {FUNCTIONNAME_DEBUG_TRACE5();type1 arg1; m_pCB->GetDWORD( &arg1 );type2 arg2; m_pCB->GetDWORD( &arg2 );type3 arg3; m_pCB->GetDWORD( &arg3 );type4 arg4; m_pCB->GetDWORD( &arg4 );type5 arg5; m_pCB->GetDWORD( &arg5 );m_pDevice->name(arg1, arg2, arg3, arg4, arg5);}
#define STDPLAYVOIDFUNC6(func, name, type1, type2, type3, type4, type5, type6) void func () {FUNCTIONNAME_DEBUG_TRACE6();type1 arg1; m_pCB->GetDWORD( &arg1 );type2 arg2; m_pCB->GetDWORD( &arg2 );type3 arg3; m_pCB->GetDWORD( &arg3 );type4 arg4; m_pCB->GetDWORD( &arg4 );type5 arg5; m_pCB->GetDWORD( &arg5 );type6 arg6; m_pCB->GetDWORD( &arg6 );m_pDevice->name(arg1, arg2, arg3, arg4, arg5, arg6);}
#define STDPLAYVOIDFUNC7(func, name, type1, type2, type3, type4, type5, type6, type7) void func () {FUNCTIONNAME_DEBUG_TRACE7();type1 arg1; m_pCB->GetDWORD( &arg1 );type2 arg2; m_pCB->GetDWORD( &arg2 );type3 arg3; m_pCB->GetDWORD( &arg3 );type4 arg4; m_pCB->GetDWORD( &arg4 );type5 arg5; m_pCB->GetDWORD( &arg5 );type6 arg6; m_pCB->GetDWORD( &arg6 );type7 arg7; m_pCB->GetDWORD( &arg7 );m_pDevice->name(arg1, arg2, arg3, arg4, arg5, arg6, arg7);}
#define STDPLAYVOIDFUNC8(func, name, type1, type2, type3, type4, type5, type6, type7, type8) void func () {FUNCTIONNAME_DEBUG_TRACE8();type1 arg1; m_pCB->GetDWORD( &arg1 );type2 arg2; m_pCB->GetDWORD( &arg2 );type3 arg3; m_pCB->GetDWORD( &arg3 );type4 arg4; m_pCB->GetDWORD( &arg4 );type5 arg5; m_pCB->GetDWORD( &arg5 );type6 arg6; m_pCB->GetDWORD( &arg6 );type7 arg7; m_pCB->GetDWORD( &arg7 );type8 arg8; m_pCB->GetDWORD( &arg8 );m_pDevice->name(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);}
#define STDPLAYVOIDFUNC9(func, name, type1, type2, type3, type4, type5, type6, type7, type8, type9) void func () {FUNCTIONNAME_DEBUG_TRACE9();type1 arg1; m_pCB->GetDWORD( &arg1 );type2 arg2; m_pCB->GetDWORD( &arg2 );type3 arg3; m_pCB->GetDWORD( &arg3 );type4 arg4; m_pCB->GetDWORD( &arg4 );type5 arg5; m_pCB->GetDWORD( &arg5 );type6 arg6; m_pCB->GetDWORD( &arg6 );type7 arg7; m_pCB->GetDWORD( &arg7 );type8 arg8; m_pCB->GetDWORD( &arg8 );type9 arg9; m_pCB->GetDWORD( &arg9 );m_pDevice->name(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);}
#define STDPLAYFUNC0(func, name) void func () {FUNCTIONNAME_DEBUG_TRACE0();if(FAILED(m_pDevice->name())) OutputDebugStringA(__FUNCTION__ " failed in playback\n");}
#define STDPLAYFUNC1(func, name, type1) void func () {FUNCTIONNAME_DEBUG_TRACE1();type1 arg1; m_pCB->GetDWORD( &arg1 );if(FAILED(m_pDevice->name(arg1))) OutputDebugStringA(__FUNCTION__ " failed in playback\n");}
#define STDPLAYFUNC2(func, name, type1, type2) void func () {FUNCTIONNAME_DEBUG_TRACE2();type1 arg1; m_pCB->GetDWORD( &arg1 );type2 arg2; m_pCB->GetDWORD( &arg2 );if(FAILED(m_pDevice->name(arg1, arg2))) OutputDebugStringA(__FUNCTION__ " failed in playback\n");}
#define STDPLAYFUNC3(func, name, type1, type2, type3) void func () {FUNCTIONNAME_DEBUG_TRACE3();type1 arg1; m_pCB->GetDWORD( &arg1 );type2 arg2; m_pCB->GetDWORD( &arg2 );type3 arg3; m_pCB->GetDWORD( &arg3 );if(FAILED(m_pDevice->name(arg1, arg2, arg3))) OutputDebugStringA(__FUNCTION__ " failed in playback\n");}
#define STDPLAYFUNC4(func, name, type1, type2, type3, type4) void func () {FUNCTIONNAME_DEBUG_TRACE4();type1 arg1; m_pCB->GetDWORD( &arg1 );type2 arg2; m_pCB->GetDWORD( &arg2 );type3 arg3; m_pCB->GetDWORD( &arg3 );type4 arg4; m_pCB->GetDWORD( &arg4 );if(FAILED(m_pDevice->name(arg1, arg2, arg3, arg4))) OutputDebugStringA(__FUNCTION__ " failed in playback\n");}
#define STDPLAYFUNC5(func, name, type1, type2, type3, type4, type5) void func () {FUNCTIONNAME_DEBUG_TRACE5();type1 arg1; m_pCB->GetDWORD( &arg1 );type2 arg2; m_pCB->GetDWORD( &arg2 );type3 arg3; m_pCB->GetDWORD( &arg3 );type4 arg4; m_pCB->GetDWORD( &arg4 );type5 arg5; m_pCB->GetDWORD( &arg5 );if(FAILED(m_pDevice->name(arg1, arg2, arg3, arg4, arg5))) OutputDebugStringA(__FUNCTION__ " failed in playback\n");}
#define STDPLAYFUNC6(func, name, type1, type2, type3, type4, type5, type6) void func () {FUNCTIONNAME_DEBUG_TRACE6();type1 arg1; m_pCB->GetDWORD( &arg1 );type2 arg2; m_pCB->GetDWORD( &arg2 );type3 arg3; m_pCB->GetDWORD( &arg3 );type4 arg4; m_pCB->GetDWORD( &arg4 );type5 arg5; m_pCB->GetDWORD( &arg5 );type6 arg6; m_pCB->GetDWORD( &arg6 );if(FAILED(m_pDevice->name(arg1, arg2, arg3, arg4, arg5, arg6))) OutputDebugStringA(__FUNCTION__ " failed in playback\n");}
#define STDPLAYFUNC7(func, name, type1, type2, type3, type4, type5, type6, type7) void func () {FUNCTIONNAME_DEBUG_TRACE7();type1 arg1; m_pCB->GetDWORD( &arg1 );type2 arg2; m_pCB->GetDWORD( &arg2 );type3 arg3; m_pCB->GetDWORD( &arg3 );type4 arg4; m_pCB->GetDWORD( &arg4 );type5 arg5; m_pCB->GetDWORD( &arg5 );type6 arg6; m_pCB->GetDWORD( &arg6 );type7 arg7; m_pCB->GetDWORD( &arg7 );if(FAILED(m_pDevice->name(arg1, arg2, arg3, arg4, arg5, arg6, arg7))) OutputDebugStringA(__FUNCTION__ " failed in playback\n");}
#define STDPLAYFUNC8(func, name, type1, type2, type3, type4, type5, type6, type7, type8) void func () {FUNCTIONNAME_DEBUG_TRACE8();type1 arg1; m_pCB->GetDWORD( &arg1 );type2 arg2; m_pCB->GetDWORD( &arg2 );type3 arg3; m_pCB->GetDWORD( &arg3 );type4 arg4; m_pCB->GetDWORD( &arg4 );type5 arg5; m_pCB->GetDWORD( &arg5 );type6 arg6; m_pCB->GetDWORD( &arg6 );type7 arg7; m_pCB->GetDWORD( &arg7 );type8 arg8; m_pCB->GetDWORD( &arg8 );if(FAILED(m_pDevice->name(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8))) OutputDebugStringA(__FUNCTION__ " failed in playback\n");}
#define STDPLAYFUNC9(func, name, type1, type2, type3, type4, type5, type6, type7, type8, type9) void func () {FUNCTIONNAME_DEBUG_TRACE9();type1 arg1; m_pCB->GetDWORD( &arg1 );type2 arg2; m_pCB->GetDWORD( &arg2 );type3 arg3; m_pCB->GetDWORD( &arg3 );type4 arg4; m_pCB->GetDWORD( &arg4 );type5 arg5; m_pCB->GetDWORD( &arg5 );type6 arg6; m_pCB->GetDWORD( &arg6 );type7 arg7; m_pCB->GetDWORD( &arg7 );type8 arg8; m_pCB->GetDWORD( &arg8 );type9 arg9; m_pCB->GetDWORD( &arg9 );if(FAILED(m_pDevice->name(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9))) OutputDebugStringA(__FUNCTION__ " failed in playback\n");}
// Generated from MacroGenerator_Playback.xls, do not modify here -------^

//this is used primarily to read from memory buffer and play shader constant set calls.
#define STDPLAYSETCONSTS(func, name, type0, type1, type2, arraytype)\
    void func ()\
{\
    FUNCTIONNAME_DEBUG_TRACE2()\
    type0 arg0; m_pCB->GetDWORD(&arg0);\
    type2 arg2; m_pCB->GetDWORD(&arg2);\
    const DWORD iSize = arg2 * 4 * sizeof(arraytype);\
    type1 arg1{m_pCB->DoGetMem<std::remove_pointer_t<type1>>(iSize)};\
    if(FAILED( m_pDevice->name(arg0,arg1,arg2) ))\
        OutputDebugStringA(__FUNCTION__ " failed in playback\n");\
}

//---------------------------------------------------------------------------
// Get and Put macros
#define PUTDWORD( type0 ) void PutDWORD( type0  arg ) { static_assert(sizeof(arg) <= sizeof(DWORD)); DoPutDWORD( (DWORD) arg); }
#define PUTOBJ( type0 ) void PutDWORD( type0* arg ) { DoPutMem(arg, sizeof( type0 )); }
#define GETDWORD( type0 ) void GetDWORD( type0* arg ) { static_assert(sizeof(*arg) <= sizeof(DWORD)); *arg = ( type0 ) DoGetDWORD(); }
#define GETOBJ( type0 ) void GetDWORD( type0** arg ) { *arg = DoGetMem<type0>(sizeof( type0 )); }
#define GET_AND_PUT_OBJ( type0 )    GETOBJ( type0 )   PUTOBJ( type0 )
#define GET_AND_PUT_DWORD( type0 )  GETDWORD( type0 ) PUTDWORD( type0 )

#if MEMTRACE
#if VERBOSE
#define  DEBUGGET( fname, returnvalue, originalnextptr, nextptr )  { if(g_bMemoryTrace){ char temp[300]; sprintf_s(temp,299,"%s returned %x, this token at %x, next token at %x, diff = %d\n",fname,(DWORD)returnvalue,(DWORD)originalnextptr,(DWORD)nextptr,((DWORD)nextptr - (DWORD)originalnextptr));OutputDebugStringA( temp ); } }
#define  DEBUGPUT( fname, returnvalue, originalnextptr, nextptr )  { if(g_bMemoryTrace){ char temp[300]; sprintf_s(temp,299,"%s returned %x, this token at %x, next token at %x, diff = %d\n",fname,(DWORD)returnvalue,(DWORD)originalnextptr,(DWORD)nextptr,((DWORD)nextptr - (DWORD)originalnextptr));OutputDebugStringA( temp ); } }
#else
#define  DEBUGGET( fname, returnvalue, originalnextptr, nextptr )  { if(g_bMemoryTrace){ char temp[300]; sprintf_s(temp,299," 0x%x\n ",(DWORD)returnvalue); OutputDebugStringA( temp ); } }
#define  DEBUGPUT( fname, returnvalue, originalnextptr, nextptr )  { if(g_bMemoryTrace){ char temp[300]; sprintf_s(temp,299," 0x%x ",(DWORD)returnvalue); OutputDebugStringA( temp ); } }
#endif
#define  MEMSIZECHECK( AvailableMemory, iSize )  { if(g_bMemoryTrace)\
{\
    char temp[300];\
    sprintf_s(temp,299,"%lu available memory checked for size %lu\n",(DWORD)AvailableMemory,(DWORD)iSize);\
    OutputDebugStringA( temp );\
    if (iSize<0)\
        OutputDebugStringA(" negative size!!\n");\
} }
#else
#define  DEBUGGET( fname, returnvalue, originalnextptr, nextptr )
#define  DEBUGPUT( fname, returnvalue, originalnextptr, nextptr )
#define  MEMSIZECHECK( AvailableMemory, iSize )
#endif


using LPUINT = UINT*;
using LPD3DCAPS9 = D3DCAPS9*;

#endif // DIRECTX_COMMAND_BUFFER_CBMACROS_H_