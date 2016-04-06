#ifndef ELPS_KNN_H_
#define ELPS_KNN_H_

#include <stdbool.h>

typedef struct knnElement
{
	int size;
	int classes;
	double *attributes;
} KnnElement;

typedef struct knnSet
{
	int size;
	int attributes;
	int classes;
	double *maximum;
	double *minimum;
	KnnElement **elements;
} KnnSet;

KnnElement* newKnnElement(int size, int classes);
void freeKnnElement(KnnElement *elem);
void printKnnElement(KnnElement *elem);
int  getKnnElementClass(KnnElement *elem);

double distanceAll(KnnElement *elemA, KnnElement *elemB);
double distance(KnnElement *elemA, KnnElement *elemB, int attrLen);

KnnSet* newKnnSet(int size, int attributes, int classes);
void freeKnnSet(KnnSet *set);
void addKnnElement(KnnSet *set, KnnElement *element, int pos);
void normalizeSet(KnnSet *set);
void printKnnSet(KnnSet *set);

void printClasses(KnnSet *set, KnnElement *knnElement, int k, bool weight);

#endif
