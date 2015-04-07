
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int T_SUM = 128;	//教师容纳量
const int S_SUM = 1024;  //学生容纳量
const int C_SUM = 128;	//课程容纳量

class Teacher {
public:
	static int inputTeacher();	//从文件读入教师数据到对象数组
	static void outputTeacher();	//从对象数组输出教师数据到文件
	static void printHead();	//输出字段名
	static int teacherSum;	//储存实际教师人数
	void init(string tid, string tname, string tpassword);	//初始化教师信息
	bool login();	//登录功能
	void find();	//查询某个老师信息
	void addStudent();	//用于实例化一个学生类并调用学生类的init函数（增加学生信息）
	void delStudent();	//删除学生信息
	void setStudent();	//修改学生信息
	int findStudent();	//查询学生信息
	void setpassword();	//教师修改自己的密码
	void showMyInfo();	//供登录教师查看自己的信息
	void addCourse();	//增加课程信息
	void delCourse();	//删除课程信息
	void setCourse();	//修改课程信息
protected:
	string tid;			//教师id
	string tname;		//教师姓名
	string tpassword;	//教师登录密码
};

class Student {
public:
	friend class Teacher;	//友元类，使得学生类的保护成员能被教师类访问
	static int inputStudent();	//从文件读入学生数据到对象数组
	static void outputStudent();	//从对象数组输出学生数据到文件
	static void sortByASC(); //总成绩按升序排列
	static void sortByDESC();	//总成绩按降序排列
	static void sortBySid();	//总成绩按学号排列
	static void printHead();	//输出字段名
	static void display();	//显示所有学生信息
	static void selectFail();	//显示不及格的学生
	static int studentSum;	//储存实际学生
	void init(string sid, string sname, string spassword, double midScore , double finalScore);	//初始化(增加)学生信息
	bool login();	//登录功能
	void add();	//增加学生信息
	void del();	//删除学生信息
	void find();	//查询某个学生信息
	void setSid();	//修改学生id
	void setSname();	//修改学生姓名
	void setSpassword();	//修改学生密码
	void setMidScore();	//修改期中成绩
	void setFinalScore();	//修改期末成绩
	void showMyInfo();	//供登录学生查看自己的信息
	void chooseCourse();	//选修课程
protected:
	string sid;	//学生id
	string sname;	//学生姓名
	string spassword;	// 学生登录密码
	double midScore;	//学生期中成绩
	double finalScore;	//学生期末成绩
	double sumScore;	//学生总分
	double aveScore;	//学生平均成绩
	string _course;	//选修课程名
};

class Course {
public:
	friend class Teacher;	//友元类，使得课程类的保护成员能被教师类访问
	friend class Student;	//友元类，使得课程类的保护成员能被学生类访问
	static int inputCourse();	//从文件读入课程数据到对象数组
	static void outputCourse();	//从对象数组输出课程数据到文件
	static void display();	//显示所有课程
	static void printHead();	//输出字段名
	static int courseSum;	//储存实际课程
	void init(string cid, string cname, int csum);	//初始化课程信息
	void add();	//添加课程
	void del();	//删除课程
	void setCid();	//修改课程号
	void setCname();	//修改课程名
	void setCsum();	//修改课程数
	void find();	//查询课程信息
protected:
	string cid;		//课程编号
	string cname;	//课程名
	int csum;	//课程剩余数
};


Teacher teacher[T_SUM];
int Teacher::teacherSum = inputTeacher();

Student student[S_SUM];
int Student::studentSum = inputStudent();

Course course[C_SUM];
int Course::courseSum = inputCourse();

//class of Teacher
int Teacher::inputTeacher() {
	int count = 0;
	string tid;	
	string tname;
	string tpassword;	

	ifstream fin;
	fin.open("D:\\teacher.txt");

	//没有文件就创建文件
	if(!fin) {
		outputTeacher();
		return 0;	//返回0个教师数
	}

	//过滤字段名
	string temp;
	fin >> temp;
	fin >> temp;
	fin >> temp;

	for(int i = 0; i < T_SUM; i++){
		fin >> tid; 
		fin >> tname;
		fin >> tpassword;
		if (fin.get() == EOF)
			break;
		teacher[i].init(tid, tname, tpassword);
		count++;
	}
	return count;
}

