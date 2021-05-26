// Core Libraries
#include "soundHandle.h"
#include <map> // for std::map
#include <memory> // for std::shared_ptr

// 3rd Party Libraries
#include <GL\glew.h>
#include <GLUT\glut.h>
#include <IL/il.h> // for ilInit()
#include <glm\vec3.hpp>

// User Libraries
#include "Shader.h"
#include "ShaderProgram.h"
#include "FrameBufferObject.h"
#include "Material.h"

// Defines and Core variables
#define FRAMES_PER_SECOND 60
const int FRAME_DELAY = 1000 / FRAMES_PER_SECOND; // Miliseconds per frame
int windowWidth;
int windowHeight;

int veiwSelect = 1;
int mousepositionX;
int mousepositionY;
unsigned int oldTimeSinceStart = 0.0f;
unsigned int timeSinceStart;
unsigned int deltaT;
GLfloat rot = 0.0;
int keyDown[256];
GLMODEL chest;
GLMODEL well;
int living = 0;
GLMODEL cone;
GLMODEL cube;
GLMODEL pyramid;
GLMODEL sphere;
GLMODEL thingy;
GLMODEL tube;
glm::vec3 oneVector(0.0f, 0.0f, 1.0f);
glm::vec3 twoVector(0.0f, 0.0f, 1.0f);
glm::vec3 threeVector(0.0f, 0.0f, 1.0f);
glm::vec3 fourVector(0.0f, 0.0f, 1.0f);
GLfloat oneHor = 18.0f;
GLfloat oneVer = 0.0f;
std::map<int, glm::vec3> pCoord;
GLfloat twoHor = 0.0f;
GLfloat twoVer = 0.0f;
bool canGo = false;
GLfloat threeHor = 0.0f;
GLfloat threeVer = 0.0f;
GLfloat zoomOne = 0.0f;
GLfloat zoomTwo = 0.0f;
GLfloat zoomThree = 0.0f;
std::vector<object> players;

std::vector<object> preload;
std::vector<object> stages;

int currentStage = 0;
glm::vec3 c;
glm::vec3 e;
GLuint backText;
int winner = 0;
GLMODEL backer;
GLuint outl;
GLuint out2;
GLuint out3;
GLuint imagineDragons;
GLuint winn;
GLuint border;
GLuint c1;
GLuint c2;
GLuint c3;
GLuint c4;
GLuint check;

float pretimer = 5.0f;
float retimer = 6.0f;
bool canStart = true;
GLuint title;
GLuint present;
GLuint star;
GLuint exits;
GLuint sele;
GLuint remote;

GLuint pL[4];

GLuint pD[4];
bool lightning = false;
float lightimer = 0.0f;
GLuint backeer;
GLuint cont;
object goPro;
float cTime;
float oldC;
float timer = 0.0f;
bool start4 = true;
glm::vec3 forwardVector(0.0f, 0.0f, 1.0f);
glm::vec3 rightVector;
bool jump = false;
float movementScalar = 0.1f;
float pTime[4] = { 0.0f,0.0f,0.0f,0.0f };
float dTime[4] = { 0.0f,0.0f,0.0f,0.0f };
float pChar[4] = { 1.0f,1.0f,1.0f,1.0f };
bool bStart[4] = { false, false, false, false };
enum Phase { menu, charselect, running };
glm::vec2 tR;
glm::vec2 tL;
glm::vec2 bR;
glm::vec2 bL;
std::vector<glm::vec3> camPo;
Phase game = menu;
soundHandle handler;
glm::vec3 soundlocal = glm::vec3(0.0f, 0.0f, 0.0f);
Noise *music;

// Asset databases
//std::map<std::string, std::shared_ptr<GLMODEL>> meshes;
//std::map<std::string, std::shared_ptr<Camera>> gameobjects1;
//std::map<std::string, std::shared_ptr<Character>> gameobjects2;
//std::map<std::string, std::shared_ptr<Stage>> gameobjects3;
//std::map<std::string, std::shared_ptr<Player>> gameobjects4;

// Materials
std::shared_ptr<Material> defaultMaterial;
std::shared_ptr<Material> invertPostProcessMaterial;
std::shared_ptr<Material> unlitTextureMaterial;

FrameBufferObject fbo;

void setGame();

