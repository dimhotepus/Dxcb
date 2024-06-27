//-----------------------------------------------------------------------------
// File: TexturesMultiThreaded.cpp
//
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#include <Windows.h>
#include <d3dx9.h>
#include <strsafe.h>

#include <cstdlib>
#include <thread>

#include "DXUT.h"
#include "DXUTgui.h"
#include "DXUTcamera.h"
#include "DXUTsettingsdlg.h"
#include "SDKmesh.h"
#include "SDKmisc.h"
#include "resource.h"

//#define DEBUG_VS   // Uncomment this line to debug vertex shaders 
//#define DEBUG_PS   // Uncomment this line to debug pixel shaders 

#include "CBRecorder9.h"
#include "CBPlayer9.h"

using namespace dxcb;

// Global variables
ID3DXFont*              g_pFont = nullptr;         // Font for drawing text
ID3DXSprite*            g_pTextSprite = nullptr;   // Sprite for batching draw text calls
ID3DXEffect*            g_pEffect = nullptr;       // D3DX effect interface
D3DXMATRIXA16           g_mView;
CModelViewerCamera      g_Camera;               // A model viewing camera
CDXUTDialogResourceManager g_DialogResourceManager; // manager for shared resources of dialogs
CD3DSettingsDlg         g_SettingsDlg;          // Device settings dialog
CDXUTDialog             g_HUD;                  // dialog for standard controls
CDXUTDialog             g_UI;             // dialog for sample specific controls
LPDIRECT3DVERTEXBUFFER9 g_pVB = nullptr; // Buffer to hold vertices
LPDIRECT3DTEXTURE9      g_pTexture = nullptr; // Our texture



size_t                  g_dwCPULoops = 0;
float                   g_fAverageCPUperDP = 0.0f;
float                   g_fMeasuredFPS = 0.0f;
float                   g_fMeasuredTotalCPULoadPerDraw = 0.0f;

float                   g_fArtificialCPULoad[10];
float                   g_fArtificialCPULoadPerFrame;
size_t                  g_dwACPULoadPosition = 0;

size_t                  g_dwCPUPosition = 0;
float                   g_fCPU[10];
constexpr float         g_fCPUScale = 1.0f;

constexpr unsigned      g_dwNumberofBufferSets = 2;
constexpr unsigned      g_dwMaxNumberofRecordThreads = 16;
constexpr int           g_dwMaxNumberofSQRTDPs = 100;
constexpr int           g_dwMaxNumberofCPULoops = 400;

constexpr unsigned      g_dwMinNumberofRecordThreads = 0;
constexpr int           g_dwMinNumberofSQRTDPs = 2;
constexpr int           g_dwMinNumberofCPULoops = 0;

int                     g_dwNumberofRecordThreads = 2;
int                     g_dwNumberofRecordThreads_toBeSet = 2;
int                     g_dwNumberofObjectsSqrt = 5;
int                     g_dwNumberofObjectsPerFrame = 0;
int                     g_dwCPUWorkPerDP = 0;
DWORD                   g_dwBBufferWidth = 1024;
DWORD                   g_dwBBufferHeight = 1024;
constexpr unsigned      g_dwNumberofBuffers = g_dwNumberofBufferSets * g_dwMaxNumberofRecordThreads;
constexpr unsigned      g_dwNumberofColors = 8;
unsigned                g_dwCurrentBufferSet = 0;
size_t                  g_dwFrame = 0;
CBRecorder9             g_CBRecorder[g_dwMaxNumberofRecordThreads * g_dwNumberofBufferSets];
CBPlayer9               g_CBPlayer;
CBRecorder9*            g_pCBRecorder[g_dwMaxNumberofRecordThreads * g_dwNumberofBufferSets];
CBPlayer9*              g_pCBPlayer = &g_CBPlayer;

size_t                  g_dwMemory[40000000];

size_t                  g_dwAccess[1000];

bool                    g_bUpdateThreadCount = false;
bool                    g_bUpdateDPs = false;
bool                    g_bUpdateThreading = false;
bool                    g_bUpdateControls = false;
bool                    g_bUpdateTesting = false;
bool                    g_bShowTestingUI = false;
bool                    g_bTesting = false;
bool                    g_bAutomateTesting = true;
bool                    g_bFlushDataToFile = true;
bool                    g_bSaveSample = false;

size_t*                 g_CBMem[g_dwNumberofBuffers];
CBMemoryBuffer          g_CB[g_dwNumberofBuffers];
bool                    g_bCBValid[g_dwNumberofBuffers];

HANDLE                  g_RenderRecordSem[g_dwMaxNumberofRecordThreads] = { nullptr };
HANDLE                  g_RenderPlaybackSem[g_dwMaxNumberofRecordThreads] = { nullptr };
HANDLE                  g_RecordThreads[g_dwMaxNumberofRecordThreads] = { nullptr };
unsigned                g_ThreadIds[g_dwMaxNumberofRecordThreads] = { 0 };
bool                    g_bThreadsInitialized = false;
bool                    g_DoRender = false;
bool                    g_bMultiThread = false;
bool                    g_bCheckDrawTime = false;
float                   g_fDrawCost = 0.0f;

bool                    g_bRunLean = false;
bool                    g_bAutoTesting = false;
bool                    g_bInAutoTesting = false;
bool                    g_bStopTesting = false;

FILE*                   g_pOutputFile = nullptr;

enum class SAMPLE_STABILIZATION
{
	STEP1_RESET,
	STEP2_STABILIZE,
	STEP3_RECORD
};

SAMPLE_STABILIZATION g_SampleStabilizationState =
	SAMPLE_STABILIZATION::STEP1_RESET;

int                     g_TestLoops = 0;
int                     g_TestDPs = 0;
int                     g_TestThreads = 0;

int                     g_TestStartLoops = 0;
int                     g_TestStartDPs = 0;
int                     g_TestStartThreads = 0;

int                     g_TestEndLoops = 0;
int                     g_TestEndDPs = 0;
int                     g_TestEndThreads = 0;

int                     g_TestLoopsIncrement = 0;
int                     g_TestDPsIncrement = 0;
int                     g_TestThreadsIncrement = 0;
bool                    g_bAllowRecordToOverlapPlayback = true;

constexpr DWORD         g_dwColors[g_dwNumberofColors] = { 0xff00ffff , 0xffff00ff , 0xffffff00 , 0xffff00ff , 0xffffffff , 0xffff00ff , 0xff8080ff, 0x808080ff };
LARGE_INTEGER           g_lFrequency, g_StartPerformanceCount, g_EndPerformanceCount;
LARGE_INTEGER           g_PerFrameTimeCount;
LARGE_INTEGER           g_TestStartTime;

// A structure for our custom vertex type. We added texture coordinates
struct CUSTOMVERTEX
{
	D3DXVECTOR3 position; // The position
	D3DCOLOR    color;    // The color
	FLOAT       tu, tv;   // The texture coordinates
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)



// UI control IDs
#define IDC_TOGGLEFULLSCREEN    1
#define IDC_TOGGLEREF           3
#define IDC_CHANGEDEVICE        4
#define IDC_EDITBOX1            5
#define IDC_EDITBOX2            6
#define IDC_ENABLEIME           7
#define IDC_DISABLEIME          8
#define IDC_COMBOBOX            9
#define IDC_STATIC              10
#define IDC_OUTPUT              12
#define IDC_SLIDER              13
#define IDC_CHECKBOX            14
#define IDC_CLEAREDIT           15
#define IDC_RADIO1A             16
#define IDC_RADIO1B             17
#define IDC_RADIO1C             18
#define IDC_RADIO2A             19
#define IDC_RADIO2B             20
#define IDC_RADIO2C             21
#define IDC_LISTBOX             22
#define IDC_LISTBOXM            23
#define IDC_THREADING           24
#define IDC_LABEL               25
#define IDC_SLIDERDP            26
#define IDC_LABELDP             27
#define IDC_SLIDERCPU           28
#define IDC_LABELCPU            29
#define IDC_LABELMEASUREDCPU    30
#define IDC_TESTING             31
#define IDC_STARTTESTING        32
#define IDC_AUTOMATETESTING     33
#define IDC_MANUALTESTING       34
#define IDC_TESTINGBUTTOMGROUP  35
#define IDC_LOOPSEDITBOXSTART        36
#define IDC_LOOPSEDITBOXFINISH       37
#define IDC_LOOPSEDITBOXINCREMENT    38
#define IDC_THREADSEDITBOXSTART      39
#define IDC_THREADSEDITBOXFINISH     40
#define IDC_THREADSEDITBOXINCREMENT  41
#define IDC_DPEDITBOXSTART           42
#define IDC_DPEDITBOXFINISH          43
#define IDC_DPEDITBOXINCREMENT       44
#define IDC_LABELLOOPSEDITBOXSTART        45
#define IDC_LABELLOOPSEDITBOXFINISH       46
#define IDC_LABELLOOPSEDITBOXINCREMENT    47
#define IDC_LABELTHREADSEDITBOXSTART      48
#define IDC_LABELTHREADSEDITBOXFINISH     49
#define IDC_LABELTHREADSEDITBOXINCREMENT  50
#define IDC_LABELDPEDITBOXSTART           51
#define IDC_LABELDPEDITBOXFINISH          52
#define IDC_LABELDPEDITBOXINCREMENT       53
#define IDC_OUTPUTSAMPLE                  54
#define IDC_FLUSHDATA                     55 
#define IDC_LABELFLUSHDATA                56 
#define IDC_PLAYBACKRECORDOVERLAP         57

// Forward declarations 
bool    CALLBACK IsDeviceAcceptable(D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext);
bool    CALLBACK ModifyDeviceSettings(DXUTDeviceSettings* pDeviceSettings, void* pUserContext);
HRESULT CALLBACK OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
HRESULT CALLBACK OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
void    CALLBACK OnFrameMove(double fTime, float fElapsedTime, void* pUserContext);
void    CALLBACK OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
LRESULT CALLBACK MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext);
void    CALLBACK KeyboardProc(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);
void    CALLBACK OnGUIEvent(UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext);
void    CALLBACK OnLostDevice(void* pUserContext);
void    CALLBACK OnDestroyDevice(void* pUserContext);

