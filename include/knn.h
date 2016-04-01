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
	int attributes;
	double *maximum;
	double *minimum;
	KnnElement **elements;
} KnnSet;

KnnElement* newKnnElement(int size);
void freeKnnElement(KnnElement *elem);
void printKnnElement(KnnElement *elem);

KnnSet* newKnnSet(int size, int attributes);
void freeKnnSet(KnnSet *set);
void addKnnElement(KnnSet *set, KnnElement *element, int pos);
void normalizeSet(KnnSet *set);
void printKnnSet(KnnSet *set);

double distanceAll(KnnElement *elemA, KnnElement *elemB);
double distance(KnnElement *elemA, KnnElement *elemB, int attrLen);

#endif
