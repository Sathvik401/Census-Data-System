#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iomanip>
#include<iostream>

#define censusfile "census.txt"
#define delfile "cendel.txt"
#define recsize 50
#define max 11

using namespace std;

fstream file;
char buffer[60],uip;
char keys[50][11];

class census
{
	public:
		char uid[6],name[20],age[5],gender[7],contact[11],address[15];
		void initial();
		int read();
		void pack();
		int getHash(char key[]);
		void display();
		void unpack();
		int search(char skey[]);
		void dispRec(int addr);
		void delRec(int addr);
		void modify(int addr);
		void reset();
};

void census::initial()
{
	int i;
	char dummy[recsize],  next;
	char check[6];
	file.open(censusfile, ios::in);
	if(!file)
	{
		cout<<"\nUnable to Open the File!!";
		getch();
		exit(1);
	}
	for(i=0; i<max; i++)
		strcpy(keys[i],"NULL");
	for(i=0; i<max; i++)
	{	
		file.seekg(i*(recsize),ios::beg);
		int f=file.tellg();
		file.getline(check, recsize, '|');
		if(strcmp(check,"###############################################") != 0)
			strcpy(keys[i],check);		
		file.getline(dummy, recsize, '\n');
	}
	file.close();
}

int census::read()
{	
	char ch;
	int flag = 0,x;
	cout<<"Enter the uid:"<<endl;
	scanf("%s",uid);
	while(search(uid) >= 0)
	{
		cout<<"\nThe ID already exists !!"<<endl;
		cout<<"Enter a unique id: ";
		scanf("%s",uid);
	}
	cout<<"Enter the name:"<<endl;
	scanf("%s",name);
    cout<<"Enter the age:"<<endl;
    scanf("%s",age);
    cout<<"Enter the gender:"<<endl;
    scanf("%s",gender);
	cout<<"Enter the contact number"<<endl;
	scanf("%s",contact);
	cout<<"Enter the address:"<<endl;
    scanf("%s",address);
	
	system("cls");
	cout<<"The provided details are as below:"<<endl;
	cout<<"Unique ID: "<<uid<<endl;
	cout<<"Name: "<<name<<endl;
    cout<<"Age: "<<age<<endl;
    cout<<"Gender: "<<gender<<endl;
	cout<<"Contact Number: "<<contact<<endl;
	cout<<"Address: "<<address<<endl;
	
	cout<<endl<<"Kindly confirm on the details (Y/N)"<<endl;
	cin>>ch;
	if(ch == 'Y'|| ch == 'y')
	{
		flag = 1;
		cout<<"Details uploaded successfully :)"<<endl;
		cout<<"Press any key to continue"<<endl;
        getch();
		pack();
		return flag;
	}
	else
	{
		cout<<"Details not uploaded !!"<<endl;
		cout<<"Press any key to continue"<<endl;
        getch();
		return flag;
	}
}


void census::pack()
{
	int addr;
	addr = getHash(uid);
	while(strcmp(keys[addr], "NULL") != 0)
	{
		addr++;
		if(addr == max)
		{
			addr = 0;
		}
		if(addr == getHash(uid))
		{
			cout<<"\nOverflow of Data!!";
			return;
		}
	}
	strcpy(keys[addr],uid);
	strcpy(buffer, uid);
	strcat(buffer,"|");
	strcat(buffer, name);
	strcat(buffer,"|");
	strcat(buffer, age);
	strcat(buffer,"|");
	strcat(buffer, gender);
	strcat(buffer,"|");
	strcat(buffer, contact);
	strcat(buffer,"|");
	strcat(buffer, address);
	strcat(buffer,"|");
	file.open(censusfile);
	if(!file)
	{
		cout<<"\nUnable to Open the File!!";
		exit(1);
	}
	file.seekg(addr*recsize, ios::beg);
	file.fill('*');
	file<<setiosflags(ios::left)<<setw(recsize-2)<<buffer<<endl;
	file.close();
}

int census::getHash(char key[])
{
	int i=0,sum=0;
	while(key[i]!='\0')
	{
		sum=sum+key[i]-48;
		i++;
	}
	return sum % max;
}

void census::display()
{
	int i, x;
	char dummy[recsize],check[recsize];
	cout<<setw(10)<<"Unique ID"<<setw(20)<<"Name"<<setw(20)<<"Age"<<setw(20)<<"Gender"<<setw(20)<<"Contact No."<<setw(20)<<"Address"<<endl;
	file.open(censusfile, ios::in);
	if(!file)
	{
		cout<<"\nUnable to Open the File";
		exit(1);
	}	
	for(i=0; i<max; i++)
	{
		file.seekg(i*(recsize),ios::beg);
		int f=file.tellg();
		file.getline(check, recsize, '|');
		if(strcmp(check,"###############################################") != 0)
		{
			strcpy(uid,check);
			file.getline(name, 20, '|');
			file.getline(age, 5, '|');
			file.getline(gender, 7, '|');
			file.getline(contact, 11, '|');
			file.getline(address,15, '|');
			cout<<setw(10)<<uid<<setw(20)<<name<<setw(20)<<age<<setw(20)<<gender<<setw(20)<<contact<<setw(20)<<address<<endl;
		}
	}
	cout<<"Press any key to continue"<<endl;
    getch();
	file.close();
}

