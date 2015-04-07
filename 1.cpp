#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int T_SUM = 128;	//��ʦ������
const int S_SUM = 1024;  //ѧ��������

class Teacher {
public:
	static int inputTeacher();	//���ļ������ʦ���ݵ���������
	static void outputTeacher();	//�Ӷ������������ʦ���ݵ��ļ�
	static int teacherSum;	//����ʵ�ʽ�ʦ����
	void initStudent();	//����ʵ����һ��ѧ���ಢ����ѧ�����initStudent����������ѧ����Ϣ��
	void delStudent();	//ɾ��ѧ����Ϣ
	void setStudent();	//�޸�ѧ����Ϣ
	void displayStudent();	//��ѯѧ����Ϣ
	void setpassword();	//��ʦ�޸��Լ�������
protected:
	string tid;			//��ʦid
	string tname;		//��ʦ����
	string tpassword;	//��ʦ��¼����
};

class Student {
public:
	static int inputStudent();	//���ļ�����ѧ�����ݵ���������
	static void outputStudent();	//�Ӷ����������ѧ�����ݵ��ļ�
	static int studentSum;	//����ʵ��ѧ��
	void init(string sid, string sname, string spassword, int midScore , int finalScore);	//��ʼ��(����)ѧ����Ϣ
	void del();	//ɾ��ѧ����Ϣ
	void find();	//��ѯĳ��ѧ����Ϣ
	void sortByASC(); //�ܳɼ�����������
	void sortByDESC();	//�ܳɼ�����������
	void display();	//��ʾ����ѧ����Ϣ
	void setSid();	//�޸�ѧ��id
	void setSname();	//�޸�ѧ������
	void setSpassword();	//�޸�ѧ������
	void setMidScore();	//�޸����гɼ�
	void setFinalScore();	//�޸���ĩ�ɼ�
protected:
	string sid;	//ѧ��id
	string sname;	//ѧ������
	string spassword;	// ѧ����¼����
	int midScore;	//ѧ�����гɼ�
	int finalScore;	//ѧ����ĩ�ɼ�
	int sumScore;	//ѧ���ܷ�
	int aveScore;	//ѧ��ƽ���ɼ�
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
	if(!fin) return 0;	//û���ļ�������0����ʦ��
	for(int i = 0; i < T_SUM; i++){
		fin >> tid; 
		fin >> tname;
		fin >> tpassword;

	}
}


//class of Student
