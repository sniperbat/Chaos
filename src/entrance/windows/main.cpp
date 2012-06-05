//#ifdef WIN32 
//#include <WTypes.h> // Include this first on Win (bug #35683) 
//#endif
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "Chaos.h"
//--------------------------------------------------------------------------------------------------
HWND gWinHandle;
HINSTANCE gInstance;
Chaos::ChsEngine * engine;

LRESULT handleMsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ){
  short mouseX = LOWORD( lParam );
  short mouseY = HIWORD( lParam );
  Chaos::ChsTouch chsTouch;
  chsTouch.numberOfTouches = 1;
  chsTouch.location.x = static_cast<float>( mouseX );
  chsTouch.location.y = static_cast<float>( mouseY );
	switch(uMsg){
  case WM_LBUTTONDBLCLK:
    return 0;
  case WM_LBUTTONDOWN:
    chsTouch.state = Chaos::CHS_TOUCH_STATE_BEGAN;
    Chaos::ChsTouchEmitter::sharedInstance()->handleTouches( Chaos::CHS_TOUCH_TYPE_BEGAN, chsTouch );
    return 0;
  case WM_MOUSEMOVE:
    chsTouch.state = Chaos::CHS_TOUCH_STATE_CHANGED;
    Chaos::ChsTouchEmitter::sharedInstance()->handleTouches( Chaos::CHS_TOUCH_TYPE_CHANGED, chsTouch );
    return 0;
  case WM_LBUTTONUP:
    chsTouch.state = Chaos::CHS_TOUCH_STATE_ENDED;
    Chaos::ChsTouchEmitter::sharedInstance()->handleTouches( Chaos::CHS_TOUCH_TYPE_ENDED, chsTouch );
    return 0;
  case WM_MOUSEWHEEL:{
    Chaos::ChsPinchTouch chsTouch;
    chsTouch.location.x = static_cast<float>( mouseX );
    chsTouch.location.y = static_cast<float>( mouseY );
    chsTouch.numberOfTouches = 1;
    chsTouch.state = Chaos::CHS_TOUCH_STATE_CHANGED;
    short wheelDelta = HIWORD( wParam );
    chsTouch.scale = wheelDelta / 120.f;
    Chaos::ChsTouchEmitter::sharedInstance()->handleTouches( Chaos::CHS_TOUCH_TYPE_PINCH, chsTouch );
                     }
    return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_MOVE:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR InCmdLine, INT nCmdShow ){
  static_cast<void>( hPrevInstance );
  static_cast<void>( InCmdLine );
  static_cast<void>( nCmdShow );
	gInstance = hInstance;
	// Register the window class.
	WNDCLASSEX wc = {
		sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, (WNDPROC)handleMsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, "chaos", "chaos", NULL};
	RegisterClassEx(&wc);
	RECT rc;
	SetRect( &rc, 0, 0, 1024, 768 );
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);
	// Create the application's window.
	gWinHandle= ::CreateWindow( "chaos", "chaos", WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS , 0, 0,
		(rc.right-rc.left), (rc.bottom-rc.top),	NULL, NULL, wc.hInstance, NULL);
	if(gWinHandle== NULL){
		PostQuitMessage(0);
	}
	ShowWindow(gWinHandle, SW_SHOWDEFAULT);
	UpdateWindow(gWinHandle);
	SetForegroundWindow(gWinHandle);
	SetFocus(gWinHandle);
  Chaos::ChsRenderSystemWindowsSetHandle( gWinHandle );
  engine = Chaos::ChsEngine::sharedInstance();
  engine->start();
  MSG msg;
  ZeroMemory(&msg, sizeof(msg));
  while(msg.message != WM_QUIT){
	  if(PeekMessage(&msg, NULL, 0, 0 ,PM_REMOVE)){
		  TranslateMessage(&msg);
		  DispatchMessage(&msg);
	  }
	  else{
      engine->run();
	  }
  }
  engine->shutdown();
}
//----------------------------------------------------------------------------------------------------------
#define _CONSOLEWIN
#ifdef _CONSOLEWIN
//Set subsystem to console
#pragma comment ( linker, "/subsystem:console" )
//----------------------------------------------------------------------------------------------------------
BOOL WINAPI ConsoleWinHandlerRoutine( DWORD dwCtrlType ){
   // Signal type
   switch( dwCtrlType ){
   case CTRL_C_EVENT:
   case CTRL_BREAK_EVENT:
   case CTRL_CLOSE_EVENT:
   case CTRL_LOGOFF_EVENT:
   case CTRL_SHUTDOWN_EVENT:
      // You can stop here gracefully:
      //
      // AfxGetMainWnd()->SendMessage( WM_CLOSE, 0, 0 );
      // WaitForSingleObject( AfxGetThread(), INFINITE );
      //
      ExitProcess(0);
      break;
   }
   return TRUE;
}

//----------------------------------------------------------------------------------------------------------
// Console main function
int _tmain( DWORD, TCHAR**, TCHAR** ){
#define SPACECHAR   _T(' ')
#define DQUOTECHAR  _T('\"')
   // Set the new handler
   SetConsoleCtrlHandler( ConsoleWinHandlerRoutine, TRUE );
   // Get command lin
	LPTSTR lpszCommandLine = ::GetCommandLine();
	if(lpszCommandLine == NULL)
		return -1;
	// Skip past program name (first token in command line).
	// Check for and handle quoted program name.
	if(*lpszCommandLine == DQUOTECHAR){
		// Scan, and skip over, subsequent characters until
		// another double-quote or a null is encountered.
		do{
			lpszCommandLine = ::CharNext(lpszCommandLine);
		}
		while((*lpszCommandLine != DQUOTECHAR) && (*lpszCommandLine != _T('\0')));

		// If we stopped on a double-quote (usual case), skip over it.
		if(*lpszCommandLine == DQUOTECHAR)
			lpszCommandLine = ::CharNext(lpszCommandLine);
	}
	else{
		while(*lpszCommandLine > SPACECHAR)
			lpszCommandLine = ::CharNext(lpszCommandLine);
	}
	// Skip past any white space preceeding the second token.
	while(*lpszCommandLine && (*lpszCommandLine <= SPACECHAR))
		lpszCommandLine = ::CharNext(lpszCommandLine);
	STARTUPINFO StartupInfo;
	StartupInfo.dwFlags = 0;
	::GetStartupInfo(&StartupInfo);
	return _tWinMain(::GetModuleHandle(NULL), NULL, lpszCommandLine,
		SW_SHOW/*(StartupInfo.dwFlags & STARTF_USESHOWWINDOW) ?
		StartupInfo.wShowWindow : SW_HIDE*/);
}
//----------------------------------------------------------------------------------------------------------
#endif // _CONSOLEWIN
//--------------------------------------------------------------------------------------------------
