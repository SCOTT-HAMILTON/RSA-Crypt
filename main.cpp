#include <gmpxx.h>
#include "RSA-Crypt.h"

using namespace std;

unsigned long long PGCD(unsigned long long a, unsigned long long b);
unsigned long long euclideEtendu(unsigned long long e, unsigned long long phi_n);
unsigned long long int IntFromStr(string val);
int IntFromChar(char val);

void ullTompz(mpz_t v, unsigned long long r);

string decrypt(unsigned long long d, unsigned long long n, vector<int> messageC){
    unsigned int i = 0;
    string message;
    mpz_class tmp, cn;
    mpz_class mpz_d, mpz_n;
    ullTompz(mpz_d.get_mpz_t(), d);
    ullTompz(mpz_n.get_mpz_t(), n);
    for (i = 0; i < (unsigned int)messageC.size(); i++){
        tmp = 0;
        cn = messageC[i];
        mpz_powm(tmp.get_mpz_t(), cn.get_mpz_t(), mpz_d.get_mpz_t(), mpz_n.get_mpz_t());
        message+= (char) tmp.get_d();
    }
    return message;
}

vector<int> crypt(unsigned long long n, unsigned long long e, string message){
    unsigned int i = 0;
    vector<int> crypt;
    mpz_class tmp, cn, mpz_n, mpz_e;
    ullTompz(mpz_n.get_mpz_t(), n);
    ullTompz(mpz_e.get_mpz_t(), e);

    int tmp_cn;
    for (i = 0; i < (unsigned int)message.size(); i++){
        tmp = 0;
        tmp_cn = (int) message[i];
        cn = tmp_cn;
        mpz_powm(tmp.get_mpz_t(), cn.get_mpz_t(), mpz_e.get_mpz_t(), mpz_n.get_mpz_t());
        crypt.push_back((int)tmp.get_d());
    }

    return crypt;
}

void getPUKey(unsigned long long p, unsigned long long q, unsigned long long &n, unsigned long long &e){
    n = p*q;
    unsigned long long pn = (p-1)*(q-1);
    e = p;
    while (PGCD(e, pn)!=1 && e<pn)e++;
}

void getPRKey(unsigned long long p, unsigned long long q, unsigned long long &n, unsigned long long &d){
    n = p*q;
    unsigned long long pn = (p-1)*(q-1);
    unsigned long long e = p;
    while (PGCD(e, pn)!=1)e++;
    d = euclideEtendu(e, pn);
}

unsigned long long PGCD(unsigned long long a, unsigned long long b){
    if (a < b){
        if (b%a==0)return a;
        if (a<=0)return -1;
        return PGCD(a, b-a);
    }else{
        if (a%b==0)return b;
        if (b<=0)return -1;
        return PGCD(b, a-b);
    }
}

int getNb_C(int val){
    int i = 0;
    while (val>=1){
        val/=10;
        i++;
    }
    return i;
}

unsigned long long IntFromStr(string val){
    int nb_c = val.size();
    int i = 0;
    unsigned long long dec = 1LL;
    for (i = 1; i < nb_c; i++){
        dec *=10;
    }
    unsigned long long int result = 0LL;
    unsigned long long int tmp;
    for (i = 0; i < nb_c; i++){
        tmp = (int) val[i]-'0';
        tmp *= dec;
        result += tmp;
        dec/=10;
    }

    return result;
}

int IntFromChar(char val){
    return (int) val-'0';
}

unsigned long long euclideEtendu(unsigned long long e, unsigned long long phi_n){
    long long n0 = phi_n;
    long long b0 = e;
    long long t0 = 0;
    long long t = 1;
    long long q = n0/b0;
    long long r = n0 - (q * b0);
    long long temp = 0;

    while (r > 0)
    {
        temp = t0 - (q * t);
        if (temp >= 0)
            temp = temp % phi_n;
        else
            temp = phi_n - ((-temp) % phi_n);

        t0 = t;
        t = temp;
        n0 = b0;
        b0 = r;
        q = n0/b0;
        r = n0 - (q * b0);
    }

    if (b0 != 1)
        return 0;
    else
        return t;
}

void ullTompz(mpz_t v, unsigned long long r){
    mpz_import(v, 1, -1, sizeof(r), 0, 0, &r);
}

std::vector<int> FromStr(std::string message){
    unsigned int i = 0;
    int cn;
    char tmp_c[1000];
    std::vector<int> result;
    std::string tmp("");
    for (i = 0; i < (unsigned int) message.size(); i++){
        cn = IntFromChar(message[i]);
        if (cn == -15){
            result.push_back(IntFromStr(tmp));
            tmp = "";
        }
        else{
            sprintf(tmp_c, "%d", cn);
            tmp += string(tmp_c);
        }
    }

    return result;
}

std::string ToStr(std::vector<int> message){

    unsigned int i = 0;
    int cn;
    std::string result("");
    char tmp[1000];
    for (i = 0; i < (unsigned int ) message.size(); i++){
        cn = message[i];
        sprintf(tmp, "%d", cn);
        result += std::string(tmp);
        result += "!";
    }
    return result;
}