void    InitApp();
HRESULT LoadMesh(IDirect3DDevice9* pd3dDevice, WCHAR* strFileName, ID3DXMesh** ppMesh);
void    RenderText();
void    Render(DWORD nParam, IDirect3DDevice9* pDevice, bool bMultiThread);
HRESULT SetUpGeometry(IDirect3DDevice9* pd3dDevice);
void DestroyGeometry();
void CPUActive();
void SetUpThreads();
void DestroyThreads();
void ZeroThreadObjects();
void Playback(IDirect3DDevice9* pd3dDevice, float fElapsedTime);
float MeasureCPUActive();
float AverageCPUSamples();
float AverageArtificialCPULoadSamples();
int CalculateDPs();

//UI and HUD functions
void UpdateFromNumberThreadsSliderChange();
void UpdateFromNumberDPsSliderChange();
void UpdateFromThreadingChange();
void UpdateTestingRadioButtons(bool bAutomateTesting);
void UpdateFromControls();
void UpdateTestingInputControls(bool bHideControls);
void UpdateSaveSampleButton(bool bShowSaveSample, bool bHideBoth);
void UpdateTestingRadioButtons(bool bAutomateTesting, bool bHide);
void UpdateFromCPUWorkPerDPSliderChange(DWORD dwCPUWorkPerDP);
void ShowSliders(bool bShow);


void OutputHeader(FILE* pfile);
void OutputData(FILE* pfile, int CPUBusyLoops, int DrawPrimitives, int Threads, float RenderCallCPUCost, float CPUBusyLoopsCost, float FPS, float SPF);
bool OpenDataFile(const char* fname);

class AverageFPS
{
	LARGE_INTEGER frequency;
	LARGE_INTEGER startTime;
	LARGE_INTEGER thisTime;
	int frameCount;
	bool bResetRequested;

public:
	AverageFPS()
	{
		frameCount = 0;
		startTime.QuadPart = thisTime.QuadPart = 0;
		QueryPerformanceFrequency(&frequency);
		Reset();
	}
	void Reset()
	{
		bResetRequested = true;
	}
	void DoReset()
	{
		frameCount = 0;
		startTime = thisTime;
		bResetRequested = false;
	}
	void MarkFrame()
	{
		frameCount++;
		QueryPerformanceCounter(&thisTime);
		if (bResetRequested)
			DoReset();
	}
	int GetElapsedFrames()
	{
		return frameCount;
	}
	float GetElapsedTime()
	{
		LARGE_INTEGER elapsedTimeINT;
		elapsedTimeINT.QuadPart = thisTime.QuadPart - startTime.QuadPart;

		float elapsedTime = elapsedTimeINT.QuadPart / (float)frequency.QuadPart;
		return elapsedTime;
	}
	float GetAverageFPS()
	{
		if (frameCount == 0 || bResetRequested)
			return 0;

		float fps = frameCount / GetElapsedTime();
		return fps;
	}
};
AverageFPS g_AverageFPS;

void InValidateAllBuffers()
{
	for (auto* r : g_pCBRecorder)
	{
		r->BeginCommandBuffer();
		r->EndCommandBuffer();
	}

	for (auto& v : g_bCBValid) v = false;
}

// Initialize everything and go into a render loop
INT WINAPI wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	MessageBoxA(nullptr, "Attach Here", "Debug Helper Dialog", MB_OK | MB_ICONASTERISK);
	ZeroThreadObjects();
	QueryPerformanceFrequency(&g_lFrequency);

	// Setup command buffer recording and playback memory
	size_t iBufferSize = std::size(g_dwMemory) / (g_dwMaxNumberofRecordThreads * g_dwNumberofBufferSets);
	for (unsigned i = 0; i < g_dwMaxNumberofRecordThreads * g_dwNumberofBufferSets; i++)
	{
		g_CBMem[i] = &(g_dwMemory[i * iBufferSize]);

		//set memory per command buffer 
		g_CB[i].SetMemory(g_CBMem[i], iBufferSize);

		//set command buffer per recorder.
		g_CBRecorder[i].SetCommandBuffer(&g_CB[i]);

		//set recorder pointers 
		g_pCBRecorder[i] = &g_CBRecorder[i];
	}

	for (auto& a : g_dwAccess)
		a = (static_cast<size_t>(rand()) * std::size(g_dwMemory) / RAND_MAX) % std::size(g_dwMemory);

	InValidateAllBuffers();

	// DXUT will create and use the best device (either D3D9 or D3D10) 
	// that is available on the system depending on which D3D callbacks are set below

	// Set DXUT callbacks
	DXUTSetCallbackD3D9DeviceAcceptable(IsDeviceAcceptable);
	DXUTSetCallbackD3D9DeviceCreated(OnCreateDevice);
	DXUTSetCallbackD3D9DeviceReset(OnResetDevice);
	DXUTSetCallbackD3D9FrameRender(OnFrameRender);
	DXUTSetCallbackD3D9DeviceLost(OnLostDevice);
	DXUTSetCallbackD3D9DeviceDestroyed(OnDestroyDevice);
	DXUTSetCallbackMsgProc(MsgProc);
	DXUTSetCallbackKeyboard(KeyboardProc);
	DXUTSetCallbackFrameMove(OnFrameMove);
	DXUTSetCallbackDeviceChanging(ModifyDeviceSettings);

	DXUTSetCursorSettings(true, true);
	InitApp();
	DXUTInit(true, true); // Parse the command line and show msgboxes
	DXUTSetHotkeyHandling(true, true, true);
	DXUTCreateWindow(L"MultiTheading Command Buffer Demo");
	DXUTCreateDevice(true, 1024, 1024);
	DXUTMainLoop();

	DestroyThreads();
	return DXUTGetExitCode();
}


