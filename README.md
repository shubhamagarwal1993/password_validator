## Output
  - prints invalid passwords with reason they are invalid
  - prints valid password which should preferrably be changed since they appear weak, or very close to common words

## Running the program
  - machine: tested on MacOS and linux

  - language c++17, also works with c++11

  - command to run program
    `g++ -std=c++17 password_validator.cpp && cat input_passwords.txt | ./a.out weak_password_list.txt`

### changing arguments
  - you can replace list of weak password and change the file `weak_password_list.txt`
  - you can give a new list of password to check by changing the file `input_passwords.txt`

### changing out of program
  - remove check of condition `edit_dist == 1` to only check for common words
  - you can increase edit distance to make password check stronger

## Integrating with your program
  - take the 4 lines in main and paste them anywhere in your code
  - the complete password check is inside a `PasswordValidate` class, so needed functions should be within the class
  - Remove `using namespace std;` while importing the code. Using namespace std is bad practise
    - Read [this](https://stackoverflow.com/questions/1452721/why-is-using-namespace-std-considered-bad-practice) for more details on it
