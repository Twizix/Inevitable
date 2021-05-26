#include "object.h"

float degToRad = 3.14159f / 180.0f;
float radToDeg = 180.0f / 3.14159f;
void DrawVector(float* origin, float* vectorToDraw, float lineWidth, float *colour)
{
	GLboolean lightingEnabled;
	glGetBooleanv(GL_LIGHTING, &lightingEnabled);

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glLineWidth(lineWidth);
	glBegin(GL_LINES);
	if (colour != nullptr)
		glColor3fv(colour);
	glVertex3fv(origin);
	glVertex3f(origin[0] + vectorToDraw[0], origin[1] + vectorToDraw[1], origin[2] + vectorToDraw[2]);
	glEnd();
	glLineWidth(1.0f);

	glEnable(GL_LIGHT0);
	if (lightingEnabled)
		glEnable(GL_LIGHTING);
}

void DrawVector(glm::vec3 origin, glm::vec3 vectorToDraw, float lineWidth, glm::vec3 colour)
{
	DrawVector(&origin[0], &vectorToDraw[0], lineWidth, &colour[0]);
}

bool detectCollision(AABB a, AABB b)
{
	return (a.min.x <= b.max.x && a.max.x >= b.min.x) &&
		(a.min.y <= b.max.y && a.max.y >= b.min.y) &&
		(a.min.z <= b.max.z && a.max.z >= b.min.z);
}

bool Player::getStatus(glm::vec3 cam)
{
	if (playerCoord.y < cam.y - 120.0f)
	{
		isIn = false;
		return false;
	}
	else if (playerCoord.x < cam.x - 50.0f)
	{
		isIn = false;
		return false;
	}
	return true;
}

Player::Player(int pNum)
{
	//pRay.dir = glm::vec3(0.0f, -1.0f, 0.0f);
	//pRay.len = 0.16f;
}

Player::~Player() {}
Player::Player() {}

void Player::refreshGamePad()
{
	pad.Refresh();
};

bool Player::Start()
{	
	if (!connection)
	{
		return true;
	}
	if (hasEnd&&pad.sButton && !ready)
	{
		ready = true;
		hasEnd = false;
	}
		return ready;
}

void Player::notReady()
{	
		ready = false;
}

bool Player::isConnected()
{
	return connection;
}

void Player::reset(float time, glm::vec3 start)
{
	isIn = true;
	hasEnd = true;
	playerCoord = start;
	playerCoord.y += 20.0f;
	bVec= glm::vec3(0.0f, 0.0f, 0.0f);
	blinkProgress = false;
	jumpVec = glm::vec3(0.0f, -0.00001f, 0.0f);
	speed = 0.0f;
	airSpeed = 0.0f;
	oldfallTime = time;
	xAir = 0.0f;
	yAir = 0.0f;
	forwardVec = glm::vec3(1.0f, 0.0f, 0.0f);
	bCd = 10.0f;
	lynspin = 0.0f;
	speedBoost = 0.0f;
	playerCharacter.endAttack();

}

Character Player::getCharacter()
{
	return playerCharacter;
}

