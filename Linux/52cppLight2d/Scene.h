#pragma once
#include <stdlib.h> // rand(), RAND_MAX
#include "Shape.h"
#include "QuadTree.h"

using namespace std;

#define MAX_DEPTH 5
#define IS_DEBUG false
#define N 16
#define N2 16
#define TWO_PI 6.28318530718f
#define BIAS 1e-4f
#define USE_QUADTREE false

void drawLine(Point p1, Point p2);

class Entity
{
protected:
	Shape* m_shape;
	Color m_emissive;
	float m_reflectivity;		//������������
	float m_refractivity;		//һ��ģ�Ҫ��reflectivity + refractivity <= 1
	float m_refract_index[N2];	//��Ϊÿ����ɫ�����в�ͬ��������
public:
	Entity(Shape* s, Color e, float re = 0.f, float ra = 0.f, float* ri = NULL) :
		m_shape(s), m_emissive(e), m_reflectivity(re), m_refractivity(ra)
	{
		if (ri)
			for (int i = 0; i < 3; i++)
				m_refract_index[i] = ri[i];
	}
	Entity(Shape* s, Color e, float re, float ra, float ri_min, float ri_max) :
		m_shape(s), m_emissive(e), m_reflectivity(re), m_refractivity(ra)
	{
		for (int i = 0; i < N2; i++)
			m_refract_index[i] = (ri_max - ri_min) / (N2 - 1) * i + ri_min;
	}
	~Entity() { SAFE_DELETE(m_shape); }
	Shape* GetShape() { return m_shape; }
	Color GetEmissive() { return m_emissive; }
	float GetReflectivity() { return m_reflectivity; }
	float GetRefractivity() { return m_refractivity; }
	float GetRefractIndex(int index) { return m_refract_index[index]; }
	//�ж��Ƿ��ཻ�����ؽ���
	virtual bool Intersect(Point p, Vector d, Point &inter)
	{
		return m_shape->Intersect(p, d, inter);
	}
	//�ж��Ƿ��ڰ�Χ���ڲ�
	bool Contained(float left, float right, float up, float down)
	{
		return m_shape->Contained(left, right, up, down);
	}
};

//�۹��
class SpotLight :public Entity
{
protected:
	Vector m_dir;		//�۹��������
	float m_cosa;		//�۹�ƽǶȷ�Χ��cos
public:
	SpotLight(Shape* s, Color e, float re = 0.f, float ra = 0.f, float* ri = NULL,
		Vector dir = { 0.f, 1.f }, float a = 0.03f) :
		Entity(s, e, re, ra, ri), m_dir(dir)
	{
		m_cosa = cos(a);
	}
	~SpotLight() {}
	bool Intersect(Point p, Vector d, Point &inter)
	{
		if (d*(-m_dir) < m_cosa)	//Ԥ���˽Ƕȷ��������䷶Χ��Ĺ���
			return false;
		else
			return m_shape->Intersect(p, d, inter);
	}
};

