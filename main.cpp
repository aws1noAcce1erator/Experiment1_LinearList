// 1. 使用带头结点的有序单链表存储一元多项式，要求所有结点按指数降幂排列。
#include "PolyNode.h"

void createPoly(Polynomial& poly, const int terms[][2], int n);

void printPoly(Polynomial& PL);

void destroyPoly(Polynomial& poly);

// 2. 实现一元多项式的基本运算 
double calValue(Polynomial PL, double x);

void derivative(const Polynomial PL, Polynomial& PD);

void reverse(Polynomial& PL);

void add(Polynomial PA, Polynomial PB, Polynomial& PC);

void multiply(Polynomial PA, Polynomial PB, Polynomial& PC);

// 输出 一次项和零次项时不应输出指数
int main() {
    Polynomial A, B, C, C0, D;

    // 1) 创建并输出两个一元多项式
    int termsA[][2] = { {5, 17}, {9, 8}, {3, 1}, {7, 0} };
    int termsB[][2] = { {-9, 8}, {22, 7}, {8, 1} };
    createPoly(A, termsA, 4);
    createPoly(B, termsB, 3);

    cout << "1)\t" << "A(x) = ";
    printPoly(A);
    cout << "\tB(x) = ";
    printPoly(B);

    // 2) 求两个一元多项式的和 C(x)=C(x)+C(x)，并输出
    add(A, B, C);
    cout << "\n2)\tC(x) = A(x) + B(x) = ";
    printPoly(C);

    // 3) 求一元多项式 C(x) 的一阶导数 C′(x)，并输出
    derivative(C, C0);
    cout << "\n3)\tC'(x) = ";
    printPoly(C0);
    destroyPoly(C0);

    // 4) 求 C′(x) 在 x=π 时的值 
    double valueAtPi = calValue(C, M_PI);
    cout << "\n4)\tx = π时，C'(π)= " << valueAtPi << endl;

    // 5) 将 C(x) 原地逆置并输出
    reverse(C);
    cout << "\n5)\t逆置：C(x) = ";
    printPoly(C);

    // 6) 选做：求两个多项式的乘积 D(x) = A(x) * B(x)，并输出
    multiply(A, B, D);
    cout << "\n6)\t乘积：D(x) = A(x) * B(x) = ";
    printPoly(D);

    // 释放内存
    destroyPoly(A);
    destroyPoly(B);
    destroyPoly(C);
    destroyPoly(D);

    return 0;
}







