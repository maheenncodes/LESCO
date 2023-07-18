#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
using namespace std;

class Helper;
class LESCO;
class Customer;
class Employee;
class BillingInfo;
class TaxTarrif;

//------------------------------------------------------------------------------------------------------------------
//											CLASS HELPER
//------------------------------------------------------------------------------------------------------------------


class Helper {

public:

	//calculates the length of string
	static int StringLength(char* str)
	{
		int strlen = 0;
		for (int i = 0; str[i] != '\0'; i++)
		{
			strlen++;
		}

		return strlen++;
	}

	//allocates memory for char array on heap
	static char* GetStringFromBuffer(char* buffer)
	{

		int strLen = StringLength(buffer);

		char* myArr = new char[strLen + 2];
		int i = 0;

		for (; buffer[i] != '\0'; i++)
			myArr[i] = buffer[i];

		myArr[i] = '\0';

		return myArr;


	}
	//Compares the two string and returns if they are equal or no
	static bool StringCompare(char* a, char* b)
	{
		bool flag = false;
		int len_a = StringLength(a);
		int len_b = StringLength(b);
		int j = 0;

		if (len_a != len_b)
		{
			return false;
		}
		else
		{
			for (int i = 0; a[i] != '\0'; i++)
			{
				if (a[i] != b[i])
				{
					return false;
				}
				else
				{
					flag = true;
				}
			}
		}


		return flag;
	}

	//Function to add one in the ID of previous customer for new added customer.
	static bool intAdd(int*& a)
	{
		int carried = 1;
		for (int i = 3; i >= 0; i--)
		{

			if (a[i] < 9)
			{
				a[i] = a[i] + carried;
				carried = 0;
			}
			else
			{
				a[i] = 0;
				carried = 1;
			}
		}
		return 0;
	}

};

//------------------------------------------------------------------------------------------------------------------
//											CLASS EMPLOYEE
//------------------------------------------------------------------------------------------------------------------

class Employee
{

private:
	char* username;
	char* password;

public:

	//Constructor
	Employee()
	{
		username = NULL;
		password = NULL;
	}
	//Function to load employees from file.
	void LoadEmployee(ifstream& fin)
	{
		char tempBuffer[100];
		fin.getline(tempBuffer, 100, ',');
		username = Helper::GetStringFromBuffer(tempBuffer);
		fin.getline(tempBuffer, 100, '\n');
		password = Helper::GetStringFromBuffer(tempBuffer);
	}
	//Updates the password of the employee.
	void UpdatePassword(ofstream& fout)
	{
		fout << username;
		fout << ",";
		fout << password;
		fout << "\n";

	}
	//GETTERS
	char* GetUsername()
	{
		return username;
	}

	char* GetPassword()
	{
		return password;
	}
	//Sets Password of employee.
	void SetPassword(char* pass)
	{
		password = pass;
	}
	
};


//------------------------------------------------------------------------------------------------------------------
//											CLASS BILLING INFORMATION
//------------------------------------------------------------------------------------------------------------------

class BillingInfo
{
private:
	int customerId[4];
	char* billingMonth;
	double current_meter_reading_regular;
	double current_meter_reading_peak;
	int  issueDate;
	double cost_electricity_regular;
	double cost_electricity_peak;
	double salesTax;
	double fixedCharges;
	double totalBillAmount;
	int DueDate;
	char* status;
	int paymentDate;
	TaxTarrif* InfoOfTax;
	double consumed_RegularUnits;
	double consumed_PeakUnits;



public:
	//Constructor
	BillingInfo()
	{

		for (int i = 0; i < 4; i++)
		{
			customerId[i] = 0;
		}
		billingMonth = 0;
		current_meter_reading_regular = 0;
		current_meter_reading_peak = 0;

		issueDate = 0;

		cost_electricity_regular = 0;
		cost_electricity_peak = 0;
		salesTax = 0;
		fixedCharges = 0;
		totalBillAmount = 0;


		DueDate = 0;


		status = 0;


		paymentDate = 0;



	}

	//Function to load the all required information of bill from file.
	void LoadBillInfo(ifstream& file)
	{

		char buffer[100];

		int id = 0;
		file >> id;
		for (int i = 3, mod = 0; id != 0; i--)
		{
			mod = id % 10;
			customerId[i] = mod;
			id = id / 10;
		}
		file.ignore();


		file.getline(buffer, 100, ',');

		billingMonth = Helper::GetStringFromBuffer(buffer);
		// file.ignore();

		file >> current_meter_reading_regular;
		file.ignore();

		file >> current_meter_reading_peak;
		file.ignore();
		//file.ignore();
		//file.ignore();

		file >> issueDate;

		file.ignore();


		file >> cost_electricity_regular;
		file.ignore();

		file >> cost_electricity_peak;
		file.ignore();

		file >> salesTax;
		file.ignore();


		file >> fixedCharges;
		file.ignore();


		file >> totalBillAmount;
		file.ignore();


		file >> DueDate;

		file.ignore();


		file.getline(buffer, 100, ',');
		status = Helper::GetStringFromBuffer(buffer);
		file.ignore();



		file >> paymentDate;
		file.ignore();





	}