void initializeShaders()
{
	std::string shaderPath = "../../Assets/Shaders/";

	// Load shaders

	Shader v_default, v_passThrough;
	v_default.loadShaderFromFile(shaderPath + "default_v.glsl", GL_VERTEX_SHADER);
	v_passThrough.loadShaderFromFile(shaderPath + "passThrough_v.glsl", GL_VERTEX_SHADER);

	Shader f_default, f_invertFilter, f_unlitTexture;
	f_default.loadShaderFromFile(shaderPath + "default_f.glsl", GL_FRAGMENT_SHADER);
	f_invertFilter.loadShaderFromFile(shaderPath + "invertFilter_f.glsl", GL_FRAGMENT_SHADER);
	f_unlitTexture.loadShaderFromFile(shaderPath + "unlitTexture_f.glsl", GL_FRAGMENT_SHADER);

	// Default material that all objects use
	defaultMaterial = std::make_shared<Material>();
	defaultMaterial->shader->attachShader(v_default);
	defaultMaterial->shader->attachShader(f_default);
	defaultMaterial->shader->linkProgram();

	// Unlit texture
	unlitTextureMaterial = std::make_shared<Material>();
	unlitTextureMaterial->shader->attachShader(v_passThrough);
	unlitTextureMaterial->shader->attachShader(f_unlitTexture);
	unlitTextureMaterial->shader->linkProgram();

	// Simple invert post process filter
	invertPostProcessMaterial = std::make_shared<Material>();
	invertPostProcessMaterial->shader->attachShader(v_passThrough);
	invertPostProcessMaterial->shader->attachShader(f_invertFilter);
	invertPostProcessMaterial->shader->linkProgram();
}

void initializeFrameBufferObjects()
{
	fbo.createFrameBuffer(windowWidth, windowHeight, 1, true);
}

void drawSquare(float x, float y, float w, float h)
{
	float fx, fy, fw, fh;
	fx = (x / 1920)*(windowWidth);
	fy = (y / 1080)*(windowHeight);
	fw = (w / 1920)*(windowWidth);
	fh = (h / 1080)*(windowHeight);

	tR = glm::vec2(1.0f - (((windowWidth / 2) - (fx + fw))) / (windowWidth / 2), 1.0f - (((windowHeight / 2) - (fy + fh)) / (windowHeight / 2)));
	tL = glm::vec2(1.0f - (((windowWidth / 2) - (fx))) / (windowWidth / 2), 1.0f - (((windowHeight / 2) - (fy + fh)) / (windowHeight / 2)));
	bR = glm::vec2(1.0f - (((windowWidth / 2) - (fx + fw))) / (windowWidth / 2), 1.0f - (((windowHeight / 2) - (fy)) / (windowHeight / 2)));
	bL = glm::vec2(1.0f - (((windowWidth / 2) - (fx))) / (windowWidth / 2), 1.0f - (((windowHeight / 2) - (fy)) / (windowHeight / 2)));
	glBegin(GL_QUADS);
	glTexCoord2f(1.f, 1.f);  glVertex3f(tR.x, tR.y, 0.0); // ++
	glTexCoord2f(0.f, 1.f);  glVertex3f(tL.x, tL.y, 0.0); // -+
	glTexCoord2f(0.f, 0.f);  glVertex3f(bL.x, bL.y, 0.0); //--
	glTexCoord2f(1.f, 0.f);  glVertex3f(bR.x, bR.y, 0.0); // +-
	glEnd();
}

void drawBack()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glPushMatrix();
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	glTranslatef(c.x + 400.0f, c.y - 20, c.z);
	glScalef(1.4f, 1.0f, 1.0f);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);

	glBindTexture(GL_TEXTURE_2D, backeer);
	backer.draw();
	glBindTexture(GL_TEXTURE_2D, 0);

	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glTranslatef(c.x + 60.0f, c.y, c.z);
	glBindTexture(GL_TEXTURE_2D, backText);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-450.0f, 50.0f, 200.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(450.0f, 50.0f, 200.0f);


	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(450.0f, -470.0f, 200.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-450.0f, -470.0f, 200.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(450.0f, 50.0f, -200.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-450.0f, 50.0f, -200.0f);


	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-450.0f, -470.0f, -200.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(450.0f, -470.0f, -200.0f);

	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

}

