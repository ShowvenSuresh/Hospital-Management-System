#include<iostream>
#include<fstream>
#include<iomanip>
#include<ctime>
#include<string>
#include<bits/stdc++.h>
# define size 500
using namespace std;

struct records
{
	string id,name,ic,address,num,dob,email,department;//this will be used for both doctor and paitient
	string date,time,totfee,paymentstat;//records that will be used in the invoice recoeds and appoinment scheduling parts as well
};
int login();
void billpay(records patient[], int);
void doctor();
void patients(records patient[],int);
void appointments(records patient[],int);

main()
{
	int log,option; 						//log = to determine if the log in was successfull, option is to choose the among the choices in the dashboard
	ofstream write;							//poitner to read and write to file
	ifstream read;
	struct records patient[size];
	int countp=0;							//countitng the number of record,p=patient.
	
	log = login();
		if(log == 1)
		{
			while(option!=5)
			{
				system("CLS");
				cout<<"\t\t\t    HOSPITAL MANAGEMENT SYSTEM"<<endl;
				cout<<"******************************************************************************"<<endl;
				cout<<"\t\t\t\tDashboard"<<endl;
				cout<<"******************************************************************************"<<endl;
				cout<<"\t\t\t1-->Doctor Management"<<endl;
				cout<<"\t\t\t2-->Patient Management"<<endl;
				cout<<"\t\t\t3-->Appointment Sheduling"<<endl;
				cout<<"\t\t\t4-->Billing and Payments"<<endl;
				cout<<"\t\t\t5-->Exit"<<endl;
				cout<<"=============================================================================="<<endl;
				do
				{
					cout<<"Please enter your option :";
					cin>>option;
					if(option<1 || option>5)
						cout<<"\a!!Invalid option!!"<<endl;
				}while(option<1 || option>5);
				
				read.open("patientInfo.txt");
					if (read.fail())
						cout<<"fail to read file"<<endl;
					while(!read.eof())
					{
						getline(read,patient[countp].name);
						getline(read,patient[countp].id);
						getline(read,patient[countp].ic);
						getline(read,patient[countp].dob);
						getline(read,patient[countp].num);
						getline(read,patient[countp].email);
						getline(read,patient[countp].address);
						countp++;
					}
				read.close();
				
				switch(option)
				{
					case 1:
						{
							doctor();
							break;
						}
					case 2:
						{
							patients(patient,countp);
							break;
						}
					case 3:
						{
							appointments(patient,countp);
							break;
						}
					case 4 :
						{
							billpay(patient,countp);
							break;
						}
				}
			}
		}
	else 
		{
			cout  << "Thank you for using the system"<<endl;
		}
	
}


int login()//For the admin to log in
{
	ofstream write;
	ifstream read;
	string username = "Admin";						//Username that is registered in the system
	string password ;					//Password that is registered in the system
	string iusername; 								// for users to input their username
	string ipassword;								//For users to input their password
	char option;
	int log;
	
	read.open("password.txt");
		getline(read,password);
	read.close();
	
	cout<<"*************************************************************************************"<<endl;
	cout<<"\t\t\t**Hospital Management system**"<<endl;
	cout<<"*************************************************************************************"<<endl;
	do											//Prompt users to enter the username. This loop will run until the user inputs the right username
	{
		cout<< "Username : ";
		getline (cin,iusername);
		
		if (iusername != username)
		{
			cout<<"-------------------------------------------------------------------------------------"<<endl;
			cout<<"\a!!Invalid username please enter again!!"<<endl;
			cout<<"-------------------------------------------------------------------------------------"<<endl;
		}
	}while (iusername != username);
	
	
	for (int i=3; i>=1; i--)//Prompts users to enter their password
	{                      //Users are only given 3 chances to to enter the password, if it is incorrect they have to change it. 
		int k = i-1;
		cout<< "Password : ";
		getline(cin,ipassword);
		
		if (ipassword == password)//If their password is correct between the number of attemps then they can proceed
			break;
		else//if the password is incorrect then the loop continues untill i>=1
		{
			cout<<"-------------------------------------------------------------------------------------"<<endl;
			cout<< "\a!!Incorrect password!!\n!!You have "<<k<<" attempts left!!"<<endl;
			cout<<"-------------------------------------------------------------------------------------"<<endl;
			cout<<"Do you wish to retry or change your password \nTo change password press 1,if no press any button : ";//user can choose if they want to proceed or if they want to re-attempt the password 
			cin>>option;
			cin.ignore();
		cout<<"-------------------------------------------------------------------------------------"<<endl;
			if(option=='1')
				goto cng_pass;//ditrectly goes to the change password part
		}
	}
	
	
	if(ipassword != password)
	{
		cout<<"\n!!The number of attemps you can input your password has been exceed!!"<<endl;
		cout<<"You are required to change the password"<<endl;
		
		system ("PAUSE");
		cng_pass://change password part
		while (ipassword != password)
		{
			system("CLS");
			cout<<"*************************************************************************************"<<endl;
			cout<<"\t\tChange your password"<<endl;
			do
			{
				cout<<"*************************************************************************************"<<endl;
				cout << "New password ( MAKE SURE THAT THE PASSWORD HAS 9 CHARACTERS ) :";//user can input ne passwordd
				getline(cin,ipassword);
					
				if(ipassword.length() == 9) //password has to be nine characters long
					break;
				else
				{
				cout<<"-------------------------------------------------------------------------------------"<<endl;
					cout<<"\aPassword does not meet the 9 characters criteria\nPlease renter"<<endl;
				}
			}while(ipassword.length() != 9);
				
			password= ipassword;
				
			cout<<"Please re-enter your new password :"; //user re enters the new password to ensure that they got it right and the login to the system
			getline(cin,ipassword);
				
			if(ipassword != password)
			{
				cout << "\aEntered password does not match. \nPlease try again"<<endl;
				system ("PAUSE");
			}
			else 
			{
				write.open("password.txt");
					write<<password;
				write.close();
				cout<<"\n=============================================================================="<<endl;
				cout<<"Your password has been changed\nYou have successfully logged in"<<endl;
				cout<<"=============================================================================="<<endl;

			}
		}
		
	}
	else
	{
		cout<<"\n\n\n=============================================================================="<<endl;
		cout<< "Congratulations You have successfully logged in"<<endl;
		cout<<"=============================================================================="<<endl;
	}
	
	system ("PAUSE");
	
	if(ipassword == password)
		log = 1;//when log =1 th elog in was sucessfull
	else 
		log =0;//when log =0 the login was a failure
	
	return log;	
}

