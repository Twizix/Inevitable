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

class object
{
public:
	//CHARACTER FUNCTIONS
	object();
	~object();
	void setCharacter(int cNum);
	void interCont(float t, float inc);
	void characterTick();
	void characterDraw();
	float getSpeed();
	int getChar();
	void startAttack();
	void endAttack();
	void animationSpeed(float f);
	void animationReset();

	//PLAYER FUNCTIONS
	void playerTick(int keyDown[], std::vector<object> stager, float time, float cTime, std::vector<object>& p);
	void preDraw(float lpos[]);
	bool getStatus(glm::vec3 cam);
	glm::vec3 getCoord();
	bool Start();
	void playerReset(float time, glm::vec3 start);
	void setPlayer(int i);
	void Blink(glm::vec3 toBlink);
	void OzeanAbility();
	void LynAbility(std::vector<object>& p);
	void BrickAbility();
	void ZeitAbility(std::vector<object>& p);
	void setBoost(float s);
	void isReady();
	void notReady();
	void knock(glm::vec3 dir);
	int getPlayerNum();
	bool isHit();
	bool isConnected();
	bool usedAbility();
	std::string characterName();
	void setChar(int c);
	void refreshGamePad();
	Gamepad getPad();
	bool isInvul();

	//STAGE FUNCTIONS
	int getTriSize();
	Triangle getTriangle(int pos);
	void stageDraw();
	void stageSet(int t);
	void stageSetI(int i);
	void reUse(float off);
	float getOff();
	bool valid(glm::vec3 p);
	float getO();
	int getT();
	void isValid(glm::vec3 c);
	bool isOff();

	//CAMERA FUNCTIONS
	void cameraLoad(float l);
	void cameraSetSpeed(float i);
	void cameraUpdate(float time);
	void cameraReset();
	void cameraAddPoints(float v, float off);
	glm::vec3 Lerp(glm::vec3 v1, glm::vec3 v2);
	glm::vec3 getEye();
	glm::vec3 getCen();
	glm::vec3 getFirst();

private:
	//CHARACTER VARIABLES
	int charNum;
	KeyFrames running;
	KeyFrames attacking;
	Animation atAnim;
	Animation chAnim;
	bool swinging = false;
	GLMODEL playerModel;
	float characterSpeed = 0.2f;
	float step = 0.0f;
	float frame = 0.0f;
	GLMODEL idel;
	GLMODEL jumping;
	GLMODEL falling;
	float maxSpeed;
	float BoundingBox;
	float mass;
	float acceleration;
	float grav = 9.8f;
	AABB charBox;

	//PLAYER VARIABLES
	int preI = 0;
	float bCd = 0.0f;
	float lynspin;
	float knockTimer;
	bool isIn = true;
	glm::vec3 playerCoord = glm::vec3(0.0f, 20.0f, 0.0f);
	float rotAngle = 0.0f;
	bool invul = false;
	GLuint Goldtex;
	bool blinkProgress = false;
	glm::vec3 bVec;
	bool found = false;
	bool found2 = false;
	bool found3 = false;
	bool found4 = false;
	bool knocked;
	Gamepad pad;
	glm::vec3 forwardVec = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 ch;
	int jumpPlane;
	glm::vec3 point;
	bool inAir;
	bool jumped = false;
	bool shoudGrace = false;
	bool jump = false;
	float xAir = 0.0f;
	float yAir = 0.0f;
	bool onLand = false;
	glm::vec3 jumpVec = glm::vec3(0.0f, -0.0000000001f, 0.0f);
	float airSpeed = 0.0f;
	float speedBoost = 0.0f;
	bool airMove = false;
	float fallTime = 0.0f;
	float oldfallTime = 0.0f;
	float gracePeriod = 0.0f;
	bool wallReJump = false;
	glm::vec3 point2;
	glm::vec3 pumpVec;
	glm::vec3 point4;
	glm::vec3 point3;
	bool connection = false;
	bool hasEnd = true;
	bool ready = false;
	int playerNumber;
	Ray pRay;
	GLMODEL shade;
	GLuint shadow;
	std::map<int, glm::vec3> mapAware;
	float velocity = 3.0f;
	float planeRot;
	float xRot;
	float zRot;
	float speed = 0.0f;
	float maxspeed = 0.5f;
	float accel = 1.0f;
	float runTime = 0.0f;
	float oldRunTime = 0.0f;
	float jumpTime = 0.0f;
	float gravity;
	glm::vec3 knockVec;
	glm::vec3 landingVec;
	bool hopStop = false;
	AABB playerBox;
	bool hasStop;
	glm::vec3 downCoord = glm::vec3(0.0f, 0.0f, 0.0f);
	bool hasConnect;

	//STAGE VARIABLES
	float offset;
	int type;
	bool draw = true;
	float end;
	float begin;
	GLMODEL stageModel;
	GLuint tex;
	AABB stageBox;
	float rotTarget;
	std::vector<object> stager;

	//CAMERA VARIABLES
	float segTime = 0.0f;
	float t = 0.0f;
	float segment = 0.0f;
	std::map<int, std::vector<glm::vec3>> loader;
	std::vector<glm::vec3> center;
	std::vector<glm::vec3> eye;
	float cameraSpeed = 0.5f;
	float xDtoF;
	float distance = 0.0f;
};