	//Function to Update the Bill Information.
	void UpdateBillInfo(ofstream& file)
	{


		for (int i = 0; i < 4; i++)
		{
			file << customerId[i];

		}
		file << ",";



		file << billingMonth;
		file << ",";

		file << current_meter_reading_regular;


		file << ",";

		file << current_meter_reading_peak;
		file << ",";
		//file.ignore();
		//file.ignore();

		file << issueDate;

		file << ",";


		file << cost_electricity_regular;
		file << ",";

		file << cost_electricity_peak;
		file << ",";

		file << salesTax;
		file << ",";


		file << fixedCharges;
		file << ",";

		file << totalBillAmount;
		file << ",";


		file << DueDate;

		file << ",";


		file << status;
		file << ",";



		file << paymentDate;
		file << "\n";


	}

	//Function to check the status if bill is paid or unpaid.
	void CheckStatus()
	{

		if (status[0] == 'U')
		{
			status = "Paid";
		}




	}

	//Function to Print the all information of bill.
	void PrintBillInfo()
	{
		cout<<endl;
		double bill=CalculateBill();
		SetTotalBillAmount(bill);
		cout<<"\n	              *******BILL*******\n";
		cout << "Cost Of Electricity Regular : " << cost_electricity_regular << "\t\t";
		cout << "Cost Of Electricity Peak : " << cost_electricity_peak << endl <<endl ;
		cout << "Total Bill Amount Due : " << totalBillAmount << "\t\t";
		cout << "Due Date : " << DueDate << endl;
		cout << "Status Of Bill: " << status << endl;

	}

	//Function to calculate the bill. 
	double CalculateBill()
	{
		double regular_Price;
		regular_Price = current_meter_reading_regular - consumed_RegularUnits;
		regular_Price = regular_Price * cost_electricity_regular;

		double peak_Price;
		peak_Price = current_meter_reading_peak - consumed_PeakUnits;
		peak_Price = peak_Price * cost_electricity_peak;

		totalBillAmount = regular_Price + peak_Price;


		return totalBillAmount;
	}

	//GETTERS
	int* GetCustomerId()
	{
		return customerId;
	}

	double GetRegularReading()
	{
		return current_meter_reading_regular;
	}

	double GetPeakReading()
	{
		return current_meter_reading_peak;
	}

	char* GetStatus()
	{
		return status;
	}

	TaxTarrif* GetTarif()
	{
		return InfoOfTax;
	}

	//SETTERS
	void SetCurrrentRegularUnits(double units_Current)
	{
		consumed_RegularUnits = units_Current;
	}

	void SetCurrrentPeakUnits(double units_Current)
	{
		consumed_PeakUnits = units_Current;
	}

	void SetTotalBillAmount(double total_Bill)
	{
		totalBillAmount = total_Bill;
	}

	void SetPayementDate(int date)
	{
		paymentDate = date;
	}

	void SetInfoOfTax(TaxTarrif*& info)
	{
		InfoOfTax = info;
	}

};


//------------------------------------------------------------------------------------------------------------------
//											CLASS CUSTOMER
//------------------------------------------------------------------------------------------------------------------

class Customer
{

private:
	int CustomerId[4];
	char* CustomerDOB;// (YYYYMMDD)
	char* CustomerName;
	char* CustomerAdress;
	char* CustomerPhnNo;
	char* CustomerType;
	char* MeterType;
	char* ConnectionDate;
	BillingInfo* bill;
	double  RegularUnits;
	double PeakHourUnits;

public:
    //Constructor 
	Customer() 
	{
		for (int i = 0; i < 4; i++)
		{
			CustomerId[i] = 0;
		}
		CustomerDOB = 0;
		CustomerName = 0;
		CustomerAdress = 0;
		CustomerPhnNo = 0;
		CustomerType = 0;
		MeterType = 0;
		ConnectionDate = 0;
		RegularUnits = 0;
		PeakHourUnits = 0;
	}
	//Overloaded Constructor
	Customer(int _CustomerId[4], char* _CustomerDOB, char* _CustomerName, char* _CustomerAdress, char* _CustomerPhnNo, char* _CustomerType, char* _MeterType, char* _ConnectionDate, double  _RegularUnits, double _PeakHourUnits)
	{
		for (int i = 0; i < 4; i++)
		{
			CustomerId[i] = _CustomerId[i];
		}

		CustomerDOB = _CustomerDOB;
		CustomerName = _CustomerName;
		CustomerAdress = _CustomerAdress;
		CustomerPhnNo = _CustomerPhnNo;
		CustomerType = _CustomerType;
		MeterType = _MeterType;
		ConnectionDate = _ConnectionDate;
		RegularUnits = _RegularUnits;
		PeakHourUnits = _PeakHourUnits;
	}
	
	//Function to load data of customers from the file.
	void LoadCustomerInfo(ifstream& fin)

