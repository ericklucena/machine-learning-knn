#include <stdio.h>
#include "knn.h"

int main(int argc, char** argv)
{
	int nAttr;
	int nClass;
	int nElem;
	int nNeighbours;
	int i, j;
	KnnSet *set;

	sscanf(argv[1], "%d", &nAttr);
	sscanf(argv[2], "%d", &nClass);
	sscanf(argv[3], "%d", &nElem);
	sscanf(argv[4], "%d", &nNeighbours);

	set = newKnnSet(nElem, nAttr, nClass);

	for (i=0; i < nElem; i++)
	{
		KnnElement *elem;
		elem = newKnnElement(nAttr, nClass);
		for (j=0; j < nAttr; j++)
		{
			fscanf(stdin, "%lf", &(elem->attributes[j]));
		}
		addKnnElement(set, elem, i);
	}

	normalizeSet(set);

	for (i = 0; i < set->size; i++)
	{
		printClassesByIndex(set, i, nNeighbours);
	}

	return 0;
}
