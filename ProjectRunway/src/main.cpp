/*@Name: Matthew Paraskevakos- 100592704 & Samuelle "Lili" Boufford-100582562
@Version: 1.1.1
*/

// kms

// Core Libraries

#include "object.h"



// 3rd Party Libraries


// Defines and Core variables
#define FRAMES_PER_SECOND 60
const int FRAME_DELAY = 1000 / FRAMES_PER_SECOND; // Miliseconds per frame
int windowWidth ;
int windowHeight;
int veiwSelect = 1;
int mousepositionX;
int mousepositionY;
 unsigned int oldTimeSinceStart=0.0f ;
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
std::vector<Player> players;

std::vector<Stage> preload;
std::vector<Stage> stages;

int currentStage=0;
glm::vec3 c;
glm::vec3 e;
GLuint backText;
int winner=0;
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
Camera goPro;
float cTime;
float oldC;
float timer = 0.0f;
bool start4 = true;
glm::vec3 forwardVector(0.0f,0.0f,1.0f);
glm::vec3 rightVector;
bool jump = false;
float movementScalar = 0.1f;
float pTime[4] = { 0.0f,0.0f,0.0f,0.0f };
float dTime[4] = { 0.0f,0.0f,0.0f,0.0f };
float pChar[4] = {1.0f,1.0f,1.0f,1.0f};
bool bStart[4] = {false, false, false, false};
enum Phase {menu,charselect,running };
glm::vec2 tR;
glm::vec2 tL;
glm::vec2 bR;
glm::vec2 bL;
std::vector<glm::vec3> camPo;
Phase game = menu;