	{

		char temp[100];
		int id = 0;
		fin >> id;
		for (int i = 3, mod = 0; id != 0; i--)
		{
			mod = id % 10;
			CustomerId[i] = mod;
			id = id / 10;
		}
		fin.ignore();

		fin.getline(temp, 100, ',');
		CustomerDOB = Helper::GetStringFromBuffer(temp);


		fin.getline(temp, 100, ',');
		CustomerName = Helper::GetStringFromBuffer(temp);

		fin.getline(temp, 100, ',');
		CustomerAdress = Helper::GetStringFromBuffer(temp);

		fin.getline(temp, 100, ',');
		CustomerPhnNo = Helper::GetStringFromBuffer(temp);

		fin.getline(temp, 100, ',');
		CustomerType = Helper::GetStringFromBuffer(temp);

		fin.getline(temp, 100, ',');
		MeterType = Helper::GetStringFromBuffer(temp);

		fin.getline(temp, 100, ',');
		ConnectionDate = Helper::GetStringFromBuffer(temp);

		fin >> RegularUnits;
		if (RegularUnits < 0 && RegularUnits>999999999)
		{
			cout << "\nOut of bound Regular units !\n";
		}
		fin.ignore();
		fin >> PeakHourUnits;
		if (PeakHourUnits < 0 && PeakHourUnits>999999999)
		{
			cout << "\nOut of bound Peak Hour Units !\n";
		}
		fin.ignore();



	}

	//Function to updating the already existing file.
	void UpdateCustomerFile(ofstream& fout)
	{

		for (int i = 0; i < 4; i++)
		{
			fout << CustomerId[i];
		}
		fout << ",";

		fout << CustomerDOB;
		fout << ",";

		fout << CustomerName;
		fout << ",";

		fout << CustomerAdress;
		fout << ",";

		fout << CustomerPhnNo;
		fout << ",";

		fout << CustomerType;
		fout << ",";

		fout << MeterType;
		fout << ",";

		fout << ConnectionDate;
		fout << ",";

		fout << RegularUnits;
		fout << ",";

		fout << PeakHourUnits;
		fout << "\n";


	}

	//SETTERS
	void SetBillInfo(BillingInfo*& _bill)
	{
		bill = _bill;
	}
	
	void SetRegularReading(double reading)
	{
		RegularUnits = reading;
	}

	void SetPeakUnits(double reading)
	{
		PeakHourUnits = reading;
	}

	//GETTERS
	BillingInfo*& GetBillInfo()
	{
		return bill;
	}

	double GetCurrentPeakUnits()
	{
		return PeakHourUnits;
	}

	double GetCurrentRegularUnits()
	{
		return RegularUnits;
	}

	char* GetName()
	{
		return CustomerName;
	}

	char* GetCustomerType()
	{
		return CustomerType;
	}

	char* GetMeterType()
	{
		return MeterType;
	}

	int* GetID()
	{
		return CustomerId;
	}

	char* GetDOB()
	{
		return CustomerDOB;
	}

	//Function to Print customer and its bill info.
	void PrintCustomer()
	{
		cout<<"		  ******CUSTOMER INFORMATION*******\n";
		cout << "Customer ID: " << CustomerId <<"\t\t\t";
		cout << "Customer Name : " << CustomerName << endl << endl;
		cout << "Address : " << CustomerAdress << endl << endl;
		cout << "Customer Phone No: " << CustomerPhnNo << endl << endl;
		cout << "Customer Type : " << CustomerType <<"\t\t";
		cout << "Meter Type : " << MeterType << endl;

		GetBillInfo()->PrintBillInfo();
	}

};


//------------------------------------------------------------------------------------------------------------------
//											CLASS TAXTARRIF
//------------------------------------------------------------------------------------------------------------------

class TaxTarrif
{

private:
	char* meterType;
	double RegularUnitPrice;
	double PeakUnitPrice;
	double salesTax;
	double fixedCharges;

public:


	//Constructor
	TaxTarrif()
	{
		RegularUnitPrice = 0;
		PeakUnitPrice = 0;
		salesTax = 0;
		fixedCharges = 0;
		meterType = 0;
	}

	//Function to load Tariff Info from File
	void LoadTaxTariffInfo(ifstream& fin)
	{


		char temp[100];
		fin.getline(temp, 100, ',');
		meterType = Helper::GetStringFromBuffer(temp);


		fin >> RegularUnitPrice;
		fin.ignore();             // ignores ','

		if (meterType[0] == '3')
		{
			fin >> PeakUnitPrice;
			fin.ignore();          // ignores ','
		}
		else if (meterType[0] == '1')
		{
			PeakUnitPrice = 0;
			fin.getline(temp, 100, ',');  // to read empty space ", ,"
		}

		fin >> salesTax;
		fin.ignore();          // ignores ','
		fin >> fixedCharges;
		fin.ignore();          // ignores '\n'

	}

	//Function to update the already existing file of TariffInfo
	void UpdateFile(ofstream& fout)
	{
		fout << meterType;
		fout << ",";
		fout << RegularUnitPrice;
		fout << ",";

		if (meterType[0] == '3')
		{
			fout << PeakUnitPrice;
			fout << ",";
		}
		else if (meterType[0] == '1')
		{

			fout << " ,";
		}

		fout << salesTax;
		fout << ",";
		fout << fixedCharges;
		fout << "\n";
	}

	//SETTERS
	void SetRegularPrice(double price)
	{
		RegularUnitPrice = price;
	}

	void SetPeakPrice(double price)
	{
		PeakUnitPrice = price;
	}

	void SetSalesTax(double tax)
	{
		salesTax = tax;
	}