void Teacher::outputTeacher() {
	ofstream fout;
	fout.open("D:\\teacher.txt", ios::trunc|ios::in);
	if(!fout) {cout<<"写入数据失败！";return;}

	fout << "教师id" << "\t"
		<<	"姓名"	<< "\t"
		<<	"密码"	<< "\t";
	fout << endl; 

	for(int i = 0; i < teacherSum; i++){
		fout << teacher[i].tid << "\t"
			<< teacher[i].tname << "\t"
			<< teacher[i].tpassword << endl;
	}
	fout.close();
}

void Teacher::printHead() {
	cout << endl;
	cout << "教师id" << "\t"
		<<	"姓名"	<< "\t"
		<<	"密码"	<< "\t";
	cout << endl;
}

bool Teacher::login() {
	cout << endl;

	string tid;
	string tpassword;
	cout << "---登录界面---" << endl;
	cout << "请输入教师id：" ;
	cin >> tid;
	cout << "请输入密码: " ;
	cin >> tpassword;

	Teacher temp;
	for(int i = 0; i < teacherSum; i++) {
		temp = teacher[i];
		if(tid == temp.tid) {
			if(tpassword == temp.tpassword) {
				cout << endl;
				cout << "---登录成功：欢迎你" << temp.tname << "!---" <<endl;

				//登录成功后要用对象数组中存放的信息初始化当前对象
				init(teacher[i].tid, teacher[i].tname, teacher[i].tpassword);

				return true;
			} else {
				cout << endl;
				cout << "---登录失败：密码不正确！---" ;
				cout << endl;
				return false;
			}
		}
	}

	cout << endl;
	cout << "---登录失败：找不到该教师id！---" ;
	cout << endl;
	return false;
}

void Teacher::init(string tid, string tname, string tpassword) {
	this -> tid = tid;
	this -> tname = tname;
	this -> tpassword = tpassword;
}

void Teacher::addStudent() {
	Student temp;

	string sid;	
	string sname;
	string spassword = "123456";	//默认密码
	double midScore;	
	double finalScore;	

	cout << endl;

back:
	cout << "请输入学生学号：";
	cin >> sid;

	//学号不能重复的输入合法性检查
	for(int i = 0; i < Student::studentSum; i++) {
		if(sid == student[i].sid ) {
			cout<<endl
				<<"学号不能重复，请重新输入。"
				<<endl;
			goto back;
		}
	}

	cout << "请输入学生姓名：";
	cin >> sname;
	cout << "请输入学生期中成绩：";
	cin >> midScore;
	cout << "请输入学生期末成绩：";
	cin >> finalScore;

	temp.init(sid, sname, spassword, midScore, finalScore);
	temp.add();

	cout << endl;
	cout << "---添加学生信息成功！---";
	cout << endl;
}

int Teacher::findStudent() {
	Student temp;

	string sid;
	cout << endl;
	cout << "请输入要查找学生的学号：";
	cin >> sid;

	int i;
	for(i = 0; i < Student::studentSum; i++) {
		if(sid == student[i].sid) {
			temp.init(student[i].sid, student[i].sname, student[i].spassword, student[i].midScore, student[i].finalScore);
			cout << "---找到如下学生信息---";
			Student::printHead();
			temp.find();

			//返回找到的学生在对象数组中的位置
			return i;
		}
	}

	cout << endl;
	cout << "---找不到该学生！---";
	cout << endl;
	return -1;

}

void Teacher::delStudent() {
	Student temp;

	cout<<endl;
	cout<< "---请先查找要被删除的学生---";
	cout<<endl;

	string sid;
	cout << endl;
	cout << "请输入要查找学生的学号：";
	cin >> sid;

	for(int i = 0; i < Student::studentSum; i++) {
		if(sid == student[i].sid) {
			temp.init(student[i].sid, student[i].sname, student[i].spassword, student[i].midScore, student[i].finalScore);
			temp.del();
			return;
		}
	}

	cout << endl;
	cout << "---找不到该学生！---";
	cout << endl;
}

void Teacher::setStudent() {
	Student temp;

	int point = findStudent();
	cout << endl;

	temp = student[point];

	int flg;
	cout<<"┌───────────┐"<<endl
		<<"│   学生成绩管理系统   │"<<endl
		<<"│   修改学生信息菜单   │"<<endl
		<<"├───────────┤"<<endl
		<<"│   1.修改学生学号     │"<<endl
		<<"│   2.修改学生姓名     │"<<endl
		<<"│   3.修改学生密码     │"<<endl
		<<"│   4.修改期中成绩     │"<<endl
		<<"│   5.修改期末成绩     │"<<endl
		<<"│   6.返回上级菜单     │"<<endl
		<<"└───────────┘"<<endl;
	cout<<"请输入操作编号：";
	cin>>flg;
	switch (flg)
	{
		case(1):
			temp.setSid();break;
		case(2):
			temp.setSname();break;
		case(3):
			temp.setSpassword();break;
		case(4):
			temp.setMidScore();break;
		case(5):
			temp.setFinalScore();break;
		case(6):
			return;
		default:
			cout<<endl<<"───输入有误！───"<<endl<<endl;
			break;
	}
}

