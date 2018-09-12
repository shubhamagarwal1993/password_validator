#include <iostream>
#include <fstream>

using namespace std;

#define MIN_PASSWORD_LENGTH 8
#define MAX_PASSWORD_LENGTH 64
#define MIN_ASCII_VAL 32
#define MAX_ASCII_VAL 126

class PasswordValidate {
    public:
        string password;

        PasswordValidate(string password) {
            this->password = password;
        }

        int editDist(string str1 , string str2 , int str1_length ,int str2_length) { 
            if(str1_length == 0) {
                return str2_length; 
            }

            if(str2_length == 0) {
                return str1_length; 
            }

            if(str1[str1_length - 1] == str2[str2_length - 1]) {
                return editDist(str1, str2, str1_length - 1, str2_length - 1);
            }

            return 1 + min(editDist(str1, str2, str1_length, str2_length - 1),        // Insert 
                           min(editDist(str1, str2, str1_length - 1, str2_length),    // Remove 
                               editDist(str1, str2, str1_length - 1, str2_length - 1) // Replace 
                              )
                          );
        }

        /**
         *
         */
        bool commonPasswordCheck(string password, string weak_password_file_name) {

            int password_length = password.length();

            string common_password;
            ifstream input_file(weak_password_file_name);

            // check if file exists
            if(input_file.fail()) {
                cout << password << " -> Given weak passwords file: " << weak_password_file_name << " does not exist";
            }

            int min_edit_dist = INT_MAX;
            if(input_file.is_open()) {
                while(getline(input_file, common_password)) {

                    int common_password_length = common_password.length();

                    int edit_dist = editDist(password, common_password, password_length, common_password_length);

                    // if edit distance is 0, password is common
                    if(edit_dist == 0) {
                        input_file.close();
                        cout << password << " -> Error: Too Common";
                        return false;
                    } else {
                        if(edit_dist < min_edit_dist) {
                            min_edit_dist = edit_dist;
                        }
                    }

                }
            }
            input_file.close();

            if(min_edit_dist == 1) {
                cout << password << " -> Similar to common words, should use a better one";
            }

            return true;
        }

        /**
         * Check if given password of appropriate length
         */
        bool passwordLengthCheck(string password) {

            int count = password.length();

            if(count < MIN_PASSWORD_LENGTH) {
                cout << password << " -> Error: Too Short";
                return false;
            }

            if(count > MAX_PASSWORD_LENGTH) {
                cout << password << " -> Error: Too Long";
                return false;
            }

            return true;
        }

        /**
         * check if given characters within ASCII range
         */
        bool validASCIICheck(string passord) {

            int password_length = password.length();

            for(int i = 0; i < password_length; i++) {

                // curr char
                char curr_char = password[i];

                // curr char ascii val
                int curr_char_ascii_val = (int)curr_char;

                if((curr_char_ascii_val < MIN_ASCII_VAL) || (curr_char_ascii_val > MAX_ASCII_VAL)) {
                    cout << password << " -> Error: Only ASCII chars";
                    return false;
                }
            }
            return true;
        }

        /**
         * main function to check password
         */
        void validatePassword(string weak_password_file_name) {

            // check for length of password
            if(!passwordLengthCheck(this->password)) {
                cout << endl;
                return;
            }

            if(!validASCIICheck(this->password)) {
                cout << endl;
                return;
            }

            if(!commonPasswordCheck(this->password, weak_password_file_name)) {
                cout << endl;
                return;
            }

            return;
        }
};

void show_usage(string file_name) {
    cerr << "Usage: " << file_name << " <option(s)> weak_password_file_name" << endl
         << "Options:\n"
         << "\t-h,--help\t\t\tShow this help message\n"
         << endl;
}

void passwordValidate(int argc, char* argv[], string input_password) {

    // Check the number of parameters
    if(argc < 2) {
        show_usage(argv[0]);
        return;
    }

    // check for help flags
    for(int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if((arg == "-h") || (arg == "--help")) {
            show_usage(argv[0]);
            return;
        }
    }

    string input_file_name = argv[1];

    // make password object and check for password validation
    PasswordValidate passwordValidate(input_password);
    passwordValidate.validatePassword(input_file_name);

    return;
}

/**
 * argc - argument count
 * argv - argument vector(array)
 */
int main(int argc, char* argv[]) {

    string lineInput;
    while(getline(cin, lineInput)) {
        string input_password = lineInput;
        passwordValidate(argc, argv, input_password);
    }

    return 0;
}