void billpay(records patient[],int countp)
{
	ofstream write;
	ifstream read;
	struct records invoice[size],history[size];	
	int counti=0,counth=0,i;							//for loop counter and countitng the number of record, i=invoice d = doctor h=history
	string pid,iid;										//for user input
	int s = 0,j;										//to determine the number of item needed in the invoice and the counter for all the for loops
	double totfee = 0.0;								// an accumalator to to count the total number of items
	char o;												//Option if the user wishes to save and continue
	int opt;											//optine to choose from the menu from this funtion
	int c,x;											//c is to choose what to do in this section and x is for holding the index value
	time_t current= time(0);							//this will capture the current time
	string datetime = ctime(&current);					//this will convert it to a string to be displayed

	do
	{
		system("CLS");	
		cout<<"***********************************************************************"<<endl;
		cout<<"\t\t\tBilling and Payments"<<endl;
		cout<<"***********************************************************************"<<endl;
		cout<<"\t\t1-->Generate an invoice"<<endl;
		cout<<"\t\t2-->View invoice records"<<endl;
		cout<<"\t\t3-->View payment history"<<endl;
		cout<<"\t\t4-->Return to dashboard"<<endl;
		cout<<"======================================================================="<<endl;
		do
		{
			cout<<"Please enter your option :";
			cin>>opt;
			if(opt<1 || opt>4)
				cout<<"\a!!Invalid option!!"<<endl;
		}while(opt<1 || opt>4);							// If an invalid option is chosen the user has to redo the option section
		
		counti=0;
		counth=0;
		read.open("invoicerec.txt");
		if(read.fail())
			cout<<"fail to read file"<<endl;
		while(!read.eof())
		{
			getline(read,invoice[counti].id);
			getline(read,invoice[counti].name);
			getline(read,invoice[counti].totfee);
			getline(read,invoice[counti].paymentstat);
			getline(read,invoice[counti].date);
			counti++;
		}
		read.close();
			
		switch(opt)
		{
			case 1://to genreate an invoice
				{
					do
					{
						
						system("CLS");
						cout<<"***********************************************************************"<<endl;
						cout<<"\t\tGENERATE AN INVOICE"<<endl;
						cout<<"***********************************************************************"<<endl;
						cin.ignore();
						do
						{
							cout<<"Invoice ID :";//propmt the user to enter a new and unique invoices  id  by checking the invoice records
							getline(cin,iid);
							for(j=0;j<counti;j++)
							{
								if(iid==invoice[j].id)
								{
									cout<<"Invoice id already exists"<<endl;
									break;
								}
							}
						}while(iid==invoice[j].id);// this loop wil run unti the invoice id entered is unique
						
						do
						{
							cout<<"Patient ID :";
							getline(cin,pid);//this section will capture the patient details for the invoice through the patient id
							i=0;
							for(i=0 ;i<countp-1;i++)
							{
								if(pid==patient[i].id)
								{
									break;
								}
							}
							if(i==countp-1)
							{
								cout<<"The patient id does not exist\nPlease re-enter"<<endl;
							}
							else
								cout<<"Patient details captured\n"<<endl;
						}while(i==countp-1);//if the user enters a do while loop it is because they entered a non existing patient id.
						
						
						
						cout<< "How many item would you like to enter :";
						cin>> s;
						cin.ignore();
						cout<<endl;//Prompt the user to enter the number of items that will be present in the invoice
						
						string service[s];	//For the user to input the sevices provided and the charge for each service
						double fee [s];
							 
						for(j=0; j<s; j++)//promts the user to input the each item needed in the invoice ....the loop will run based the user input ealier
						{
						 	cout<< "Item ["<<j+1<<"] :"<<endl;
						 	cout<< "Service Provided :";
						 	getline(cin,service[j]);
						 	cout<< "Charge for the service :RM ";
						 	cin>>fee[j];
						 	cin.ignore();
						 	totfee+=fee[j];//accumilating the total fee 
						 	cout<<"\n";
						}
						
						time_t current= time(0);//this will capture the current time
						string datetime = ctime(&current);//this will convert it to a string to be displayed
						
						system("CLS");// Clears the screen to display the entire invoice
						cout<<"***********************************************************************"<<endl;
						cout<<"\t\t\tInvoice"<<endl;
						cout<<"***********************************************************************"<<endl;
						cout<<"invoice ID             :"<<iid<<endl;
						cout<<"Patient ID             :"<<patient[i].id<<endl;
						cout<<"Patient Name           :"<<patient[i].name<<endl;
						cout<<"Patient IC             :"<<patient[i].ic<<endl;
						cout<<"Patient Address        :"<<patient[i].address<<endl;
						cout<<"Patient Phone Number   :"<<patient[i].num<<endl;
						cout<<"Patient e-mail address :"<<patient[i].email<<"\n"<<endl;
						cout<<"_________________________________________________________________________"<<endl;
						cout<<"|"<<setw(4)<<left<<"Item"<<setw(40)<<left<<"|Sevice Provided"<<setw(12)<<left<<" |Fee"<<"\t\t|"<<endl;
					    cout<<"_________________________________________________________________________"<<endl;
						    
					    cout<<fixed<<setprecision(2);
					    for(j=0;j<s;j++)//This loop will present all the items in the form of a table
					    {
					    	cout<<"|"<<setw(4)<<left<<j+1<<"|"<<setw(40)<<left<<service[j]<<"|RM "<<setw(22)<<left<<fee[j]<<"|"<<endl;
					    	cout<<"_________________________________________________________________________"<<endl;
						}
						cout<<endl;
						cout<<"Payment Due                                      :RM "<<totfee<<endl;
						cout<<"\n\tThis invoice was generated on "<<datetime<<endl;
						
						cout<<"Do you wish to save this invoice "<<endl;
						cout<<"If you do press 1, If you dont press any button :";
						cin>> o;
						
						if( o =='1')//This prints the invoice to a text file and adds it to the invoice record.
						{
							write.open ("invoice "+pid+".txt");// the invoice file will be save acording to the patient id entered
								
								write<<"***********************************************************************"<<endl;
								write<<"\t\t\tInvoice"<<endl;
								write<<"***********************************************************************"<<endl;
								write<<"Patient ID             :"<<patient[i].id<<endl;
								write<<"Patient Name           :"<<patient[i].name<<endl;
								write<<"Patient IC             :"<<patient[i].ic<<endl;
								write<<"Patient Address        :"<<patient[i].address<<endl;
								write<<"Patient Phone Number   :"<<patient[i].num<<endl;
								write<<"Patient e-mail address :"<<patient[i].email<<"\n"<<endl;
								write<<"_________________________________________________________________________"<<endl;
								write<<"|"<<setw(4)<<left<<"Item"<<setw(40)<<left<<"|Sevice Provided"<<setw(12)<<left<<" |Fee"<<"\t\t|"<<endl;
							    write<<"_________________________________________________________________________"<<endl;
							    
							    write<<fixed<<setprecision(2);
							    for(j=0;j<s;j++)
							    {
							    	write<<"|"<<setw(4)<<left<<j+1<<"|"<<setw(40)<<left<<service[j]<<setw(12)<<left<<"|RM "<<fee[j]<<"\t|"<<endl;
							    	write<<"_________________________________________________________________________"<<endl;
								}
								write<<endl;
								write<<"Payment Due                                     :RM "<<totfee<<endl;
								write<<"\n\tThis invoice was generated on "<<datetime<<endl;
							
							write.close	();
							cout<< "\nSucessfully Saved"<<endl;
							cout<<"Invoice record updated"<<endl;
							
							write.open("invoicerec.txt",ios::app);//this will append the invoice records file with the following details
								write<<iid<<endl;
								write<<patient[i].name<<endl;
								write<<"RM"<<totfee<<endl;
								write<<"NOTPAID"<<endl;
								write<<datetime;	
							write.close();
							cout<<"\nDo you wish to generate another invoice "<<endl;//ask the user if they want to continue or not  
							cout<<"If you do press 1, If you dont press any button to back to the menu :";
							cin>> o;
						}
						else
						{
							cout<<"\nDo you wish to generate another invoice "<<endl;//to ask the user if they want to continue or not
							cout<<"If you do press 1, If you dont press any button to go back to menu : ";
							cin>> o;
						}
					}while (o == '1');

					break;
				}
			case 2:
				{
					do
					{
						system("CLS");//user can view all the invoice records
						cout<<"***********************************************************************"<<endl;
						cout<<"\t\t\tInvoice Records"<<endl;
						cout<<"***********************************************************************"<<endl;
						cout<<"\n_________________________________________________________________________________________________________________"<<endl;	
						cout<<"|"<<setw(4)<<left<<"No."<<setw(11)<<left<<"|Invoice ID"<<setw(30)<<left<<"|Inovice Date"<<setw(37)<<left<<"|Patient Name"<<setw(14)<<left<<"|Total Amount"<<setw(14)<<left<<"|Payment Status"<<"|"<<endl;
						cout<<"_________________________________________________________________________________________________________________"<<endl;
						for(j=0;j<counti-1;j++)
						{
							cout<<"|"<<setw(4)<<left<<j+1<<"|"<<setw(10)<<left<<invoice[j].id<<"|"<<setw(29)<<left<<invoice[j].date<<"|"<<setw(36)<<left<<invoice[j].name<<"|"<<setw(13)<<left<<invoice[j].totfee<<"|"<<setw(14)<<left<<invoice[j].paymentstat<<"|"<<endl;
							cout<<"_________________________________________________________________________________________________________________"<<endl;
						}
						cout<<"\nWhat would you like to do :"<<endl;// they have the option od deleting an invoice record or update the paymnet status of an invoice record
						cout<<"-----------------------------"<<endl;
						cout<<"1--> Update payment status"<<endl;
						cout<<"2--> Delete an invoice"<<endl;
						cout<<"3--> Return to menu"<<endl;
						cout<<"-----------------------------"<<endl;
						do
						{
							cout<<"Please enter your choice ~>";
							cin>>c;
							if(c<1 || c>3)
							cout<<"\a!!Invalid option!!"<<endl;
						}while(c<1 || c>3);
						
						switch(c)
						{
							case 1://to update payment status
								{
									system("CLS");
									cout<<"***********************************************************************"<<endl;
									cout<<"\t\tUpdate Payment status"<<endl;
									cout<<"***********************************************************************"<<endl;
									cin.ignore();
									cout<<"Enter an invoice id :";
									getline(cin,iid);
									for(j=0;j<counti;j++)
									{
										if(iid==invoice[j].id)
										{
											x=j;
											break;
										}
									}
									
									invoice[x].paymentstat = "PAID";
									
									cout<<"\n_________________________________________________________________________________________________________________"<<endl;
									cout<<"|"<<setw(4)<<left<<"No."<<setw(11)<<left<<"|Invoice ID"<<setw(30)<<left<<"|Inovice Date"<<setw(37)<<left<<"|Patient Name"<<setw(14)<<left<<"|Total Amount"<<setw(14)<<left<<"|Payment Status"<<"|"<<endl;
									cout<<"_________________________________________________________________________________________________________________"<<endl;
									for(j=0;j<counti-1;j++)
									{
										cout<<"|"<<setw(4)<<left<<j+1<<"|"<<setw(10)<<left<<invoice[j].id<<"|"<<setw(29)<<left<<invoice[j].date<<"|"<<setw(36)<<left<<invoice[j].name<<"|"<<setw(13)<<left<<invoice[j].totfee<<"|"<<setw(14)<<left<<invoice[j].paymentstat<<"|"<<endl;
										cout<<"_________________________________________________________________________________________________________________"<<endl;
									}
									
									write.open("invoicerec.txt");//this will overwrite the invoice records file with the new details
										for(j=0;j<counti-1;j++)
										{
											write<<invoice[j].id<<endl;
											write<<invoice[j].name<<endl;
											write<<invoice[j].totfee<<endl;
											write<<invoice[j].paymentstat<<endl;
											write<<invoice[j].date<<endl;	
										}
									write.close();
									
									cout<<"\nPayment Status Updated"<<endl;
									
									write.open("paymenthistory.txt",ios::app);//will append the payment history file 
										write<<invoice[x].id<<endl;
										write<<invoice[x].name<<endl;
										write<<invoice[x].totfee<<endl;
										write<<datetime;
									write.close();
									
									cout<<"\nPayment History updated"<<endl;
									cout<<"\nDo you wish to viewing and managing invoices "<<endl;//to ask the user if they want to continue or not
									cout<<"If you do press 1, If you dont press any button to go back to menu : ";
									cin>> o;
									break;
								}
							case 2://to delete an invoice records
								{
									system("CLS");
									cout<<"***********************************************************************"<<endl;
									cout<<"\t\t\tDelete an Invoice"<<endl;
									cout<<"***********************************************************************"<<endl;
									cin.ignore();
									cout<<"Enter the invoce id you wish to delete :";
									getline(cin,iid);
									for(j=0;j<counti;j++)
									{
										if(iid==invoice[j].id)
										{
											x=j;
											break;
										}
									}
									
									for(j=x;j<counti-1;j++)
									{
										invoice[j].id=invoice[j+1].id;
										invoice[j].date=invoice[j+1].date;
										invoice[j].name=invoice[j+1].name;
										invoice[j].totfee=invoice[j+1].totfee;
										invoice[j].paymentstat=invoice[j+1].paymentstat;
									}
									
									counti--;
									
									cout<<"\n_________________________________________________________________________________________________________________"<<endl;	
									cout<<"|"<<setw(4)<<left<<"No."<<setw(11)<<left<<"|Invoice ID"<<setw(30)<<left<<"|Inovice Date"<<setw(37)<<left<<"|Patient Name"<<setw(14)<<left<<"|Total Amount"<<setw(14)<<left<<"|Payment Status"<<"|"<<endl;
									cout<<"_________________________________________________________________________________________________________________"<<endl;
									for(j=0;j<counti-1;j++)
									{
										cout<<"|"<<setw(4)<<left<<j+1<<"|"<<setw(10)<<left<<invoice[j].id<<"|"<<setw(29)<<left<<invoice[j].date<<"|"<<setw(36)<<left<<invoice[j].name<<"|"<<setw(13)<<left<<invoice[j].totfee<<"|"<<setw(14)<<left<<invoice[j].paymentstat<<"|"<<endl;
										cout<<"_________________________________________________________________________________________________________________"<<endl;
									}
									
									write.open("invoicerec.txt");//this will append the invoice records file with the following details
										for(j=0;j<counti-1;j++)
										{
											write<<invoice[j].id<<endl;
											write<<invoice[j].name<<endl;
											write<<invoice[j].totfee<<endl;
											write<<invoice[j].paymentstat<<endl;
											write<<invoice[j].date<<endl;	
										}
									write.close();
									cout<<" Record Deleted"<<endl;
									cout<<"\nDo you wish to viewing and managing invoices "<<endl;//to ask the user if they want to continue or not
									cout<<"If you do press 1, If you dont press any button to go back to menu : ";
									cin>> o;
									break;
								}
							case 3 :// to return to menu
								{
									o='2';
									break;
								}
						}
						
						
					}while(o=='1');
					break;
				}
			case 3://to view payment history
				{
					do
					{
						system("CLS");
						cout<<"***********************************************************************"<<endl;
						cout<<"\t\tPayment History"<<endl;
						cout<<"***********************************************************************\n"<<endl;
						read.open("paymenthistory.txt");
							if (read.fail())
								cout<<"Payment history file does not exists"<<endl;
							counth=0;
							while(!read.eof())
							{
								getline(read,history[counth].id);
								getline(read,history[counth].name);
								getline(read,history[counth].totfee);
								getline(read,history[counth].date);
								counth++;
							}
						read.close();
						cout<<"__________________________________________________________________________________________________"<<endl;
						cout<<"|"<<setw(4)<<left<<"No."<<setw(11)<<left<<"|Invoice ID"<<setw(37)<<left<<"|Patient Name"<<setw(14)<<left<<"|Total Amount"<<setw(30)<<left<<"|Date Paid"<<"|"<<endl;
						cout<<"__________________________________________________________________________________________________"<<endl;
						 for(j=0;j<counth-1;j++)
						 {
						 	cout<<"|"<<setw(4)<<left<<j+1<<"|"<<setw(10)<<left<<history[j].id<<"|"<<setw(36)<<left<<history[j].name<<"|"<<setw(13)<<left<<history[j].totfee<<"|"<<setw(29)<<left<<history[j].date<<"|"<<endl;
						 	cout<<"__________________________________________________________________________________________________"<<endl;
						 }
						 
						cout<<"\nPress any button  except '1' to return to the main menu "<<endl;//to ask the user if they want to continue or not
						cin>> o;
					}while( o== '1');
					break;
				}
		}
	}while(opt!=4);
		
}

