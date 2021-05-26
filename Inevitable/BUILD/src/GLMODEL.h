#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <GLM\gtx\rotate_vector.hpp>
#include <fmod.hpp>
#include <vector>
#include <ctime>
#include <xinput.h>
#include <mmsystem.h>
#include <GL/glew.h>
#include <GLUT/glut.h>
#include <map>
#include <IL\ilut.h>
#include "ShaderProgram.h"
#include "VertexBufferObject.h"

#pragma once
struct Ray {
	
	glm::vec3 p0; // P0 
	glm::vec3 p1; // P0 
//	glm::vec3 dir; // Direction Unit Vector
	//float len; // Ray length 
};



struct Triangle { glm::vec3 V0;     glm::vec3 V1;     glm::vec3 V2;         glm::vec3 normal; };
glm::vec3 CalcNormalOfFace(glm::vec3 pPositions[3], glm::vec3 pNormals[3]);
typedef struct Vertex
{
	float x;
	float y;
	float z;
	Vertex()
	{
		x = 0; y = 0; z = 0;
	}
	Vertex(int X, int Y, int Z)
	{
		x = X;
		y = Y;
		z = Z;
	}
}Vertex;

typedef struct
{
	float x;
	float y;
	float z;

}Normal;
typedef struct UV
{
	float u;
	float v;

	UV()
	{
	}
	UV(int U, int V)
	{
		u = U;
		v = V;
	}
}UV;

typedef struct
{
	int vx;
	int vy;
	int vz;

	int uvx;
	int uvy;
	int uvz;

	int vnx;
	int vny;
	int vnz;
	glm::vec3 faceNorm;


}Face;

class GLMODEL {
public:
	GLMODEL();
	~GLMODEL();
	bool load(std::string file_path);//, ShaderProgram* sp);	
	void setP(int i);
	void draw();
	void prepStage();
	void setVerts(Vertex v,int i);
	int getVS();
	int getNS();
	int getUS();
	void setUVs(std::vector <UV> us);
	std::vector <UV> getUvs();
	std::vector <Face> getFaces();
	void setFaces(std::vector <Face> f);
	float getEnd();
	float getBeg();
	void setSize(int size,int n,int b);
	void setNorms(Normal v, int i);
	Vertex getVerts(int i);
	Normal getNorms(int i);
	int getTSize();
	Triangle triangle(int n);
	std::vector <Vertex> vertices;
	std::vector <Vertex> outvertices;
	std::vector <Normal> normals;
	std::vector <Normal> outnormals;
	std::vector <glm::vec3> texCoords;

	void createVBO();

	VertexBufferObject vbo;

private:
	float bigX=0.0f;
	float littleX=0.0f;
	std::vector <UV> uvs;
	std::vector <UV> outuvs;
	std::vector <Face> faces;
	std::vector <Triangle> tries;
	GLint newplane;
	bool stage=false;

	ShaderProgram* shaderProgram; //can change to shared later
};