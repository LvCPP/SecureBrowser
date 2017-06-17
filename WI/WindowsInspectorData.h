#pragma once
#include <unordered_map>
#include <windows.h>
#include <string.h>

namespace SBWindowsInspector
{

class WindowsData
{
public:	
	WindowsData(HWND hwnd);
	~WindowsData() = default;

	void SetHwnd(HWND hwnd);
	void SetTitle(char* title);
	void SetProcessName(char* process_name);
	void SetProcessId(DWORD processid);

	UINT GetEventCode() const;
	char* GetTitle() const;
	char* GetProcessName() const;
	DWORD GetProcessId() const;
	std::string GetText() const;

private:
	HWND hwnd_;
	char* wnd_title_;
	char* process_name_;
	DWORD processid_;
	UINT event_code_;

};

const static std::unordered_map <UINT, std::string> Events =
{
	{EVENT_MIN, "Event_Min"},
	{EVENT_OBJECT_ACCELERATORCHANGE, "Event_Acelleratorchange"},
	{EVENT_OBJECT_CLOAKED, "Event_Cloaked"},
	{EVENT_OBJECT_CONTENTSCROLLED, "Event_Min"},
	{EVENT_OBJECT_CREATE, "Event_Create"},
	{EVENT_OBJECT_DEFACTIONCHANGE, "Event_Defactionchange"},
	{EVENT_OBJECT_DESCRIPTIONCHANGE, "Event_Desctiptionchange"},
	{EVENT_OBJECT_DESTROY, "Event_Destroy"},
	{EVENT_OBJECT_DRAGSTART, "Event_Dragstart"},
	{EVENT_OBJECT_DRAGCANCEL, "Event_Dragcancel"},
	{EVENT_OBJECT_DRAGCOMPLETE, "Event_Dragcomplete"},
	{EVENT_OBJECT_DRAGENTER, "Event_Dragenter"},
	{EVENT_OBJECT_DRAGLEAVE, "Event_Dragleave"},
	{EVENT_OBJECT_DRAGDROPPED, "Event_Dragdropped"},
	{EVENT_OBJECT_END, "Event_End"},
	{EVENT_OBJECT_FOCUS, "Event_Focus"},
	{EVENT_OBJECT_HELPCHANGE, "Event_Helpchange"},
	{EVENT_OBJECT_HIDE, "Event_Hide"},
	{EVENT_OBJECT_HOSTEDOBJECTSINVALIDATED, "Event_Hostedobjectsinvalidated"},
	{EVENT_OBJECT_IME_HIDE, "Event_Ime_Hide"},
	{EVENT_OBJECT_IME_CHANGE, "Event_Ime_Change"},
	{EVENT_OBJECT_INVOKED, "Event_Invoked"},
	{EVENT_OBJECT_LIVEREGIONCHANGED, "Event_Liveregionchanged"},
	{EVENT_OBJECT_LOCATIONCHANGE, "Event_Locationchange"},
	{EVENT_OBJECT_NAMECHANGE, "Event_Namechange"},
	{EVENT_OBJECT_PARENTCHANGE, "Event_Parentchange"},
	{EVENT_OBJECT_REORDER, "Event_Reorder"},
	{EVENT_OBJECT_SELECTION, "Event_Selection"},
	{EVENT_OBJECT_SELECTIONADD, "Event_Selectionadd"},
	{EVENT_OBJECT_SELECTIONREMOVE, "Event_Selectionremove"},
	{EVENT_OBJECT_SELECTIONWITHIN, "Event_Selectionwithin"},
	{EVENT_OBJECT_SHOW, "Event_Show"},
	{EVENT_OBJECT_STATECHANGE, "Event_Statechange"} ,
	{EVENT_OBJECT_TEXTEDIT_CONVERSIONTARGETCHANGED, "Event_Conversiontargetchanged"},
	{EVENT_OBJECT_TEXTSELECTIONCHANGED, "Event_Textselectionchanged"},
	{EVENT_OBJECT_UNCLOAKED, "Event_Uncloaked"},
	{EVENT_OBJECT_VALUECHANGE, "Event_Valuechange"},
	{EVENT_SYSTEM_ALERT, "Event_Alert"},
	{EVENT_SYSTEM_ARRANGMENTPREVIEW, "Event_Arrangmentpreview"},
	{EVENT_SYSTEM_CAPTUREEND, "Event_Capture_End"},
	{EVENT_SYSTEM_CAPTURESTART, "Event_Capture_Start"},
	{EVENT_SYSTEM_CONTEXTHELPEND, "Event_Contexthelp_End"},
	{EVENT_SYSTEM_CONTEXTHELPSTART, "Event_Contexthelp_Start"},
	{EVENT_SYSTEM_DESKTOPSWITCH, "Event_Desktop_Switch"},
	{EVENT_SYSTEM_DIALOGEND, "Event_Dialog_End"},
	{EVENT_SYSTEM_DIALOGSTART, "Event_Dialog_Start"},
	{EVENT_SYSTEM_DRAGDROPEND, "Event_Drag_End"},
	{EVENT_SYSTEM_DRAGDROPSTART, "Event_Drag_Start"},
	{EVENT_SYSTEM_END, "Event_End"} ,
	{EVENT_SYSTEM_FOREGROUND, "Event_Foreground"},
	{EVENT_SYSTEM_MENUPOPUPEND, "Event_Menupop_End"},
	{EVENT_SYSTEM_MENUEND, "Event_Menu_End"},
	{EVENT_SYSTEM_MENUSTART, "Event_Menu_Start"},
	{EVENT_SYSTEM_MINIMIZEEND, "Event_Minimize_End"},
	{EVENT_SYSTEM_MINIMIZESTART, "Event_Minimize_Start"},
	{EVENT_SYSTEM_MOVESIZEEND, "Event_Movesize_End"},
	{EVENT_SYSTEM_MOVESIZESTART, "Event_Movesize_Start"},
	{EVENT_SYSTEM_SCROLLINGEND, "Event_Scrolling_End"},
	{EVENT_SYSTEM_SCROLLINGSTART, "Event_Scrolling_Start"},
	{EVENT_SYSTEM_SOUND, "Event_Sound"},
	{EVENT_SYSTEM_SWITCHEND, "Event_Switch_End"},
	{EVENT_SYSTEM_SWITCHSTART, "Event_Switch_Start"},
	{EVENT_MAX, "Event_Max"}

};

} // namespace SBWindowsInspector
