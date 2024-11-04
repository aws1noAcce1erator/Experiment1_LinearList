#include "PolyNode.h"
// 创建多项式的有序单链表
// 输入头指针 系数和指数序列 以及多项式的项数
void createPoly(Polynomial& PL, const int terms[][2], int n) {
    PL = new PolyNode; // 创建头结点
    PL->next = nullptr;


    for (int i = 0; i < n; i++) {
        int coef = terms[i][0];
        int exp = terms[i][1];

        // 创建新节点
        PolyNode* temp = new PolyNode;
        temp->data[0] = coef;
        temp->data[1] = exp;
        temp->next = NULL;

        // 每个节点按指数降幂排列
        // 为了不修改头指针poly，创建两个指针
        PolyNode* prev = PL;
        PolyNode* curr = PL->next;
        // 如果到达链表尾部
        // 或者当前节点的指数小于新节点的指数
        while (curr != NULL && curr->data[1] > exp)
        {
            prev = curr;
            curr = curr->next;
        }
        // 插入新节点
        temp->next = curr;
        prev->next = temp;
    }
}


void printPoly(Polynomial& PL) {
    PolyNode* head = PL->next; // 真正的头指针
    while (head != nullptr) {
        // 修正：指数为1或0时不输出指数
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
    PL = nullptr; // 将头指针置为空，表示链表已被销毁
}


// 计算一元多项式在x处的值
double calValue(Polynomial PL, double x) {
    double result = 0;
    PolyNode* head = PL->next; // 真正的头指针
    while (head != nullptr) {
        result += head->data[0] * pow(x, head->data[1]);
        head = head->next;
    }
    return result;
}

// 修正：将导函数输出到新链表中
// 求一元多项式的一阶导函数
void derivative(const Polynomial PL, Polynomial& PD) {
    PD = new PolyNode; // 创建导数多项式的头节点
    PD->next = nullptr;

    PolyNode* curr = PL->next; // 从原多项式的第一个节点开始
    PolyNode* rear = PD;       // 用于构建导数链表的尾指针

    while (curr != nullptr) {
        int coef = curr->data[0] * curr->data[1]; // 计算导数系数
        int exp = curr->data[1] - 1;              // 计算导数指数

        // 修正：导数项的系数为0时不添加到链表
                // 常数项的导数为0，不加入链表
        if (curr->data[1] != 0) {
            // 创建新的导数项节点
            PolyNode* temp = new PolyNode;
            temp->data[0] = coef;
            temp->data[1] = exp;
            temp->next = nullptr;

            // 将新节点添加到结果链表的尾部
            rear->next = temp;
            rear = temp; // 导数链表更新尾指针
        }

        curr = curr->next; // 移动到下一个节点
    }
}



// 将按指数降幂排列的一元多项式原地逆置，使其按指数升幂排列
void reverse(Polynomial& PL) {
    PolyNode* prev = PL->next; // 真正的头指针
    PolyNode* curr = prev->next;
    prev->next = nullptr; // 逆序，头指针成为末尾

    while (curr != nullptr) {
        // 操作部分
        PolyNode* next = curr->next; // 保存下一个节点
        curr->next = prev; // 当前节点指向前一个节点

        // prev和curr分别向后移动一位
        prev = curr;
        curr = next;
        // 重复上述操作
    }
    PL->next = prev;
}

// 实现两个一元多项式的相加运算
// 二路归并
void add(Polynomial PA, Polynomial PB, Polynomial& PC) {
    PC = new PolyNode; // 创建输出的头结点
    PC->next = nullptr;
    PolyNode* rear = PC; // 尾指针，始终在输出的尾部

    PolyNode* currA = PA->next; // 从第一个实际节点开始
    PolyNode* currB = PB->next;

    // 循环条件能统一处理PA和PB中有一个为空的情况
    while (currA && currB) {
        PolyNode* temp = new PolyNode;
        temp->next = nullptr;

        if (currA->data[1] > currB->data[1]) {
            // 如果PA的当前项指数更大，复制
            temp->data[0] = currA->data[0];
            temp->data[1] = currA->data[1];
            currA = currA->next;
        }
        else if (currA->data[1] < currB->data[1]) {
            // 如果PB的当前项指数更大，复制
            temp->data[0] = currB->data[0];
            temp->data[1] = currB->data[1];
            currB = currB->next;
        }
        else {
            // 如果指数相同，系数相加
            temp->data[0] = currA->data[0] + currB->data[0];
            temp->data[1] = currA->data[1];
            currA = currA->next;
            currB = currB->next;
        }

        // 将输入并入输出的部分

        // 仅当系数不为零时，将新项加入输出
        // // 示例中8次方的系数之和为0，不添加到输出
        if (temp->data[0] != 0) {
            rear->next = temp;
            rear = temp;
        }
        else {
            delete temp; // 避免添加系数为零的项
        }
    }

    // PA或PB中有一个已经遍历结束
    // 将另一个多项式的剩余项加入输出
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

// 实现两个一元多项式的相乘运算
void multiply(Polynomial PA, Polynomial PB, Polynomial& PC) {
    PC = new PolyNode; // 创建输出的头节点
    PC->next = nullptr;

    // 遍历 PA 的每一项
    for (PolyNode* currA = PA->next; currA != nullptr; currA = currA->next) {
        // 遍历 PB 的每一项
        for (PolyNode* currB = PB->next; currB != nullptr; currB = currB->next) {
            // 计算当前两项的系数和指数
            int coef = currA->data[0] * currB->data[0];
            int exp = currA->data[1] + currB->data[1];

            // 将新的项合并到输出中
            PolyNode* prev = PC;
            PolyNode* curr = PC->next;

            // 找到正确的位置插入（按指数降幂排列）
            while (curr != nullptr && curr->data[1] > exp) {
                prev = curr;
                curr = curr->next;
            }

            if (curr != nullptr && curr->data[1] == exp) {
                // 如果当前指数相同，累加系数
                curr->data[0] += coef;
                if (curr->data[0] == 0) {
                    // 如果系数为零，删除该节点
                    prev->next = curr->next;
                    delete curr;
                }
            }
            else {
                // 插入新节点
                PolyNode* temp = new PolyNode;
                temp->data[0] = coef;
                temp->data[1] = exp;
                temp->next = curr;
                prev->next = temp;
            }
        }
    }
}


