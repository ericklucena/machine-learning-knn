#ifndef ELPS_KNN_H_
#define ELPS_KNN_H_

typedef struct knnElement
{
	int size;
	double *attributes;
} KnnElement;

typedef struct knnSet
{
	int size;
	KnnElement **elements;
} KnnSet;

KnnElement* newKnnElement(int size);
void freeKnnElement(KnnElement *elem);

void printKnnElement(KnnElement *elem);

KnnSet* newKnnSet(int size);
void freeKnnSet(KnnSet *set);

double distanceAll(KnnElement *elemA, KnnElement *elemB);
double distance(KnnElement *elemA, KnnElement *elemB, int attrLen);

#endif
