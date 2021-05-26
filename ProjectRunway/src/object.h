

#include "Controller.h"
#pragma once
typedef struct
{
	glm::vec3 min; //Contains lowest corner of the box
	glm::vec3 max; //Contains highest corner of the box
} AABB;


bool detectCollision(AABB a, AABB b);
int triangle_intersection(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 O, glm::vec3 D, float* out);
int intersect3D_RayTriangle(glm::vec3 O, glm::vec3 D, glm::vec3 &len, Triangle T, glm::vec3 &I, float xOff);

class Camera {

public:
	Camera();
	~Camera();
	void load(float l);
	void setSpeed(float i);
	void update(float time);
	void reset();
	void cameraAddPoints(float v, float off);
	glm::vec3 Lerp(glm::vec3 v1, glm::vec3 v2);
	glm::vec3 getEye();
	glm::vec3 getCen();
	glm::vec3 getFirst();
private:
	float segTime=0.0f;
	float t=0.0f;
	float segment=0.0f;
	std::map<int, std::vector<glm::vec3>> loader;
	std::vector<glm::vec3> center;
	std::vector<glm::vec3> eye;
	float speed = 0.5f;
	float xDtoF;
	float distance = 0.0f;
};
class Character {
public:
	Character();
	~Character();
	void setCharacter(int cNum);
	void interCont(float t,float inc);
	void tick();
	void Draw();
	float getSpeed();
	void fuckUp(float f);
	void fuckDown();
	void startAttack();
	void endAttack();
	int getChar();
private:
//	std::vector<GLMODEL> models;
	bool swinging = false;
	int charNum;
	float step=0.0f;
	float frame=0.0f;
	GLMODEL playerModel;
	GLMODEL idel;
	GLMODEL jumping;
	GLMODEL falling;
	KeyFrames running;
	KeyFrames attacking;
	Animation chAnim;
	Animation atAnim;
	float maxSpeed;
	float BoundingBox;
	float mass;
	float speed=0.2f;
	float acceleration;
	float grav = 9.8f;
	AABB charBox;
};

class Stage {
public:
	Stage();
	~Stage();
	int getTriSize();
	Triangle getTriangle(int pos);
	void Draw();
	void set(int t);
	void setI(int i);
	void reUse(float off);
	float getOff();
	bool valid(glm::vec3 p);
	float getO();
	int getT();
	void isValid(glm::vec3 c);
	
	bool isOff();
private:
	float offset;
	int type;
	bool isIn;
	bool draw = true;
	float end;
	float begin;
	GLMODEL stageModel;
	GLuint tex;

	AABB stageBox;
};

class Player {
public:
	Player();
	Player(int pNum);
	~Player();
	Character getCharacter();
	void tick(int keyDown[], std::vector<Stage> stager,float time,float cTime,std::vector<Player>& p);
	void preDraw(float lpos[]);
	bool getStatus(glm::vec3 cam);
	glm::vec3 getCoord();
	bool Start();
	void set(int i);
	void reset(float time,glm::vec3 start);
	void Blink(glm::vec3 toBlink);
	void OzenAbility();
	void LynAbility(std::vector<Player>& p);
	void BrickAbility();
	void ZeitAbility(std::vector<Player>& p);
	void setBoost(float s);
	void isReady();
	void knock(glm::vec3 dir);
	int getPlayerNum();
	bool isHit();
	bool isConnected();
	void notReady();
	bool usedAbility();
	std::string characterName();
	void setCharacter(int c);
	void refreshGamePad();
	Gamepad getPad();
	bool isInvul();
private:
	Stage stage;
	std::vector<Stage> stager;
	Character playerCharacter;
	Gamepad pad;
	float rotTarget;
	glm::vec3 playerCoord = glm::vec3(0.0f, 20.0f, 0.0f);
	int preI = 0;
	bool jumped = false;
	bool invul = false;
	bool connection=false;
	glm::vec3 downCoord = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 forwardVec= glm::vec3(0.0f,0.0f,1.0f);
	glm::vec3 jumpVec = glm::vec3(0.0f, -0.0000000001f, 0.0f);
	bool hasConnect;
	GLuint tex;
	GLuint Goldtex;
	GLuint shadow;
	GLMODEL shade;
	std::map<int, glm::vec3> mapAware;
	float velocity=3.0f;
	bool knocked;
	float knockTimer;
	float planeRot;
	float xRot;
	float zRot;
	float speed=0.0f;
	float maxspeed = 0.5f;
	float accel = 1.0f;
	float runTime = 0.0f;
	float airSpeed = 0.0f;
	float speedBoost = 0.0f;
	float oldRunTime = 0.0f;
	float jumpTime=0.0f;
	bool hasEnd = true;
	float fallTime=0.0f;
	float gravity;
	float oldfallTime = 0.0f;
	AABB playerBox;
	Ray pRay;
	float xAir=0.0f;
	float yAir=0.0f;
	bool inAir ;
	bool hasStop;
	bool isIn = true;
	bool airMove = false;
	float rotAngle=0.0f;
	int playerNumber;
	bool found = false;
	bool found2 = false;
	bool found3 = false;
	bool found4 = false;
	bool shoudGrace=false;
	bool onLand = false;
	bool hopStop = false;
	bool wallReJump = false;
	bool blinkProgress = false;
	bool jump = false;
	bool ready = false;
	float lynspin;
	float bCd=0.0f;
	int jumpPlane;
	float gracePeriod = 0.0f;
	glm::vec3 bVec;
	glm::vec3 knockVec;
	glm::vec3 landingVec;
	glm::vec3 pumpVec;
	glm::vec3 ch;
	glm::vec3 point;
	glm::vec3 point2;
	glm::vec3 point3;
	glm::vec3 point4;
};