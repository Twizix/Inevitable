#include "object.h"

float anS = 1.0f;

void Character::interCont(float t, float inc) {
	//std::vector<Vertex> temp;
	



}

Character::Character() { 
	
	


}
	

Character::~Character() {}
void Character::tick() { 
	
	chAnim.tick();
	atAnim.tick();
//	playerModel=chAnim.getCurrentFrame(playerModel);

}
void Character::fuckUp(float f) {
//	chAnim.setAnimation(running, 0.05f);
	chAnim.changeSpeed(16.0f*(f/0.5));
}
void Character::fuckDown() {
	//	chAnim.setAnimation(running, 0.05f);
	chAnim.reset();
}
void Character::setCharacter(int cNum) {
	charNum = cNum;
	if (cNum == 1) {
running.loadFrames("BrickRunning", 9);
	}
		
	if (cNum == 2){
	running.loadFrames("L-run", 9);
	attacking.loadFrames("lyn_attack", 8);
	atAnim.setAnimation(attacking, 0.01f);
	atAnim.changeSpeed(32.0f);
	}
		
	if (cNum == 3) {
		running.loadFrames("OzeanRunning", 9);
	}
	if (cNum == 4) {
		running.loadFrames("ZeitRunning", 9);
	}
	chAnim.setAnimation(running, 0.01f);
}
void Character::startAttack() { swinging = true; }
void Character::endAttack() { swinging = false; }
int Character::getChar() { return charNum; }
float Character::getSpeed() { return speed; }
void Character::Draw() {

	
	if(!swinging){
	playerModel = chAnim.getModel();
	}
	if (swinging) {
		playerModel = atAnim.getModel();
	}
	//std::cout << step;
	playerModel.draw();
}