void Player::tick(int keyDown[], std::vector<Stage> stagerl, float time, float cTime, std::vector<Player>& p)
{
	//	mapAware = m;
	stager = stagerl;
	preI = 0;
	if (bCd > 0.0f)
	{
		bCd -= cTime;
	}
	if (lynspin > 0.0f)
	{
		lynspin -= cTime;
	}
	if (knockTimer > 0.0f)
	{
		knockTimer -= cTime;
	}
	if (isIn)
	{
		for (int i = 0; i < stager.size(); i++)
		{
			if (stager[i].valid(playerCoord))
			{
				stage = stager[i];
				if (i < stager.size() - 2)
				{
					preI = i + 1;
				}
				else if (i == stager.size() - 1)
				{
					preI = i;
				}
			}
		}
		glm::vec3 forVec(0.0f, 0.0f, 1.0f);

		playerCharacter.tick();
		found = false;
		found2 = false;
		found3 = false;
		found4 = false;

		if (knocked&&knockTimer > 0.0f)
		{
			speed = 0.9;
		}
		if (knocked&&knockTimer <= 0.0f)
		{
			knocked = false;
		}
		if (!knocked)
		{
			if (pad.leftStickX > 0.0f || pad.leftStickX < 0.0f)
			{
				forwardVec.z = pad.leftStickX;
				speed = 0.7f;
			}
			if (pad.leftStickY > 0.0f || pad.leftStickY < 0.0f)
			{
				forwardVec.x = pad.leftStickY;
				speed = 0.7f;
			}
			forwardVec = glm::normalize(forwardVec);

			if ((pad.leftStickY > 0.0f || pad.leftStickY < 0.0f) || (pad.leftStickX > 0.0f || pad.leftStickX < 0.0f))
			{
				float dot = forVec.x*forwardVec.x + forVec.z*forwardVec.z;
				float	det = forVec.x*forwardVec.z - forVec.z*forwardVec.x;
				rotAngle = -(atan2(det, dot) * radToDeg);

				if (rotAngle < 0.0f)
				{
					rotAngle = 180.0f + (180.0f + rotAngle);
				}

			}
			else
			{
				playerCharacter.fuckDown();
				speed = 0.0f;
			}
		}
		for (int i = 0; i < stage.getTriSize(); i++)
		{

			if (intersect3D_RayTriangle(playerCoord, glm::vec3(0.0f, -5.00f, 0.0f), ch, stage.getTriangle(i), point, stage.getO()) && found == false)
			{
				if (playerCoord.y != point.y + 5.0f)
				{
					playerCoord.y = point.y + 4.9f;

				}
				jumpPlane = i;
				glm::vec3	planeVec = stage.getTriangle(i).normal;

				planeVec = glm::normalize(planeVec);

				if (!glm::any(glm::isnan(planeVec)) && planeVec.y != 0.0f)
				{
					forwardVec.y = -(((planeVec.x*forwardVec.x) + (planeVec.z*forwardVec.z)) / (planeVec.y));

					if (!glm::any(glm::isnan(forwardVec)))
					{
						forwardVec = glm::normalize(forwardVec);
					}
				}

				found = true;
				inAir = false;
				jumped = false;
			}
		}
		if (pad.aButton && ((!inAir || shoudGrace) || (jump)))
		{
			xAir = 0.0f;
			yAir = 0.0f;

			shoudGrace = false;
			onLand = false;
			if (jumpVec.y > 0.0f)
			{
				jumpVec.y = 1.3f;
			}
			else 	if (jumpVec.y <= 0.0f)
			{
				jumpVec.y = 0.9f;
			}
			airSpeed = (speed + speedBoost);
			jumped = true;
			found = false;

			if ((pad.leftStickY > 0 || pad.leftStickY < 0) || (pad.leftStickX > 0 || pad.leftStickX < 0))
			{
				airMove = true;
				xAir = forwardVec.x;
				yAir = forwardVec.z;
			}
		}
		if (found == false && !inAir)
		{
			inAir = true;
			if (!pad.aButton)
			{
				shoudGrace = true;
			}
			if (!jumped)
			{
				airSpeed = 0.2;
			}
			else if (jumped)
			{
				airSpeed = (speed + speedBoost);
			}
			fallTime = 0;

			oldfallTime = time;

			if ((pad.leftStickY > 0 || pad.leftStickY < 0) || (pad.leftStickX > 0 || pad.leftStickX < 0))
			{
				airMove = true;
				xAir = forwardVec.x;
				yAir = forwardVec.z;

			}
			else
			{
				airMove = false;
			}

			if (!pad.aButton)
			{
				jumpVec.y = 0.0f;
			}

		}
		if (shoudGrace&&gracePeriod < 0.03f)
		{
			gracePeriod = (fallTime / 1000.0f);
		}
		if (gracePeriod > 0.03f)
		{
			shoudGrace = false;
			gracePeriod = 0.0f;
		}

		if (!inAir)
		{
			wallReJump = false;
			jump = false;
			glm::vec3 pois;

			for (int i = 0; i < stage.getTriSize(); i++)
			{
				if (intersect3D_RayTriangle(playerCoord, 2.5f*forwardVec, pois, stage.getTriangle(i), point2, stage.getO()) && found2 == false)
				{
					if (onLand&&jumpVec.y <= 0.0f)
					{
						onLand = false;
						playerCoord = point2 - (2.5f*forwardVec);
					}
					glm::vec3	planeVec = stage.getTriangle(i).normal;

					planeVec = glm::normalize(planeVec);

					if (fabs(forwardVec.x) - fabs(planeVec.x) > 0)
					{
						forwardVec.x = forwardVec.x + planeVec.x;
					}
					else
					{
						forwardVec.x = 0.0f;
					}
					if (fabs(forwardVec.y) - fabs(planeVec.y) > 0)
					{
						forwardVec.y = forwardVec.y + planeVec.y;
					}
					else
					{
						forwardVec.y = 0.0f;
					}
					if (fabs(forwardVec.z) - fabs(planeVec.z) > 0)
					{
						forwardVec.z = forwardVec.z + planeVec.z;
					}
					else
					{
						forwardVec.z = 0.0f;
					}
					found2 = true;
				}
			}
			if (onLand)
			{
				onLand = false;
			}
		}

		if (!inAir && ((pad.leftStickY > 0 || pad.leftStickY < 0) || (pad.leftStickX > 0 || pad.leftStickX < 0)))
		{
			if ((forwardVec.x > 0.0f || forwardVec.x < 0.0f) || (forwardVec.y > 0.0f || forwardVec.y < 0.0f) || (forwardVec.z > 0.0f || forwardVec.z < 0.0f))
			{
				playerCoord += ((speed + speedBoost)*forwardVec);
			}
		}
		if (inAir && ((pad.leftStickY > 0 || pad.leftStickY < 0) || (pad.leftStickX > 0 || pad.leftStickX < 0)))
		{
			if (airSpeed == 0)
			{
				airSpeed = 0.5 + speedBoost;
			}
			xAir = forwardVec.x;
			yAir = forwardVec.z;
		}
		if (inAir)
		{
			fallTime = time - oldfallTime;

			if (jumpVec.y < -3.0f)
			{
				jumpVec.y = -3.0f;
			}
			else
			{
				jumpVec.y += -(((9.8f))*(fallTime / 1000.0f)) / 60.0f;
			}
		}

		pumpVec = forwardVec*airSpeed;
		pumpVec.y = 0.0f;

		if (inAir)
		{
			bool dontGo = false;
			glm::vec3 pois3;

			for (int i = 0; i < stage.getTriSize(); i++)
			{
				if (intersect3D_RayTriangle(glm::vec3(playerCoord.x, playerCoord.y - 5.0f, playerCoord.z), 2.5f*pumpVec, pois3, stage.getTriangle(i), point4, stage.getO()) && found4 == false)
				{
					stage.setI(i);

					glm::vec3	planeVec = stage.getTriangle(i).normal;

					planeVec = glm::normalize(planeVec)*airSpeed;

					if (i != jumpPlane)
					{
						if (jumpVec.y <= 0.0f)
						{
							onLand = true;
						}
						wallReJump = true;
					}

					pumpVec.x = pumpVec.x + planeVec.x;
					pumpVec.z = pumpVec.z + planeVec.z;
					found4 = true;
				}
			}
			if (!found4)
			{
				onLand = false;
			}
		}
		if (wallReJump&&found4 == false)
		{
			jump = true;
			wallReJump = false;
		}
		else
		{
			jump = false;
		}

		if (found4 == false)
		{
			if (inAir)
			{
				glm::vec3 pois2;
				for (int i = 0; i < stage.getTriSize(); i++)
				{
					if (intersect3D_RayTriangle(playerCoord, glm::vec3(0.0f, 4.00f, 0.0f), pois2, stage.getTriangle(i), point3, stage.getO()) && found3 == false)
					{
						glm::vec3	planeVec = stage.getTriangle(i).normal;

						planeVec = glm::normalize(planeVec);

						if (fabs(pumpVec.x) - fabs(planeVec.x) > 0)
						{
							pumpVec.x = pumpVec.x + planeVec.x;
						}
						else
						{
							pumpVec.x = 0.0f;
						}

						if (jumpVec.y > 0)
						{
							jumpVec.y = 0.0f;
						}

						if (fabs(pumpVec.z) - fabs(pumpVec.z) > 0)
						{
							pumpVec.z = pumpVec.z + planeVec.z;
						}
						else
						{
							pumpVec.z = 0.0f;
						}

						found3 = true;
					}
				}
			}
		}

		if (inAir)
		{
			playerCoord += jumpVec + (pumpVec);
		}

		playerCharacter.fuckUp(speed + speedBoost);

		if (playerCharacter.getChar() == 1)
		{
			BrickAbility();
		}

		if (playerCharacter.getChar() == 2)
		{
			LynAbility(p);
		}
		if (playerCharacter.getChar() == 3)
		{
			OzenAbility();
		}

		if (playerCharacter.getChar() == 4)
		{
			ZeitAbility(p);
		}
	}
}
void Player::knock(glm::vec3 dir)
{
	forwardVec.x = dir.x;
	forwardVec.z = dir.z;
	knocked = true;
	knockTimer = 0.5;
}

