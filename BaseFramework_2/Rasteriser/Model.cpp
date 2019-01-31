#define NOMINMAX
#include "Model.h"
#include <algorithm>

Model::Model()
{
	kd_red = 1.0f;
	kd_green = 1.0f;
	kd_blue = 1.0f;
	ka_red = 0.2f;
	ka_green = 0.2f;
	ka_blue = 0.2f;
	ks_red = 0.5f;
	ks_green = 0.5f;
	ks_blue = 0.5f;
}

Model::~Model()
{
}

bool DepthComparison(Polygon3D Poly1, Polygon3D Poly2)
{
	bool greaterThen = Poly1.GetZDepth() > Poly2.GetZDepth();
	return greaterThen;
}

std::vector<Polygon3D>& Model::GetPolygons()
{
	return _polygons;
}

//Gets the transformedVertices collection 
std::vector<Vertex>& Model::GetTransformedVertices()
{
	return _vertices;
}

std::vector<Vertex>& Model::GetVertices()
{
	return _transformedVertices;
}

//Gets amount of polygons in model
size_t Model::GetPolygonCount() const
{
	return  _polygons.size();
}

//Gets amount of vertices in model
size_t Model::GetVertexCount() const
{
	return  _vertices.size();
}

void Model::AddVertex(float x, float y, float z)
{
	_vertices.push_back(Vertex(x,y,z));
}

void Model::AddPolygon(int i0, int i1, int i2)
{
	_polygons.push_back(Polygon3D(i0, i1, i2));
}

//Applies matrix transformation to the local vertices
void Model::ApplyTransformToLocalVertices(const Matrix & transform)
{
	_transformedVertices.clear();
	for(int i = 0; i < (int) _vertices.size(); i++)
	{
		_transformedVertices.push_back(transform * _vertices[i]);
	}
}

//Applies matrix transformation to the transformed vertices
void Model::ApplyTransformToTransformedVertices(const Matrix & transform)
{
	for (int i = 0; i < GetVertexCount(); i++)
	{
		_transformedVertices[i] = transform * _transformedVertices[i];
	}
}

//Dehomogenize all vertices inside of the model
void Model::DehomogenizeVertices()
{
	for (size_t i = 0; i < _transformedVertices.size(); i++)
	{
		_transformedVertices[i].DehomogenizeVertex();
	}
}


void Model::CalculateBackfaces(Camera cam)
{

	for(size_t i = 0; i < _polygons.size(); i++)
	{
		Vertex vert0 = Vertex(_transformedVertices[_polygons[i].GetIndex(0)]);
		Vertex vert1 = Vertex(_transformedVertices[_polygons[i].GetIndex(1)]);
		Vertex vert2 = Vertex(_transformedVertices[_polygons[i].GetIndex(2)]);

		Vector a = vert0 - vert1;
		Vector b = vert0 - vert2;
		Vector normal = b.CrossProduct(a);
		Vector eyeVector = vert0 - cam.GetPosition();
		//normal.Normalise();
		//eyeVector.Normalise();
		float result = eyeVector.DotProduct(normal);
		_polygons[i].SetNormal(normal);

		if(result < 0.0f)
		{
			_polygons[i].SetIsCulled(true);
		}
		else
		{
			_polygons[i].SetIsCulled(false);
		}
	}
}

void Model::CalculateNormalVertex()
{
	for (size_t i = 0; i < _transformedVertices.size(); i++) 
	{
		_transformedVertices[i].SetNormal(Vector(0,0,0));
		_transformedVertices[i].SetContribution(0);
	}

	for(size_t j = 0; j < _polygons.size(); j++)
	{
		Vertex vert0 = Vertex(_transformedVertices[_polygons[j].GetIndex(0)]);
		Vertex vert1 = Vertex(_transformedVertices[_polygons[j].GetIndex(1)]);
		Vertex vert2 = Vertex(_transformedVertices[_polygons[j].GetIndex(2)]);

		vert0.SetNormal(vert0.GetNormal()  + _polygons[j].GetNormal());
		vert1.SetNormal(vert1.GetNormal()  + _polygons[j].GetNormal());
		vert2.SetNormal(vert2.GetNormal()  + _polygons[j].GetNormal());

		vert0.SetContribution(vert0.GetContribution() + 1);
		vert1.SetContribution(vert0.GetContribution() + 1);
		vert2.SetContribution(vert0.GetContribution() + 1);

		_transformedVertices[_polygons[j].GetIndex(0)] = vert0;
		_transformedVertices[_polygons[j].GetIndex(1)] = vert1;
		_transformedVertices[_polygons[j].GetIndex(2)] = vert2;

	}

	for (size_t k = 0; k < _transformedVertices.size(); k++)
	{
		 Vector vect = Vector(_transformedVertices[k].GetNormal().GetX() / _transformedVertices[k].GetContribution(),
							  _transformedVertices[k].GetNormal().GetY() / _transformedVertices[k].GetContribution(),
							  _transformedVertices[k].GetNormal().GetX() / _transformedVertices[k].GetContribution()
							);
		 vect.Normalise();
		 _transformedVertices[k].SetNormal(vect);
	}

}

