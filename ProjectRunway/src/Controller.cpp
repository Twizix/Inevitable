#include "Controller.h"


int Gamepad::GetPort()
{
	return cId + 1;
}
Gamepad::Gamepad() { cId = -1; }
XINPUT_GAMEPAD *Gamepad::GetState()
{
	return &state.Gamepad;
}



	bool Gamepad::CheckConnection()
	{



		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		if (XInputGetState(cId, &state) == ERROR_SUCCESS) {
			return true;

		}
		return false;





	}







// Returns false if the controller has been disconnected
bool Gamepad::Refresh()
{
	
	

	if (CheckConnection())
	{
	//	std::cout << (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) << std::endl;
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		if (XInputGetState(cId, &state) != ERROR_SUCCESS)
		{

			return false;
		}
		short sX = state.Gamepad.sThumbLX;
		short sY = state.Gamepad.sThumbLY;

		// X axis is outside of deadzone
		if (sX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
			sX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
			leftStickX = sX;
		}
		else {
			leftStickX = 0.0f;
		}
		// Y axis is outside of deadzone
		if (sY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
			sY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
			leftStickY = sY;
		}
		else {
			leftStickY = 0.0f;
		}
		dUp= IsPressed(XINPUT_GAMEPAD_DPAD_UP);
		dDown = IsPressed(XINPUT_GAMEPAD_DPAD_DOWN);
		aButton = IsPressed(XINPUT_GAMEPAD_A);
		bButton = IsPressed(XINPUT_GAMEPAD_B);
		sButton = IsPressed(XINPUT_GAMEPAD_START);
		r1Button = IsPressed(XINPUT_GAMEPAD_RIGHT_SHOULDER);
		return true;
	}

	return false;
}
void Gamepad::setPort(int f) {
	cId = f - 1;
	
}
bool Gamepad::IsPressed(WORD button)
{
	return (state.Gamepad.wButtons & button) != 0;
	
}
