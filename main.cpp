#include "main.h"

u8 DSPHost_ReadHostMemory(u32 addr) { return 0; }
void DSPHost_WriteHostMemory(u8 value, u32 addr) {}
bool DSPHost_OnThread() { return false; }
bool DSPHost_Wii() { return false; }
void DSPHost_CodeLoaded(const u8 *ptr, int size) {}
void DSPHost_InterruptRequest() {}
void DSPHost_UpdateDebugger() {}

void Host_NotifyMapLoaded() {}
void Host_RefreshDSPDebuggerWindow() {}
void Host_ShowJitResults(unsigned int address){}
bool Host_IsCLI() { return false; }
void Host_Message(int Id) {}
void* Host_GetRenderHandle() { return 0; }
void* Host_GetInstance() { return 0; }
void Host_UpdateTitle(const char* title){};
void Host_UpdateLogDisplay(){}
void Host_UpdateDisasmDialog(){}
void Host_UpdateMainFrame() {}
void Host_UpdateBreakPointView(){}
bool Host_GetKeyState(int keycode) { return false; }
void Host_GetRenderWindowSize(int& x, int& y, int& width, int& height) {}
void Host_RequestRenderWindowSize(int width, int height) {}
void Host_SetStartupDebuggingParameters() {}
bool Host_RendererHasFocus() { return false; }
void Host_ConnectWiimote(int wm_idx, bool connect) {}
void Host_SetWaitCursor(bool enable){}
void Host_UpdateStatusBar(const char* _pText, int Filed){}
void Host_SysMessage(const char *fmt, ...) {}
void Host_SetWiiMoteConnectionState(int _State) {}

double Round(double n, double dec)
{
	return floor(n * pow(10, dec) + 0.5) / pow(10, dec);
}

//test_object test_object_;
//test_object *test_object_ = new test_object();

/*
int main(int argc, char **argv) {
//int wmain(int argc, wchar_t **argv) {
	//test_lzop();
	//test_ini();
	//test_wx(argc, argv);
	//test_debug();
	//test_wpad();
	//test_gcpad();
	//test_thread();

	cin.get();

	return 0;
}
*/