bool Player::isHit()
{
	return knocked;
}

int Player::getPlayerNum()
{
	return playerNumber;
}

void Player::LynAbility(std::vector<Player>& p)
{
	if (bCd <= 0.0f&&pad.r1Button&&blinkProgress == false)
	{
		blinkProgress = true;
		lynspin = 3.0f;
		playerCharacter.startAttack();
	}
	if (bCd <= 0.0f && lynspin > 0.0f&&blinkProgress == true)
	{
		for (int i = 0; i < 4; i++)
		{
			if (p[i].getPlayerNum() != playerNumber&&!p[i].isHit()&&!p[i].isInvul())
			{
				float lenny;
				glm::vec3 sensor;
				sensor = p[i].getCoord()-playerCoord;
				lenny = glm::length(sensor);
				if (lenny < 4.0f&&lenny>0.0f)
				{
					p[i].knock(glm::normalize(sensor));
				}
			}
		}
	}

	if (bCd <= 0.0f && lynspin<=0.0f&&blinkProgress == true)
	{
		playerCharacter.endAttack();
		bCd =7.0f;
		blinkProgress = false;
	}
}
bool Player::usedAbility()
{
	if(bCd > 0.0f)
	{
		return true;
	}
	if (bCd <= 0.0f)
	{
		return false;
	}
}