//--------------------------------------------------------------------------------------
// Initialize the app 
//--------------------------------------------------------------------------------------
void InitApp()
{
	// Initialize dialogs
	g_SettingsDlg.Init(&g_DialogResourceManager);
	g_HUD.Init(&g_DialogResourceManager);
	g_UI.Init(&g_DialogResourceManager);
	g_bShowTestingUI = false;
	g_bAutomateTesting = true;


	g_HUD.SetCallback(OnGUIEvent); int iY = 10;
	g_HUD.AddButton(IDC_TOGGLEFULLSCREEN, L"Toggle full screen", 35, iY, 125, 22);
	g_HUD.AddButton(IDC_TOGGLEREF, L"Toggle REF (F3)", 35, iY += 24, 125, 22);
	g_HUD.AddButton(IDC_CHANGEDEVICE, L"Change device (F2)", 35, iY += 24, 125, 22, VK_F2);
	g_HUD.AddButton(IDC_THREADING, L"Toggle MultiThreading", 35, iY += 24, 125, 22);
	g_HUD.AddButton(IDC_PLAYBACKRECORDOVERLAP, L"No Playback Overlap", 35, iY += 24, 125, 22);
	g_HUD.AddButton(IDC_TESTING, L"Toggle Test UI", 35, iY += 24, 125, 22);
	g_HUD.AddButton(IDC_STARTTESTING, L"Start Testing", 35, iY += 96, 125, 22);
	g_HUD.GetButton(IDC_STARTTESTING)->SetVisible(g_bShowTestingUI && g_bAutomateTesting);
	g_HUD.AddButton(IDC_OUTPUTSAMPLE, L"Save Sample", 35, iY, 125, 22);
	g_HUD.GetButton(IDC_OUTPUTSAMPLE)->SetVisible(g_bShowTestingUI && !g_bAutomateTesting);
	g_HUD.AddRadioButton(IDC_AUTOMATETESTING, IDC_TESTINGBUTTOMGROUP, L"Automatic", 35, iY += (24 + 5), 125, 22);
	g_HUD.AddRadioButton(IDC_MANUALTESTING, IDC_TESTINGBUTTOMGROUP, L"Manual", 35, iY += 24, 125, 22);


	g_HUD.AddEditBox(IDC_LOOPSEDITBOXSTART, L" 0 ", 97, iY += 32, 65, 32);
	g_HUD.AddStatic(IDC_LABELLOOPSEDITBOXSTART, L"Loops Start", 0, iY, 105, 31);
	g_HUD.GetControl(IDC_LABELLOOPSEDITBOXSTART)->GetElement(0)->dwTextFormat = DT_LEFT | DT_VCENTER;

	g_HUD.AddEditBox(IDC_LOOPSEDITBOXFINISH, L" 250 ", 97, iY += 32, 65, 32);
	g_HUD.AddStatic(IDC_LABELLOOPSEDITBOXFINISH, L"Loops End", 0, iY, 105, 31);
	g_HUD.GetControl(IDC_LABELLOOPSEDITBOXFINISH)->GetElement(0)->dwTextFormat = DT_LEFT | DT_VCENTER;

	g_HUD.AddEditBox(IDC_LOOPSEDITBOXINCREMENT, L" 50 ", 97, iY += 32, 65, 32);
	g_HUD.AddStatic(IDC_LABELLOOPSEDITBOXINCREMENT, L"Loops Increment", 0, iY, 105, 31);
	g_HUD.GetControl(IDC_LABELLOOPSEDITBOXINCREMENT)->GetElement(0)->dwTextFormat = DT_LEFT | DT_VCENTER;

	g_HUD.AddEditBox(IDC_THREADSEDITBOXSTART, L" 0 ", 97, iY += (32 + 5), 65, 32);
	g_HUD.AddStatic(IDC_LABELTHREADSEDITBOXSTART, L"Threads Start", 0, iY, 105, 31);
	g_HUD.GetControl(IDC_LABELTHREADSEDITBOXSTART)->GetElement(0)->dwTextFormat = DT_LEFT | DT_VCENTER;

	g_HUD.AddEditBox(IDC_THREADSEDITBOXFINISH, L" 5 ", 97, iY += 32, 65, 32);
	g_HUD.AddStatic(IDC_LABELTHREADSEDITBOXFINISH, L"Threads End", 0, iY, 105, 31);
	g_HUD.GetControl(IDC_LABELTHREADSEDITBOXFINISH)->GetElement(0)->dwTextFormat = DT_LEFT | DT_VCENTER;

	g_HUD.AddEditBox(IDC_THREADSEDITBOXINCREMENT, L" 1 ", 97, iY += 32, 65, 32);
	g_HUD.AddStatic(IDC_LABELTHREADSEDITBOXINCREMENT, L"Threads Increment", 0, iY, 105, 31);
	g_HUD.GetControl(IDC_LABELTHREADSEDITBOXINCREMENT)->GetElement(0)->dwTextFormat = DT_LEFT | DT_VCENTER;

	g_HUD.AddEditBox(IDC_DPEDITBOXSTART, L"100", 97, iY += (32 + 5), 65, 32);
	g_HUD.AddStatic(IDC_LABELDPEDITBOXSTART, L"Draw Start", 0, iY, 105, 31);
	g_HUD.GetControl(IDC_LABELDPEDITBOXSTART)->GetElement(0)->dwTextFormat = DT_LEFT | DT_VCENTER;

	g_HUD.AddEditBox(IDC_DPEDITBOXFINISH, L" 2000 ", 97, iY += 32, 65, 32);
	g_HUD.AddStatic(IDC_LABELDPEDITBOXFINISH, L"Draw End", 0, iY, 105, 31);
	g_HUD.GetControl(IDC_LABELDPEDITBOXFINISH)->GetElement(0)->dwTextFormat = DT_LEFT | DT_VCENTER;

	g_HUD.AddEditBox(IDC_DPEDITBOXINCREMENT, L" 100 ", 97, iY += 32, 65, 32);
	g_HUD.AddStatic(IDC_LABELDPEDITBOXINCREMENT, L"Draw Increment", 0, iY, 105, 31);
	g_HUD.GetControl(IDC_LABELDPEDITBOXINCREMENT)->GetElement(0)->dwTextFormat = DT_LEFT | DT_VCENTER;

	g_HUD.AddCheckBox(IDC_FLUSHDATA, L"Flush data to file", 97, iY += 32, 26, 26, g_bFlushDataToFile);
	g_HUD.AddStatic(IDC_LABELFLUSHDATA, L"Flush data to file", 0, iY, 105, 31);
	g_HUD.GetControl(IDC_LABELFLUSHDATA)->GetElement(0)->dwTextFormat = DT_LEFT | DT_VCENTER;

	UpdateTestingInputControls(!g_bShowTestingUI || !g_bAutomateTesting);
	UpdateSaveSampleButton(g_bAutomateTesting, !g_bShowTestingUI);
	UpdateTestingRadioButtons(g_bAutomateTesting, !g_bShowTestingUI);

	g_UI.SetCallback(OnGUIEvent);
	g_UI.SetFont(1, L"Comic Sans MS", 24, FW_NORMAL);
	g_UI.SetFont(2, L"Courier New", 16, FW_NORMAL);

	g_UI.AddStatic(IDC_OUTPUT, L"FPS XX.XX", 3, 50, 100, 100);
	g_UI.GetStatic(IDC_OUTPUT)->SetTextColor(D3DCOLOR_ARGB(255, 255, 100, 100)); // Change color to red
	g_UI.GetControl(IDC_OUTPUT)->GetElement(0)->dwTextFormat = DT_LEFT | DT_TOP | DT_WORDBREAK;
	g_UI.GetControl(IDC_OUTPUT)->GetElement(0)->iFont = 2;
	g_UI.AddStatic(IDC_LABELMEASUREDCPU, L"Measured CPU", 3, 66, 100, 100);
	g_UI.GetStatic(IDC_LABELMEASUREDCPU)->SetTextColor(D3DCOLOR_ARGB(255, 255, 100, 100)); // Change color to red
	g_UI.GetControl(IDC_LABELMEASUREDCPU)->GetElement(0)->dwTextFormat = DT_LEFT | DT_TOP | DT_WORDBREAK;
	g_UI.GetControl(IDC_LABELMEASUREDCPU)->GetElement(0)->iFont = 2;

	g_UI.AddStatic(IDC_LABEL, L"Number of Worker Threads: 0", 3, 66, 300, 30);
	g_UI.GetStatic(IDC_LABEL)->SetTextColor(D3DCOLOR_ARGB(255, 255, 255, 0)); // Change color to green
	CDXUTControl* label = g_UI.GetControl(IDC_LABEL);
	label->GetElement(0)->dwTextFormat = DT_LEFT | DT_TOP | DT_WORDBREAK;
	label->GetElement(0)->iFont = 2;
	label->SetVisible(g_bMultiThread);

	// Slider
	g_UI.AddSlider(IDC_SLIDER, 300, 450, 500, 24, 1, g_dwMaxNumberofRecordThreads, g_dwNumberofRecordThreads, false);
	g_UI.GetControl(IDC_SLIDER)->SetVisible(g_bMultiThread);


	g_UI.AddStatic(IDC_LABELDP, L"Number of DrawPrimitives: 0", 3, 66, 300, 30);
	g_UI.GetStatic(IDC_LABELDP)->SetTextColor(D3DCOLOR_ARGB(255, 255, 255, 0)); // Change color to green
	g_UI.GetControl(IDC_LABELDP)->GetElement(0)->dwTextFormat = DT_LEFT | DT_TOP | DT_WORDBREAK;
	g_UI.GetControl(IDC_LABELDP)->GetElement(0)->iFont = 2;


	g_UI.AddStatic(IDC_LABELCPU, L"CPU Load per Draw: 0.0", 3, 82, 300, 30);
	g_UI.GetStatic(IDC_LABELCPU)->SetTextColor(D3DCOLOR_ARGB(255, 255, 255, 0)); // Change color to green
	g_UI.GetControl(IDC_LABELCPU)->GetElement(0)->dwTextFormat = DT_LEFT | DT_TOP | DT_WORDBREAK;
	g_UI.GetControl(IDC_LABELCPU)->GetElement(0)->iFont = 2;

	// Slider
	g_UI.AddSlider(IDC_SLIDERDP, 300, 420, 500, 24, 2, g_dwMaxNumberofSQRTDPs, g_dwNumberofRecordThreads, false);
	g_UI.AddSlider(IDC_SLIDERCPU, 300, 390, 500, 24, 0, g_dwMaxNumberofCPULoops, g_dwCPUWorkPerDP, false);

	for (auto& l : g_fArtificialCPULoad) l = 1;
}


//--------------------------------------------------------------------------------------
// Rejects any D3D9 devices that aren't acceptable to the app by returning false
bool CALLBACK IsDeviceAcceptable(D3DCAPS9* pCaps, D3DFORMAT AdapterFormat,
	D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext)
{
	// Skip backbuffer formats that don't support alpha blending
	IDirect3D9* pD3D = DXUTGetD3D9Object();
	if (FAILED(pD3D->CheckDeviceFormat(pCaps->AdapterOrdinal, pCaps->DeviceType,
		AdapterFormat, D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING,
		D3DRTYPE_TEXTURE, BackBufferFormat)))
		return false;

	// Must support pixel shader 2.0
	if (pCaps->PixelShaderVersion < D3DPS_VERSION(2, 0))
		return false;

	return true;
}