void Teacher::setpassword() {
	string tpassword;
	cout << endl;
	cout << "请输入新密码：";

	cin >> tpassword;
	this -> tpassword = tpassword;

	for(int i = 0; i < teacherSum; i++) {
		if(this -> tid == teacher[i].tid) {


			teacher[i].tpassword = tpassword;
			break;

		}
	}

	outputTeacher();
	inputTeacher();

	cout << "---密码修改成功！---" <<endl;
}

void Teacher::showMyInfo() {
	printHead();
	find();
}

void Teacher::find() {
	cout << tid << "\t"
		<< tname << "\t"
		<< tpassword << "\t";
	cout << endl;
}

void Teacher::addCourse() {
	Course temp;

	string cid;
	string cname;
	int csum;

	cout << endl;

back9:
	cout << "请输入课程号：";
	cin >> cid;

	//学号不能重复的输入合法性检查
	for(int i = 0; i < Course::courseSum; i++) {
		if(cid == course[i].cid ) {
			cout<< endl
				<< "---课程号不能重复，请重新输入！---"
				<< endl;
			goto back9;
		}
	}

	cout << "请输入课程名称：";
	cin >> cname;
	cout << "请输入课程数目：";
	cin >> csum; 

	temp.init(cid, cname, csum);
	temp.add();

	cout << endl;
	cout << "---添加课程信息成功！---";
	cout << endl;
}

void Teacher::delCourse() {
	Course temp;

	cout<<endl;
	cout<< "---请先查找要被删除的课程---";
	cout<<endl;

	string cid;
	cout << endl;
	cout << "请输入要查找的课程号：";
	cin >> cid;

	for(int i = 0; i < Course::courseSum; i++) {
		if(cid == course[i].cid) {
			temp.init(course[i].cid, course[i].cname, course[i].csum);
			temp.del();
			return;
		}
	}

	cout << endl;
	cout << "---找不到该课程！---";
	cout << endl;
}

void Teacher::setCourse() {
	Course temp;

	cout<<endl;
	cout<< "---请先查找要被修改的课程---";
	cout<<endl;

	string cid;
	cout << endl;
	cout << "请输入要查找的课程号：";
	cin >> cid;

	int point = -1;
	for(int i = 0; i < Course::courseSum; i++) {
		if(cid == course[i].cid) {
			temp = course[i];
			point = i;
		}
	}

	cout << "---找到以下课程---" << endl;
	temp.find();

	if(point == -1) {
		cout << endl;
		cout << "---找不到该课程！---";
		cout << endl;
		return;
	}

	int flg;
	cout<<"┌───────────┐"<<endl
		<<"│   学生成绩管理系统   │"<<endl
		<<"│     课程管理菜单     │"<<endl
		<<"├───────────┤"<<endl
		<<"│     1.修改课程号     │"<<endl
		<<"│     2.修改课程名     │"<<endl
		<<"│     3.修改课程数     │"<<endl
		<<"├───────────┤"<<endl
		<<"│    4.返回上级菜单    │"<<endl
		<<"└───────────┘"<<endl;
	cout<<"请输入操作编号：";
	cin>>flg;
	switch (flg)
	{
		case(1):
			temp.setCid();
			break;
		case(2):
			temp.setCname();
			break;
		case(3):
			temp.setCsum();
			break;
		case(4):
			return;
		default:
			cout<<endl<<"───输入有误！───"<<endl<<endl;
			break;
	}
}

//class of Student
int Student::inputStudent() {
	int count = 0;
	string sid;	
	string sname;	
	string spassword;	
	double midScore;	
	double finalScore;
	string _course;

	ifstream fin;
	fin.open("D:\\student.txt");

	//没有文件就创建文件
	if(!fin) {
		outputStudent();
		return 0;	//返回0个学生数
	}

	//过滤字段名
	string temp;
	fin >> temp; 
	fin >> temp;
	fin >> temp;
	fin >> temp;
	fin >> temp;
	fin >> temp;	
	fin >> temp;
	fin >> temp;

	for(int i = 0; i < S_SUM; i++){
		fin >> sid; 
		fin >> sname;
		fin >> spassword;
		fin >> midScore;
		fin >> finalScore;
		fin >> temp;	//总分和平均成绩让init函数去计算，这里读入temp为过滤掉
		fin >> temp;
		fin >> _course;
		if (fin.get() == EOF)
			break;
		student[i].init(sid, sname, spassword, midScore, finalScore);
		student[i]._course = _course;
		count++;
	}
	return count;
}

