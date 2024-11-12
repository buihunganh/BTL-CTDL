#include <iostream>
#include <string>
#include "vector.cpp"
using namespace std;

class SoLon{
private:
    Vector<int> V; 
    bool Negative; 

public:
    // Constructor mặc định
    SoLon() : Negative(false){
        V.push_back(0);
    }

    // Constructor từ string
    SoLon(string num){
        Negative = false;
        if(num.empty()){
            V.push_back(0);
            return;
        }
        
        int start = 0;
        if(num[0] == '-'){
            Negative = true;
            start = 1;
        }
        
        for(int i = num.length() - 1; i >= start; i--){
            V.push_back(num[i] - '0');
        }
        
        if(V.size() == 0){
            V.push_back(0);
        }
    }

    // Constructor từ int
    SoLon(int num){
        Negative = (num < 0);
        num = abs(num);
        
        if(num == 0){
            V.push_back(0);
            return;
        }
        
        while(num > 0){
            V.push_back(num % 10);
            num /= 10;
        }
    }

    // Copy constructor
    SoLon(const SoLon& other) : V(other.V), Negative(other.Negative){}

    // So sánh trị tuyệt đối của 2 số
    bool absLess(const SoLon& other) const{
        if(V.size() != other.V.size())
            return V.size() < other.V.size();
        
        for(int i = V.size() - 1; i >= 0; i--){
            if(V[i] != other.V[i])
                return V[i] < other.V[i];
        }
        return false;
    }

    // Cộng hai số lớn 
    SoLon absAdd(const SoLon& other) const{
        SoLon result;
        result.V = Vector<int>();
        
        int carry = 0;
        int i = 0;
        
        while(i < V.size() || i < other.V.size() || carry){
            int sum = carry;
            if(i < V.size()) sum += V[i];
            if(i < other.V.size()) sum += other.V[i];
            
            result.V.push_back(sum % 10);
            carry = sum / 10;
            i++;
        }
        
        return result;
    }

    // Trừ hai số lớn 
    SoLon absSub(const SoLon& other) const{
        SoLon result;
        result.V = Vector<int>();
        
        int borrow = 0;
        
        for(int i = 0; i < V.size(); i++){
            int diff = V[i] - borrow;
            if(i < other.V.size()) diff -= other.V[i];
            
            if(diff < 0){
                diff += 10;
                borrow = 1;
            } else{
                borrow = 0;
            }
            
            result.V.push_back(diff);
        }
        
        while(result.V.size() > 1 && result.V.back() == 0){
            result.V.pop_back();
        }
        
        return result;
    }

    // Cộng hai số lớn
    SoLon operator+(const SoLon& other) const{
        if(Negative == other.Negative){
            SoLon result = absAdd(other);
            result.Negative = Negative;
            return result;
        }
        
        if(absLess(other)){
            SoLon result = other.absSub(*this);
            result.Negative = other.Negative;
            return result;
        } else{
            SoLon result = absSub(other);
            result.Negative = Negative;
            return result;
        }
    }

    // Trừ hai số lớn
    SoLon operator-(const SoLon& other) const{
        SoLon temp = other;
        temp.Negative = !temp.Negative;
        return *this + temp;
    }

    // Nhân với số int
    SoLon operator*(int num) const{
        if(num == 0) return SoLon(0);
        
        SoLon result;
        result.V = Vector<int>();
        result.Negative = Negative ^ (num < 0);
        num = abs(num);
        
        int carry = 0;
        for(int i = 0; i < V.size() || carry; i++){
            long long cur = carry;
            if(i < V.size()){
                cur += (long long)V[i] * num;
            }
            result.V.push_back(cur % 10);
            carry = cur / 10;
        }
        
        return result;
    }

    // Nhân hai số lớn
    SoLon operator*(const SoLon& other) const{
        SoLon result;
        result.V = Vector<int>(V.size() + other.V.size(), 0);
        result.Negative = Negative ^ other.Negative;
        
        for(int i = 0; i < V.size(); i++){
            int carry = 0;
            for(int j = 0; j < other.V.size() || carry; j++){
                long long cur = result.V[i + j] + carry;
                if(j < other.V.size()){
                    cur += (long long)V[i] * other.V[j];
                }
                result.V[i + j] = cur % 10;
                carry = cur / 10;
            }
        }
        
        while(result.V.size() > 1 && result.V.back() == 0){
            result.V.pop_back();
        }
        
        return result;
    }

    // In số
    friend ostream& operator<<(ostream& out, const SoLon& num){
        if(num.Negative && !(num.V.size() == 1 && num.V[0] == 0)){
            out << "-";
        }
        for(int i = num.V.size() - 1; i >= 0; i--){
            out << num.V[i];
        }
        return out;
    }
};

// Hàm tính Fibonacci
SoLon fibonacci(int n){
    if(n <= 0) return SoLon(0);
    if(n <= 2) return SoLon(1);
    
    SoLon a(1), b(1), c;
    for(int i = 3; i <= n; i++){
        c = a + b;
        a = b;
        b = c;
    }
    return c;
}

// Hàm tính giai thừa
SoLon factorial(int n){
    if(n < 0) return SoLon(0);
    if(n <= 1) return SoLon(1);
    
    SoLon result(1);
    for(int i = 2; i <= n; i++){
        result = result * i;
    }
    return result;
}

int main(){
    int n;
    cout << "Nhap n (1 <= n <= 1000): ";
    cin >> n;
    
    if(n < 1 || n > 1000){
        cout << "n phai nam trong khoang [1,1000]" << endl;
        return 0;
    }
    
    cout << "Fibonacci thu " << n << " la: " << fibonacci(n) << endl;
    cout << "Giai thua cua " << n << " la: " << factorial(n) << endl;
    
    return 0;
}