int census::search(char skey[6])
{
	int addr, i=0, flag=0;
	addr = getHash(skey);
	i = addr;
	do
	{
		if(strcmp(keys[i],skey) == 0)
		{
			flag = 1;
			return i;
		}
		i++;
		if(i == max)
			i=0;
		if(keys[i] == "NULL")
			break;
	}while(i != addr);
	return -1;
}

void census::dispRec(int addr)
{
	int x;
	char ch;
	file.open(censusfile);
	if(!file)
	{
		cout<<"\nUnable to Open the File!!";
		exit(1);
	}
	file.seekg(addr*(recsize),ios::beg);
	int f=file.tellg();
	file.getline(uid, 6, '|');
	file.getline(name, 20, '|');
    file.getline(age, 5, '|');
    file.getline(gender, 7, '|');
	file.getline(contact, 11, '|');
	file.getline(address, 15, '|');
	cout<<"Unique ID:"<<uid<<endl;
	cout<<"Name: "<<name<<endl;
    cout<<"Age: "<<age<<endl;
    cout<<"Gender: "<<gender<<endl;
	cout<<"Contact Number: "<<contact<<endl;
	cout<<"Address: "<<address<<endl;
	file.close();
}

void census::delRec(int addr)
{
	int j;
	file.open(censusfile);
	if(!file)
	{
		cout<<"\nUnable to Open the File!!";
		exit(1);
	}
	file.seekp(addr*(recsize),ios::beg);
	for(j=0;j<recsize-3;j++)
		file<<"#";
	file<<"|";
	file.close();
	strcpy(keys[addr], "NULL");
}

void census::reset()
{
	int i,j;
	for(i=0; i<max; i++)
		strcpy(keys[i],"NULL");
	
	file.open(censusfile);
	if(!file)
	{
		cout<<"\nUnable to open the file!!";
		exit(1);
	}
		
	for(i=0;i<max;i++)
	{
		file.seekp(i*(recsize),ios::beg);
		for(j=0;j<recsize-3;j++)
			file<<"#";
		file<<"|";
		file<<"\n";
	}
	cout<<"Empty file created!"<<endl;
	cout<<"Press any key to continue";
    getch();
	file.close();
}

int main()
{
	census c;
	c.initial();
	int ch, addr,flag;
	char ex, skey[6],dch;
	for(;;)
	{
		system("cls");
		cout<<"============== CENSUS DATA SYSTEM =============="<<endl;
		cout<<"1. Enter a new record.\n2. Display all the records.\n3. Search for a record.\n4. Modify an existing record.\n5. Delete a record.\n6. Exit the Program.\n7. Reset. \n";
		cout<<"Enter your Choice: ";
		cin>>ch;
		
		switch(ch)
		{
			case 1: cout<<"\nEnter the person details"<<endl;
			        flag = c.read();
					break;
				
			case 2: c.display();
					break;
					
			case 3: cout<<"\nEnter the Unique ID: ";
					cin>>skey;
					addr = c.search(skey);
					if(addr == -1)
					{
						cout<<"\nRecord not found :("<<endl;
                        cout<<"Please enter valid unique id !!"<<endl;
						cout<<"Press any key to continue"<<endl;
						getch();
					}
					else
					{
						cout<<"\nRecord Found :)\n";
						c.dispRec(addr);
						cout<<"Press any key to continue"<<endl;
						getch();
					}
					break;
					
			case 4: cout<<"\nEnter the Unique ID to modify: ";
					cin>>skey;
					addr = c.search(skey);
					if(addr == -1)
					{
						cout<<"\nRecord not found :("<<endl;
                        cout<<"Please enter valid unique id !!"<<endl;
						cout<<"Press any key to continue"<<endl;
						getch();
					}
					else
					{
						c.dispRec(addr);
						c.delRec(addr);
						cout<<"\nPlease enter the details to be modified:"<<endl;
						flag=c.read();
						if(flag == 1) {
							cout<<"\nRecord Updation Scccessful :)"<<endl;
						}
						else {
							cout<<"\nNo record updated.."<<endl;
						}
						cout<<"Press any key to continue"<<endl;
						getch();
					}
					break;
					
			case 5: cout<<"\nEnter the Unique ID to delete: ";
					cin>>skey;
					addr = c.search(skey);
					if(addr == -1)
					{
						cout<<"\nRecord not found :("<<endl;
                        cout<<"Please enter valid unique id !!"<<endl;
						cout<<"Press any key to continue"<<endl;
						getch();
					}
					else
					{
						c.dispRec(addr);
						cout<<endl<<"The above record will be deleted permanently. Do you confirm? (Y/N)"<<endl;
	                    cin>>dch;
	                    if(dch == 'Y'|| dch == 'y')
	                    {
							c.delRec(addr);
							cout<<endl<<"\nRecord Deletion Scccessful :)"<<endl;
	                    }
	                    else
						{
							cout<<"Record deletion unsuccessful !!"<<endl;
	                    }
						cout<<"Press any key to continue....";
	                    getch();						
					}
					break;
				
			case 6:	exit(0);
					break;
			
			case 7:	c.reset();
					break;
		}
	}	
	return 0;
}
