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

// Public functions

KnnElement* newKnnElement(int size)
{
	KnnElement *knnElement;

	knnElement = malloc(sizeof(KnnElement));
	knnElement->size = size;
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
		printf("%lf ", elem->attributes[i]);
	}
	printf("\n");
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

KnnSet* newKnnSet(int size, int attributes)
{
	KnnSet *set;
	set = malloc(sizeof(KnnSet));
	set->size = size;
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