void drawSquare(float x, float y, float w, float h) {
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

void drawBack() {
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

void drawGUI() {
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
	for (int i = 0; i < 4; i++) {
		if (players[i].isConnected()) {
			if (players[i].getStatus(c)) {
				glBindTexture(GL_TEXTURE_2D, pL[i]);
			}
			else {
				glBindTexture(GL_TEXTURE_2D, pD[i]);

			}
			glColor4f(0.5f, 0.5f, 0.5f, 1.0f); //ensure no color distortion
			drawSquare(-600.0f + (300.0f*i), -500.0f, 100.0f, 100.0f);
			glBindTexture(GL_TEXTURE_2D, 0);
			if (players[i].usedAbility()) {
				glBindTexture(GL_TEXTURE_2D, outl);
			}
			if (!players[i].usedAbility()&&lightning) {
				glBindTexture(GL_TEXTURE_2D, out2);
			}
			if (!players[i].usedAbility()&& !lightning) {
				glBindTexture(GL_TEXTURE_2D, out3);
			}
			glColor4f(0.5f, 0.5f, 0.5f, 1.0f); //ensure no color distortion
			drawSquare(-600.0f + (300 * i) - 15, -500.0f - 15, 180.0f, 130.0f);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

	}
	if (canGo == false) {
		glBindTexture(GL_TEXTURE_2D, cont);
		glColor4f(0.5f, 0.5f, 0.5f, 1.0f); //ensure no color distortion
		drawSquare(-600, -100.0f, 1200.0f, 200.0f);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if (winner > 0) {
		if (winner == 1) {
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
		
		glBindTexture(GL_TEXTURE_2D,imagineDragons);
		drawSquare(-600.0f + (300 * (winner-1)) - 15, -500.0f - 15, 180.0f, 130.0f);
		glBindTexture(GL_TEXTURE_2D, winn);
		drawSquare(-600.0f + (300 * (winner-1) ) - 15, -500.0f+100 - 15, 300.0f, 75.0f);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

}
void setGame();
void drawRunning(){
	glClearDepth(1);
	/* clear the screen */
	c = goPro.getCen();
	e = goPro.getEye();
	GLfloat light_position[] = { e.x, e.y,e.z, 1.0 };
	glClearColor(0.0, 0.0, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glViewport(0, 0, windowWidth, windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, windowWidth / windowHeight, 0.01f, 1000000000000000.0f);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	gluLookAt(e.x, e.y, e.z, c.x, c.y, c.z, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glPopMatrix();
	if (canGo == true) {

		for (int i = 0; i < 4; i++) {

			if (players[i].isConnected()) {
				players[i].preDraw(light_position);
			}
		}
	}
	for (int i = 0; i < stages.size(); i++) {
		stages[i].Draw();
	}

	drawBack();
	drawGUI();
	/* Swap Buffers to Make it show up on screen */
	glutSwapBuffers();
}

void tickRunning() {

	if (lightimer > 0.0f) {
		lightimer -= cTime;
	}
	if (lightimer <= 0.0f) {
		lightimer = 0.07f;
		
		lightning = !lightning;
	}
	living = 0;
	for (int i = 0; i < 4; i++) {
		
		
		if (players[i].isConnected() && players[i].getStatus(c)) {
			living++;
			//std::cout << living << std::endl;
		}
	}
	if (living == 1) {
		for (int i = 0; i < 4; i++) {
			if (players[i].getStatus(c) && players[i].isConnected()) {
				winner = i + 1;
			}
		}
	}
	if (canGo) {
		for (int i = 0; i < 4; i++) {
			pCoord[i] = players[i].getCoord();

		}


		for (int i = 0; i < 4; i++) {
			if (players[i].isConnected()) {
				players[i].tick(keyDown, stages, deltaT, cTime, players);

			}
		}
		goPro.update(deltaT);
		for (int i = 0; i < stages.size(); i++) {
			stages[i].isValid(c);

		}
		if (stages[currentStage].isOff()) {
			currentStage++;
			int type = rand() % 4;
			stages.push_back(preload[type]);

			stages[stages.size() - 1].reUse(stages[stages.size() - 2].getOff());


			goPro.cameraAddPoints(type, stages[stages.size() - 1].getO());
		}

	}
	if (canGo) {
		if ((!(players[0].getStatus(c)) || !players[0].isConnected()) && (!(players[1].getStatus(c)) || !players[1].isConnected()) && (!(players[2].getStatus(c)) || !players[2].isConnected()) && (!(players[3].getStatus(c)) || !players[3].isConnected()) && canGo) {
			canGo = false;
			for (int i = 0; i < 4; i++) {
				players[i].notReady();
			}
		}
	}
	if (canGo == false) {
		if (players[0].Start() && players[1].Start() && players[2].Start() && players[3].Start() && canGo == false) {
			game = charselect;
			PlaySound(TEXT("Inevitable.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		}
	}

}
void drawMenu() {
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
	if (pretimer > 0.0f) {
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
		drawSquare(0.0f-100, -300, 200, 100);
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
		PlaySound(TEXT("Inevitable.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
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


	if (((pChar[0] > 0&& bStart[0])||!players[0].isConnected())&& ((pChar[1] > 0 && bStart[1]) || !players[1].isConnected()) && ((pChar[2] > 0 && bStart[2]) || !players[2].isConnected()) && (((pChar[3] > 0 && bStart[3]) || !players[3].isConnected()))) {
		players[0].setCharacter(pChar[0]);
		players[1].setCharacter(pChar[1]);
		players[2].setCharacter(pChar[2]);
		players[3].setCharacter(pChar[3]);
		PlaySound(TEXT("Inevitable2.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		for (int i = 0; i < 4; i++) {
			bStart[i] = false;
			std::string str = players[i].characterName() + ".png";
			char *cstr = new char[str.length() + 1];
			strcpy(cstr, str.c_str());
			glBindTexture(GL_TEXTURE_2D, pL[i]);
			pL[i] = ilutGLLoadImage(cstr);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindTexture(GL_TEXTURE_2D, pD[i]);
			str = players[i].characterName() + "_dead.png";
			cstr = new char[str.length() + 1];
			strcpy(cstr, str.c_str());
			pD[i] = ilutGLLoadImage(cstr);
			glBindTexture(GL_TEXTURE_2D, 0);
			delete[] cstr;

		}

		deltaT = 0;
		oldTimeSinceStart = timeSinceStart;
		goPro.reset();
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
		players[0].reset(deltaT, goPro.getFirst());
		players[1].reset(deltaT, goPro.getFirst());
		players[2].reset(deltaT, goPro.getFirst());
		players[3].reset(deltaT, goPro.getFirst());
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
	drawSquare(-(1920 / 2), 0, 1920/2, 1080/2);
	if (bStart[0]) {
		glBindTexture(GL_TEXTURE_2D, check);
		drawSquare(-(1920 / 2)+30, 0+20, 100, 100);
	}
	bindPortrait(pChar[1]);
	glColor4f(0.5f, 0.5f, 0.5f, 1.0f); //ensure no color distortion
	drawSquare(0, 0, 1920 / 2, 1080 / 2);
	if (bStart[1]) {
		glBindTexture(GL_TEXTURE_2D, check);
		drawSquare( 30, 0 + 20, 100, 100);
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
		drawSquare( 30, -(1080 / 2) + 20, 100, 100);
	}
	glBindTexture(GL_TEXTURE_2D, border);
	glColor4f(0.5f, 0.5f, 0.5f, 1.0f); //ensure no color distortion
	drawSquare(-(1920/2),-(1080/2),1920,1080);
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
		drawRunning();
	}
	if (game == charselect) {
		drawCharSelect();
	}
	if (game == menu) {
		drawMenu();
	}
	if (keyDown[27]) {
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

}

int main(int argc, char **argv)
{
	srand(time(NULL));
	/* initialize the window and OpenGL properly */
	GetDesktopResolution(windowWidth, windowHeight);
	glutInit(&argc, argv);
	ShowCursor(false);
		glutInitWindowSize(windowWidth, windowHeight);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA| GLUT_ALPHA);
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
	glMaterialfv(GL_FRONT,GL_EMISSION, mat_ambient);
	glLightfv(GL_LIGHT0,GL_SPECULAR,mat_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, mat_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, mat_diffuse);
	for (int i = 0; i < 4; i++) {
		Player pl;
		
		players.push_back(pl);
		players[i].set(i + 1);
	}
	
	
	

	setGame();
			/* start the event handler */
	glutMainLoop();
	return 0;
}

void setGame() {
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, backText);
	backText = ilutGLLoadImage("background.png");
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_2D, outl);
	outl = ilutGLLoadImage("outline.png");
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_2D, out2);
	out2 = ilutGLLoadImage("outline1.png");
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_2D, out3);
	out3 = ilutGLLoadImage("outline2.png");
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_2D, backeer);
	backeer = ilutGLLoadImage("Ground1.png");
	glBindTexture(GL_TEXTURE_2D, 0);
	backer.load("Ground.obj");
	glBindTexture(GL_TEXTURE_2D, cont);
	cont = ilutGLLoadImage("start.png");
	glBindTexture(GL_TEXTURE_2D, border);
	border = ilutGLLoadImage("charoverlay.png");
	glBindTexture(GL_TEXTURE_2D, c1);
	c1 = ilutGLLoadImage("brick_sel.png");
	glBindTexture(GL_TEXTURE_2D, c2);
	c2 = ilutGLLoadImage("lyn_sel.png");
	glBindTexture(GL_TEXTURE_2D, c3);
	c3 = ilutGLLoadImage("ozean_sel.png");
	glBindTexture(GL_TEXTURE_2D, c4);
	c4 = ilutGLLoadImage("zeit_sel.png");
	glBindTexture(GL_TEXTURE_2D, imagineDragons);
	imagineDragons = ilutGLLoadImage("winner.png");
	glBindTexture(GL_TEXTURE_2D, winn);
	winn = ilutGLLoadImage("winnerfont.png");
	glBindTexture(GL_TEXTURE_2D, check);
	check = ilutGLLoadImage("yes.png");
	


	glBindTexture(GL_TEXTURE_2D, title);
	title = ilutGLLoadImage("title.png");

	glBindTexture(GL_TEXTURE_2D, present);
	present = ilutGLLoadImage("presents.png");

	glBindTexture(GL_TEXTURE_2D, remote);
	remote = ilutGLLoadImage("xbox.png");


	glBindTexture(GL_TEXTURE_2D, star);
	star = ilutGLLoadImage("startmenu.png");

	glBindTexture(GL_TEXTURE_2D, exits);
	exits = ilutGLLoadImage("exit.png");

	glBindTexture(GL_TEXTURE_2D, sele);
	sele = ilutGLLoadImage("lselect.png");
	
	glBindTexture(GL_TEXTURE_2D, 0);
	
	for (int i = 0; i < 4; i++) {
		Stage pre;
		pre.set(i + 1);
		preload.push_back(pre);

	}
	goPro.load(preload.size());


	stages.push_back(preload[0]);
	stages[0].reUse(0.0f);
	goPro.cameraAddPoints(0, stages[0].getO());
	for (int i = 0; i < 6; i++) {
		int type = rand() % 4;
		stages.push_back(preload[type]);

		stages[i + 1].reUse(stages[i].getOff());



		goPro.cameraAddPoints(type, stages[i + 1].getO());
	}




}