void drawGUI()
{
	glLoadIdentity();
	glViewport(0, 0, windowWidth, windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -100.0, 101.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	for (int i = 0; i < 4; i++)
	{
		if (players[i].isConnected())
		{
			if (players[i].getStatus(c))
			{
				glBindTexture(GL_TEXTURE_2D, pL[i]);
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, pD[i]);
			}
			glColor4f(0.5f, 0.5f, 0.5f, 1.0f); //ensure no color distortion
			drawSquare(-600.0f + (300.0f*i), -500.0f, 100.0f, 100.0f);
			glBindTexture(GL_TEXTURE_2D, 0);
			if (players[i].usedAbility())
			{
				glBindTexture(GL_TEXTURE_2D, outl);
			}
			if (!players[i].usedAbility() && lightning)
			{
				glBindTexture(GL_TEXTURE_2D, out2);
			}
			if (!players[i].usedAbility() && !lightning)
			{
				glBindTexture(GL_TEXTURE_2D, out3);
			}
			glColor4f(0.5f, 0.5f, 0.5f, 1.0f); //ensure no color distortion
			drawSquare(-600.0f + (300 * i) - 15, -500.0f - 15, 180.0f, 130.0f);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
	if (canGo == false)
	{
		glBindTexture(GL_TEXTURE_2D, cont);
		glColor4f(0.5f, 0.5f, 0.5f, 1.0f); //ensure no color distortion
		drawSquare(-600, -100.0f, 1200.0f, 200.0f);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if (winner > 0)
	{
		if (winner == 1)
		{
			glBindTexture(GL_TEXTURE_2D, pL[0]);
		}
		if (winner == 2) {
			glBindTexture(GL_TEXTURE_2D, pL[1]);
		}
		if (winner == 3) {
			glBindTexture(GL_TEXTURE_2D, pL[2]);
		}
		if (winner == 4) {
			glBindTexture(GL_TEXTURE_2D, pL[3]);
		}

		glBindTexture(GL_TEXTURE_2D, imagineDragons);
		drawSquare(-600.0f + (300 * (winner - 1)) - 15, -500.0f - 15, 180.0f, 130.0f);
		glBindTexture(GL_TEXTURE_2D, winn);
		drawSquare(-600.0f + (300 * (winner - 1)) - 15, -500.0f + 100 - 15, 300.0f, 75.0f);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}


void drawRunning()
{
	glClearDepth(1);
	/* clear the screen */
	c = goPro.getCen();
	e = goPro.getEye();
	GLfloat light_position[] = { e.x, e.y, e.z, 1.0 };

	glClearColor(0.0, 0.0, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glViewport(0, 0, windowWidth, windowHeight);
	glMatrixMode(GL_PROJECTION); //x
	glLoadIdentity(); //x
	gluPerspective(90.0f, windowWidth / windowHeight, 0.01f, 1000000000000000.0f); //projection matrix
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); //x
	gluLookAt(e.x, e.y, e.z, c.x, c.y, c.z, 0.0, 1.0, 0.0); //x
	glMatrixMode(GL_MODELVIEW); //x
	glLoadIdentity(); //x
	glPushMatrix(); //x
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); //x
	glPopMatrix(); //x


	////////// DRAW PLAYERS
	
	if (canGo == true)
	{
		for (int i = 0; i < 4; i++)
		{
			if (players[i].isConnected())
			{
				players[i].preDraw(light_position);
			}
		}
	}

	////////// DRAW LEVELS
	for (int i = 0; i < stages.size(); i++)
	{
		stages[i].stageDraw();
	}

	drawBack();
	drawGUI();
	/* Swap Buffers to Make it show up on screen */
	glutSwapBuffers();
}

void tickRunning()
{

	if (lightimer > 0.0f)
	{
		lightimer -= cTime;
	}
	if (lightimer <= 0.0f)
	{
		lightimer = 0.07f;

		lightning = !lightning;
	}
	living = 0;
	for (int i = 0; i < 4; i++)
	{
		if (players[i].isConnected() && players[i].getStatus(c))
		{
			living++;
			//std::cout << living << std::endl;
		}
	}
	if (living == 1)
	{
		for (int i = 0; i < 4; i++)
		{
			if (players[i].getStatus(c) && players[i].isConnected())
			{
				winner = i + 1;
			}
		}
	}
	if (canGo)
	{
		for (int i = 0; i < 4; i++)
		{
			pCoord[i] = players[i].getCoord();
		}
		for (int i = 0; i < 4; i++)
		{
			if (players[i].isConnected())
			{
				players[i].playerTick(keyDown, stages, deltaT, cTime, players);
			}
		}
		goPro.cameraUpdate(deltaT);
		for (int i = 0; i < stages.size(); i++)
		{
			stages[i].isValid(c);

		}
		if (stages[currentStage].isOff())
		{
			currentStage++;
			int type = rand() % 4;
			stages.push_back(preload[type]);

			stages[stages.size() - 1].reUse(stages[stages.size() - 2].getOff());

			goPro.cameraAddPoints(type, stages[stages.size() - 1].getO());
		}

	}
	if (canGo)
	{
		if ((!(players[0].getStatus(c)) || !players[0].isConnected()) && (!(players[1].getStatus(c)) || !players[1].isConnected()) && (!(players[2].getStatus(c)) || !players[2].isConnected()) && (!(players[3].getStatus(c)) || !players[3].isConnected()) && canGo)
		{
			canGo = false;
			for (int i = 0; i < 4; i++)
			{
				players[i].notReady();
			}
		}
	}
	if (canGo == false)
	{
		if (players[0].Start() && players[1].Start() && players[2].Start() && players[3].Start() && canGo == false)
		{
			game = charselect;
			//	PlaySound(TEXT("Inevitable.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		}
	}

}
void drawMenu()
{
	glClearColor(0.0, 0.0, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glViewport(0, 0, windowWidth, windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, windowWidth / windowHeight, 0.01f, 1000000000000000.0f);
	glLoadIdentity();
	glViewport(0, 0, windowWidth, windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -100.0, 101.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	if (pretimer > 0.0f)
	{
		glBindTexture(GL_TEXTURE_2D, present);
		glColor4f(0.5f, 0.5f, 0.5f, 1.0f); //ensure no color distortion
		drawSquare(-(1920 / 2), -(1080 / 2), 1920, 1080);
		glBindTexture(GL_TEXTURE_2D, 0);

	}
	if (pretimer <= 0.0f&&retimer > 0.0f) {
		glBindTexture(GL_TEXTURE_2D, remote);
		glColor4f(0.5f, 0.5f, 0.5f, 1.0f); //ensure no color distortion
		drawSquare(-(1920 / 2), -(1080 / 2), 1920, 1080);
		glBindTexture(GL_TEXTURE_2D, 0);

	}
	if (pretimer <= 0.0f&&retimer <= 0.0f) {
		glBindTexture(GL_TEXTURE_2D, title);
		glColor4f(0.5f, 0.5f, 0.5f, 1.0f); //ensure no color distortion
		drawSquare(-(1920 / 2), -(1080 / 2), 1920, 1080);
		if (canStart) {
			glBindTexture(GL_TEXTURE_2D, sele);
			glColor4f(0.5f, 0.5f, 0.5f, 1.0f); //ensure no color distortion
			drawSquare(0.0f - 100, -300, 200, 100);
		}
		glBindTexture(GL_TEXTURE_2D, star);
		glColor4f(0.5f, 0.5f, 0.5f, 1.0f); //ensure no color distortion
		drawSquare(0.0f - 100, -300, 200, 100);
		if (!canStart) {
			glBindTexture(GL_TEXTURE_2D, sele);
			glColor4f(0.5f, 0.5f, 0.5f, 1.0f); //ensure no color distortion
			drawSquare(0.0f - 100, -450, 200, 100);
		}
		glBindTexture(GL_TEXTURE_2D, exits);
		glColor4f(0.5f, 0.5f, 0.5f, 1.0f); //ensure no color distortion
		drawSquare(0.0f - 100, -450, 200, 100);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glutSwapBuffers();

}
void tickMenu() {
	if (start4) {
		pretimer = 15.0f;
		retimer = 6.0f;
		start4 = false;
		//PlaySound(TEXT("Inevitable.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	}
	if (pretimer > 0.0f) {
		pretimer -= cTime;
	}
	if (pretimer <= 0.0f&&retimer > 0.0f) {
		retimer -= cTime;

	}
	if (pretimer <= 0.0f&&retimer <= 0.0f) {
		if (players[0].getPad().dDown) {
			canStart = false;

		}
		if (players[0].getPad().dUp) {
			canStart = true;

		}
		if (players[0].getPad().aButton) {
			if (canStart) {
				game = charselect;

			}
			if (!canStart) {
				handler.end();
				exit(0);
			}
		}
	}
}

void tickCharSelect() {
	for (int i = 0; i < 4; i++) {
		if (players[i].getPad().aButton) {
			bStart[i] = true;
		}
		if (players[i].getPad().bButton) {
			bStart[i] = false;
		}
		if (pTime[i] > 0.0f) {
			pTime[i] -= cTime;
		}
		if (dTime[i] > 0.0f) {
			dTime[i] -= cTime;
		}
		if (players[i].getPad().dUp&&pTime[i] <= 0.0f) {
			bStart[i] = false;
			pTime[i] = 0.3;
			pChar[i] += 1.0f;
			if (pChar[i] > 4.0f) {
				pChar[i] = 1.0f;
			}


		}
		if (!players[i].getPad().dUp) {
			pTime[i] = 0.0f;
		}
		if (players[i].getPad().dDown&&dTime[i] <= 0.0f) {
			bStart[i] = false;
			dTime[i] = 0.3;
			pChar[i] -= 1.0f;
			if (pChar[i] < 1.0f) {
				pChar[i] = 4.0f;
			}


		}
		if (!players[i].getPad().dDown) {
			dTime[i] = 0.0f;
		}
	}

	if (((pChar[0] > 0 && bStart[0]) || !players[0].isConnected()) && ((pChar[1] > 0 && bStart[1]) || !players[1].isConnected()) && ((pChar[2] > 0 && bStart[2]) || !players[2].isConnected()) && (((pChar[3] > 0 && bStart[3]) || !players[3].isConnected()))) {
		players[0].setChar(pChar[0]);
		players[1].setChar(pChar[1]);
		players[2].setChar(pChar[2]);
		players[3].setChar(pChar[3]);
		//PlaySound(TEXT("Inevitable2.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		for (int i = 0; i < 4; i++) {
			bStart[i] = false;
			std::string str = "assets/images/" + players[i].characterName() + ".png";
			char *cstr = new char[str.length() + 1];
			strcpy(cstr, str.c_str());
			glBindTexture(GL_TEXTURE_2D, pL[i]);
			pL[i] = ilutGLLoadImage(cstr);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindTexture(GL_TEXTURE_2D, pD[i]);
			str = "assets/images/" + players[i].characterName() + "_dead.png";
			cstr = new char[str.length() + 1];
			strcpy(cstr, str.c_str());
			pD[i] = ilutGLLoadImage(cstr);
			glBindTexture(GL_TEXTURE_2D, 0);
			delete[] cstr;

		}

		deltaT = 0;
		oldTimeSinceStart = timeSinceStart;
		goPro.cameraReset();
		canGo = true;
		stages.clear();
		stages.push_back(preload[0]);
		stages[0].reUse(0.0f);
		goPro.cameraAddPoints(0, stages[0].getO());
		for (int i = 0; i < 6; i++) {
			int type = rand() % 4;
			stages.push_back(preload[type]);
			stages[i + 1].reUse(stages[i].getOff());
			goPro.cameraAddPoints(type, stages[i + 1].getO());
		}
		players[0].playerReset(deltaT, goPro.getFirst());
		players[1].playerReset(deltaT, goPro.getFirst());
		players[2].playerReset(deltaT, goPro.getFirst());
		players[3].playerReset(deltaT, goPro.getFirst());
		currentStage = 0;
		game = running;
	}
}
void bindPortrait(int i) {
	if (i == 1) {
		glBindTexture(GL_TEXTURE_2D, c1);
	}
	if (i == 2) {
		glBindTexture(GL_TEXTURE_2D, c2);
	}
	if (i == 3) {
		glBindTexture(GL_TEXTURE_2D, c3);
	}
	if (i == 4) {
		glBindTexture(GL_TEXTURE_2D, c4);
	}
}
void drawCharSelect() {
	glClearColor(0.0, 0.0, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glViewport(0, 0, windowWidth, windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, windowWidth / windowHeight, 0.01f, 1000000000000000.0f);
	glLoadIdentity();
	glViewport(0, 0, windowWidth, windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -100.0, 101.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	bindPortrait(pChar[0]);
	glColor4f(0.5f, 0.5f, 0.5f, 1.0f); //ensure no color distortion
	drawSquare(-(1920 / 2), 0, 1920 / 2, 1080 / 2);
	if (bStart[0]) {
		glBindTexture(GL_TEXTURE_2D, check);
		drawSquare(-(1920 / 2) + 30, 0 + 20, 100, 100);
	}
	bindPortrait(pChar[1]);
	glColor4f(0.5f, 0.5f, 0.5f, 1.0f); //ensure no color distortion
	drawSquare(0, 0, 1920 / 2, 1080 / 2);
	if (bStart[1]) {
		glBindTexture(GL_TEXTURE_2D, check);
		drawSquare(30, 0 + 20, 100, 100);
	}
	bindPortrait(pChar[2]);
	glColor4f(0.5f, 0.5f, 0.5f, 1.0f); //ensure no color distortion
	drawSquare(-(1920 / 2), -(1080 / 2), 1920 / 2, 1080 / 2);
	if (bStart[2]) {
		glBindTexture(GL_TEXTURE_2D, check);
		drawSquare(-(1920 / 2) + 30, -(1080 / 2) + 20, 100, 100);
	}
	bindPortrait(pChar[3]);
	glColor4f(0.5f, 0.5f, 0.5f, 1.0f); //ensure no color distortion
	drawSquare(0, -(1080 / 2), 1920 / 2, 1080 / 2);
	if (bStart[3]) {
		glBindTexture(GL_TEXTURE_2D, check);
		drawSquare(30, -(1080 / 2) + 20, 100, 100);
	}
	glBindTexture(GL_TEXTURE_2D, border);
	glColor4f(0.5f, 0.5f, 0.5f, 1.0f); //ensure no color distortion
	drawSquare(-(1920 / 2), -(1080 / 2), 1920, 1080);
	glBindTexture(GL_TEXTURE_2D, 0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glutSwapBuffers();

}
void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
}
float position[4] = { 0.0f,0.0f,0.0f,1.0f };


void DisplayCallbackFunction(void)
{

	if (game == running) {
		drawRunning(); // game
	}
	if (game == charselect) {
		drawCharSelect();
	}
	if (game == menu) {
		drawMenu();
	}
	if (keyDown[27]) {
		handler.end();
		exit(0);

	}
}



/* function void KeyboardCallbackFunction(unsigned char, int,int)
* Description:
*   - this handles keyboard input when a button is pressed
*/
void KeyboardCallbackFunction(unsigned char key, int x, int y)
{
	//std::cout << "Key Down:" << (int)key << std::endl;
	keyDown[key] = true;



}

/* function void KeyboardUpCallbackFunction(unsigned char, int,int)
* Description:
*   - this handles keyboard input when a button is lifted
*/
void KeyboardUpCallbackFunction(unsigned char key, int x, int y)
{
	//std::cout << (int)key << std::endl;
	keyDown[key] = false;
}

void idleFunc()
{

}

/* function TimerCallbackFunction(int value)
* Description:
*  - this is called many times per second
*  - this enables you to animate things
*  - no drawing, just changing the state
*  - changes the frame number and calls for a redisplay
*  - FRAME_DELAY is the number of milliseconds to wait before calling the timer again
*/
void TimerCallbackFunction(int value)
{
	if (keyDown['w']) {
		soundlocal.z += 0.5f;
	}
	if (keyDown['s']) {
		soundlocal.z -= 0.5f;
	}
	if (keyDown['d']) {
		soundlocal.x += 0.5f;
	}
	if (keyDown['a']) {
		soundlocal.x -= 0.5f;
	}

	if (keyDown['r']) {
		soundlocal = glm::vec3(0.0f, 0.0f, 0.0f);
	}
	handler.setPos(glm::vec3(0.0f, 0.0f, 0.0f));
	music->setPos(soundlocal);
	handler.tick();
	timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	deltaT = timeSinceStart - oldTimeSinceStart;
	cTime = (timeSinceStart - oldC) / 1000.0f;
	oldC = timeSinceStart;
	for (int i = 0; i < 4; i++) {
		players[i].refreshGamePad();
	}

	if (game == running) {
		tickRunning();
	}
	if (game == charselect) {
		tickCharSelect();
	}
	if (game == menu) {
		tickMenu();
	}

	glutPostRedisplay();
	/* this call gives it a proper frame delay to hit our target FPS */
	glutTimerFunc(FRAME_DELAY, TimerCallbackFunction, 0);
}

/* function WindowReshapeCallbackFunction()
* Description:
*  - this is called whenever the window is resized
*  - and sets up the projection matrix properly
*/
void WindowReshapeCallbackFunction(int w, int h)
{
	// switch to projection because we're changing projection
	float asp = (float)w / (float)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glMatrixMode(GL_MODELVIEW);

}
void MouseClickCallbackFunction(int button, int state, int x, int y)
{
	// Handle mouse clicks
	if (state == GLUT_DOWN)
	{
		//	std::cout << "Mouse x:" << x << " y:" << y << std::endl;

	}
	//	std::cout << veiwSelect << std::endl;
}


/* function MouseMotionCallbackFunction()
* Description:
*   - this is called when the mouse is clicked and moves
*/
void MouseMotionCallbackFunction(int x, int y)
{
}

void MousePassiveMotionCallbackFunction(int x, int y)
{
}

void init()
{
	///// INIT OpenGL /////
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	handler.init();

	initNoise(music);
	music->set("assets/sounds/Inevitable.wav", NEVER, 0, false);
	handler.addSound(music);

	////load shaders
	//
	//std::string shaderPath = "assets/shaders/";
	//
	//// Load shaders
	//
	//Shader v_default;
	//v_default.loadShaderFromFile(shaderPath + "default_v.glsl", GL_VERTEX_SHADER);
	//
	//Shader f_default;
	//f_default.loadShaderFromFile(shaderPath + "default_f.glsl", GL_FRAGMENT_SHADER);
	//
	//shaderprogram = new ShaderProgram();
	// 
	//shaderprogram->attachShader(v_default);
	//shaderprogram->attachShader(f_default);
	//shaderprogram->linkProgram();
}

int main(int argc, char **argv)
{
	srand(time(NULL));
	/* initialize the window and OpenGL properly */
	GetDesktopResolution(windowWidth, windowHeight);
	glutInit(&argc, argv);
	ShowCursor(false);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA);
	glutCreateWindow("Inevitable");


	/* set up our function callbacks */
	glutDisplayFunc(DisplayCallbackFunction);
	glutKeyboardFunc(KeyboardCallbackFunction);
	glutKeyboardUpFunc(KeyboardUpCallbackFunction);
	glutIdleFunc(idleFunc);
	glutReshapeFunc(WindowReshapeCallbackFunction);
	glutMouseFunc(MouseClickCallbackFunction);
	glutMotionFunc(MouseMotionCallbackFunction);
	glutPassiveMotionFunc(MousePassiveMotionCallbackFunction);
	glutTimerFunc(1, TimerCallbackFunction, 0);
	glutFullScreen();


	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);
	ilInit();
	iluInit();
	ilutRenderer(ILUT_OPENGL);
	init(); //Setup OpenGL States

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0.0, 0.0, 0.0, 1.0 };





	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, mat_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, mat_diffuse);
	for (int i = 0; i < 4; i++) {
		object pl;

		players.push_back(pl);
		players[i].setPlayer(i + 1);
	}

	setGame();
	/* start the event handler */
	glutMainLoop();
	return 0;
}

void setGame()
{
	//std::string meshPath = "Assets/Models/";
	//
	//std::shared_ptr<GLMODEL> ground = std::make_shared<GLMODEL>();
	//
	//ground->load(meshPath + "Ground.obj");
	//
	//meshes["ground"] = ground;
	//
	//gameobjects1["ground"] = std::make_shared<GLMODEL>();
	//
	//// Create a quad (probably want to put this in a class...)
	//std::shared_ptr<GLMODEL> quadMesh = std::make_shared<GLMODEL>();
	//meshes["quad"] = quadMesh;
	//
	// Triangle 1
	//quadMesh->vertices.push_back(Vertex(1.0, 1.0, 0.0));
	//quadMesh->uvs.push_back(glm::vec2(1.0, 1.0));
	//
	//quadMesh->vertices.push_back(Vertex(-1.0, 1.0, 0.0));
	//quadMesh->texCoords.push_back(0.0, 1.0);
	//
	//quadMesh->vertices.push_back(Vertex(-1.0, -1.0, 0.0));
	//quadMesh->texCoords.push_back(0.0, 0.0);
	//
	//// Triangle 2
	//quadMesh->vertices.push_back(Vertex(1.0, 1.0, 0.0));
	//quadMesh->texCoords.push_back(1.0, 1.0);
	//
	//quadMesh->vertices.push_back(Vertex(-1.0, 1.0, 0.0));
	//quadMesh->texCoords.push_back(0.0, 1.0);
	//
	//quadMesh->vertices.push_back(Vertex(1.0, -1.0, 0.0));
	//quadMesh->texCoords.push_back(1.0, 0.0);
	//
	//quadMesh->createVBO();

	///std::string meshPath = "Assets/Models/";
	///
	///std::shared_ptr<GLMODEL> floorMesh = std::make_shared<GLMODEL>(); // a shared pointer will overload the '=' operator so it keep track of how many pointers point to the object, when nothing points to the data anymore it will automatically delete the memory
	///std::shared_ptr<GLMODEL> sphereMesh = std::make_shared<GLMODEL>();
	///std::shared_ptr<GLMODEL> torusMesh = std::make_shared<GLMODEL>();
	///
	///floorMesh->load(meshPath + "floor.obj");
	///sphereMesh->load(meshPath + "sphere.obj");
	///torusMesh->load(meshPath + "torus.obj");
	///
	///// Note: looking up a mesh by it's string name is not the fastest thing,
	///// you don't want to do this every frame, once in a while (like now) is fine.
	///// If you need you need constant access to a mesh (i.e. you need it every frame),
	///// store a reference to it so you don't need to look it up every time.
	///meshes["floor"] = floorMesh;
	///meshes["sphere"] = sphereMesh;
	///meshes["torus"] = torusMesh;
	///
	///// Create objects
	///gameobjects1["floor"] = std::make_shared<Camera>(/*glm::vec3(0.0f, 0.0f, 0.0f), floorMesh, defaultMaterial*/); // a material describes the render property of an object
	///gameobjects2["sphere"] = std::make_shared<Character>(/*glm::vec3(0.0f, 5.0f, 0.0f), sphereMesh, defaultMaterial*/);
	///gameobjects3["torus"] = std::make_shared<Stage>(/*glm::vec3(5.0f, 5.0f, 0.0f), torusMesh, defaultMaterial*/);
	///
	/// Set object properties
	///["sphere"]->colour = glm::vec4(1.0f);
	///["floor"]->colour = glm::vec4(0.2f, 0.1f, 0.2f, 1.0f);
	///["torus"]->colour = glm::vec4(0.1f, 0.2f, 0.2f, 1.0f);
	
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	glBindTexture(GL_TEXTURE_2D, backText);
	backText = ilutGLLoadImage("assets/images/background.png");
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, outl);
	outl = ilutGLLoadImage("assets/images/outline.png");
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, out2);
	out2 = ilutGLLoadImage("assets/images/outline1.png");
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_2D, out3);
	out3 = ilutGLLoadImage("assets/images/outline2.png");
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_2D, backeer);
	backeer = ilutGLLoadImage("assets/images/Ground1.png");
	glBindTexture(GL_TEXTURE_2D, 0);
	backer.load("assets/models/Ground.obj");
	glBindTexture(GL_TEXTURE_2D, cont);
	cont = ilutGLLoadImage("assets/images/start.png");
	glBindTexture(GL_TEXTURE_2D, border);
	border = ilutGLLoadImage("assets/images/charoverlay.png");
	glBindTexture(GL_TEXTURE_2D, c1);
	c1 = ilutGLLoadImage("assets/images/brick_sel.png");
	glBindTexture(GL_TEXTURE_2D, c2);
	c2 = ilutGLLoadImage("assets/images/lyn_sel.png");
	glBindTexture(GL_TEXTURE_2D, c3);
	c3 = ilutGLLoadImage("assets/images/ozean_sel.png");
	glBindTexture(GL_TEXTURE_2D, c4);
	c4 = ilutGLLoadImage("assets/images/zeit_sel.png");
	glBindTexture(GL_TEXTURE_2D, imagineDragons);
	imagineDragons = ilutGLLoadImage("assets/images/winner.png");
	glBindTexture(GL_TEXTURE_2D, winn);
	winn = ilutGLLoadImage("assets/images/winnerfont.png");
	glBindTexture(GL_TEXTURE_2D, check);
	check = ilutGLLoadImage("assets/images/yes.png");
	
	glBindTexture(GL_TEXTURE_2D, title);
	title = ilutGLLoadImage("assets/images/title.png");

	glBindTexture(GL_TEXTURE_2D, present);
	present = ilutGLLoadImage("assets/images/presents.png");

	glBindTexture(GL_TEXTURE_2D, remote);
	remote = ilutGLLoadImage("assets/images/xbox.png");

	glBindTexture(GL_TEXTURE_2D, star);
	star = ilutGLLoadImage("assets/images/startmenu.png");

	glBindTexture(GL_TEXTURE_2D, exits);
	exits = ilutGLLoadImage("assets/images/exit.png");

	glBindTexture(GL_TEXTURE_2D, sele);
	sele = ilutGLLoadImage("assets/images/lselect.png");

	glBindTexture(GL_TEXTURE_2D, 0);

	for (int i = 0; i < 5; i++) {
		object pre;
		pre.stageSet(i + 1);
		preload.push_back(pre);

	}
	goPro.cameraLoad(preload.size());

	stages.push_back(preload[0]);
	stages[0].reUse(0.0f);
	goPro.cameraAddPoints(0, stages[0].getO());
	for (int i = 0; i < 6; i++)
	{
		int type = rand() % 5;

		stages.push_back(preload[type]);

		stages[i + 1].reUse(stages[i].getOff());

		goPro.cameraAddPoints(type, stages[i + 1].getO());
	}
}