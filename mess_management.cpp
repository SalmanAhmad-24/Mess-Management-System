#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int rctr = 0; //Global variable to keep tract of number of rows
string all_data[100][5]; //(Global Variable) 2D string array of 100 rows and 5 columns
bool found;
int choice;
void read(string fname);
void write(string fname);
void search();
bool search(string reg_num);
void sorting();
void display();
void registration();
void status();
void delete_student();
void count();
void call_bill();
int main()
{
    string fname, reg_num;
    bool again = true;
    //Note: The data file should be pasted in the code file (.cpp) directory
    cout << "Enter file name with extension: ";
    cin >> fname;
    read(fname);
    while (again)
    {
        cout << endl;
        system("pause");
        system("cls");
        cout << "Select your choice: " << endl;
        cout << "0. Exit" << endl;
        cout << "1. Search a student" << endl;
        cout << "2. Registration" << endl;
        cout << "3. Count status " << endl;
        cout << "4. Delete student record" << endl;
        cout << "5. Change status" << endl;
        cout << "6. Calculate bills" << endl;
        cout << "7. Display all students" << endl;
        cin >> choice;
        switch (choice)
        {
        case 0:
            cout << "Case 0 called ..." << endl;
            write("data.csv");
            again = false;
            break;
        case 1:
            search();
            break;
        case 2:
            registration();
            break;
        case 3:
            count();
            break;
        case 4:
            delete_student();
            break;
        case 5:
            status();
            break;
        case 6:
            call_bill();
            break;
        case 7:
            display();
            break;
        default:
            cout << "Invalid option" << endl;
        }

    }


}
void registration()
{
    
    cout << "Enter reg no: " << endl;
    cin >> all_data[rctr][0];
    cout << "Enter Name: " << endl;
    cin >> all_data[rctr][1];
    all_data[rctr][2] = "0";
    all_data[rctr][3] = "Out";
    all_data[rctr][4] = "0";
    rctr++;
    sorting();
    write("data.csv");
    
}
void status()
{
    string reg_no;
    int std_index;
    int option;
    cout << "Status" << endl << endl;
    cout << "Enter your Reg No: " << endl;
    cin >> reg_no;
    if (search(reg_no))
    {
        for (int i = 0; i < rctr; i++)
        {
            if (all_data[i][0] == reg_no)
            {
                std_index = i;
                break;
            }
        }
        cout << "Hello " << all_data[std_index][1];
        cout << ", Your current mess status is " << all_data[std_index][3];
        cout << " Do you want to change your status " << endl;
        cout << "1. Yes" << endl;
        cout << "2. No" << endl;
        cin >> option;
        if (option == 1)
        {
            cout << "Enter your mess status: ";
            cin >> all_data[std_index][3];
            //if(all_data[std_index][3] == "in") // 4 posibilities
            //all_data[std_index][4]++;
        }
        write("data.csv");
        cout << "Your status has been changed successfully." << endl;
    }
    else {
        cout << "Sorry you are not register with us." << endl;
    }

}
void delete_student()
{
    string reg;
    int std_index;
    cout << "Enter your reg no: ";
    cin >> reg;
    for (int i = 0; i < rctr; i++)
    {
        if (all_data[i][0] == reg)
        {
            std_index = i;
            break;
        }
    }
    for (int i = std_index; i < rctr - 1; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            all_data[i][j] = all_data[i + 1][j];
        }
    }
    rctr--;
    for (int i = 0; i < rctr; i++)
        cout << all_data[i][0] << endl;
    write("data.csv");


}

void call_bill()
{
    string reg_no;
    cout << "Enter your Reg No: ";
    cin >> reg_no;

    if (search(reg_no))
    {
        int std_index = -1;

        for (int i = 0; i < rctr; i++)
        {
            if (all_data[i][0] == reg_no)
            {
                std_index = i;
                break;
            }
        }

        if (std_index != -1)
        {
            int days = stoi(all_data[std_index][4]); // Extract the number of days from the student's data
            int bill; // Initialize the bill to 0

            // Calculate the bill based on some formula or rate per day
            // Replace the following line with your specific calculation:
            bill =300* days;

            // Update the bill in the student's record
            all_data[std_index][2] = to_string(bill);

            cout << "Bill calculated and updated successfully." << endl;

            // Write the updated data back to the file
            write("data.csv");
        }
        else
        {
            cout << "Student not found." << endl;
        }
    }
    else
    {
        cout << "Student not registered with us." << endl;
    }
}



// Pass file name (as a string). The data will be stored in the global array named "all_data".
void read(string fname)
{
    string line, word;
    int wctr, len;
    fstream file("data.csv", ios::in);
    while (getline(file, line)) //getline function reads line by line from file and store each data in a string variable named "line."
    {
        wctr = 0;
        word = "";
        len = line.length(); //Gives you the number of characters (length) of a string
        for (int ctr = 0; ctr < len; ctr++)
        {
            if (line[ctr] == ',')
            {
                all_data[rctr][wctr] = word;
                word = "";
                wctr++;
            }
            else if (ctr == len - 1)
            {
                word = word + line[ctr];
                all_data[rctr][wctr] = word;
            }
            else
            {
                word = word + line[ctr];
            }
        }
        rctr++;
    }
}
void count()
{
    int in = 0;
    int out = 0;
    for (int i = 2; i < rctr; i++)
    {
        if (all_data[i][3] == "IN" || all_data[i][3] == "in" || all_data[i][3] == "In" || all_data[i][3] == "iN")
            in++;
        else
            out++;
    }
    cout << "Total In students: " << in << endl;
    cout << "Total Out students: " << out << endl;
}

// Just pas the file name which you want to update (writes data from "all_data" 2D global array)
void write(string fname)
{
    fstream file("data.csv", ios::out);
    for (int i = 0; i < rctr; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (j == 4)
            {
               
                file << all_data[i][j] << endl;
            }
            else
            {
               
                file << all_data[i][j] << ",";
            }

        }
    }
}

void search()
{
    string reg_num;
    cout << "Enter the reg number you want to search: ";
    cin >> reg_num;

    for (int r = 1; r < rctr; r++)
    {
        if (reg_num == all_data[r][0])
        {
            cout << "Registered! Further information: \n";
            cout << "Name: " << all_data[r][1] << "\nBill: " << all_data[r][2] << "\nStatus: " << all_data[r][3] << "\nDays: " << all_data[r][4];
            found = true;
        }
    }
    if (found != true)
    {
        cout << "Not Registered!";
    }

}
void sorting()
{
    for (int r = 1; r < rctr; r++) {
        for (int nr = r + 1; nr < rctr; nr++) {
            if (all_data[r][0] > all_data[nr][0]) {
                swap(all_data[r], all_data[nr]);
            }
        }
    }
}
void display() {
    for (int r = 0; r < rctr; r++) {
        for (int c = 0; c < 5; c++) {
            cout << all_data[r][c] << " ";
        }
        cout << endl;
    }
}
bool search(string reg_num)
{
    for (int r = 1; r < rctr; r++)
    {
        if (reg_num == all_data[r][0])
        {
            return true;
        }

    }

    return false;


}