Gamepad Player::getPad()
{
	return pad;
}

void Player::BrickAbility()
{
	if (bCd <= 0.0f&&!invul&&pad.r1Button)
	{
		lynspin = 2.0f;
		speedBoost = 0.2f;
		invul = true;
	}
	if (bCd <= 0.0f&&lynspin<=0.0f&&invul)
	{
		bCd = 3.0f;
		speedBoost = 0.0f;
		invul = false;
	}
}

void Player::ZeitAbility(std::vector<Player>& p)
{
	if (bCd <= 0.0f && !blinkProgress&&pad.r1Button)
	{
		lynspin = 1.5f;
		for (int i = 0; i < 4; i++)
		{
			if (p[i].getPlayerNum() != playerNumber && !p[i].isInvul())
			{
				p[i].setBoost(-0.4f);
			}
		}
		blinkProgress = true;
	}
	if (bCd <= 0.0f&&lynspin <= 0.0f&&blinkProgress) 
	{
		bCd = 15.0f;
		
		blinkProgress = false;
		for (int i = 0; i < 4; i++) 
		{
			if (p[i].getPlayerNum() != playerNumber && !p[i].isInvul())
			{
				p[i].setBoost(0.0f);
			}
		}
	}
}

void Player::setBoost(float s)
{
	speedBoost = s;
}

