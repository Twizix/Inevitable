#pragma once
#include "object.h"
const int   INTERFACE_UPDATETIME = 50;      // 50ms update for interface
const float DISTANCEFACTOR = 1.0f;          // Units per meter.  I.e feet would = 3.28.  centimeters would = 100.
enum LoopStyle{
NEVER,ONCE,LOOP,NTIMES
};

class Noise {
public:
	Noise() {}
	void set(char *s,LoopStyle l,int n,bool paused);
	void Create(FMOD::System **cpu, FMOD_RESULT &result);
	FMOD::Sound   *&getSound();
	FMOD::Channel   *&getChannel();
	FMOD_VECTOR &getPos();
	FMOD_VECTOR &getVel();
	void tick();
	bool flag();
	void pause();
	void play();
	void reset();
	int getLoops();
	int getNLoops();
	void nextLoop();
	LoopStyle getStyle();
	void setPos(glm::vec3 v);
	 const char *getFile();
private:	
	FMOD::Sound     *sound1;
	FMOD::Channel   *channel1=0;
	char *fileName;
	FMOD_VECTOR pos = { 0.0f, 0.0f, 0.0f };
	FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };
	FMOD_VECTOR lastpos = { 0.0f, 0.0f, 0.0f };
	bool listenFlag;
	bool loopFlag;
	int loopTimes;
	LoopStyle loops;
	int maxLoops=0;
	
};
void initNoise(Noise *&n);
class soundHandle {
public:
	soundHandle();
	void init();
	void end();
	void addSound(Noise *&n);
	void tick();
	void setPos(glm::vec3 v);
	FMOD::System *&getSystem();
	FMOD_RESULT &getResult();
private:
	Noise whiteNoise;
	std::vector<Noise> sounds;
	FMOD::System    *cpu;
	FMOD_VECTOR      listenerpos = { 0.0f, 0.0f, 0.0f };
	FMOD_VECTOR forward = { 0.0f, 0.0f, 1.0f };
	FMOD_VECTOR up = { 0.0f, 1.0f, 0.0f };
	 FMOD_VECTOR lastpos = { 0.0f, 0.0f, 0.0f };
	 float t = 0;
	FMOD_RESULT      result;
	unsigned int     version;
	void            *extradriverdata = 0;
};

