#include <json.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <immintrin.h>
#include <stdexcept>
#include <sstream>
using namespace std;

void prntmenu(string option1, string option2 = "", string option3 = "", string option4 = "", string text1 = "")
{
    if (option1 != "") {
        option1 = option1 + "\n";
    }
    if (option2 != "") {
        option2 = option2 + "\n";
    }
    if (option3 != "") {
        option3 = option3 + "\n";
    }
    if (option4 != "") {
        option4 = option4 + "\n";
    }
    cout << option1
         << option2
         << option3
         << option4
         << text1 << "\n";
}
struct Data {
    string jsonURL;
    string jsonUsername;
    string jsonPassword;

};

void to_json(nlohmann::json& j, const Data& data) {
    j = nlohmann::json{
            {"URL", data.jsonURL},
            {"Username", data.jsonUsername},
            {"Password", data.jsonPassword}
    };
}

void from_json(const nlohmann::json& j, Data& data) {
    j.at("URL").get_to(data.jsonURL);
    j.at("Username").get_to(data.jsonUsername);
    j.at("Password").get_to(data.jsonPassword);
}

int main() {
    string answer;
    int answer1;
    string URL;
    string username;
    string password;
    istringstream(answer) >> answer1;

    Data data;

    prntmenu("1.Add Password", "2.Show Passwords", "3.Close", "","Choose an option:");
    cin >> answer1;
    switch (answer1) {
        case 1:
            prntmenu("Website URL:");
            cin >> URL;
            prntmenu("Username:");
            cin >> username;
            prntmenu("Password:");
            cin >> password;


            while (true) {
                prntmenu("Are these Informations correct?:", "URL:"+URL, "Username:"+username,"Password:"+password);
                //if correct >> Save information in json file, if not >> Change options/Cancel password entry//

                cout << "Please type Yes or No:" << endl;
                cin >> answer;
                transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

                if (answer == "yes") {
                    // write information to file and encrypt
                    data.jsonUsername = username;
                    data.jsonPassword = password;
                    data.jsonURL = URL;

                    nlohmann::json j = data;

                    std::ofstream file("../data.json");
                    file << j.dump(4);
                    file.close();

                    prntmenu("Password Saved!\n","1.Return to menu", "2.Quit", "", "Please Choose an Option");

                    break;
                }
                else if (answer == "no") {
                    // return to menu (loop??)
                    break;
                }
                else {
                    cout << "Invalid input. \n" << endl;
                    continue;
                }

            }

            break;
        case 2:;
            //add other options//
    }
    //add en- decryption
}
