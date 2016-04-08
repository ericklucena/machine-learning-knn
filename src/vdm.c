#include "vdm.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

// Private functions

void clearMinMax(VdmSet *set)
{
	int i;

	for (i=0; i < set->attributes; i++)
	{
		set->minimum[i] = INT_MAX;
		set->maximum[i] = INT_MIN;
	}
}


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
		printf("%d ", elem->attributes[i]);
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
	VdmSet *set;
	
	set = malloc(sizeof(VdmSet));
	set->size = size;
	set->classes = classes;
	set->attributes = attributes;
	set->elements = malloc(sizeof(VdmElement*)*size);
	set->minimum = malloc(sizeof(int)*attributes);
	set->maximum = malloc(sizeof(int)*attributes);
	
	clearMinMax(set);

	return set;
}

double*** newProbabilityMatrix(int classes, int attributes, int* attributesSizes)
{
	int i, j;
	double ***matrix;

	matrix = malloc(sizeof(double**)*classes);
	for (i = 0; i < classes; i++)
	{
		matrix[i] = calloc(sizeof(double*), attributes);
		for (j=0; j < attributes; j++)
		{
			matrix[i][j] = calloc(sizeof(double), attributesSizes[j]);
		}
	}	

	return matrix;
}

int** newQuantityMatrix(int attributes, int* attributesSizes)
{
	int i;
	int **matrix;

	matrix= calloc(sizeof(int*), attributes);
	for (i = 0; i < attributes; i++)
	{
		matrix[i] = calloc(sizeof(int), attributesSizes[i]);
	}

	return matrix;
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
	int i;
	set->elements[pos] = element;

	for (i=0; i < element->size; i++)
	{
		if(element->attributes[i] < set->minimum[i])
		{
			set->minimum[i] = element->attributes[i];
		}
		if(element->attributes[i] > set->maximum[i])
		{
			set->maximum[i] = element->attributes[i];
		}
	}
}

void calculateProbability(VdmSet *set)
{
	int i, j, k;
	int attributesSizes[set->attributes];
	double ***probability;
	int **quantity;
	VdmElement *element;

	for (i = 0; i < set->attributes; i++)
	{
		attributesSizes[i] = set->maximum[i];
	}

	probability = newProbabilityMatrix(set->classes, set->attributes, attributesSizes);
	quantity = newQuantityMatrix(set->attributes, attributesSizes);

	for (i = 0; i < set->size; i++)
	{
		element = set->elements[i];
		for (j = 0; j < element->size; j++)
		{
			probability[element->class][j][element->attributes[j]]++;
			quantity[j][element->attributes[j]]++;
		}
	}

	for (i = 0; i < set->classes; i++)
	{
		for (j = 0; j < set->attributes; j++)
		{
			for (k = 0; k < attributesSizes[j]; k++)
			{
				probability[i][j][k] /= quantity[j][k];
			}
		}
	}

	set->probability = probability;
	set->attributesSizes = attributesSizes;
	
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
	int i;

	printf("Size: %d\n", set->size);

	printf("Attr Sizes: \n");

	for (i = 0; i < set->attributes; i++)
	{
		printf("%d ", set->attributesSizes[i]);
	}

	printf("\nMin Sizes: \n");

	for (i = 0; i < set->attributes; i++)
	{
		printf("%d ", set->minimum[i]);
	}

	printf("\nMax Sizes: \n");

	for (i = 0; i < set->attributes; i++)
	{
		printf("%d ", set->maximum[i]);
	}

	printf("\nElements: \n");

	for (i = 0; i < set->size; i++)
	{
		printVdmElement(set->elements[i]);
	}
}

