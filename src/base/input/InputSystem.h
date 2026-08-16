#pragma once

#include <unordered_map>

namespace VS
{
	class InputSystem
	{
	public:
		InputSystem();
		
		void Update();
		bool IsQuit() const { return is_quit_; }

		bool GetKey(const char* key_name);
	private:
		void RegisterKeys();

		const bool* key_state_;
		std::unordered_map<const char*, int> key_map_;
		bool is_quit_;
	};
}