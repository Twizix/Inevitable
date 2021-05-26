
#include "GLMODEL.h"
int please;
GLMODEL::GLMODEL()
{
}
void DrawVector2(float* origin, float* vectorToDraw, float lineWidth, float *colour)
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

void DrawVector2(glm::vec3 origin, glm::vec3 vectorToDraw, float lineWidth, glm::vec3 colour)
{
	DrawVector2(&origin[0], &vectorToDraw[0], lineWidth, &colour[0]);
}
glm::vec3 CalcNormalOfFace(glm::vec3 pPositions[3], glm::vec3 pNormals[3]){
	glm::vec3 p0 = pPositions[1] - pPositions[0];
	glm::vec3 p1 = pPositions[2] - pPositions[0];
	glm::vec3 faceNormal = glm::cross(p0, p1);
	
	
	glm::vec3 vertexNormal = (pNormals[0] + pNormals[1] + pNormals[2]) / 3.0f; // or you can average 3 normals.
	float dotP = glm::dot(faceNormal, vertexNormal);

	return (dotP < 0.0f ? -faceNormal : faceNormal);
	//return ( faceNormal);
}
GLMODEL::~GLMODEL()
{
}
void GLMODEL::setFaces(std::vector <Face> f) {
	faces = f;
}
bool GLMODEL::load(std::string file_path)
{
	//newplane = 0;
	std::ifstream file(file_path);
	//std::ifstream stream("obj.txt");
	std::string line;
	if (file.fail())
	{
		return false;
	}

	int verNum = 0;
	int norNum = 0;
	int facNum = 0;
	int uvsNum = 0;
	int fillery = 0;

	
	while (!file.eof())
	{
		std::getline(file, line);

		if (line.c_str()[0] == 'v') {

			if (line.c_str()[1] == ' ')
			{
				vertices.resize(verNum + 1);

				sscanf(line.c_str(), "v %f %f %f", &vertices[verNum].x, &vertices[verNum].y, &vertices[verNum].z);

				if (stage) {
					if (vertices[verNum].x>bigX) {
						bigX = vertices[verNum].x;
					}
					if (vertices[verNum].x<littleX) {
						littleX = vertices[verNum].x;
					}
				}
				//	std::cout << "vertex " << vertices[verNum].x << "," << vertices[verNum].y << "," << vertices[verNum].z << std::endl;
				verNum += 1;
			}
			else if (line.c_str()[1] == 'n')
			{
				normals.resize(norNum + 1);

				sscanf(line.c_str(), "vn %f %f %f", &normals[norNum].x, &normals[norNum].y, &normals[norNum].z);
				//	std::cout << "normals " << normals[norNum].x << "," << normals[norNum].y << "," << normals[norNum].z << std::endl;
				norNum += 1;
			}
			else if (line.c_str()[1] == 't')
			{
				uvs.resize(uvsNum + 1);

				sscanf(line.c_str(), "vt %f %f", &uvs[uvsNum].u, &uvs[uvsNum].v);
				//	std::cout << "normals " << normals[norNum].x << "," << normals[norNum].y << "," << normals[norNum].z << std::endl;
				uvsNum += 1;
			}
		}
		else if (line.c_str()[0] == 'f')
		{

			faces.resize(facNum + 1);
		
			sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &faces[facNum].vx, &faces[facNum].uvx, &faces[facNum].vnx, &faces[facNum].vy, &faces[facNum].uvy, &faces[facNum].vny, &faces[facNum].vz, &faces[facNum].uvz, &faces[facNum].vnz);
			//std::cout << line.size()<<"faces " << faces[facNum].vx << "//" << faces[facNum].vnx << "," << faces[facNum].vy << "//" << faces[facNum].vny << "," << faces[facNum].vz << "//" << faces[facNum].vnz << std::endl;
		
			/*vertices.push_back(outvertices[faces[facNum].vx - 1]);
			vertices.push_back(outvertices[faces[facNum].vy - 1]);
			vertices.push_back(outvertices[faces[facNum].vz - 1]);
		

			normals.push_back(outnormals[faces[facNum].vx - 1]);
			normals.push_back(outnormals[faces[facNum].vy - 1]);
			normals.push_back(outnormals[faces[facNum].vz - 1]);*/
			if (stage) {
				glm::vec3 pPositions[3];
				glm::vec3 pNormals[3];

				pPositions[0] = glm::vec3(vertices[faces[facNum].vx-1].x, vertices[faces[facNum].vx - 1].y, vertices[faces[facNum].vx - 1].z);
				pPositions[1] = glm::vec3(vertices[faces[facNum].vy-1].x, vertices[faces[facNum].vy - 1].y, vertices[faces[facNum].vy - 1].z);
				pPositions[2] = glm::vec3(vertices[faces[facNum].vz-1].x, vertices[faces[facNum].vz - 1].y, vertices[faces[facNum].vz - 1].z);

				pNormals[0] = glm::vec3(normals[faces[facNum].vnx - 1].x, normals[faces[facNum].vnx - 1].y, normals[faces[facNum].vnx - 1].z);
				pNormals[1] = glm::vec3(normals[faces[facNum].vny - 1].x, normals[faces[facNum].vny - 1].y, normals[faces[facNum].vny - 1].z);
				pNormals[2] = glm::vec3(normals[faces[facNum].vnz - 1].x, normals[faces[facNum].vnz - 1].y, normals[faces[facNum].vnz - 1].z);

		

				faces[facNum].faceNorm = glm::normalize(CalcNormalOfFace(pPositions, pNormals));
				Triangle t;
				t.V0 = pPositions[0];
				t.V1 = pPositions[1];
				t.V2 = pPositions[2];
				t.normal = faces[facNum].faceNorm;
				tries.push_back(t);
			}
					facNum += 1;
		}
	}
	file.close();
	return true;
}
void GLMODEL::setUVs(std::vector <UV> us) {
	uvs = us;
}
std::vector <UV> GLMODEL::getUvs() {
	return uvs;
}
float  GLMODEL::getEnd() { return bigX; }
float  GLMODEL::getBeg() { return littleX; }
void GLMODEL::prepStage() { stage = true; }
Vertex GLMODEL::getVerts(int i) {
	return vertices[i];

}
void GLMODEL::setSize(int size,int n,int b) {
	//vertices.clear();
	vertices.resize(size);
	//normals.clear();
	normals.resize(n);
	uvs.resize(b);
}
Normal GLMODEL::getNorms(int i) {
	return normals[i];

}
void GLMODEL::setVerts(Vertex v,int i) {

	vertices[i]=v;
}
void GLMODEL::setNorms(Normal m,int i) {
	normals[i] = m;

}
std::vector <Face> GLMODEL::getFaces() {
	return faces;

}
int  GLMODEL::getVS() {
	//std::cout << vertices.size();
	return vertices.size();

}
int  GLMODEL::getNS() {
	//std::cout << vertices.size();
	return normals.size();

}
int  GLMODEL::getUS() {
	//std::cout << vertices.size();
	return uvs.size();

}
void GLMODEL::setP(int i) {
	if(i>0)
	newplane = i;
	please = i;
//	std::cout << newplane << std::endl;
	
}
void GLMODEL::draw()
{
	for (int i = 0; i < faces.size(); i++)
	{
		
		//if (faces[i].vnx - 1 > 0 && faces[i].vny - 1 > 0 && faces[i].vnz - 1 > 0 && faces[i].vx - 1 > 0 && faces[i].vy - 1 > 0 && faces[i].vz - 1 > 0) {
		/*if (stage) {
//std::cout << please << std::endl;
			DrawVector2(glm::vec3((vertices[faces[i].vx - 1].x+ vertices[faces[i].vy - 1].x+ vertices[faces[i].vz - 1].x)/3.0f, (vertices[faces[i].vx - 1].y + vertices[faces[i].vy - 1].y + vertices[faces[i].vz - 1].y) / 3.0f, (vertices[faces[i].vx - 1].z + vertices[faces[i].vy - 1].z + vertices[faces[i].vz - 1].z) / 3.0f), 7.0f*tries[i].normal, 4.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
			if (i== please) {
				glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
				glDisable(GL_TEXTURE_2D);
			//	std::cout << newplane << std::endl;
			}

		}*/
			glBegin(GL_TRIANGLE_FAN);
			
			glTexCoord2f(uvs[faces[i].uvx - 1].u, uvs[faces[i].uvx - 1].v);	
			glNormal3f(normals[faces[i].vnx - 1].x, normals[faces[i].vnx - 1].y, normals[faces[i].vnx - 1].z);
			glVertex3f(vertices[faces[i].vx - 1].x, vertices[faces[i].vx - 1].y, vertices[faces[i].vx - 1].z);

			glTexCoord2f(uvs[faces[i].uvy - 1].u, uvs[faces[i].uvy - 1].v);
			glNormal3f(normals[faces[i].vny - 1].x, normals[faces[i].vny - 1].y, normals[faces[i].vny - 1].z);
			glVertex3f(vertices[faces[i].vy - 1].x, vertices[faces[i].vy - 1].y, vertices[faces[i].vy - 1].z);

			glTexCoord2f(uvs[faces[i].uvz - 1].u, uvs[faces[i].uvz - 1].v);
			glNormal3f(normals[faces[i].vnz - 1].x, normals[faces[i].vnz - 1].y, normals[faces[i].vnz - 1].z);
			glVertex3f(vertices[faces[i].vz - 1].x, vertices[faces[i].vz - 1].y, vertices[faces[i].vz - 1].z);

			glEnd();
		/*	if (stage&&i == please) {
				glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
				glEnable(GL_TEXTURE_2D);
			}*/
	
		//}
		/*
		glBegin(GL_TRIANGLE_FAN);
		glNormal3f(normals[i] .x, normals[i].y, normals[i].z);
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
		glNormal3f(normals[i+1].x, normals[i+1].y, normals[i+1].z);
		glVertex3f(vertices[i+1].x, vertices[i+1].y, vertices[i+1].z);
		glNormal3f(normals[i+2].x, normals[i+2].y, normals[i+2].z);
		glVertex3f(vertices[i+2].x, vertices[i+2].y, vertices[i+2].z);
		

		glEnd();
		*/
	}
}
int GLMODEL::getTSize() { return tries.size(); }
Triangle GLMODEL::triangle(int n) {
	return tries[n];
}