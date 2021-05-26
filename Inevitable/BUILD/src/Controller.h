#pragma once
#include "Animation.h"



class Gamepad
{
private:
	int cId;
	XINPUT_STATE state;
	float deadzoneX;
	float deadzoneY;

public:
	Gamepad();
	Gamepad(float dzX, float dzY) : deadzoneX(dzX), deadzoneY(dzY) {}
	bool isConnected;
	void setPort(int f);
	float leftStickX;
	float leftStickY;
	float rightStickX;
	float rightStickY;
	float leftTrigger;
	float rightTrigger;
	bool aButton;
	bool r1Button;
	bool bButton;
	bool sButton;
	bool dUp;
	bool dDown;
	int  GetPort();
	XINPUT_GAMEPAD *GetState();
	bool CheckConnection();
	bool Refresh();
	bool IsPressed(WORD);
};
