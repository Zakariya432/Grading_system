#include<iostream>
#include<string.h>
#include<fstream> // for file system


using namespace std;

class Student; // forward declaration of class Student

class Course
{
	int courseCode;
	string coursename;
	int insemMarks;
	int endsemMarks;
	int credit;

	public:
	void getCourse(); // get course details
	void showCourse(); // show course details!!
	void getInsmarks();   // get insemester marks for a subject
	void getEndsmarks(); // get endsemester marks for a subject
	void showInsmarks(); // show insem marks
	void showEndsmarks(); // show endsem marks
	int EndsMarks(); // to retrieve endsemester marks for a particular student!!
	int Total(); // calculate the total marks of the student(insemMarks+endsemMarks)
};

class TheoryCourse:public Course
{
	int totalM;// total marks

	public:

	int& gettotalM();
	friend void totalMarks(Student&);
};

class LaboratoryCourse:public Course
{
	int totalM;

	public:

	int& gettotalM();
	friend void totalMarks(Student&);
};


class Student
{
	string name;
	int rollnum;
	int numLC;
	int numTC;

	TheoryCourse*tc;
	LaboratoryCourse*lc;

	public:

	Student()
	{
		name="";
		rollnum=0;
		numLC=0;
		numTC=0;
		tc=NULL;
		lc=NULL;
	}

	void details();
	int getnumTC(); // get the number of theory courses
	int getnumLC(); // get the number of laboratory courses
	void EndSemestermark();
	void InSemestermark();
	void TheoryExamResults(); // calculate the total marks obtained by the student in theory and show the result(whether pass/fail)
	void LaboratoryExamResults(); // calculate the total marks obtained by the student in laboratory and show the result(whether pass/fail)
	void TotalMarks(); // calculate the total marks(calls Total() of class Course)
	void writeFile(); // write contents to a file!!!
	void terminate();
};

//--- member functions of class Course ---//
void Course::getCourse()
{
	cout<<"Course name: ";
	cin>>coursename;
	cout<<"Course code: ";
	cin>>courseCode;
	cout<<"Credit: ";
	cin>>credit;
}

int Course::Total()
{
	return(insemMarks+endsemMarks);
}

int Course::EndsMarks()
{
	return endsemMarks;
}

void Course::showCourse()
{
	cout<<"Course name: "<<coursename<<"\n";
	cout<<"Course code: "<<courseCode<<"\n";
	cout<<"Credit: "<<credit<<"\n";
}


void Course::getEndsmarks()
{
	cout<<"End-semester marks: ";
	cin>>endsemMarks;
}

void Course::getInsmarks()
{
	cout<<"In-semester marks: ";
	cin>>insemMarks;
}

void Course::showInsmarks()
{
	cout<<"\nIn-semester marks: "<<insemMarks;
}

void Course::showEndsmarks()
{
	cout<<"\nEndsemester marks: "<<endsemMarks;
}

//--- Course member functions end here ---//


//--- member functions of class TheoryCourse ---//
int& TheoryCourse::gettotalM()
{
	return totalM;
}
///--- TheoryCourse member functions end here ----//

//--- member functions of class LaboratoryCourse ---//
int& LaboratoryCourse::gettotalM()
{
	return totalM;
}
//--- LaboratoryCourse member functions end here ---//


//--- member functions of class Student ---//
void Student::details()
{
	cout<<"Name: ";
	cin>>name;
	cout<<"Roll number: ";
	cin>>rollnum;
	cout<<"Number of theory courses taken up: ";
	cin>>numTC;
	cout<<"Number of laboratory courses taken up: ";
	cin>>numLC;

	tc=new TheoryCourse[numTC];
	lc=new LaboratoryCourse[numLC];
	cout<<"\nenter theory course details:\n\n";
	for(int i=0; i<numTC; i++)
	{
		cout<<"\n\n[[[ SUBJECT "<<i+1<<" ]]]\n";
		tc[i].getCourse();
	}

	cout<<"\nenter laboratory course details:\n\n";

	for(int i=0; i<numLC; i++)
	{
		cout<<"\n\n[[[ SUBJECT "<<i+1<<" ]]]\n";
		lc[i].getCourse();
	}
}

void Student::EndSemestermark()
{
	cout<<"\n\nenter endsemester marks for the theory subjects:\n\n";
	for(int i=0; i<numTC; i++)
	{
		tc[i].showCourse(); // showing the details for TheoryCourse[i]
		tc[i].getEndsmarks(); // getting the endsemester marks for TheoryCourse[i]
	}


	cout<<"\n\nenter endsemester marks for the laboratory subjects:\n\n";
	for(int i=0; i<numLC; i++)
	{
		lc[i].showCourse(); // showing the details for LaboratoryCourse[i]
		lc[i].getEndsmarks(); // getting the endsemester marks for LaboratoryCourse[i]
	}
}