class Scene
{
protected:
	Color rainbow[7] =
	{
		{ 1.f,0.f,0.f },
		{ 1.f,0.65f,0.f },
		{ 1.f,1.f,0.f },
		{ 0.f,1.f,0.f },
		{ 0.f,0.5f,1.f },
		{ 0.f,0.f, 1.f },
		{ 0.55f,0.f,1.f },
	};
	QuadTree<Entity>* m_entityTree;
	list<Entity*> m_entities;		//��Ȼ����entity�б����ڵ���
public:
	Scene(list<Entity*> entities):m_entities(entities)
	{
		m_entityTree = new QuadTree<Entity>(entities);
	}
	~Scene()
	{
		delete m_entityTree;
		for (auto ent : m_entities)
			SAFE_DELETE(ent);
	}
	list<Entity*> GetEntities() { return m_entities; }
	Color GetRefractColor(int index)
	{
		float idxf = index * 6.f / (N2 - 1);
		float idx1 = floor(idxf);
		float idx2 = ceil(idxf);
		float gap1 = idxf - idx1;
		float gap2 = idx2 - idxf;
		Color color;
		if (idx1 == idx2)
			color = rainbow[(int)idx2];
		else
			color = {	rainbow[(int)idx1].r * gap2 + rainbow[(int)idx2].r * gap1,
						rainbow[(int)idx1].g * gap2 + rainbow[(int)idx2].g * gap1,
						rainbow[(int)idx1].b * gap2 + rainbow[(int)idx2].b * gap1,
		};
		return color;
	}
	Color Refract(Entity* ent, Point inter, Vector d, Vector normal, int color_index, int depth)
	{
		if (depth > MAX_DEPTH || ent->GetRefractivity() == 0.f) return{ 0.f, 0.f,0.f };
		float idotn = d * normal;
		float ri = ent->GetRefractIndex(color_index);
		float k, a;
		if (idotn > 0.f)	//������������
		{
			k = 1.f - ri*ri*(1.f - idotn*idotn);
			if (k < 0.f) return{ 0.f, 0.f, 0.f };  //ȫ����
			a = ri * idotn - sqrtf(k);
		}
		else  //������������
		{
			ri = 1.f / ri;
			k = 1.f - ri*ri*(1.f - idotn*idotn);
			a = ri * idotn + sqrtf(k);
		}
		Vector refract = d*ri - normal*a;
		return GetColor(inter + refract * BIAS, refract, color_index, depth) * ent->GetRefractivity();
	}
	Color Reflect(Entity* ent, Point inter, Vector d, Vector normal, int color_index, int depth)
	{
		if (depth > MAX_DEPTH || ent->GetReflectivity() == 0.f) return{ 0.f, 0.f,0.f };
		//if (normal * d > 0.f) return{ 0.f, 0.f,0.f };
		Vector reflect = d.reflect(normal);
		return GetColor(inter + reflect * BIAS, reflect, color_index, depth) * ent->GetReflectivity();
	}
	Color GetColor(Point p, Vector d, int color_index, int depth = 0)	//��ȡp���d�����յ���emissive
	{
		Color trace_emissive{ 0.0f, 0.0f, 0.0f };
		float distance = 10.0f;
		Entity* ent_near = NULL;
		Point inter;
#if USE_QUADTREE
		m_entityTree->Intersect(p, d, ent_near, inter);
#else
		for (auto ent:m_entities)
		{
			Point tmp_inter;
			if (ent->Intersect(p, d, tmp_inter))
			{
				float new_dist = (tmp_inter - p).len();
				if (distance > new_dist)
				{
					ent_near = ent;
					distance = new_dist;
					inter = tmp_inter;
				}
			}
		}
#endif // USE_QUADTREE
		
		if (ent_near)
		{
			if (IS_DEBUG)
				drawLine(p, inter);
			Vector normal = ent_near->GetShape()->GetNormal(inter);
			Color reflect = Reflect(ent_near, inter, d, normal, color_index, depth + 1);
			Color refract = { 0.f, 0.f, 0.f };
			if (color_index >= N2)
			{
				//refract.r = Refract(ent_near, inter, d, normal, 0, depth + 1).r;
				//refract.g = Refract(ent_near, inter, d, normal, 1, depth + 1).g;
				//refract.b = Refract(ent_near, inter, d, normal, 2, depth + 1).b;
//#pragma omp parallel for
				for (int i = 0; i < N2; i++)
					refract = refract + Refract(ent_near, inter, d, normal, i, depth + 1) * GetRefractColor(i);
				refract = refract * 2.f / N2;
			}
			else
				refract = Refract(ent_near, inter, d, normal, color_index, depth + 1);
			return ent_near->GetEmissive() + reflect + refract;
		}
		else
			return{ 0.0f, 0.0f, 0.0f };
	}
	Color Sample(Point p)
	{
		Color sum{ 0.0f, 0.0f, 0.0f };
		Color tmp[N];
#pragma omp parallel for
		for (int i = 0; i < N; i++)
		{
			float a = TWO_PI * (i + (float)rand() / RAND_MAX) / N;
			//float a = TWO_PI * (i) / N;
			tmp[i] = GetColor(p, { cosf(a), sinf(a) }, N2);
		}
		for (int i = 0; i < N; i++)
			sum = sum + tmp[i];
		return sum / N;
	}
	Color GetBaseColor(Point p)
	{
		for (auto ent : m_entities)
			if (ent->GetShape()->IsInside(p))
				return ent->GetEmissive();
		return{ 0.f, 0.f, 0.f };
	}
};