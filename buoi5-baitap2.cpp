#include <iostream>
using namespace std;

int main() {
    const double PI = 3.14159;
    double banKinh, chuVi, dienTich;
    cout << "Nhap ban kinh hinh tron: ";
    cin >> banKinh;
    chuVi = 2 * PI * banKinh;
    cout << "Chu vi hinh tron la: " << chuVi << endl;
    dienTich = PI * banKinh * banKinh;
    cout << "Dien tich hinh tron la: " << dienTich << endl;
    return 0;
}