	void SetFixedCharges(double price)
	{
		fixedCharges = price;
	}

	//Function to print the Tariff Info.
	void PrintTariff()
	{
		cout<<endl;
		cout<<"\n		     ******TARIFF TAX*******\n";
		cout << "Fixed Charges : " << fixedCharges << endl << endl;
		cout << "Sales Tax : " << salesTax << endl;
	}
};


//------------------------------------------------------------------------------------------------------------------
//											CLASS LESCO
//------------------------------------------------------------------------------------------------------------------



class Lesco
{

private:

	Employee**  employeeList;
	Customer**  customerList;
	TaxTarrif** TaxInfo;
	BillingInfo** ListOfCustomerBills;

	int Total_Customers;
	int Total_Employees;
	int noOfCustomerBills;
	int password_Index;

public:


	//Default Constructor
	Lesco()
	{

		employeeList = new Employee*[100];
		customerList = new Customer*[100];
		TaxInfo		 = new TaxTarrif*[4];

		ListOfCustomerBills = new BillingInfo*[100];

		noOfCustomerBills = 0;
		Total_Customers   = 0;
		Total_Employees   = 0;
		password_Index    = 0;

	}

	//This is used to load all the data from .txt files 
	void LoadAllData()
	{
		ifstream IN("EmployyeesData.txt");

		int i = 0;
		if(IN.is_open())
		{
			while (!IN.eof())
			{
				employeeList[i] = new Employee;
				employeeList[i]->LoadEmployee(IN);
				i++;
			}
		}
		else
		{
			cout<<"\nThe desired file is not opened.\n";
		}
		Total_Employees = i - 1;


		ifstream fin("CustomerInfo.txt");
 
		if(fin.is_open())
		{

			i = 0;
			while (!fin.eof())
			{
				customerList[i] = new Customer;
				customerList[i]->LoadCustomerInfo(fin);
				i++;
			}

		}
		else
		{
			cout<<"\nThe desired file is not opened.\n";
		}

		Total_Customers = i - 1;

		i = 0;
		
		ifstream billIN("BillingInfo.txt");

		if (billIN.is_open())
		{
			while (!billIN.eof())
			{
				ListOfCustomerBills[i] = new BillingInfo;
				ListOfCustomerBills[i]->LoadBillInfo(billIN);
				i++;
			}
		}
		else
		{
			cout<<"\nThe desired file is not opened.\n";
		}

		noOfCustomerBills = i - 1;


		ifstream fin_("TariffTaxInfo.txt");

		i = 0;

		if (fin_.is_open())
		{
			while (!fin_.eof())
			{
				TaxInfo[i] = new TaxTarrif;
				TaxInfo[i]->LoadTaxTariffInfo(fin_);
				i++;
			}
		}
		else
		{
			cout<<"\nThe desired file is not opened.\n";
		}


	}

	//Creates assosiation of Customers with billing files 
	void AssociateUserToBills()
	{

			for (int i = 0; i < Total_Customers; i++)
			{

				bool isFound = false;

				for (int j = 0; j < noOfCustomerBills && !isFound; j++)
				{
						bool IDMatches = true;

						int *id_1 = customerList[i]->GetID();								//accesing ids of customer and bills
						int	*id_2 = ListOfCustomerBills[j]->GetCustomerId();

						for (int i = 0; i < 4; i++)
						{
							if (id_1[i] != id_2[i])
							{
								IDMatches = false;
							}
						}


						if (IDMatches)
						{
							//using setters and getters to set the bill in customer class

							customerList[i]->SetBillInfo(ListOfCustomerBills[j]);											    //customers bill 

							customerList[i]->GetBillInfo()->SetCurrrentRegularUnits(customerList[i]->GetCurrentRegularUnits()); //regular units

							customerList[i]->GetBillInfo()->SetCurrrentPeakUnits(customerList[i]->GetCurrentPeakUnits());		//peak units

							isFound = true;
						}

				}

			}

	}

	//Creates assosiation of Bill Information with Tariff Taxes
	void AssociateBillingToTax()
	{

			for (int i = 0; i < Total_Customers; i++)
			{

				char* userType = customerList[i]->GetCustomerType();			//commercial or domestic
				char* meterType = customerList[i]->GetMeterType();				//1Phase or 3Phase
						

				//'d' for domestic, 'c' for commercial , '1' for single phase and '3' for three phase
				if (userType[0] == 'd' && meterType[0] == '1')
				{
					customerList[i]->GetBillInfo()->SetInfoOfTax(TaxInfo[0]);
				}

				else if (userType[0] == 'c' && meterType[0] == '1')
				{
					customerList[i]->GetBillInfo()->SetInfoOfTax(TaxInfo[1]);
				}

				else if (userType[0] == 'd' && meterType[0] == '3')
				{
					customerList[i]->GetBillInfo()->SetInfoOfTax(TaxInfo[2]);
				}

				else if (userType[0] == 'c' && meterType[0] == '3')
				{
					customerList[i]->GetBillInfo()->SetInfoOfTax(TaxInfo[3]);
				}


			}

	}

