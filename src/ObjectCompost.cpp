#include "ObjectCompost.h"

ObjectCompost::ObjectCompost(string filename1,string filename2){
	apr = new CGFappearance("../data/w.jpg",1,1);
	float sp[4] = {0.1, 0.1,0.1, 0.0};
	float a[4] = {0.1, 0.1,0.1, 0.0};
	float z[4] = {0.1, 0.1,0.1, 0.0};
	apr->setSpecular(sp);
	apr->setAmbient(a);
	apr->setDiffuse(z);
	scene1 = importer.ReadFile(filename1,aiProcess_CalcTangentSpace|aiProcess_Triangulate|aiProcess_JoinIdenticalVertices|aiProcess_SortByPType);
	scene2 = importer1.ReadFile(filename2,aiProcess_CalcTangentSpace|aiProcess_Triangulate|aiProcess_JoinIdenticalVertices|aiProcess_SortByPType);

	if(!scene1){
		cout << importer.GetErrorString();
	}
	if(!scene2){
		cout << importer.GetErrorString();
	}

}

void ObjectCompost::draw(){
	
	if(!scene1)
		return;

	if(!scene1->mNumMeshes){
		cout << "NO PRIMITIVES" << endl;
		return;
	}
	if(!scene2)
		return;

	if(!scene2->mNumMeshes){
		cout << "NO PRIMITIVES" << endl;
		return;
	}
	glPushMatrix();
	glTranslated(0,2.5,0);
	apr->apply();
	glScalef(0.3,0.3,0.3);
	for(auto i = 0u; i < scene1->mNumMeshes ; i++){
		for (auto j = 0u; j < scene1->mMeshes[i]->mNumFaces ; j++)
		{
		
			glBegin(GL_TRIANGLES);

			for (auto k = 0; k < 3; ++k)
				glNormal3f(scene1->mMeshes[i]->mNormals[scene1->mMeshes[i]->mFaces[j].mIndices[k]].x,
					scene1->mMeshes[i]->mNormals[scene1->mMeshes[i]->mFaces[j].mIndices[k]].y,
					scene1->mMeshes[i]->mNormals[scene1->mMeshes[i]->mFaces[j].mIndices[k]].z);
			
			for(auto n = 0; n < 3 ; n++)
				glVertex3f(scene1->mMeshes[i]->mVertices[scene1->mMeshes[i]->mFaces[j].mIndices[n]].x,
				scene1->mMeshes[i]->mVertices[scene1->mMeshes[i]->mFaces[j].mIndices[n]].y,
				scene1->mMeshes[i]->mVertices[scene1->mMeshes[i]->mFaces[j].mIndices[n]].z);


			glEnd();
		}
	}
	glTranslated(0,-3,0);
	glScalef(0.4,0.4,0.4);
		apr->apply();
		for(auto i = 0u; i < scene2->mNumMeshes ; i++){
		for (auto j = 0u; j < scene2->mMeshes[i]->mNumFaces ; j++)
		{
			glBegin(GL_TRIANGLES);
			for (auto k = 0; k < 3; ++k)
				glNormal3f(scene2->mMeshes[i]->mNormals[scene2->mMeshes[i]->mFaces[j].mIndices[k]].x,
					scene2->mMeshes[i]->mNormals[scene2->mMeshes[i]->mFaces[j].mIndices[k]].y,
					scene2->mMeshes[i]->mNormals[scene2->mMeshes[i]->mFaces[j].mIndices[k]].z);
			
			for(auto n = 0; n < 3 ; n++)
				glVertex3f(scene2->mMeshes[i]->mVertices[scene2->mMeshes[i]->mFaces[j].mIndices[n]].x,
				scene2->mMeshes[i]->mVertices[scene2->mMeshes[i]->mFaces[j].mIndices[n]].y,
				scene2->mMeshes[i]->mVertices[scene2->mMeshes[i]->mFaces[j].mIndices[n]].z);


			glEnd();
		}
	}
		glPopMatrix();
}

const aiScene* ObjectCompost::getScene(){
	return scene1,scene2;
}

ObjectCompost::~ObjectCompost(){

}