void Model::CalculateLightingDirectionalVertex(vector<DirectionaLighting> lights)
{
	float tempR = 0;
	float tempG = 0;
	float tempB = 0;
	float totalR = 0;
	float totalG = 0;
	float totalB = 0;
	float Lightdotproduct;
	COLORREF totalColor;
	Vector L;
	Vector N;

	for (size_t i = 0; i < _transformedVertices.size(); i++)
	{

		totalR = GetRValue(_transformedVertices[i].GetColor());
		totalG = GetGValue(_transformedVertices[i].GetColor());
		totalB = GetBValue(_transformedVertices[i].GetColor());

		for (size_t j = 0; j < lights.size(); j++)
		{
			tempR = lights[j].getRed();
			tempG = lights[j].getGreen();
			tempB = lights[j].getBlue();


			tempR = kd_red * tempR;
			tempG = kd_green * tempG;
			tempB = kd_blue * tempB;

			//Vertex vert0 = Vertex(_transformedVertices[_polygons[i].GetIndex(0)]);
			L = lights[j].getLightDirection();
			N = _transformedVertices[i].GetNormal();
			N.Normalise();
			L.Normalise();

			Lightdotproduct = L.DotProduct(N);
			tempR = tempR * Lightdotproduct;
			tempG = tempG * Lightdotproduct;
			tempB = tempB * Lightdotproduct;

			totalR += tempR;
			totalG += tempG;
			totalB += tempB;
		}

		totalR = (totalR > 255 ? 255 : (totalR < 0 ? 0 : totalR));
		totalG = (totalG > 255 ? 255 : (totalG < 0 ? 0 : totalG));
		totalB = (totalB > 255 ? 255 : (totalB < 0 ? 0 : totalB));

		totalColor = RGB(totalR, totalG, totalB);
		_transformedVertices[i].SetColor(totalColor);
	}
}

void Model::Sort(void)
{
	for (size_t i = 0; i < _polygons.size(); i++)
	{
		Vertex vert0 = Vertex(_transformedVertices[_polygons[i].GetIndex(0)]);
		Vertex vert1 = Vertex(_transformedVertices[_polygons[i].GetIndex(1)]);
		Vertex vert2 = Vertex(_transformedVertices[_polygons[i].GetIndex(2)]);

		float averageZdepth = (vert0.GetZ() + vert1.GetZ() + vert2.GetZ()) / 3;
		_polygons[i].SetZDepth(averageZdepth);
	}

	std::sort(_polygons.begin(), _polygons.end(), DepthComparison);

}

void Model::CalculateLightingDirectional(vector<DirectionaLighting> lights)
{

	float tempR = 0;
	float tempG = 0;
	float tempB = 0;
	float totalR = 0;
	float totalG = 0;
	float totalB = 0;
	float Lightdotproduct;
	COLORREF totalColor;
	Vector L;
	Vector N;

	for (size_t i = 0; i < _polygons.size(); i++)
	{

		totalR = GetRValue(_polygons[i].GetColor());
		totalG = GetGValue(_polygons[i].GetColor());
		totalB = GetBValue(_polygons[i].GetColor());

		for (size_t j = 0; j < lights.size(); j++)
		{
			tempR = lights[j].getRed();
			tempG = lights[j].getGreen();
			tempB = lights[j].getBlue();

			
			tempR = kd_red * tempR; 
			tempG = kd_green * tempG;
			tempB = kd_blue * tempB;

			//Vertex vert0 = Vertex(_transformedVertices[_polygons[i].GetIndex(0)]);
			L = lights[j].getLightDirection();
		    N = _polygons[i].GetNormal();
			N.Normalise();
			L.Normalise();

			Lightdotproduct = L.DotProduct(N);
			tempR =  tempR * Lightdotproduct;
			tempG =  tempG * Lightdotproduct;
			tempB =  tempB * Lightdotproduct;

			totalR += tempR;
			totalG += tempG;
			totalB += tempB;
		}

		totalR = (totalR > 255 ? 255 : (totalR < 0 ? 0 : totalR));
		totalG = (totalG > 255 ? 255 : (totalG < 0 ? 0 : totalG));
		totalB = (totalB > 255 ? 255 : (totalB < 0 ? 0 : totalB));

		totalColor = RGB(totalR, totalG, totalB);
		_polygons[i].SetColor(totalColor);
	}
}

