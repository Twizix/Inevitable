#pragma once
#pragma once
#include "GLMODEL.h"

class KeyFrames {
public:
	KeyFrames();
	~KeyFrames();
	void loadFrames(std::string charName, int n);
	GLMODEL getFrame(int i);
	int getAnimSize();
	std::vector<GLMODEL> getKeys();

private:
	std::vector<GLMODEL> keys;


	int amountOfFrames;


};

class Animation {
public:
	Animation();
	~Animation();
	void setAnimation(KeyFrames f, float s);
	void tick();
	GLMODEL getCurrentFrame(int frame, float tp);
	GLMODEL getModel();
	GLMODEL getStaticModel(int i);
	void changeSpeed(float s);
	void reset();

private:
	KeyFrames frames;
	std::vector<UV> tex;
	std::vector<GLMODEL> keys;
	std::vector<GLMODEL> skeys;
	float maxframe;
	float t;
	float speed;
	float bspeed;
	float step;
	float normSize;
	float pointSize;
	float uvSize;
	int animSize;

};
