#include "PolyNode.h"
// ��������ʽ����������
// ����ͷָ�� ϵ����ָ������ �Լ�����ʽ������
void createPoly(Polynomial& PL, const int terms[][2], int n) {
    PL = new PolyNode; // ����ͷ���
    PL->next = nullptr;


    for (int i = 0; i < n; i++) {
        int coef = terms[i][0];
        int exp = terms[i][1];

        // �����½ڵ�
        PolyNode* temp = new PolyNode;
        temp->data[0] = coef;
        temp->data[1] = exp;
        temp->next = NULL;

        // ÿ���ڵ㰴ָ����������
        // Ϊ�˲��޸�ͷָ��poly����������ָ��
        PolyNode* prev = PL;
        PolyNode* curr = PL->next;
        // �����������β��
        // ���ߵ�ǰ�ڵ��ָ��С���½ڵ��ָ��
        while (curr != NULL && curr->data[1] > exp)
        {
            prev = curr;
            curr = curr->next;
        }
        // �����½ڵ�
        temp->next = curr;
        prev->next = temp;
    }
}


void printPoly(Polynomial& PL) {
    PolyNode* head = PL->next; // ������ͷָ��
    while (head != nullptr) {
        // ������ָ��Ϊ1��0ʱ�����ָ��
        if (head->data[1] != 1 && head->data[1] != 0)
            cout << head->data[0] << "x^" << head->data[1];
        else if (head->data[1] == 1)
            cout << head->data[0] << "x";
        else if (head->data[1] == 0)
            cout << head->data[0];
        if (head->next != nullptr) cout << " + ";
        head = head->next;
    }
    cout << endl;
}


void destroyPoly(Polynomial& PL) {
    PolyNode* curr = PL;
    while (curr != nullptr) {
        PolyNode* next = curr->next;
        delete curr;
        curr = next;
    }
    PL = nullptr; // ��ͷָ����Ϊ�գ���ʾ�����ѱ�����
}


// ����һԪ����ʽ��x����ֵ
double calValue(Polynomial PL, double x) {
    double result = 0;
    PolyNode* head = PL->next; // ������ͷָ��
    while (head != nullptr) {
        result += head->data[0] * pow(x, head->data[1]);
        head = head->next;
    }
    return result;
}

// ���������������������������
// ��һԪ����ʽ��һ�׵�����
void derivative(const Polynomial PL, Polynomial& PD) {
    PD = new PolyNode; // ������������ʽ��ͷ�ڵ�
    PD->next = nullptr;

    PolyNode* curr = PL->next; // ��ԭ����ʽ�ĵ�һ���ڵ㿪ʼ
    PolyNode* rear = PD;       // ���ڹ������������βָ��

    while (curr != nullptr) {
        int coef = curr->data[0] * curr->data[1]; // ���㵼��ϵ��
        int exp = curr->data[1] - 1;              // ���㵼��ָ��

        // �������������ϵ��Ϊ0ʱ����ӵ�����
                // ������ĵ���Ϊ0������������
        if (curr->data[1] != 0) {
            // �����µĵ�����ڵ�
            PolyNode* temp = new PolyNode;
            temp->data[0] = coef;
            temp->data[1] = exp;
            temp->next = nullptr;

            // ���½ڵ���ӵ���������β��
            rear->next = temp;
            rear = temp; // �����������βָ��
        }

        curr = curr->next; // �ƶ�����һ���ڵ�
    }
}



// ����ָ���������е�һԪ����ʽԭ�����ã�ʹ�䰴ָ����������
void reverse(Polynomial& PL) {
    PolyNode* prev = PL->next; // ������ͷָ��
    PolyNode* curr = prev->next;
    prev->next = nullptr; // ����ͷָ���Ϊĩβ

    while (curr != nullptr) {
        // ��������
        PolyNode* next = curr->next; // ������һ���ڵ�
        curr->next = prev; // ��ǰ�ڵ�ָ��ǰһ���ڵ�

        // prev��curr�ֱ�����ƶ�һλ
        prev = curr;
        curr = next;
        // �ظ���������
    }
    PL->next = prev;
}

