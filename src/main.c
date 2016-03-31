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

	printf("%d\n", nElem);

	set = newKnnSet(nElem);

	for (i=0; i < nElem; i++)
	{
		set->elements[i] = newKnnElement(nAttr);
		for (j=0; j < nAttr; j++)
		{
			fscanf(stdin, "%lf", &(set->elements[i]->attributes[j]));
		}
	}

	for (i=0; i < nElem; i++)
	{
		printKnnElement(set->elements[i]);
	}

	printf("Distance: %lf\n", distance(set->elements[0], set->elements[1], tAttr));

	return 0;
}
