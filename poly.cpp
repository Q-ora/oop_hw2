#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

/*****************************************
1. 零多項式 以及 常數多項式微分後項數不變
2. 非數字的輸入
3. 輸出精度
4. 輸入的最高次方數不能大於5
*****************************************/

const int MAX_POW = 5;  //x最高5次方
const int DEBUG = 0;

int highestPower(float coff[]);
void display(int highestPow, float coff[]);
void derivative(int highestPow, float coff[], float dev_coff[]);
float compute(int highestPow, float coff[], float x);

int main(int argc, char **argv)
{
    int n = 0;
    float coff[MAX_POW+1] = {0.0};
    float dev_coff[MAX_POW+1] = {0.0};
    float x = 0.0;

    if(DEBUG)   //從鍵盤讀入
    {
        while( (cout << "Please enter n: ") && (cin >> n) ){
            //陣列歸零
            for(int i=0;i<=MAX_POW;i++){
                coff[i] = 0.0;
                dev_coff[i] = 0.0;
            }

            //當輸入n為-1時則停止
            if(n==-1){
                break;
            }else if(n>5){      //***錯誤處理***
                cout << "invalid input: The highest power cannot be over 5" << endl << endl;
                cin.ignore(10000, '\n');    //跳過這行
                continue;
            }else if(cin.fail()){
                cout << "invalid input: n is an integer" << endl << endl;
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }

            cout << "Please enter coff[]: ";
            for(int i=0;i<=n;i++)   
                cin >> coff[i];
            //***錯誤處理***
            if(cin.fail()){
                cout << "invalid input in coff" << endl << endl;
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }

            int highestPow_coff = highestPower(coff);
            derivative(highestPow_coff, coff, dev_coff);    //計算導函數
            int highestPow_dev_coff = highestPower(dev_coff);
            
            /*****************輸出******************/
            cout << "Please enter the value of x: ";
            cin >> x;
            while(cin.fail()){  //***錯誤處理***
                cout << "The input is not a number. Please enter again: ";
                cin.clear();
                cin.ignore(10000, '\n');
                cin >> x;
            }

            cout << "f(x) = ";
            display(highestPow_coff, coff);

            cout << "f'(x) = ";
            display(highestPow_dev_coff, dev_coff);

            cout << "f(" << x << ") = " << compute(highestPow_coff, coff, x) << endl;

            cout << "f'(" << x << ") = " << compute(highestPow_dev_coff, dev_coff, x) << endl;
            
            cout << endl;   //與下個測資的答案間隔一行
        }
    }
    else    //從file讀入
    {
        //開啟polydata.txt
        ifstream fin("polydata.txt", ios::in);

        while(!fin.eof()){
            //陣列歸零
            for(int i=0;i<=MAX_POW;i++){
                coff[i] = 0.0;
                dev_coff[i] = 0.0;
            }

            fin >> n;
            //***錯誤處理***
            if(n>5){
                cout << "invalid input: The highest power cannot be over 5" << endl << endl;
                fin.ignore(10000, '\n');    //跳過這行
                continue;
            }else if(fin.fail()){
                cout << "invalid input: n is an integer" << endl << endl;
                fin.clear();
                fin.ignore(10000, '\n');
                continue;
            }

            for(int i=0;i<=n;i++)   
                fin >> coff[i];
            //***錯誤處理***
            if(fin.fail()){
                cout << "invalid input in coff" << endl << endl;
                fin.clear();
                fin.ignore(10000, '\n');
                continue;
            }

            int highestPow_coff = highestPower(coff);
            derivative(highestPow_coff, coff, dev_coff);    //計算導函數
            int highestPow_dev_coff = highestPower(dev_coff);
            
            /*****************輸出******************/
            cout << "Please enter the value of x: ";
            cin >> x;
            while(cin.fail()){  //***錯誤處理***
                cout << "The input is not a number. Please enter again: ";
                cin.clear();
                cin.ignore(10000, '\n');
                cin >> x;
            }

            cout << "f(x) = ";
            display(highestPow_coff, coff);

            cout << "f'(x) = ";
            display(highestPow_dev_coff, dev_coff);

            cout << "f(" << x << ") = " << compute(highestPow_coff, coff, x) << endl;

            cout << "f'(" << x << ") = " << compute(highestPow_dev_coff, dev_coff, x) << endl;
            
            cout << endl;   //與下個測資的答案間隔一行
        }
        fin.close();
    }

    return 0;
}

int highestPower(float coff[])
{
    for(int i=MAX_POW;i>=0;i--){
        if(coff[i])
            return i;
    }

    return 0;
}

void display(int highestPow, float coff[])
{
    bool isfirst = true, allzero = true;
    for(int i=0;i<=highestPow;i++){
        if(coff[i]){
            if(isfirst){
                cout << coff[i];
                for(int j=0;j<i;j++)
                    cout << "*x";
                isfirst = false;
                allzero = false;
            }else{
                if(coff[i] > 0){    //正負判斷
                    cout << " + " << coff[i];
                }else{
                    cout << " - " << (-1)*coff[i];
                }
                for(int j=0;j<i;j++)
                    cout << "*x";
            }
        }
    }

    if(allzero)  //只有0
        cout << "0";

    cout << endl;
}

void derivative(int highestPow, float coff[], float dev_coff[])
{
    dev_coff[0] = 0.0;  //常數函數微分
    for(int i=0;i<highestPow;i++){
        dev_coff[i] = (i+1) * coff[i+1];
    }
}

float compute(int highestPow, float coff[], float x)
{
    float ret = 0.0;
    for(int i=0;i<=highestPow;i++){
        ret += coff[i] * powf(x, (float)i);
    }

    return ret;
}