void doctor()
{
	//declare variable
	int select,rcounter,counter,nfound,delrecord;
	char end,vselect,aselect,dselect,mselect;
	string search,check;
	//declare pointer
	ifstream read;
	ofstream write;
	//declare structure
	struct records doctor[size];
	struct records buffer;
	
	do{
		//clear screen
		system("cls");
		//load doctor record
		read.open("DoctorInfo.txt");
		if (read.fail())
			cout<<"File not exist"<<endl;
		else
		{
			rcounter=0;
			while(!read.eof())
			{
				getline(read,doctor[rcounter].name);
				getline(read,doctor[rcounter].id);
				getline(read,doctor[rcounter].ic);
				getline(read,doctor[rcounter].department);
				getline(read,doctor[rcounter].dob);
				getline(read,doctor[rcounter].num);
				getline(read,doctor[rcounter].email);
				getline(read,doctor[rcounter].address);
				rcounter++;
			}
			//-1 for '\n'
			rcounter=rcounter-1;
			
			//cout<<rcounter<<endl;
		}
		read.close(); 
		
		//make selection use which function
		do{
			system("CLS");
			cout<<"***********************************************************************"<<endl;
			cout<<"\t\t\tDoctor management system"<<endl;
			cout<<"***********************************************************************"<<endl;
			cout<<"\t\t1-->View doctor records"<<endl;
			cout<<"\t\t2-->Add a new doctor"<<endl;
			cout<<"\t\t3-->Delete a doctor record"<<endl;
			cout<<"\t\t4-->Modify doctor records"<<endl;
			cout<<"\t\t5-->Return to Dashbord"<<endl;
			cout<<"======================================================================="<<endl;
			cout<<"Enter an option :";
			cin>>select;
			//invalid check
			if (select<1||select>5)
				cout<<"Invalid option,pls re-enter\a"<<endl<<endl;	
		}while(select<1||select>5);

		//to deference function
		switch (select)
		{
			//view record
			case 1:
				//clear screen
				system("cls"); 
				cout<<"***********************************************************************"<<endl;
				cout<<"\t\t View doctor records"<<endl;
				cout<<"***********************************************************************"<<endl;
				//display doctor record
				cout<<"_____________________________________________________________"<<endl;
				cout<<"|"<<left<<setw(30)<<"Name"<<left<<setw(29)<<"|Doctor ID"<<"|"<<endl;
				cout<<"_____________________________________________________________"<<endl;
				for(counter=0;counter<rcounter;counter++)
				{
					cout<<"|"<<left<<setw(30)<<doctor[counter].name<<"|"<<left<<setw(28)<<doctor[counter].id<<"|"<<endl;
					cout<<"_____________________________________________________________"<<endl;
				}
				cout<<endl;
				//view details
				cout<<"Enter 'y' to search and view record details"<<endl;
				cout<<"Press any other button to return to the menu."<<endl;
				cin>>vselect;
				if (vselect=='Y'||vselect=='y')
				{
					cout<<"Search record by name enter n"<<endl;
					cout<<"Search record by Doctor ID enter i"<<endl;
					cout<<"Enter other key to return to the menu"<<endl;
					cin>>vselect;
					//Search record by name
					if(vselect=='N'||vselect=='n')
					{
						//get name need to view details
						cout<<"Enter the name:";
						cin.ignore();
						getline(cin,search);
						nfound=1;
						//clear screen
						system("cls"); 
						cout<<"***********************************************************************"<<endl;
						cout<<"\t\t View doctor records"<<endl;
						cout<<"***********************************************************************\n"<<endl;
						for(counter=0;counter<rcounter;counter++)
						{
							check=doctor[counter].name;
							//convert to lower case,cant use strlwr because not char[]
							transform(search.begin(),search.end(),search.begin(),::tolower);
							transform(check.begin(),check.end(),check.begin(),::tolower);
							if (search==check)
							{
								cout<<"_______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"Name"<<"|"<<setw(30)<<left<<doctor[counter].name<<"|"<<endl;
								cout<<"_______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"Doctor ID"<<"|"<<setw(30)<<left<<doctor[counter].id<<"|"<<endl;
								cout<<"_______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"IC Number"<<"|"<<setw(30)<<left<<doctor[counter].ic<<"|"<<endl;
								cout<<"_______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"Department"<<"|"<<setw(30)<<left<<doctor[counter].department<<"|"<<endl;
								cout<<"_______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"Date of birth"<<"|"<<setw(30)<<left<<doctor[counter].dob<<"|"<<endl;
								cout<<"_______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"Phone number"<<"|"<<setw(30)<<left<<doctor[counter].num<<"|"<<endl;
								cout<<"_______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"Email"<<"|"<<setw(30)<<left<<doctor[counter].email<<"|"<<endl;
								cout<<"_______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"Address"<<"|"<<setw(30)<<left<<doctor[counter].address<<"|"<<endl;
								cout<<"_______________________________________________________________"<<endl;
								cout<<endl;
								nfound=0;
							}
						}
						if(nfound==1)
							cout<<"No record found"<<endl;
					}
					//Search record by Doctor ID
					if(vselect=='I'||vselect=='i')
					{
						//get ID need to view details
						cout<<"Enter the Doctor ID:";
						cin.ignore();
						getline(cin,search);
						nfound=1;
						//clear screen
						system("cls"); 
						cout<<"***********************************************************************"<<endl;
						cout<<"\t\t View doctor records"<<endl;
						cout<<"***********************************************************************\n"<<endl;
						for(counter=0;counter<rcounter;counter++)
						{
							check=doctor[counter].id;
							//convert to lower case,cant use strlwr because not char[]
							transform(search.begin(),search.end(),search.begin(),::tolower);
							transform(check.begin(),check.end(),check.begin(),::tolower);
							if (search==check)
							{
								cout<<"_______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"Name"<<"|"<<setw(30)<<left<<doctor[counter].name<<"|"<<endl;
								cout<<"_______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"Doctor ID"<<"|"<<setw(30)<<left<<doctor[counter].id<<"|"<<endl;
								cout<<"_______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"IC Number"<<"|"<<setw(30)<<left<<doctor[counter].ic<<"|"<<endl;
								cout<<"_______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"Department"<<"|"<<setw(30)<<left<<doctor[counter].department<<"|"<<endl;
								cout<<"_______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"Date of birth"<<"|"<<setw(30)<<left<<doctor[counter].dob<<"|"<<endl;
								cout<<"_______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"Phone number"<<"|"<<setw(30)<<left<<doctor[counter].num<<"|"<<endl;
								cout<<"_______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"Email"<<"|"<<setw(30)<<left<<doctor[counter].email<<"|"<<endl;
								cout<<"_______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"Address"<<"|"<<setw(30)<<left<<doctor[counter].address<<"|"<<endl;
								cout<<"_______________________________________________________________"<<endl;
								cout<<endl;
								nfound=0;
								break;
							}
						}
						if(nfound==1)
							cout<<"No record found"<<endl;
					}
				cout<<endl<<"Press any key to return home"<<endl;
				cin>>end;
				}				
				break;	
			//add record
			case 2:
				do{
					//clear screen
					system("cls"); 
					cout<<"***********************************************************************"<<endl;
					cout<<"\t\t Add a doctor"<<endl;
					cout<<"***********************************************************************\n"<<endl;
					//get record
					cin.ignore();
					cout<<left<<setw(30)<<"Name"<<":";
					getline(cin,buffer.name);
					
					do{
						cout<<left<<setw(30)<<"Doctor ID"<<":";
						getline(cin,buffer.id);
						//assign value and convert to lower case
						check=buffer.id;
						transform(check.begin(),check.end(),check.begin(),::tolower);
						for(counter=0;counter<rcounter;counter++)
						{
							//assign value and convert to lower case
							search=doctor[counter].id;
							transform(search.begin(),search.end(),search.begin(),::tolower);
							if(search==check)
							{
								cout<<"The Doctor ID is not unique,please RE-ENTER"<<endl;
								sleep(1);
								break;
							}
						}
					}while(search==check);
					
					do{

						cout<<left<<setw(30)<<"IC number"<<":";
						getline(cin,buffer.ic);
						//assign value and convert to lower case
						check=buffer.ic;
						transform(check.begin(),check.end(),check.begin(),::tolower);
						for(counter=0;counter<rcounter;counter++)
						{
							//assign value and convert to lower case
							search=doctor[counter].ic;
							transform(search.begin(),search.end(),search.begin(),::tolower);
							if(search==check)
							{
								cout<<"The IC Number is not unique,please RE-ENTER"<<endl;
								sleep(1);
								break;
							}
						}
					}while(search==check);
					
					cout<<left<<setw(30)<<"Department"<<":";
					getline(cin,buffer.department);
					cout<<left<<setw(30)<<"Date of birth"<<":";
					getline(cin,buffer.dob);
					cout<<left<<setw(30)<<"Phone number"<<":";
					getline(cin,buffer.num);
					cout<<left<<setw(30)<<"Email"<<":";
					getline(cin,buffer.email);
					cout<<left<<setw(30)<<"Address"<<":";
					getline(cin,buffer.address);
					
					//write record
					write.open("DoctorInfo.txt",ios::app);
					write<<buffer.name<<endl;
					write<<buffer.id<<endl;
					write<<buffer.ic<<endl;
					write<<buffer.department<<endl;
					write<<buffer.dob<<endl;
					write<<buffer.num<<endl;
					write<<buffer.email<<endl;
					write<<buffer.address<<endl;
					write.close();
					//load doctor record
					read.open("DoctorInfo.txt");
					if (read.fail())
						cout<<"File not exist"<<endl;
					else
					{
						rcounter=0;
						while(!read.eof())
						{
							getline(read,doctor[rcounter].name);
							getline(read,doctor[rcounter].id);
							getline(read,doctor[rcounter].ic);
							getline(read,doctor[rcounter].department);
							getline(read,doctor[rcounter].dob);
							getline(read,doctor[rcounter].num);
							getline(read,doctor[rcounter].email);
							getline(read,doctor[rcounter].address);
							rcounter++;
						}
						//-1 for '\n'
						rcounter=rcounter-1;
						
						//cout<<rcounter<<endl;
					}
					read.close(); 
					//ask for write more record?
					cout<<"\nRecord successfully added"<<endl;
					cout<<"Enter y to add more record, Press any other button to return to the menu"<<endl;
					cin>>aselect;
				}while(aselect=='Y'||aselect=='y');
				break;
			//delete record
			case 3:
				//clear screen
				system("cls"); 
				cout<<"***********************************************************************"<<endl;
				cout<<"\t\t Delete a doctor Record"<<endl;
				cout<<"***********************************************************************\n"<<endl;
				//display doctor record
				cout<<"_____________________________________________________________"<<endl;
				cout<<"|"<<left<<setw(30)<<"Name"<<left<<setw(29)<<"|Doctor ID"<<"|"<<endl;
				cout<<"_____________________________________________________________"<<endl;
				for(counter=0;counter<rcounter;counter++)
				{
					cout<<"|"<<left<<setw(30)<<doctor[counter].name<<"|"<<left<<setw(28)<<doctor[counter].id<<"|"<<endl;
					cout<<"_____________________________________________________________"<<endl;
				}
				cout<<endl;
				//get Doctor ID need to delete
				cout<<"Enter the Doctor ID:";
				cin.ignore();
				getline(cin,search);
				nfound=1;
				
				system("cls"); 
				cout<<"***********************************************************************"<<endl;
				cout<<"\t\t Delete a doctor Record"<<endl;
				cout<<"***********************************************************************\n"<<endl;
				for(counter=0;counter<rcounter;counter++)
				{
					check=doctor[counter].id;
					//convert to lower case,cant use strlwr because not char[]
					transform(search.begin(),search.end(),search.begin(),::tolower);
					transform(check.begin(),check.end(),check.begin(),::tolower);
					if (search==check)
					{
						cout<<"_______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"Name"<<"|"<<setw(30)<<left<<doctor[counter].name<<"|"<<endl;
						cout<<"_______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"Doctor ID"<<"|"<<setw(30)<<left<<doctor[counter].id<<"|"<<endl;
						cout<<"_______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"IC Number"<<"|"<<setw(30)<<left<<doctor[counter].ic<<"|"<<endl;
						cout<<"_______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"Department"<<"|"<<setw(30)<<left<<doctor[counter].department<<"|"<<endl;
						cout<<"_______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"Date of birth"<<"|"<<setw(30)<<left<<doctor[counter].dob<<"|"<<endl;
						cout<<"_______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"Phone number"<<"|"<<setw(30)<<left<<doctor[counter].num<<"|"<<endl;
						cout<<"_______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"Email"<<"|"<<setw(30)<<left<<doctor[counter].email<<"|"<<endl;
						cout<<"_______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"Address"<<"|"<<setw(30)<<left<<doctor[counter].address<<"|"<<endl;
						cout<<"_______________________________________________________________"<<endl;
						cout<<endl;
						nfound=0;
						break;
					}
				}
				if(nfound==1)
					cout<<"No record found"<<endl;
				else
				{
					//ask for last comform
					cout<<"Enter y to delete record"<<endl;
					cin>>dselect;
					//overwrite record
					if(dselect=='Y'||dselect=='y')
					{
						delrecord=counter;
						write.open("DoctorInfo.txt");
						if (write.fail())
							cout<<"File not exist"<<endl;
						for(counter=0;counter<rcounter;counter++)
						{
							if(delrecord!=counter)
							{
								write<<doctor[counter].name<<endl;
								write<<doctor[counter].id<<endl;
								write<<doctor[counter].ic<<endl;
								write<<doctor[counter].department<<endl;
								write<<doctor[counter].dob<<endl;
								write<<doctor[counter].num<<endl;
								write<<doctor[counter].email<<endl;
								write<<doctor[counter].address<<endl;
							}
						}
						write.close();
						cout<<"Record successfully deleted"<<endl;
					}
				}
				cout<<endl<<"Press any key to return home"<<endl;
				cin>>end;					
				break;
			//modify record
			case 4:
				//clear screen
				system("cls"); 
				cout<<"***********************************************************************"<<endl;
				cout<<"\t\t Modify a doctor Record"<<endl;
				cout<<"***********************************************************************\n"<<endl;
				//display doctor record
				cout<<"_____________________________________________________________"<<endl;
				cout<<"|"<<left<<setw(30)<<"Name"<<left<<setw(29)<<"|Doctor ID"<<"|"<<endl;
				cout<<"_____________________________________________________________"<<endl;
				for(counter=0;counter<rcounter;counter++)
				{
					cout<<"|"<<left<<setw(30)<<doctor[counter].name<<"|"<<left<<setw(28)<<doctor[counter].id<<"|"<<endl;
					cout<<"_____________________________________________________________"<<endl;
				}
				cout<<endl;
				//get Doctor ID need to modify
				cout<<"Enter the Doctor ID:";
				cin.ignore();
				getline(cin,search);
				nfound=1;
				//search same record
				for(counter=0;counter<rcounter;counter++)
				{
					check=doctor[counter].id;
					//convert to lower case,cant use strlwr because not char[]
					transform(search.begin(),search.end(),search.begin(),::tolower);
					transform(check.begin(),check.end(),check.begin(),::tolower);
					if (search==check)
					{
						cout<<"\nCurrent Information of the doctor"<<endl;
						cout<<"_______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"Name"<<"|"<<setw(30)<<left<<doctor[counter].name<<"|"<<endl;
						cout<<"_______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"Doctor ID"<<"|"<<setw(30)<<left<<doctor[counter].id<<"|"<<endl;
						cout<<"_______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"IC Number"<<"|"<<setw(30)<<left<<doctor[counter].ic<<"|"<<endl;
						cout<<"_______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"Department"<<"|"<<setw(30)<<left<<doctor[counter].department<<"|"<<endl;
						cout<<"_______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"Date of birth"<<"|"<<setw(30)<<left<<doctor[counter].dob<<"|"<<endl;
						cout<<"_______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"Phone number"<<"|"<<setw(30)<<left<<doctor[counter].num<<"|"<<endl;
						cout<<"_______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"Email"<<"|"<<setw(30)<<left<<doctor[counter].email<<"|"<<endl;
						cout<<"_______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"Address"<<"|"<<setw(30)<<left<<doctor[counter].address<<"|"<<endl;
						cout<<"_______________________________________________________________"<<endl;
						cout<<endl;
						nfound=0;
						system ("PAUSE");
						break;
					}
				}
					
				if(nfound==1)
					cout<<"No record found"<<endl;
				else
				{
					delrecord=counter;
					//clear screen
					system("cls"); 
					cout<<"***********************************************************************"<<endl;
					cout<<"\t\t Modify a doctor Record"<<endl;
					cout<<"***********************************************************************\n"<<endl;
					//get record
					cout<<left<<setw(30)<<"Name"<<":";
					getline(cin,buffer.name);
					cout<<left<<setw(30)<<"Doctor ID"<<":";
					getline(cin,buffer.id);
					cout<<left<<setw(30)<<"IC number"<<":";
					getline(cin,buffer.ic);
					cout<<left<<setw(30)<<"Department"<<":";
					getline(cin,buffer.department);
					cout<<left<<setw(30)<<"Date of birth"<<":";
					getline(cin,buffer.dob);
					cout<<left<<setw(30)<<"Phone number"<<":";
					getline(cin,buffer.num);
					cout<<left<<setw(30)<<"Email"<<":";
					getline(cin,buffer.email);
					cout<<left<<setw(30)<<"Address"<<":";
					getline(cin,buffer.address);
					
					//ask for last comform
					//clear screen
					system("cls");
					cout<<"***********************************************************************"<<endl;
					cout<<"\t\t Modify a doctor Record"<<endl;
					cout<<"***********************************************************************\n"<<endl;
					cout<<"_______________________________________________________________"<<endl;
					cout<<"|"<<left<<setw(30)<<"Name"<<"|"<<left<<setw(30)<<buffer.name<<"|"<<endl;
					cout<<"_______________________________________________________________"<<endl;
					cout<<"|"<<left<<setw(30)<<"Doctor ID"<<"|"<<left<<setw(30)<<buffer.id<<"|"<<endl;
					cout<<"_______________________________________________________________"<<endl;
					cout<<"|"<<left<<setw(30)<<"IC Number"<<"|"<<left<<setw(30)<<buffer.ic<<"|"<<endl;
					cout<<"_______________________________________________________________"<<endl;
					cout<<"|"<<left<<setw(30)<<"Department"<<"|"<<left<<setw(30)<<buffer.department<<"|"<<endl;
					cout<<"_______________________________________________________________"<<endl;
					cout<<"|"<<left<<setw(30)<<"Date of birth"<<"|"<<left<<setw(30)<<buffer.dob<<"|"<<endl;
					cout<<"_______________________________________________________________"<<endl;
					cout<<"|"<<left<<setw(30)<<"Phone number"<<"|"<<left<<setw(30)<<buffer.num<<"|"<<endl;
					cout<<"_______________________________________________________________"<<endl;
					cout<<"|"<<left<<setw(30)<<"Email"<<"|"<<left<<setw(30)<<buffer.email<<"|"<<endl;
					cout<<"_______________________________________________________________"<<endl;
					cout<<"|"<<left<<setw(30)<<"Address"<<"|"<<left<<setw(30)<<buffer.address<<"|"<<endl;
					cout<<"_______________________________________________________________"<<endl;
					cout<<endl;
					cout<<"Enter y to  modify record"<<endl;
					cout<<"Press any other button to cacel the modifications"<<endl;
					cin>>mselect;
					//overwrite record
					if(mselect=='Y'||mselect=='y')
					{
						write.open("DoctorInfo.txt");
						if (write.fail())
							cout<<"File not exist"<<endl;
						//cout<<rcounter<<endl<<delrecord<<endl;
						for(counter=0;counter<rcounter;counter++)
						{
							if(delrecord!=counter)
							{
								write<<doctor[counter].name<<endl;
								write<<doctor[counter].id<<endl;
								write<<doctor[counter].ic<<endl;
								write<<doctor[counter].department<<endl;
								write<<doctor[counter].dob<<endl;
								write<<doctor[counter].num<<endl;
								write<<doctor[counter].email<<endl;
								write<<doctor[counter].address<<endl;
								//cout<<counter<<endl;
							}
							else
							{
								write<<buffer.name<<endl;
								write<<buffer.id<<endl;
								write<<buffer.ic<<endl;
								write<<buffer.department<<endl;
								write<<buffer.dob<<endl;
								write<<buffer.num<<endl;
								write<<buffer.email<<endl;
								write<<buffer.address<<endl;
								//cout<<"Overwrite"<<endl;
							}
						}
						write.close();
						//sleep(50);

						cout<<"Modification complete"<<endl;
					}
				}
				cout<<endl<<"Press any key to return home"<<endl;
				cin>>end;					
				break;
		}

	}while(select !=5);
	//select function
	
}

