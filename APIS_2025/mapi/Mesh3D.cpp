#include "Mesh3D.h"

int Mesh3D::nextId = 1;

// Constructor
Mesh3D::Mesh3D()
	: meshID(nextId++),
	colorRGBA(1.0f, 1.0f, 1.0f, 1.0f),
	vVertList(),
	mat(nullptr),
	vTriangleIdxList(new std::vector<glm::uint32>())
{}

// Getters
int Mesh3D::getMeshId() const
{
	return meshID;
}

const vector<vertex_t>* Mesh3D::getVertexList() const
{
	return &vVertList;
}

Material* Mesh3D::getMaterial() const
{
	return mat;
}

vector<glm::uint32>* Mesh3D::getTriangleIdxList() const
{
	return vTriangleIdxList;
}

// Setters
void Mesh3D::setMaterial(Material* material)
{
	mat = material;
}

void Mesh3D::setTriangleIdxList(std::vector<glm::uint32>* triangleIdxList)
{
	if (vTriangleIdxList != nullptr)
	{
		delete vTriangleIdxList;
	}
	vTriangleIdxList = triangleIdxList;
}

// Métodos
void Mesh3D::addVertex(const vertex_t& vertex)
{
	vVertList.push_back(vertex);
}

void Mesh3D::addTriangle(glm::uint32 vId1, glm::uint32 vId2, glm::uint32 vId3)
{
	if (vTriangleIdxList != nullptr)
	{
		vTriangleIdxList->push_back(vId1);
		vTriangleIdxList->push_back(vId2);
		vTriangleIdxList->push_back(vId3);
	}
	else
	{
		// Si 'vTriangleIdxList' no ha sido inicializado, lo inicializamos aquí
		vTriangleIdxList = new vector<glm::uint32>();
		vTriangleIdxList->push_back(vId1);
		vTriangleIdxList->push_back(vId2);
		vTriangleIdxList->push_back(vId3);
	}
}
