#include <iostream>
using namespace std;
int main()
{
    system("openssl enc -aes-256-cbc -pass pass:kekayan -p -in test.txt -out file.enc");
    return 0;
}