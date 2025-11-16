#include <json.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <thread>
#include <stdexcept>
#include <sstream>

using namespace std;
using json = nlohmann::json;

void prntmenu(string option1, string option2 = "", string option3 = "", string option4 = "", string text1 = "")
{
    if (option1 != "") option1 += "\n";
    if (option2 != "") option2 += "\n";
    if (option3 != "") option3 += "\n";
    if (option4 != "") option4 += "\n";

    cout << option1 << option2 << option3 << option4 << text1 << "\n";
}

struct Entry {
    string jsonURL;
    string jsonUsername;
    string jsonPassword;
};

void to_json(json& j, const Entry& e) {
    j = json{
        {"URL", e.jsonURL},
        {"Username", e.jsonUsername},
        {"Password", e.jsonPassword}
    };
}

void from_json(const json& j, Entry& e) {
    j.at("URL").get_to(e.jsonURL);
    j.at("Username").get_to(e.jsonUsername);
    j.at("Password").get_to(e.jsonPassword);
}


int main() {

    string answer;
    int answer1;
    string URL, username, password;

    json jFile;
    string storedMasterPassword;
    vector<Entry> entries;

    ifstream infile("../data.json");
    if (infile.good()) {
        infile >> jFile;
        if (jFile.contains("MasterPassword"))
            storedMasterPassword = jFile["MasterPassword"].get<string>();
    }
    infile.close();

    if (storedMasterPassword.empty()) {
        cout << "Create Master Password:\n> ";
        cin >> storedMasterPassword;

        jFile["MasterPassword"] = storedMasterPassword;
        jFile["Entries"] = json::array();

        ofstream out("../data.json");
        out << jFile.dump(4);
        out.close();
    }

    string input;
    while (true) {
        cout << "Enter Master Password:\n> ";
        cin >> input;

        if (input == storedMasterPassword)
            break;

        cout << "Incorrect Master Password!\n\n";
    }

    cout << "Access granted!\n\n";
    this_thread::sleep_for(chrono::milliseconds(800));

    if (jFile.contains("Entries")) {
        for (auto& item : jFile["Entries"]) {
            entries.push_back(item.get<Entry>());
        }
    }

    cout << "Loaded " << entries.size() << " entries.\n\n";

    prntmenu("1.Add Password", "2.Show Passwords", "3.Close", "", "Choose an option:");
    cin >> answer1;

    switch (answer1) {

        case 1: {
            // Passwort eingeben
            prntmenu("Website URL:");
            cin >> URL;
            prntmenu("Username:");
            cin >> username;
            prntmenu("Password:");
            cin >> password;

            while (true) {
                prntmenu("Are these Informations correct?:",
                         "URL: " + URL,
                         "Username: " + username,
                         "Password: " + password,
                         "");

                cout << "Please type Yes or No:\n> ";
                cin >> answer;
                transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

                if (answer == "yes") {
                    Entry newEntry{URL, username, password};

                    jFile["Entries"].push_back(newEntry);

                    ofstream out("../data.json");
                    out << jFile.dump(4);
                    out.close();

                    prntmenu("Password Saved!\n", "1.Return to menu", "2.Quit", "", "Please Choose an Option");

                    break;
                }
                else if (answer == "no") {
                    break;
                }
                else {
                    cout << "Invalid input.\n\n";
                }
            }
            break;
        }

        case 2: {

           //show passwords
        }

        case 3:
            cout << "Closing...\n";
            break;
    }

    return 0;
}
