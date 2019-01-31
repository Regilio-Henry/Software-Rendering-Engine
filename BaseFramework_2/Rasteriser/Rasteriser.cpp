#include "Rasteriser.h"
#include "MD2Loader.h"
#include <time.h>
#include <chrono>

Rasteriser app;
Model _model = Model();
DirectionaLighting light1;
PointLight pointlight1;
float _rotateAmountY = 0;
float _rotateAmountX = 0;
float _rotateAmountZ = 0;
float radians = 0;
float angle = 180;
float moveback = 50;
float intensity = 0.0f;
int counter = 0;
int showcase = 0;
int showTimer = 0;

//uni model path U:\\MD2\\cube.md2
//home model path E:\\University\\MD2\\cube.md2
//E:\\University\\MD2

bool Rasteriser::LoadModel()
{
	if (!MD2Loader::LoadModel("./cartman.md2", _model, &Model::AddPolygon, &Model::AddVertex))
	{
		return false;
	}

	return true;
}


//Generates Matrix to project vertices to 3D coordinates
void Rasteriser::GeneratePerspectiveMatrix(float d, float aspectRatio)
{
	perspectiveMatrix = Matrix { d / aspectRatio, 0, 0, 0,
		0, d, 0, 0,
		0, 0, d, 0,
		0, 0, 1,  0 };
	 
}
//Generates Matrix to transform vertices to screen coordinates
void Rasteriser::GenerateViewMatrix(float d, int width, int height)
{
	 viewMatrix = Matrix { (float)width/2, 0, 0, (float)width/2,
        0, -(float)height / 2, 0, (float)height/2,
				  0, 0, d/2, d/2,
				  0, 0, 0,  1};
}

//Fill polygons with solid colour
void Rasteriser::DrawSolidFlat(Bitmap & bitmap)
{
	for (int i = 0; i < _model.GetPolygonCount(); i++)
	{
		
		if (!_model.GetPolygons()[i].GetIsCulled())
		{	
			HBRUSH hBrush = CreateSolidBrush(_model.GetPolygons()[i].GetColor());
			HGDIOBJ oldBursh = SelectObject(bitmap.GetDC(), hBrush);
			HPEN hPen = CreatePen(PS_SOLID, 3, _model.GetPolygons()[i].GetColor());
			HGDIOBJ oldPen = SelectObject(bitmap.GetDC(), hPen);

			Vertex vert1 = _model.GetVertices()[_model.GetPolygons()[i].GetIndex(0)];
			Vertex vert2 = _model.GetVertices()[_model.GetPolygons()[i].GetIndex(1)];
			Vertex vert3 = _model.GetVertices()[_model.GetPolygons()[i].GetIndex(2)];
			
			POINT point1 = { (int)vert1.GetX() , (int)vert1.GetY() };
			POINT point2 = { (int)vert2.GetX() , (int)vert2.GetY() };
			POINT point3 = { (int)vert3.GetX() , (int)vert3.GetY()};

			POINT myPointArray[3] = {point1, point2, point3};
			
			Polygon(bitmap.GetDC(), myPointArray, 3);

			// Reset old brush
		    SelectObject(bitmap.GetDC(), oldBursh);
			// and delete our bursh
			DeleteObject(hBrush);

			// Reset old pen
			SelectObject(bitmap.GetDC(), oldPen);
			// and delete our pen
			DeleteObject(hPen);
		}
	}
	
	
}

void Rasteriser::MyDrawSolidFlat(Bitmap & bitmap)
{
	for (int i = 0; i < _model.GetPolygonCount(); i++)
	{

		if (!_model.GetPolygons()[i].GetIsCulled())
		{
			HPEN hPen = CreatePen(PS_SOLID, 3, _model.GetPolygons()[i].GetColor());
			HGDIOBJ oldPen = SelectObject(bitmap.GetDC(), hPen);

			Vertex vert1 = _model.GetVertices()[_model.GetPolygons()[i].GetIndex(0)];
			Vertex vert2 = _model.GetVertices()[_model.GetPolygons()[i].GetIndex(1)];
			Vertex vert3 = _model.GetVertices()[_model.GetPolygons()[i].GetIndex(2)];

			FillPolygonFlat(bitmap, vert1, vert2, vert3, _model.GetPolygons()[i].GetColor());

			// Reset old pen
			SelectObject(bitmap.GetDC(), oldPen);
			// and delete our pen
			DeleteObject(hPen);

		}
	}
}

