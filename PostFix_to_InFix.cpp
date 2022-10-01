#include <iostream>
#include <stack>

using namespace std;

// POSTFIX TO INFIX
class Infix
{
private:
    string Exp,Output;
    stack<string> Stack;
    string Process;
public:
    Infix(string s = "");

    string GetOutput();
    string GetProcess();

    int GetASCII(char i); // lay ma ASCII cua moi ky tu trong Exp
    string Standardize(); // chuan hoa chuoi
    bool Check(); // kiem tra chuoi hop le

    void Convert();

    friend ostream& operator<<(ostream& os, Infix &_Infix);
};

Infix::Infix(string s)
{
    Exp = s;
    Output = "";
    Process = "";
}

ostream& operator<<(ostream & os, Infix &_Infix)
{
    _Infix.Convert();
    os<<"Process: \n"<<_Infix.GetProcess()<<endl;
    os<<"Result: "<<_Infix.GetOutput()<<endl;
    return os;
}

string Infix::GetOutput()
{
    return Output;
}

string Infix::GetProcess()
{
    return Process;
}

int Infix::GetASCII(char i)
{
    return (int)i;
}

string Infix::Standardize() // chuan hoa chuoi
{
    string result = "";

    // xoa ky tu trang
    for(unsigned int i = 0; i < Exp.length(); i++)
    {
        if(Exp[i] != ' ') result += Exp[i];

    }
    return result;
}
bool Infix::Check()
{
    for(unsigned int i = 0; i < Exp.length(); i++)
    {
        int char_int = GetASCII(Exp[i]);

        // 0 -> 9 (48 -> 57) A -> Z (65 -> 90) a -> z (97 -> 122)

        if((char_int >= 48 && char_int <= 57) || (char_int >= 65 && char_int <= 90) || (char_int >= 97 && char_int <= 122)) continue;
        else if (Exp[i] == '+' || Exp[i] == '-' || Exp[i] == '*' || Exp[i] == '/') continue;
        else
        {
            return false;
        }
    }
    return true;
}

void Infix::Convert()
{
    Exp = Standardize();

    // 0 -> 9 (48 -> 57)
    // A -> Z (65 -> 90)
    // a -> z (97 -> 122)
    if(Check() == false)
    {
        Output =  "TOAN TU hoac TOAN HANG sai cu phap\n";
    }
    else
    {
        for(unsigned int i = 0; i < Exp.length(); i++)
        {

            int char_int = GetASCII(Exp[i]);
            string _process = to_string(i) + "\t|" + Exp[i] + "\t|";

            if((char_int >= 48 && char_int <= 57) || (char_int >= 65 && char_int <= 90) || (char_int >= 97 && char_int <= 122))
            {
                string temp = "";
                temp += Exp[i];
                Stack.push(temp);

                _process += "\t|\t|";
            }
            else if(Exp[i] == '+' || Exp[i] == '-' || Exp[i] == '*' || Exp[i] == '/')
            {
                string a = Stack.top();
                Stack.pop();

                string b = Stack.top();
                Stack.pop();

                string temp = '(' + b + Exp[i] + a + ')';

                Stack.push(temp);

                _process += a + "\t|" + b + "\t|" + temp + "\t|";
            }

            stack<string> _stack = Stack;
            while(_stack.size() != 0)
            {
                _process += _stack.top() + ' ';
                _stack.pop();
            }
            Process += _process + '\n';
        }
        Output = Stack.top();
        Stack.pop();
    }
}

void Tutorial()
{
    cout<<"POSTFIX TO INFIX\n";
    cout<<"Charactors that can be use:\n";
    cout<<"Operand: (a -> z) or (A -> Z) or (0 -> 9)\n";
    cout<<"Operator: +, -, *, /\n";
    cout<<endl;
}

int main()
{
    Tutorial();
    string s = "";
    cout<<"Enter string to convert: ";fflush(stdin);getline(cin,s);

    Infix _Infix(s);

    cout<<_Infix<<endl;


    return 2;
}
