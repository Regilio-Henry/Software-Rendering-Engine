#pragma once
#include <vector>
#include "Framework.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "AmbientLight.h"
#include "PointLight.h"



class Rasteriser : public Framework
{
public:
	void Update(Bitmap &bitmap);
	void Render(Bitmap &bitmap);
	virtual bool Initialise();
	void GeneratePerspectiveMatrix(float d, float aspectRatio);
	void GenerateViewMatrix(float d, int width, int height);
	void DrawWireFrame(Bitmap &bitmap);
	bool LoadModel();
	void DrawSolidFlat(Bitmap &bitmap);
	void MyDrawSolidFlat(Bitmap &bitmap);
	void DrawGouraud(Bitmap &bitmap);
	void FillPolygonFlat(Bitmap & bitmap, Vertex _vert1, Vertex _vert2, Vertex _vert3, COLORREF color);
	void fillBottomFlatTriangle(Bitmap & bitmap, Vertex vert1, Vertex vert2, Vertex vert3, COLORREF color);
	void fillTopFlatTriangle(Bitmap & bitmap, Vertex vert1, Vertex vert2, Vertex vert3, COLORREF color);
	void sortVerticesAscendingByY(Vertex &vert1, Vertex &vert2, Vertex &vert3);
	void FillPolygonGouraud(Bitmap & bitmap, Vertex _vert1, Vertex _vert2, Vertex _vert3, COLORREF color);
	void DrawString(Bitmap &bitmap, LPCTSTR text);

private:
	Matrix perspectiveMatrix;
	Matrix viewMatrix;
	Camera _Camera;
	Matrix _worldMatrix;
	vector<DirectionaLighting> DirectionaLights;
	AmbientLight ambientlight;
	vector<PointLight> pointLights;
};