void Player::OzenAbility()
{

	glm::vec3 blinkPo;
	glm::vec3 bo;
	glm::vec3 blinker;
	if (bCd <= 0.0f&&pad.r1Button)
	{
		blinkProgress = true;
		bool founder = false;
		float oldLength = 9999999.0f;
		float length;

		if (!inAir)
		{
			for (int i = 0; i < stage.getTriSize(); i++)
			{
				if (intersect3D_RayTriangle(playerCoord, 30.0f*forwardVec, bo, stage.getTriangle(i), blinkPo, stage.getO()) && founder == false)
				{
					length = std::fabs(glm::length(blinkPo - playerCoord));

					if (length < oldLength)
					{
						oldLength = length;
						blinker = blinkPo;
					}
					founder = true;
				}
			}
			if (founder == false)
			{
				for (int i = 0; i < stager[preI].getTriSize(); i++)
				{
					if (intersect3D_RayTriangle(playerCoord, 30.0f*forwardVec, bo, stager[preI].getTriangle(i), blinkPo, stager[preI].getO()) && founder == false)
					{
						length = std::fabs(glm::length(blinkPo - playerCoord));

						if (length < oldLength)
						{
							oldLength = length;
							blinker = blinkPo;
						}
						founder = true;
					}
				}
			}
		}
		if (inAir)
		{
			for (int i = 0; i < stage.getTriSize(); i++)
			{
				if (intersect3D_RayTriangle(playerCoord, 30.0f*forwardVec, bo, stage.getTriangle(i), blinkPo, stage.getO()))
				{
					length = std::fabs(glm::length(blinkPo - playerCoord));

					if (length < oldLength)
					{
						oldLength = length;
						blinker = blinkPo;
					}
					founder = true;
				}
			}
			if (founder == false)
			{
				for (int i = 0; i < stager[preI].getTriSize(); i++)
				{
					if (intersect3D_RayTriangle(playerCoord, 30.0f*forwardVec, bo, stager[preI].getTriangle(i), blinkPo, stager[preI].getO()))
					{
						length = std::fabs(glm::length(blinkPo - playerCoord));
						if (oldLength > length)
						{
							oldLength = length;
							blinker = blinkPo;
						}
						founder = true;
					}
				}
			}
		}
		if (founder == false) 
		{
			bo = playerCoord + forwardVec*30.0f;
		}
		if (founder == true)
		{
			bo = blinker - (2.5f*forwardVec);
		}
		bVec = bo;
	}
	if (bCd <= 0.0f && !pad.r1Button&&blinkProgress == true)
	{
		bCd = 3.0f;
		blinkProgress = false;
		Blink(bVec);
	}
}

void Player::set(int i)
{
	pad.setPort(i);
	playerNumber =i;
	pRay.p0 = playerCoord;
	connection = pad.CheckConnection();
}

std::string Player::characterName()
{
	if (playerCharacter.getChar() == 1)
	{
		return "brick";
	}
	if (playerCharacter.getChar() == 2)
	{
		return "lyn";
	}
	if (playerCharacter.getChar() == 3)
	{
		return "ozean";
	}
	if (playerCharacter.getChar() == 4)
	{
		return "zeit";
	}

}