	//Function to calculate the bill using bill and customer information
	void CalculateBill()
	{
			double bill;

			for (int i = 0; i < Total_Customers; i++)
			{
				bill = customerList[i]->GetBillInfo()->CalculateBill();			//Calculate bill is in Billing Info class

				customerList[i]->GetBillInfo()->SetTotalBillAmount(bill);		//sets the total bill

			}

	}

	//function to update Billing and Customer Information in .txt file  
	void UpdateBillingInfoFile()
	{

			ofstream fout("BillingInfo.txt");
			ofstream out("CustomerInfo.txt");

			for (int i = 0; i < Total_Customers; i++)
			{
																			
				customerList[i]->GetBillInfo()->UpdateBillInfo(fout);			
				customerList[i]->UpdateCustomerFile(out);

			}

	}

	//change the bill status (Paid or Unpaid)
	void UpdateBillStatus()
	{
		
			int Customer_ID;
			double Regular_Reading = 0;
			double Peak_Reading = 0;
			int PaymentDate;

			cout << "\n\nEnter the ID of Customer(4 Digits) to update the Billing Information:	";
			cin >> Customer_ID;

			cout << "Enter the date for Payment (YYYYMMDD):   ";
			cin >> PaymentDate;

			int enteredCustomer_Id[4];

			for (int i = 0; i < 4; i++)
			{
				enteredCustomer_Id[i] = 0;						//initializing to 0
			}

			
			for (int i = 3, mod = 0; Customer_ID != 0; i--)		
			{
				mod = Customer_ID % 10;
				enteredCustomer_Id[i] = mod;
				Customer_ID = Customer_ID / 10;

			}


			bool found = false;

			for (int i = 0; i < noOfCustomerBills && !found; i++)
			{
					int * existingCustomer_Id = customerList[i]->GetID();						//id of customer already in the file

					found = true;

					for (int i = 0; i < 4; i++)
					{

							if (enteredCustomer_Id[i] != existingCustomer_Id[i])
							{
								found = false;
							}

					}

					if (found)
					{
							customerList[i]->GetBillInfo()->CheckStatus();					  	//changes the status
									
							if (ListOfCustomerBills[i]->GetRegularReading() >= Regular_Reading)	
							{
								Regular_Reading = ListOfCustomerBills[i]->GetRegularReading();
							}

							if (ListOfCustomerBills[i]->GetPeakReading() >= Peak_Reading)
							{
								Peak_Reading = ListOfCustomerBills[i]->GetPeakReading();
							}


					}

				}

			   //sets the consumed units by the cutomers in .txt file to the current units after the payement of bills

				for (int i = 0; i < Total_Customers; i++)
				{
						char* meterType = customerList[i]->GetMeterType();
						int * existingCustomer_Id = customerList[i]->GetID();

						bool found = true;

						for (int i = 0; i < Total_Customers ; i++)
						{

								if (enteredCustomer_Id[i] != existingCustomer_Id[i])
								{
									found = false;
								}

						}

						if (found)
						{

							if (meterType[0] == '1')								//1 Phase meter
							{
								customerList[i]->SetRegularReading(Regular_Reading);
								customerList[i]->GetBillInfo()->SetPayementDate(PaymentDate);

							}

							if (meterType[0] == '3')							  //3 Phase meter
							{
								customerList[i]->SetRegularReading(Regular_Reading);
								customerList[i]->SetPeakUnits(Peak_Reading);
								customerList[i]->GetBillInfo()->SetPayementDate(PaymentDate);
							}
						}
				}

				UpdateBillingInfoFile();		//to print 

	}

	//In this, the total paid and unpaid reports is achieved
	void GetReports()
	{
			int unpaid_Bills = 0;
			int paid_Bills = 0;

			//counts the bills unpaid or paid
			for (int i = 0; i < noOfCustomerBills; i++)
			{

					if (ListOfCustomerBills[i]->GetStatus()[0] == 'U')
					{
						unpaid_Bills++;
					}

					if (ListOfCustomerBills[i]->GetStatus()[0] == 'P')
					{
						paid_Bills++;
					}

			}

			//Printing Information of Reports 

			cout << "Number of Paid Bills:	" << paid_Bills;
			cout << endl;

			cout << "Number of Unpaid Bills:	" << unpaid_Bills;
			cout << endl << endl;

		
			cout << "List of Customers who have paid Bills: \n\n\n";

			if (paid_Bills == 0)
			{
				cout << "All Bills are Paid. No unpaid bill.\n\n";
			}
			else
			{
				for (int i = 0; i < paid_Bills; i++)
				{
						if (ListOfCustomerBills[i]->GetStatus()[0] == 'P')
						{

							cout << "Customer Id:	" << ListOfCustomerBills[i]->GetCustomerId() 
    							 << "	, Customer Name: " << customerList[i]->GetName();

						}
						cout << endl;
				}
			}

			cout << endl << endl;
			cout << "List of Customers who have not paid Bills: \n\n\n";

			if (unpaid_Bills == 0)
			{
				cout << "All Bills are UnPaid. No bill.payed yet.\n\n";
			}
			else
			{

				for (int i = 0; i < unpaid_Bills + 1; i++)
				{
						if (ListOfCustomerBills[i]->GetStatus()[0] == 'U')
						{

							cout << "Customer Id:	" << ListOfCustomerBills[i]->GetCustomerId()
						  		 << "	, Customer Name: " << customerList[i]->GetName();

						}
						cout << endl;
				}

			}

	}

