#include "towerengine.h"


tVertex::tVertex(tMesh *mesh)
{
	Create(mesh);
	pos = Vec(0.0, 0.0, 0.0);
}

tVertex::tVertex(tVector v, tMesh *mesh)
{
	Create(mesh);
	pos = v;
}

void tVertex::Create(tMesh *mesh)
{
	if(mesh)
	{
		this->mesh = mesh;
		mesh->AddVertex(this);
		id = -1;
	}
	else
	{
		mesh = 0;
		id = -1;
	}
}

tVertex::~tVertex(void)
{
	tTriangle **t;
	int *n;
	int c, i;

	c = GetTriangles(t, n);
	for(i=0; i<c; i++)
		delete t[i];

	if(mesh)
        mesh->RemoveVertex(this);
}

int tVertex::GetTriangles(tTriangle **&t, int *&number, tTriangle *exclude)
{
	tTriangle *ti;
	int i;
	int count, j, k;

	count = 0;

	if(!mesh)
		return 0;

	for(i=0; i<mesh->GetTriangleCount(); i++)
	{
		ti = mesh->GetTriangle(i);

		if(ti == exclude)
			continue;

		for(j=0; j<3; j++)
			if(ti->v[j] == this)
			{
				count++;
				break;
			}
	}

	t = new tTriangle *[count];
	number = new int[count];
	k = 0;
	for(i=0; i<mesh->GetTriangleCount(); i++)
	{
		ti = mesh->GetTriangle(i);

		if(exclude == ti)
			continue;
		for(j=0; j<3; j++)
			if(ti->v[j] == this)
			{
				t[k] = ti;
				number[k] = j;
				k++;
				break;
			}
	}
	return count;
}

