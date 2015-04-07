
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int T_SUM = 128;	//��ʦ������
const int S_SUM = 1024;  //ѧ��������
const int C_SUM = 128;	//�γ�������

class Teacher {
public:
	static int inputTeacher();	//���ļ������ʦ���ݵ���������
	static void outputTeacher();	//�Ӷ������������ʦ���ݵ��ļ�
	static void printHead();	//����ֶ���
	static int teacherSum;	//����ʵ�ʽ�ʦ����
	void init(string tid, string tname, string tpassword);	//��ʼ����ʦ��Ϣ
	bool login();	//��¼����
	void find();	//��ѯĳ����ʦ��Ϣ
	void addStudent();	//����ʵ����һ��ѧ���ಢ����ѧ�����init����������ѧ����Ϣ��
	void delStudent();	//ɾ��ѧ����Ϣ
	void setStudent();	//�޸�ѧ����Ϣ
	int findStudent();	//��ѯѧ����Ϣ
	void setpassword();	//��ʦ�޸��Լ�������
	void showMyInfo();	//����¼��ʦ�鿴�Լ�����Ϣ
	void addCourse();	//���ӿγ���Ϣ
	void delCourse();	//ɾ���γ���Ϣ
	void setCourse();	//�޸Ŀγ���Ϣ
protected:
	string tid;			//��ʦid
	string tname;		//��ʦ����
	string tpassword;	//��ʦ��¼����
};

class Student {
public:
	friend class Teacher;	//��Ԫ�࣬ʹ��ѧ����ı�����Ա�ܱ���ʦ�����
	static int inputStudent();	//���ļ�����ѧ�����ݵ���������
	static void outputStudent();	//�Ӷ����������ѧ�����ݵ��ļ�
	static void sortByASC(); //�ܳɼ�����������
	static void sortByDESC();	//�ܳɼ�����������
	static void sortBySid();	//�ܳɼ���ѧ������
	static void printHead();	//����ֶ���
	static void display();	//��ʾ����ѧ����Ϣ
	static void selectFail();	//��ʾ�������ѧ��
	static int studentSum;	//����ʵ��ѧ��
	void init(string sid, string sname, string spassword, double midScore , double finalScore);	//��ʼ��(����)ѧ����Ϣ
	bool login();	//��¼����
	void add();	//����ѧ����Ϣ
	void del();	//ɾ��ѧ����Ϣ
	void find();	//��ѯĳ��ѧ����Ϣ
	void setSid();	//�޸�ѧ��id
	void setSname();	//�޸�ѧ������
	void setSpassword();	//�޸�ѧ������
	void setMidScore();	//�޸����гɼ�
	void setFinalScore();	//�޸���ĩ�ɼ�
	void showMyInfo();	//����¼ѧ���鿴�Լ�����Ϣ
	void chooseCourse();	//ѡ�޿γ�
protected:
	string sid;	//ѧ��id
	string sname;	//ѧ������
	string spassword;	// ѧ����¼����
	double midScore;	//ѧ�����гɼ�
	double finalScore;	//ѧ����ĩ�ɼ�
	double sumScore;	//ѧ���ܷ�
	double aveScore;	//ѧ��ƽ���ɼ�
	string _course;	//ѡ�޿γ���
};

class Course {
public:
	friend class Teacher;	//��Ԫ�࣬ʹ�ÿγ���ı�����Ա�ܱ���ʦ�����
	friend class Student;	//��Ԫ�࣬ʹ�ÿγ���ı�����Ա�ܱ�ѧ�������
	static int inputCourse();	//���ļ�����γ����ݵ���������
	static void outputCourse();	//�Ӷ�����������γ����ݵ��ļ�
	static void display();	//��ʾ���пγ�
	static void printHead();	//����ֶ���
	static int courseSum;	//����ʵ�ʿγ�
	void init(string cid, string cname, int csum);	//��ʼ���γ���Ϣ
	void add();	//��ӿγ�
	void del();	//ɾ���γ�
	void setCid();	//�޸Ŀγ̺�
	void setCname();	//�޸Ŀγ���
	void setCsum();	//�޸Ŀγ���
	void find();	//��ѯ�γ���Ϣ
protected:
	string cid;		//�γ̱��
	string cname;	//�γ���
	int csum;	//�γ�ʣ����
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

