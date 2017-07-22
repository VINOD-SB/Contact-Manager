	#include<fstream>
	#include<ctype.h>
	#include<iostream>
	#include<string.h>
	#include<conio.h>
	using namespace std;
	int password=1234;
/********************************************************************************/

/* class name: Contact
   Data members: name, phone no, email id, category
   function: to store member details */



	class Contact
	{
	private:

		char name[20];
		char phone[20];
		char email[40];
		char category[20];
		//static int password=1234;
	public:

    	void setcategory(char cat[]);
	friend istream & operator >> ( istream &in , Contact &arg);
	friend ostream & operator << ( ostream &out , Contact &arg );
	char *getcategory();
	char * getName();
	char getFirstLetter();
	void store_email(int a);
	char * getemail();
	};



/*******************************************************************************/

/* FUNCTION NAME: setcategory
   INPUT : category data member
   OUTPUT : NULL
   FUNCTION : sets the category of member  */


    void Contact :: setcategory(char cat[])
        {
           // for(int i=0;i<20;i++)
            //    category[i]=cat[i];
            strcpy(category,cat);
        }

/* FUNCTION NAME: >>
   INPUT : reference to cin, reference to object
   OUTPUT : cin
   FUNCTION : store the detail of members from standard input like keyboard
   Logic : operator overloading  */

	istream & operator >> ( istream &in , Contact &arg)
	{

        cout << "Enter name and phone \n";
        in >> arg.name >> arg.phone;
        strupr( arg.name );
        return in;

	}

/* FUNCTION NAME: <<
   INPUT : reference to cout, reference to object
   OUTPUT : cout
   FUNCTION : outputs the details of the members in contact to standard output device like monitor
   Logic : operator overloading  */


	ostream & operator << ( ostream &out , Contact &arg )
	{
	  out << arg.name << "\t\t" << arg.phone << "\t\t" << arg.email << endl;
	  return out;
	}


/* FUNCTION NAME: getcategory
   INPUT : void
   OUTPUT : string
   FUNCTION : returns the category type*/


    char* Contact :: getcategory()
    {
        return category;
    }



/* FUNCTION NAME: getname
   INPUT : void
   OUTPUT : string
   FUNCTION : returns the name of contact member*/




	char* Contact :: getName()
	{
	  return name;
	}


/* FUNCTION NAME: getFirstLetter
   INPUT : void
   OUTPUT : character
   FUNCTION : returns first letter of the name of contact member*/


	char Contact :: getFirstLetter()
	{
	 return name[0];
	}


/* FUNCTION NAME: store_email
   INPUT : integer
   OUTPUT : void
   FUNCTION : get the email id from std input*/


	void Contact :: store_email(int a)
	{
	    if(a==1)
	    {
	        cin >> email;

	        strlwr(email);
	    }

	    else if(a==2)
        {
            strcpy(email,"--------------");
        }
	}


/* FUNCTION NAME: getemail
   INPUT : void
   OUTPUT : string
   FUNCTION : returns the email_id of contact member*/

    char* Contact :: getemail()
	{
	  return email;
	}





/*******************************************************************************/

/* CLASS NAME: AddressBook
   FUNCTION : adds, delete , edit, display , total no of members in
               the contact all these functions will be done*/


	class AddressBook
	{
	private:

		int getCount();


	public:

		void Add();
		void selectcategory(int i, Contact &c);
		void Display();
		void Display(char name[ ]);
		void Display(char letter );
		void ContextSearch( char name[ ] );
		void category_search(char cat[ ]);
		void del(char name[]);
		void delall();
		void del(int no);
		void edit (int index);
		void email_id(Contact &c);
		void email_search( char mail[] );
		void change_cat(int index);
		void vipoption();
		void edit_vip(int index);
		void del_vip(int index);
		void cat_vip(int index);
	};



/*******************************************************************************/

/* FUNCTION NAME: getcount
   INPUT : void
   OUTPUT : integer
   FUNCTION : returns the count of total no of members in memory*/


int AddressBook :: getCount()
		{
		  ifstream fp;
		  fp.open( "contactdb.dat", ios::in );
		  fp.seekg( 0 , ios::end );
		  int recs = fp.tellg()  / sizeof( Contact );
		  fp.close();
		  return recs;
		 }



/* FUNCTION NAME: selectcategory
   INPUT : integer , object to Contact
   OUTPUT : void
   FUNCTION : this is to select the category of newly adding member to memory*/