void Rasteriser::DrawGouraud(Bitmap & bitmap)
{
	for (int i = 0; i < _model.GetPolygonCount(); i++)
	{

		if (!_model.GetPolygons()[i].GetIsCulled())
		{
			HPEN hPen = CreatePen(PS_SOLID, 3, _model.GetPolygons()[i].GetColor());
			HGDIOBJ oldPen = SelectObject(bitmap.GetDC(), hPen);

			Vertex vert1 = _model.GetVertices()[_model.GetPolygons()[i].GetIndex(0)];
			Vertex vert2 = _model.GetVertices()[_model.GetPolygons()[i].GetIndex(1)];
			Vertex vert3 = _model.GetVertices()[_model.GetPolygons()[i].GetIndex(2)];

			FillPolygonGouraud(bitmap, vert1, vert2, vert3, _model.GetPolygons()[i].GetColor());

			// Reset old pen
			SelectObject(bitmap.GetDC(), oldPen);
			// and delete our pen
			DeleteObject(hPen);

		}
	}
}



void Rasteriser::sortVerticesAscendingByY(Vertex &vert1, Vertex &vert2, Vertex &vert3)
{
	Vertex vTmp;

	if (vert1.GetY() > vert2.GetY())
	{
		vTmp = vert1;
		vert1 = vert2;
		vert2 = vTmp;
	}
	/* here v1.y <= v2.y */
	if (vert1.GetY() > vert3.GetY())
	{
		vTmp = vert1;
		vert1 = vert3;
		vert3 = vTmp;
	}
	/* here v1.y <= v2.y and v1.y <= v3.y so test v2 vs. v3 */
	if (vert2.GetY() > vert3.GetY())
	{
		vTmp = vert2;
		vert2 = vert3;
		vert3 = vTmp;
	}

}

void Rasteriser::FillPolygonGouraud(Bitmap & bitmap, Vertex _vert1, Vertex _vert2, Vertex _vert3, COLORREF color)
{

}


void Rasteriser::FillPolygonFlat(Bitmap & bitmap, Vertex _vert1, Vertex _vert2, Vertex _vert3, COLORREF color)
{
	Vertex vert1 = Vertex();
    Vertex vert2 = Vertex();
	Vertex vert3 = Vertex();

	vert1 = _vert1;
	vert2 = _vert2;
	vert3 = _vert3;

	sortVerticesAscendingByY(vert1, vert2, vert3);


	if (vert2.GetY() == vert3.GetY())
	{
		fillBottomFlatTriangle(bitmap, vert1, vert2, vert3, color);
	}
	else if (vert1.GetY() == vert2.GetY())
	{
		fillTopFlatTriangle(bitmap, vert1, vert2, vert3, color);
	}
	else
	{
		/* general case - split the triangle in a topflat and bottom-flat one */
		Vertex vTmp = Vertex ((vert1.GetX() + ((vert2.GetY() - vert1.GetY()) / (vert3.GetY() - vert1.GetY())) * (vert3.GetX() - vert1.GetX())), vert2.GetY(), 0);
		fillBottomFlatTriangle(bitmap, vert1, vert2, vTmp, color);
		fillTopFlatTriangle(bitmap, vert2, vTmp, vert3, color);
	}
}

void Rasteriser::fillBottomFlatTriangle(Bitmap & bitmap, Vertex vert1, Vertex vert2, Vertex vert3, COLORREF color)
{
	float slope1 = (vert2.GetX() - vert1.GetX()) / (vert2.GetY() - vert1.GetY());
	float slope2 = (vert3.GetX() - vert1.GetX()) / (vert3.GetY() - vert1.GetY());

	float x1 = vert1.GetX();
	float x2 = vert1.GetX() +0.5f;

	for (float scanlineY = vert1.GetY(); scanlineY <= vert2.GetY(); scanlineY++)
	{
		MoveToEx(bitmap.GetDC(), (int)x1, (int)scanlineY, NULL);
		LineTo(bitmap.GetDC(), (int)x2, (int)scanlineY);

		x1 += slope1;
		x2 += slope2;
	}
	
	
}

