/*сигнатура
p  m      | * / | ^     |  + - | выбор большего, меньшего < > = не равно # | отрицание ~| конъюнкция & | дизъюнкция !
правая     левая  левая    левая                левая                           правая        левая          левая
*/
// експонента, натуральный логарифм

#include "stack.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

void reversestack(StackList&);
StackList copystack(StackList&);
string schet_1(string, string, string,string,string);
string schet_2(string, string, string);
string ob(string, string, string, string, string);
string unitar(string, string);
string otr(string, string,string,string);
string getErr(int);
double naturalLog(double);
double exponent(double);

struct Sign {
	int sign;
	string znak;
};

Sign signature(string str) {
	Sign sign;
	if (str == "(" || str == ")") 
	{
		sign.sign = 0;
		sign.znak = "right";
	}
	else if (str=="p" || str=="m")
	{
		sign.sign=8;
		sign.znak = "right";
	}
	else if (str == "*" || str == "/") {
		sign.sign = 7;
		sign.znak = "left";
	}
	else if (str == "^") {
		sign.sign = 6;
		sign.znak = "left";
	}
	else if (str == "+" || str == "-") {
		sign.sign = 5;
		sign.znak = "left";
	}
	else if (str == "<" || str == ">" || str=="=" || str=="#") {
		sign.sign = 4;
		sign.znak = "left";
	}
	else if (str == "~") {
		sign.sign = 3;
		sign.znak = "right";
	}
	else if (str == "&") {
		sign.sign = 2;
		sign.znak = "left";
	}
	else if (str == "!") {
		sign.sign = 1;
		sign.znak = "left";
	}
    else {
        cout << getErr(4)<<endl;
        return {};
    }
	return sign;
}


vector <string> metod_Deykstra(string str, StackList& stack_R, StackList& stack_bool, StackList& stack_select, StackList& stack_operation) {
    vector <Sign> sign;
    vector <string> opz;
    int schetchik = 0;
    int temp = 0;
    string tempr;

    for (int i = 0; i < str.size(); i++) {
        // Числа
        if (isdigit(str[i])) {
            tempr = str[i];
            temp = i;
            while (temp + 1 < str.size() && isdigit(str[temp + 1])) {
                temp++;
                tempr += str[temp];
            }
            i = temp;
            stack_R.push_str(tempr);
            stack_select.push_str("R");
        }
        // Булевые значения
        else if (isalpha(str[i])) {
            tempr = str[i];
            temp = i;
            while (temp + 1 < str.size() && isalpha(str[temp + 1])) {
                temp++;
                tempr += str[temp];
            }
            i = temp;

            if (tempr != "true" && tempr != "false" && tempr != "p" && tempr != "m") {
                cout << getErr(5);
                return {};
            }

            if (tempr == "p" || tempr == "m") {
                stack_operation.push_str(tempr);
                sign.push_back(signature(tempr));
                schetchik++;
            }
            else {
                stack_bool.push_str(tempr);
                stack_select.push_str("B");
            }
        }
        // Открывающая скобка
        else if (str[i] == '(') {
            tempr = str[i];
            stack_operation.push_str(tempr);
        }
        // Закрывающая скобка
        else if (str[i] == ')') {
            reversestack(stack_select);
            reversestack(stack_R);
            reversestack(stack_bool);

            while (!stack_select.empty()) {
                if (stack_select.top() == "R") {
                    opz.push_back(stack_R.top());
                    stack_select.pop();
                    stack_R.pop();
                }
                else if (stack_select.top() == "B") {
                    opz.push_back(stack_bool.top());
                    stack_select.pop();
                    stack_bool.pop();
                }
            }

            while (!stack_operation.empty() && stack_operation.top() != "(") {
                opz.push_back(stack_operation.top());
                stack_operation.pop();
                if (!sign.empty()) {
                    sign.pop_back();
                    schetchik--;
                }
            }

            if (!stack_operation.empty() && stack_operation.top() == "(") {
                stack_operation.pop();
            }
            /*else if (stack_operation.empty()) {
                cout << getErr(7);
                return {};
            }*/
        }
        // Операции
        else {
            if (stack_select.empty() && str[i] != '~' && opz.empty()) {
                cout << getErr(8);
                return {};
            }
            tempr = str[i];
            Sign signat = signature(tempr);
            sign.push_back(signat);

            if (stack_operation.empty() || stack_operation.top() == "(") {
                stack_operation.push_str(tempr);               
                schetchik++;
            }
            else if (sign[schetchik].sign > sign[schetchik - 1].sign) {
                stack_operation.push_str(tempr);
                schetchik++;
            }
            else if (sign[schetchik].sign == sign[schetchik - 1].sign && sign[schetchik].znak == "right") {
                stack_operation.push_str(tempr);
                schetchik++;
            }
            else if (sign[schetchik].sign == sign[schetchik - 1].sign && sign[schetchik].znak == "left") {
                reversestack(stack_select);
                if (not stack_R.empty()) reversestack(stack_R);
                if (not stack_bool.empty()) reversestack(stack_bool);

                while (not stack_select.empty()) {
                    if (stack_select.top() == "R") {
                        opz.push_back(stack_R.top());
                        stack_select.pop();
                        stack_R.pop();
                    }
                    else if (stack_select.top() == "B") {
                        opz.push_back(stack_bool.top());
                        stack_select.pop();
                        stack_bool.pop();
                    }
                }
                opz.push_back(stack_operation.top());
                stack_operation.pop();
                sign.pop_back();
                stack_operation.push_str(tempr);
            }
            else if (sign[schetchik].sign < sign[schetchik - 1].sign) {
                schetchik++;
                reversestack(stack_select);
                if (not stack_R.empty()) reversestack(stack_R);
                if (not stack_bool.empty()) reversestack(stack_bool);

                while (not stack_select.empty()) {
                    if (stack_select.top() == "R") {
                        opz.push_back(stack_R.top());
                        stack_select.pop();
                        stack_R.pop();
                    }
                    else if (stack_select.top() == "B") {
                        opz.push_back(stack_bool.top());
                        stack_select.pop();
                        stack_bool.pop();
                    }
                }
                while ((schetchik != 1 && (sign[schetchik - 1].sign < sign[schetchik - 2].sign || sign[schetchik - 1].sign == sign[schetchik - 2].sign && sign[schetchik - 1].znak == "left"))) {
                    if (sign[schetchik - 1].sign < sign[schetchik - 2].sign || sign[schetchik - 1].sign == sign[schetchik - 2].sign && sign[schetchik - 1].znak == "left")
                    {
                        opz.push_back(stack_operation.top());
                        stack_operation.pop();
                        sign.pop_back();
                        sign.pop_back();
                        sign.push_back(signat);
                        schetchik--;
                    }
                }
                stack_operation.push_str(tempr);
            }
        }
    }

    // Переносим оставшиеся числа и булевы значения
    reversestack(stack_select);
    reversestack(stack_R);
    reversestack(stack_bool);

    while (!stack_select.empty()) {
        if (stack_select.top() == "R") {
            opz.push_back(stack_R.top());
            stack_R.pop();
        }
        else if (stack_select.top() == "B") {
            opz.push_back(stack_bool.top());
            stack_bool.pop();
        }
        stack_select.pop();
    }

    // Переносим оставшиеся операции
    while (!stack_operation.empty()) {
        if (stack_operation.top() != "(" && stack_operation.top() != ")") {
            opz.push_back(stack_operation.top());
        }
        stack_operation.pop();
    }

    return opz;
}