//--------------------------------------------------------------------------------------
// Called right before creating a D3D9 or D3D10 device, allowing the app to modify the device settings as needed
//--------------------------------------------------------------------------------------
bool CALLBACK ModifyDeviceSettings(DXUTDeviceSettings* pDeviceSettings, void* pUserContext)
{
	assert(DXUT_D3D9_DEVICE == pDeviceSettings->ver);

	HRESULT hr;
	IDirect3D9* pD3D = DXUTGetD3D9Object();
	D3DCAPS9 caps;

	V(pD3D->GetDeviceCaps(pDeviceSettings->d3d9.AdapterOrdinal,
		pDeviceSettings->d3d9.DeviceType,
		&caps));

	// If device doesn't support HW T&L or doesn't support 1.1 vertex shaders in HW 
	// then switch to SWVP.
	if ((caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 ||
		caps.VertexShaderVersion < D3DVS_VERSION(1, 1))
	{
		pDeviceSettings->d3d9.BehaviorFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	// Debugging vertex shaders requires either REF or software vertex processing 
	// and debugging pixel shaders requires REF.  
#ifdef DEBUG_VS
	if (pDeviceSettings->d3d9.DeviceType != D3DDEVTYPE_REF)
	{
		pDeviceSettings->d3d9.BehaviorFlags &= ~D3DCREATE_HARDWARE_VERTEXPROCESSING;
		pDeviceSettings->d3d9.BehaviorFlags &= ~D3DCREATE_PUREDEVICE;
		pDeviceSettings->d3d9.BehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}
#endif
#ifdef DEBUG_PS
	pDeviceSettings->d3d9.DeviceType = D3DDEVTYPE_REF;
#endif

	// For the first device created if its a REF device, optionally display a warning dialog box
	static bool s_bFirstTime = true;
	if (s_bFirstTime)
	{
		s_bFirstTime = false;
		if (pDeviceSettings->d3d9.DeviceType == D3DDEVTYPE_REF)
			DXUTDisplaySwitchingToREFWarning(pDeviceSettings->ver);
	}

	return true;
}


//--------------------------------------------------------------------------------------
// Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED)
// and aren't tied to the back buffer size
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	HRESULT hr;
	g_bRunLean = false;
	V_RETURN(g_DialogResourceManager.OnD3D9CreateDevice(pd3dDevice));
	V_RETURN(g_SettingsDlg.OnD3D9CreateDevice(pd3dDevice));
	// Initialize the font
	V_RETURN(D3DXCreateFont(pd3dDevice, 15, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"Arial", &g_pFont));

	// Read the D3DX effect file
	WCHAR str[MAX_PATH];
	V_RETURN(DXUTFindDXSDKMediaFileCch(str, MAX_PATH, L"CustomUI.fx"));

	// Setup the camera's view parameters
	D3DXVECTOR3 vecEye(0.0f, 1.5f, -7.0f);
	D3DXVECTOR3 vecAt(0.0f, 0.2f, 0.0f);
	D3DXVECTOR3 vecUp(0.0f, 1.0f, 0.0f);
	g_Camera.SetViewParams(&vecEye, &vecAt);
	D3DXMatrixLookAtLH(&g_mView, &vecEye, &vecAt, &vecUp);

	return S_OK;
}


//--------------------------------------------------------------------------------------
// This function loads the mesh and ensures the mesh has normals; it also optimizes the 
// mesh for the graphics card's vertex cache, which improves performance by organizing 
// the internal triangle list for less cache misses.
//--------------------------------------------------------------------------------------
HRESULT LoadMesh(IDirect3DDevice9* pd3dDevice, WCHAR* strFileName, ID3DXMesh** ppMesh)
{
	ID3DXMesh* pMesh = nullptr;
	WCHAR str[MAX_PATH];
	HRESULT hr;

	// Load the mesh with D3DX and get back a ID3DXMesh*.  For this
	// sample we'll ignore the X file's embedded materials since we know 
	// exactly the model we're loading.  See the mesh samples such as
	// "OptimizedMesh" for a more generic mesh loading example.
	V_RETURN(DXUTFindDXSDKMediaFileCch(str, MAX_PATH, strFileName));

	V_RETURN(D3DXLoadMeshFromX(str, D3DXMESH_MANAGED, pd3dDevice, nullptr, nullptr, nullptr, nullptr, &pMesh));

	DWORD* rgdwAdjacency = nullptr;

	// Make sure there are normals which are required for lighting
	if (!(pMesh->GetFVF() & D3DFVF_NORMAL))
	{
		ID3DXMesh* pTempMesh;
		V(pMesh->CloneMeshFVF(pMesh->GetOptions(),
			pMesh->GetFVF() | D3DFVF_NORMAL,
			pd3dDevice, &pTempMesh));
		V(D3DXComputeNormals(pTempMesh, nullptr));

		SAFE_RELEASE(pMesh);
		pMesh = pTempMesh;
	}

	// Optimize the mesh for this graphics card's vertex cache 
	// so when rendering the mesh's triangle list the vertices will 
	// cache hit more often so it won't have to re-execute the vertex shader 
	// on those vertices so it will improve perf.     
	rgdwAdjacency = new (std::nothrow) DWORD[pMesh->GetNumFaces() * 3];
	if (rgdwAdjacency == nullptr)
		return E_OUTOFMEMORY;
	V(pMesh->GenerateAdjacency(1e-6f, rgdwAdjacency));
	V(pMesh->OptimizeInplace(D3DXMESHOPT_VERTEXCACHE, rgdwAdjacency, nullptr, nullptr, nullptr));
	delete[]rgdwAdjacency;

	*ppMesh = pMesh;

	return S_OK;
}


//--------------------------------------------------------------------------------------
// Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) 
// or that are tied to the back buffer size 
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnResetDevice(IDirect3DDevice9* pd3dDevice,
	const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	HRESULT hr;
	g_bRunLean = false;
	V_RETURN(g_DialogResourceManager.OnD3D9ResetDevice());
	V_RETURN(g_SettingsDlg.OnD3D9ResetDevice());

	if (g_pFont)
		V_RETURN(g_pFont->OnResetDevice());
	if (g_pEffect)
		V_RETURN(g_pEffect->OnResetDevice());

	// Create a sprite to help batch calls when drawing many lines of text
	V_RETURN(D3DXCreateSprite(pd3dDevice, &g_pTextSprite));

	// Setup the camera's projection parameters
	float fAspectRatio = pBackBufferSurfaceDesc->Width / (FLOAT)pBackBufferSurfaceDesc->Height;
	g_Camera.SetProjParams(D3DX_PI / 4, fAspectRatio, 0.1f, 1000.0f);
	g_Camera.SetWindow(pBackBufferSurfaceDesc->Width, pBackBufferSurfaceDesc->Height);

	g_HUD.SetLocation(pBackBufferSurfaceDesc->Width - 170, 0);
	g_HUD.SetSize(170, 170);
	g_UI.SetLocation(0, 0);
	g_UI.SetSize(pBackBufferSurfaceDesc->Width, pBackBufferSurfaceDesc->Height);

	g_UI.GetControl(IDC_OUTPUT)->SetSize(pBackBufferSurfaceDesc->Width - 170, pBackBufferSurfaceDesc->Height / 4);
	g_UI.GetControl(IDC_LABELMEASUREDCPU)->SetSize(pBackBufferSurfaceDesc->Width - 170, pBackBufferSurfaceDesc->Height / 4);
	g_UI.GetControl(IDC_LABEL)->SetLocation(7, pBackBufferSurfaceDesc->Height - 50);

	WCHAR wszOutput[1024];
	StringCchPrintf(wszOutput, 1024, L"Number of Worker Threads: %d", g_dwNumberofRecordThreads);
	g_UI.GetStatic(IDC_LABEL)->SetText(wszOutput);
	g_UI.GetControl(IDC_SLIDER)->SetLocation(310, pBackBufferSurfaceDesc->Height - 50);
	g_UI.GetControl(IDC_LABEL)->SetVisible(g_bMultiThread);
	g_UI.GetControl(IDC_SLIDER)->SetVisible(g_bMultiThread);
	((CDXUTSlider*)g_UI.GetControl(IDC_SLIDER))->SetValue(g_dwNumberofRecordThreads);


	g_UI.GetControl(IDC_LABELDP)->SetLocation(7, pBackBufferSurfaceDesc->Height - 66);
	int NumberDPs = g_dwNumberofObjectsSqrt * g_dwNumberofObjectsSqrt;

	StringCchPrintf(wszOutput, 1024, L"Number of DrawPrimitives: %d", NumberDPs);
	g_UI.GetStatic(IDC_LABELDP)->SetText(wszOutput);
	g_UI.GetControl(IDC_SLIDERDP)->SetLocation(310, pBackBufferSurfaceDesc->Height - 66);
	((CDXUTSlider*)g_UI.GetControl(IDC_SLIDERDP))->SetValue(g_dwNumberofObjectsSqrt);

	float fCPULoad = float(g_dwCPUWorkPerDP) * g_fCPUScale;
	StringCchPrintf(wszOutput, 1024, L"CPU Load per Draw: %f", fCPULoad);
	g_UI.GetStatic(IDC_LABELCPU)->SetText(wszOutput);
	g_UI.GetControl(IDC_LABELCPU)->SetLocation(7, pBackBufferSurfaceDesc->Height - 82);
	g_UI.GetControl(IDC_SLIDERCPU)->SetLocation(310, pBackBufferSurfaceDesc->Height - 82);
	((CDXUTSlider*)g_UI.GetControl(IDC_SLIDERDP))->SetValue(g_dwCPUWorkPerDP);

	return S_OK;
}


void SetState(int Loops, int DPs, int Threads)
{
	int CPULoops = max(min(Loops, g_dwMaxNumberofCPULoops), g_dwMinNumberofCPULoops);
	int SQRTDPs = max(min((int)(sqrt((float)DPs)), g_dwMaxNumberofSQRTDPs), g_dwMinNumberofSQRTDPs);
	int iThreads = max(min(Threads, g_dwMaxNumberofRecordThreads), g_dwMinNumberofRecordThreads);

	g_bUpdateThreadCount = true;
	g_bUpdateControls = true;
	g_bUpdateDPs = true;

	if (!g_bInAutoTesting)
		g_UI.GetSlider(IDC_SLIDER)->SetVisible(g_bMultiThread);
	g_UI.GetSlider(IDC_SLIDER)->SetValue(iThreads);
	g_UI.GetSlider(IDC_SLIDER)->Refresh();
	g_dwNumberofRecordThreads_toBeSet = iThreads;

	g_UI.GetSlider(IDC_SLIDERDP)->SetValue(SQRTDPs);
	g_UI.GetSlider(IDC_SLIDERDP)->Refresh();
	g_dwNumberofObjectsSqrt = SQRTDPs;

	g_UI.GetSlider(IDC_SLIDERCPU)->SetValue(CPULoops);
	g_UI.GetSlider(IDC_SLIDERCPU)->Refresh();
	UpdateFromCPUWorkPerDPSliderChange(CPULoops);
}

//--------------------------------------------------------------------------------------
// Handle updates to the scene.  This is called regardless of which D3D API is used
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameMove(double fTime, float fElapsedTime, void* pUserContext)
{
	g_AverageFPS.MarkFrame();
	if (!g_bInAutoTesting && g_AverageFPS.GetElapsedTime() > 5)
		g_AverageFPS.Reset();
	float fFPS = g_AverageFPS.GetAverageFPS();

	float fMeasuredCPUActivePerDraw = MeasureCPUActive();
	g_dwACPULoadPosition = (g_dwACPULoadPosition + 1) % std::size(g_fArtificialCPULoad);
	g_fArtificialCPULoad[g_dwACPULoadPosition] = fMeasuredCPUActivePerDraw;
	if (g_bInAutoTesting || fFPS > 3.0f)
		g_fArtificialCPULoadPerFrame = AverageArtificialCPULoadSamples();
	else
		g_fArtificialCPULoadPerFrame = fMeasuredCPUActivePerDraw;



	g_bCheckDrawTime = true;
	g_dwCPUPosition = (g_dwCPUPosition + 1) % std::size(g_fCPU);
	g_fCPU[g_dwCPUPosition] = g_fDrawCost;
	if (g_bInAutoTesting || fFPS > 3.0f)
		g_fMeasuredTotalCPULoadPerDraw = AverageCPUSamples();
	else
		g_fMeasuredTotalCPULoadPerDraw = g_fDrawCost;


	WCHAR wszOutput[1024];
	if (g_bMultiThread)
	{
		StringCchPrintf(wszOutput, 1024, L"%s FPS %.2f with %d threads with %s.",
			(g_SampleStabilizationState == SAMPLE_STABILIZATION::STEP3_RECORD) ? L"  MEASURING" : L"Stabilizing",
			fFPS,
			g_dwNumberofRecordThreads + 1,
			g_bAllowRecordToOverlapPlayback ? L"Playback Overlap" : L"No Playback Overlap");
	}
	else
	{
		StringCchPrintf(wszOutput, 1024, L"%s FPS %.2f ",
			(g_SampleStabilizationState == SAMPLE_STABILIZATION::STEP3_RECORD) ? L"  MEASURING" : L"Stabilizing",
			fFPS);
	}

	g_UI.GetStatic(IDC_OUTPUT)->SetText(wszOutput);
	if (g_bInAutoTesting)
		StringCchPrintf(wszOutput, 1024, L"Testing Loops = %d, DP goal = %d, Threads = %d config. Last Measured FPS = %.3f\n Measured cpu load per draw call: %.1f microseconds. %.1f microseconds generated from %zu loops", g_TestLoops, g_TestDPs, g_TestThreads, g_fMeasuredFPS, g_fMeasuredTotalCPULoadPerDraw, g_fArtificialCPULoadPerFrame, g_dwCPULoops);
	else
		StringCchPrintf(wszOutput, 1024, L"Measured cpu load per draw call: %.1f microseconds. %.1f microseconds generated from %zu loops", g_fMeasuredTotalCPULoadPerDraw, g_fArtificialCPULoadPerFrame, g_dwCPULoops);
	g_UI.GetStatic(IDC_LABELMEASUREDCPU)->SetText(wszOutput);

	if (g_bAutoTesting && g_bStopTesting)
	{
		g_bAutoTesting = false;
		g_bInAutoTesting = false;
		g_bSaveSample = false;
		if (g_pOutputFile)
			fclose(g_pOutputFile);
		g_pOutputFile = nullptr;
		ShowSliders(true);
		g_HUD.GetButton(IDC_STARTTESTING)->SetText(L"Start Testing");
	}
	if ((g_bSaveSample || g_bAutoTesting) && !g_bInAutoTesting && g_pOutputFile == nullptr)
	{
		ShowSliders(false);
		OpenDataFile("c:\\testresults.txt");
		if (g_bSaveSample)
		{
			g_TestStartLoops = g_dwCPULoops;
			g_TestEndLoops = g_dwCPULoops;
			g_TestLoopsIncrement = 10;

			g_TestStartDPs = g_dwNumberofObjectsSqrt;
			g_TestEndDPs = g_dwNumberofObjectsSqrt;
			g_TestDPsIncrement = 10;

			g_TestStartThreads = g_dwNumberofRecordThreads;
			g_TestEndThreads = g_dwNumberofRecordThreads;
			g_TestThreadsIncrement = 10;
			g_bAutoTesting = true;
			g_bSaveSample = false;
		}
		else
		{
			OutputHeader(g_pOutputFile);
			SetState(g_TestStartLoops, g_TestStartDPs, g_TestStartThreads);
		}
		g_SampleStabilizationState = SAMPLE_STABILIZATION::STEP1_RESET;
		QueryPerformanceCounter(&g_TestStartTime);
		g_bInAutoTesting = true;
	}
	if (g_bAutoTesting && g_bInAutoTesting && g_pOutputFile)
	{
		ShowSliders(false);

		switch (g_SampleStabilizationState)
		{
		case SAMPLE_STABILIZATION::STEP1_RESET:
		{
			g_SampleStabilizationState = SAMPLE_STABILIZATION::STEP2_STABILIZE;
			g_AverageFPS.Reset();
		}
		break;
		case SAMPLE_STABILIZATION::STEP2_STABILIZE:
			if (g_AverageFPS.GetElapsedTime() > 2.f) // wait # seconds to stabilize
			{
				g_SampleStabilizationState = SAMPLE_STABILIZATION::STEP3_RECORD;
				g_AverageFPS.Reset();
			}
			break;
		case SAMPLE_STABILIZATION::STEP3_RECORD:
			if (// g_AverageFPS.GetElapsedFrames() > 100 // wait for # frames
				// ||
				g_AverageFPS.GetElapsedTime() > 5.f) // or # seconds
			{
				g_SampleStabilizationState = SAMPLE_STABILIZATION::STEP1_RESET;

				g_fMeasuredFPS = g_AverageFPS.GetAverageFPS();

				int NumberDPs = CalculateDPs();
				int DPs = max(min(NumberDPs, g_dwMaxNumberofSQRTDPs * g_dwMaxNumberofSQRTDPs), g_dwMinNumberofSQRTDPs * g_dwMinNumberofSQRTDPs);

				int currentThreads = g_bMultiThread ? max(min(g_dwNumberofRecordThreads, g_dwMaxNumberofRecordThreads), g_dwMinNumberofRecordThreads) : 0;
				OutputData(g_pOutputFile,
					max(min(g_dwCPULoops, g_dwMaxNumberofCPULoops), g_dwMinNumberofCPULoops),
					DPs,
					currentThreads,
					g_fMeasuredTotalCPULoadPerDraw,
					g_fArtificialCPULoadPerFrame,
					g_fMeasuredFPS,
					1.f / g_fMeasuredFPS);
				g_TestLoops += g_TestLoopsIncrement;
				if (g_TestLoops > g_TestEndLoops)
				{
					g_TestLoops = g_TestStartLoops;

					// We are incrementing the goal DPs, but in reality use the square root
					// Keep incrementing until we get to the next unique square root value.
					int lastSqrtDP = (int)(sqrt(float(g_TestDPs)));
					do
					{
						g_TestDPs += g_TestDPsIncrement;
					} while (lastSqrtDP == (int)(sqrt(float(g_TestDPs))));

					if (g_TestDPs > g_TestEndDPs)
					{
						g_TestDPs = g_TestStartDPs;
						g_TestThreads += g_TestThreadsIncrement;
						if (g_TestThreads > g_TestEndThreads)
						{
							if (g_pOutputFile)
							{
								fclose(g_pOutputFile);
							}
							g_bAutoTesting = false;
							g_bInAutoTesting = false;
							g_bSaveSample = false;
							g_pOutputFile = nullptr;
							ShowSliders(true);
							g_HUD.GetButton(IDC_STARTTESTING)->SetText(L"Start Testing");
						}
					}
				}
				else if (g_bSaveSample)
				{
					if (g_pOutputFile)
					{
						fclose(g_pOutputFile);
					}
					g_bAutoTesting = false;
					g_bInAutoTesting = false;
					g_bSaveSample = false;
					g_pOutputFile = nullptr;
					ShowSliders(true);
					g_HUD.GetButton(IDC_STARTTESTING)->SetText(L"Start Testing");
					return;
				}
#if 0
				char temp[300];
				sprintf_s(temp, 299, "loop %d,DPs %d,Threads %d\n", g_TestLoops, g_TestDPs, g_TestThreads);
				OutputDebugStringA(temp);
#endif
				if (g_bAutoTesting && g_bInAutoTesting && g_pOutputFile)
					SetState(g_TestLoops, g_TestDPs, g_TestThreads);
			}
			break;
		default:
			assert(!"Invalid g_SampleStabilizationState");
		}
	}
	else if (g_bAutoTesting && g_bInAutoTesting && g_pOutputFile == nullptr)
	{
		g_bSaveSample = false;
		g_bAutoTesting = false;
		g_bInAutoTesting = false;
		g_pOutputFile = nullptr;
		g_HUD.GetButton(IDC_STARTTESTING)->SetText(L"Start Testing");
	}
}

void UpdateFromControls()
{
	if (g_bUpdateThreading)
	{
#if DOTRACE
		char temp[300];
		sprintf_s(temp, 299, "UpdateFromControls UpdateThreading.\n");
		OutputDebugStringA(temp);
#endif
		UpdateFromThreadingChange();
	}
	g_bUpdateThreading = false;
	if (g_bUpdateThreadCount)
	{
#if DOTRACE
		char temp[300];
		sprintf_s(temp, 299, "UpdateFromControls UpdateThreadCount.\n");
		OutputDebugStringA(temp);
#endif
		UpdateFromNumberThreadsSliderChange();
	}
	g_bUpdateThreadCount = false;
	if (g_bUpdateDPs)
	{
#if DOTRACE
		char temp[300];
		sprintf_s(temp, 299, "UpdateFromControls UpdateDPs.\n");
		OutputDebugStringA(temp);
#endif
		UpdateFromNumberDPsSliderChange();
	}
	g_bUpdateDPs = false;

	// Update the thread count
	g_dwNumberofRecordThreads = g_dwNumberofRecordThreads_toBeSet;
	if (g_bAutoTesting)
		g_bMultiThread = g_dwNumberofRecordThreads > 0;
}

//--------------------------------------------------------------------------------------
// Render the scene using the D3D9 device
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	if (!g_bRunLean)
	{
		if (g_SettingsDlg.IsActive())
		{
			g_SettingsDlg.OnRender(fElapsedTime);
			return;
		}
	}


	SetUpGeometry(pd3dDevice);

	HRESULT hr;
	if (g_bMultiThread)
	{
		SetUpThreads();
		Playback(pd3dDevice, fElapsedTime);
	}
	else
	{
		DestroyThreads();
		if (g_bUpdateControls)
		{
			UpdateFromControls();
			InValidateAllBuffers();
			Sleep(10);
			g_bUpdateControls = false;
		}

		// Clear the render target and the zbuffer     
		V(pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0));


		// Render the scene
		if (SUCCEEDED(pd3dDevice->BeginScene()))
		{
			Render(0, pd3dDevice, false);

			if (!g_bRunLean)
			{
				RenderText();
				V(g_HUD.OnRender(fElapsedTime));
				V(g_UI.OnRender(fElapsedTime));
			}
			V(pd3dDevice->EndScene());
		}
	}
}