void Student::outputStudent() {
	ofstream fout;
	fout.open("D:\\student.txt", ios::trunc|ios::in);
	if(!fout) {cout<<"写入数据失败！";return;}

	fout << "学号" << "\t"
		<<	"姓名"	<< "\t"
		<<	"密码"	<< "\t"
		<<	"期中"	<< "\t"
		<<	"期末"	<< "\t"
		<<	"总分"	<< "\t"
		<<	"平均分"	<< "\t"
		<<	"选修课"	<< "\t";
	fout << endl;

	for(int i = 0; i < studentSum; i++){

		//只将未被标记删除的学生导入文件
		if( student[i].sid != "deleted") {
			fout << student[i].sid<< "\t\t"
				<< student[i].sname << "\t"
				<< student[i].spassword << "\t\t"
				<< student[i].midScore << "\t\t"
				<< student[i].finalScore << "\t\t"
				<< student[i].sumScore << "\t\t"
				<< student[i].aveScore << "\t\t"
				<< student[i]._course << endl;
		}
	}
	fout.close();
}

void Student::printHead() {
	cout << endl;
	cout << "学号" << "\t"
		<<	"姓名"	<< "\t"
		<<	"密码"	<< "\t"
		<<	"期中"	<< "\t"
		<<	"期末"	<< "\t"
		<<	"总分"	<< "\t"
		<<	"平均分"	<< "\t"
		<<	"选修课"	<< "\t";
	cout << endl;
}

void Student::init(string sid, string sname, string spassword, double midScore , double finalScore) {
	this -> sid = sid;
	this -> sname = sname;
	this -> spassword = spassword;
	this -> midScore = midScore;
	this -> finalScore = finalScore;

	this -> _course = "无";

	//计算总分和平均分
	this -> sumScore = midScore + finalScore;
	this -> aveScore = sumScore / 2;
}

void Student::add() {
	student[studentSum].sid = sid;
	student[studentSum].sname = sname;
	student[studentSum].spassword = spassword;
	student[studentSum].midScore = midScore;
	student[studentSum].finalScore = finalScore;
	student[studentSum].sumScore = sumScore;
	student[studentSum].aveScore = aveScore;
	student[studentSum]._course = _course;

	Student::studentSum++;
	outputStudent();
}

void Student::del() {
	bool flg = false;
	string flg0;

	//先找到要被删除的学生在对象数组中的位置
	for(int i = 0; i < studentSum; i++) {
		if(sid == student[i].sid ) {
			//二次确认
			cout << endl;
			cout << "---你确定要删除学生：" << sid << "，" << student[i].sname << "。---";
			cout << endl;
			cout << "---输入Y确定---";
			cout << endl;
			cin >> flg0;

			if(flg0 == "Y" || flg0 == "y") {

				//将被删除学生的sid标记为deleted
				student[i].sid = "deleted";

				//学生总数-1
				Student::studentSum--;	

				//使删除后的学生覆盖到对象数组中
				outputStudent();
				inputStudent();	
				flg = true;

				cout << endl;
				cout << "---删除学生信息成功！---";
				cout << endl;

				break;
			} else {
				break;
			}
		}
	}

	if(flg == false) {
		cout << endl;
		cout << "---删除学生信息失败！---";
		cout << endl;
	}

}

void Student::find() {
	cout << sid << "\t"
		<< sname << "\t"
		<< spassword << "\t"
		<< midScore << "\t"
		<< finalScore << "\t"
		<< sumScore << "\t"
		<< aveScore << "\t"
		<< _course;
	cout << endl;
}

void Student::sortByASC() {
	Student temp;

	//将对象数组student中的数据按总分升序排序
	for(int i = 0; i < studentSum - 1; i++){
		for(int j = i + 1; j < studentSum; j++){
			if( student[i].sumScore > student[j].sumScore){
				temp = student[i]; 
				student[i] = student[j]; 
				student[j] = temp;
			}
		}
	}

	//输出到文件保存
	outputStudent();
}

