#include "vertex.h"
#include "Material.h"

#pragma once
using namespace std;

class Mesh3D
{
private:
	static int nextId;
	int meshID;
	vector<vertex_t> vVertList;
	Material* mat;
	vector<glm::uint32>* vTriangleIdxList;

public:
	Mesh3D();

	// Getters
	int getMeshId() const;
	const vector<vertex_t>* getVertexList() const;
	Material* getMaterial() const;
	vector<glm::uint32>* getTriangleIdxList() const;

	// Setters
	void setMaterial(Material* material);
	void setTriangleIdxList(vector<glm::uint32>* triangleIdxList);

	//Métodos
	void addVertex(const vertex_t& vertex);
	void addTriangle(glm::uint32 vId1, glm::uint32 vId2, glm::uint32 vId3);
};