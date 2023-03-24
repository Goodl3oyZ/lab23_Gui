#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND,UINT , WPARAM ,LPARAM);
/* This is where all the input to the window goes to */
char Text1[20];
char Text2[20];
HWND Text_Field,Button,Text_Box1,Text_Box2;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
			case WM_CREATE: 
				Text_Field = CreateWindow("STATIC","   Please input two numbers",WS_VISIBLE|WS_CHILD|WS_BORDER,25,15,200,25,hwnd,NULL,NULL,NULL);
				Text_Box1 = CreateWindow("EDIT"," ",WS_BORDER|WS_CHILD|WS_VISIBLE,60,70,50,25,hwnd,NULL,NULL,NULL);
				Text_Box2 = CreateWindow("EDIT"," ",WS_BORDER|WS_CHILD|WS_VISIBLE,60,105,50,25,hwnd,NULL,NULL,NULL);
				Button = CreateWindow("BUTTON","+",WS_VISIBLE|WS_CHILD|WS_BORDER,150,55,35,25,hwnd,(HMENU) 1,NULL,NULL);
				Button = CreateWindow("BUTTON","-",WS_VISIBLE|WS_CHILD|WS_BORDER,150,80,35,25,hwnd,(HMENU) 2,NULL,NULL);
				Button = CreateWindow("BUTTON","*",WS_VISIBLE|WS_CHILD|WS_BORDER,150,105,35,25,hwnd,(HMENU) 3,NULL,NULL);
				Button = CreateWindow("BUTTON","/",WS_VISIBLE|WS_CHILD|WS_BORDER,150,130,35,25,hwnd,(HMENU) 4,NULL,NULL);
				break;
			case WM_COMMAND: // processing calculatorin in math
				if(LOWORD(wParam)!=0){
					int gwtstat1 =0,gwtstat2 =0;
					gwtstat1 = GetWindowText(Text_Box1,&Text1[0],20);
					gwtstat2 = GetWindowText(Text_Box2,&Text2[0],20);
				}
				if(LOWORD(wParam)==1){
					float re=atof(Text1)+atof(Text2);
					char t[100];
					sprintf(t, "%f", re);
					:: MessageBox(hwnd,t,"Result",MB_OK);
				}
				if(LOWORD(wParam)==2){
					float re=atof(Text1)-atof(Text2);
					char t[100];
					sprintf(t, "%f", re);
					:: MessageBox(hwnd,t,"Result",MB_OK);
				}
				if(LOWORD(wParam)==3){
					float re=atof(Text1)*atof(Text2);
					char t[100];
					sprintf(t, "%f", re);
					:: MessageBox(hwnd,t,"Result",MB_OK);
				}
				if(LOWORD(wParam)==4){
					float re=atof(Text1)/atof(Text2);
					char t[100];
					sprintf(t, "%f", re);
					:: MessageBox(hwnd,t,"Result",MB_OK);
				}
				break;			
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			default:
				return DefWindowProc (hwnd,Message,wParam,lParam);
		}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(0xE);
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"WindowClass",
		"My Calculator",//On top name program
		WS_VISIBLE|WS_SYSMENU, // fixed size cant up/down size
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width fixed*/ 
		200, /* height fixed*/
		NULL, NULL, hInstance, NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;

}