void Rasteriser::fillTopFlatTriangle(Bitmap & bitmap, Vertex vert1, Vertex vert2, Vertex vert3, COLORREF color)
{
	float slope1 = (vert3.GetX() - vert1.GetX()) / (vert3.GetY() - vert1.GetY());
	float slope2 = (vert3.GetX() - vert2.GetX()) / (vert3.GetY() - vert2.GetY());

	float x1 = vert3.GetX();
	float x2 = vert3.GetX() + 0.5f;

	for (float scanlineY = vert3.GetY(); scanlineY > vert1.GetY(); scanlineY--)
	{
		MoveToEx(bitmap.GetDC(), (int)x1, (int)scanlineY, NULL);
		LineTo(bitmap.GetDC(), (int)x2, (int)scanlineY);

		x1 -= slope1;
		x2 -= slope2;
	}
	
}

// Output a string to the bitmap at co-ordinates 10, 10
// 
// Parameters: bitmap - A reference to the bitmap object
//             text   - A pointer to a string of wide characters
//
// For example, you might call this using:
//
//   DrawString(bitmap, L"Text to display");

void Rasteriser::DrawString(Bitmap &bitmap, LPCTSTR text)
{
	HDC hdc = bitmap.GetDC();
	HFONT hFont, hOldFont;

	// Retrieve a handle to the variable stock font.  
	hFont = hFont = CreateFont(30, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Myfont"));

	// Select the variable stock font into the specified device context. 
	if (hOldFont = (HFONT)SelectObject(hdc, hFont))
	{
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, RGB(0, 0, 0));

		// Display the text string.  
		TextOut(hdc, 10, 10, text, lstrlen(text));

		// Restore the original font.        
		SelectObject(hdc, hOldFont);
	}
	DeleteObject(hFont);
}


//Draw lines to each point in the polygon
void Rasteriser::DrawWireFrame(Bitmap & bitmap)
{
	HPEN hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	HGDIOBJ oldPen = SelectObject(bitmap.GetDC(), hPen);

	for(int i = 0; i < _model.GetPolygonCount(); i++)
	{
		if (!_model.GetPolygons()[i].GetIsCulled()) 
		{
			Vertex vert1 = _model.GetVertices()[_model.GetPolygons()[i].GetIndex(0)];
			Vertex vert2 = _model.GetVertices()[_model.GetPolygons()[i].GetIndex(1)];
			Vertex vert3 = _model.GetVertices()[_model.GetPolygons()[i].GetIndex(2)];

			MoveToEx(bitmap.GetDC(), (int)vert1.GetX(), (int)vert1.GetY(), NULL);
			LineTo(bitmap.GetDC(), (int)vert2.GetX(), (int)vert2.GetY());

			LineTo(bitmap.GetDC(), (int)vert3.GetX(), (int)vert3.GetY());

			LineTo(bitmap.GetDC(), (int)vert1.GetX(), (int)vert1.GetY());
		}
	}

	// Reset old pen
	SelectObject(bitmap.GetDC(), oldPen);
	// and delete our pen
	DeleteObject(hPen);
}

bool Rasteriser::Initialise()
{
	radians = angle * (3.14f / 180);
	_rotateAmountY = radians;
	_Camera = Camera(0, 0, 0, Vertex(0, 0, -50));
	LoadModel();
	_worldMatrix = Matrix::IdentityMatrix();
	light1 = DirectionaLighting(Vector(1,0,0), 255, 0, 0);
	pointlight1 = PointLight(Vertex(0, 0, 0),10, 50, 30, 0,1,0);
	pointLights.push_back(pointlight1);
	ambientlight = AmbientLight(100,100,100);
	DirectionaLights.push_back(light1);
	return true;
}

