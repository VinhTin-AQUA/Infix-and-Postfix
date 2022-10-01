#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <iomanip>

using namespace std;

// CHUYEN BIEU THUC CHUNG TO SANG HAU TO
// CONVERT INFIX TO POSTFIX
// ======================================================

class Postfix
{
private:
    string Exp; // chuoi bna dau
    stack<char> Stack;
    string Output, Process; // ket qua
    map<char,int> _operator = { // thiet lap do lon (do uu tien) cua cac toan tu
        {'+',1},
        {'-',1},
        {'*',2},
        {'/',2},
    };

public:
    Postfix()
    {
        Exp = "";
        Output = "";
        Process = "";
    }
    Postfix(string _s)
    {
        Exp = _s;
        Output = "";
        Process = "";
    }
    string GetProcess(){return Process;} // lay tien trinh
    string GetOutput(){return Output;}

    bool Check();
    void Standardize(); // chuan hoa chuoi
    int GetASCII(char i); // lay ma ASCII cua moi ky tu trong Exp
    void Convert(); // chuyen doi

    friend ostream& operator<<(ostream& os, Postfix &_Postfix);
};

bool Postfix::Check()
{
    /*
         A -> Z (65 -> 90)    a -> z (97 -> 122)
    */
    Standardize(); // chuan hoa chuoi truoc khi

    for(unsigned int i = 0; i < Exp.length(); i++)
    {
        int char_temp = GetASCII(Exp[i]);

        if((char_temp >= 97 && char_temp <= 122) || (char_temp >= 65 && char_temp <= 90)) continue;
        else if (Exp[i] == '+' || Exp[i] == '-' || Exp[i] == '*' || Exp[i] == '/' || Exp[i] == ')' || Exp[i] == '(') continue;
        else return false;
    }
    return true;
}

void Postfix::Standardize() // chuan hoa chuoi
{
    string result = "";

    // xoa ky tu trang
    for(unsigned int i = 0; i < Exp.length(); i++)
    {
        if(Exp[i] != ' ') result += Exp[i];

    }
    Exp.swap(result);
}

int Postfix::GetASCII(char i)
{
    return (int)i;
}

void Postfix::Convert()
{
    if(Check() == false)
    {
        Output =  "TOAN TU hoac TOAN HANG sai cu phap\n";
    }
    else
    {
        string tab = "\t\t\t";
        for(unsigned int i = 0; i < Exp.length(); i++)
        {
            string _Process = to_string(i) + '\t' + Exp[i] + '\t';

            int char_int = GetASCII(Exp[i]);
            if((char_int >= 97 && char_int <= 122) || (char_int >= 65 && char_int <= 90))
            {
                Output += Exp[i];
            }
            else if(Exp[i] == '(')
            {
                Stack.push('(');
            }
            else if(Exp[i] == ')')
            {
                char temp = Stack.top();
                while(temp != '(')
                {
                    Output += temp;
                    Stack.pop();
                    temp = Stack.top();
                }
                Stack.pop();
            }
            else if(Exp[i] == '*' || Exp[i] == '/')
            {
                char oprt_Exp = Exp[i];
                char oprt_Stack = (Stack.size() != 0) ? Stack.top() : ' ';

                while (_operator[oprt_Exp] <= _operator[oprt_Stack])
                {
                    Output += oprt_Stack;
                    Stack.pop();
                    oprt_Stack = (Stack.size() != 0) ? Stack.top() : ' ';
                }
                Stack.push(oprt_Exp);
            }
            else if(Exp[i] == '+' || Exp[i] == '-')
            {
                char oprt_Exp = Exp[i];
                char oprt_Stack = (Stack.size() != 0) ? Stack.top() : ' ';

                while (_operator[oprt_Exp] <= _operator[oprt_Stack])
                {
                    Output += oprt_Stack;
                    Stack.pop();
                    oprt_Stack = (Stack.size() != 0) ? Stack.top() : ' ';
                }
                Stack.push(oprt_Exp);
            }

            if(i == 13) tab = "\t\t";
            _Process += Output + tab;
            stack<char> temp = Stack;
            while(temp.size() != 0)
            {
                _Process += temp.top();
                temp.pop();
            }
            Process += _Process + '\n';
        }
        while(Stack.size() != 0)
        {
            Output += Stack.top();
            Stack.pop();
        }
    }
}

ostream& operator<<(ostream& os, Postfix &_Postfix)
{
    _Postfix.Convert();
    os << setw(5) << left << "i";
	os << setw(11) << left << "Exp[i]";
	os << setw(10) << left << "Output";
	os << setw(19) << right << "Stack" << endl;

	os << setfill('-');
	os << setw(50) << "-" << endl;
	os << _Postfix.Process<<endl;
	os <<"RESULT: "<< _Postfix.Output<<endl;
	return os;
}

void Turtorial()
{
    cout<<"TUTORIAL\n";
    cout<<"CHARACTERS THAT CAN BE USED\n\n";
    cout<<"OPERATOR: +, -, *, / \n";
    cout<<"OPERAND: ('A' to 'Z') or ('a' to 'z')\n";
    cout<<endl;
}

int main()
{
    Turtorial();

    string Exp = "";
    cout<<"Enter the string to be converted: ";fflush(stdin);getline(cin,Exp);

    Postfix convert(Exp);
    cout<<convert;

    return 2;
}