	//Function to ask user to change the Tariff files information and set it
	void UpdateTarriffFile()
	{
			char* temp;
			char buffer[100];
			double RegularUnitPrice;
			double PeakUnitPrice;
			double salesTax;
			double fixedCharges;


			cout << "For which Phase do You want to update the Tariff File: \n\n";
			cout << "Enter Phase(1 or 3):   ";
			cin >> buffer;
			temp = Helper::GetStringFromBuffer(buffer);

			cout << endl << "Enter Customer Type:(C or D)  ";
			cin >> buffer;
			cout << endl << endl;

			//temp represents the phase tyoe and C_Type is Customer Type

			char* C_Type = Helper::GetStringFromBuffer(buffer);

			if (temp[0] == '1' && C_Type[0] == 'D')
			{

					cout << "Enter Regular Units Price: ";
					cin >> RegularUnitPrice;

					cout << "\nEnter Sales Tax Percentage: ";
					cin >> salesTax;

					cout << "\nEnter Fixed Charges: ";
					cin >> fixedCharges;

					//setters

					TaxInfo[0]->SetRegularPrice(RegularUnitPrice);
					TaxInfo[0]->SetSalesTax(salesTax);
					TaxInfo[0]->SetFixedCharges(fixedCharges);

			}

			if (temp[0] == '1' && C_Type[0] == 'C')
			{

					cout << "Enter Regular Units Price: ";
					cin >> RegularUnitPrice;

					cout << "\nEnter Sales Tax Percentage: ";
					cin >> salesTax;

					cout << "\nEnter Fixed Charges: ";
					cin >> fixedCharges;

					//setters
					TaxInfo[1]->SetRegularPrice(RegularUnitPrice);
					TaxInfo[1]->SetSalesTax(salesTax);
					TaxInfo[1]->SetFixedCharges(fixedCharges);

			}

			if (temp[0] == '3' && C_Type[0] == 'D')
			{

					cout << "Enter Regular Units Price: ";
					cin >> RegularUnitPrice;

					cout << "\nEnter Peak Units Price: ";
					cin >> PeakUnitPrice;

					cout << "\nEnter Sales Tax Percentage: ";
					cin >> salesTax;

					cout << "\nEnter Fixed Charges: ";
					cin >> fixedCharges;

					//setters
					TaxInfo[2]->SetRegularPrice(RegularUnitPrice);
					TaxInfo[2]->SetPeakPrice(PeakUnitPrice);
					TaxInfo[2]->SetSalesTax(salesTax);
					TaxInfo[2]->SetFixedCharges(fixedCharges);

			}

			if (temp[0] == '3' && C_Type[0] == 'C')
			{

					cout << "Enter Regular Units Price: ";
					cin >> RegularUnitPrice;

					cout << "\nEnter Peak Units Price: ";
					cin >> PeakUnitPrice;

					cout << "\nEnter Sales Tax Percentage: ";
					cin >> salesTax;

					cout << "\nEnter Fixed Charges: ";
					cin >> fixedCharges;

					//setters
					TaxInfo[3]->SetRegularPrice(RegularUnitPrice);
					TaxInfo[3]->SetPeakPrice(PeakUnitPrice);
					TaxInfo[3]->SetSalesTax(salesTax);
					TaxInfo[3]->SetFixedCharges(fixedCharges);
			}

			UpdateTarrif();			//to update
	}

	//Function to update the txt file using Tariff class funcs
	void UpdateTarrif()
	{

			ofstream fout("TariffTaxInfo.txt");

			for (int i = 0; i < 4; i++)
			{
				TaxInfo[i]->UpdateFile(fout);
			}


	}

	//Function to add and login customer
	void SignUp()
	{

		int TempUserName;
		char Password[10];

		cout << "Input UserName:\t";
		cin >> TempUserName;

		cin.ignore();
		cout << "Input Password:\t";
		cin.getline(Password, 10, '\n');
		bool canCreate = false;
		bool isSame = false;
		for (int j = 0; j < Total_Employees && isSame == false; j++)
		{
			bool MatchUsername = 0;
			int* CustomerId = customerList[j]->GetID();

			if (TempUserName == 0)
			{
				if (CustomerId[3] == 0)
				{
					isSame = true;
				}
			}
			else
			{
				for (int i = 0, mod = 0; TempUserName != 0 && isSame == false; i--)
				{
					mod = TempUserName % 10;
					if (CustomerId[i] == mod)
					{
						isSame = true;
					}

					TempUserName = TempUserName / 10;
				}

			}



			if (isSame == false)
			{
				canCreate = true;
			}

		}
		if (!canCreate)
		{
			cout << "Can not Signup use different username\n\n";
		}
		else
		{
			char Temp[100];
			int *Id = customerList[Total_Customers - 1]->GetID();
			char* DOB = 0, *Name = 0, *Address = 0, *PhnNo = 0, *CustomerType = 0, *MeterType = 0, *ConnectionDate = 0;

			Helper::intAdd(Id);

			cout << "Enter customer Name :\t";
			cin.getline(Temp, 100, '\n');
			Name = Helper::GetStringFromBuffer(Temp);

			cout << "Enter customer Date of Birth :\t";
			cin.getline(Temp, 100, '\n');
			DOB = Helper::GetStringFromBuffer(Temp);

			cout << "Enter customer Address :\t";
			cin.getline(Temp, 100, '\n');
			Address = Helper::GetStringFromBuffer(Temp);

			cout << "Enter customer Phone Number of :\t";
			cin.getline(Temp, 100, '\n');
			PhnNo = Helper::GetStringFromBuffer(Temp);

			cout << "Enter customer Type :\t";
			cin.getline(Temp, 100, '\n');
			CustomerType = Helper::GetStringFromBuffer(Temp);

			cout << "Enter customer meter type :\t";
			cin.getline(Temp, 100, '\n');
			MeterType = Helper::GetStringFromBuffer(Temp);

			cout << "Enter customer Connection Date :\t";
			cin.getline(Temp, 100, '\n');
			ConnectionDate = Helper::GetStringFromBuffer(Temp);


			customerList[Total_Customers++] = new Customer(Id, DOB, Name, Address, PhnNo, CustomerType, MeterType, ConnectionDate, 0, 0);
			cout << "\nSuccesfully signed up \n\n";
		}


	}
	
