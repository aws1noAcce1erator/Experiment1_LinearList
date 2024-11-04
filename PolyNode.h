#ifndef POLYNODE_H
#define POLYNODE_H
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
using namespace std;

typedef struct pnode
{
	int data[2]; // data[0] 存储系数, data[1] 存储指数
	struct pnode* next;
} PolyNode, * Polynomial;
#endif
#pragma once
