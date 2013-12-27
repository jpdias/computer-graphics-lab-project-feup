#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <iostream>
#include "CGFscene.h"
#include "CGFshader.h"
#include "CGFaxis.h"
#include "CGFapplication.h"

#include <math.h>
#include "CGFappearance.h"

#include <string>
using namespace std;


class Object{

private:
	const aiScene* scene;
	const aiScene* scene1;
	const aiScene* scene2;
	Assimp::Importer importer;
	Assimp::Importer importer1;
	CGFappearance* apr;
	CGFappearance* apr1;
	CGFappearance* mon;	
	bool compost;
public:
	Object(string filename);
	Object(string filename1,string filename2);
	const aiScene* getScene();
	void draw(int player);
	void drawS(int player);
	void drawC(bool player);
	~Object();

	
};