#include <stdio.h>
#include "knn.h"

int main(int argc, char** argv)
{
	int nAttr;
	int nClass;
	int nElem;
	int nTest;
	int nNeighbours;
	int i, j;
	int weight;
	KnnSet *set;
	KnnSet *training;
	KnnSet *test;

	sscanf(argv[1], "%d", &nAttr);
	sscanf(argv[2], "%d", &nClass);
	sscanf(argv[3], "%d", &nElem);
	sscanf(argv[4], "%d", &nTest);
	sscanf(argv[5], "%d", &nNeighbours);
	sscanf(argv[6], "%d", &weight);

	set = newKnnSet(nElem, nAttr, nClass);
	training = newKnnSet(nElem - nTest, nAttr, nClass);
	test = newKnnSet(nTest, nAttr, nClass);

	for (i=0; i < set->size; i++)
	{
		KnnElement *elem;
		elem = newKnnElement(nAttr, nClass);
		for (j=0; j < nAttr; j++)
		{
			fscanf(stdin, "%lf", &(elem->attributes[j]));
		}
		fscanf(stdin, "%d", &(elem->class));
		addKnnElement(set, elem, i);
	}
	normalizeSet(set);

	for (i=0; i < set->size; i++)
	{
		if (i < training->size)
		{
			addKnnElement(training, set->elements[i], i);
		}
		else
		{
			addKnnElement(test, set->elements[i], i-training->size);
		}
	}

	for (i = 0; i < test->size; i++)
	{
		printClasses(training, test->elements[i], nNeighbours, weight);
	}

	return 0;
}
