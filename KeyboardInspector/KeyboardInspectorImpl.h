#pragma once

#include "KeySequence.h"

#include <windows.h>

#include <thread>
#include <bitset>
#include <unordered_map>

class KeyboardInspectorImpl
{
	using KeySequenceHandler = std::function<bool(const KeySequence&)>;

public:
	static HMODULE instance;

	KeyboardInspectorImpl();
	~KeyboardInspectorImpl();

	void Start();
	void Stop();
	void StopAndWait();

	void InstallKeySequenceHandler(const KeySequence& key, const KeySequenceHandler& handler);

protected:
	void MessageLoop();

	static LRESULT CALLBACK LowLevelKeyboardProc(int code, WPARAM wParam, LPARAM lParam);
	
private:
	std::thread msg_loop_thread_;
	static KeySequence current_key_seq_;
	static std::unordered_map<KeySequence, KeySequenceHandler> key_seq_to_handler_;
};