void patients(records patient[],int rcounter)
{
	//declare variable
	int select,counter,nfound,delrecord;
	char end,vselect,aselect,dselect,mselect;
	string search,check;
	//declare pointer
	ifstream read;
	ofstream write;
	//declare structure
	struct records buffer;
	
	do{
		//clear screen
		system("cls");
		rcounter=0;
		read.open("patientInfo.txt");
			if (read.fail())
				cout<<"fail to read file"<<endl;
			while(!read.eof())
			{
				getline(read,patient[rcounter].name);
				getline(read,patient[rcounter].id);
				getline(read,patient[rcounter].ic);
				getline(read,patient[rcounter].dob);
				getline(read,patient[rcounter].num);
				getline(read,patient[rcounter].email);
				getline(read,patient[rcounter].address);
				rcounter++;
			}
		read.close();
			//-1 for '\n'
			rcounter=rcounter-1;
			
			//cout<<rcounter<<endl;

		//make selection use which function
		do{
			cout<<"***********************************************************************"<<endl;
			cout<<"\t\t\tPatient Management System"<<endl;
			cout<<"***********************************************************************"<<endl;
			cout<<"\t\t1-->View patient records"<<endl;
			cout<<"\t\t2-->Add new a patient record"<<endl;
			cout<<"\t\t3-->Delete patient records"<<endl;
			cout<<"\t\t4-->Modify patient records"<<endl;
			cout<<"\t\t5-->Return to dashboard"<<endl;
			cout<<"======================================================================="<<endl;
			cout<<"Enter an option :";
			cin>>select;
			//invalid check
			if (select<1||select>5)
				cout<<"Invalid option,pls re-enter\a"<<endl<<endl;	
		}while(select<1||select>5);

		//to deference function
		switch (select)
		{
			//view record
			case 1:
				//clear screen
				system("cls"); 
				cout<<"***********************************************************************"<<endl;
				cout<<"\t\tView patient records"<<endl;
				cout<<"***********************************************************************"<<endl;
				//display patient record
				cout<<"_____________________________________________________________"<<endl;
				cout<<"|"<<left<<setw(30)<<"Name"<<"|"<<left<<setw(28)<<"patient ID"<<"|"<<endl;
				cout<<"_____________________________________________________________"<<endl;
				for(counter=0;counter<rcounter;counter++)
				{
					cout<<"|"<<left<<setw(30)<<patient[counter].name<<"|"<<left<<setw(28)<<patient[counter].id<<"|"<<endl;
					cout<<"_____________________________________________________________"<<endl;
				}
				cout<<endl;
				//view details
				cout<<"Enter 'y' to search and view record details"<<endl;
				cout<<"Any other key to return to the menu"<<endl;
				cin>>vselect;
				if (vselect=='Y'||vselect=='y')
				{
					cout<<"Search record by name enter n"<<endl;
					cout<<"Search record by patient ID enter i"<<endl;
					cout<<"Enter other key to exit"<<endl;
					cin>>vselect;
					//Search record by name
					if(vselect=='N'||vselect=='n')
					{
						//get name need to view details
						cout<<"Enter the name:";
						cin.ignore();
						getline(cin,search);
						nfound=1;
						//clear screen
						system("cls"); 
						cout<<"***********************************************************************"<<endl;
						cout<<"\t\tView patient records"<<endl;
						cout<<"***********************************************************************"<<endl;
						for(counter=0;counter<rcounter;counter++)
						{
							check=patient[counter].name;
							//convert to lower case,cant use strlwr because not char[]
							transform(search.begin(),search.end(),search.begin(),::tolower);
							transform(check.begin(),check.end(),check.begin(),::tolower);
							if (search==check)
							{
								cout<<"______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"Name"<<"|"<<left<<setw(29)<<patient[counter].name<<"|"<<endl;
								cout<<"______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"patient ID"<<"|"<<left<<setw(29)<<patient[counter].id<<"|"<<endl;
								cout<<"______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"IC Number"<<"|"<<left<<setw(29)<<patient[counter].ic<<"|"<<endl;
								cout<<"______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"Date of birth"<<"|"<<left<<setw(29)<<patient[counter].dob<<"|"<<endl;
								cout<<"______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"Phone number"<<"|"<<left<<setw(29)<<patient[counter].num<<"|"<<endl;
								cout<<"______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"Email"<<"|"<<left<<setw(29)<<patient[counter].email<<"|"<<endl;
								cout<<"______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"Address"<<"|"<<left<<setw(29)<<patient[counter].address<<"|"<<endl;
								cout<<"______________________________________________________________"<<endl;
								cout<<endl;
								nfound=0;
							}
						}
						if(nfound==1)
							cout<<"No record found"<<endl;
					}
					//Search record by patient ID
					if(vselect=='I'||vselect=='i')
					{
						//get ID need to view details
						cout<<"Enter the patient ID:";
						cin.ignore();
						getline(cin,search);
						nfound=1;
						//clear screen
						system("cls"); 
						cout<<"***********************************************************************"<<endl;
						cout<<"\t\tView patient records"<<endl;
						cout<<"***********************************************************************"<<endl;
						for(counter=0;counter<rcounter;counter++)
						{
							check=patient[counter].id;
							//convert to lower case,cant use strlwr because not char[]
							transform(search.begin(),search.end(),search.begin(),::tolower);
							transform(check.begin(),check.end(),check.begin(),::tolower);
							if (search==check)
							{
								cout<<"______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"Name"<<"|"<<left<<setw(29)<<patient[counter].name<<"|"<<endl;
								cout<<"______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"patient ID"<<"|"<<left<<setw(29)<<patient[counter].id<<"|"<<endl;
								cout<<"______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"IC Number"<<"|"<<left<<setw(29)<<patient[counter].ic<<"|"<<endl;
								cout<<"______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"Date of birth"<<"|"<<left<<setw(29)<<patient[counter].dob<<"|"<<endl;
								cout<<"______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"Phone number"<<"|"<<left<<setw(29)<<patient[counter].num<<"|"<<endl;
								cout<<"______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"Email"<<"|"<<left<<setw(29)<<patient[counter].email<<"|"<<endl;
								cout<<"______________________________________________________________"<<endl;
								cout<<"|"<<left<<setw(30)<<"Address"<<"|"<<left<<setw(29)<<patient[counter].address<<"|"<<endl;
								cout<<"______________________________________________________________"<<endl;
								cout<<endl;
								nfound=0;
								break;
							}
						}
						if(nfound==1)
							cout<<"No record found"<<endl;
					}
				}
				cout<<endl<<"Press any key to return home"<<endl;
				cin>>end;					
				break;	
			//add record
			case 2:
				do{
					//clear screen
					system("cls"); 
					cout<<"***********************************************************************"<<endl;
					cout<<"\t\tAdd patient records"<<endl;
					cout<<"***********************************************************************"<<endl;
					//get record
					cin.ignore();
					cout<<left<<setw(30)<<"Name"<<":";
					getline(cin,buffer.name);
					
					do{
						cout<<left<<setw(30)<<"patient ID"<<":";
						getline(cin,buffer.id);
						//assign value and convert to lower case
						check=buffer.id;
						transform(check.begin(),check.end(),check.begin(),::tolower);
						for(counter=0;counter<rcounter;counter++)
						{
							//assign value and convert to lower case
							search=patient[counter].id;
							transform(search.begin(),search.end(),search.begin(),::tolower);
							if(search==check)
							{
								cout<<"The patient ID is not unique,please RE-ENTER"<<endl;
								sleep(1);
								break;
							}
						}
					}while(search==check);
					
					do{ 
						cout<<left<<setw(30)<<"IC number"<<":";
						getline(cin,buffer.ic);
						//assign value and convert to lower case
						check=buffer.id;
						transform(check.begin(),check.end(),check.begin(),::tolower);
						for(counter=0;counter<rcounter;counter++)
						{
							//assign value and convert to lower case
							search=patient[counter].ic;
							transform(search.begin(),search.end(),search.begin(),::tolower);
							if(search==check)
							{
								cout<<"The IC Number is not unique,please RE-ENTER"<<endl;
								sleep(1);
								break;
							}
						}
					}while(search==check);

					cout<<left<<setw(30)<<"Date of birth"<<":";
					getline(cin,buffer.dob); 
					cout<<left<<setw(30)<<"Phone number"<<":";
					getline(cin,buffer.num);
					cout<<left<<setw(30)<<"Email"<<":";
					getline(cin,buffer.email);
					cout<<left<<setw(30)<<"Address"<<":";
					getline(cin,buffer.address);
					
					//write record
					write.open("patientInfo.txt",ios::app);
					write<<buffer.name<<endl;
					write<<buffer.id<<endl;
					write<<buffer.ic<<endl;
					write<<buffer.dob<<endl;
					write<<buffer.num<<endl;
					write<<buffer.email<<endl;
					write<<buffer.address<<endl;
					write.close();
					//load patient record
					read.open("patientInfo.txt");
					if (read.fail())
						cout<<"File not exist"<<endl;
					else
					{
						rcounter=0;
						while(!read.eof())
						{
							getline(read,patient[rcounter].name);
							getline(read,patient[rcounter].id);
							getline(read,patient[rcounter].ic);
							getline(read,patient[rcounter].dob);
							getline(read,patient[rcounter].num);
							getline(read,patient[rcounter].email);
							getline(read,patient[rcounter].address);
							rcounter++;
						}
						//-1 for '\n'
						rcounter=rcounter-1;
						
						//cout<<rcounter<<endl;
					}
					read.close(); 
					//ask for write more record?
					cout<<"\nRecord successfully added"<<endl;
					cout<<"Enter y to add more record"<<endl;
					cout<<"Press any other button to continue :";
					cin>>aselect;
				}while(aselect=='Y'||aselect=='y');
				break;
			//delete record
			case 3:
				//clear screen
				system("cls"); 
				cout<<"***********************************************************************"<<endl;
				cout<<"\t\tDelete patient reords"<<endl;
				cout<<"***********************************************************************"<<endl;
				//display patient record
				cout<<"_____________________________________________________________"<<endl;
				cout<<"|"<<left<<setw(30)<<"Name"<<"|"<<left<<setw(28)<<"patient ID"<<"|"<<endl;
				cout<<"_____________________________________________________________"<<endl;
				for(counter=0;counter<rcounter;counter++)
				{
					cout<<"|"<<left<<setw(30)<<patient[counter].name<<"|"<<left<<setw(28)<<patient[counter].id<<"|"<<endl;
					cout<<"_____________________________________________________________"<<endl;
				}
				cout<<endl;
				//get patient ID need to delete
				cout<<"Enter the patient ID:";
				cin.ignore();
				getline(cin,search);
				nfound=1;
				//clear screen
				system("cls"); 
				cout<<"***********************************************************************"<<endl;
				cout<<"\t\tDelete patient reords"<<endl;
				cout<<"***********************************************************************"<<endl;
				for(counter=0;counter<rcounter;counter++)
				{
					check=patient[counter].id;
					//convert to lower case,cant use strlwr because not char[]
					transform(search.begin(),search.end(),search.begin(),::tolower);
					transform(check.begin(),check.end(),check.begin(),::tolower);
					if (search==check)
					{
						cout<<"______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"Name"<<"|"<<left<<setw(29)<<patient[counter].name<<"|"<<endl;
						cout<<"______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"patient ID"<<"|"<<left<<setw(29)<<patient[counter].id<<"|"<<endl;
						cout<<"______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"IC Number"<<"|"<<left<<setw(29)<<patient[counter].ic<<"|"<<endl;
						cout<<"______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"Date of birth"<<"|"<<left<<setw(29)<<patient[counter].dob<<"|"<<endl;
						cout<<"______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"Phone number"<<"|"<<left<<setw(29)<<patient[counter].num<<"|"<<endl;
						cout<<"______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"Email"<<"|"<<left<<setw(29)<<patient[counter].email<<"|"<<endl;
						cout<<"______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"Address"<<"|"<<left<<setw(29)<<patient[counter].address<<"|"<<endl;
						cout<<"______________________________________________________________"<<endl;
						cout<<endl;
						nfound=0;
						break;
					}
				}
				if(nfound==1)
					cout<<"No record found"<<endl;
				else
				{
					//ask for last comform
					cout<<"Enter y to delete record"<<endl;
					cin>>dselect;
					//overwrite record
					if(dselect=='Y'||dselect=='y')
					{
						delrecord=counter;
						write.open("patientInfo.txt");
						if (write.fail())
							cout<<"File not exist"<<endl;
						for(counter=0;counter<rcounter;counter++)
						{
							if(delrecord!=counter)
							{
								write<<patient[counter].name<<endl;
								write<<patient[counter].id<<endl;
								write<<patient[counter].ic<<endl;
								write<<patient[counter].dob<<endl;
								write<<patient[counter].num<<endl;
								write<<patient[counter].email<<endl;
								write<<patient[counter].address<<endl;
							}
						}
						write.close();
						cout<<"Record sucessfully deleted"<<endl;
					}
				}
				cout<<endl<<"Press any key to return home"<<endl;
				cin>>end;					
				break;
			//modify record
			case 4:
				//clear screen
				system("cls"); 
				cout<<"***********************************************************************"<<endl;
				cout<<"\t\tModify patient reords"<<endl;
				cout<<"***********************************************************************"<<endl;
				//display patient record
				cout<<"_____________________________________________________________"<<endl;
				cout<<"|"<<left<<setw(30)<<"Name"<<"|"<<left<<setw(28)<<"patient ID"<<"|"<<endl;
				cout<<"_____________________________________________________________"<<endl;
				for(counter=0;counter<rcounter;counter++)
				{
					cout<<"|"<<left<<setw(30)<<patient[counter].name<<"|"<<left<<setw(28)<<patient[counter].id<<"|"<<endl;
					cout<<"_____________________________________________________________"<<endl;
				}
				cout<<endl;
				//get patient ID need to modify
				cout<<"Enter the patient ID:";
				cin.ignore();
				getline(cin,search);
				nfound=1;
				//search same record
				for(counter=0;counter<rcounter;counter++)
				{
					check=patient[counter].id;
					//convert to lower case,cant use strlwr because not char[]
					transform(search.begin(),search.end(),search.begin(),::tolower);
					transform(check.begin(),check.end(),check.begin(),::tolower);
					if (search==check)
					{
						cout<<"\nCurrent information of the patient"<<endl;
						cout<<"______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"Name"<<"|"<<left<<setw(29)<<patient[counter].name<<"|"<<endl;
						cout<<"______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"patient ID"<<"|"<<left<<setw(29)<<patient[counter].id<<"|"<<endl;
						cout<<"______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"IC Number"<<"|"<<left<<setw(29)<<patient[counter].ic<<"|"<<endl;
						cout<<"______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"Date of birth"<<"|"<<left<<setw(29)<<patient[counter].dob<<"|"<<endl;
						cout<<"______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"Phone number"<<"|"<<left<<setw(29)<<patient[counter].num<<"|"<<endl;
						cout<<"______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"Email"<<"|"<<left<<setw(29)<<patient[counter].email<<"|"<<endl;
						cout<<"______________________________________________________________"<<endl;
						cout<<"|"<<left<<setw(30)<<"Address"<<"|"<<left<<setw(29)<<patient[counter].address<<"|"<<endl;
						cout<<"______________________________________________________________"<<endl;
						cout<<endl;
						nfound=0;
						system ("PAUSE");
						break;
					}
				}
					
				if(nfound==1)
					cout<<"No record found"<<endl;
				else
				{
					delrecord=counter;
					//clear screen
					system("cls"); 
					cout<<"***********************************************************************"<<endl;
					cout<<"\t\tModify patient reords"<<endl;
					cout<<"***********************************************************************"<<endl;
					//get record
					cout<<left<<setw(30)<<"Name"<<":";
					getline(cin,buffer.name);
					cout<<left<<setw(30)<<"patient ID"<<":";
					getline(cin,buffer.id);
					cout<<left<<setw(30)<<"IC number"<<":";
					getline(cin,buffer.ic);				
					cout<<left<<setw(30)<<"Date of birth"<<":";
					getline(cin,buffer.dob); 
					cout<<left<<setw(30)<<"Phone number"<<":";
					getline(cin,buffer.num);
					cout<<left<<setw(30)<<"Email"<<":";
					getline(cin,buffer.email);
					cout<<left<<setw(30)<<"Address"<<":";
					getline(cin,buffer.address);
					
					//ask for last comform
					//clear screen
					system("cls");
					cout<<"***********************************************************************"<<endl;
					cout<<"\t\tModify patient reords"<<endl;
					cout<<"***********************************************************************"<<endl;
					cout<<"______________________________________________________________"<<endl;
					cout<<"|"<<left<<setw(30)<<"Name"<<"|"<<left<<setw(29)<<buffer.name<<"|"<<endl;
					cout<<"______________________________________________________________"<<endl;
					cout<<"|"<<left<<setw(30)<<"patient ID"<<"|"<<left<<setw(29)<<buffer.id<<"|"<<endl;
					cout<<"______________________________________________________________"<<endl;
					cout<<"|"<<left<<setw(30)<<"IC Number"<<"|"<<left<<setw(29)<<buffer.ic<<"|"<<endl;
					cout<<"______________________________________________________________"<<endl;
					cout<<"|"<<left<<setw(30)<<"Date of birth"<<"|"<<left<<setw(29)<<buffer.dob<<"|"<<endl;
					cout<<"______________________________________________________________"<<endl;
					cout<<"|"<<left<<setw(30)<<"Phone number"<<"|"<<left<<setw(29)<<buffer.num<<"|"<<endl;
					cout<<"______________________________________________________________"<<endl;
					cout<<"|"<<left<<setw(30)<<"Email"<<"|"<<left<<setw(29)<<buffer.email<<"|"<<endl;
					cout<<"______________________________________________________________"<<endl;
					cout<<"|"<<left<<setw(30)<<"Address"<<"|"<<left<<setw(29)<<buffer.address<<"|"<<endl;
					cout<<"______________________________________________________________"<<endl;
					cout<<endl;
					cout<<"Enter y to  modify record"<<endl;
					cin>>mselect;
					//overwrite record
					if(mselect=='Y'||mselect=='y')
					{
						write.open("patientInfo.txt");
						if (write.fail())
							cout<<"File not exist"<<endl;
						//cout<<rcounter<<endl<<delrecord<<endl;
						for(counter=0;counter<rcounter;counter++)
						{
							if(delrecord!=counter)
							{
								write<<patient[counter].name<<endl;
								write<<patient[counter].id<<endl;
								write<<patient[counter].ic<<endl;
								write<<patient[counter].dob<<endl;
								write<<patient[counter].num<<endl;
								write<<patient[counter].email<<endl;
								write<<patient[counter].address<<endl;
								//cout<<counter<<endl;
							}
							else
							{
								write<<buffer.name<<endl;
								write<<buffer.id<<endl;
								write<<buffer.ic<<endl;
								write<<buffer.dob<<endl;
								write<<buffer.num<<endl;
								write<<buffer.email<<endl;
								write<<buffer.address<<endl;
								//cout<<"Overwrite"<<endl;
							}
						}
						write.close();
						//sleep(50);
						//clear screen
			
						cout<<"Modification record complete"<<endl;
					}
				}
				cout<<endl<<"Press any key to return home"<<endl;
				cin>>end;					
				break;
		}

	}while(select!=5);
	//select function
}

