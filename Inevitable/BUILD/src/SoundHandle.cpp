#include "SoundHandle.h"

void initNoise(Noise *&n) {
	n = new Noise();
}
void Noise::tick() {
	
	vel.x = (pos.x - lastpos.x) ;
	vel.y = (pos.y - lastpos.y) ;
	vel.z = (pos.z - lastpos.z);
}

void Noise::set(char *s, LoopStyle l, int n, bool paused) {
	fileName = s;
	loops = l;
	loopTimes = n;
	listenFlag = paused;

	if (loops == NEVER) {
		loopTimes = 0;
	}
	if (loops == ONCE) {
		loopTimes = 1;
	}
	if (loops == LOOP) {
		loopTimes = 0;
	}
	
}
int Noise::getLoops() {
	return maxLoops;
}
int Noise::getNLoops() {
	return loopTimes;
}
void Noise::nextLoop() {
	maxLoops++;
}

void Noise::Create(FMOD::System **cpu, FMOD_RESULT &result) {}
FMOD::Sound   *&Noise::getSound() {
	return sound1;
}
FMOD::Channel   *&Noise::getChannel() {
	return channel1;

}

FMOD_VECTOR &Noise::getPos() { return pos; }
FMOD_VECTOR &Noise::getVel() { return vel; }
bool Noise::flag() { return listenFlag; }

void Noise::play() {
	listenFlag = false;
}

void Noise::pause() {
	listenFlag = true;
}
void Noise::reset() {

}
LoopStyle Noise::getStyle() {
	return loops;
}
void Noise::setPos(glm::vec3 v) {
	pos.x = v.x;
	pos.y = v.y;
	pos.z = v.z;
}
const char *Noise::getFile() {
	return fileName;
}
soundHandle::soundHandle(){
	
}
FMOD::System *&soundHandle::getSystem() {
	return cpu;
}
FMOD_RESULT &soundHandle::getResult() {
	return result;
}
void soundHandle::init() {

	result = FMOD::System_Create(&cpu);


	result = cpu->getVersion(&version);

	result = cpu->init(100, FMOD_INIT_NORMAL, extradriverdata);
	result = cpu->set3DSettings(1.0, DISTANCEFACTOR, 1.0f);
}
void soundHandle::setPos(glm::vec3 v){

	listenerpos.x = v.x;
	listenerpos.y = v.y;
	listenerpos.z = v.z;
}
void soundHandle::addSound(Noise *&n) {
	
	
sounds.push_back(*n);
int index = sounds.size() - 1;
n = &sounds[index];
std::string f = sounds[index].getFile();
//	FMOD::Sound *s= sounds[index].getSound();
	//FMOD::Channel *c = sounds[index].getChannel();
	result = cpu->createSound(f.c_str(), FMOD_3D, 0, &sounds[index].getSound());

	result = sounds[index].getSound()->set3DMinMaxDistance(0.5f * DISTANCEFACTOR, 5000.0f * DISTANCEFACTOR);
	
	if (sounds[index].getStyle() == LOOP) {
		result = sounds[index].getSound()->setMode(FMOD_LOOP_NORMAL);
	}
	if (sounds[index].getStyle() == NEVER || sounds[index].getStyle() == NTIMES || sounds[index].getStyle() == ONCE) {
		result = sounds[index].getSound()->setMode(FMOD_LOOP_OFF);
	}

	result = cpu->playSound(sounds[index].getSound(), 0, true, &sounds[index].getChannel());

	result = sounds[index].getChannel()->set3DAttributes(&sounds[index].getPos(), &sounds[index].getVel());

	result = sounds[index].getChannel()->setPaused(false);
	

}
void soundHandle::tick() {

	for (int i = 0; i < sounds.size(); i++) {
		sounds[i].tick();

		result = sounds[i].getChannel()->set3DAttributes(&sounds[i].getPos(), &sounds[i].getVel());
		bool b=false;
		
		
		sounds[i].getChannel()->isPlaying(&b);
		//std::cout << sounds[i].getPos().x << ", " << sounds[i].getPos().y << ", " << sounds[i].getPos().z << std::endl;
			
				std::cout <<"IsPlaying: "<< b<<std::endl;
				if (!b&& ( sounds[i].getStyle() == NTIMES || sounds[i].getStyle() == ONCE)&& sounds[i].getLoops()<sounds[i].getNLoops()) {
					sounds[i].nextLoop();
					result = cpu->playSound(sounds[i].getSound(), 0, true, &sounds[i].getChannel());-
					sounds[i].getChannel()->setPaused(false);
				}

		
		if (sounds[i].flag()) {
			result = sounds[i].getChannel()->setPaused(true);
		}else if (!sounds[i].flag()) {
			result = sounds[i].getChannel()->setPaused(false);
		}
	}

	FMOD_VECTOR vel;

	//listenerpos.x = players[0].getCoord().x;

	// ********* NOTE ******* READ NEXT COMMENT!!!!!
	// vel = how far we moved last FRAME (m/f), then time compensate it to SECONDS (m/s).
	vel.x = (listenerpos.x - lastpos.x) ;
	vel.y = (listenerpos.y - lastpos.y);
	vel.z = (listenerpos.z - lastpos.z) ;

	// store pos for next time
	lastpos = listenerpos;
	t += (30 * (1.0f / (float)INTERFACE_UPDATETIME));    // t is just a time value .. it increments in 30m/s steps in this example

	result = cpu->set3DListenerAttributes(0, &listenerpos, &vel, &forward, &up);





	result = cpu->update();
}

void soundHandle::end() {
	for (int i = 0; i < sounds.size(); i++) {
		result = sounds[i].getSound()->release();
	}

	result = cpu->close();
	
	result = cpu->release();
	

}