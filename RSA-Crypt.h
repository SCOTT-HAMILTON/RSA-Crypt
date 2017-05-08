#ifndef RSA_CRYPT
#define RSA_CRYPT

#include <vector>
#include <string>

std::string decrypt(unsigned long long d, unsigned long long n, std::vector<int> messageC);
std::vector<int> crypt(unsigned long long n, unsigned long long e, std::string message);
void getPUKey(unsigned long long p, unsigned long long q, unsigned long long &n, unsigned long long &e);
void getPRKey(unsigned long long p, unsigned long long q, unsigned long long &n, unsigned long long &d);

std::string ToStr(std::vector<int> message);
std::vector<int> FromStr(std::string message);

#endif // RSA_CRYPT
