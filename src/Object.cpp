#include "Object.h"

Object::Object(string filename){

	scene = importer.ReadFile(filename,aiProcess_CalcTangentSpace|aiProcess_Triangulate|aiProcess_JoinIdenticalVertices|aiProcess_SortByPType);

	if(!scene){
		cout << importer.GetErrorString();
	}

}

void Object::draw(){

	if(!scene)
		return;

	if(!scene->mNumMeshes){
		cout << "NO PRIMITIVES" << endl;
		return;
	}

	glTranslated(0,2.8,0);
	glScalef(0.4,0.4,0.4);
	glColor3f(0.8 ,0.2 ,0.0);
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


