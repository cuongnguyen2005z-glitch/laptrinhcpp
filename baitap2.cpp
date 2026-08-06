#include <iostream> // Khai báo thư viện iostream để sử dụng các hàm nhập xuất
using namespace std; // Sử dụng không gian tên std để tránh phải viết std:: trước các hàm và đối tượng chuẩn

int main() {
    string Hovaten, lophoc; //Khai báo biến 
    cout << "Nhap ho va ten: "; // xuât ra màn hình yêu cầu nhập họ và tên
    getline(cin, Hovaten); // Nhập họ và tên từ bàn phím
    cout << "Nhap lop hoc: "; // Xuất ra màn hình yêu cầu nhập lớp học
    getline(cin, lophoc); // Nhập lớp học từ bàn phím
    cout << "Xin chao, " << Hovaten << ", " << lophoc <<"!" << endl; 
    // Xuất ra màn hình lời chào với họ và tên, lớp học
}
