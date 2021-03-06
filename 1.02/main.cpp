#include <iostream>
#include <cstring>
#include <cmath>
#include <windows.h>

using namespace std;

bool symbol_check(char sym){   //�������� �� ���������� ������
    switch(sym)
    {
        case '*': return true;
        case '+': return true;
        case '-': return true;
        case '(': return true;
        case ')': return true;
        case '^': return true;
        case '/': return true;
    }
    return false;
}

int priority(char sym){   //����������� ����������
    switch(sym)
    {
        case '(': return 1;
        case '+': return 2;
        case '-': return 2;
        case '^': return 4;
        case '/': return 3;
        case '%': return 3;
        case '*': return 3;
    }
    return 0;
}

int ultrapain(int first,int second, char operation){   //���������� �������������� �������� ���
    switch(operation)
    {
        case'+': return first+second;
        case'-': return first-second;
        case'*': return first*second;
        case'/': return first/second;
        case'%': return first % second;
        case'^': return pow(first,second);
    }
}

/*void error(char getallerrors, int line){
    int a=0; int b=0;
    for(int i=0;i<line;i++){
        if(getallerrors[i]=='('){
            a++;
           } else if(getallerrors[i]==')'){
                b++
           }
    }
    if(a>b||a<b||a!=b){
        cout<<"Error. Wrong bracket alignment"<<endl;
    }
}*/

int main(){
    char *input = new char[100];
    cin.getline(input, 100);
    char *exit = new char[strlen(input)+10]; int exitid = 0;
    char *operstack = new char[strlen(input)+10]; int ostid = 0;
    int *calculation = new int[10]; int calc = 0;
    bool bin=false;
    char *per = new char[100];
    char *value = new char[100];
    char *quantity = new char[100];
    int percount=0; bool check=false;

    cout<<"How many variables does the expression contain?"<<endl;
    cin>>percount;
    for(int i = 0; i < percount;i++){
        cout<<i+1<<" variable name: ";
        cin>>per[i];
        cout<<i+1<<" variable value: ";
        cin>>value[i];

    }
    for(int j = 0; j < percount; j++){
        for(int i = 0; i < strlen(input);i++){
            if(input[i]==per[j]){
                input[i]=value[j];
                quantity[j]++;
            }
        }
    }
    for(int i = 0; i < strlen(input);i++){
        for(int j = 0; j < percount; j++){
                if(!symbol_check(input[i]) && input[i]>=97 && input[i]<=122 && input[i]==value[j]){
                    check=true;
                }
        }
        if(check==false && !symbol_check(input[i]) && input[i]>=97 && input[i]<=122){
            cout<<"Error. Unknown variable "<< input[i]<<endl;
        }
    }

    for(int i = 0; i < strlen(input);){                  //�������� � ��������� ���� ��������-������
            if(!symbol_check(input[i])&&exit[i]!=')'){
                    exit[exitid] = input[i];
                    i++; exitid++;
            } else if(symbol_check(input[i])){
                    if(ostid > 0){
                            if(priority(input[i]) <= priority(operstack[ostid-1]) && input[i]!=')' && input[i]!='('){
                                exit[exitid] = operstack[ostid-1];
                                operstack[ostid-1] = input[i];
                                exitid++;
                                cout<< "first"<<input[i]<<endl;
                            }else if(priority(input[i]) > priority(operstack[ostid-1]) && input[i]!=')' && input[i]!='('){
                                operstack[ostid] = input[i];
                                ostid++;
                                cout<<"second"<<input[i]<<endl;
                            }else if(input[i]=='('&& input[i]!=')'){
                                operstack[ostid] = input[i];
                                ostid++;
                            }else if(input[i]==')'){
                                ostid--;
                                while(operstack[ostid]!='('){
                                    exit[exitid]=operstack[ostid];
                                    ostid--;exitid++;
                                }
                                cout<<"wtf"<<endl;
                            }
                    }else if(ostid == 0){
                            operstack[ostid] = input[i];
                            ostid++;
                            cout<<"third"<< input[i]<<endl;
                    }
             i++;
            }
    }
    ostid--;
    int m = exitid+ostid;                       //��������� ���� �������-������
    while(exitid<m || ostid >= 0){             //� �� ��� ��� ��������, �� ��� ��������, ������ ���������!!!!
        exit[exitid] = operstack[ostid];
        exitid++; ostid--;
    }
    cout<<endl;
    for(int i = 0; i <= m; i++){                     //������ �����!
        if(!symbol_check(exit[i])){
            calculation[calc] = (int)exit[i]-48;
            calc++;
        }else if(symbol_check(exit[i])){
            calculation[calc-2] = ultrapain(calculation[calc-2], calculation[calc-1], exit[i]);
            calc--;
        }
    }

    cout<<exit/*<<" "<<exitid<<" | " << operstack<<" "<<ostid<<" "<<operstack[ostid] */ <<endl;
    cout<<"Answer - "<<calculation[0]<<endl;

    delete[] operstack;
    delete[] exit;
    delete[] input;
    delete[] calculation;
    delete[] per;
    delete[] value;
    delete[] quantity;

    cout<<"Exit y/n"<<endl;
    char symbo; cin>>symbo;
    switch(symbo){
        case 'n':
            cout<<"Your program!";
                main();
        case 'y':
            cout<<"End program!";
                break;
    }

    return 0;
}
//Somebody once told me the world is gonna roll me
//I ain't the sharpest tool in the shed
//She was looking kind of dumb with her finger and her thumb
//In the shape of an "L" on her forehead