void Student::sortByDESC() {
	Student temp;

	//将对象数组student中的数据按总分降序排序
	for(int i = 0; i < studentSum - 1; i++){
		for(int j = i + 1; j < studentSum; j++){
			if( student[i].sumScore < student[j].sumScore){
				temp = student[i]; 
				student[i] = student[j]; 
				student[j] = temp;
			}
		}
	}

	//输出到文件保存
	outputStudent();
}

void Student::sortBySid() {
	Student temp;

	//将对象数组student中的数据按总分降序排序
	for(int i = 0; i < studentSum - 1; i++){
		for(int j = i + 1; j < studentSum; j++){
			if( student[i].sid > student[j].sid){
				temp = student[i]; 
				student[i] = student[j]; 
				student[j] = temp;
			}
		}
	}

	//输出到文件保存
	outputStudent();
}

void Student::display() {
	printHead();

	//遍历数组，赋值给temp，调用temp对象find()函数进行输出
	Student temp;
	for(int i = 0; i < studentSum; i++){
		temp = student[i];
		temp.find();
	}
}

void Student::selectFail() {
	printHead();

	//遍历数组，赋值给temp，调用temp对象find()函数进行输出
	Student temp;
	for(int i = 0; i < studentSum; i++){

		//期中，期末有一科不及格就筛选出来并输出
		if(student[i].midScore < 60 || student[i].finalScore < 60) {
			temp = student[i];
			temp.find();
		}
	}
}

void Student::setSid() {
	cout << endl;

	string sid;
	for(int i = 0; i < Student::studentSum; i++) {

		//注意this
		if(this -> sid == student[i].sid ) {
back0:
			cout << "请输入新的学号：";
			cin >> sid;

			//学号不能重复的输入合法性检查
			for(int i = 0; i < Student::studentSum; i++) {
				if(sid == student[i].sid ) {
					cout<< endl
						<< "---学号不能重复，请重新输入！---"
						<< endl;
					goto back0;
				}
			}

			student[i].sid = sid;
			break;
		}
	}

	outputStudent();
	inputStudent();

	cout << "---学号修改成功！---" <<endl;
}

void Student::setSname() {
	cout << endl;

	string sname;
	for(int i = 0; i < Student::studentSum; i++) {
		if(this -> sid == student[i].sid) {
			cout << "请输入新的姓名：";
			cin >> sname;

			student[i].sname = sname;
			break;
		}

	}

	outputStudent();
	inputStudent();

	cout << "---姓名修改成功！---" <<endl;
}

void Student::setSpassword() {
	cout << endl;

	string spassword;
	for(int i = 0; i < Student::studentSum; i++) {
		if(this -> sid == student[i].sid) {
back1:
			cout << "请输入新的密码：";
			cin >> spassword;

			//新密码不能为初始密码123456 且不能少于6位
			if(spassword == "123456" && spassword.length() < 6) {
				cout<<endl
					<<"密码过于简单，请重新输入！"
					<<endl
					<<endl;
				goto back1;

				//学生有权限更改自己的密码，要将当前对象的spassword也更改了
				this -> spassword = spassword;

				student[i].spassword = spassword;
				break;
			}
		}
	}

	outputStudent();
	inputStudent();

	cout << "---密码修改成功！---" <<endl;
}

void Student::setMidScore() {
	cout << endl;

	double midScore;
	for(int i = 0; i < Student::studentSum; i++) {
		if(this -> sid == student[i].sid) {

			cout << "请输入新的期中成绩：";
			cin >> midScore;

			student[i].midScore = midScore;
			break;

		}
	}

	outputStudent();
	inputStudent();

	cout << "---期中成绩修改成功！---" <<endl;
}

void Student::setFinalScore() {
	cout << endl;

	double finalScore;
	for(int i = 0; i < Student::studentSum; i++) {
		if(this -> sid == student[i].sid) {

			cout << "请输入新的期末成绩：";
			cin >> finalScore;

			student[i].finalScore = finalScore;
			break;

		}
	}

	outputStudent();
	inputStudent();

	cout << "---期末成绩修改成功！---" <<endl;
}