void Student::InSemestermark()
{
	cout<<"\n\nenter insemester marks for the theory subjects:\n\n";
	for(int i=0; i<numTC; i++)
	{
		tc[i].showCourse(); // showing the details for TheoryCourse[i]
		tc[i].getInsmarks();// getting the insemester marks for TheoryCourse[i]
	}


	cout<<"\n\nenter insemester marks for the laboratory subjects:\n\n";
	for(int i=0; i<numLC; i++)
	{
		lc[i].showCourse(); // showing the details for LaboratoryCourse[i]
		lc[i].getInsmarks(); // getting the insemester marks for LaboratoryCourse[i]
	}
}

void Student::TheoryExamResults()
{
	int endsM;
	cout<<"Name: "<<name<<"\n";
	cout<<"Roll number: "<<rollnum<<"\n";
	
	for(int i=0; i<numTC; i++)
	{
		tc[i].showCourse();
		tc[i].showInsmarks();
		tc[i].showEndsmarks();
		endsM=tc[i].EndsMarks();
		if(endsM>=28 && tc[i].gettotalM()>=40)
		{
			cout<<"\nRESULT: Pass\n\n";
		}

		else
		{
			cout<<"\nRESULT: Fail\n\n";
		}
	}
}

void Student::LaboratoryExamResults()
{
	int endsM;
	cout<<"Name: "<<name<<"\n";
	cout<<"Roll number: "<<rollnum<<"\n";

	for(int i=0; i<numLC; i++)
	{
		lc[i].showCourse();
		lc[i].showInsmarks();
		lc[i].showEndsmarks();
		endsM=lc[i].EndsMarks();
		if(endsM>=35 && lc[i].gettotalM()>=50)
		{
			cout<<"\nRESULT: Pass\n\n";
		}

		else
		{
			cout<<"\nRESULT: Fail\n\n";
		}

	}

}


void Student::TotalMarks()
{
	// --- calculating total marks for theory subjects ---
	for(int i=0; i<numTC; i++)
		tc[i].gettotalM()=tc[i].Total();

	// --- calculating total marks for laboratory subjects ---
	for(int i=0; i<numLC; i++)
		lc[i].gettotalM()=lc[i].Total();
}


void Student::writeFile()
{
	ofstream fout;
	fout.open("StuDetails.txt", ios::app);

	for(int i=0; i<numTC; i++)
	{
		fout.write((char*)&tc[i], sizeof(tc[i]));
	}

	for(int i=0; i<numLC; i++)
	{
		fout.write((char*)&lc[i], sizeof(lc[i]));
	}
	fout.close();
}

void Student::terminate()
{
	delete[] tc;
	delete[] lc;
}
//--- member function definitions of class Student end here ---//

//--- friend functions ---//
void totalMarks(Student std) 
{
	std.TotalMarks();

}
//--- friend functions end here ---//





int main(void)
{
	int n;

	ofstream fout;
	ifstream fin;

	cout<<"enter number of students: ";
	cin>>n;

	Student*std;
	std=new Student[n];

	cout<<"\n\nenter student details:\n";

	fout.open("StuDetails.txt", ios::app);

	for(int i=0; i<n; i++)
	{
		cout<<"\n\n\n[ Student "<<i+1<<" ]\n";
		std[i].details();
	}

	cout<<"\n\nenter the insemester and endsemester marks of the students:\n\n";

	for(int i=0; i<n; i++)
	{
		cout<<"\n\n\n[ Student "<<i+1<<" ]\n";
		std[i].InSemestermark();
		std[i].EndSemestermark();
	}


	/* calculating the marks of each students*/
	for(int i=0; i<n; i++)
	{
		totalMarks(std[i]);
	}


	//--- Result Declaration ---//
	cout<<"\n\nTHEORY RESULTS:\n\n";
	for(int i=0; i<n; i++)
	{
		std[i].TheoryExamResults();
	}

	cout<<"\n\nLABORATORY RESULTS:\n\n";
	for(int i=0; i<n; i++)
	{
		std[i].LaboratoryExamResults();
	}


	/* -- writing the results to a file(text file) -- */
	for(int i=0; i<n; i++)
	{
		fout.write((char*)&std[i], sizeof(std[i]));
		fout.close();
		std[i].writeFile();
	}


	//----freeing up space----//
	for(int i=0; i<n; i++)
	{
		std[i].terminate();
	}
	delete std;

	return 0;
}