/*
Model

Depends on: Polygon.h

Description: A container for groups of related geometry. It handles the creation of 
arbitrarily sized vertex arrays from the polgons that it contains.

TODO: Create API for one origin point for the entire polygon

origin: the point of origin for this particular polygon
vaComponentCount: the number of vertex components in the Polygons of the model
vaByteSize: the number Bytes required to contain the vertices of all the polygons in memory

*/

#pragma once

#include "Model.h"
#include <iostream>


Model::Model()
{
	origin = glm::vec3(0.f);
}

void Model::addPolygon(Polygon* poly) 
{
	polygons.push_back(poly);
}

int Model::getVAFloatCount()
{
	vaComponentCount = 0;
	for (std::vector<Polygon *>::iterator it = polygons.begin(); it < polygons.end(); it++) 
	{
		vaComponentCount += (**it).getVAFloatCount();
	}
	return vaComponentCount;
}

void Model::transform(glm::mat4 transmat)
{
	for (std::vector<Polygon *>::iterator it = polygons.begin(); it < polygons.end(); it++)
	{
		(**it).transform(transmat);
	}
}

int Model::getVAByteSize()
{
	vaByteSize = 0;
	for (std::vector<Polygon *>::iterator it = polygons.begin(); it < polygons.end(); it++)
	{
		vaByteSize += (**it).getVAByteSize();
	}
	return vaByteSize;
}

int Model::getVAVertexCount() 
{
	int vertexCount = 0;
	for (std::vector<Polygon *>::iterator it = polygons.begin(); it < polygons.end(); it++)
	{
		vertexCount += (**it).getVAVertexCount();
	}
	return vertexCount;
}

float* Model::getVertexArray()
{
	float* va = new float[getVAFloatCount()];
	int filled = 0;
	for (std::vector<Polygon*>::iterator it = polygons.begin(); it < polygons.end(); it++)
	{
		int vertexCount = (**it).getVAFloatCount();
		float* a = (**it).getVertexArray();
		std::copy(a, a + vertexCount, va + filled);
		filled += vertexCount;
	}
	return va;

}