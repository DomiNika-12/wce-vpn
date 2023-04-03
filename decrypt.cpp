#include <iostream>
using namespace std;
int main()
{
    system("openssl enc -aes-256-cbc -pass pass:kekayan -d -in file.enc -out test_new.txt");
    return 0;
}