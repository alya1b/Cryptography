#include <iostream>
#include <cstring>
#include <string>
using namespace std;
/*
������ ���� ̲-3

�� �-�� �������������� ���������� ���� ����������� ��� : H^t(w), H^t-1(w), ... , H^t-i.
��� �������� �볺��� �� i+1 ��������, ����� �������� H^t-i-1, �� ��������� �� ������ ��������� hash-������ �� �� ��������

*/


//������ hash ������� ��� �������� (�� ��������������� � �������� ��������)
/*
djb2 algorithm: multiply the current hash value by 33 and add the next character. The constant 5381 is used as the initial hash value.
*/
unsigned long fhash(const char* str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

//�볺�� 
class Client {
private: 
    const char* password; //��������� ����-������ w

    unsigned long superposition(int n) { //�������-������������ H^n(w)
        unsigned long hash = fhash(password);
        for (int i = 1; i < n; i++)
        {
            hash = fhash(to_string(hash).c_str());
        }
        return hash;
    }
public:
    Client() {
        this->password = "qklrbszyhyjlihpgdrkdrha"; 
    }
    unsigned long send_to_server(int n) {
        return superposition(n);
    }
};

int main()
{
    setlocale(LC_ALL,"ukr");
    //t - ������� ������ ����������
    int t = 100;

    Client A;
    //� �������� w0 = H^t(w), �� w - ��������� ������ �볺���.
    unsigned long w0 = A.send_to_server(t);
    //w0 - ������� ������ A i B

    unsigned long curr_w;
    unsigned long prev_w = w0;
    cout << "=========================================" << endl;
    for (int i = 1; i < t; i++) {
        cout << i <<"-��  ��������i���i�" << endl;
        //� �������� H^(t-i) � ������ �������.
        curr_w = A.send_to_server(t - i);

        cout << "A_i hash: "<<curr_w<<"  B_i hash: " << fhash(to_string(curr_w).c_str()) << endl;


        //B ��������, �� H(w_i) = w_i-1
        if (fhash(to_string(curr_w).c_str()) == prev_w) {
             //�������������� � ������� ������
            cout<<"���i���" << endl;
            prev_w = curr_w;
        }
        else {
            cout <<"�������: ��������i���i� " <<i<<" �� ��������" << endl;
            break;
        }
        cout << "==========================================" << endl;

    }
    cout << "===================THE END=======================" << endl;
}

