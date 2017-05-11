#pragma once

#include "KeySequence.h"

#include <thread>

//namespace SBKeyboardInspector
//{

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
	static bool ChangeIgnoreFlagIfNecessary(const KeySequence& ks, std::unordered_map<KeySequence
		, KeySequenceHandler>& key_seq_to_handler);
	
protected:
	void MessageLoop();
	static LRESULT CALLBACK LowLevelKeyboardProc(int code, WPARAM wParam, LPARAM lParam);
	
private:
	std::thread msg_loop_thread_;
	static bool ignore_key_;
	static KeySequence current_key_seq_;
	static std::unordered_map<KeySequence, KeySequenceHandler> key_seq_to_handler_;
};

//} // end of namespace