	//function to print Customers bill Information
	void ViewCustomerInfo()
	{

		Customer* customer = CustomerSignIN();
		if (customer)
		{
			customer->GetBillInfo()->PrintBillInfo();
		}

	}

	//Function to sign in employees
	Employee* EmployeeSignIN()
	{
			Employee* EmployeeSignIn=0;

			char Temp[80];
			char Password[10];
			bool isFound = false;				

			cout << "Input UserName:\t";
			cin.ignore();
			cin.getline(Temp, 80,'\n');

			cout << "Input Password:\t";
			cin.getline(Password, 10, '\n');

			for (int j = 0; j < Total_Employees && !isFound; j++)
			{
				//checks if the employee exists or not 
				bool MatchUsername = Helper::StringCompare(Temp, employeeList[j]->GetUsername());
				bool MatchPassword = Helper::StringCompare(Password, employeeList[j]->GetPassword());

				if (MatchUsername == true && MatchPassword == true)
				{

					EmployeeSignIn=employeeList[j];
					password_Index=j;
					isFound = true;

				}

			}

			if (isFound)
			{
				cout << "\n\nSucessfully Signed in!\n\n";

			}
			else
			{
				cout << "\nIncorrect Username or password\n\n";
			}

			return EmployeeSignIn;
	}

	//Function to sign in Customers
	Customer* CustomerSignIN()
	{

			Customer* CustomerLoggedIn=0;

			int id, _username[4];
			char Password[10];
			bool isFound = false;

			cout << "Input UserName:\t";
			cin >> id;
			cin.ignore();

			cout << "Input Password:\t";
			cin.getline(Password, 10, '\n');

			for (int i = 0; i < 4; i++)
			{
				_username[i] = 0;
			}

			for (int i = 3, mod = 0; id != 0; i--)
			{
				mod = id % 10;
				_username[i] = mod;
				id = id / 10;

			}
			for (int j = 0; j < Total_Customers && isFound==false; j++)
			{

					bool MatchUsername = true;
					int* CustomerId = customerList[j]->GetID();

					for (int i = 0; i < 4; i++)
					{
						if (CustomerId[i] != _username[i])
						{
							MatchUsername = false;
						}
					}

					//checks if the password is correct or not(according to DOB)
					bool MatchPassword = Helper::StringCompare(Password, customerList[j]->GetDOB());

					if (MatchUsername == true && MatchPassword == true)
					{
						CustomerLoggedIn=customerList[j];
						isFound = true;
					}

			}

			if (isFound)
			{
				cout << "Sucessfully Signed In!\n\n";

			}
			else
			{
				cout << "\nIncorrect Username or password\n\n";

			}

			return CustomerLoggedIn;

	}

	//To input the password and set it 
	void EmployeesPassword()
	{

			char* Password;
			char* UpdatedPassword;
			char buffer[50];

			cout << "\n\nYou are Signed in as " << employeeList[password_Index]->GetUsername() << endl;

			cout << "Enter Old Password(maximum 8 characters):	";
			cin >> buffer;
			Password = Helper::GetStringFromBuffer(buffer);
	        
			if (Helper::StringCompare(Password, employeeList[password_Index]->GetPassword()) == true)
			{

					cout << "Enter New Password(maximum 8 characters):  ";
					cin >> buffer;
					UpdatedPassword = Helper::GetStringFromBuffer(buffer);

					employeeList[password_Index]->SetPassword(UpdatedPassword);				//setting the password 

			}
			else
			{

				cout << "\nThe Password entered is not correct\n.";

			}

			UpdatePassword();			//to update in file

	}

	//to update password in .txt file
	void UpdatePassword()
		{
			ofstream fout("EmployyeesData.txt");
			for (int i = 0; i < Total_Employees; i++)
			{
				employeeList[i]->UpdatePassword(fout);

			}
		}

