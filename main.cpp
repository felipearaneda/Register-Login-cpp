#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <thread>
#include <chrono>


void login();
void registration();
void forgot();
void close();
std::vector<std::string> parseComma(std::string line);

std::string actualUser {};

int main(){

    int opt;
    system("cls");

    if(actualUser != ""){
        std::cout << "Hello!, " << actualUser << std::endl;
    }
    

    std::cout << "\n**************************" << std::endl;
    std::cout << "***********MENU***********" << std::endl;
    std::cout << "**************************" << std::endl;

    std::cout << "Press 1 | LOGIN" << std::endl;
    std::cout << "Press 2 | REGISTER" << std::endl;
    printf( "Press 3 | %cForgot your password?\n", 168);
    std::cout << "Press 4 | LOG OUT" << std::endl;
    std::cout << "Press 5 | EXIT" << std::endl;

    std::cin >> opt;

    switch(opt){
        
        case 1:
            login();
            break;
        case 2:
            registration();
            break;
        case 3:
            forgot();
            break;
        case 4:
            close();
            break;
        case 5:
            system("cls");
            std::cout << "****************" << std::endl;
            printf("%cGood Bye!\n", 173);
            std::cout << "****************" << std::endl;
            break;
        default:
            system("cls");
            std::cout << "*Please select an option*\n";
            main();
    }


}

//returns a vector of strings
std::vector<std::string> parseComma(std::string line){

    //vector of strings called 'result'
    std::vector<std::string> result;
    std::stringstream s_stream(line);

    //while the stringstream object called 's_stream' is not failing (that is, it's working)
    while(!s_stream.fail()){ 

        //creates an empty string called subString 
        std::string subString {};

        //grabs the info from the s_stream object(line) until it founds a comma and puts the info into subString
        std::getline(s_stream, subString, ','); 

        //pushes into the back of the array the result inside subString
        result.push_back(subString); 
    }
    return result;

};

void login(){

    std::fstream input;
    int count;
    std::string username, userPass, recordPass, filename = "records.txt";

    input.open(filename, std::ios::in);

    system("cls");

    if(input.is_open()){

        std::string line;

        std::cout << "*****************************" << std::endl;
        std::cout << "**********LOGIN PAGE*********" << std::endl;
        std::cout << "*****************************" << std::endl;

        std::cout << "Username: ";
        std::cin >> username;

        std::cout << "Password: ";
        std::cin >> userPass;

        while(getline(input, line)){

            std::vector<std::string> resultVector {parseComma(line)};
            const char *user {resultVector.at(0).c_str()};

            const char *usernameString = username.c_str();

            if(std::strcmp(user, usernameString) == 0){
                const char *password {resultVector.at(1).c_str()};

                const char *passwordString = userPass.c_str();

                if(std::strcmp(password, passwordString) == 0){

                    std::chrono::seconds timer(2);

                    system("cls");
                    std::cout << username << ", The Login Was Successfull!" << std::endl;
                    actualUser = username;
                    std::cout << "Redirecting to the main menu..." << std::endl;
                    std::this_thread::sleep_for(timer);
                    input.close();
                    main(); //return to the main menu

                }else{
                    std::cout << "Error Loging in \n Please check your USERNAME or PASSWORD" << std::endl;
                    system("pause");
                    login();
                }

            }
        }

    }else{
        std::cout << "There was an error, you are being rederected to the main menu" << std::endl;
        system("pause");
        main();
    };

};

void registration(){

    std::string userName, userPass, filename = "records.txt";
    system("cls");

    std::fstream file;
    file.open(filename, std::ios::app);

    if(file.is_open()){

        std::cout << "Please enter your username: ";
        std::cin >> userName;
        std::cout << "Please enter your password: ";
        std::cin >> userPass;

        file << userName << "," << userPass << std::endl;

        

        system("cls");

        std::cout << "Registration Successfull!\n";

        system("pause");

        file.close();
        main();
    }else{
        std::cout << "File is not open." << std::endl;
        main();
    }

};

void forgot(){

    std::fstream file2;

    int opt;

    std::string username, filename {"records.txt"};

    system("cls");

    printf( "%cForgot your password?\n", 168);
    std::cout << "Press 1 | Search your username" << std::endl;
    std::cout << "Press 2 | Return to the main menu" << std::endl;

    std::cout << "Enter your option: ";
    std::cin >> opt;

    system("cls");

    file2.open(filename, std::ios::in);

    system("cls");

    if(file2.is_open()){

        std::string line;

        switch(opt){

            case 1: {

                std::cout << "Write your username: ";
                std::cin >> username;            

                while(getline(file2, line)){

                    std::vector<std::string> resultVector {parseComma(line)};
                    const char *user {resultVector.at(0).c_str()};

                    const char *usernameString = username.c_str();

                    if(std::strcmp(user, usernameString) == 0){
                        const char *password {resultVector.at(1).c_str()};

                            system("cls");
                            std::cout << username << ", Your account was found!" << std::endl;
                            std::cout << "Your password is: " << password << std::endl;

                            system("pause");
                            login();

                    }else{
                        system("cls");
                        std::cout << "The username was not found, please try again" << std::endl;
                        system("pause");
                        forgot();
                    }
                }
            }
                break;

            case 2: {
                std::chrono::seconds duration(2);

                system("cls");

                std::cout << "You are being redirected to the main menu..." << std::endl;
                std::this_thread::sleep_for(duration);

                file2.close();
                main();
                break;
            }
            
            default:
                std::chrono::seconds duration(1);

                std::cout << "Select a valid option" << std::endl;
                std::this_thread::sleep_for(duration);

                forgot();
                break;
        }

    }else{
        std::chrono::seconds duration(2);

        system("cls");

        std::cout << "There was an error, you are being rederected to the main menu" << std::endl;
        std::this_thread::sleep_for(duration);

        main();
    }


};

void close(){

    int dec;

    while(actualUser != ""){

        system("cls");

        printf( "%cDo you really want to log out?\n", 168);
        std::cout << "Press 1 for YES or 2 for NO" << std::endl;
        std::cin >> dec;

        if(dec == 1){
            std::chrono::seconds timer(2);

            system("cls");

            actualUser = {};

            std::cout << "You have been logged out successfully" << std::endl;
            std::cout << "Redirectioning you to the main menu..." << std::endl;
            
            std::this_thread::sleep_for(timer);
            main();
        
        }else if(dec == 2){
            std::chrono::seconds timer(2);

            system("cls");

            std::cout << "You are being redirected to the main menu..." << std::endl;

            std::this_thread::sleep_for(timer);
            main();

        }else{
            std::chrono::seconds timer(2);

            system("cls");

            std::cout << "There has been a problem, you are being redirected to the main menu" << std::endl;

            std::this_thread::sleep_for(timer);
            main();
        }

    }
    std::chrono::seconds timer(2);
    system("cls");

    std::cout << "No user to log out" << std::endl;
    std::cout << "Redirecting to the main menu" << std::endl;
    std::this_thread::sleep_for(timer);
    main();

};