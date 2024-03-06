#include<bits/stdc++.h>
using namespace std;
//--------------Base64---------------------
int sBase64[64] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/'
};
string Base64_encode(string str){
    int len = str.size();
    string res;
    res.resize((len + 2) / 3 * 4);
    int j = 0;
    for(int i = 0; i < len / 3 * 3;i += 3){
        int bits = ((str[i] & 0xff) << 16) | ((str[i+1] & 0xff) << 8) | (str[i+2] & 0xff);
        res[j++] = sBase64[(bits >> 18) & 0x3f];
        res[j++] = sBase64[(bits >> 12) & 0x3f];
        res[j++] = sBase64[(bits >> 6) & 0x3f];
        res[j++] = sBase64[bits & 0x3f];
    }
    if(len % 3 == 1){
        int bits = (str[len - 1] & 0xff) << 4;
        res[j++] = sBase64[(bits >> 6) & 0x3f];
        res[j++] = sBase64[bits & 0x3f];
        res[j++] = '=';
        res[j] = '=';
    }
    else if(len % 3 == 2){
        int bits = (str[len - 2] & 0xff) << 10 | (str[len - 1] & 0xff) << 2;
        res[j++] = sBase64[(bits >> 12) & 0x3f];
        res[j++] = sBase64[(bits >> 6) & 0x3f];
        res[j++] = sBase64[bits & 0x3f];
        res[j] = '=';
    }
    return res;
}
unsigned char BaseValue(char c){
    if(c > 'a' - 1){
        return c - 'a' + 26;
    }
    else if(c > 'A' - 1){
        return c - 'A';
    }
    else if(c > '0' - 1){
        return c - '0' + 52;
    }
    else if(c == '+'){
        return 62;
    }
    else if(c == '/'){
        return 63;
    }
    return -1;
}
string Base64_decode(string str){
    int len = str.size();
    string res;
    for(int i = 0; i < len - 4; i+=4){
        res.push_back((BaseValue(str[i]) << 2) | (BaseValue(str[i+1]) >> 4));
        res.push_back((BaseValue(str[i+1]) << 4) | (BaseValue(str[i+2]) >> 2));
        res.push_back((BaseValue(str[i+2]) << 6)| (BaseValue(str[i+3])));
    }
    res.push_back((BaseValue(str[len-4]) << 2) | (BaseValue(str[len-3]) >> 4));
    if(str[len-2] != '='){
        res.push_back((BaseValue(str[len-3]) << 4) | (BaseValue(str[len-2]) >> 2));
    }
    if(str[len-1] != '='){
        res.push_back((BaseValue(str[len-2]) << 6) | (BaseValue(str[len-1])));
    }
    return res;
}
//--------------Base64---------------------
//---------------RC4-----------------------

string ciphertext;
unsigned char K[256];//�@�w�nunsigned�A�d��~�O0~255
unsigned char S[256];
void KSA(string key){
    for(int i = 0; i < 256; i++){//��l��S��
        S[i] = i;
    }
    for(int i = 0; i < 256; i++){//�X�i�K�_
        K[i] = key[i % key.size()];
    }
    int j = 0;
    for(int i = 0; i < 256; i++){//�m���A����S��
        j = (j + S[i] + K[i]) % 256;
        swap(S[i],S[j]);
    }
    return;
}

void PRGA_XOR(string plaintext){
    int i = 0, j = 0;
    for(int p = 0; p < plaintext.size(); p++){
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);
        unsigned char k = (S[i] + S[j]) % 256;

        ciphertext[p] = plaintext[p] ^ S[k];
    }
    return;
}
bool isASCII(string str){
    for(int i = 0; i < str.size(); i++){
        if(!isprint(str[i])){
            return 0;
        }
    }
    return 1;
}
//---------------RC4-----------------------
int main(){
    string key;
    string text;
    cout << "�`:RC4����٬���٥[�K��k�A�[�ѱK�ϥΦP�@�ձK�_" << '\n';
    //cout << "�`:RC4�[�K���䴩string��X�A�e����ܶýX(�ѱK�䴩)" << '\n';

    while(1){
        cout << "�n�i��[�K�п�J0�A�ѱK�п�J1" << '\n';
        int flag1;cin >> flag1;
        if(!flag1){//�[�K
            cout << "��J������H�r�`�x�s(�N�O�`����1byte�x�s�@��)���п�J0"<<'\n';
            cout << "��J������HBase64�s�X���п�J1" << '\n';
            int flag2; cin >> flag2;

            cin.ignore();
            cout << "�п�J����\n";
            getline(cin, text);

            if(flag2){
                text = Base64_decode(text);
            }
        }
        if(flag1){//�ѱK
            cout << "�п�JBase64�s�X���K��" << '\n';
            cin.ignore();
            getline(cin,text);
            text = Base64_decode(text);
        }

        cout << "�п�J�K�_(�K�_�H�r�`�x�s�B�z)\n";
        getline(cin, key);
        KSA(key);
        ciphertext.clear();
        ciphertext.resize(text.size());
        PRGA_XOR(text);

        if(!flag1){
            cout << "�K�媺Base64�s�X:" << Base64_encode(ciphertext) << '\n';
        }
        if(flag1){
            cout << "���嬰:" << ciphertext;
            cout.clear();
            cout << '\n';
            cout << "���媺Base64�s�X:" << Base64_encode(ciphertext) << '\n';
        }
        cout << "-------------" << '\n';
    }

    return 0;
}