	//û���ļ��ʹ����ļ�
	if(!fin) {
		outputTeacher();
		return 0;	//����0����ʦ��
	}

	//�����ֶ���
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
	if(!fout) {cout<<"д������ʧ�ܣ�";return;}

	fout << "��ʦid" << "\t"
		<<	"����"	<< "\t"
		<<	"����"	<< "\t";
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
	cout << "��ʦid" << "\t"
		<<	"����"	<< "\t"
		<<	"����"	<< "\t";
	cout << endl;
}

bool Teacher::login() {
	cout << endl;

	string tid;
	string tpassword;
	cout << "---��¼����---" << endl;
	cout << "�������ʦid��" ;
	cin >> tid;
	cout << "����������: " ;
	cin >> tpassword;

	Teacher temp;
	for(int i = 0; i < teacherSum; i++) {
		temp = teacher[i];
		if(tid == temp.tid) {
			if(tpassword == temp.tpassword) {
				cout << endl;
				cout << "---��¼�ɹ�����ӭ��" << temp.tname << "!---" <<endl;

				//��¼�ɹ���Ҫ�ö��������д�ŵ���Ϣ��ʼ����ǰ����
				init(teacher[i].tid, teacher[i].tname, teacher[i].tpassword);

				return true;
			} else {
				cout << endl;
				cout << "---��¼ʧ�ܣ����벻��ȷ��---" ;
				cout << endl;
				return false;
			}
		}
	}

	cout << endl;
	cout << "---��¼ʧ�ܣ��Ҳ����ý�ʦid��---" ;
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
	string spassword = "123456";	//Ĭ������
	double midScore;	
	double finalScore;	

	cout << endl;

back:
	cout << "������ѧ��ѧ�ţ�";
	cin >> sid;

	//ѧ�Ų����ظ�������Ϸ��Լ��
	for(int i = 0; i < Student::studentSum; i++) {
		if(sid == student[i].sid ) {
			cout<<endl
				<<"ѧ�Ų����ظ������������롣"
				<<endl;
			goto back;
		}
	}

	cout << "������ѧ��������";
	cin >> sname;
	cout << "������ѧ�����гɼ���";
	cin >> midScore;
	cout << "������ѧ����ĩ�ɼ���";
	cin >> finalScore;

	temp.init(sid, sname, spassword, midScore, finalScore);
	temp.add();

	cout << endl;
	cout << "---���ѧ����Ϣ�ɹ���---";
	cout << endl;
}

int Teacher::findStudent() {
	Student temp;

	string sid;
	cout << endl;
	cout << "������Ҫ����ѧ����ѧ�ţ�";
	cin >> sid;

	int i;
	for(i = 0; i < Student::studentSum; i++) {
		if(sid == student[i].sid) {
			temp.init(student[i].sid, student[i].sname, student[i].spassword, student[i].midScore, student[i].finalScore);
			cout << "---�ҵ�����ѧ����Ϣ---";
			Student::printHead();
			temp.find();

			//�����ҵ���ѧ���ڶ��������е�λ��
			return i;
		}
	}

	cout << endl;
	cout << "---�Ҳ�����ѧ����---";
	cout << endl;
	return -1;

}

void Teacher::delStudent() {
	Student temp;

	cout<<endl;
	cout<< "---���Ȳ���Ҫ��ɾ����ѧ��---";
	cout<<endl;

	string sid;
	cout << endl;
	cout << "������Ҫ����ѧ����ѧ�ţ�";
	cin >> sid;

	for(int i = 0; i < Student::studentSum; i++) {
		if(sid == student[i].sid) {
			temp.init(student[i].sid, student[i].sname, student[i].spassword, student[i].midScore, student[i].finalScore);
			temp.del();
			return;
		}
	}

	cout << endl;
	cout << "---�Ҳ�����ѧ����---";
	cout << endl;
}

