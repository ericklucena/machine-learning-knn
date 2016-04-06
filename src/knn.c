#include "knn.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

// Private functions

double euclidianDistance(double x, double y)
{
	double distance = x - y;
	return isnan(distance)?0:distance>0?distance:distance*(-1);
}

int higherIndex(int *array, int size)
{
	int i;
	int index=0;
	int count = array[0];
	
	for (i = 1; i < size; i++)
	{
		if (array[i] > count)
		{
			index = i;
			count = array[i];
		}
	}

	return index;
}

// Public functions

KnnElement* newKnnElement(int size, int classes)
{
	KnnElement *knnElement;

	knnElement = malloc(sizeof(KnnElement));
	knnElement->size = size;
	knnElement->classes = classes;
	knnElement->attributes = calloc(sizeof(double), size);

	return knnElement;
}

void freeKnnElement(KnnElement *elem)
{
	free(elem->attributes);
	free(elem);
}

void printKnnElement(KnnElement *elem)
{
	int i;

	for (i=0; i< elem->size; i++)
	{
		printf("%.2lf ", elem->attributes[i]);
	}
	printf("\n");
}

int  getKnnElementClass(KnnElement *elem)
{
	int i, shift;

	shift = elem->size - elem->classes;

	for (i = 0; i < elem->classes; i++)
	{
		if (elem->attributes[shift + i] >= 1)
		{
			break;
		}
	}

	return i;
}

double distanceAll(KnnElement *elemA, KnnElement *elemB)
{
	return distance(elemA, elemB, elemA->size);
}

double distance(KnnElement *elemA, KnnElement *elemB, int attrLen)
{
	int i;
	double totalDistance = 0;

	for (i=0; i < attrLen; i++)
	{
		totalDistance += euclidianDistance(elemA->attributes[i], elemB->attributes[i]);
	}

	return totalDistance/attrLen;
}

void clearMinMax(KnnSet *set)
{
	int i;

	for (i=0; i < set->attributes; i++)
	{
		set->minimum[i] = DBL_MAX;
		set->maximum[i] = -DBL_MAX;
	}
}

KnnSet* newKnnSet(int size, int attributes, int classes)
{
	KnnSet *set;
	set = malloc(sizeof(KnnSet));
	set->size = size;
	set->classes = classes;
	set->attributes = attributes;
	set->elements = malloc(sizeof(KnnElement*)*size);
	set->minimum = malloc(sizeof(double)*attributes);
	set->maximum = malloc(sizeof(double)*attributes);

	clearMinMax(set);

	return set;
}

void freeKnnSet(KnnSet *set)
{
	int i;
	for (i = 0; i < set->size; i++)
	{
		freeKnnElement(set->elements[i]);
	}
	free(set->elements);
	free(set->minimum);
	free(set->maximum);
	free(set);
}

void addKnnElement(KnnSet *set, KnnElement *element, int pos)
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

void normalizeSet(KnnSet *set)
{
	int i, j;
	for (i = 0; i < set->size; i++)
	{
		for(j = 0; j < set->elements[i]->size; j++)
		{
			set->elements[i]->attributes[j] = (set->elements[i]->attributes[j] - set->minimum[j]) / (set->maximum[j] - set->minimum[j]);
		}
	}
}

void printClasses(KnnSet *set, KnnElement *knnElement, int k)
{
	int i, j;
	int neighbours[k];
	int classes[set->classes];

	for (i = 0; i < k; i++)
	{
		neighbours[i] = i;
	}

	for (i = 0; i < set->classes; i++)
	{
		classes[i] = 0;
	}


	for (j = k+1; j < set->size; j++)
	{
		for (i = 0; i < k; i++)
		{
			if (distance(knnElement, set->elements[j], set->attributes) < distance(knnElement, set->elements[neighbours[i]], set->attributes))
			{
				neighbours[i] = j;
				break;
			}

		}
	}

	for (i = 0; i < k; i++)
	{
		classes[getKnnElementClass(set->elements[neighbours[i]])]++;
	}

	printf("%d\t%d\n", getKnnElementClass(knnElement), higherIndex(classes, k));
}

void printClassesByIndex(KnnSet *set, int index, int k)
{
	int i, j;
	int neighbours[k];
	int classes[set->classes];

	for (i = 0, j = 0; i < k; i++)
	{
		if (i==index) // Skip if index is among the first k elements
		{
			j++;
		}
		neighbours[i] = i+j;
	}

	for (i = 0; i < set->classes; i++)
	{
		classes[i] = 0;
	}

	for (j += k+1; j < set->size; j++)
	{
		if (j==index)
		{
			continue;
		}
		for (i = 0; i < k; i++)
		{
			if (distance(set->elements[index], set->elements[j], set->attributes) < distance(set->elements[index], set->elements[neighbours[i]], set->attributes))
			{
				neighbours[i] = j;
				break;
			}

		}
	}

	for (i = 0; i < k; i++)
	{
		classes[getKnnElementClass(set->elements[neighbours[i]])]++;
	}

	printf("%d\t%d\n", getKnnElementClass(set->elements[index]), higherIndex(classes, set->classes));
}

void printKnnSet(KnnSet *set)
{
	int i;
	printf("Size: %d\n", set->size);
	printf("Minimum: ");
	for (i = 0; i< set->attributes; i++)
	{
		printf("%lf ", set->minimum[i]);
	}
	printf("\n");
	printf("Maximum: ");
	for (i = 0; i< set->attributes; i++)
	{
		printf("%lf ", set->maximum[i]);
	}
	printf("\n");
}