void Rasteriser::Update(Bitmap &bitmap)
{
	counter++;

	if(counter >= 60)
	{
		showTimer += 1;
		counter = 0;
	}

	if(showTimer >= 5)
	{
		showTimer = 0;
		showcase++;
	}

	if(showcase > 4)
	{
		showcase = 0;
	}

	//_rotateAmountY += .1f;
	//_Camera.SetPosition(Vertex(0, 0, moveback));
	
	if (moveback > 0) 
	{
		_worldMatrix = _worldMatrix.TranslationMatrix(moveback, 0, 0);
		moveback -= 2;
	}
	else if( _rotateAmountY < 10)
	{
		_rotateAmountY += .1f;
		_worldMatrix = _worldMatrix.XYZRotationMatrix(0, _rotateAmountY, 0);
	}
	else if (_rotateAmountY >= 10 && _rotateAmountX < 10)
	{
		_rotateAmountX += .1f;
		_worldMatrix = _worldMatrix.XYZRotationMatrix(_rotateAmountX, 0, 0);
	}
	else if (_rotateAmountY >= 10 && _rotateAmountX >= 10 && _rotateAmountZ < 10)
	{
		_rotateAmountZ += .1f;
		_worldMatrix = _worldMatrix.XYZRotationMatrix(0, 0, _rotateAmountZ);
	}
	else
	{
		moveback = 0;
		_rotateAmountZ = 0;
		_rotateAmountX = 0;
		_rotateAmountY = 0;
	}

	GeneratePerspectiveMatrix(1.0f,(float) bitmap.GetWidth()/ bitmap.GetHeight());
	GenerateViewMatrix(1.0f, bitmap.GetWidth(), bitmap.GetHeight());
}


void Rasteriser::Render(Bitmap &bitmap)
{
	// Clear the window to black
	bitmap.Clear(RGB(0, 0, 0));

	auto start = std::chrono::steady_clock::now();
	
	//world transformation
	_model.ApplyTransformToLocalVertices(_worldMatrix);
	
	if (showcase >= 1)
	{
		//Backface culling
		_model.CalculateBackfaces(_Camera);
	}
	//Vectior normals
	_model.CalculateNormalVertex();

	//Calculate ambient Lighting 
	if (showcase >= 2)
	{
		_model.CalculateLightingAmbient(ambientlight);
	}
	//Calculate Directional Lighting Flat
	if (showcase >= 3)
	{
		_model.CalculateLightingDirectional(DirectionaLights);
	}
	//Calculate Directional Lighting Vertex
	//_model.CalculateLightingDirectionalVertex(DirectionaLights);

	//Calculate PointLight
	//_model.CalculateLightingPoint(pointLights);

	//Viewing/Camera transformation
	_model.ApplyTransformToTransformedVertices(_Camera.GetCameraMatrix());
	
	//Depth sorting
	_model.Sort();

	//Projection transformation
	_model.ApplyTransformToTransformedVertices(perspectiveMatrix);
	
	//Dehomogenize vertices of the model
	_model.DehomogenizeVertices();

	//Screen transformation
	_model.ApplyTransformToTransformedVertices(viewMatrix);

	//Draw wireframe model
	if (showcase >= 0 && showcase < 2) 
	{
		DrawWireFrame(bitmap);
		if (showcase == 0)
		{
			DrawString(bitmap, L"DrawMode: WireFrame");
		}
		else 
		{
			DrawString(bitmap, L"DrawMode: Backface culling");
		}
	}

	//DrawSolid
	if (showcase >= 2 && showcase < 4)
	{
		DrawSolidFlat(bitmap);
		if (showcase == 2)
		{
			DrawString(bitmap, L"DrawMode: Flat Shading GDI + Ambient ligthing");
		}
		else
		{
			DrawString(bitmap, L"DrawMode: Directional lighting");
		}
	}

	if (showcase == 4)
	{
		MyDrawSolidFlat(bitmap);
		DrawString(bitmap, L"DrawMode: My Flat Shading + Lighting");
	}

	auto end = std::chrono::steady_clock::now();
	double elapsedTime = double(std::chrono::duration_cast <std::chrono::seconds> (end - start).count());
	//counter = (int) elapsedTime;
}


