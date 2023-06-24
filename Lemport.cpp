#include <iostream>
#include <cstring>
#include <string>
using namespace std;
/*
Баклан Аліса МІ-3

На і-ій автонтефікації потенційно відомі зловмиснику дані : H^t(w), H^t-1(w), ... , H^t-i.
Щоб імітувати клієнта на i+1 ітерації, треба дізнатися H^t-i-1, що зводиться до задачі обернення hash-фукції по її значенню

*/


//Проста hash функція для прикладу (не використовується в справжніх системах)
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

//Клієнт 
class Client {
private: 
    const char* password; //приватний ключ-пароль w

    unsigned long superposition(int n) { //функція-супераозиція H^n(w)
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
    //t - кількість раундів комунікації
    int t = 100;

    Client A;
    //А обчислює w0 = H^t(w), де w - особистий пароль клієнта.
    unsigned long w0 = A.send_to_server(t);
    //w0 - спільний секрет A i B

    unsigned long curr_w;
    unsigned long prev_w = w0;
    cout << "=========================================" << endl;
    for (int i = 1; i < t; i++) {
        cout << i <<"-та  автентифiкацiя" << endl;
        //А обчислює H^(t-i) і передає серверу.
        curr_w = A.send_to_server(t - i);

        cout << "A_i hash: "<<curr_w<<"  B_i hash: " << fhash(to_string(curr_w).c_str()) << endl;


        //B перевіряє, чи H(w_i) = w_i-1
        if (fhash(to_string(curr_w).c_str()) == prev_w) {
             //автонтефікація і пройшла успішно
            cout<<"Успiшно" << endl;
            prev_w = curr_w;
        }
        else {
            cout <<"Помилка: автентифiкацiя " <<i<<" не пройдена" << endl;
            break;
        }
        cout << "==========================================" << endl;

    }
    cout << "===================THE END=======================" << endl;
}