bool Student::login() {
	cout << endl;

	string sid;
	string spassword;
	cout << "---登录界面---" << endl;
	cout << "请输入学号：" ;
	cin >> sid;
	cout << "请输入密码（初始密码123456）: " ;
	cin >> spassword;

	Student temp;
	for(int i = 0; i < studentSum; i++) {
		temp = student[i];
		if(sid == temp.sid) {
			if(spassword == temp.spassword) {
				
				//判断是否第一次登录，第一次登录需要改密码
				if(temp.spassword != "123456") {
					cout << endl;
					cout << "---登录成功：欢迎你" << temp.sname << "!---" <<endl;

					//登录成功后要用对象数组中存放的信息初始化当前对象
					init(student[i].sid, student[i].sname, student[i].spassword, student[i].midScore , student[i].finalScore);

					return true;
				} else {
					cout << endl;
					cout << "---登录成功：你是第一次登录，需要修改密码！ ---" << endl;

					//登录成功后要用对象数组中存放的信息初始化当前对象
					init(student[i].sid, student[i].sname, student[i].spassword, student[i].midScore , student[i].finalScore);

					student[i].setSpassword();

					return true;
				}
			} else {
				cout << endl;
				cout << "---登录失败：密码不正确！---" ;
				return false;
			}
		}
	}

	cout << endl;
	cout << "---登录失败：找不到该学号，请联系管理员！---" ;
	cout << endl;
	return false;
}

void Student::showMyInfo() {
	printHead();
	find();
}

void Student::chooseCourse() {
	cout << endl;
	Course::display();
	cout << endl;

	Course temp;
	string cid;
	cout << "请选择要选修的课程号（请谨慎选择：选修后不能退选）：" << endl;
	cin >> cid;

	for(int i = 0; i < Course::courseSum; i++) {
		if(cid == course[i].cid) {
			if(course[i].csum > 0) {
				_course = course[i].cname;
				course[i].csum--;	//选修后，课程剩余量-1

				//保存数据
				for(int j = 0; j < Student::studentSum; j++)  {
					if(this -> sid == student[j].sid) {
						student[j]._course = course[i].cname;
						outputStudent();

						//记得保存course对象数组中的数据到文件！！
						Course::outputCourse();	
						break;
					}
				}

				cout << "---选修"<< course[i].cname << "成功！---";
				cout << endl;
				return;

			} else {
				cout << "---该课程已满！---";
				cout << endl;
			}
		}
	}

	cout << "---找不到该课程！---";
	cout << endl;
}

//class of Course
int Course::inputCourse() {
	int count = 0;
	string cid;	
	string cname;
	int csum;

	ifstream fin;
	fin.open("D:\\course.txt");

	//没有文件就创建文件
	if(!fin) {
		outputCourse();
		return 0;	//返回0个课程数
	}

	//过滤字段名
	string temp;
	fin >> temp;
	fin >> temp;
	fin >> temp;

	for(int i = 0; i < C_SUM; i++){
		fin >> cid; 
		fin >> cname;
		fin >> csum;
		if (fin.get() == EOF)
			break;
		course[i].init(cid, cname, csum);
		count++;
	}

	return count;
}

void Course::outputCourse() {
	ofstream fout;

	fout.open("D:\\course.txt", ios::trunc|ios::in);
	if(!fout) {cout<<"写入数据失败！";return;}

	fout << "课程id" << "\t"
		<<	"课程名"	<< "\t"
		<<	"剩余数"	<< "\t";
	fout << endl; 

	for(int i = 0; i < courseSum; i++){

		//只将未被标记删除的课程导入文件
		if( course[i].cid != "deleted") {
			fout << course[i].cid << "\t"
				<< course[i].cname << "\t"
				<< course[i].csum << endl;
		}

	}
	fout.close();
}

void Course::init(string cid, string cname, int csum) {
	this -> cid = cid;
	this -> cname = cname;
	this -> csum = csum;
}

void Course::printHead() {
	cout << endl;
	cout << "课程id" << "\t"
		<<	"课程名"	<< "\t"
		<<	"剩余数"	<< "\t";
	cout << endl;
}

void Course::add() {
	course[courseSum].cid = cid;
	course[courseSum].cname = cname;
	course[courseSum].csum = csum;

	Course::courseSum++;
	outputCourse();
}

void Course::del() {
	bool flg = false;
	string flg0;

	//先找到要被删除的课程在对象数组中的位置
	for(int i = 0; i < courseSum; i++) {
		if(cid == course[i].cid ) {
			//二次确认
			cout << endl;
			cout << "---你确定要删除课程：" << cid << "，" << course[i].cid << "。---";
			cout << endl;
			cout << "---输入Y确定---";
			cout << endl;
			cin >> flg0;

			if(flg0 == "Y" || flg0 == "y") {

				//将被删除课程的cid标记为deleted
				course[i].cid = "deleted";

				//课程总数-1
				Course::courseSum--;	

				//使删除后的课程覆盖到对象数组中
				outputCourse();
				inputCourse();	
				flg = true;

				cout << endl;
				cout << "---删除课程信息成功！---";
				cout << endl;

				break;
			} else {
				break;
			}
		}
	}

	if(flg == false) {
		cout << endl;
		cout << "---删除课程信息失败！---";
		cout << endl;
	}
}

