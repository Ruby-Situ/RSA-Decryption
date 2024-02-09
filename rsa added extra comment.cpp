#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

vector<int> findPrime(int n)
{
    
    vector<int> divisors;
    int ii;
    bool prime = true;
    vector<int> primeDiv;
    
    for (int i = 2; i < n; i++)
    {
        if(n % i == 0)
        {
            //found a divisor
            divisors.push_back(i);
        }
    }
    
    //see which divisors are prime
    for(int i = 0; i < divisors.size(); i++)
    {
        for(ii = 2; ii < divisors.at(i); ii++)
        {
            if(divisors.at(i)%ii == 0)
            {
                prime = false;
            }
        }
        if (prime == true)
        {
            primeDiv.push_back(divisors.at(i)); //found int that is a divisor and prime
        }
    }
    
    return primeDiv;
}

int findD(int phi, int e)
{
    //find multiple alpha * x + beta *(-m) = 1
    int multA;
    int i = 1;
    
    while(i < phi)
    {
        if((e*i)%phi == 1) //if e * i is 1 greater than phi then thats alpha
        {
            multA = i;
        }
        i++;
    }
    
    return multA;
}


int findMessage(int base, int d, int n)
{
    int answer;
    if(d == 0 || base == 1){
        return 1;
    }
    else{
        if(d % 2 ==0) {// if even we can continue as normal
            answer = findMessage(((base * base) % n), d/2, n); //mod the squared base, 
                                                    //change the exp to represent (base^2)^{exp/2}and repeat
        }
        else{
            answer = (base % n) * findMessage(base, d - 1, n); // base^{even} * base mod n
                                                                //recursive call again with an even base-1
        }  
    }

    return answer % n; 
}

string toEnglish (vector<int> decoded)
{
    string cracked = "";
    
    for (int i = 0; i < decoded.size(); i++)
    {
        switch(decoded.at(i)){
            case 7: cracked += "A";
                break;
            case 8: cracked += "B";
                break;
            case 9: cracked += "C";
                break;
            case 10: cracked += "D";
                break;
            case 11: cracked += "E";
                break;
            case 12: cracked += "F";
                break;
            case 13: cracked += "G";
                break;
            case 14: cracked += "H";
                break;
            case 15: cracked += "I";
                break;
            case 16: cracked += "J";
                break;
            case 17: cracked += "K";
                break;
            case 18: cracked += "L";
                break;
            case 19: cracked += "M";
                break;
            case 20: cracked += "N";
                break;
            case 21: cracked += "O";
                break;
            case 22: cracked += "P";
                break;
            case 23: cracked += "Q";
                break;
            case 24: cracked += "R";
                break;
            case 25: cracked += "S";
                break;
            case 26: cracked += "T";
                break;
            case 27: cracked += "U";
                break;
            case 28: cracked += "V";
                break;
            case 29: cracked += "W";
                break;
            case 30: cracked += "X";
                break;
            case 31: cracked += "Y";
                break;
            case 32: cracked += "Z";
                break;
            case 33: cracked += " ";
                break;
            case 34: cracked += "\"";
                break;
            case 35: cracked += ",";
                break;
            case 36: cracked += ".";
                break;
            case 37: cracked += "\'";
                break;
        }
    }
    
    return cracked;
}

int main()
{
    //inputs
    int e, n, m, input;
    vector<int> message;
    cin >> e;
    cin >> n;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> input;
        message.push_back(input);
    }
    
    int d, phi, p , q;
    bool valid = true;
    
    //get p and q
    vector<int> primes = findPrime(n);
    
    if(primes.size() == 2 && (primes.at(0) * primes.at(1) == n))
    {
        if(primes.at(0) > primes.at(1))
        {
            p = primes.at(1);
            q = primes.at(0);
        }
        else
        {
            p = primes.at(0);
            q = primes.at(1);
        }
    }
    else{
        valid = false;
    }
    
    //get phi
    phi = (p - 1)*(q - 1);
    
    //find d
    
    if(__gcd(e, phi) != 1){ //check if there is an inverse
        valid = false;
    }
    else{
        d = findD(phi, e);
    }
    
    
    if (valid == false)
    {
        cout << "Public key is not valid!";
        return -1;
    }
    else
    {
        //output
        cout << p << " " << q << " " << phi << " " << d << endl;
        
        //find and display message in integers
        vector<int> decode;
        
        for(int i = 0; i < message.size(); i++)
        {
            decode.push_back(findMessage(message.at(i), d, n));
            cout << decode.at(i) << " ";
        }
        
        //decode the integers to english
        cout << endl << toEnglish(decode);
    }
    
    return 0;
}



