// GDK++.cpp : Defines the entry point for the application.
//
#include "GDK++.h"

#define MAX_LOADSTRING 100
#define sleep(X) {boost::this_thread::sleep(boost::posix_time::millisec(X));}
// Global Variables:

#ifdef USE_WINAPI
HINSTANCE hInst;                                // current instance
HWND hWnd;										// Main window
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
RenderWindow* renderwin;
void				InitRenderWindow();

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    PluginMgr(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GDK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GDK));

    MSG msg;
	
	
    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

void InitRenderWindow() 
{
	renderwin = new RenderWindow(_RendererType, CW_USEDEFAULT, CW_USEDEFAULT, 480, 640, hInst, hWnd, currentScene);
}


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GDK));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GDK);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	// Create a window description
	WNDCLASSEX renderWC;

	renderWC.cbSize = sizeof(WNDCLASSEX);
	renderWC.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_NOCLOSE ;
	renderWC.lpfnWndProc = WndProc;						// Register the callback function for the window procedure
	renderWC.cbClsExtra = 0;
	renderWC.cbWndExtra = 0;
	renderWC.hInstance = hInstance;
	renderWC.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GDK));
	renderWC.hCursor = LoadCursor(nullptr, IDC_ARROW);
	renderWC.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));
	renderWC.lpszMenuName = NULL;
	renderWC.lpszClassName = TEXT("GDKRenderWindow");
	renderWC.hIconSm = NULL;

	if (!RegisterClassEx(&renderWC))
	{
		MessageBox(0, TEXT("Failed to register window class."), NULL, 0);
		return RegisterClassExW(&wcex);
	}

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case ID_WINDOW_PLUGINMANAGER:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_PLUGIN_MANAGER), hWnd, PluginMgr);
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
		if(renderwin && renderwin->renderWindowHandle && hWnd == renderwin->renderWindowHandle) 
		{
			renderwin->renderer->Render();
		}
		else 
		{
			PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
		}
           
        }
        break;
    case WM_DESTROY:
		UnloadModules();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// Message handler for about box.
INT_PTR CALLBACK PluginMgr(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
#endif
// Forward declarations of functions included in this code module:


void				Load();
void				EngineTests();
void				LoadPreferences();
void				InitEngine();
void				InitUI();
void				Unload();

void Load()
{
	printf(">> Starting GDK++...\r\n");
	LoadPreferences();
	InitModules(EditorInstance::GetSingleton());
	sleep(500);
	InitEngine();
	InitUI();
	//EngineTests();
}

void Unload() 
{
	sleep(1000);
	UnloadModules();
}

void InitUI()
{
	InitEUI("GDK++", 1000, 650);
}

void LoadPreferences()
{

}

void InitEngine()
{
	if (EditorInstance::GetSingleton()->currentScene->hierarchy.empty())
	{
		GameObject* edcam = new GameObject("Editor Camera");
		Camera* edcamc = new Camera();
		edcamc->Init(edcam);
		edcam->layer = GDK_LAYER_EDITOR;
		EditorInstance::GetSingleton()->currentScene->hierarchy.push_front(edcam);
		//edcamc->renderer->currentScene = EditorInstance::GetSingleton()->currentScene;
	}
}


void EngineTests()
{
	Vector3 v(1, 2, 3), v1(3, 2, 1);
	std::stringstream wss;
	wss << "V1: " << v.toStringA() << ", V2: " << v1.toStringA() << "\n";
	auto v2 = v + v1;
	v += v1;
	wss << "V1: " << v.toStringA() << ", V2: " << v1.toStringA() << " Result: " << v2.toStringA() << "\n";
	Quaternion q{ 1,1,1,1 }, q1{2,2,2,2};
	q -= q1;
	wss << "Quaternion: " << q.toStringA() << ", Quaternion2: " << q1.toStringA() << "\n";
	wss << "Day of the year: " << Time::CalcDayOfYear(30, 03, 2018) << "\n";
	wss << "Round Up Day Of Year: " << Time::CalcWeekOfYear(Time::CalcDayOfYear(30, 03, 2018)) << "\n";
	OutputDebugStringA(wss.str().c_str());
}

int main()
{
	atexit(Unload);
	Load();
	return 0;
}

