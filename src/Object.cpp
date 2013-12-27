#include "Object.h"

Object::Object(string filename){
	apr = new CGFappearance("data/w.jpg",1,1);
	apr1 = new CGFappearance("data/blue.png",1,1);
	mon = new CGFappearance("data/mountain.jpg",1,1);
	float sp[4] = {0.1, 0.1,0.1, 0.0};
	float a[4] = {0.1, 0.1,0.1, 0.0};
	float z[4] = {0.1, 0.1,0.1, 0.0};
	apr->setSpecular(sp);
	apr->setAmbient(a);
	apr->setDiffuse(z);
		mon->setSpecular(sp);
	mon->setAmbient(a);
	mon->setDiffuse(z);
	apr1->setSpecular(sp);
	apr1->setAmbient(a);
	apr1->setDiffuse(z);
	scene = importer.ReadFile(filename,aiProcess_CalcTangentSpace|aiProcess_Triangulate|aiProcess_JoinIdenticalVertices|aiProcess_SortByPType);
	compost=false;
	if(!scene){
		cout << importer.GetErrorString();
	}

}

void Object::draw(int player){

	if(compost)
		drawC(player);
	else
		drawS(player);

}

void Object::drawS(int player){

	if(!scene)
		return;

	if(!scene->mNumMeshes){
		cout << "NO PRIMITIVES" << endl;
		return;
	}

	glTranslated(0,1.8,0);
	glScalef(0.26,0.26,0.26);
if(player==1){
		glRotated(-90,0,1,0);
		apr->apply();
		
	}

	else if(player==0){
		glRotated(90,0,1,0);
		apr1->apply();
	}
	else
	{
		mon->apply();
	}
	
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



Object::~Object(){

}


Object::Object(string filename1,string filename2){
	compost=true;
	apr = new CGFappearance("data/w.jpg",1,1);
	apr1 = new CGFappearance("data/blue.png",1,1);
	float sp[4] = {0.1, 0.1,0.1, 0.0};
	float a[4] = {0.1, 0.1,0.1, 0.0};
	float z[4] = {0.1, 0.1,0.1, 0.0};
	apr->setSpecular(sp);
	apr->setAmbient(a);
	apr->setDiffuse(z);
	apr1->setSpecular(sp);
	apr1->setAmbient(a);
	apr1->setDiffuse(z);
	scene1 = importer.ReadFile(filename1,aiProcess_CalcTangentSpace|aiProcess_Triangulate|aiProcess_JoinIdenticalVertices|aiProcess_SortByPType);
	scene2 = importer1.ReadFile(filename2,aiProcess_CalcTangentSpace|aiProcess_Triangulate|aiProcess_JoinIdenticalVertices|aiProcess_SortByPType);
	scene = NULL;
	if(!scene1){
		cout << importer.GetErrorString();
	}
	if(!scene2){
		cout << importer.GetErrorString();
	}

}

void Object::drawC(bool player){
	
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
	
	if(player){
		glRotated(-90,0,1,0);
		apr->apply();
		
	}

	else{
		glRotated(90,0,1,0);
		apr1->apply();
	}

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
	if(player)
		apr->apply();
	else
		apr1->apply();
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

const aiScene* Object::getScene(){
	
	if(scene==NULL)
		return scene1,scene2;
	else
		return scene;
}
