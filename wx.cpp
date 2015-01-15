#include "main.h"

#include <iostream>

#include <Common/FileUtil.h>
#include <Common/IniFile.h>
#include <DolphinWX/WxUtils.h>
#include <polarssl/md5.h>

#include <wx/app.h>
#include <wx/cmdline.h>
#include <wx/artprov.h>
#include <wx/aui/aui.h>
#include <wx/filename.h>
#include <wx/textfile.h>
#include <wx/wx.h>

using namespace std;

void main_wx();

enum
{
	IDM_EDIT_PERSPECTIVES
};




// app

class MyApp : public wxApp {
//class MyApp : public wxAppConsole {
public:
    virtual bool OnInit();
	bool Initialize_(int& c, wxChar **v);
};

//DECLARE_APP(MyApp);
IMPLEMENT_APP(MyApp)
//IMPLEMENT_APP_CONSOLE(MyApp)
//wxIMPLEMENT_APP_NO_MAIN(MyApp);




// frame

class CFrame : public wxFrame
{
public:
    CFrame(wxWindow *parent,
            wxWindowID id,
            const wxString& title,
            const wxPoint& pos,
            const wxSize& size,
            long style,
            const wxString& name);

	 void CFrame::OnDropDownSettingsToolbar(wxAuiToolBarEvent& event);

private:
	enum {
		ID_MENU

		, IDM_PERSPECTIVES_ADD_PANE
		, IDM_TAB_SPLIT
		, IDM_NO_DOCKING
	};

	DECLARE_EVENT_TABLE();

	wxAuiManager m_mgr;
};

BEGIN_EVENT_TABLE(CFrame, wxFrame)
EVT_AUITOOLBAR_TOOL_DROPDOWN(IDM_EDIT_PERSPECTIVES, CFrame::OnDropDownSettingsToolbar)
END_EVENT_TABLE()


void CFrame::OnDropDownSettingsToolbar(wxAuiToolBarEvent& event)
{
	//event.Skip();

	if (event.IsDropDownClicked())
	{
		wxAuiToolBar* Tb = static_cast<wxAuiToolBar*>(event.GetEventObject());
		Tb->SetToolSticky(event.GetId(), true);

		// Create the popup menu
		//wxMenu* menuPopup = new wxMenu;
		wxMenu menuPopup;

		wxMenuItem* Item =  new wxMenuItem(&menuPopup, IDM_PERSPECTIVES_ADD_PANE, _("Add new pane"));
		menuPopup.Append(Item);
		menuPopup.Append(new wxMenuItem(&menuPopup));
		//Item = new wxMenuItem(&menuPopup, IDM_TAB_SPLIT, _("Tab split"), wxT(""), wxITEM_CHECK);
		//menuPopup.Append(Item);
		//Item->Check(true);
		//Item = new wxMenuItem(&menuPopup, IDM_NO_DOCKING, _("No docking"), wxT(""), wxITEM_CHECK);
		//menuPopup.Append(Item);
		//Item->Check(true);

		// Line up our menu with the button
		wxRect rect = Tb->GetToolRect(event.GetId());
		wxPoint Pt = Tb->ClientToScreen(rect.GetBottomLeft());
		Pt = ScreenToClient(Pt);

		// Show
		PopupMenu(&menuPopup, Pt);

		// Make the button un-stuck again
		//if (true)
		//{
			Tb->SetToolSticky(event.GetId(), false);
		//}
	}
}





//bitmap

//wxDC *dc;

#define VIS_BITMAP_SIZE 256

#define VIS_NORMALIZE(a) ((a / 2.0) + 0.5)
#define VIS_COORD(a) (a + VIS_BITMAP_SIZE / 2)

#define COORD_VIS_SIZE 2

wxBitmap bitmap(VIS_BITMAP_SIZE, VIS_BITMAP_SIZE);

static void DrawCenteredRectangle(wxDC &dc, int x, int y, int w, int h)
{
	x -= w / 2;
	y -= h / 2;
	dc.DrawRectangle(x, y, w, h);
}

void DrawCoordinate(wxPen p, wxBrush b, int x, int y)
{
	//int xc = VIS_COORD(x);
	//int yc = VIS_COORD(y);
	//DrawCenteredRectangle(dc, xc, yc, COORD_VIS_SIZE, COORD_VIS_SIZE);

	wxMemoryDC dc;
	dc.SelectObject(bitmap);
	dc.SetPen(p);
	dc.SetBrush(b);
	//dc.DrawPoint(VIS_COORD(x), VIS_COORD(y));
	DrawCenteredRectangle(dc, VIS_COORD(x), VIS_COORD(y), COORD_VIS_SIZE, COORD_VIS_SIZE);
}


