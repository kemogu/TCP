#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;



int client()
{
    //	Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        return 1;
    }

    //	Create a hint structure 
    int port = 54000;
    string ipAddress = "127.0.0.1";

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    //	Connect to the server on the socket
    int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connectRes == -1)
    {
        return 1;
    }

    //	While loop:
    char buf[4096];
    string user;
	int i=0;
    do {

		if(i==0){
			cout << "Username: ";
			cin >> user;
		}

        //  Send to server
        int sendRes = send(sock, user.c_str(), user.size() + 1, 0);
        
		if (sendRes == -1 )
        {
            cout << "Could not send to server! Whoops!\r\n";
            continue;
        }

        //  Wait for response
		memset(buf, 0, 4096);
        string gelen;
        int bytesReceived = recv(sock, buf, 4096, 0);

        int choice;
        string choiceStr;
        int i=1;
        //  Username checking
        if (true){
            
			cout << "Password: ";
			cin >> user;
			send(sock, user.c_str(), user.size() + 1, 0);
            bytesReceived = recv(sock, buf, 4096, 0);
            //password checking
            if (string(buf,0, bytesReceived) == ("correct")){
                cout<< ""<< endl;
                cout << "--Giris Islemi Basarili--" << endl;
                cout<< ""<< endl;
                do {
                cout << "1-Hesap Bilgilerini Gosterme." << endl;
                cout << "2-Hesaba Para Yatirma." << endl;
                cout << "3-Hesaptan Para Cekme." << endl;
                cout << "4-Baska Hesaba Para Yatirma." << endl;
                cout<< ""<< endl;
                cout << "Lutfen yapmak istediginiz islem numarasini giriniz: ";
                cin>>choice;
                cout<< ""<< endl;
                if(choice<=0 || choice>=5) {
                    cout << "Yanlis bir secim yapildi.Yeniden Deneyin."<<endl;
                    cout<< ""<< endl;
                }

                }while(choice<=0 || choice>=5);

                
                string response="1";
                switch(choice) {
                    case 1:{
                        choiceStr=to_string(choice);
                        send(sock, choiceStr.c_str(), choiceStr.size() + 1, 0);
                        for(int i=0;i<5;i++){
                            if(i==0){
                                cout << "Isim: ";
                            }
                            else if(i==1){
                                cout << "Soyisim: ";
                            }
                            else if(i==2){
                                cout << "Banka Adi: ";
                            }
                            else if(i==3){
                                cout << "Hesap Numarasi: ";
                            }else
                            {
                                cout << "Hesap Bakiyesi: ";
                            }
                            bytesReceived = recv(sock, buf, 4096, 0);
                            cout << string(buf,0, bytesReceived) << endl;
                            send(sock, response.c_str(), response.size() + 1, 0);

                        }
                        cout<< "    "<< endl;
                }
                    break;

                    case 2:{
                        int value;
                        choiceStr=to_string(choice);
                        send(sock, choiceStr.c_str(), choiceStr.size() + 1, 0);
                        bytesReceived = recv(sock, buf, 4096, 0);

                        cout << "Hesap Bakiyeniz: "<< (string(buf,0, bytesReceived)) << endl;
                        cout<< ""<< endl;
                        
                        cout << "Lutfen yatirmak istediginiz tutari giriniz: ";
                        cin >> value;
                        cout<< ""<< endl;
                        string valueStr;
                        valueStr= to_string(value);
                        send(sock, valueStr.c_str(), valueStr.size() + 1, 0);
                        bytesReceived = recv(sock, buf, 4096, 0);
                        cout << "Hesap Bakiyeniz: " << (string(buf,0, bytesReceived)) <<endl;
                        cout<< ""<< endl;

                    }
                    break;

                    case 3:{
                        int value;
                        choiceStr=to_string(choice);
                        send(sock, choiceStr.c_str(), choiceStr.size() + 1, 0);
                        bytesReceived = recv(sock, buf, 4096, 0);
                        string oldValue = (string(buf,0, bytesReceived));
                        int toplamBakiye = stoi(oldValue);
                        do {
                            if(value > toplamBakiye){
                            cout << "Hesabinizda bulunandan daha fazla bir miktar girdiniz!" << endl;
                            }
                        cout << "Hesap Bakiyeniz: "<< oldValue << endl;
                        cout<< ""<< endl;
                        cout << "Lutfen cekmek istediginiz tutari giriniz: ";
                        cin >> value;
                        cout<< "" << endl;
                        }while(value > toplamBakiye);
                        string valueStr;
                        valueStr= to_string(value);

                        send(sock, valueStr.c_str(), valueStr.size() + 1, 0);
                        bytesReceived = recv(sock, buf, 4096, 0);
                        
                        
                        toplamBakiye = stoi((string(buf,0, bytesReceived)));
                        if(toplamBakiye != -1) {
                            cout << "Hesap Bakiyeniz: " << (string(buf,0, bytesReceived)) <<endl;
                        }
                        cout<< ""<< endl;
                    }
                    break;

                    case 4:
                    {
                        string tarName,tarSurname,noStr,valueStr;
                        int targetNo,value;
                        choiceStr=to_string(choice);
                        
                        send(sock, choiceStr.c_str(), choiceStr.size() + 1, 0);
                        bytesReceived = recv(sock, buf, 4096, 0);
                        
                        string oldValue = (string(buf,0, bytesReceived));
                        cout << "Farkli banka ile yapilan islemlerde 5 TL islem ucreti olarak gondericiden alinacaktir."<< endl;
                        cout<< "    " << endl;
                        cout << "Hesap Bakiyeniz: TL"<< oldValue << endl;
                        cout << "Para Gnderilecek Hesap No: ";
                        cin >> targetNo;
                        noStr = to_string(targetNo);
                        
                        send(sock, noStr.c_str(), noStr.size() + 1, 0);
                        bytesReceived = recv(sock, buf, 4096, 0);
                        
                        cout << "Para Gonderilecek Kisi Ismi: ";
                        cin >> tarName;
                        
                        send(sock, tarName.c_str(), tarName.size() + 1, 0);
                        bytesReceived = recv(sock, buf, 4096, 0);
                        
                        cout << "Para Gonderilecek Kisi Soyismi: ";
                        cin >> tarSurname;
                        
                        send(sock, tarSurname.c_str(), tarSurname.size() + 1, 0);
                        bytesReceived = recv(sock, buf, 4096, 0);
                        
                        cout << "Gondermek istenen para miktari: $";
                        cin >> value;
                        valueStr = to_string(value);
                        
                        send(sock, valueStr.c_str(), valueStr.size() + 1, 0);
                        bytesReceived = recv(sock, buf, 4096, 0);

                        string bakiyeLast = (string(buf,0, bytesReceived));
                        int bakiyeInt = stoi(bakiyeLast);
                        if(bakiyeInt==-1){
                            cout << "Yanlis hesap Bilgileri girildi."<<endl;
                            }
                        else if(bakiyeInt==-2)
                        {
                            cout << "Hesabinizda yeterli bakiye bulunmamaktadir."<<endl;
                        }
                        else{
                        
                             cout << "Hesap Bakiyeniz: $"<< bakiyeLast << endl;
                        }
        
                    }
                    break;  
                }

            }else{
                cout << "Kullanici adi veya parola hatali." << endl;
                continue;
            }   
        }else
        {
            
            continue;
        }
        
    } while(true);

    //	Close the socket
    close(sock);

    return 0;
}

int main(){
    //Calling the client function for endless loop
	client();

}
