#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int convertToInt(const string& str) {
    int result = 0;
    try {
        result = stoi(str);
    }
    catch (const invalid_argument&) {
        throw "Error: 올바른 숫자가 아닙니다.";
    }
    catch (const out_of_range&) {
        throw "Error: 숫자가 너무 큽니다.";
    }
    return result;
}

string arabicToRoman(int num) {
    string roman = "";
    int arabic[] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
    string romanNumeral[] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };

    for (int i = 0; i < 13; i++) {
        while (num >= arabic[i]) {
            roman += romanNumeral[i];
            num -= arabic[i];
        }
    }

    return roman;
}

int main() {
    string strNum;
    while (true) {
        cout << "숫자를 입력하세요 (종료: esc): ";
        getline(cin, strNum);
        if (getchar() == 27) { // 단축키 esc 입력
            break;
        }
        try {
            int num = convertToInt(strNum);
            if (num < 1 || num > 3999) {
                throw "Error: 범위 값을 벗어났습니다 (1~3999)";
            }
            cout << "변환된 값 : " << arabicToRoman(num) << endl;
        }
        catch (const char* msg) {
            cerr << msg << endl;
        }
    }

    return 0;
}