// ʵ������һԪ����ʽ���������
// ��·�鲢
void add(Polynomial PA, Polynomial PB, Polynomial& PC) {
    PC = new PolyNode; // ���������ͷ���
    PC->next = nullptr;
    PolyNode* rear = PC; // βָ�룬ʼ���������β��

    PolyNode* currA = PA->next; // �ӵ�һ��ʵ�ʽڵ㿪ʼ
    PolyNode* currB = PB->next;

    // ѭ��������ͳһ����PA��PB����һ��Ϊ�յ����
    while (currA && currB) {
        PolyNode* temp = new PolyNode;
        temp->next = nullptr;

        if (currA->data[1] > currB->data[1]) {
            // ���PA�ĵ�ǰ��ָ�����󣬸���
            temp->data[0] = currA->data[0];
            temp->data[1] = currA->data[1];
            currA = currA->next;
        }
        else if (currA->data[1] < currB->data[1]) {
            // ���PB�ĵ�ǰ��ָ�����󣬸���
            temp->data[0] = currB->data[0];
            temp->data[1] = currB->data[1];
            currB = currB->next;
        }
        else {
            // ���ָ����ͬ��ϵ�����
            temp->data[0] = currA->data[0] + currB->data[0];
            temp->data[1] = currA->data[1];
            currA = currA->next;
            currB = currB->next;
        }

        // �����벢������Ĳ���

        // ����ϵ����Ϊ��ʱ��������������
        // // ʾ����8�η���ϵ��֮��Ϊ0������ӵ����
        if (temp->data[0] != 0) {
            rear->next = temp;
            rear = temp;
        }
        else {
            delete temp; // �������ϵ��Ϊ�����
        }
    }

    // PA��PB����һ���Ѿ���������
    // ����һ������ʽ��ʣ����������
    while (currA != nullptr) {
        PolyNode* temp = new PolyNode;
        temp->data[0] = currA->data[0];
        temp->data[1] = currA->data[1];
        temp->next = nullptr;
        rear->next = temp;
        rear = temp;
        currA = currA->next;
    }

    while (currB != nullptr) {
        PolyNode* temp = new PolyNode;
        temp->data[0] = currB->data[0];
        temp->data[1] = currB->data[1];
        temp->next = nullptr;
        rear->next = temp;
        rear = temp;
        currB = currB->next;
    }
}

// ʵ������һԪ����ʽ���������
void multiply(Polynomial PA, Polynomial PB, Polynomial& PC) {
    PC = new PolyNode; // ���������ͷ�ڵ�
    PC->next = nullptr;

    // ���� PA ��ÿһ��
    for (PolyNode* currA = PA->next; currA != nullptr; currA = currA->next) {
        // ���� PB ��ÿһ��
        for (PolyNode* currB = PB->next; currB != nullptr; currB = currB->next) {
            // ���㵱ǰ�����ϵ����ָ��
            int coef = currA->data[0] * currB->data[0];
            int exp = currA->data[1] + currB->data[1];

            // ���µ���ϲ��������
            PolyNode* prev = PC;
            PolyNode* curr = PC->next;

            // �ҵ���ȷ��λ�ò��루��ָ���������У�
            while (curr != nullptr && curr->data[1] > exp) {
                prev = curr;
                curr = curr->next;
            }

            if (curr != nullptr && curr->data[1] == exp) {
                // �����ǰָ����ͬ���ۼ�ϵ��
                curr->data[0] += coef;
                if (curr->data[0] == 0) {
                    // ���ϵ��Ϊ�㣬ɾ���ýڵ�
                    prev->next = curr->next;
                    delete curr;
                }
            }
            else {
                // �����½ڵ�
                PolyNode* temp = new PolyNode;
                temp->data[0] = coef;
                temp->data[1] = exp;
                temp->next = curr;
                prev->next = temp;
            }
        }
    }
}