void Teacher::setStudent() {
	Student temp;

	int point = findStudent();
	cout << endl;

	temp = student[point];

	int flg;
	cout<<"��������������������������"<<endl
		<<"��   ѧ���ɼ�����ϵͳ   ��"<<endl
		<<"��   �޸�ѧ����Ϣ�˵�   ��"<<endl
		<<"��������������������������"<<endl
		<<"��   1.�޸�ѧ��ѧ��     ��"<<endl
		<<"��   2.�޸�ѧ������     ��"<<endl
		<<"��   3.�޸�ѧ������     ��"<<endl
		<<"��   4.�޸����гɼ�     ��"<<endl
		<<"��   5.�޸���ĩ�ɼ�     ��"<<endl
		<<"��   6.�����ϼ��˵�     ��"<<endl
		<<"��������������������������"<<endl;
	cout<<"�����������ţ�";
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
			cout<<endl<<"�������������󣡩�����"<<endl<<endl;
			break;
	}
}

void Teacher::setpassword() {
	string tpassword;
	cout << endl;
	cout << "�����������룺";

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

	cout << "---�����޸ĳɹ���---" <<endl;
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
	cout << "������γ̺ţ�";
	cin >> cid;

	//ѧ�Ų����ظ�������Ϸ��Լ��
	for(int i = 0; i < Course::courseSum; i++) {
		if(cid == course[i].cid ) {
			cout<< endl
				<< "---�γ̺Ų����ظ������������룡---"
				<< endl;
			goto back9;
		}
	}

	cout << "������γ����ƣ�";
	cin >> cname;
	cout << "������γ���Ŀ��";
	cin >> csum; 

	temp.init(cid, cname, csum);
	temp.add();

	cout << endl;
	cout << "---��ӿγ���Ϣ�ɹ���---";
	cout << endl;
}

void Teacher::delCourse() {
	Course temp;

	cout<<endl;
	cout<< "---���Ȳ���Ҫ��ɾ���Ŀγ�---";
	cout<<endl;

	string cid;
	cout << endl;
	cout << "������Ҫ���ҵĿγ̺ţ�";
	cin >> cid;

	for(int i = 0; i < Course::courseSum; i++) {
		if(cid == course[i].cid) {
			temp.init(course[i].cid, course[i].cname, course[i].csum);
			temp.del();
			return;
		}
	}

	cout << endl;
	cout << "---�Ҳ����ÿγ̣�---";
	cout << endl;
}