//--------------------------------------------------------------------------------------
// Render the help and statistics text. This function uses the ID3DXFont interface for 
// efficient text rendering.
//--------------------------------------------------------------------------------------
void RenderText()
{
	CDXUTTextHelper txtHelper(g_pFont, g_pTextSprite, 15);

	// Output statistics
	txtHelper.Begin();
	txtHelper.SetInsertionPos(5, 5);
	txtHelper.SetForegroundColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	txtHelper.DrawTextLine(DXUTGetFrameStats(DXUTIsVsyncEnabled()));
	txtHelper.DrawTextLine(DXUTGetDeviceStats());
	txtHelper.SetForegroundColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	txtHelper.SetForegroundColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	txtHelper.DrawTextLine(L"Press ESC to quit. F1 to render only test objects.");
	txtHelper.End();
}


//--------------------------------------------------------------------------------------
// Handle messages to the application
//--------------------------------------------------------------------------------------
LRESULT CALLBACK MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	// Always allow dialog resource manager calls to handle global messages
	// so GUI state is updated correctly
	//*pbNoFurtherProcessing = CDXUTIMEEditBox::StaticMsgProc( hWnd, uMsg, wParam, lParam );
	//if( *pbNoFurtherProcessing )
	//    return 0;
	*pbNoFurtherProcessing = g_DialogResourceManager.MsgProc(hWnd, uMsg, wParam, lParam);
	if (*pbNoFurtherProcessing)
		return 0;

	if (g_SettingsDlg.IsActive())
	{
		g_SettingsDlg.MsgProc(hWnd, uMsg, wParam, lParam);
		return 0;
	}

	// Give the dialogs a chance to handle the message first
	*pbNoFurtherProcessing = g_HUD.MsgProc(hWnd, uMsg, wParam, lParam);
	if (*pbNoFurtherProcessing)
		return 0;
	*pbNoFurtherProcessing = g_UI.MsgProc(hWnd, uMsg, wParam, lParam);
	if (*pbNoFurtherProcessing)
		return 0;

	// Pass all remaining windows messages to camera so it can respond to user input
	g_Camera.HandleMessages(hWnd, uMsg, wParam, lParam);

	return 0;
}


//--------------------------------------------------------------------------------------
// Handle key presses
//--------------------------------------------------------------------------------------
void CALLBACK KeyboardProc(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
	if (bKeyDown)
	{
		switch (nChar)
		{
		case VK_F1: g_bRunLean = !g_bRunLean; break;
		}
	}
}

int CalculateDPs()
{
	return g_dwNumberofObjectsSqrt * g_dwNumberofObjectsSqrt;
}

