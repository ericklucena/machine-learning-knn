#include "vdm.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>

// Public functions

VdmElement* newVdmElement(int size, int classes)
{
	VdmElement *vdmElement;

	vdmElement = malloc(sizeof(VdmElement));
	vdmElement->size = size;
	vdmElement->classes = classes;
	vdmElement->attributes = calloc(sizeof(int), size);

	return vdmElement;
}

void freeVdmElement(VdmElement *elem)
{
	free(elem->attributes);
	free(elem);
}

void printVdmElement(VdmElement *elem)
{
	int i;

	for (i=0; i< elem->size; i++)
	{
		printf("%.d ", elem->attributes[i]);
	}
	printf("\n");
}

int  getVdmElementClass(VdmElement *elem)
{
	return elem->attributes[elem->size-1];
}

double vdmDistance(VdmElement *elemA, VdmElement *elemB, int attrLen)
{
	// TODO
	return 0.0;
}

VdmSet* newVdmSet(int size, int attributes, int classes)
{
	int i;
	VdmSet *set;
	
	set = malloc(sizeof(VdmSet));
	set->size = size;
	set->classes = classes;
	set->attributes = attributes;
	set->elements = malloc(sizeof(VdmElement*)*size);
	
	set->probability = malloc(sizeof(double*)*classes);
	for (i = 0; i < classes; i++)
	{
		set->probability[i] = calloc(sizeof(double), size);		
	}

	return set;
}

void freeVdmSet(VdmSet *set)
{
	int i;
	for (i = 0; i < set->size; i++)
	{
		freeVdmElement(set->elements[i]);
	}
	free(set->elements);
	free(set);
}

void addVdmElement(VdmSet *set, VdmElement *element, int pos)
{
	set->elements[pos] = element;
}

void vdmPrintClasses(VdmSet *set, VdmElement *vdmElement, int k, bool weight)
{
	int i, j;
	int neighbours[k];
	int classes[set->classes];
	int farest=0;
	double greaterDistance=0;

	for (i = 0; i < k; i++)
	{
		neighbours[i] = i;
		if (vdmDistance(vdmElement, set->elements[i], set->attributes-set->classes) > greaterDistance)
		{
			greaterDistance = vdmDistance(vdmElement, set->elements[i], set->attributes-set->classes);
			farest = i;
		}

	}

	for (i = 0; i < set->classes; i++)
	{
		classes[i] = 0;
	}


	for (j = k+1; j < set->size; j++)
	{
		if (vdmDistance(vdmElement, set->elements[j], set->attributes-set->classes) < greaterDistance)
		{
			neighbours[farest] = j;
			greaterDistance = vdmDistance(vdmElement, set->elements[j], set->attributes-set->classes);

			for (i = 0; i < k; i++)
			{
				if (vdmDistance(vdmElement, set->elements[neighbours[i]], set->attributes-set->classes) > greaterDistance)
				{
					greaterDistance = vdmDistance(vdmElement, set->elements[neighbours[i]], set->attributes-set->classes);
					farest = i;
				}
			}
		}
	}

	for (i = 0; i < k; i++)
	{
		//printVdmElement(set->elements[neighbours[i]]);
		if (weight)
		{
			classes[getVdmElementClass(set->elements[neighbours[i]])] += 1.0/vdmDistance(vdmElement, set->elements[neighbours[i]], set->attributes-set->classes);
		}
		else
		{
			classes[getVdmElementClass(set->elements[neighbours[i]])]++;
		}
	}

	//printf("%d\t%d\n", getVdmElementClass(vdmElement), higherIndex(classes, set->classes));
	//printf("%d\t%d\t%d\n", getVdmElementClass(vdmElement), higherIndex(classes, set->classes), classes[higherIndex(classes, set->classes)]);
}

void printVdmSet(VdmSet *set)
{
	printf("Size: %d\n", set->size);
}




