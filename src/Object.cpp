#include "Object.h"

Object::Object(string filename){
	apr = new CGFappearance("../data/w.jpg",1,1);
	apr1 = new CGFappearance("../data/blue.png",1,1);
	float sp[4] = {0.1, 0.1,0.1, 0.0};
	float a[4] = {0.1, 0.1,0.1, 0.0};
	float z[4] = {0.1, 0.1,0.1, 0.0};
	apr->setSpecular(sp);
	apr->setAmbient(a);
	apr->setDiffuse(z);
	apr1->setSpecular(sp);
	apr1->setAmbient(a);
	apr1->setDiffuse(z);
	scene = importer.ReadFile(filename,aiProcess_CalcTangentSpace|aiProcess_Triangulate|aiProcess_JoinIdenticalVertices|aiProcess_SortByPType);

	if(!scene){
		cout << importer.GetErrorString();
	}

}

void Object::draw(bool player){

	if(!scene)
		return;

	if(!scene->mNumMeshes){
		cout << "NO PRIMITIVES" << endl;
		return;
	}

	glTranslated(0,1.8,0);
	glScalef(0.26,0.26,0.26);
	if(player)
	apr->apply();
	else
		apr1->apply();
	for(auto i = 0u; i < scene->mNumMeshes ; i++){
		for (auto j = 0u; j < scene->mMeshes[i]->mNumFaces ; j++)
		{
			glBegin(GL_TRIANGLES);

			for (auto k = 0; k < 3; ++k)
				glNormal3f(scene->mMeshes[i]->mNormals[scene->mMeshes[i]->mFaces[j].mIndices[k]].x,
					scene->mMeshes[i]->mNormals[scene->mMeshes[i]->mFaces[j].mIndices[k]].y,
					scene->mMeshes[i]->mNormals[scene->mMeshes[i]->mFaces[j].mIndices[k]].z);
			
			for(auto n = 0; n < 3 ; n++)
				glVertex3f(scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[j].mIndices[n]].x,
				scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[j].mIndices[n]].y,
				scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[j].mIndices[n]].z);


			glEnd();
		}
	}
}

const aiScene* Object::getScene(){
	return scene;
}

Object::~Object(){

}