void SALU(vector <string> opz) {
    string s_op = " + - * / ^ > < & ! = # m p ~";

    string s_ar = " + - * / ^ > < ";
    string s_log = " & ! ";
    string s_ob = " = # ";
    string s_od_ar = " m p ";
    string s_right = " p m ~";
    string s_left = " * / ^ + - > < = # & !";
    string str_1("true");
    string str_2("false");

    for (int i = 0; i < opz.size(); i++) {
        size_t found_ar = s_ar.find(opz[i]);
        size_t found_log = s_log.find(opz[i]);
        size_t found_ob = s_ob.find(opz[i]);
        size_t found_od_ar = s_od_ar.find(opz[i]);
        size_t found_right = s_right.find(opz[i]);
        size_t found_left = s_left.find(opz[i]);
        size_t found_op = s_op.find(opz[i]);

        if (found_ar != string::npos) {
            if (found_right != string::npos) {
                opz[i] = schet_1(opz[i - 1], opz[i - 2], opz[i],str_1,str_2);
                opz.erase(opz.begin() + i - 2, opz.begin() + i); // Удаляем два элемента
                i -= 2; // Обновляем индекс
            }
            else if (found_left != string::npos) {
                opz[i] = schet_1(opz[i - 2], opz[i - 1], opz[i],str_1,str_2);
                opz.erase(opz.begin() + i - 2, opz.begin() + i); // Удаляем два элемента
                i -= 2; // Обновляем индекс
            }
        }
        else if (found_log != string::npos) {
            if (found_right != string::npos) {
                opz[i] = schet_2(opz[i - 1], opz[i - 2], opz[i]);
                opz.erase(opz.begin() + i - 2, opz.begin() + i); // Удаляем два элемента
                i -= 2; // Обновляем индекс
            }
            else if (found_left != string::npos) {
                opz[i] = schet_2(opz[i - 2], opz[i - 1], opz[i]);
                opz.erase(opz.begin() + i - 2, opz.begin() + i); // Удаляем два элемента
                i -= 2; // Обновляем индекс
            }
        }
        else if (found_od_ar != string::npos) {
            opz[i] = unitar(opz[i - 1], opz[i]);
            opz.erase(opz.begin() + i - 1, opz.begin() + i); // Удаляем элемент
            i -= 1; // Обновляем индекс
        }
        else if (found_ob != string::npos) {
            opz[i] = ob(opz[i - 2],opz[i-1],opz[i],str_1,str_2);
            opz.erase(opz.begin() + i - 2, opz.begin() + i); // Удаляем элемент
            i -= 2; // Обновляем индекс
        }
        else if (opz[i] == "~") {
            opz[i] = otr(opz[i - 1], opz[i],str_1,str_2);
            opz.erase(opz.begin() + i - 1, opz.begin() + i); // Удаляем элемент
            i -= 1; // Обновляем индекс
        }
        
        if (found_op != string::npos) {
            for (int i = 0; i < opz.size(); i++) {
                cout << opz[i] << " ";
            }
            cout << endl;
        }
    }  
}