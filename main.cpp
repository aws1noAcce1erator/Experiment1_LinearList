// 1. ʹ�ô�ͷ������������洢һԪ����ʽ��Ҫ�����н�㰴ָ���������С�
#include "PolyNode.h"

void createPoly(Polynomial& poly, const int terms[][2], int n);

void printPoly(Polynomial& PL);

void destroyPoly(Polynomial& poly);

// 2. ʵ��һԪ����ʽ�Ļ������� 
double calValue(Polynomial PL, double x);

void derivative(const Polynomial PL, Polynomial& PD);

void reverse(Polynomial& PL);

void add(Polynomial PA, Polynomial PB, Polynomial& PC);

void multiply(Polynomial PA, Polynomial PB, Polynomial& PC);

// ��� һ����������ʱ��Ӧ���ָ��
int main() {
    Polynomial A, B, C, C0, D;

    // 1) �������������һԪ����ʽ
    int termsA[][2] = { {5, 17}, {9, 8}, {3, 1}, {7, 0} };
    int termsB[][2] = { {-9, 8}, {22, 7}, {8, 1} };
    createPoly(A, termsA, 4);
    createPoly(B, termsB, 3);

    cout << "1)\t" << "A(x) = ";
    printPoly(A);
    cout << "\tB(x) = ";
    printPoly(B);

    // 2) ������һԪ����ʽ�ĺ� C(x)=C(x)+C(x)�������
    add(A, B, C);
    cout << "\n2)\tC(x) = A(x) + B(x) = ";
    printPoly(C);

    // 3) ��һԪ����ʽ C(x) ��һ�׵��� C��(x)�������
    derivative(C, C0);
    cout << "\n3)\tC'(x) = ";
    printPoly(C0);
    destroyPoly(C0);

    // 4) �� C��(x) �� x=�� ʱ��ֵ 
    double valueAtPi = calValue(C, M_PI);
    cout << "\n4)\tx = ��ʱ��C'(��)= " << valueAtPi << endl;

    // 5) �� C(x) ԭ�����ò����
    reverse(C);
    cout << "\n5)\t���ã�C(x) = ";
    printPoly(C);

    // 6) ѡ��������������ʽ�ĳ˻� D(x) = A(x) * B(x)�������
    multiply(A, B, D);
    cout << "\n6)\t�˻���D(x) = A(x) * B(x) = ";
    printPoly(D);

    // �ͷ��ڴ�
    destroyPoly(A);
    destroyPoly(B);
    destroyPoly(C);
    destroyPoly(D);

    return 0;
}