void Course::find() {
	cout << cid << "\t"
		<< cname << "\t"
		<< csum << "\t";
	cout << endl;
}

void Course::setCid() {
	cout << endl;

	string cid;
	for(int i = 0; i < courseSum; i++) {

		//注意this
		if(this -> cid == course[i].cid) {
back1:
			cout << "请输入新的课程号：";
			cin >> cid;

			//学号不能重复的输入合法性检查
			for(int i = 0; i < Course::courseSum; i++) {
				if(cid == course[i].cid ) {
					cout<< endl
						<< "---课程号不能重复，请重新输入！---"
						<< endl;
					goto back1;
				}
			}

			course[i].cid = cid;
			break;
		}
	}

	outputCourse();
	inputCourse();

	cout << "---课程号修改成功！---" <<endl;

}

void Course::setCname() {
	cout << endl;

	string cname;
	for(int i = 0; i < courseSum; i++) {
		if(this -> cname == course[i].cname) {
			cout << "请输入新的课程号：";
			cin >> cname;

			course[i].cname = cname;
			break;
		}
	}

	outputCourse();
	inputCourse();

	cout << "---课程名修改成功！---" <<endl;
}

void Course::setCsum() {
	cout << endl;

	int csum;
	for(int i = 0; i < courseSum; i++) {
		if(this -> csum == course[i].csum) {
			cout << "请输入新的课程数：";
			cin >> csum;

			course[i].csum = csum;
			break;
		}
	}

	outputCourse();
	inputCourse();

	cout << "---课程数修改成功！---" <<endl;
}

void Course::display() {
	printHead();

	//遍历数组，赋值给temp，调用temp对象find()函数进行输出
	Course temp;
	for(int i = 0; i < courseSum; i++){
		temp = course[i];
		temp.find();
	} 
}

