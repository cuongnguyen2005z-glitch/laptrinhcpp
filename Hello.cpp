#include <iostream> // Khai báo thư viện iostream để sử dụng các hàm nhập xuất
using namespace std; // Sử dụng không gian tên std để tránh phải viết std:: trước các hàm và đối tượng chuẩn

int main() {
    string name; // Khai báo biến name để lưu trữ tên người dùng
    cout << "Moi ban nhap ten: "; // Xuất ra màn hình yêu cầu người dùng nhập tên
    cin >> name; // Nhập tên từ bàn phím và lưu vào biến name
    cout << "Xin chao, " << name << "!" << endl; 
    // Xuất ra màn hình lời chào với tên người dùng
    return 0; // Kết thúc chương trình và trả về giá trị 0 để báo hiệu rằng chương trình đã kết thúc thành công
}