void AddressBook :: selectcategory(int i,Contact &c)
    {
        int ch;
        long int pin;

        cout <<"choose category of contact "<<i<<" : "<<endl;
        cout <<"1.Family \n";
        cout <<"2.Friends\n";
        cout <<"3.Co-worker\n";
        cout <<"4.vip\n";
        cin  >>ch;
        switch(ch)
            {
            case 1:
                //char cat[]="family";
                c.setcategory("family");
                break;


            case 2:

                {
                char cat[]="friends";
                c.setcategory(cat);
                break;
                }


            case 3:
                {
                char cat[]="co-workers";
                c.setcategory(cat);
                break;
                }


            case 4:
              label:  {
                cout<<"enter 4 digit pin\n";
                cin>>pin;
                if(pin<9999)
                {
                    if(pin==password)
                    {
                        char cat[]="vip";
                        c.setcategory(cat);
                        break;
                    }
                    else
                    {
                        cout<<"incorrect pin\n";
                        return;
                    }
                }
                else
                {
                    cout<<"u entered more than 4 digit \n 1.try again \t 2.quite";
                    int b;
                    cin>>b;
                    if(b==1)
                        goto label;
                    else
                    return;

                }

                }
            }


    }



 /* FUNCTION NAME: Add
   INPUT : void
   OUTPUT : void
   FUNCTION : to add new members in contact and get their details*/



void AddressBook :: Add()
		{
		  Contact c;
		  int no;

		  cout<<"how many contacts yu need to add\n";
		  cin>>no;


          for(int i=1;i<=no;i++)

          {
            selectcategory(i,c);
            cin >> c;

            email_id(c);

            ofstream fp;
            fp.open("contactdb.dat", ios::app);


            /*we r writing into file in file everything is string and hence v
            hav char* and &c is address of c r reference to c object of contact
            i.e, writing a string of character from adress of c until its size*/


            fp.write( (char *)&c , sizeof(c) );
            fp.close();
		}


		}

/* FUNCTION NAME: Display
   INPUT : void
   OUTPUT : void
   FUNCTION : prints contact details of all the member */


    void AddressBook:: Display()
		{
		Contact c;
		int index = 1;
		int recs = getCount();
		ifstream fp;
		fp.open("contactdb.dat", ios::in);
		for(int i=1; i<=recs; i++)
		{

            fp.read( ( char *)&c , sizeof(c));
            if( stricmp( c.getcategory() , "vip" ) == 0 )
            {
               // cout<<"naanu bande";
            }
            else
            {

            cout<<index<<". ";
            cout << c;
            index++;
		}}
		fp.close();
		}


/* FUNCTION NAME: Display
   INPUT : string
   OUTPUT : void
   FUNCTION : display the contact details of the name we input*/


    void AddressBook :: Display(char name[ ])
		{
		Contact c;
		int recs = getCount();
		ifstream fp;
		fp.open("contactdb.dat", ios::in);
		for(int i=1; i<=recs; i++)
		{
		    // reading a sting of character of size c from file and store to object datamembers
		  fp.read( ( char *)&c , sizeof(c));
		 if( stricmp( c.getcategory() , "vip" ) == 0 )
          {

          }
          else
          {

		  if( stricmp( c.getName() , name ) == 0 )
			  cout << c;
          }
		}
		fp.close();
		}

/* FUNCTION NAME: Display
   INPUT : character
   OUTPUT : void
   FUNCTION : displays all the member details whose name starts with letter we input*/


		void AddressBook :: Display(char letter )
		{
		Contact c;
		long int pin;
		int recs = getCount();
		ifstream fp;
		fp.open("contactdb.dat", ios::in);
		for(int i=1; i<=recs; i++)
		{
		  fp.read( ( char *)&c , sizeof(c));
		   if( stricmp( c.getcategory() , "vip" ) == 0 )
          {

          }
          else
         {
		  if( c.getFirstLetter() == letter )
			  cout << c;
          }
		}
		fp.close();
		}


/* FUNCTION NAME: contextsearch
   INPUT : string
   OUTPUT : void
   FUNCTION : displays details of all the members whose name starts with strings we input*/


    void AddressBook :: ContextSearch( char name[ ] )
		{
		Contact c;
		int recs = getCount();
		ifstream fp;
		fp.open("contactdb.dat", ios::in);
		for(int i=1; i<=recs; i++)
		{
		  fp.read( ( char *)&c , sizeof(c));
		  if( stricmp( c.getcategory() , "vip" ) == 0 )
          {

          }
          else
          {
		  if( strstr( c.getName() , name ) != NULL )
			  cout << c;
		}}
		fp.close();
		}


