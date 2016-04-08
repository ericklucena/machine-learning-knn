#include <stdio.h>
#include "vdm.h"

int main(int argc, char** argv)
{
	int nAttr;
	int nClass;
	int nElem;
	int nTest;
	int nNeighbours;
	int i, j;
	int weight;
	VdmSet *set;
	VdmSet *training;
	VdmSet *test;

	sscanf(argv[1], "%d", &nAttr);
	sscanf(argv[2], "%d", &nClass);
	sscanf(argv[3], "%d", &nElem);
	sscanf(argv[4], "%d", &nTest);
	sscanf(argv[5], "%d", &nNeighbours);
	sscanf(argv[6], "%d", &weight);

	set = newVdmSet(nElem, nAttr, nClass);
	training = newVdmSet(nElem - nTest, nAttr, nClass);
	test = newVdmSet(nTest, nAttr, nClass);

	for (i=0; i < set->size; i++)
	{
		VdmElement *elem;
		elem = newVdmElement(nAttr, nClass);
		for (j=0; j < nAttr; j++)
		{
			fscanf(stdin, "%d", &(elem->attributes[j]));
		}
		fscanf(stdin, "%d", &(elem->class));

		addVdmElement(set, elem, i);
	}

	for (i=0; i < set->size; i++)
	{
		if (i < training->size)
		{
			addVdmElement(training, set->elements[i], i);
		}
		else
		{
			addVdmElement(test, set->elements[i], i-training->size);
		}
	}
	calculateProbability(training);

	for (i = 0; i < test->size; i++)
	{
		vdmPrintClasses(training, test->elements[i], nNeighbours, weight);
	}

	return 0;
}
