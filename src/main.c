#include <stdio.h>
#include "knn.h"

int main(int argc, char** argv)
{
	int nAttr;
	int tAttr;
	int nElem;
	int i, j;
	KnnSet *set;

	sscanf(argv[1], "%d", &nAttr);
	sscanf(argv[2], "%d", &tAttr);
	sscanf(argv[3], "%d", &nElem);

	set = newKnnSet(nElem, nAttr);

	for (i=0; i < nElem; i++)
	{
		KnnElement *elem;
		elem = newKnnElement(nAttr);
		for (j=0; j < nAttr; j++)
		{
			fscanf(stdin, "%lf", &(elem->attributes[j]));
		}
		addKnnElement(set, elem, i);
	}

	normalizeSet(set);

	printf("Distance: %lf\n", distance(set->elements[0], set->elements[nElem-1], tAttr));

	return 0;
}