/* FUNCTION NAME: category_search
   INPUT : string
   OUTPUT : void
   FUNCTION : displays all the member detail of input category*/


    void AddressBook :: category_search(char cat[ ])
		{
		Contact c;
		int counter=1;
		int recs = getCount();
		ifstream fp;
		fp.open("contactdb.dat", ios::in);
		for(int i=1; i<=recs; i++)
		{
		    // reading a sting of character of size c from file and store to object datamembers
		  fp.read( ( char *)&c , sizeof(c));
		  if( stricmp( c.getcategory() , cat ) == 0 )
          {
              cout << counter << ". ";
			  cout << c;
			  counter++;
		}}
		fp.close();
		}


/* FUNCTION NAME: del
   INPUT : string
   OUTPUT : void
   FUNCTION : deletes the member  detail with name we input from memory*/


    void AddressBook :: del(char name[])
		{

		    Contact c;
		    int rec = getCount();
		    ifstream fp;
		    ofstream pf;

		    fp.open("contactdb.dat", ios::in);
		    pf.open("new.dat",ios::app);


		    for(int i=1;i<=rec;i++)
            {
                 fp.read((char *)&c, sizeof(c));
                 if(stricmp(c.getName(),name)!=0)
                    pf.write((char *)&c,sizeof(c));
            }

            fp.close();
            pf.close();

            remove("contactdb.dat");
            rename("new.dat","contactdb.dat");


		}


/* FUNCTION NAME: del
   INPUT : void
   OUTPUT : integer
   FUNCTION : deletes the member details with index we input*/


    void AddressBook :: del(int index)
		{

		    Contact c;
		    int counter = 0;
		    int rec = getCount();
		    ifstream fp;
		    ofstream pf;

		    fp.open("contactdb.dat", ios::in);
		    pf.open("new.dat",ios::app);


		    for(int i=1;i<=rec;i++)
            {
                 fp.read((char *)&c, sizeof(c));

                if( stricmp( c.getcategory() , "vip" ) == 0 )
                      {
                          pf.write((char *)&c,sizeof(c));

                      }
                      else
                      {
                          ++counter;
                          if(counter!=index)
                            pf.write((char *)&c,sizeof(c));
                          else
                            continue;
                      }
                 }



            fp.close();
            pf.close();

            remove("contactdb.dat");
            rename("new.dat","contactdb.dat");


		}


/* FUNCTION NAME: delall
   INPUT : void
   OUTPUT : void
   FUNCTION : deletes the whole file we created*/


    void AddressBook :: delall()
		{

		    remove("contactdb.dat");

		}

/* FUNCTION NAME: edit
   INPUT : integer
   OUTPUT : void
   FUNCTION : update or edit the details of the member*/

   void AddressBook :: edit(int index)
    {

		    Contact c;
		    int counter=0;
		    int rec = getCount();
		    ifstream fp;
		    ofstream pf;

		    fp.open("contactdb.dat", ios::in);
		    pf.open("new.dat",ios::app);


		    for(int i=1;i<=rec;i++)
            {
                 fp.read((char *)&c, sizeof(c));

                if( stricmp( c.getcategory() , "vip" ) == 0 )
                {

                    pf.write((char *)&c,sizeof(c));
                }
                 else
                 {
                     ++counter;

                    if(i!=index)

                    pf.write((char *)&c,sizeof(c));

                    else
                    {
                    cout<<"Editing..............\n";

                    char* cat=c.getcategory();

                    cin >> c;

                    cout << "select your choice\n";

                    cout << "1.edit email_id\n";

                    cout << "2.same email_id\n";

                    int option;

                    cin >> option;

                    if(option==1)
                    {
                    cout << " Enter email_id"<< endl;

                    }

                    else

                        ++option;

                    c.store_email(option);

                    c.setcategory(cat);

                    pf.write((char *)&c, sizeof(c));
                }
            }}

            fp.close();
            pf.close();

            remove("contactdb.dat");
            rename("new.dat","contactdb.dat");

    }



/* FUNCTION NAME: getname
   INPUT : void
   OUTPUT : string
   FUNCTION : returns the name of contact member*/


 void AddressBook :: email_id(Contact &c)
 {
     cout << "select your choice\n";

     cout << "1.add email_id\n";

     cout << "2.no email_id\n";

     int option;

     cin >> option;

     if(option==1)
     {
         cout << " Enter email_id"<< endl;
     }

     c.store_email(option);

 }