void ShowSliders(bool bShow)
{
	if (bShow)
	{
		g_UI.GetControl(IDC_LABEL)->SetVisible(g_bMultiThread);
		g_UI.GetControl(IDC_SLIDER)->SetVisible(g_bMultiThread);
	}
	else
	{
		g_UI.GetControl(IDC_LABEL)->SetVisible(false);
		g_UI.GetControl(IDC_SLIDER)->SetVisible(false);
	}
	g_UI.GetControl(IDC_LABELDP)->SetVisible(bShow);
	g_UI.GetControl(IDC_SLIDERDP)->SetVisible(bShow);
	g_UI.GetControl(IDC_LABELCPU)->SetVisible(bShow);
	g_UI.GetControl(IDC_SLIDERCPU)->SetVisible(bShow);
}

void UpdateFromNumberThreadsSliderChange()
{
	int dwThreads = g_UI.GetSlider(IDC_SLIDER)->GetValue();
	if (g_bAutoTesting)
		dwThreads = g_TestThreads;
	WCHAR wszOutput[1024];
	if (dwThreads != g_dwNumberofRecordThreads && g_bMultiThread)
	{
		DestroyThreads();
		//DestroyGeometry();
		g_bMultiThread = true;
		g_dwNumberofRecordThreads_toBeSet = dwThreads;
	}
	StringCchPrintf(wszOutput, 1024, L"Number of Worker Threads: %d",
		dwThreads);
	g_UI.GetStatic(IDC_LABEL)->SetText(wszOutput);
	int NumberDPs = CalculateDPs();
	StringCchPrintf(wszOutput, 1024, L"Number of DrawPrimitives: %d", NumberDPs);
	g_UI.GetStatic(IDC_LABELDP)->SetText(wszOutput);
}

void UpdateFromNumberDPsSliderChange()
{
	int dwObjectsSQRT = g_UI.GetSlider(IDC_SLIDERDP)->GetValue();
	WCHAR wszOutput[1024];
	bool bMultiThread = g_bMultiThread;
	int dwThreads = g_dwNumberofRecordThreads;
	if (dwObjectsSQRT != g_dwNumberofObjectsSqrt)
	{
		g_dwNumberofObjectsSqrt = dwObjectsSQRT;
		DestroyThreads();
		g_bMultiThread = bMultiThread;
		g_dwNumberofRecordThreads_toBeSet = dwThreads;
	}
	StringCchPrintf(wszOutput, 1024, L"Number of Worker Threads: %c",
		dwThreads);
	g_UI.GetStatic(IDC_LABEL)->SetText(wszOutput);
	int NumberDPs = CalculateDPs();
	StringCchPrintf(wszOutput, 1024, L"Number of DrawPrimitives: %d", NumberDPs);
	g_UI.GetStatic(IDC_LABELDP)->SetText(wszOutput);
}

void UpdateFromThreadingChange()
{
	WCHAR wszOutput[1024];
	g_bMultiThread = !g_bMultiThread;
	bool bMultiThread = g_bMultiThread;
	g_UI.GetControl(IDC_LABEL)->SetVisible(g_bMultiThread);
	g_UI.GetControl(IDC_SLIDER)->SetVisible(g_bMultiThread);
	DestroyThreads();
	g_bMultiThread = bMultiThread;
	int NumberDPs = CalculateDPs();
	((CDXUTSlider*)g_UI.GetControl(IDC_SLIDERDP))->SetValue(g_dwNumberofObjectsSqrt);
	StringCchPrintf(wszOutput, 1024, L"Number of DrawPrimitives: %d", NumberDPs);
	g_UI.GetStatic(IDC_LABELDP)->SetText(wszOutput);
	((CDXUTSlider*)g_UI.GetControl(IDC_SLIDER))->SetValue(g_dwNumberofRecordThreads);
	StringCchPrintf(wszOutput, 1024, L"Number of Worker Threads: %d", g_dwNumberofRecordThreads);
	g_UI.GetStatic(IDC_LABEL)->SetText(wszOutput);

}


void UpdateFromCPUWorkPerDPSliderChange(DWORD dwCPUWorkPerDP)
{
	WCHAR wszOutput[1024];
	g_dwCPULoops = dwCPUWorkPerDP;
	StringCchPrintf(wszOutput, 1024, L"Target CPU Load per Draw: %lu", dwCPUWorkPerDP);
	g_UI.GetStatic(IDC_LABELCPU)->SetText(wszOutput);
}

void UpdateTestingRadioButtons(bool bAutomateTesting, bool bHide)
{
	g_HUD.GetRadioButton(IDC_AUTOMATETESTING)->SetVisible(!bHide);
	g_HUD.GetRadioButton(IDC_MANUALTESTING)->SetVisible(!bHide);
	if (bAutomateTesting)
		g_HUD.GetRadioButton(IDC_AUTOMATETESTING)->SetChecked(true);
	else
		g_HUD.GetRadioButton(IDC_MANUALTESTING)->SetChecked(true);
}

void UpdateSaveSampleButton(bool bShowSaveSample, bool bHideBoth)
{
	if (bHideBoth)
	{
		g_HUD.GetButton(IDC_STARTTESTING)->SetVisible(false);
		g_HUD.GetButton(IDC_OUTPUTSAMPLE)->SetVisible(false);
	}
	else
	{
		g_HUD.GetButton(IDC_STARTTESTING)->SetVisible(!bShowSaveSample);
		g_HUD.GetButton(IDC_OUTPUTSAMPLE)->SetVisible(bShowSaveSample);
	}
}

void UpdateTestingInputControls(bool bHideControls)
{

	g_HUD.GetControl(IDC_LABELLOOPSEDITBOXSTART)->SetVisible(!bHideControls);
	g_HUD.GetEditBox(IDC_LOOPSEDITBOXSTART)->SetVisible(!bHideControls);
	g_HUD.GetStatic(IDC_LABELLOOPSEDITBOXSTART)->SetVisible(!bHideControls);

	g_HUD.GetControl(IDC_LABELLOOPSEDITBOXFINISH)->SetVisible(!bHideControls);
	g_HUD.GetEditBox(IDC_LOOPSEDITBOXFINISH)->SetVisible(!bHideControls);
	g_HUD.GetStatic(IDC_LABELLOOPSEDITBOXFINISH)->SetVisible(!bHideControls);

	g_HUD.GetControl(IDC_LABELLOOPSEDITBOXINCREMENT)->SetVisible(!bHideControls);
	g_HUD.GetEditBox(IDC_LOOPSEDITBOXINCREMENT)->SetVisible(!bHideControls);
	g_HUD.GetStatic(IDC_LABELLOOPSEDITBOXINCREMENT)->SetVisible(!bHideControls);

	g_HUD.GetControl(IDC_LABELTHREADSEDITBOXSTART)->SetVisible(!bHideControls);
	g_HUD.GetEditBox(IDC_THREADSEDITBOXSTART)->SetVisible(!bHideControls);
	g_HUD.GetStatic(IDC_LABELTHREADSEDITBOXSTART)->SetVisible(!bHideControls);

	g_HUD.GetControl(IDC_LABELTHREADSEDITBOXFINISH)->SetVisible(!bHideControls);
	g_HUD.GetEditBox(IDC_THREADSEDITBOXFINISH)->SetVisible(!bHideControls);
	g_HUD.GetStatic(IDC_LABELTHREADSEDITBOXFINISH)->SetVisible(!bHideControls);

	g_HUD.GetControl(IDC_LABELTHREADSEDITBOXINCREMENT)->SetVisible(!bHideControls);
	g_HUD.GetEditBox(IDC_THREADSEDITBOXINCREMENT)->SetVisible(!bHideControls);
	g_HUD.GetStatic(IDC_LABELTHREADSEDITBOXINCREMENT)->SetVisible(!bHideControls);

	g_HUD.GetControl(IDC_LABELDPEDITBOXSTART)->SetVisible(!bHideControls);
	g_HUD.GetEditBox(IDC_DPEDITBOXSTART)->SetVisible(!bHideControls);
	g_HUD.GetStatic(IDC_LABELDPEDITBOXSTART)->SetVisible(!bHideControls);

	g_HUD.GetControl(IDC_LABELDPEDITBOXFINISH)->SetVisible(!bHideControls);
	g_HUD.GetEditBox(IDC_DPEDITBOXFINISH)->SetVisible(!bHideControls);
	g_HUD.GetStatic(IDC_LABELDPEDITBOXFINISH)->SetVisible(!bHideControls);

	g_HUD.GetControl(IDC_LABELDPEDITBOXINCREMENT)->SetVisible(!bHideControls);
	g_HUD.GetEditBox(IDC_DPEDITBOXINCREMENT)->SetVisible(!bHideControls);
	g_HUD.GetStatic(IDC_LABELDPEDITBOXINCREMENT)->SetVisible(!bHideControls);

	g_HUD.GetControl(IDC_FLUSHDATA)->SetVisible(!bHideControls);
	g_HUD.GetStatic(IDC_LABELFLUSHDATA)->SetVisible(!bHideControls);


}

void GetTestData()
{
	g_TestStartLoops = _wtoi(g_HUD.GetEditBox(IDC_LOOPSEDITBOXSTART)->GetText());
	g_TestEndLoops = _wtoi(g_HUD.GetEditBox(IDC_LOOPSEDITBOXFINISH)->GetText());
	g_TestLoopsIncrement = _wtoi(g_HUD.GetEditBox(IDC_LOOPSEDITBOXINCREMENT)->GetText());
	g_TestStartDPs = _wtoi(g_HUD.GetEditBox(IDC_DPEDITBOXSTART)->GetText());
	g_TestEndDPs = _wtoi(g_HUD.GetEditBox(IDC_DPEDITBOXFINISH)->GetText());
	g_TestDPsIncrement = _wtoi(g_HUD.GetEditBox(IDC_DPEDITBOXINCREMENT)->GetText());
	g_TestStartThreads = _wtoi(g_HUD.GetEditBox(IDC_THREADSEDITBOXSTART)->GetText());
	g_TestEndThreads = _wtoi(g_HUD.GetEditBox(IDC_THREADSEDITBOXFINISH)->GetText());
	g_TestThreadsIncrement = _wtoi(g_HUD.GetEditBox(IDC_THREADSEDITBOXINCREMENT)->GetText());
	g_bFlushDataToFile = g_HUD.GetCheckBox(IDC_FLUSHDATA)->GetChecked();

	g_TestLoops = g_TestStartLoops;
	g_TestDPs = g_TestStartDPs;
	g_TestThreads = g_TestStartThreads;
}

void OutputHeader(FILE* pfile)
{
	if (pfile)
		fprintf(pfile, "CPU Busy Loops\tDrawPrimitives\tThreads\tRenderCall CPU Cost\tCPU Busy Loops Cost\tFPS\tSPF\n");
}