//主函数用来做界面显示和函数调用
void main() {
		/*
	Teacher t;
//	t.addStudent();
//	t.findStudent();
//	Student::login();
//	Teacher::printHead();
//	t.delStudent();
	t.setStudent();
	Student::display();
	Teacher::outputTeacher();
	Student::outputStudent();

	*/
//	Course::display();
	

	Student stu;
	Teacher tea;

//	tea.addCourse();
//	tea.setCourse();

	int flg;
	bool result;

	do{
menu0:
		cout<<"┌───────────┐"<<endl
			<<"│     学生成绩管理     │"<<endl
			<<"│      和选课系统      │"<<endl
			<<"│     选择登录类型     │"<<endl
			<<"├───────────┤"<<endl
			<<"│     1.学生登录       │"<<endl
			<<"│     2.教师登录       │"<<endl
			<<"├———————————┤"<<endl
			<<"│     3.退出系统       │"<<endl
			<<"└───────────┘"<<endl;
		cout<<"请输入操作编号：";
		cin>>flg;
		switch (flg)
		{
		case(1):
			system("cls");

			//判断登录是否成功
			result = false;
			result = stu.login();
			if(result) {goto menu1;}
			break;
		case(2):
			system("cls");

			//判断登录是否成功
			result = false;
			result = tea.login();
			if(result) {goto menu2;}
			break;
		case(3):
			cout<<endl;
			cout<<"┌───────────┐"<<endl
				<<"│      感谢使用！      │"<<endl
				<<"└───────────┘"<<endl;
			getchar();getchar();
			return;
		default:
			system("cls");
			cout<<endl<<"───输入有误，请重新输入！───"<<endl<<endl;
			goto menu0;
			break;
		}
	}while(1);

menu1:
	do{
		cout<<"┌───────────┐"<<endl
			<<"│     学生成绩管理     │"<<endl
			<<"│      和选课系统      │"<<endl
			<<"│    学生操作主菜单    │"<<endl
			<<"├───────────┤"<<endl
			<<"│      1.查询成绩      │"<<endl
			<<"│      2.学生选课      │"<<endl
			<<"│      3.更改密码      │"<<endl
			<<"├———————————┤"<<endl
			<<"│      4.退出登录      │"<<endl
			<<"└───────────┘"<<endl;
		cout<<"请输入操作编号：";
		cin>>flg;
		switch (flg)
		{
		case(1):
			system("cls");
			stu.showMyInfo();
			break;
		case(2):
			system("cls");
			stu.chooseCourse();
			break;
		case(3):
			system("cls");
			stu.setSpassword();
			break;
		case(4):
			system("cls");
			goto menu0;
			return;
		default:
			system("cls");
			cout<<endl<<"───输入有误，请重新输入！───"<<endl<<endl;
			goto menu1;
			break;
		}
	}while(1);

menu2:
	do{
		cout<<"┌───────────┐"<<endl
			<<"│     学生成绩管理     │"<<endl
			<<"│      和选课系统      │"<<endl
			<<"│    教师操作主菜单    │"<<endl
			<<"├───────────┤"<<endl
			<<"│      1.学生管理      │"<<endl
			<<"│      2.选课管理      │"<<endl
			<<"├———————————┤"<<endl
			<<"│    3.显示我的信息    │"<<endl
			<<"│      4.更改密码      │"<<endl
			<<"├———————————┤"<<endl
			<<"│      5.退出登录      │"<<endl
			<<"└───────────┘"<<endl;
		cout<<"请输入操作编号：";
		cin>>flg;
		switch (flg)
		{
		case(1):
			system("cls");
			goto menu21;
			break;
		case(2):
			system("cls");
			tea.setCourse();
			break;
		case(3):
			system("cls");
			tea.showMyInfo();
			break;
		case(4):
			system("cls");
			tea.setpassword();
			break;
		case(5):
			system("cls");
			goto menu0;
			break;
		default:
			system("cls");
			cout<<endl<<"───输入有误，请重新输入！───"<<endl<<endl;
			goto menu2;
			break;
		}
	}while(1);

menu21:
	do{
		cout<<"┌───────────┐"<<endl
			<<"│     学生成绩管理     │"<<endl
			<<"│      和选课系统      │"<<endl
			<<"│    教师操作主菜单    │"<<endl
			<<"│      /学生管理       │"<<endl
			<<"├───────────┤"<<endl
			<<"│    1.查询学生信息    │"<<endl
			<<"│    2.修改学生信息    │"<<endl
			<<"│    3.增加学生信息    │"<<endl
			<<"│    4.删除学生信息    │"<<endl
			<<"│  5.显示所有学生信息  │"<<endl
			<<"├———————————┤"<<endl
			<<"│      6.退出登录      │"<<endl
			<<"└───────────┘"<<endl;
		cout<<"请输入操作编号：";
		cin>>flg;
		switch (flg)
		{
		case(1):
			system("cls");
			tea.findStudent();
			break;
		case(2):
			system("cls");
			tea.setStudent();
			break;
		case(3):
			system("cls");
			tea.addStudent();
			break;
		case(4):
			system("cls");
			tea.delStudent();
			break;
		case(5):
			system("cls");
			Student::display();
			goto menu25;
			break;
		case(6):
			system("cls");
			goto menu0;
			break;
		default:
			system("cls");
			cout<<endl<<"───输入有误，请重新输入！───"<<endl<<endl;
			goto menu21;
			break;
		}
	}while(1);

menu25:
	do{
		cout<<"┌───────────┐"<<endl
			<<"│     学生成绩管理     │"<<endl
			<<"│      和选课系统      │"<<endl
			<<"│      /学生管理       │"<<endl
			<<"│   /查询学生信息菜单  │"<<endl
			<<"├───────────┤"<<endl
			<<"│    1.升序排列成绩    │"<<endl
			<<"│    2.降序排列成绩    │"<<endl
			<<"│    3.学号排列成绩    │"<<endl
			<<"│   4.列出不及格名单   │"<<endl
			<<"├———————————┤"<<endl
			<<"│    5.返回上级菜单    │"<<endl
			<<"└───────────┘"<<endl;
		cout<<"请输入操作编号：";
		cin>>flg;
		switch (flg)
		{
		case(1):
			system("cls");
			Student::sortByASC();
			Student::display();
			break;
		case(2):
			system("cls");
			Student::sortByDESC();
			Student::display();
			break;
		case(3):
			system("cls");
			Student::sortBySid();
			Student::display();
			break;
		case(4):
			system("cls");
			Student::selectFail();
			break;
		case(5):
			system("cls");
			goto menu2;
			return;
		default:
			system("cls");
			cout<<endl<<"───输入有误，请重新输入！───"<<endl<<endl;
			goto menu25;
			break;
		}
	}while(1);
}