/* FUNCTION NAME: email_search
   INPUT : string
   OUTPUT : void
   FUNCTION : search the details of the member by giving mail id*/


    void AddressBook :: email_search( char mail[] )
		{
		Contact c;
		int recs = getCount();
		ifstream fp;
		fp.open("contactdb.dat", ios::in);
		for(int i=1; i<=recs; i++)
		{
		  fp.read( ( char *)&c , sizeof(c));
		  if( stricmp( c.getcategory() , "vip" ) == 0 )
          {

          }
          else
          {
		  if( strstr( c.getemail() , mail ) != NULL )
			  cout << c;
		}}
		fp.close();
		}


/* FUNCTION NAME: change_cat
   INPUT : integer
   OUTPUT : void
   FUNCTION : to change category of a contact from one category to another*/

     void AddressBook :: change_cat(int index)
     {

		    Contact c;
		    int counter=0;
		    int rec = getCount();
		    int choice , pin;
		    ifstream fp;
		    ofstream pf;

		    fp.open("contactdb.dat", ios::in);
		    pf.open("new.dat",ios::app);


		    for(int i=1;i<=rec;i++)
            {
                 fp.read((char *)&c, sizeof(c));
                if( stricmp( c.getcategory() , "vip" ) == 0 )
                {
                    pf.write((char *)&c,sizeof(c));
                }
                else
                {
                    ++counter;
                    if(counter!=index)
                    pf.write((char *)&c,sizeof(c));


                    else
                    {

                    char* cat=c.getcategory();
                    cout<< "FROM "<< cat << " to " << endl;
                    if( stricmp( c.getcategory() , "family" ) == 0 )
                    {
                        cout << "1.friends\n";
                        cout << "2.co-workers\n";
                        cout << "3.vip\n";

                        cin >> choice;

                        switch (choice)
                        {
                        case 1:
                            c.setcategory("friends");
                             pf.write((char *)&c, sizeof(c));
                             break;


                        case 2:
                             c.setcategory("co-workers");
                             pf.write((char *)&c, sizeof(c));
                             break;


                        case 3:
                             c.setcategory("vip");
                             cout<< "enter 4 digit pin\n";
                             cin>>pin;
                             if(pin==password)
                             {
                                 pf.write((char *)&c, sizeof(c));
                             }
                             else
                             {
                                 cout << "incorrect password\n";
                             }
                             break;
                        }


                    }


                    else if( stricmp( c.getcategory() , "friends" ) == 0 )
                    {
                        cout << "1.family\n";
                        cout << "2.co-workers\n";
                        cout << "3.vip\n";

                        cin >> choice;

                        switch(choice)
                        {
                        case 1:
                            c.setcategory("family");
                             pf.write((char *)&c, sizeof(c));
                             break;


                        case 2:
                             c.setcategory("co-workers");
                             pf.write((char *)&c, sizeof(c));
                             break;


                        case 3:
                             c.setcategory("vip");
                             cout<< "enter 4 digit pin\n";
                             cin>>pin;
                             if(pin==password)
                             {
                                 pf.write((char *)&c, sizeof(c));
                             }
                             else
                             {
                                 cout << "incorrect password\n";
                             }
                             break;
                        }


                    }


                    else if( stricmp( c.getcategory() , "co-workers" ) == 0 )
                    {
                        cout << "1.friends\n";
                        cout << "2.family\n";
                        cout << "3.vip\n";

                        cin >> choice;

                        switch (choice)
                        {
                        case 1:
                            c.setcategory("friends");
                             pf.write((char *)&c, sizeof(c));
                             break;


                        case 2:
                             c.setcategory("family");
                             pf.write((char *)&c, sizeof(c));
                             break;


                        case 3:
                             c.setcategory("vip");
                             cout<< "enter 4 digit pin\n";
                             cin>>pin;
                             if(pin==password)
                             {
                                 pf.write((char *)&c, sizeof(c));
                             }
                             else
                             {
                                 cout << "incorrect password\n";
                             }
                             break;
                        }


                    }


                }
            }}

            fp.close();
            pf.close();

            remove("contactdb.dat");
            rename("new.dat","contactdb.dat");
     }