void appointments(records patient [],int countp)
{
	int opt;//selection int he main menu
	int k;//counter
	int c;//for the choice of the record
	int i;//for the for loop counter
	ofstream write;
	int counta;// record counter...a counter for the appointment
	ifstream read;
	string pid;// user in put to find the patient
	string time[]= { "0900","1000","1100","1200","1300","1400","1500","1600"};//the array of the time slot available
	bool avail[]= {1,1,1,1,1,1,1,1};// 1= available and 0= booked
	struct records appointment[size], temp;
	char o;//to continue or not	
	do
	{
		int j=0,l=0; // to hold array prosecces temporaryly
		system("CLS");
		cout<<"****************************************************************"<<endl;
		cout<<"\t\t\tAppointment scheduling "<<endl;
		cout<<"****************************************************************"<<endl;
		cout<<"\t\t1-->Schedule an appointment"<<endl;
		cout<<"\t\t2-->Reschedule an appointment"<<endl;
		cout<<"\t\t3-->Cancel an appointment"<<endl;
		cout<<"\t\t4-->View appointments"<<endl;
		cout<<"\t\t5-->return to dashboard"<<endl;
		cout<<"================================================================"<<endl;
		do
		{
			cout<<"Please enter your option :";
			cin>>opt;
			if(opt<1 || opt>5)
				cout<<"\a!!Invalid option!!"<<endl;
		}while(opt<1 || opt>5);							// If an invalid option is chosen the user has to redo the option section
		cin.ignore();
		counta=0;//reset the counter
		
		read.open("Appointmentrec.txt");
			if (read.fail())
				cout<<"fail to read file"<<endl;
			while(!read.eof())
			{
				getline(read,appointment[counta].id);
				getline(read,appointment[counta].name);
				getline(read,appointment[counta].department);
				getline(read,appointment[counta].date);
				getline(read,appointment[counta].time);
				counta++;
			}
		read.close();
		counta-=1;//'\n' so -1
	//	cout<<counta<<endl;
		
	
		switch(opt)
		{
			case 1://schedule and appointment
				{
					do
					{
						system ("CLS");
						cout<<"****************************************************************"<<endl;
						cout<<"\t\tSchedule an appointment "<<endl;
						cout<<"****************************************************************"<<endl;
						cout<<"--The hospital is only allowed to book an appointment during working hours."<<endl;
						cout<<"--Which are 0900 to 1700.The last available slot that can be booked in a day is 1600"<<endl;
						cout<<"--There can be only be a maximum of 8 slots in a day\n"<<endl;
						do
						{
							
							cout<<"Patient ID :";
							getline(cin,pid);//this section will capture the patient details for the invoice through the patient id
							
							for(i=0 ;i<countp-1;i++)
							{
								if(pid==patient[i].id)
								{
									j=i;//to hold the location
									break;
								}
							}
							if(i==countp)
							{
								cout<<"The patient id does not exist\nPlease re-enter"<<endl;
							}
							else
								cout<<"\nPatient details captured"<<endl;
						}while(i==countp);//if the user enters a do while loop it is because they entered a non existing patient id.
						
						cout<<"\nDepartment the patient would like visit	:";
						getline(cin,temp.department);
						do
						{
							cout<<"Date of the appointment in the format of (dd/mm/yyyy)	:";
							getline(cin,temp.date);
							
							for(i=0;i<counta;i++)//to check if the slots in the day has exceeded the limit
							{
								if(temp.date==appointment[i].date)
									l++;
							}
						//	cout<<l<<endl;
							if(l>9)
							{
								cout<<"\n--------------------------------------------------"<<endl;
								cout<<"Appointment slots on that day are fully booked"<<endl;
								cout<<"Please re-enter the date of the appointment"<<endl;
								cout<<"--------------------------------------------------"<<endl;
							}
							else 
							{
								for(i=0;i<counta;i++)//check all the available slots on that day
								{
									if(temp.date==appointment[i].date)
									{
										for(k=0;k<8;k++)
										{
											if(time[k]==appointment[i].time)//compare it againgst all the general available slots
											{
												avail[k]=0;// kepps trck of the time slots that are booked
											}
										}
									}
								}
								
								cout<<"\n\t\t___________________________________________"<<endl;
								cout<<"\t\t|"<<setw(41)<<left<<temp.date<<"|"<<endl;
								cout<<"\t\t___________________________________________"<<endl;
								cout<<"\t\t|"<<setw(20)<<left<<"Time Slots"<<"|"<<setw(20)<<left<<"Availabillity"<<"|"<<endl;
								cout<<"\t\t___________________________________________"<<endl;
								for(i=0;i<8;i++)
								{
									if(avail[i]==0)
									{
										cout<<"\t\t|"<<setw(20)<<left<<time[i]<<"|"<<setw(20)<<left<<"Booked"<<"|"<<endl;
										cout<<"\t\t___________________________________________"<<endl;
									}
									if(avail[i]==1)
									{
										cout<<"\t\t|"<<setw(20)<<left<<time[i]<<"|"<<setw(20)<<left<<"Available"<<"|"<<endl;
										cout<<"\t\t___________________________________________"<<endl;
									}
								}
								do
								{	
									cout<<"Time of appointment in the 24hr format	:";
									getline(cin,temp.time);
									for(i=0;i<counta;i++)// to check the time slot is taken 
									{
										if(temp.date==appointment[i].date&&temp.time==appointment[i].time)
										{
											cout<<"\n--------------------------------------------------"<<endl;
											cout<<"The time slot "<<temp.time<<" is not available on this date"<<endl;
											cout<<"Please try a diffrent time slot"<<endl;
											cout<<"--------------------------------------------------"<<endl;
											break;
										}
									}
								}while(temp.date==appointment[i].date&&temp.time==appointment[i].time);
							}
						}while(l>9);
						
						system("CLS");//confirmation
						cout<<"****************************************************************"<<endl;
						cout<<"\t\tSchedule an appointment "<<endl;
						cout<<"****************************************************************"<<endl;
						cout<<"_________________________________________________________________________________________________"<<endl;
						cout<<"|"<<setw(10)<<left<<"PatientID"<<"|"<<setw(40)<<left<<"Patient Name"<<"|"<<setw(25)<<left<<"Department"<<"|"<<setw(10)<<left<<"Date"<<"|"<<setw(6)<<left<<"Time"<<"|"<<endl;
						cout<<"_________________________________________________________________________________________________"<<endl;
						cout<<"|"<<setw(10)<<left<<patient[j].id<<"|"<<setw(40)<<left<<patient[j].name<<"|"<<setw(25)<<left<<temp.department<<"|"<<setw(10)<<left<<temp.date<<"|"<<setw(6)<<left<<temp.time<<"|"<<endl;
						cout<<"_________________________________________________________________________________________________"<<endl;
						
						cout<<"\n Do you wish to Schedule this appointmnet\n Press '1' if yes, and any other button if no	:";
						cin>>o;
						if(o=='1')
						{
							
							write.open("Appointmentrec.txt",ios::app);//to save the record
								write<<patient[j].id<<endl;
								write<<patient[j].name<<endl;
								write<<temp.department<<endl;
								write<<temp.date<<endl;
								write<<temp.time<<endl;
							write.close();
							l=counta;//to add into the existing array
							counta++;//adds the counter size
							appointment[l].id=patient[j].id;
							appointment[l].name=patient[j].name;
							appointment[l].department= temp.department;
							appointment[l].date=temp.date;
							appointment[l].time= temp.time;
							cout<<"\nAppointment Scheduled successfully"<<endl;
						
						}
						else;
						cout<<"\nDo you wish to schedule another appointment \n Press '1' if yes, and any other button if no	:";
						cin>>o;
						cin.ignore();
					}while (o == '1');
					
					break;	
				}
			case 2://reschedule appointment
				{
					do
					{
						system ("CLS");
						string time[]= { "0900","1000","1100","1200","1300","1400","1500","1600"};//the array of the time slot available
						bool avail[]= {1,1,1,1,1,1,1,1};// 1= available and 0= booked											To re initialize the array 
						cout<<"****************************************************************"<<endl;
						cout<<"\t\tReschedule an appointment "<<endl;
						cout<<"****************************************************************"<<endl;	
						cout<<"______________________________________________________________________________________________________"<<endl;
						cout<<"|"<<setw(4)<<left<<"No."<<"|"<<setw(10)<<left<<"PatientID"<<"|"<<setw(40)<<left<<"Patient Name"<<"|"<<setw(25)<<left<<"Department"<<"|"<<setw(10)<<left<<"Date"<<"|"<<setw(6)<<left<<"Time"<<"|"<<endl;
						cout<<"______________________________________________________________________________________________________"<<endl;
						for(i=0;i<counta;i++)
						{
							cout<<"|"<<setw(4)<<left<<i+1<<"|"<<setw(10)<<left<<appointment[i].id<<"|"<<setw(40)<<left<<appointment[i].name<<"|"<<setw(25)<<left<<appointment[i].department<<"|"<<setw(10)<<left<<appointment[i].date<<"|"<<setw(6)<<left<<appointment[i].time<<"|"<<endl;
							cout<<"______________________________________________________________________________________________________"<<endl;
						}
						cout<<"Enter the number of the appointment that you want to reschedule	:";
						cin>>c;
						cin.ignore();
						
						system("CLS");
						cout<<"****************************************************************"<<endl;
						cout<<"\t\tReschedule an appointment "<<endl;
						cout<<"****************************************************************"<<endl;
						c-=1;//array index
						do
						{
							cout<<"Date of the appointment in the format of (dd/mm/yyyy)	:";
							getline(cin,temp.date);
							
							for(i=0;i<counta;i++)//to check if the slots in the day has exceeded the limit
							{
								if(temp.date==appointment[i].date)
									l++;
							}
						//	cout<<l<<endl;
							if(l>9)
							{
								cout<<"--------------------------------------------------"<<endl;
								cout<<"Appointment slots on that day are fully booked"<<endl;
								cout<<"Please re-enter the date of the appointment"<<endl;
								cout<<"--------------------------------------------------"<<endl;
							}
							else 
							{
								for(i=0;i<counta;i++)//check all the available slots on that day
								{
									if(temp.date==appointment[i].date)
									{
										for(k=0;k<8;k++)//compare it with the parallel  array that has been initialized to find if the slots are available or not
										{
											if(time[k]==appointment[i].time)
											{
												avail[k]=0;
											}
										}
									}
								}
								
								cout<<"\n\t\t___________________________________________"<<endl;
								cout<<"\t\t|"<<setw(41)<<left<<temp.date<<"|"<<endl;
								cout<<"\t\t___________________________________________"<<endl;
								cout<<"\t\t|"<<setw(20)<<left<<"Time Slots"<<"|"<<setw(20)<<left<<"Availabillity"<<"|"<<endl;
								cout<<"\t\t___________________________________________"<<endl;
								for(i=0;i<8;i++)
								{
									if(avail[i]==0)
									{
										cout<<"\t\t|"<<setw(20)<<left<<time[i]<<"|"<<setw(20)<<left<<"Booked"<<"|"<<endl;
										cout<<"\t\t___________________________________________"<<endl;
									}
									if(avail[i]==1)
									{
										cout<<"\t\t|"<<setw(20)<<left<<time[i]<<"|"<<setw(20)<<left<<"Available"<<"|"<<endl;
										cout<<"\t\t___________________________________________"<<endl;
									}
								}
								do
								{	
									cout<<"\nTime of appointment in the 24hr format	:";
									getline(cin,temp.time);
									for(i=0;i<counta;i++)// to check the time slot is taken 
									{
										if(temp.date==appointment[i].date&&temp.time==appointment[i].time)
										{
											cout<<"\n--------------------------------------------------"<<endl;
											cout<<"The time slot "<<temp.time<<" is not available on this date"<<endl;
											cout<<"Please try a diffrent time slot"<<endl;
											cout<<"--------------------------------------------------"<<endl;
											break;
										}
									}
								}while(temp.date==appointment[i].date&&temp.time==appointment[i].time);
							}
						}while(l>9);
							
							appointment[c].date=temp.date;
							appointment[c].time=temp.time;
						
						system("CLS");//display confirmation
						cout<<"****************************************************************"<<endl;
						cout<<"\t\tReschedule an appointment "<<endl;
						cout<<"****************************************************************"<<endl;
						cout<<"______________________________________________________________________________________________________"<<endl;
						cout<<"|"<<setw(4)<<left<<"No."<<"|"<<setw(10)<<left<<"PatientID"<<"|"<<setw(40)<<left<<"Patient Name"<<"|"<<setw(25)<<left<<"Department"<<"|"<<setw(10)<<left<<"Date"<<"|"<<setw(6)<<left<<"Time"<<"|"<<endl;
						cout<<"______________________________________________________________________________________________________"<<endl;
						for(i=0;i<counta;i++)
						{
							cout<<"|"<<setw(4)<<left<<i+1<<"|"<<setw(10)<<left<<appointment[i].id<<"|"<<setw(40)<<left<<appointment[i].name<<"|"<<setw(25)<<left<<appointment[i].department<<"|"<<setw(10)<<left<<appointment[i].date<<"|"<<setw(6)<<left<<appointment[i].time<<"|"<<endl;
							cout<<"______________________________________________________________________________________________________"<<endl;
						}
						
						cout<<"\nAppointment Reshceduled"<<endl;
						write.open("Appointmentrec.txt");
							for(i=0;i<counta;i++)
							{
								write<<appointment[i].id<<endl;
								write<<appointment[i].name<<endl;
								write<<appointment[i].department<<endl;
								write<<appointment[i].date<<endl;
								write<<appointment[i].time<<endl;
							}
						write.close();
						
						cout<<"Do you wish to reschedule another appointment"<<endl;
						cout<<"Press 1 if yes, press any other button to return to the menu	:";
						cin>>o;
					}while(o=='1');
						
					break;
					
				}
			case 3:
				{
					do
					{
						system ("CLS");
						cout<<"****************************************************************"<<endl;
						cout<<"\t\tCancel an appointment "<<endl;
						cout<<"****************************************************************"<<endl;	
						cout<<"______________________________________________________________________________________________________"<<endl;
						cout<<"|"<<setw(4)<<left<<"No."<<"|"<<setw(10)<<left<<"PatientID"<<"|"<<setw(40)<<left<<"Patient Name"<<"|"<<setw(25)<<left<<"Department"<<"|"<<setw(10)<<left<<"Date"<<"|"<<setw(6)<<left<<"Time"<<"|"<<endl;
						cout<<"______________________________________________________________________________________________________"<<endl;
						for(i=0;i<counta;i++)
						{
							cout<<"|"<<setw(4)<<left<<i+1<<"|"<<setw(10)<<left<<appointment[i].id<<"|"<<setw(40)<<left<<appointment[i].name<<"|"<<setw(25)<<left<<appointment[i].department<<"|"<<setw(10)<<left<<appointment[i].date<<"|"<<setw(6)<<left<<appointment[i].time<<"|"<<endl;
							cout<<"______________________________________________________________________________________________________"<<endl;	
						}
						cout<<"Enter the number of the appointment that you want to cancel	:";
						cin>>c;
						c-=1;//array index of the item that is to be deleted
						
						for(i=c;i<counta;i++)//overwrites that array index place
						{
							appointment[i].id=appointment[i+1].id;
							appointment[i].name=appointment[i+1].name;
							appointment[i].department=appointment[i+1].department;
							appointment[i].date=appointment[i+1].date;
							appointment[i].time=appointment[i+1].time;
						}
						counta--;//to update the counter size
						
						write.open("Appointmentrec.txt");
							for(i=0;i<counta;i++)
							{
								write<<appointment[i].id<<endl;
								write<<appointment[i].name<<endl;
								write<<appointment[i].department<<endl;
								write<<appointment[i].date<<endl;
								write<<appointment[i].time<<endl;
							}
						write.close();
						
						system ("CLS");
						cout<<"****************************************************************"<<endl;
						cout<<"\t\tCancel an appointment "<<endl;
						cout<<"****************************************************************"<<endl;	
						cout<<"______________________________________________________________________________________________________"<<endl;
						cout<<"|"<<setw(4)<<left<<"No."<<"|"<<setw(10)<<left<<"PatientID"<<"|"<<setw(40)<<left<<"Patient Name"<<"|"<<setw(25)<<left<<"Department"<<"|"<<setw(10)<<left<<"Date"<<"|"<<setw(6)<<left<<"Time"<<"|"<<endl;
						cout<<"______________________________________________________________________________________________________"<<endl;
						for(i=0;i<counta;i++)
						{
							cout<<"|"<<setw(4)<<left<<i+1<<"|"<<setw(10)<<left<<appointment[i].id<<"|"<<setw(40)<<left<<appointment[i].name<<"|"<<setw(25)<<left<<appointment[i].department<<"|"<<setw(10)<<left<<appointment[i].date<<"|"<<setw(6)<<left<<appointment[i].time<<"|"<<endl;
							cout<<"______________________________________________________________________________________________________"<<endl;	
						}
						cout<<"\nAppointment Canceled"<<endl;
						cout<<"\nDo your wish to cancel another appointment?"<<endl;
						cout<<"If you do press '1', If your dont press any button	:"<<endl;
						cin>>o;
					}while(o=='1');
					
					break;
				}
			case 4:
				{
					do
					{
						system ("CLS");
						cout<<"****************************************************************"<<endl;
						cout<<"\t\tView all appointments "<<endl;
						cout<<"****************************************************************"<<endl;	
						cout<<"Enter the date of the appointments that you wish to view	:";
						getline(cin,temp.date);
						
						cout<<"______________________________________________________________________________________________________"<<endl;
						cout<<"|"<<setw(4)<<left<<"No."<<"|"<<setw(10)<<left<<"PatientID"<<"|"<<setw(40)<<left<<"Patient Name"<<"|"<<setw(25)<<left<<"Department"<<"|"<<setw(10)<<left<<"Date"<<"|"<<setw(6)<<left<<"Time"<<"|"<<endl;
						cout<<"______________________________________________________________________________________________________"<<endl;
						for(i=0;i<counta;i++)
						{
							if(temp.date==appointment[i].date)//to display the only required date
							{
								cout<<"|"<<setw(4)<<left<<i+1<<"|"<<setw(10)<<left<<appointment[i].id<<"|"<<setw(40)<<left<<appointment[i].name<<"|"<<setw(25)<<left<<appointment[i].department<<"|"<<setw(10)<<left<<appointment[i].date<<"|"<<setw(6)<<left<<appointment[i].time<<"|"<<endl;
								cout<<"______________________________________________________________________________________________________"<<endl;
							}
						}
						cout<<"\nPress '1' if you wish to view appointmets on another date \nPress any button to return to the MENU"<<endl;
						cin>>o;
						cin.ignore();
					}while(o=='1');
					break;
				}
		}
	}while (opt!=5);
}