void Model::CalculateLightingAmbient(AmbientLight light)
{
	float tempR = 0;
	float tempG = 0;
	float tempB = 0;
	float totalR = 0;
	float totalG = 0;
	float totalB = 0;
	COLORREF totalColor;

	for (size_t i = 0; i < _polygons.size(); i++)
	{

		totalR = 0;
		totalG = 0;
		totalB = 0;

		tempR = light.getRed();
		tempG = light.getGreen();
		tempB = light.getBlue();

		
		tempR = ka_red * tempR; 
		tempG = ka_green * tempG;
		tempB = ka_blue * tempB;

		totalR += tempR;
		totalG += tempG;
		totalB += tempB;
		
		totalR = (totalR > 255 ? 255 : (totalR < 0 ? 0 : totalR));
		totalG = (totalG > 255 ? 255 : (totalG < 0 ? 0 : totalG));
		totalB = (totalB > 255 ? 255 : (totalB < 0 ? 0 : totalB));

		totalColor = RGB(totalR, totalG, totalB);
		_polygons[i].SetColor(totalColor);
	}
}

void Model::CalculateLightingPoint(vector<PointLight> lights)
{

	float tempR = 0;
	float tempG = 0;
	float tempB = 0;
	float totalR = 0;
	float totalG = 0;
	float totalB = 0;
	float Lightdotproduct;
	COLORREF totalColor;
	Vertex Lpos;
	Vector L;
	Vector N;

	for (size_t i = 0; i < _polygons.size(); i++)
	{

		totalR = GetRValue(_polygons[i].GetColor());
		totalG = GetGValue(_polygons[i].GetColor());
		totalB = GetBValue(_polygons[i].GetColor());

		for (size_t j = 0; j < lights.size(); j++)
		{
			tempR = lights[j].getRed();
			tempG = lights[j].getGreen();
			tempB = lights[j].getBlue();
			Vertex vert0 = Vertex(_transformedVertices[_polygons[i].GetIndex(0)]);

			tempR = ks_red * tempR;
			tempG = ks_green * tempG;
			tempB = ks_blue * tempB;
			
			Lpos = lights[j].getPosition();
			//L = lights[j].getPosition();
			Vector lightVector = vert0 - Lpos;
			lightVector.Normalise();
			Vector vecDist = Vector(lightVector.GetX() - Lpos.GetX(), lightVector.GetY() - Lpos.GetY(), lightVector.GetZ() - Lpos.GetZ());
			float D = Vector().Magnitude(vecDist);
			float attenuation = (lights[j].getA() + lights[j].getB() * D) + (lights[j].getC() * pow(D, 2));
			N = _polygons[i].GetNormal();
			N.Normalise();
			L.Normalise();

			Lightdotproduct = L.DotProduct(N);
			tempR = tempR * (Lightdotproduct * attenuation);
			tempG = tempG * (Lightdotproduct * attenuation);
			tempB = tempB * (Lightdotproduct * attenuation);
														  
			totalR += tempR;
			totalG += tempG;
			totalB += tempB;
		}

		totalR = (totalR > 255 ? 255 : (totalR < 0 ? 0 : totalR));
		totalG = (totalG > 255 ? 255 : (totalG < 0 ? 0 : totalG));
		totalB = (totalB > 255 ? 255 : (totalB < 0 ? 0 : totalB));

		totalColor = RGB(totalR, totalG, totalB);
		_polygons[i].SetColor(totalColor);
	}
}
