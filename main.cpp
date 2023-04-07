#include<iostream>
#include<fstream>
#include<string>

bool User();
void register_user();
/*
int main()
{
   int choice;
   while(choice)
   {
      swtich(1)
         case 1:
         case 2:
         case 3:
         default:
   }
}
*/

//Ensure User exists
bool User(){
     std::string username,password,uns,pw;

     std::cout << "Enter your username: "; std::cin >> username;
     std::cout << "Enter your password: "; std::cin >> password;
     //ifstream read()
     if(uns == username && pw == password)
     {
        return true;
     
     }else
     {
        return false;
        
     }
     
     std::cout << "You are logged In!" << std::endl;

}




// Register Users
void register_user()
{
    std::string name, college_year, username ,password;
    int age;
    std::fstream User_file;
    User_file.open("user.txt", std::ios::app); // Input the user-info w/o overwritting 
    std::cout << "Enter your name: "; std::cin >> name;
    std::cin >> name;
    std::cout << "Enter your College year: "; std::cin >> college_year;
    std::cin >> college_year;   
    User_file << college_year << std::endl;
    std::cout << "Enter your username: "; std::cin >> username;
    std::cin >> username;
    User_file << username << std::endl;
    std::cout << "Enter your password: "; std::cin >> password;
    std::cin >> username;
    User_file << password << std::endl;
    User_file.close();
    

}