void OutputData(FILE* pfile, int CPUBusyLoops, int DrawPrimitives, int Threads, float RenderCallCPUCost, float CPUBusyLoopsCost, float FPS, float SPF)
{
	if (pfile)
	{
		// render and busy loop timings are invalid for multiple threads, so clip them out if multithreaded
		if (Threads <= 1)
			fprintf(pfile, "%d\t%d\t%d\t%f\t%f\t%f\t%f\n", CPUBusyLoops, DrawPrimitives, Threads, RenderCallCPUCost, CPUBusyLoopsCost, FPS, SPF);
		else
			fprintf(pfile, "%d\t%d\t%d\t\t\t%f\t%f\n", CPUBusyLoops, DrawPrimitives, Threads, FPS, SPF);

		if (g_bFlushDataToFile)
			fflush(pfile);
	}
}

bool OpenDataFile(const char* fname)
{
	fopen_s(&g_pOutputFile, fname, "a");
	if (g_pOutputFile) fprintf(g_pOutputFile, "\n");
	return g_pOutputFile != nullptr;
}

//--------------------------------------------------------------------------------------
// Handles the GUI events
//--------------------------------------------------------------------------------------
void CALLBACK OnGUIEvent(UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext)
{
	if (g_bRunLean)
		return;

	switch (nControlID)
	{
	case IDC_TOGGLEFULLSCREEN:
		if (g_bAutoTesting)
			return;
		DXUTToggleFullScreen();
		break;
	case IDC_TOGGLEREF:
		if (g_bAutoTesting)
			return;
		DXUTToggleREF();
		break;
	case IDC_CHANGEDEVICE:
		if (g_bAutoTesting)
			return;
		g_SettingsDlg.SetActive(!g_SettingsDlg.IsActive());
		break;
	case IDC_PLAYBACKRECORDOVERLAP:
		if (g_bAutoTesting)
			return;
		g_bAllowRecordToOverlapPlayback = !g_bAllowRecordToOverlapPlayback;
		if (!g_bAllowRecordToOverlapPlayback)
		{
			g_HUD.GetButton(IDC_PLAYBACKRECORDOVERLAP)->SetText(L"Playback Overlap");
		}
		else
		{
			g_HUD.GetButton(IDC_PLAYBACKRECORDOVERLAP)->SetText(L"No Playback Overlap");
		}
		break;
	case IDC_TESTING:
		if (g_bAutoTesting)
			return;
		g_HUD.GetButton(IDC_STARTTESTING)->SetText(L"Start Testing");
		g_bShowTestingUI = !g_bShowTestingUI;
		UpdateTestingInputControls(!g_bShowTestingUI || !g_bAutomateTesting);
		UpdateSaveSampleButton(!g_bAutomateTesting, !g_bShowTestingUI);
		UpdateTestingRadioButtons(g_bAutomateTesting, !g_bShowTestingUI);
		break;
	case IDC_STARTTESTING:
		if (!g_bAutoTesting)
		{
			g_bStopTesting = false;
			GetTestData();
			g_bAutoTesting = true;
			g_HUD.GetButton(IDC_STARTTESTING)->SetText(L"Stop Testing");
		}
		else
		{
			g_bStopTesting = true;
			g_HUD.GetButton(IDC_STARTTESTING)->SetText(L"Start Testing");
		}
		break;
	case IDC_AUTOMATETESTING:
		if (g_bAutoTesting)
			return;
		g_bAutomateTesting = true;
		UpdateTestingRadioButtons(g_bAutomateTesting, !g_bShowTestingUI);
		UpdateTestingInputControls(!g_bShowTestingUI || !g_bAutomateTesting);
		UpdateSaveSampleButton(!g_bAutomateTesting, !g_bShowTestingUI);
		break;
	case IDC_OUTPUTSAMPLE:
		if (g_bAutoTesting)
			return;
		if (!g_bSaveSample)
			g_bSaveSample = true;
		break;
	case IDC_MANUALTESTING:
		if (g_bAutoTesting)
			return;
		Sleep(100);
		g_bAutomateTesting = false;
		UpdateTestingRadioButtons(g_bAutomateTesting, !g_bShowTestingUI);
		UpdateTestingInputControls(!g_bShowTestingUI || !g_bAutomateTesting);
		UpdateSaveSampleButton(!g_bAutomateTesting, !g_bShowTestingUI);
		break;
	case IDC_FLUSHDATA:
		if (g_bAutoTesting)
			return;
		g_bFlushDataToFile = g_HUD.GetCheckBox(IDC_FLUSHDATA)->GetChecked();
		break;
	case IDC_THREADING:
	{
		if (g_bAutoTesting)
			return;
		g_bUpdateThreading = true;
		g_bUpdateControls = true;
	}
	break;
	case IDC_SLIDER:
	{
		if (g_bAutoTesting)
			return;
		int dwThreads = g_UI.GetSlider(IDC_SLIDER)->GetValue();
		if (dwThreads != g_dwNumberofRecordThreads)
		{
			g_bUpdateThreadCount = true;
			g_bUpdateControls = true;
		}
	}
	break;
	case IDC_SLIDERDP:
	{
		if (g_bAutoTesting)
			return;
		int dwNumberofObjectSqrt = g_UI.GetSlider(IDC_SLIDERDP)->GetValue();
		if (g_dwNumberofObjectsSqrt != dwNumberofObjectSqrt)
		{
			g_bUpdateDPs = true;
			g_bUpdateControls = true;
		}
	}
	break;
	case IDC_SLIDERCPU:
	{
		if (g_bAutoTesting)
			return;
		DWORD dwCPUWorkPerDP = ((CDXUTSlider*)pControl)->GetValue();
		UpdateFromCPUWorkPerDPSliderChange(dwCPUWorkPerDP);
	}
	break;
	}
}

//--------------------------------------------------------------------------------------
// Release D3D9 resources created in the OnD3D9ResetDevice callback 
//--------------------------------------------------------------------------------------
void CALLBACK OnLostDevice(void* pUserContext)
{
	g_DialogResourceManager.OnD3D9LostDevice();
	g_SettingsDlg.OnD3D9LostDevice();
	DestroyGeometry();
	DestroyThreads();

	if (g_pFont)
		g_pFont->OnLostDevice();
	if (g_pEffect)
		g_pEffect->OnLostDevice();
	SAFE_RELEASE(g_pTextSprite);
}


//--------------------------------------------------------------------------------------
// Release D3D9 resources created in the OnD3D9CreateDevice callback 
//--------------------------------------------------------------------------------------
void CALLBACK OnDestroyDevice(void* pUserContext)
{
	g_DialogResourceManager.OnD3D9DestroyDevice();
	g_SettingsDlg.OnD3D9DestroyDevice();
	DestroyGeometry();
	DestroyThreads();

	SAFE_RELEASE(g_pEffect);
	SAFE_RELEASE(g_pFont);
}


//done above
unsigned __stdcall RenderThreadProc(void* pParam)
{
	DWORD nParam = (DWORD)(UINT_PTR)pParam;
	while (true)
	{
		WaitForSingleObject(g_RenderRecordSem[nParam], INFINITE);
		//figure out what buffer to use.
		DWORD nBuffer = nParam + g_dwNumberofRecordThreads * g_dwCurrentBufferSet;
		//don't start recording until everything is ready.
		if (g_DoRender)
		{
			//record your objects assigned to this thread.
			g_bCBValid[nBuffer] = true;

			g_pCBRecorder[nBuffer]->BeginCommandBuffer();

			Render(nParam, g_pCBRecorder[nBuffer], true);

			g_pCBRecorder[nBuffer]->EndCommandBuffer();
		}
		//finished with this recording.
		ReleaseSemaphore(g_RenderPlaybackSem[nParam], 1, nullptr);
	}
	return 0;
}


void Playback(IDirect3DDevice9* pd3dDevice, float fElapsedTime)
{
	LONG previous;
	DWORD dwCurrentBuildingSet = g_dwCurrentBufferSet;

	//get things started
	if (!g_DoRender)
	{
		g_DoRender = true;

		for (int i = 0; i < g_dwNumberofRecordThreads; i++)
			ReleaseSemaphore(g_RenderRecordSem[i], 1, &previous);
	}

	//signal that the threads can record this frame and wait for them to finish.
	WaitForMultipleObjects(g_dwNumberofRecordThreads, g_RenderPlaybackSem, TRUE, INFINITE);

	if (g_bUpdateControls)
	{
		DestroyThreads();
		UpdateFromControls();
		InValidateAllBuffers();
		Sleep(10);
		g_bUpdateControls = false;
	}
	else
	{
		//the threads have recorded data so now change to the next set of buffers
		g_dwCurrentBufferSet = (g_dwCurrentBufferSet + 1) % g_dwNumberofBufferSets;
	}

	if (g_bAllowRecordToOverlapPlayback)
	{
		//before I render the current recordings, I let the threads work on the next recordings.
		for (int i = 0; i < g_dwNumberofRecordThreads; i++)
			ReleaseSemaphore(g_RenderRecordSem[i], 1, &previous);
	}

	// Clear the backbuffer and the zbuffer
	pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	// Begin the scene
	if (SUCCEEDED(pd3dDevice->BeginScene()))
	{
		//playback each thread's recording buffer.
		for (int i = 0; i < g_dwNumberofRecordThreads; i++)
		{
			int iBuffer = i + dwCurrentBuildingSet * g_dwNumberofRecordThreads;
			if (g_bCBValid[i])//only play buffers that are valid.
			{
				//calculate the current buffers from the current buffer set.
				g_pCBPlayer->Playback(pd3dDevice, &g_CB[iBuffer]);
			}
		}

		if (!g_bRunLean)
		{
			RenderText();
			g_HUD.OnRender(fElapsedTime);
			g_UI.OnRender(fElapsedTime);
		}

		// End the scene
		pd3dDevice->EndScene();
	}

	g_dwFrame++;

	if (!g_bAllowRecordToOverlapPlayback)
	{
		//Let the threads work on the next recordings.
		for (int i = 0; i < g_dwNumberofRecordThreads; i++)
			ReleaseSemaphore(g_RenderRecordSem[i], 1, &previous);
	}
}