CFrame::CFrame(wxWindow *parent,
            wxWindowID id,
            const wxString& title,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxDEFAULT_FRAME_STYLE,
            const wxString& name = wxFrameNameStr)
       : wxFrame(parent, id, title, pos, size, style, name)
{
	//wxPanel *m_Panel = new wxPanel(m_Frame, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED);
	//wxBoxSizer *m_Sizer = new wxBoxSizer(wxHORIZONTAL);

	// m_Frame->SetAutoLayout(true);
	//m_Frame->SetSizer(m_Sizer);

	//m_Panel->SetSizer(m_Sizer);

	//m_Sizer->Fit(m_Frame);
	// m_Sizer->SetSizeHints(m_Frame);


	//aui

	/*
	m_mgr.SetManagedWindow(this);

	// toolbar
    wxAuiToolBar* tb1 = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_OVERFLOW);
	tb1->AddTool(ID_MENU, wxT("Test"), wxArtProvider::GetBitmap(wxART_ERROR));
	tb1->SetToolDropDown(ID_MENU, true);
	tb1->Realize();

    m_mgr.AddPane(tb1, wxAuiPaneInfo().
                  Name(wxT("tb1")).Caption(wxT("Big Toolbar")).
                  ToolbarPane().Top());
	*/


	//sizer
	wxBoxSizer *m_Sizer = new wxBoxSizer(wxHORIZONTAL);
	SetSizer(m_Sizer);

	//wxMemoryDC *pdc;
	//pdc = new wxMemoryDC(bitmap);

	wxMemoryDC dc;
	//wxDC &dc = (wxDC&) pdc;

	dc.SelectObject(bitmap);
	//dc.SetPen(*wxRED_PEN);
	dc.SetBrush(*wxLIGHT_GREY_BRUSH);
	//dc.Clear();
	dc.FloodFill(0, 0, wxColour());

	//dc.SetBrush(*wxRED_BRUSH);
	//DrawCoordinate(dc, 10, 10);
	//dc.DrawRectangle(0, 0, 10, 10);
	//dc.DrawPoint(0, 0);
	DrawCoordinate(*wxRED_PEN, *wxRED_BRUSH, 0, 0);

	test_gcpad();

	wxStaticBitmap *m_Bitmap = new wxStaticBitmap(this, wxID_ANY, bitmap);
	//wxStaticBitmap *m_Bitmap = new wxStaticBitmap(this, wxID_ANY, wxArtProvider::GetBitmap(wxART_ERROR));
	m_Sizer->Add(m_Bitmap, 1, wxEXPAND);
	m_Sizer->Fit(this);

	Center();
    Show(true);
}





// app

bool MyApp::OnInit() {
	//wxMessageBox("OnInit");
	//printf("%d\n", wxTheApp->argc);
	//printf("%s\n", wxTheApp->argv[0]);

	//wxImage::AddHandler(new wxPNGHandler);

    CFrame *m_Frame = new CFrame(NULL, wxID_ANY, _T("wxApp"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE);
	SetTopWindow(m_Frame);

	return true;
}


bool ReadFile(string fname, u8 *data)
{
	File::IOFile pFile(fname.c_str(), "rb");
	const size_t size = File::GetSize(fname);

	printf("\"%s\" %u\n", fname.c_str(), size);

	data = (u8*) malloc(size);
	if (pFile)
	{
		pFile.ReadArray(data, size);
		pFile.Close();

		// byteswap
		//for (int i = 0; i < size_in_words; i++)
			//data[i] = Common::swap16(data[i]);

		//printf("%s\n", ArrayToString(data, size).c_str());

		return true;
	}

	printf("Failed to load \t%s\n", fname);

	return false;
}


void test_artmoney() {
	string name = "test.txt";
	//string name = wxTheApp->argv[0];

	wxFileName wxName(name);
	wprintf(L"%s %s %s\n"
		, wxName.GetName().wc_str()
		, wxName.GetFullName().wc_str()
		, wxName.GetFullPath().wc_str());

	u8 *data = 0;
	ReadFile(name, data);

	const size_t size = File::GetSize(name.c_str());
	u8 md5_hash[16];
	wxString line;

	//md5((u8*)&data, size, md5_hash);
	md5_file((char*)name.c_str(), md5_hash);

	printf("%s\n", ArrayToString(md5_hash, 16, 16, false).c_str());

	std::ofstream out;
	OpenFStream(out, name, std::ios::out);

	if (out.fail())
		return;

	std::string s = "";
	out << s << std::endl;

	out.close();
	return;

	//wxTextFile file("test.emul");
	//file.Create();

	//file.AddLine( wxT("Hello world") );
	//file.AddLine(ArrayToString(md5_hash, 16, 16, false));

	//file.Write();
	//file.Close();
}


// pointer

void test_pointer_dc(wxMemoryDC *dc) {

}

void test_pointer() {
	wxMemoryDC dc;
	test_pointer_dc(&dc);
}


bool wx_init() {
    wxApp::CheckBuildOptions(WX_BUILD_OPTIONS_SIGNATURE, "program");

    wxInitializer initializer;
    if (!initializer) {
        fprintf(stderr, "Failed to initialize the wxWidgets library, aborting.");
        return false;
    }

	return true;
}


void test_wx(int argc, char **argv) {
//void test_wx(int argc, wchar_t **argv) {

	//if (!wx_init())
		//return;

	MyApp *app = new MyApp();
	app->Initialize(argc, (wxChar**)argv);
	app->OnInit();

	//printf("%s", argv[0]);

	//test_artmoney();
	//test_pointer();
}