/* FUNCTION NAME: vipoption
   INPUT : void
   OUTPUT : void
   FUNCTION : more operation on vip contact list*/

 void AddressBook :: vipoption()
 {
     int index;
     int choice;

     cout<<"\n Choose ur option \n";
     cout << "1.Edit a contact\n";
     cout << "2.Delete a contact\n";
     cout << "3.change category\n";
     cout << "4.add new contact\n";
     cout << "5.back\n";

     cin>>choice;

     if(choice==1)
     {
         cout<<"Enter the index of contact needed to edit\n";

         cin>>index;

         edit_vip(index);
     }

     else if (choice == 2)
     {
         cout<<"Enter the index of contact needed to delete\n";

         cin>>index;

         del_vip(index);
     }

     else if (choice == 3)
     {
         cout<< "Enter the index of contact to change category\n";

         cin >> index;

         cat_vip(index);
     }

    else if (choice==4)
    {
            Contact c;
            c.setcategory("vip");
            cin >> c;

            email_id(c);

            ofstream fp;
            fp.open("contactdb.dat", ios::app);


            /*we r writing into file in file everything is string and hence v
            hav char* and &c is address of c r reference to c object of contact
            i.e, writing a string of character from adress of c until its size*/


            fp.write( (char *)&c , sizeof(c) );
            fp.close();

    }
     else
     {
         return;
     }
 }


/* FUNCTION NAME: edit_vip
   INPUT : integer
   OUTPUT : void
   FUNCTION : to edit vip contact*/

 void AddressBook :: edit_vip(int index)
 {
            Contact c;
            int counter=0;
		    int rec = getCount();
		    ifstream fp;
		    ofstream pf;

		    fp.open("contactdb.dat", ios::in);
		    pf.open("new.dat",ios::app);


		    for(int i=1;i<=rec;i++)
            {
                 fp.read((char *)&c, sizeof(c));

                if( stricmp( c.getcategory() , "vip" ) == 0 )
                {
                    ++counter;
                    if(counter==index)
                    {
                    cout<<"Editing..............\n";

                    char* cat=c.getcategory();

                    cin >> c;

                    cout << "select your choice\n";

                    cout << "1.edit email_id\n";

                    cout << "2.same email_id\n";

                    int option;

                    cin >> option;

                    if(option==1)
                    {
                    cout << " Enter email_id"<< endl;

                    }

                    else

                        ++option;

                    c.store_email(option);

                    c.setcategory(cat);

                    pf.write((char *)&c, sizeof(c));
                    }

                    else
                        pf.write((char *)&c , sizeof(c));
                }
                 else

                    pf.write((char *)&c,sizeof(c));

            }

            fp.close();
            pf.close();

            remove("contactdb.dat");
            rename("new.dat","contactdb.dat");
 }



/* FUNCTION NAME: del_vip
   INPUT : integer
   OUTPUT : void
   FUNCTION : to delete a vip contact*/

 void AddressBook :: del_vip(int index)
 {
		    Contact c;
		    int counter=0;
		    int rec = getCount();
		    ifstream fp;
		    ofstream pf;

		    fp.open("contactdb.dat", ios::in);
		    pf.open("new.dat",ios::app);


		    for(int i=1;i<=rec;i++)
            {
                 fp.read((char *)&c, sizeof(c));

                 if( stricmp( c.getcategory() , "vip" ) == 0 )
                {
                    ++counter;
                    if(counter==index)
                    {

                    }
                    else

                    pf.write((char *)&c,sizeof(c));
                }

                 else
                   {
                       pf.write((char *)&c,sizeof(c));
                   }
            }

            fp.close();
            pf.close();

            remove("contactdb.dat");
            rename("new.dat","contactdb.dat");



 }



/* FUNCTION NAME: cat_vip
   INPUT : integer
   OUTPUT : void
   FUNCTION : to change category of a contact from vip category to other*/


 void AddressBook :: cat_vip(int index)
 {
		    Contact c;
		    int rec = getCount();
		    int counter =0;
		    int choice , pin;
		    ifstream fp;
		    ofstream pf;

		    fp.open("contactdb.dat", ios::in);
		    pf.open("new.dat",ios::app);


		    for(int i=1;i<=rec;i++)
            {
                fp.read((char *)&c, sizeof(c));
                if( stricmp( c.getcategory() , "vip" ) == 0 )
                {
                    ++counter;

                    if(counter!=index)
                        pf.write((char *)&c,sizeof(c));
                    else
                    {

                        char* cat=c.getcategory();
                        cout<< "FROM "<< cat << " to " << endl;
                        cout << "1.family\n";
                        cout << "2.friends\n";
                        cout << "3.co-workers\n";

                        cin >> choice;

                        switch (choice)
                        {
                        case 1:
                            c.setcategory("family");
                             pf.write((char *)&c, sizeof(c));
                             break;


                        case 2:
                             c.setcategory("friends");
                             pf.write((char *)&c, sizeof(c));
                             break;


                        case 3:
                             c.setcategory("co-workers");
                             pf.write((char *)&c, sizeof(c));
                             break;
                        }


                    }

                    }
                    else
                        pf.write((char *)&c, sizeof(c));

                }


            fp.close();
            pf.close();

            remove("contactdb.dat");
            rename("new.dat","contactdb.dat");

 }