void SetUpThreads()
{

	if (g_bMultiThread && !g_bThreadsInitialized)
	{
		for (int i = 0; i < g_dwNumberofRecordThreads; i++)
		{
			//create record semiphore per thread
			if (g_RenderRecordSem[i])
				CloseHandle(g_RenderRecordSem[i]);
			g_RenderRecordSem[i] = CreateSemaphore(nullptr, 0, 1, nullptr);

			//create playback semiphore per thread
			if (g_RenderPlaybackSem[i])
				CloseHandle(g_RenderPlaybackSem[i]);
			g_RenderPlaybackSem[i] = CreateSemaphore(nullptr, 0, 1, nullptr);

			//create record thread
			if (g_RecordThreads[i])
				CloseHandle(g_RecordThreads[i]);
			g_RecordThreads[i] = (HANDLE)_beginthreadex(nullptr, 0, RenderThreadProc, (LPVOID)(UINT_PTR)i, 0, &g_ThreadIds[i]);
		}

		g_bThreadsInitialized = true;
		g_DoRender = false;
	}
}


//-----------------------------------------------------------------------------
// Name: SetUpGeometry()
// Desc: Create the Textures and vertex buffers
//-----------------------------------------------------------------------------
HRESULT SetUpGeometry(IDirect3DDevice9* pd3dDevice)
{
	if (g_pTexture == nullptr)
	{
		// Turn off culling
		pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		// Turn off D3D lighting
		pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		// Turn on the zbuffer
		pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		// Use D3DX to create a texture from a file based image
		if (FAILED(D3DXCreateTextureFromFile(pd3dDevice, L"banana.bmp", &g_pTexture)))
		{
			// If texture is not in current folder, try parent folder
			if (FAILED(D3DXCreateTextureFromFile(pd3dDevice, L"..\\banana.bmp", &g_pTexture)))
			{
				MessageBox(nullptr, L"Could not find banana.bmp", L"TexturesMultiThreaded.exe", MB_OK | MB_ICONERROR);
				return E_FAIL;
			}
		}
	}
	// Create the vertex buffer.
	if (g_pVB == nullptr)
	{
		if (FAILED(pd3dDevice->CreateVertexBuffer(50 * 2 * sizeof(CUSTOMVERTEX),
			0, D3DFVF_CUSTOMVERTEX,
			D3DPOOL_DEFAULT, &g_pVB, nullptr)))
		{
			return E_FAIL;
		}
		// Fill the vertex buffer. We are setting the tu and tv texture
		// coordinates, which range from 0.0 to 1.0
		CUSTOMVERTEX* pVertices;
		if (FAILED(g_pVB->Lock(0, 0, (void**)&pVertices, 0)))
			return E_FAIL;
		for (DWORD i = 0; i < 50; i++)
		{
			FLOAT theta = (2 * D3DX_PI * i) / (50 - 1);

			pVertices[2 * i + 0].position = D3DXVECTOR3(sinf(theta), -1.0f, cosf(theta));
			pVertices[2 * i + 0].color = 0xffffffff;

			pVertices[2 * i + 1].position = D3DXVECTOR3(sinf(theta), 1.0f, cosf(theta));
			pVertices[2 * i + 1].color = 0xff808080;
		}
		g_pVB->Unlock();
	}

	return S_OK;
}


// Desc: Releases all previously initialized objects
void ZeroThreadObjects()
{
	for (auto& s : g_RenderRecordSem) s = nullptr;
	for (auto& s : g_RenderPlaybackSem) s = nullptr;
	for (auto& t : g_RecordThreads) t = nullptr;
}


// Desc: Releases all previously initialized objects
void DestroyThreads()
{
	for (auto& s : g_RenderRecordSem)
	{
		if (s)
		{
			CloseHandle(s);
			s = nullptr;
		}
	}

	for (auto& s : g_RenderPlaybackSem)
	{
		if (s)
		{
			CloseHandle(s);
			s = nullptr;
		}
	}

	for (auto& t : g_RecordThreads)
	{
		if (t)
		{
			CloseHandle(t);
			t = nullptr;
		}
	}

	g_dwCurrentBufferSet = 0;
	g_bThreadsInitialized = false;
	g_DoRender = false;
}

void DestroyGeometry()
{
	SAFE_RELEASE(g_pTexture);
	SAFE_RELEASE(g_pVB);
}



//-----------------------------------------------------------------------------
// Name: SetupMatrices()
// Desc: Sets up the world, view, and projection transform matrices.
//-----------------------------------------------------------------------------
void SetupMatrices(D3DXVECTOR3* pvOffSet, DWORD dwPhase, IDirect3DDevice9* pDevice)
{
	// Set up world matrix
	D3DXMATRIXA16 matWorld, matWorldOffSet, matWorldRotate;
	D3DXMatrixIdentity(&matWorldRotate);
	D3DXMatrixRotationX(&matWorldRotate, (timeGetTime() + dwPhase) / 1000.0f);
	D3DXMatrixTranslation(&matWorldOffSet, pvOffSet->x, pvOffSet->y, pvOffSet->z);
	D3DXMatrixMultiply(&matWorld, &matWorldRotate, &matWorldOffSet);
	pDevice->SetTransform(D3DTS_WORLD, &matWorld);

	// Set up our view matrix. A view matrix can be defined given an eye point,
	// a point to lookat, and a direction for which way is up. Here, we set the
	// eye five units back along the z-axis and up three units, look at the
	// origin, and define "up" to be in the y-direction.
	D3DXVECTOR3 vEyePt(0.0f, 0.0f, -5.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	pDevice->SetTransform(D3DTS_VIEW, &matView);

	// For the projection matrix, we set up a perspective transform (which
	// transforms geometry from 3D view space to 2D viewport space, with
	// a perspective divide making objects smaller in the distance). To build
	// a perpsective transform, we need the field of view (1/4 pi is common),
	// the aspect ratio, and the near and far clipping planes (which define at
	// what distances geometry should be no longer be rendered).
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 3000.0f);
	pDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
void Render(D3DXVECTOR3* pvOffSet, DWORD dwPhase, IDirect3DDevice9* pDevice, DWORD dwColor)
{
	BOOL bSuccess = false;

	//if you have not yet timed a draw do so now.
	if (g_bCheckDrawTime && g_lFrequency.QuadPart > 0)
	{
		bSuccess = QueryPerformanceCounter(&g_StartPerformanceCount);
	}

	CPUActive();
	// Setup the world, view, and projection matrices
	SetupMatrices(pvOffSet, dwPhase, pDevice);

	// Setup our texture. Using Textures introduces the texture stage states,
	// which govern how Textures get blended together (in the case of multiple
	// Textures) and lighting information. In this case, we are modulating
	// (blending) our texture with the diffuse color of the vertices.
	pDevice->SetRenderState(D3DRS_TEXTUREFACTOR, dwColor);
	pDevice->SetTexture(0, g_pTexture);
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TFACTOR);
	pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
	pDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

	// Render the vertex buffer contents
	pDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
	pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2 * 50 - 2);

	if (g_bCheckDrawTime && bSuccess)
	{
		if (QueryPerformanceCounter(&g_EndPerformanceCount))
		{
			LONGLONG time = g_EndPerformanceCount.QuadPart - g_StartPerformanceCount.QuadPart;
			float dtime = g_lFrequency.QuadPart / 1000000.0F;
			g_fDrawCost = time / dtime;
		}
	}

	if (g_bCheckDrawTime)
		g_bCheckDrawTime = false;
}

void Render(DWORD nParam, IDirect3DDevice9* pDevice, bool bMultiThread)
{
	D3DXVECTOR3 vTemp;
	vTemp.z = float(g_dwNumberofObjectsSqrt * 8);

	for (int i = 0; i < g_dwNumberofObjectsSqrt; i++)
	{
		if (!g_bMultiThread || i % g_dwNumberofRecordThreads == nParam)
		{
			for (int j = 0; j < g_dwNumberofObjectsSqrt; j++)
			{
				vTemp.x = float(4 * i - 2 * g_dwNumberofObjectsSqrt);
				vTemp.y = float(4 * j - 2 * g_dwNumberofObjectsSqrt);
				Render(&vTemp, i * j * 100, pDevice, g_dwColors[nParam % g_dwNumberofColors]);
			}
		}
	}
}

#if DEBUG
#define INNERLOOP   INNERLOOPDEBUG
#else
#define INNERLOOP   INNERLOOPRELEASE
#endif


//use 400.0 for the double for loop bound for release builds. Use 40.0 for debug
#define INNERLOOPRELEASE   for(double i=0.0f;i<40.0;i++)                                \
    {                                                                                   \
        const size_t index = g_dwAccess[g_dwAccessCounter % std::size(g_dwAccess)];     \
        g_dwAccessCounter += 1;                                                         \
        g_dwAccessCounter %= std::size(g_dwAccess);                                     \
        size_t dwValue = g_dwMemory[index];                                             \
        f = sqrt( f + 2.0f*((float)dwValue) );                                          \
    }                                                                                   \
    loops++;



//use 40.0 for the double for loop bound for debug builds.
#define INNERLOOPDEBUG   for(int i=0;i<4;i++)                                           \
    {                                                                                   \
        const size_t index = g_dwAccess[g_dwAccessCounter % std::size(g_dwAccess)];     \
        g_dwAccessCounter += 1;                                                         \
        g_dwAccessCounter %= std::size(g_dwAccess);                                     \
        size_t dwValue = g_dwMemory[index];                                             \
        f = sqrt( f + 2.0f*((float)dwValue) );                                          \
    }                                                                                   \
    loops++;



void CPUActive()
{
	size_t loops = 0;
	double f = 123.0;
	size_t g_dwAccessCounter = 0;

	while (loops < g_dwCPULoops)
	{
		INNERLOOP
	}
}


float MeasureCPUActive()
{
	LARGE_INTEGER start, end;
	float ret = 0.0f;

	if (g_lFrequency.QuadPart > 0 && QueryPerformanceCounter(&start))
	{
		size_t loops = 0;
		double f = 123.0;
		size_t g_dwAccessCounter = 0;

		while (loops < g_dwCPULoops)
		{
			INNERLOOP
		}

		QueryPerformanceCounter(&end);
		const LONGLONG time = end.QuadPart - start.QuadPart;

		float dtime = g_lFrequency.QuadPart / 1000000.0F;
		float fCurrentMicroSeconds = time / dtime;

		ret = fCurrentMicroSeconds;
	}

	return ret;
}

float AverageCPUSamples()
{
	float ret = 0.0f;

	for (auto s : g_fCPU) ret += s;

	return ret / float(std::size(g_fCPU));
}

float AverageArtificialCPULoadSamples()
{
	float ret = 0.0f;

	for (auto s : g_fArtificialCPULoad) ret += s;

	return ret / float(std::size(g_fArtificialCPULoad));
}

