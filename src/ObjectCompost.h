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


class ObjectCompost{

private:
	const aiScene* scene1;
	const aiScene* scene2;
	Assimp::Importer importer;
	Assimp::Importer importer1;
public:
	ObjectCompost(string filename1,string filename2);
	const aiScene* getScene();
	void draw();
	~ObjectCompost();
};