/*******************************************************************************/



	int main()
	{
	   int ch;
	   char name[20] , letter;
	   AddressBook book;
	  // book.ascending();
	   while( 1 )
	   {
	       //clrscr();


	       cout << "\n \n1. Add new contact \n";

	       cout << "2. Display contacts\n";

	       cout << "3. Search by name \n";

	       cout << "4. Context search\n";

	       cout << "5. search using first alphabet\n";

	       cout << "6. category search\n";

	       cout << "7. delete contacts\n";

	       cout << "8. edit contact\n";

	       cout << "9.search through email_id\n";

	       cout << "10.change category of a contact\n";

	       cout << "11.Enter vip\n";

	       cout << "12. Exit\n";

	       cin >> ch;


		switch( ch )
		{
            case 1:
                book.Add();
                break;


            case 2:
                book.Display();
                break;


            case 3:
                cout << "Enter name\n";
                cin.ignore();
                cin.getline( name , 20 );
                book.Display( name );
                break;


            case 4:
                cout << "Enter name\n";
                cin.ignore();

                cin.getline( name , 20 );
                strupr( name );
                book.ContextSearch( name );
                break;


            case 5:
                cout << "Enter first alphabet for index search " << endl;
                cin >> letter;
                letter = toupper( letter );
                book.Display( letter );
                break;


            case 6:
                int ch;
                cout <<"choose category: \n";
                cout <<"1.Family \n";
                cout <<"2.Friends\n";
                cout <<"3.Co-worker\n";
                cout <<"4.vip\n";
                cin  >>ch;
                switch(ch)
                {

                    case 1:
                        book.category_search("family");
                        break;

                    case 2:
                        book.category_search("friends");
                        break;


                    case 3:
                        book.category_search("co-workers");
                        break;

                    case 4:
                        cout<<"enter pin\n";
                        unsigned long int pin;
                        cin>>pin;
                        if(pin==password)
                        {
                            book.category_search("vip");
                            break;
                        }
                        else
                        {
                            cout<<"incorrect pin\n";
                            break;
                        }
                    }
                break;



            case 7:
                cout<<"choose delete options"<<endl;
                int c;
                cout<<"1. delete all \n";
                cout<<"2. delete specific \n";
                cin>>c;
                switch(c)
                {
                    case 1:
                        book.delall();
                        break;

                    case 2:
                        int no;
                        cout<<"enter option\n";
                        cout<<"1. delete by index\n";
                        cout<<"2. delete by name\n";
                        cin>>no;
                        if(no==2)
                        {


                            //char name[]
                            book.Display();
                            cout<<"enter name of contact needed to be delete"<<endl;
                            cin.ignore();
                            cin.getline( name , 20 );
                            book.del(name);
                            book.Display();
                            break;
                        }
                        else
                        {
                            book.Display();
                            cout<<"enter index no\n"<<endl;
                            int ind;
                            cin >> ind;
                            book.del(ind);

                        }
                }


                break;



            case 8:
                book.Display();
                cout<<"enter index of contact needed to edit\n";
                int ind;
                cin>>ind;
                book.edit(ind);
                break;



           case 9:

                char mail[40];
                cout << "Enter email_id\n";
                cin.ignore();

                cin.getline( mail , 20 );
                strlwr( mail );
                book.email_search(mail);
                break;


           case 10:

                book.Display();
                cout<<"enter index of contact to change category\n";
                int index;
                cin>>index;
                book.change_cat(index);
                break;

           case 11:
                        cout<<"enter pin\n";
                        unsigned int pin;
                        cin>>pin;
                        if(pin==password)
                        {
                            book.category_search("vip");
                            book.vipoption();
                        }
                        else
                        {
                            cout<<"incorrect pin\n";
                            break;
                        }

                break;

            case 12:

                return 0;
            }

            getch();
	     }


    }









