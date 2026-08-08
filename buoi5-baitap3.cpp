#include <iostream>
using namespace std;

int main() {
    int tuoi;
    double thuNhap;

    cout << "Nhap tuoi: ";
    cin >> tuoi;

    cout << "Nhap thu nhap: ";
    cin >> thuNhap;

    bool duDieuKien = (tuoi >= 18 && thuNhap >= 5000000);
    cout << duDieuKien << endl;

    return 0;
}