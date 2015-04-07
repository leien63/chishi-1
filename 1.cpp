#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int T_SUM = 128;	//教师容纳量
const int S_SUM = 1024;  //学生容纳量

class Teacher {
public:
	static int inputTeacher();	//从文件读入教师数据到对象数组
	static void outputTeacher();	//从对象数组输出教师数据到文件
	static int teacherSum;	//储存实际教师人数
	void initStudent();	//用于实例化一个学生类并调用学生类的initStudent函数（增加学生信息）
	void delStudent();	//删除学生信息
	void setStudent();	//修改学生信息
	void displayStudent();	//查询学生信息
	void setpassword();	//教师修改自己的密码
protected:
	string tid;			//教师id
	string tname;		//教师姓名
	string tpassword;	//教师登录密码
};

class Student {
public:
	static int inputStudent();	//从文件读入学生数据到对象数组
	static void outputStudent();	//从对象数组输出学生数据到文件
	static int studentSum;	//储存实际学生
	void init(string sid, string sname, string spassword, int midScore , int finalScore);	//初始化(增加)学生信息
	void del();	//删除学生信息
	void find();	//查询某个学生信息
	void sortByASC(); //总成绩按升序排列
	void sortByDESC();	//总成绩按降序排列
	void display();	//显示所有学生信息
	void setSid();	//修改学生id
	void setSname();	//修改学生姓名
	void setSpassword();	//修改学生密码
	void setMidScore();	//修改期中成绩
	void setFinalScore();	//修改期末成绩
protected:
	string sid;	//学生id
	string sname;	//学生姓名
	string spassword;	// 学生登录密码
	int midScore;	//学生期中成绩
	int finalScore;	//学生期末成绩
	int sumScore;	//学生总分
	int aveScore;	//学生平均成绩
};


Teacher teacher[T_SUM];
Student student[S_SUM];

//class of Teacher
int Teacher::inputTeacher(){
	int _count = 0;
	string tid;	
	string tname;		
	string tpassword;	

	ifstream fin;
	fin.open("D:\\teacher.txt");
	if(!fin) return 0;	//没有文件即返回0个教师数
	for(int i = 0; i < T_SUM; i++){
		fin >> tid; 
		fin >> tname;
		fin >> tpassword;

	}
}


//class of Student