	//Function to display each functunality
	void View()
	{
			char choice;

			cout<<"					     ---------\n"	;
			cout<<"                           *****************| SIGN IN |*****************\n";
			cout<<"					     ---------\n\n"	;
			cout<<"1.Employee Sign In\tPress E"<<endl;
			cout<<"2.Customer Sign In\tPress C"<<endl;
			cout<<"Enter option:		";

			bool isValidOption = false;
			bool isFound = false;
			bool notTrue = false;
			char input_Option;
			while (!isValidOption)
			{
				cin >> input_Option;
			
				if(input_Option=='E')
				{
			
					isValidOption = false;

					cout<<"					   ---------------\n"	;
					cout<<"                         *****************|EMPLOYEE PORTAL|*****************\n";
					cout<<"					   ---------------\n\n"	;
					

						Employee* SignedIn = EmployeeSignIN();

						if(SignedIn)
						{
							  
								int option;
								cout<<"					  ---------\n"	;
								cout<<"                         *****************|OPTIONS|*****************\n";
								cout<<"					  ---------\n\n"	;

								cout << "Enter 1: To Register New Customer\n";
								cout << "Enter 2: To Change Bill Status\n";
								cout << "Enter 3: View Customer info\n";
								cout << "Enter 4: Update Tarrif Tax Info \n";
								cout << "Enter 5: To Get Bills Report\n";
								cout << "Enter 6: Update Password \n";
								cout << "Enter 7: To Log Out\n";
								cout<<"\nEnter Option:	";

								cin >> option;
								while (option != 7)
								{
									if (option == 1)
									{
											cout<<"					   -----------------\n"	;
											cout<<"                         *****************|REGISTER CUSTOMER|*****************\n";
											cout<<"					   -----------------\n\n"	;

											SignUp();
											cout<<"\nCustomer is successfully Signed UP"<<endl;
		
									}

									if (option == 2)
									{
											cout<<"					   ------------\n"	;
											cout<<"                         *****************|BILL STATUS|*****************\n";
											cout<<"					   ------------\n\n"	;
											UpdateBillStatus();
											cout<<"\n\nBill Status Has Been Updated"<<endl;
								

									}

									if (option == 3)
									{
											cout<<"					   --------------------\n"	;
											cout<<"                         *****************|CUSTOMER INFORMATION|*****************\n";
											cout<<"					   --------------------\n\n"	;

											ViewCustomerInfo();

									}

									if (option == 4)
									{

										    cout<<"					   -----------------\n"	;
											cout<<"                         *****************|UPDATE TARIFF TAX|*****************\n";
											cout<<"					   -----------------\n\n"	;
											UpdateTarrif();
											cout<<"Tariff Info has been Successfully Updated!"<<endl;
									}

									if (option == 5)
									{
											cout<<"					   ------------\n"	;
											cout<<"                         *****************|BILL REPORT|*****************\n";
											cout<<"					   -------------\n\n"	;
									     	GetReports();
									}

									if (option == 6)
									{
											cout<<"					  ----------------\n"	;
											cout<<"                         *****************|UPDATE PASSWORD|*****************\n";
											cout<<"					  ----------------\n\n"	;
											EmployeesPassword();
								
									}


									
									cout<<"					  ---------\n"	;
									cout<<"                         *****************|OPTIONS|*****************\n";
									cout<<"					  ---------\n\n"	;
									
									cout << "Enter 1: To Register New Customer\n";
									cout << "Enter 2: To Change Bill Status\n";
									cout << "Enter 3: View Customer info\n";
									cout << "Enter 4: Update Tarrif Tax Info \n";
									cout << "Enter 5: To Get Bills Report\n";
									cout << "Enter 6: Update Password \n";
									cout << "Enter 7: To Log Out\n";
									cout << "\nEnter Option:	";
									cin >> option;

								}
								if(option == 7)
								{
									cout<<"\nEmployee Successfully Log Out!\n";
									cout<<"					     ---------\n"	;
									cout<<"                           *****************| SIGN IN |*****************\n";
									cout<<"					     ---------\n\n"	;
									cout<<"1.Employee Sign In\tPress E"<<endl;
									cout<<"2.Customer Sign In\tPress C"<<endl;
									cout<<"Enter option:		";
								}
							}
							
						
				}

					

					

				if(input_Option=='C')
				{
					

						cout<<"					   ---------------\n"	;
						cout<<"                         *****************|CUSTOMER PORTAL|*****************\n";
						cout<<"					   ---------------\n\n"	;
					

				

						Customer*  customer_signin=CustomerSignIN();
						cout<<"					   --------------------\n"	;
						cout<<"                         *****************|BILLING INFORMATION|*****************\n";
						cout<<"					   --------------------\n\n"	;
					    cout<<"\n---------------------------------------------------------------------------------\n";
						customer_signin->PrintCustomer();
					    
						customer_signin->GetBillInfo()->GetTarif()->PrintTariff();

						cout<<"\n---------------------------------------------------------------------------------\n-";


						
					
				}
			}
			
		
	}
			



							
							
				

	};



	int main()
	{
		system("color 80");
		cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "                                         LESCO BILL CALCULATOR                                           " << endl;
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Made By CodeXOwls\n\n";

		Lesco l;

		l.LoadAllData();
		
		l.AssociateUserToBills();
		l.AssociateBillingToTax();
		
		l.View();
		
		system("pause");

	}