void Teacher::setCourse() {
	Course temp;

	cout<<endl;
	cout<< "---���Ȳ���Ҫ���޸ĵĿγ�---";
	cout<<endl;

	string cid;
	cout << endl;
	cout << "������Ҫ���ҵĿγ̺ţ�";
	cin >> cid;

	int point = -1;
	for(int i = 0; i < Course::courseSum; i++) {
		if(cid == course[i].cid) {
			temp = course[i];
			point = i;
		}
	}

	cout << "---�ҵ����¿γ�---" << endl;
	temp.find();

	if(point == -1) {
		cout << endl;
		cout << "---�Ҳ����ÿγ̣�---";
		cout << endl;
		return;
	}

	int flg;
	cout<<"��������������������������"<<endl
		<<"��   ѧ���ɼ�����ϵͳ   ��"<<endl
		<<"��     �γ̹���˵�     ��"<<endl
		<<"��������������������������"<<endl
		<<"��     1.�޸Ŀγ̺�     ��"<<endl
		<<"��     2.�޸Ŀγ���     ��"<<endl
		<<"��     3.�޸Ŀγ���     ��"<<endl
		<<"��������������������������"<<endl
		<<"��    4.�����ϼ��˵�    ��"<<endl
		<<"��������������������������"<<endl;
	cout<<"�����������ţ�";
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
			cout<<endl<<"�������������󣡩�����"<<endl<<endl;
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

	//û���ļ��ʹ����ļ�
	if(!fin) {
		outputStudent();
		return 0;	//����0��ѧ����
	}

	//�����ֶ���
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
		fin >> temp;	//�ֺܷ�ƽ���ɼ���init����ȥ���㣬�������tempΪ���˵�
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
	if(!fout) {cout<<"д������ʧ�ܣ�";return;}

	fout << "ѧ��" << "\t"
		<<	"����"	<< "\t"
		<<	"����"	<< "\t"
		<<	"����"	<< "\t"
		<<	"��ĩ"	<< "\t"
		<<	"�ܷ�"	<< "\t"
		<<	"ƽ����"	<< "\t"
		<<	"ѡ�޿�"	<< "\t";
	fout << endl;

	for(int i = 0; i < studentSum; i++){

		//ֻ��δ�����ɾ����ѧ�������ļ�
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
	cout << "ѧ��" << "\t"
		<<	"����"	<< "\t"
		<<	"����"	<< "\t"
		<<	"����"	<< "\t"
		<<	"��ĩ"	<< "\t"
		<<	"�ܷ�"	<< "\t"
		<<	"ƽ����"	<< "\t"
		<<	"ѡ�޿�"	<< "\t";
	cout << endl;
}

void Student::init(string sid, string sname, string spassword, double midScore , double finalScore) {
	this -> sid = sid;
	this -> sname = sname;
	this -> spassword = spassword;
	this -> midScore = midScore;
	this -> finalScore = finalScore;

	this -> _course = "��";

	//�����ֺܷ�ƽ����
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

	//���ҵ�Ҫ��ɾ����ѧ���ڶ��������е�λ��
	for(int i = 0; i < studentSum; i++) {
		if(sid == student[i].sid ) {
			//����ȷ��
			cout << endl;
			cout << "---��ȷ��Ҫɾ��ѧ����" << sid << "��" << student[i].sname << "��---";
			cout << endl;
			cout << "---����Yȷ��---";
			cout << endl;
			cin >> flg0;

			if(flg0 == "Y" || flg0 == "y") {

				//����ɾ��ѧ����sid���Ϊdeleted
				student[i].sid = "deleted";

				//ѧ������-1
				Student::studentSum--;	

				//ʹɾ�����ѧ�����ǵ�����������
				outputStudent();
				inputStudent();	
				flg = true;

				cout << endl;
				cout << "---ɾ��ѧ����Ϣ�ɹ���---";
				cout << endl;

				break;
			} else {
				break;
			}
		}
	}

	if(flg == false) {
		cout << endl;
		cout << "---ɾ��ѧ����Ϣʧ�ܣ�---";
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

	//����������student�е����ݰ��ܷ���������
	for(int i = 0; i < studentSum - 1; i++){
		for(int j = i + 1; j < studentSum; j++){
			if( student[i].sumScore > student[j].sumScore){
				temp = student[i]; 
				student[i] = student[j]; 
				student[j] = temp;
			}
		}
	}

	//������ļ�����
	outputStudent();
}

void Student::sortByDESC() {
	Student temp;

	//����������student�е����ݰ��ֽܷ�������
	for(int i = 0; i < studentSum - 1; i++){
		for(int j = i + 1; j < studentSum; j++){
			if( student[i].sumScore < student[j].sumScore){
				temp = student[i]; 
				student[i] = student[j]; 
				student[j] = temp;
			}
		}
	}

	//������ļ�����
	outputStudent();
}

void Student::sortBySid() {
	Student temp;

	//����������student�е����ݰ��ֽܷ�������
	for(int i = 0; i < studentSum - 1; i++){
		for(int j = i + 1; j < studentSum; j++){
			if( student[i].sid > student[j].sid){
				temp = student[i]; 
				student[i] = student[j]; 
				student[j] = temp;
			}
		}
	}

	//������ļ�����
	outputStudent();
}

void Student::display() {
	printHead();

	//�������飬��ֵ��temp������temp����find()�����������
	Student temp;
	for(int i = 0; i < studentSum; i++){
		temp = student[i];
		temp.find();
	}
}

void Student::selectFail() {
	printHead();

	//�������飬��ֵ��temp������temp����find()�����������
	Student temp;
	for(int i = 0; i < studentSum; i++){

		//���У���ĩ��һ�Ʋ������ɸѡ���������
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

		//ע��this
		if(this -> sid == student[i].sid ) {
back0:
			cout << "�������µ�ѧ�ţ�";
			cin >> sid;

			//ѧ�Ų����ظ�������Ϸ��Լ��
			for(int i = 0; i < Student::studentSum; i++) {
				if(sid == student[i].sid ) {
					cout<< endl
						<< "---ѧ�Ų����ظ������������룡---"
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

	cout << "---ѧ���޸ĳɹ���---" <<endl;
}

void Student::setSname() {
	cout << endl;

	string sname;
	for(int i = 0; i < Student::studentSum; i++) {
		if(this -> sid == student[i].sid) {
			cout << "�������µ�������";
			cin >> sname;

			student[i].sname = sname;
			break;
		}

	}

	outputStudent();
	inputStudent();

	cout << "---�����޸ĳɹ���---" <<endl;
}

void Student::setSpassword() {
	cout << endl;

	string spassword;
	for(int i = 0; i < Student::studentSum; i++) {
		if(this -> sid == student[i].sid) {
back1:
			cout << "�������µ����룺";
			cin >> spassword;

			//�����벻��Ϊ��ʼ����123456 �Ҳ�������6λ
			if(spassword == "123456" && spassword.length() < 6) {
				cout<<endl
					<<"������ڼ򵥣����������룡"
					<<endl
					<<endl;
				goto back1;

				//ѧ����Ȩ�޸����Լ������룬Ҫ����ǰ�����spasswordҲ������
				this -> spassword = spassword;

				student[i].spassword = spassword;
				break;
			}
		}
	}

	outputStudent();
	inputStudent();

	cout << "---�����޸ĳɹ���---" <<endl;
}

void Student::setMidScore() {
	cout << endl;

	double midScore;
	for(int i = 0; i < Student::studentSum; i++) {
		if(this -> sid == student[i].sid) {

			cout << "�������µ����гɼ���";
			cin >> midScore;

			student[i].midScore = midScore;
			break;

		}
	}

	outputStudent();
	inputStudent();

	cout << "---���гɼ��޸ĳɹ���---" <<endl;
}

void Student::setFinalScore() {
	cout << endl;

	double finalScore;
	for(int i = 0; i < Student::studentSum; i++) {
		if(this -> sid == student[i].sid) {

			cout << "�������µ���ĩ�ɼ���";
			cin >> finalScore;

			student[i].finalScore = finalScore;
			break;

		}
	}

	outputStudent();
	inputStudent();

	cout << "---��ĩ�ɼ��޸ĳɹ���---" <<endl;
}

bool Student::login() {
	cout << endl;

	string sid;
	string spassword;
	cout << "---��¼����---" << endl;
	cout << "������ѧ�ţ�" ;
	cin >> sid;
	cout << "���������루��ʼ����123456��: " ;
	cin >> spassword;

	Student temp;
	for(int i = 0; i < studentSum; i++) {
		temp = student[i];
		if(sid == temp.sid) {
			if(spassword == temp.spassword) {
				
				//�ж��Ƿ��һ�ε�¼����һ�ε�¼��Ҫ������
				if(temp.spassword != "123456") {
					cout << endl;
					cout << "---��¼�ɹ�����ӭ��" << temp.sname << "!---" <<endl;

					//��¼�ɹ���Ҫ�ö��������д�ŵ���Ϣ��ʼ����ǰ����
					init(student[i].sid, student[i].sname, student[i].spassword, student[i].midScore , student[i].finalScore);

					return true;
				} else {
					cout << endl;
					cout << "---��¼�ɹ������ǵ�һ�ε�¼����Ҫ�޸����룡 ---" << endl;

					//��¼�ɹ���Ҫ�ö��������д�ŵ���Ϣ��ʼ����ǰ����
					init(student[i].sid, student[i].sname, student[i].spassword, student[i].midScore , student[i].finalScore);

					student[i].setSpassword();

					return true;
				}
			} else {
				cout << endl;
				cout << "---��¼ʧ�ܣ����벻��ȷ��---" ;
				return false;
			}
		}
	}

	cout << endl;
	cout << "---��¼ʧ�ܣ��Ҳ�����ѧ�ţ�����ϵ����Ա��---" ;
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
	cout << "��ѡ��Ҫѡ�޵Ŀγ̺ţ������ѡ��ѡ�޺�����ѡ����" << endl;
	cin >> cid;

	for(int i = 0; i < Course::courseSum; i++) {
		if(cid == course[i].cid) {
			if(course[i].csum > 0) {
				_course = course[i].cname;
				course[i].csum--;	//ѡ�޺󣬿γ�ʣ����-1

				//��������
				for(int j = 0; j < Student::studentSum; j++)  {
					if(this -> sid == student[j].sid) {
						student[j]._course = course[i].cname;
						outputStudent();

						//�ǵñ���course���������е����ݵ��ļ�����
						Course::outputCourse();	
						break;
					}
				}

				cout << "---ѡ��"<< course[i].cname << "�ɹ���---";
				cout << endl;
				return;

			} else {
				cout << "---�ÿγ�������---";
				cout << endl;
			}
		}
	}

	cout << "---�Ҳ����ÿγ̣�---";
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

	//û���ļ��ʹ����ļ�
	if(!fin) {
		outputCourse();
		return 0;	//����0���γ���
	}

	//�����ֶ���
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
	if(!fout) {cout<<"д������ʧ�ܣ�";return;}

	fout << "�γ�id" << "\t"
		<<	"�γ���"	<< "\t"
		<<	"ʣ����"	<< "\t";
	fout << endl; 

	for(int i = 0; i < courseSum; i++){

		//ֻ��δ�����ɾ���Ŀγ̵����ļ�
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
	cout << "�γ�id" << "\t"
		<<	"�γ���"	<< "\t"
		<<	"ʣ����"	<< "\t";
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

	//���ҵ�Ҫ��ɾ���Ŀγ��ڶ��������е�λ��
	for(int i = 0; i < courseSum; i++) {
		if(cid == course[i].cid ) {
			//����ȷ��
			cout << endl;
			cout << "---��ȷ��Ҫɾ���γ̣�" << cid << "��" << course[i].cid << "��---";
			cout << endl;
			cout << "---����Yȷ��---";
			cout << endl;
			cin >> flg0;

			if(flg0 == "Y" || flg0 == "y") {

				//����ɾ���γ̵�cid���Ϊdeleted
				course[i].cid = "deleted";

				//�γ�����-1
				Course::courseSum--;	

				//ʹɾ����Ŀγ̸��ǵ�����������
				outputCourse();
				inputCourse();	
				flg = true;

				cout << endl;
				cout << "---ɾ���γ���Ϣ�ɹ���---";
				cout << endl;

				break;
			} else {
				break;
			}
		}
	}

	if(flg == false) {
		cout << endl;
		cout << "---ɾ���γ���Ϣʧ�ܣ�---";
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

		//ע��this
		if(this -> cid == course[i].cid) {
back1:
			cout << "�������µĿγ̺ţ�";
			cin >> cid;

			//ѧ�Ų����ظ�������Ϸ��Լ��
			for(int i = 0; i < Course::courseSum; i++) {
				if(cid == course[i].cid ) {
					cout<< endl
						<< "---�γ̺Ų����ظ������������룡---"
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

	cout << "---�γ̺��޸ĳɹ���---" <<endl;

}

void Course::setCname() {
	cout << endl;

	string cname;
	for(int i = 0; i < courseSum; i++) {
		if(this -> cname == course[i].cname) {
			cout << "�������µĿγ̺ţ�";
			cin >> cname;

			course[i].cname = cname;
			break;
		}
	}

	outputCourse();
	inputCourse();

	cout << "---�γ����޸ĳɹ���---" <<endl;
}

void Course::setCsum() {
	cout << endl;

	int csum;
	for(int i = 0; i < courseSum; i++) {
		if(this -> csum == course[i].csum) {
			cout << "�������µĿγ�����";
			cin >> csum;

			course[i].csum = csum;
			break;
		}
	}

	outputCourse();
	inputCourse();

	cout << "---�γ����޸ĳɹ���---" <<endl;
}

void Course::display() {
	printHead();

	//�������飬��ֵ��temp������temp����find()�����������
	Course temp;
	for(int i = 0; i < courseSum; i++){
		temp = course[i];
		temp.find();
	} 
}

//������������������ʾ�ͺ�������
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
		cout<<"��������������������������"<<endl
			<<"��     ѧ���ɼ�����     ��"<<endl
			<<"��      ��ѡ��ϵͳ      ��"<<endl
			<<"��     ѡ���¼����     ��"<<endl
			<<"��������������������������"<<endl
			<<"��     1.ѧ����¼       ��"<<endl
			<<"��     2.��ʦ��¼       ��"<<endl
			<<"��������������������������"<<endl
			<<"��     3.�˳�ϵͳ       ��"<<endl
			<<"��������������������������"<<endl;
		cout<<"�����������ţ�";
		cin>>flg;
		switch (flg)
		{
		case(1):
			system("cls");

			//�жϵ�¼�Ƿ�ɹ�
			result = false;
			result = stu.login();
			if(result) {goto menu1;}
			break;
		case(2):
			system("cls");

			//�жϵ�¼�Ƿ�ɹ�
			result = false;
			result = tea.login();
			if(result) {goto menu2;}
			break;
		case(3):
			cout<<endl;
			cout<<"��������������������������"<<endl
				<<"��      ��лʹ�ã�      ��"<<endl
				<<"��������������������������"<<endl;
			getchar();getchar();
			return;
		default:
			system("cls");
			cout<<endl<<"�����������������������룡������"<<endl<<endl;
			goto menu0;
			break;
		}
	}while(1);

menu1:
	do{
		cout<<"��������������������������"<<endl
			<<"��     ѧ���ɼ�����     ��"<<endl
			<<"��      ��ѡ��ϵͳ      ��"<<endl
			<<"��    ѧ���������˵�    ��"<<endl
			<<"��������������������������"<<endl
			<<"��      1.��ѯ�ɼ�      ��"<<endl
			<<"��      2.ѧ��ѡ��      ��"<<endl
			<<"��      3.��������      ��"<<endl
			<<"��������������������������"<<endl
			<<"��      4.�˳���¼      ��"<<endl
			<<"��������������������������"<<endl;
		cout<<"�����������ţ�";
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
			cout<<endl<<"�����������������������룡������"<<endl<<endl;
			goto menu1;
			break;
		}
	}while(1);

menu2:
	do{
		cout<<"��������������������������"<<endl
			<<"��     ѧ���ɼ�����     ��"<<endl
			<<"��      ��ѡ��ϵͳ      ��"<<endl
			<<"��    ��ʦ�������˵�    ��"<<endl
			<<"��������������������������"<<endl
			<<"��      1.ѧ������      ��"<<endl
			<<"��      2.ѡ�ι���      ��"<<endl
			<<"��������������������������"<<endl
			<<"��    3.��ʾ�ҵ���Ϣ    ��"<<endl
			<<"��      4.��������      ��"<<endl
			<<"��������������������������"<<endl
			<<"��      5.�˳���¼      ��"<<endl
			<<"��������������������������"<<endl;
		cout<<"�����������ţ�";
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
			cout<<endl<<"�����������������������룡������"<<endl<<endl;
			goto menu2;
			break;
		}
	}while(1);

menu21:
	do{
		cout<<"��������������������������"<<endl
			<<"��     ѧ���ɼ�����     ��"<<endl
			<<"��      ��ѡ��ϵͳ      ��"<<endl
			<<"��    ��ʦ�������˵�    ��"<<endl
			<<"��      /ѧ������       ��"<<endl
			<<"��������������������������"<<endl
			<<"��    1.��ѯѧ����Ϣ    ��"<<endl
			<<"��    2.�޸�ѧ����Ϣ    ��"<<endl
			<<"��    3.����ѧ����Ϣ    ��"<<endl
			<<"��    4.ɾ��ѧ����Ϣ    ��"<<endl
			<<"��  5.��ʾ����ѧ����Ϣ  ��"<<endl
			<<"��������������������������"<<endl
			<<"��      6.�˳���¼      ��"<<endl
			<<"��������������������������"<<endl;
		cout<<"�����������ţ�";
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
			cout<<endl<<"�����������������������룡������"<<endl<<endl;
			goto menu21;
			break;
		}
	}while(1);

menu25:
	do{
		cout<<"��������������������������"<<endl
			<<"��     ѧ���ɼ�����     ��"<<endl
			<<"��      ��ѡ��ϵͳ      ��"<<endl
			<<"��      /ѧ������       ��"<<endl
			<<"��   /��ѯѧ����Ϣ�˵�  ��"<<endl
			<<"��������������������������"<<endl
			<<"��    1.�������гɼ�    ��"<<endl
			<<"��    2.�������гɼ�    ��"<<endl
			<<"��    3.ѧ�����гɼ�    ��"<<endl
			<<"��   4.�г�����������   ��"<<endl
			<<"��������������������������"<<endl
			<<"��    5.�����ϼ��˵�    ��"<<endl
			<<"��������������������������"<<endl;
		cout<<"�����������ţ�";
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
			cout<<endl<<"�����������������������룡������"<<endl<<endl;
			goto menu25;
			break;
		}
	}while(1);
}