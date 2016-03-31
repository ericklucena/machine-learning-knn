#include "knn.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Private functions

double euclidianDistance(double x, double y)
{
	double distance = x - y;
	return (distance >= 0) ? distance : distance * (-1);
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

KnnSet* newKnnSet(int size)
{
	KnnSet *set;
	set = malloc(sizeof(KnnSet));
	set->size = size;
	set->elements = malloc(sizeof(KnnElement*)*size);

	return set;
}

void freeKnnSet(KnnSet *set)
{
	int i;
	for (i = 0; i < set->size; i++)
	{
		freeKnnElement(set->elements[i]);
	}
	free(set);
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
