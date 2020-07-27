/*
Model

Depends on: Polygon.h

Description: A container for groups of related geometry. It handles the creation of
arbitrarily sized vertex arrays from the polygons that it contains.

origin: the point of origin for this particular polygon
vaComponentCount: the number of vertex components in the Polygons of the model
vaByteSize: the number Bytes required to contain the vertices of all the polygons in memory 

*/

#pragma once
#include "binder.h"
#include <vector>
#include <glm/glm.hpp>
#include "polygon.h"
#include <glm/gtc/type_ptr.hpp>
#include "../../opengl_a/Shader.h"


class Model : public Polygon, public Binder
{
public:
	virtual void setVertexController(bool position, bool texture, bool color, bool normal);
	virtual void transform(glm::mat4 transmat);
	std::vector<Polygon*> polygons;
	void addPolygon(Polygon* poly);
	Model(bool position = true, bool texture = false, bool color = false, bool normal = false, std::string name = "default", Shader* shader = nullptr, int textureIndex = -1);
	Model();

	void addRotation(float radians, glm::vec3 axis);
	void addShear(glm::vec3 axis);
	void addScale(glm::vec3 scale);
	void addTranslation(glm::vec3 translate);
	void Reposition(glm::vec3 position);
	glm::mat4 getRotation();
	glm::mat4 getTranslation();
	glm::mat4 getScale();
	glm::mat4 getModelMatrix(bool shear = false);
	glm::mat4 getShear(); 
	glm::mat4 getReposition();


	virtual float* getVertexArray();
	virtual int getVAFloatCount();
	virtual int getVAByteSize();
	virtual int getVAVertexCount();
	virtual int getVertexByteSize();
	virtual Vertex getSampleVertex();
	virtual std::map<std::string, glm::vec3> getMinMax();

	void draw(int mode, Shader* shaderProg);
	void translateToOrigin();
	void setBoolean(bool position, bool texture, bool color, bool normal);

	std::string name;
	Shader* shader;
	int textureIndex;

	glm::vec3 origin;
	int vaComponentCount;
	int vaByteSize;
	float offset = 1.0f;


	//vertex components
	bool position, color, texture, normal;
	glm::vec3 shear_vec;
	glm::vec3 rotate_vec;
	glm::vec3 translate_vec;
	glm::vec3 scale_vec;
	float rotate_angle;

};