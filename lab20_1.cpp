#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string>&names, vector<int>&score, vector<char>&grade){
// เปิดไฟล์
ifstream file;
file.open(filename);

string textline;
 // อ่านแต่ละบรรทัดจากไฟล์จนกว่าจะถึงสิ้นสุดของไฟล์
while(getline(file,textline)){
    char format[] = "%[^:]: %d %d %d";
    char name[100]; // สมมติว่าชื่อจะไม่เกิน 100 ตัวอักษร
    int a,b,c;
    sscanf(textline.c_str(),format,name,&a,&b,&c);
    // เก็บข้อมูลที่แยกออกมา
    names.push_back(name); // เก็บชื่อ
    score.push_back((a + b + c)); // คำนวณและเก็บคะแนนรวม
    char x = score2grade(a + b + c); // คำนวณและเก็บเกรดตามคะแนนรวมโดยใช้ฟังก์ชัน score2grade
    grade.push_back(x); // เก็บเกรด
}
file.close();
}

void getCommand(string &command, string &key){
cout << "Please input your command: ";
cin >> command;

if(toUpperStr(command)== "GRADE" || toUpperStr(command)== "NAME"){
    cin.ignore();
    getline(cin,key);
}
}

void searchName(vector<string>names, vector<int>scores, vector<char>grades, string key){
int n = 0;
cout << "---------------------------------" << endl;
for(unsigned int i = 0; i<names.size(); i++){
    if(key == toUpperStr(names[i])){
        cout << names[i] << "'s score = "<< scores[i] << endl;
        cout << names[i] << "'s grade = "<< grades[i] << endl;
        n++;
    }else if(i == names.size()-1 && n == 0){
        cout << "Cannot found."<< endl;
    }
}
    cout << "---------------------------------" << endl;
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    int n = 0;
    cout << "---------------------------------" << endl;
    for(unsigned int i=0;i<names.size();i++){
        if(*key.c_str() == grades[i]){
            cout << names[i] << " (" << scores[i] << ")" << endl;
            n++;
        }
    }
    if (n == 0) {
        cout << "Cannot found." << endl;
    }
    cout << "---------------------------------" << endl;
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
