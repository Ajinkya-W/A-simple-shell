/*INCLUDING REQUIRED HEADER FILES*/
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<fstream>
#include<fcntl.h>
#include <time.h>
using namespace std;

#include"list.h"
LinkedList mylist;
LinkedList mystack;


int main(void)
{
	/*FOR DILUSIONING EFFECT OF NEW TERMINAL*/
	cout<<"\e[1;1H\e[2J";
	cout<<"-----------------------------Welcome to Toy Shell-----------------------------";	
	cout<<endl;
	char* path = new char[1000];

	while(1)
	{
		cout<<endl<<"Execute>>> $ ";
		char *parameter[20],*argv[19],p='a';
		string args,str[20];
		char buffer[50];
		int i = 0,argc=0,j=0,fd1=0,fd2=0;
		int n=50;
		
		/*TAKIING INPUT*/
		while(p!='\n'){
			cin>>noskipws>>p;			//for not skipping whitespaces while taking input
			args += p;					//for complete string info
				
			if(p!=' ' && p!='\n')		//checking character for space and newline
			{
				str[i] += p;			//adding char by char 'p' to string str[]
			}
			else
			{							//once whitespace reached add it as a parameter
				argc++;
				parameter[i]=&str[i][0];
				i++;
			}	
		}
		/*PRINTING ENTERED ARGUMENTS
		for(i=0;i<argc;i++)
		{
			cout<<"parameter"<<i<<"-->";
			for(j=0;parameter[i][j]!='\0';j++)
				cout<<parameter[i][j];
			j=0;
			cout<<endl;
		}*/
	
		if(strcmp(parameter[0],"exit")==0)
		{
			/*GETTING NEW SCREEN DILUSION*/
			cout<<"\e[1;1H\e[2J";		
			exit(0);
		}
		/*------------------FILE CREATION-------------*/
		else if(strcmp(parameter[0],"create")==0)
		{
			creat(parameter[1],S_IRUSR | S_IWUSR );
			clock_t start=0, end=0;
			bool flag=0;
			int size;
			/*TO CREATE FILE SIZE AS 1MB*/
			if(strcmp(parameter[2],"1mb")==0)
				size=1000*1000;
			/*TO CREATE FILE SIZE AS 1KB*/
			else if(strcmp(parameter[2],"1kb")==0)
				size=1000;
			/*TO CREATE FILE SIZE OF SIZE 1B*/
			else if(strcmp(parameter[2],"1b")==0)
				size=1;
			/*IF ANY OTHER WRONG INPUT IS GIVEN WITH CREATE COMMAND*/
			else
			{
				cout<<"Wrong size in 2nd argument"<<endl;
				flag=1;
			}
			/*COPYING THE FILE & TIMING IT*/
			if(flag==0)
			{
				truncate(parameter[1],size);
				start = clock();
				{
					fd1 =open(parameter[1], O_RDONLY);
					fd2=open(parameter[3], O_CREAT | O_WRONLY | O_EXCL , 0700);

					/*CHECKING FOR ERRORS IN FILE DESCRIPTORS*/
					if(fd1 == -1 || fd2 ==-1)
						perror("error with the files descriptors");

					while(1)
					{
						n=read(fd1, buffer, 50);
						//cout<<"n="<<n<<"\n";

						if(write(fd2, buffer, n)!=n)
						{	
							perror("problem in writing");
							break;
						}
						if(n==-1)
						{
							perror("problem in reading");
							break;
						}
						else if(n<50)
							break;
					}
					
					close(fd2);
				}
				end = clock();
				double duration_sec = double(end-start)/CLOCKS_PER_SEC;
				/*IF ANY ERROR DOESN'T OCCUR*/	
				cout<<"File Successfully Copied in :"<<duration_sec*1000<<"ms"<<endl;
			}	
		}
		/*------------------COPY FUNCTION-------------*/
		else if(strcmp(parameter[0],"copy")==0)
		{
			fd1 =open(parameter[1], O_RDONLY);
			fd2=open(parameter[2], O_CREAT | O_WRONLY | O_EXCL , 0700);

			/*CHECKING FOR ERRORS IN FILE DESCRIPTORS*/
			if(fd1 == -1 || fd2 ==-1)
				perror("??error with the files descriptors");

			while(1)
			{
				n=read(fd1, buffer, 50);
				//cout<<"n="<<n<<"\n";

				if(write(fd2, buffer, n)!=n)
				{	
					perror("??problem in writing");
					break;
				}
				if(n==-1)
				{
					perror("??problem in reading");
					break;
				}
				else if(n<50)
					break;
			}
			close(fd2);

			if(remove(parameter[1])==0)
				cout<<"Copied Successfully!";
			else
				cout<<"??error in copying";
		}
		/*------------CHANGE DIRECTORY FUNCTION-------------*/
		else if(strcmp(parameter[0],"cd")==0)
		{
			char* path = new char[1000];
			int k = chdir(parameter[1]);
		
			if (k!=0)
				printf("error while changing the directory");
			else
			{
				path = getcwd(path,1000);
				cout<<"Current working dir: "<<path<<"\n";
			}
		}
		/*------------------PUSHD FUNCTION-------------*/
		else if(strcmp(parameter[0],"pushd")==0)
		{		
			char* temp = new char[1000];
		 	temp = getcwd(temp,1000);
			int k = chdir(parameter[1]);
			if(k!=0)
				cout<<"error while changing the directory"<<endl;
			else
			{
				mystack.push(temp);
				cout<<"Current working dir: "<<getcwd(temp,1000)<<endl;
			}
		}
		/*------------------POPD FUNCTION-------------*/
		else if(strcmp(parameter[0],"popd")==0)
		{
			char* npath = new char[1000];
			if(mystack.empty())
				cout<<"error : stack is empty!!";
			else
			{
				npath = mystack.top();
				mystack.pop();
				chdir(npath);
				cout<<"Current working dir: "<<getcwd(npath,1000)<<endl;
			}
		}
		/*------------------DIRS FUNCTION-------------*/
		else if(strcmp(parameter[0],"dirs")==0)
		{
			if(!mystack.empty())
			{
				mystack.printList();
			}
			else 
				cout<<"stack is empty"<<endl;
		}
		/*----------------FOR PATH COMMAND------------*/
		else if(strcmp(parameter[0],"path")==0)
		{

			if(argc==1)
			{
				if(!mylist.empty())
					mylist.printList();
				else cout<<"path list is empty"<<endl;
			}
			
			else if(strcmp(parameter[1],"+")==0)
			{
				mylist.push(parameter[2]);
			}
		
			else if(strcmp(parameter[1],"-")==0)
				mylist.remove(parameter[2]);
			
			else
				cout<<"syntax error";	

		}
		
		else if(strcmp(parameter[0],"pwd")==0)
		{
			char* path = new char[1000];
			path = getcwd(path,1000);
			cout<<"Current working dir: "<<path<<"\n";
		}
	
		else
		{	/*CHILD PROCESS BODY STARTS*/
			if(fork()==0)
			{

				int e=0;
				for(i=1;i<argc;i++)
				{
					argv[i]=parameter[i];
				}

				argv[i]=NULL;
				
				// searching in the current directory
				char* currpath = new char[1000];
				currpath = getcwd(path,1000);
				currpath = strcat(currpath,"/");
				char* currcommand = strcat(currpath,parameter[0]);
				argv[0] = currcommand;
				execvp(currcommand,argv);

				if(mylist.empty())
				{
					cout<<"No path is added."<<endl;
					exit(0);
				}
				else
				{
					for(int i=0;i<mylist.size();i++)
					{
						argv[0]=strcat(mylist.get(i),parameter[0]);
						e=execvp(argv[0],argv);
					}
					if(e==-1)
					{	
						cout<<"No proper path for "<<parameter[0]<<" command was found."<<endl;
						exit(0);
					}
				}
		
			}
			/*PARENT THREAD BODY STARTS*/
			else
			{
					wait(NULL);
			} 
		}
	}
return 0;
}
