#ifndef ELPS_VDM_H_
#define ELPS_VDM_H_

#include <stdbool.h>

typedef struct vdmElement
{
	int size;
	int classes;
	int *attributes;
} VdmElement;

typedef struct vdmSet
{
	int size;
	int attributes;
	int classes;
	double **probability;
	VdmElement **elements;
} VdmSet;

VdmElement* newVdmElement(int size, int classes);
void freeVdmElement(VdmElement *elem);
void printVdmElement(VdmElement *elem);
int  getVdmElementClass(VdmElement *elem);

double vdmDistance(VdmElement *elemA, VdmElement *elemB, int attrLen);

VdmSet* newVdmSet(int size, int attributes, int classes);
void freeVdmSet(VdmSet *set);
void addVdmElement(VdmSet *set, VdmElement *element, int pos);
void printVdmSet(VdmSet *set);

void vdmPrintClasses(VdmSet *set, VdmElement *vdmElement, int k, bool weight);

#endif
