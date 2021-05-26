#include "Animation.h"

Vertex CatmullRoll(float t, Vertex p1, Vertex p2, Vertex p3, Vertex p4)
{

	float t2 = t*t;
	float t3 = t*t*t;
	Vertex v; // Interpolated point

			  /* Catmull Rom spline Calculation */

	v.x = ((-t3 + 2 * t2 - t)*(p1.x) + (3 * t3 - 5 * t2 + 2)*(p2.x) + (-3 * t3 + 4 * t2 + t)* (p3.x) + (t3 - t2)*(p4.x)) / 2;
	v.y = ((-t3 + 2 * t2 - t)*(p1.y) + (3 * t3 - 5 * t2 + 2)*(p2.y) + (-3 * t3 + 4 * t2 + t)* (p3.y) + (t3 - t2)*(p4.y)) / 2;
	v.z = ((-t3 + 2 * t2 - t)*(p1.z) + (3 * t3 - 5 * t2 + 2)*(p2.z) + (-3 * t3 + 4 * t2 + t)* (p3.z) + (t3 - t2)*(p4.z)) / 2;
	//std::cout<<"Values of v.x = "<< v.x<< " and v.y = "<<v.y<<std::endl;

	return v;
}
Normal CatmullRoll(float t, Normal p1, Normal p2, Normal p3, Normal p4)
{

	float t2 = t*t;
	float t3 = t*t*t;
	Normal v; // Interpolated point

			  /* Catmull Rom spline Calculation */

	v.x = ((-t3 + 2 * t2 - t)*(p1.x) + (3 * t3 - 5 * t2 + 2)*(p2.x) + (-3 * t3 + 4 * t2 + t)* (p3.x) + (t3 - t2)*(p4.x)) *0.5f;
	v.y = ((-t3 + 2 * t2 - t)*(p1.y) + (3 * t3 - 5 * t2 + 2)*(p2.y) + (-3 * t3 + 4 * t2 + t)* (p3.y) + (t3 - t2)*(p4.y)) *0.5f;
	v.z = ((-t3 + 2 * t2 - t)*(p1.z) + (3 * t3 - 5 * t2 + 2)*(p2.z) + (-3 * t3 + 4 * t2 + t)* (p3.z) + (t3 - t2)*(p4.z)) *0.5f;
	//std::cout<<"Values of v.x = "<< v.x<< " and v.y = "<<v.y<<std::endl;

	return v;
}
KeyFrames::KeyFrames() {}
KeyFrames::~KeyFrames() {}
void KeyFrames::loadFrames(std::string charName, int n) {
	keys.resize(n);
	amountOfFrames = n;
	std::cout << "loading "<<n<<" frames" << std::endl;
	for (int i = 0; i < n; i++) {
		keys[i].load("assets/models/" + charName + std::to_string(i + 1) + ".obj");
	}
}
GLMODEL KeyFrames::getFrame(int i) { return keys[i]; }
int KeyFrames::getAnimSize() { return amountOfFrames - 1; }

std::vector<GLMODEL> KeyFrames::getKeys() { return keys; }

Animation::Animation() {}
Animation::~Animation() {}
void Animation::setAnimation(KeyFrames f, float s) {
	skeys.clear();
	frames = f;

	step = s;
	speed = 1.0f;
	bspeed = speed;
	t = 0.0f;
	keys = frames.getKeys();
	animSize = frames.getAnimSize();
	maxframe = ((float)animSize)*(1.0f / step);
	pointSize = frames.getFrame(0).getVS();
	normSize = frames.getFrame(0).getNS();
	uvSize = frames.getFrame(0).getUS();
	for (int x = 0; x < animSize; x++) {
		for (float y = 0; y <1.0f; y += step) {
			skeys.push_back(getCurrentFrame(x, y));

		}
	}
	std::cout <<skeys.size() << " frames loaded" << std::endl;
}
void Animation::tick() {
	if (t + std::fabs(speed) < maxframe - 1.0f) {
		t += std::fabs(speed);
	}
	else {
		t = 0.0f;
	}
}
bool notEqual(Vertex one, Vertex two) {
	if (one.x == two.x&&one.y == two.y&&one.z == two.z) {

		return false;

	}
	return true;
}
void Animation::changeSpeed(float s) {
	speed = bspeed* s;

}
GLMODEL Animation::getCurrentFrame(int frame, float tp) {
	GLMODEL playerModel;
	playerModel.setSize(pointSize, normSize,uvSize);
	playerModel.setFaces(keys[frame].getFaces());
	playerModel.setUVs(keys[frame].getUvs());
	//std::cout << "here1";
	for (int i = 0; i < pointSize; i++) {

		if (frame == 0) {
			//
			if (notEqual(keys[frame].getVerts(i), keys[frame + 1].getVerts(i))) {
				playerModel.setVerts(CatmullRoll(tp, keys[animSize].getVerts(i), keys[frame].getVerts(i), keys[frame + 1].getVerts(i), keys[frame + 2].getVerts(i)), i);
			}
		}
		else
			if (frame == animSize - 1) {
				if (notEqual(keys[frame].getVerts(i), keys[frame + 1].getVerts(i))) {
					playerModel.setVerts(CatmullRoll(tp, keys[frame - 1].getVerts(i), keys[frame].getVerts(i), keys[frame + 1].getVerts(i), keys[0.0f].getVerts(i)), i);
				}
			}
			else
				if (frame == animSize) {
					if (notEqual(keys[frame].getVerts(i), keys[0.0f].getVerts(i))) {
						playerModel.setVerts(CatmullRoll(tp, keys[frame - 1].getVerts(i), keys[frame].getVerts(i), keys[0.0f].getVerts(i), keys[1.0f].getVerts(i)), i);
					}
				}
		if (frame != animSize&&frame != animSize - 1 && frame != 0) {
			if (notEqual(keys[frame].getVerts(i), keys[frame + 1].getVerts(i))) {
				playerModel.setVerts(CatmullRoll(tp, keys[frame - 1].getVerts(i), keys[frame].getVerts(i), keys[frame + 1].getVerts(i), keys[frame + 2].getVerts(i)), i);
			}
		}
	}
	for (int i = 0; i < normSize; i++) {
		if (frame == 0) {
			//
			playerModel.setNorms(CatmullRoll(tp, keys[animSize].getNorms(i), keys[frame].getNorms(i), keys[frame + 1].getNorms(i), keys[frame + 2].getNorms(i)), i);
		}
		else
			if (frame == animSize - 1) {
				playerModel.setNorms(CatmullRoll(tp, keys[frame - 1].getNorms(i), keys[frame].getNorms(i), keys[frame + 1].getNorms(i), keys[0.0f].getNorms(i)), i);
			}
			else
				if (frame == animSize) {
					playerModel.setNorms(CatmullRoll(tp, keys[frame - 1].getNorms(i), keys[frame].getNorms(i), keys[0.0f].getNorms(i), keys[1.0f].getNorms(i)), i);
				}
		if (frame != animSize&&frame != animSize - 1 && frame != 0) {
			playerModel.setNorms(CatmullRoll(tp, keys[frame - 1].getNorms(i), keys[frame].getNorms(i), keys[frame + 1].getNorms(i), keys[frame + 2].getNorms(i)), i);
		}


	}

	return playerModel;

}

GLMODEL Animation::getModel() {

	return skeys[t];
}
GLMODEL Animation::getStaticModel(int i) {
	return frames.getFrame(i);

}




void Animation::reset() {
	t = 0.0f;
}