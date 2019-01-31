#pragma once
#include <vector>
#include <algorithm> 
#include "Polygon3D.h"
#include "Camera.h"
#include "Vector.h"
#include "AmbientLight.h"
#include "PointLight.h"

class Model
{
public:
	Model();
	~Model();
	// Accessors
	std::vector<Polygon3D>& GetPolygons();
	std::vector<Vertex>& GetTransformedVertices();
	std::vector<Vertex>& GetVertices();
	size_t GetPolygonCount() const;
	size_t GetVertexCount() const;
	void AddVertex(float x, float y, float z);
	void AddPolygon(int i0, int i1, int i2);
	void ApplyTransformToLocalVertices(const Matrix &transform);
	void ApplyTransformToTransformedVertices(const Matrix &transform);
	void DehomogenizeVertices();
	void CalculateBackfaces(Camera cam);
	void CalculateNormalVertex();
	void CalculateLightingDirectionalVertex(vector<DirectionaLighting> lights);
	void CalculateLightingDirectional(vector<DirectionaLighting> lights);
	void CalculateLightingAmbient(AmbientLight light);
	void CalculateLightingPoint(vector<PointLight> lights);
	void Sort(void);
private:
	std::vector<Polygon3D> _polygons;
	std::vector<Vertex> _vertices;
	std::vector<Vertex> _transformedVertices;
	float ka_red;
	float ka_green;
	float ka_blue;
	float kd_red;
	float kd_green;
	float kd_blue;
	float ks_red;
	float ks_green;
	float ks_blue;
	
};