void Player::setCharacter(int c)
{
	playerCharacter.setCharacter(c);
	shade.load("assets/models/Shadow.obj");
	glBindTexture(GL_TEXTURE_2D, shadow);
	shadow = ilutGLLoadImage("assets/images/Shadow.png");
	glBindTexture(GL_TEXTURE_2D, tex);

	if (playerCharacter.getChar() == 1)
	{
		tex = ilutGLLoadImage("assets/images/BrickMap.png");
		glBindTexture(GL_TEXTURE_2D, Goldtex);
		Goldtex = ilutGLLoadImage("assets/images/GoldenBoy.png");
	}

	if (playerCharacter.getChar() == 2)
	{
		tex = ilutGLLoadImage("assets/images/LynMap.png");
	}

	if (playerCharacter.getChar() == 3)
	{
		tex = ilutGLLoadImage("assets/images/OzeanMap.png");
	}

	if (playerCharacter.getChar() == 4)
	{
		tex = ilutGLLoadImage("assets/images/ZeitFace.png");
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}
void Player::Blink(glm::vec3 toBlink)
{
	playerCoord = toBlink;
	speed = 0.0f;
	airSpeed = 0.0f;
}
bool Player::isInvul()
{
	return invul;
}
void Player::preDraw(float lpos[])
{
	if (isIn)
	{
		glPushMatrix();
		glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
		glTranslatef(playerCoord.x, playerCoord.y, playerCoord.z);
		glRotatef(rotAngle, 0.0f, 1.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, tex);
		if (invul) {
			glBindTexture(GL_TEXTURE_2D, Goldtex);
		}
		playerCharacter.Draw();
		glBindTexture(GL_TEXTURE_2D, 0);
		glPopMatrix();
		if (blinkProgress&&playerCharacter.getChar()==3) {
			glDisable(GL_LIGHT0);
			glDisable(GL_LIGHTING);
			glPushMatrix();
			glClearColor(1.0, 1.0f, 1.0f, 0.0f);
			glColor4f(0.0f, 1.0f, 0.0f, 0.2);
			glTranslatef(bVec.x, bVec.y, bVec.z);
			glRotatef(rotAngle, 0.0f, 1.0f, 0.0f);
			playerCharacter.Draw();
			glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
		//	glClearColor(0.0, 0.0, 0.0f, 0.0f);
			glPopMatrix();
			glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		}
	}
}

glm::vec3 Player::getCoord()
{
	return playerCoord;
}

#define SMALL_NUM   0.00000001 

int intersect3D_RayTriangle(glm::vec3 O, glm::vec3 D, glm::vec3 &len, Triangle T, glm::vec3 &I, float xOff)
{
	glm::vec3    u, v, n;              // triangle vectors
	glm::vec3    dir, w0, w;           // ray vectors
	float     r, a, b;              // params to calc ray-plane intersect

									// get triangle edge vectors and plane normal
	T.V0.x += xOff;
	T.V1.x += xOff;			// get triangle edge vectors and plane normal
	T.V2.x += xOff;
	u = T.V1 - T.V0;
	v = T.V2 - T.V0;
	
	n = glm::cross(u , v);              // cross product
	len = n;
	if (n == (glm::vec3)0)             // triangle is degenerate
		return 0;                  // do not deal with this case
	
	dir = D;              // ray direction vector
	//std::cout <<n.x << ", " << n.y << ", " << n.z << std::endl;
	//dir=glm::normalize(dir);
	w0 =O - T.V0;
	a = -glm::dot(n, w0);
	b = glm::dot(n, dir);
	if (fabs(b) < SMALL_NUM) // ray is  parallel to triangle plane
	{     
		if (a == 0)                 // ray lies in triangle plane
			return 0;
		else return 0;              // ray disjoint from plane
	}
	
	// get intersect point of ray with triangle plane
	r = a / b;
	if (r < 0.0f)                    // ray goes away from triangle
		return 0;                   // => no intersect
	if (r > 1.0f)                    // ray goes away from triangle
		return 0;     						// for a segment, also test if (r > 1.0) => no intersect

	I = O + r * dir;            // intersect point of ray and plane

									// is I inside T?
	float    uu, uv, vv, wu, wv, Di;
	uu = glm::dot(u, u);
	uv = glm::dot(u, v);
	vv = glm::dot(v, v);
	w = I - T.V0;
	wu = glm::dot(w, u);
	wv = glm::dot(w, v);
	Di = uv * uv - uu * vv;

	// get and test parametric coords
	float s, t;
	s = (uv * wv - vv * wu) / Di;
	if (s < 0.0f || s > 1.0f)         // I is outside T
	{
		return 0;
	}
	t = (uv * wu - uu * wv) / Di;
	if (t < 0.0f || (s + t) > 1.0f)  // I is outside T
	{
		return 0;
	}
	return 1;                       // I is in T
}

void Stage::set(int t)
{
	type =t;
	stageModel.prepStage();
	stageModel.load("assets/models/cell"+ std::to_string(type)+".obj");
	begin = stageModel.getBeg();
	end= stageModel.getEnd();
	glBindTexture(GL_TEXTURE_2D, tex);
	tex = ilutGLLoadImage("assets/images/celltext.png");
	glBindTexture(GL_TEXTURE_2D, 0);
	
}

float Stage::getOff()
{
	return offset+end+10.0f;
}

void Stage::reUse(float off)
{
	if (off == 0.0f) {
		offset = off;
	}
	else if(off>0.0f){
		offset = off + fabs(begin);
	}
}

Stage::Stage() {}
Stage::~Stage() {}

int Stage::getTriSize()
{
	return stageModel.getTSize();
}

Triangle Stage::getTriangle(int pos)
{
	return stageModel.triangle(pos);
}

void Stage::Draw()
{
	if (draw)
	{
		glPushMatrix(); //todo: push 4x4 transformatrix matrix
		glTranslatef(offset, 0.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, tex);

		stageModel.draw();
		glBindTexture(GL_TEXTURE_2D, 0);
		glPopMatrix();
	}
}
bool Stage::valid(glm::vec3 p) { if (p.x > offset + begin&&p.x < offset + end)
{	
	return true;
	}
	else  if (p.x < offset + begin||p.x > offset + end) {
		return false;
	} 

}

float Stage::getO()
{
	return offset;
}

void Stage::isValid(glm::vec3 c)
{ 
	
	if (c.x - 120.0f > offset + end)
	{
		draw = false;
	}
	else
	{
		draw = true;
	}

}
bool Stage::isOff()
{
	return !draw;

}
void Stage::setI(int i)
{
	stageModel.setP(i);
}

int Stage::getT()
{
	return type;
}

#define EPSILON 0.000001

int triangle_intersection(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 O, glm::vec3 D, float* out)
{
	glm::vec3 e1, e2;//edges
	glm::vec3 P, Q, T;
	float det, inv_det, u, v;
	float t;
	e1 = v2 - v1;
	e2 = v3 - v1;
	
	P=glm::cross(D,e2);

	det = glm::dot(e1,P);

	if (det > -EPSILON&&det < EPSILON)
	{
		return 0;
	}

	inv_det = 1.0f / det;
	
	T = O - v1;

	u = glm::dot(T, P)*inv_det;

	if (u<0.0f || u>1.0f)
	{
		return 0;
	}
	Q = glm::cross(T, e1);
	
	v=glm::dot(D,Q) *inv_det;

	if (v<0.0f || u + v>1.0f)
	{
		return 0;
	}

	t = glm::dot(e2, Q)*inv_det;
	if (t > EPSILON)
	{
		*out = t;
		return 1;
	}


	return 0;
}

Camera::Camera() {}
Camera::~Camera() {}

glm::vec3 Camera::getFirst()
{
	return center[0];
}

void Camera::load(float l)
{
	for (int i = 0; i < l; i++)
	{
		float vx;
		float vy;
		float vz;
		std::vector<glm::vec3> temp;
		std::string line;
		std::ifstream file("assets/models/cell" + std::to_string(i+1) + ".txt");
		if (file.fail())
		{
			return;
		}
		while (!file.eof())
		{
			std::getline(file, line);
			sscanf(line.c_str(), "%f %f %f", &vx, &vy, &vz);
			temp.push_back(glm::vec3(vx, vy, vz));
		}
		loader[i]=temp;
		file.close();
	}
}

glm::vec3 Camera::Lerp(glm::vec3 v1, glm::vec3 v2)
{
	glm::vec3 finishVec;
	 xDtoF =  center[segment + 1].x-center[segment].x ;
	t = distance / xDtoF;
	finishVec.x = v1.x + distance;
	finishVec.y = ((1.0f - t)*v1.y) + (t*v2.y);
	finishVec.z = ((1.0f - t)*v1.z) + (t*v2.z);
	return finishVec;
}

void Camera::cameraAddPoints(float v,float off)
{
	std::vector<glm::vec3> temp =loader[v];
	for (int i = 0; i < temp.size(); i++)
	{
		center.push_back(glm::vec3(temp[i].x+off, temp[i].y , temp[i].z));
		eye.push_back(glm::vec3(temp[i].x - 30.0f+off, temp[i].y + 50.0f, temp[i].z));
	}
}

void Camera::setSpeed(float i)
{
	speed = i;
}

void Camera::reset()
{
	segTime = 1.0f;
	t = 0.0f;
	distance = 0.0f;
	segment = 0.0f;
	center.clear();
	eye.clear();
}
void Camera::update(float time)
{
	if (segment < center.size()-1 && t >= 1.0f)
	{
		segment++;
		distance = 0.0f;
		segTime = time;
	}
	distance += speed;
}

glm::vec3 Camera::getEye()
{
	return Lerp(eye[segment], eye[segment+1.0f]);
}

glm::vec3 Camera::getCen()
{
	return  Lerp(center[segment], center[segment + 1.0f]);
}