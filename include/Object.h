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
	Assimp::Importer importer;
	CGFappearance* apr;
	CGFappearance* apr1;
	CGFappearance* mon;
public:
	Object(string filename);
	const aiScene* getScene();
	void draw(int player);
	~Object();
};