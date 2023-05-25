// TekSayfa-OOP.cpp


#include <iostream>
#include <regex>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <ctime>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS



using namespace std;



// class prototyping
class Utility;
class Kiyafet;
class KiyafetList;
class Kisi;
class Kullanici;
class Siparis;
class Yonetici;
class Kurye;
class Zaman;

#pragma region Global Degiskenler
int kullanicilarTxtLineUzunlugu;


vector<Kullanici> uyeler;
vector<Yonetici> yoneticiler;
vector<string> fisler;
vector<string> sikayetler;
vector<Kurye> kuryeler;

fstream kullanicilarOkumaDosyasi;
fstream fisOkumaDosyasi;
string satir;

#pragma endregion

Kurye KuryeAtamasi(vector<Kurye> kuryeler);
void txtyeVerileriYaz(char* ad_soyad, char* kullanici_adi, char* eposta, char* sifre, char* telno, char* adres_ilce, char* dtarihi, char* indirimKodu);




#pragma region UTILITY
class Utility
{
public:

	char* stringToChar(string);
	string charToString(char*); // buna da çok da gerek yok ama dursun 

	string* getTxtContent(string, int);
	int TxtlineCount(string);

	vector<vector<string>> splitListItems(string[], int);
	Kullanici KullaniciObjesiYarat(string, string, string, string, string, string, string, string);


};

char* Utility::stringToChar(string str)
{
	char* chr = new char[str.length()];
	for (int i = 0; i < str.length(); i++)
	{
		chr[i] = str[i];
	}
	chr[str.length()] = '\0';

	// char*'lar c-type stringlerdir. 
	// stringler '\0' karakterine sahiptir ki bellek nereye kadar okuyacağını bilsin, \0 görünce okumayı bırakır
	// char * sonuna \0 ekleyince artık garbage valuelar okunmuyor gerçek bir string'e dönüşüyor.

	return chr;
}

string Utility::charToString(char* chr)
{
	string str;
	str = chr;
	return str;
}

int Utility::TxtlineCount(string txtName)
{
	ifstream read;
	string line;
	int numberOfLines = 0;

	read.open(txtName, ios::app);

	if (read.is_open())
	{
		while (!(read.eof()))
		{
			getline(read, line);
			numberOfLines++;
		}
	}
	read.close();
	return numberOfLines;
}

string* Utility::getTxtContent(string txtName, int txtLineCount)
{
	ifstream read;
	string line;
	string* txtLines = new string[txtLineCount + 1];
	int i = 0;

	read.open(txtName, ios::app);

	if (read.is_open())
	{
		for (int i = 0; i < txtLineCount; i++)
		{
			getline(read, line);
			txtLines[i] = line;
		}
	}
	read.close();
	return txtLines;
}

vector<vector<string>> Utility::splitListItems(string list[], int listSize)
{
	string bracket = ",";
	string line;
	vector<string> words;
	vector<vector<string>> lines;

	for (int i = 0; i < listSize; i++)
	{
		int pos = 0;
		int wordsindex = 0;


		line = list[i];


		while ((pos = line.find(bracket)) != string::npos)
		{
			words.push_back(line.substr(0, pos));
			line = line.erase(0, pos + bracket.length());
		}
		words.push_back(line);

		lines.push_back(words);

		for (int j = 0; j < words.size(); j++) // sizeından bir eksik yazılıyor
		{
			words.clear();
		}
	}

	return lines;
}

#pragma endregion

#pragma region KIYAFET 
class Kiyafet
{
private:
	char* kategori;
	int kiyafet_adi;
	char* boyut;
	char* renk;

protected:
	double fiyat;

public:
	Kiyafet(int, char*, char*, char*, double);
	Kiyafet()
	{

	}
	Utility utility;

	void setKategori(char*);
	char* getKategori();

	void setKiyafetAdi(int);
	int getKiyafetAdi();

	void setFiyat(double);
	double getFiyat();

	void setBoyut(char*);
	char* getBoyut();

	void setRenk(char*);
	char* getRenk();


};
/*
kıyafetleri dosyadan alıp her bir satırı vektöre koyacağız pointer listtede tutabiliriz, daha sonra silinme işlemi de yapılabilir
her bir satır ayrıştırılıp dizi haline getirelecek
her bir diziyi bir kıyafet objesine atayacağız ve bir obje listesinde tutacağız.
bunun için ayrı kifayetList adında bir class ve fonksiyonlarına ihtiyaç var.
*/
Kiyafet::Kiyafet(int kiyafet_adi, char* kategori, char* renk, char* boyut, double fiyat)
{
	setKategori(kategori);
	setKiyafetAdi(kiyafet_adi);
	setFiyat(fiyat);
	setBoyut(boyut);
	setRenk(renk);
}

// elbise tshirt pantolon gömlek etek ayakkabı
void Kiyafet::setKategori(char* kategori)
{
	string strkategory = utility.charToString(kategori);
	while (true)
	{
		if ((strkategory == "elbise") || (strkategory == "tshirt") || (strkategory == "pantolon") || (strkategory == "gomlek") || (strkategory == "etek") || (strkategory == "ayakkabi"))
		{
			this->kategori = kategori;
			break;
		}
		else
		{
			string tempstr;
			char* tempchr = nullptr;
			cout << "yanlis kategori girisi yaptiniz. lutfen tekrar giriniz: ";
			cin >> tempstr;
			tempchr = utility.stringToChar(tempstr);
			setKategori(tempchr);
			break;
		}
	}
}
char* Kiyafet::getKategori()
{
	return this->kategori;
}

void Kiyafet::setKiyafetAdi(int kiyafet_adi)
{
	this->kiyafet_adi = kiyafet_adi;
}
int Kiyafet::getKiyafetAdi()
{
	return this->kiyafet_adi;
}

void Kiyafet::setFiyat(double fiyat)
{
	while (true)
	{
		if (fiyat > 0.0)
		{
			this->fiyat = fiyat;
			break;
		}
		else
		{
			double tempFiyat;
			cout << " fiyat 0 ya da negatif bir deger olamaz. lütfen dogru giriniz: ";
			cin >> tempFiyat;
			setFiyat(tempFiyat);
			break;
		}
	}
}
double Kiyafet::getFiyat()
{
	return this->fiyat;
}

void Kiyafet::setBoyut(char* pboyut)
{
	string strboyut = utility.charToString(pboyut);

	while (true)
	{
		if ((strboyut == "s") || (strboyut == "m") || (strboyut == "l") || (strboyut == "xl"))
		{
			this->boyut = pboyut;
			break;
		}
		else
		{
			string tempstr;
			char* tempchr = nullptr;
			cout << "yanlis boyut girisi yaptiniz. lutfen tekrar giriniz: ";
			cin >> tempstr;
			tempchr = utility.stringToChar(tempstr);
			setBoyut(tempchr);
			break;
		}
	}
}
char* Kiyafet::getBoyut()
{
	return this->boyut;
}

// mavi, yeşil, kırmızı, sarı, siyah, beyaz
void Kiyafet::setRenk(char* renk)
{
	string strrenk = utility.charToString(renk);
	while (true)
	{
		if ((strrenk == "mavi") || (strrenk == "yesil") || (strrenk == "kirmizi") || (strrenk == "sari") || (strrenk == "siyah") || (strrenk == "beyaz"))
		{
			this->renk = renk;
			break;
		}
		else
		{
			string tempstr;
			char* tempchr = nullptr;
			cout << "yanlis renk girisi yaptiniz. lutfen tekrar giriniz: ";
			cin >> tempstr;
			tempchr = utility.stringToChar(tempstr);
			setRenk(tempchr);
			break;
		}
	}
}
char* Kiyafet::getRenk()
{
	return this->renk;
}

#pragma endregion

#pragma region KiyafetList 
// bir nevi linked list olacak her seferinde son item nullptr olacak 
// forlar da nullptr gelene kadar çalıştırılır

class KiyafetList
{
private:
	vector<Kiyafet> kiyafetvector;
public:

	Utility utility;

	KiyafetList();

	void UrunEkle(Kiyafet& kiyafet);

	void UrunSil(int id);//

	Kiyafet& getUrun(int id);
	void KategoriyeGoreAra(char* kategori);//

	void urunleriGoruntule();
	void urunuGoruntule(int id); // kiyafet adına göre arıyacak, kiyafetin tüm özellikleri gösterilir.

	int DepodakiUrunMiktari();
	Kiyafet& KiyafetObjesiYarat(string sisim, string skategori, string srenk, string sboyut, string sfiyat);
};
KiyafetList::KiyafetList()
{
	// txt den kiyafet verilerini çek
	int lineCount = utility.TxtlineCount("kiyafetdeposu.txt");
	string* depoSatirlari = utility.getTxtContent("kiyafetdeposu.txt", lineCount);
	vector<vector<string>> bolunmusDepoListesi = utility.splitListItems(depoSatirlari, lineCount);

	// her bir satırı kiyafet objesine dönüştür
	for (int satirIndex = 0; satirIndex < lineCount; satirIndex++)
	{
		Kiyafet kiyafet = KiyafetObjesiYarat(bolunmusDepoListesi[satirIndex][0], // kiyafet adi
			bolunmusDepoListesi[satirIndex][1],  // kategori
			bolunmusDepoListesi[satirIndex][2],  // renk
			bolunmusDepoListesi[satirIndex][3],  // boyut
			bolunmusDepoListesi[satirIndex][4]);  // fiyat

		// kiyafetListesi objesi için depo vectörümüze ürünlerimizi pushluyoruz
		kiyafetvector.push_back(kiyafet);

		// depo objesi oluşturulduğu an içi dolu gelecek
	}
}

void KiyafetList::UrunEkle(Kiyafet& kiyafet)
{
	this->kiyafetvector.push_back(kiyafet);
}

void KiyafetList::UrunSil(int id)
{
	if (kiyafetvector.size() != 0) // listede eleman var ise
	{
		for (int i = 0; i < kiyafetvector.size(); i++)
		{
			if (kiyafetvector[i].getKiyafetAdi() == id)
			{
				kiyafetvector.erase(kiyafetvector.begin() + i);
			}
			else
			{
				cout << "kiyafet bulunamadi";
			}
		}
	}
	else
	{
		cout << "bombos...";
	}
}

// sonradan menüye eklenebilir
void KiyafetList::KategoriyeGoreAra(char* kategori) // int 
{
	if (kiyafetvector.size() != 0)
	{
		Utility utility;
		string strkategori_param = utility.charToString(kategori);
		string strkategori;

		for (int i = 0; i < kiyafetvector.size(); i++)
		{
			strkategori = utility.charToString(kiyafetvector[i].getKategori());

			if (strkategori == strkategori_param)
			{
				cout << std::left << setw(7) << kiyafetvector[i].getKiyafetAdi() << "- "
					<< std::left << setw(10) << kiyafetvector[i].getKategori() << setw(5) << " "
					<< std::left << setw(10) << kiyafetvector[i].getRenk() << " - "
					<< std::left << setw(5) << kiyafetvector[i].getBoyut()
					<< std::left << kiyafetvector[i].getFiyat() << " TL"
					<< endl;
			}
			else
			{
				cout << "kategori bulunamadi";
			}
		}
	}
	else
	{
		cout << "bombos...";
	}
}

Kiyafet& KiyafetList::getUrun(int id)
{
	if (kiyafetvector.size() != 0)
	{
		for (int i = 0; i < kiyafetvector.size(); i++)
		{
			if (kiyafetvector[i].getKiyafetAdi() == id)
			{
				return kiyafetvector[i];
			}
		}
	}
	else
	{
		cout << "bombos...";
	}

}

void KiyafetList::urunleriGoruntule()
{
	if (kiyafetvector.size() != 0)
	{
		for (int i = 0; i < kiyafetvector.size(); i++)
		{

			cout << std::left << setw(6) << kiyafetvector[i].getKiyafetAdi() << "- "
				<< std::left << setw(10) << kiyafetvector[i].getKategori() << setw(5) << " "
				<< std::left << setw(10) << kiyafetvector[i].getRenk() << " - "
				<< std::left << setw(5) << kiyafetvector[i].getBoyut()
				<< std::left << kiyafetvector[i].getFiyat() << " TL"
				<< endl;
		}
	}
	else
	{
		cout << "bombos...";
	}
}

void KiyafetList::urunuGoruntule(int id)
{
	if (kiyafetvector.size() != 0)
	{
		for (int i = 0; i < kiyafetvector.size(); i++)
		{
			if (kiyafetvector[i].getKiyafetAdi() == id)
			{
				cout << kiyafetvector[i].getKiyafetAdi() << "- "
					<< kiyafetvector[i].getKategori() << endl
					<< kiyafetvector[i].getRenk() << " - "
					<< kiyafetvector[i].getBoyut() << endl
					<< kiyafetvector[i].getFiyat() << " TL"
					<< endl;
			}
			else
			{
				cout << "kiyafet bulunamadi";
			}
		}
	}
	else
	{
		cout << "bombos...";
	}
}

int KiyafetList::DepodakiUrunMiktari()
{
	return kiyafetvector.size();
}

// utility'ye atılabilir
Kiyafet& KiyafetList::KiyafetObjesiYarat(string sisim, string skategori, string srenk, string sboyut, string sfiyat)
{
	Utility utility;
	int kiyafet_adi = stoi(sisim);
	char* kategori = utility.stringToChar(skategori);
	char* renk = utility.stringToChar(srenk);
	char* boyut = utility.stringToChar(sboyut);
	double fiyat = stod(sfiyat);


	Kiyafet kiyafet = Kiyafet(kiyafet_adi, kategori, renk, boyut, fiyat);
	return kiyafet;
}

#pragma endregion

#pragma region KISI
class Kisi
{
protected:
	// data member
	char* ad_soyad;
	char* telno;


public:
	Kisi(char*, char*);
	Kisi()
	{

	}

	Utility utility;
	// komposizyon olacağı kesin fakat static olmalı mı emin değilim 

	void setAdSoyad(char*);
	char* getAdSoyad() const;

	void setTelNo(char*);
	char* getTelNo() const;

};


Kisi::Kisi(char* ad_soyad, char* telno)
{
	setAdSoyad(ad_soyad);
	setTelNo(telno);
}

void Kisi::setAdSoyad(char* ad_soyad)
{
	this->ad_soyad = ad_soyad;
}
char* Kisi::getAdSoyad() const
{
	return this->ad_soyad;
}


void Kisi::setTelNo(char* telno)
{
	this->telno = telno;
}
char* Kisi::getTelNo() const
{
	return this->telno;
}

#pragma endregion

#pragma region KULLANICI
class Kullanici : public Kisi // kullanıcı id eklenebilir
{
private:
	// const tanımlayıp member initialize içerisinde fonksiyon kullanabilme
	char* kullanici_adi;
	char* eposta;
	char* adres_ilcesi;
	char* sifre;
	char* indirim_kodu;
	char* dtarihi;

	// utility function
	bool IsEpostaValid(string);

	string PasswordStrongness(string);
	bool IsSifreValid(string);

	bool IsDtarihiValid(string);

public:

	Kullanici(char*, char*, char*, char*, char*, char*, char*, char*);
	Kullanici()
	{

	}

	void setKullanici_adi(char*);
	char* getKullanici_adi() const;

	void setEposta(char*);
	char* getEposta() const;

	void setAdres_ilce(char*);
	char* getAdres_ilce() const;

	void setSifre(char*);
	char* getSifre() const;

	void setIndirim_kodu(char*);
	char* getIndirim_kodu() const;

	void setDtarihi(char*);
	char* getDtarihi() const;

	void operator = (const Kullanici&);

	Kullanici uyeKaydiOlustur();

	void SikayetAl();



};


Kullanici::Kullanici(char* name, char* kullanici_adi, char* eposta, char* sifre,
	char* telno, char* adres_ilce, char* dtarihi, char* indirim_kodu = 0)
	:Kisi(name, telno)
{
	setKullanici_adi(kullanici_adi);
	setEposta(eposta);
	setAdres_ilce(adres_ilce);
	setSifre(sifre);
	setDtarihi(dtarihi);

	char* default_kod = utility.stringToChar("0");
	// ileride kullanırken de 0 olmadığı sürece indirim kodunu uygula denir.
	setIndirim_kodu(default_kod);

}

bool Kullanici::IsEpostaValid(string email)
{
	bool goodstarting = false;      // başında sayı @ olmayacak
	bool hasAt = false;         // @ içerecek
	bool goodending = false;    // .com içerecek

	bool hasvalidservice = false;    // gmail, hotmail vb. kontrolü
	string validServices[2] = { "hotmail", "gmail" };


	// kontroller
	if (email[0] != ('@') && not(isdigit(email[0]))) { goodstarting = true; } // başlangıcında @ yoksa ve başı digit değilse

	size_t foundAt = email.find('@'); // içinde @ bulunuyor
	if (foundAt != string::npos) { hasAt = true; }

	for (int i = 0; i < 2; i++)  // belirtilen email servislerinden biri mevcut 
	{
		size_t foundService = email.find(validServices[i]);
		if (foundService != string::npos) { hasvalidservice = true; break; }
	}

	if (email.substr(email.length() - 4) == ".com") { goodending = true; } // sonunda .com var

	if (goodstarting && goodending && hasAt && hasvalidservice)
		return true;
	else
		return false;
}

string Kullanici::PasswordStrongness(string password)
{

	int sifre_uzunlugu = password.length();
	bool buyuk_harf = false;
	bool kucuk_harf = false;
	bool rakam = false;

	string special_chars = "~! @#$%^&*()_-+={[}]|:;'<,>.?/";
	bool ozel_char = false;

	for (int i = 0; i < sifre_uzunlugu; i++)
	{
		if (isupper(password[i])) { buyuk_harf = true; }
		if (islower(password[i])) { kucuk_harf = true; }
		if (isdigit(password[i])) { rakam = true; }

		size_t found = password.rfind(special_chars);
		if (found != std::string::npos) { ozel_char = true; }
	}

	string return_value;

	if (buyuk_harf && kucuk_harf && rakam && ozel_char && (sifre_uzunlugu >= 8))
	{
		return_value = " cok guclu";
	}
	if (buyuk_harf && kucuk_harf && rakam && (sifre_uzunlugu >= 8))
	{
		return_value = "guclu";
	}
	else if ((buyuk_harf || kucuk_harf) && (sifre_uzunlugu >= 8))
	{
		return_value = "ortalama";
	}
	else
	{
		return_value = "zayif";
	}
	return return_value;
}
bool Kullanici::IsSifreValid(string strogness)
{
	if ((strogness == "guclu") || (strogness == "ortalama"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Kullanici::IsDtarihiValid(string date) // 2/5/2000 şeklinde gelecek
{
	// gelen tarihi bölme kısmı
	string ayrac = "-";
	string line = date;
	string* splittedDate = new string[3];
	int pos = 0;
	int index = 0;

	while ((pos = line.find(ayrac)) != string::npos)
	{
		splittedDate[index++] = line.substr(0, pos);
		line = line.erase(0, pos + ayrac.length());
	}
	splittedDate[2] = line;

	// validation için verilerin atanması
	int day, month, year;

	day = stoi(splittedDate[0]);
	month = stoi(splittedDate[1]);
	year = stoi(splittedDate[2]);

	// validation
	if (1000 <= year <= 3000)
	{
		if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day > 0 && day <= 31)
			return true;
		else
			if (month == 4 || month == 6 || month == 9 || month == 11 && day > 0 && day <= 30)
				return true;
			else
				if (month == 2)
				{
					if ((year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) && day > 0 && day <= 29)
						return true;
					else if (day > 0 && day <= 28)
						return true;
					else
						return false;
				}
				else
					return false;
	}
	else
		return false;
}


void Kullanici::setKullanici_adi(char* param)
{
	this->kullanici_adi = param;
}
char* Kullanici::getKullanici_adi() const
{
	return this->kullanici_adi;
}

void Kullanici::setEposta(char* param)
{
	bool isValid = IsEpostaValid(param);
	while (true)
	{
		if (isValid)
		{
			this->eposta = param;
			break;
		}
		else
		{
			char* tempchar = nullptr;
			string tempstr;

			cout << "gecersiz eposta girimi lutfen bir daha giriniz: ";
			cin >> tempstr;
			tempchar = utility.stringToChar(tempstr);
			setEposta(tempchar);
			break;
		}
	}
}
char* Kullanici::getEposta() const
{
	return this->eposta;
}

void Kullanici::setAdres_ilce(char* param)
{
	this->adres_ilcesi = param;
}
// belirtilen adreslerden birine seçim yapınız gibi bir seçenek belirlenebilir.
char* Kullanici::getAdres_ilce() const
{
	return this->adres_ilcesi;
}

void Kullanici::setSifre(char* param)
{
	string parameter = utility.charToString(param);
	string strongness = PasswordStrongness(parameter);
	bool isValid = IsSifreValid(strongness);
	while (true)
	{
		if (isValid)
		{
			this->sifre = param;
			break;
		}
		else
		{
			char* tempchar = nullptr;
			string tempstr;

			cout << "gecersiz sifre girimi lutfen bir daha giriniz: ";
			cin >> tempstr;
			tempchar = utility.stringToChar(tempstr);
			setSifre(tempchar);
			break;
		}
	}
}
char* Kullanici::getSifre() const
{
	return this->sifre;
}

void Kullanici::setIndirim_kodu(char* param)
{
	this->indirim_kodu = param;
}
char* Kullanici::getIndirim_kodu() const
{
	return this->indirim_kodu;
}

void Kullanici::setDtarihi(char* param)
{
	bool isValid = IsDtarihiValid(param);
	while (true)
	{
		if (isValid)
		{
			this->dtarihi = param;
			break;
		}
		else
		{
			char* tempchar = nullptr;
			string tempstr;

			cout << "gecersiz dogum tarihi girimi lutfen bir daha giriniz: ";
			cin >> tempstr;
			tempchar = utility.stringToChar(tempstr);
			setDtarihi(tempchar);
			break;
		}
	}
}
char* Kullanici::getDtarihi() const
{
	return this->dtarihi;
}


void Kullanici::operator = (const Kullanici& kullanici)
{
	this->setAdSoyad(kullanici.getAdSoyad());
	this->setTelNo(kullanici.getTelNo());
	this->setKullanici_adi(kullanici.getKullanici_adi());
	this->setEposta(kullanici.getEposta());
	this->setAdres_ilce(kullanici.getAdres_ilce());
	this->setSifre(kullanici.getSifre());
	this->setIndirim_kodu(kullanici.getIndirim_kodu());
	this->setDtarihi(kullanici.getDtarihi());
}

Kullanici Kullanici::uyeKaydiOlustur()
{
	string ad;
	string soyad;
	char* kullanici_adi = new char;
	char* eposta = new char;
	char* sifre = new char;
	char* telno = new char;
	char* adres_ilcesi = new char;
	int adres_no;
	char* dtarihi = new char;

	cout << "* Kullanici adiniz bosluk ve turkce karakter icermemelidir.\n";
	cout << "* Sifreniz en az 8 karakter uzunlugunda, buyuk ve kucuk harf, ozel karakter icermelidir.\n";
	cout << "* Telefon numaranızı 01234567890 formatında giriniz.\n";
	cout << "* Dogum tarihinizi 2-5-2000 formatında giriniz.\n";
	cout << std::left << setw(20) << "Isim: ";
	cin >> ad;
	cout << std::left << setw(20) << "Soyisim: ";
	cin >> soyad;
	cout << std::left << setw(20) << "Kullanici Adi: ";
	cin >> kullanici_adi;
	cout << std::left << setw(20) << "Eposta: ";
	cin >> eposta;
	cout << std::left << setw(20) << "Sifre: ";
	cin >> sifre;
	cout << std::left << setw(20) << "Telefon no: ";
	cin >> telno;
	cout << std::left << setw(20) << "Dogum Tarihiniz: ";
	cin >> dtarihi;
	cout << "\nSu adreslerden birini seciniz,\n";
	cout << "1- Ortahisar\n2- Akcaabat\n 3- Vakfikebir\n4- Besikdüzü\n5- Yomra\n6- Arsin\n7- Arakli\n";
	cout << std::left << setw(20) << "Adresiniz: ";
	cin >> adres_no;
	while (true)
	{
		if (adres_no == 1)
		{
			adres_ilcesi = utility.stringToChar("Ortahisar");
			break;
		}
		else if (adres_no == 2)
		{
			adres_ilcesi = utility.stringToChar("Akcaabat");
			break;
		}
		else if (adres_no == 3)
		{
			adres_ilcesi = utility.stringToChar("Vakfikebir");
			break;
		}
		else if (adres_no == 4)
		{
			adres_ilcesi = utility.stringToChar("Besikdüzü");
			break;
		}
		else if (adres_no == 5)
		{
			adres_ilcesi = utility.stringToChar("Yomra");
			break;
		}
		else if (adres_no == 6)
		{
			adres_ilcesi = utility.stringToChar("Arsin");
			break;
		}
		else if (adres_no == 7)
		{
			adres_ilcesi = utility.stringToChar("Arakli");
			break;
		}
		else
		{
			cout << "\nyanlıs giris yaptiniz...|\n\n";
		}
	}

	cout << "whiledan cıktı";
	string s_isim_soyisim = ad + " " + soyad;

	char* ad_soyad = utility.stringToChar(s_isim_soyisim);

	Kullanici kullanici = Kullanici(ad_soyad, kullanici_adi, eposta, sifre, telno, adres_ilcesi, dtarihi);

	return kullanici;
}

Kullanici KullaniciObjesiYarat(string pad_soyad, string pkullanici_adi, string peposta, string psifre,
	string ptelno, string padres_ilcesi, string pdtarihi, string pindirim_kodu)
{
	Utility utility;
	char* ad_soyad = utility.stringToChar(pad_soyad);
	char* kullanici_adi = utility.stringToChar(pkullanici_adi);
	char* eposta = utility.stringToChar(peposta);
	char* adres = utility.stringToChar(padres_ilcesi);
	char* sifre = utility.stringToChar(psifre);
	char* indirim_kodu = utility.stringToChar(pindirim_kodu);
	char* dtarihi = utility.stringToChar(pdtarihi);
	char* telno = utility.stringToChar(ptelno);


	Kullanici user = Kullanici(ad_soyad, kullanici_adi, eposta, sifre, telno, adres, dtarihi, indirim_kodu);
	return user;
}

void Kullanici::SikayetAl()
{
	string sikayetveOneri;

	fstream log;
	log.open("sikayetveOneriler.txt", ios::out | ios::app);

	cout << "SIKAYET VE ONERILERINIZI GIRINIZ:" << endl;
	cin.ignore();
	getline(cin, sikayetveOneri);
	log << endl << sikayetveOneri;
	cout << "dileginiz alinmistir" << endl;
	log.close();
}

#pragma endregion

#pragma region ZAMAN
class Zaman
{
private:
	int dakika;
	int saat;
public:

	Zaman(int, int);

	void setSaat(int);
	int getSaat() const;

	void setDakika(int);
	int getDakika() const;

	string printZaman();

	friend ostream& operator<<(ostream& output, const Zaman& zaman);
	Zaman operator+(const Zaman& zaman);
	void operator = (const Zaman& zaman);
};


Zaman::Zaman(int saat = 0, int dakika = 0)
{
	setSaat(saat);
	while (dakika >= 60)
	{
		dakika = dakika - 60;
		this->saat = this->saat + 1;
	}
	setDakika(dakika);
}

void Zaman::setSaat(int saat)
{
	this->saat = saat;
}
int Zaman::getSaat() const
{
	return this->saat;
}

void Zaman::setDakika(int dakika)
{
	this->dakika = dakika;
}
int Zaman::getDakika() const
{
	return this->dakika;
}

string Zaman::printZaman()
{
	string _saat;
	string _dakika;
	if (this->saat < 10)
	{
		_saat = "0" + to_string(this->saat);
	}
	else { _saat = to_string(this->saat); }

	if (this->dakika < 10)
	{
		_dakika = "0" + to_string(this->dakika);
	}
	else { _dakika = to_string(this->dakika); }
	return _saat + ":" + _dakika;

}


ostream& operator<<(ostream& output, const Zaman& zaman)
{
	if (zaman.saat < 10)
	{
		output << "0" << zaman.saat;
	}
	else
	{
		output << zaman.saat;
	}
	output << ":";
	if (zaman.dakika < 10)
	{
		output << "0" << zaman.dakika;
	}
	else
	{
		output << zaman.dakika;
	}
	return output;
}

Zaman Zaman::operator+(const Zaman& zaman)
{
	int return_saat = this->saat + zaman.getSaat();
	int return_dakika = this->dakika + zaman.getDakika();

	while (return_dakika >= 60)
	{
		return_saat = return_saat + (return_dakika / 60); // return dakika diyelim 75 75/60=1,... +1 saat ekler
		return_dakika = return_dakika - 60; // kalan dakikayı da dakikaya yazar	 
	}
	Zaman return_zaman = Zaman(return_saat, return_dakika);

	return return_zaman;
}

void Zaman::operator = (const Zaman& zaman) //!!!!!!
{
	this->saat = zaman.getSaat();
	this->dakika = zaman.getDakika();
}


#pragma endregion

#pragma region SEPET
class Sepet
{
private:
	double sepetTotalFiyat;
	vector<Kiyafet> sepet;

	void setSepetTotalFiyat();


public:
	Sepet();
	void SepeteEkle(Kiyafet& kiyafet);
	void SepettenCikar(int id);
	void SepetiBosalt();
	void printSepet();
	double getSepetTotalFiyat();
	int getUrunAdedi();

	vector<Kiyafet> getSepet();

};



Sepet::Sepet()
{
	this->sepetTotalFiyat = 0;
}

void Sepet::SepeteEkle(Kiyafet& kiyafet)
{
	sepet.push_back(kiyafet);
	setSepetTotalFiyat();
}

void Sepet::SepettenCikar(int id)
{
	if (sepet.size() != 0) // listede eleman var ise
	{
		for (int i = 0; i < sepet.size(); i++)
		{
			if (sepet[i].getKiyafetAdi() == id)
			{
				sepet.erase(sepet.begin() + i);
				setSepetTotalFiyat();
			}
			else
			{
				cout << "kiyafet bulunamadi";
			}
		}
	}
	else
	{
		cout << "sepet bombos..." << endl;
	}
}

void Sepet::SepetiBosalt()
{
	sepet.clear();
}

void Sepet::printSepet()
{
	if (sepet.size() != 0)
	{
		for (int i = 0; i < sepet.size(); i++)
		{

			cout << std::left << setw(6) << sepet[i].getKiyafetAdi() << "- "
				<< std::left << setw(10) << sepet[i].getKategori() << setw(5) << " "
				<< std::left << setw(10) << sepet[i].getRenk() << " - "
				<< std::left << setw(5) << sepet[i].getBoyut()
				<< std::left << sepet[i].getFiyat() << " TL"
				<< endl;
		}
	}
	else
	{
		cout << "bombos...";
	}
}

void Sepet::setSepetTotalFiyat()
{
	double total = 0.0;
	if (sepet.size() != 0)
	{
		for (int i = 0; i < sepet.size(); i++)
		{
			total = total + sepet[i].getFiyat();
		}
		this->sepetTotalFiyat = total;
	}
	else
	{
		cout << "bombos...";
	}
}
double Sepet::getSepetTotalFiyat()
{
	return this->sepetTotalFiyat;
}

int Sepet::getUrunAdedi()
{
	return this->sepet.size();
}


vector<Kiyafet> Sepet::getSepet()
{
	return this->sepet;

}

#pragma endregion

#pragma region SIPARIS
class Siparis :Kiyafet
{
private:
	int siparis_no;
	double siparis_fiyat;
	Zaman siparis_baslangic;
	Zaman siparis_ulasim;
	char* adres;
	Zaman adres_default_ulasim_zamani;
	Kullanici siparis_sahibi;
	int kuryeID;
	int urun_adedi;

public:
	Siparis(Kiyafet, Kullanici);
	Siparis(Sepet, Kullanici);
	Siparis()
	{

	}

	void setSiparisNo();
	int getSiparisNo();

	void setSiparisFiyatı(double);
	double getSiparisFiyatı();

	void setSiparisBaslangic();
	Zaman getSiparisBaslangic();

	void setSiparisUlasim(Zaman);
	Zaman getSiparisUlasim();

	void setAdres(char*);
	char* getAdres();

	void setAdresZamani();
	Zaman getAdresZamani();

	void setKurye(int id);
	int getKurye();

	int getUrunAdedi();

	void SiparisGoruntule(Kullanici user);
	void FisOlustur(Sepet sepet);
	void FisOlustur();


};


Siparis::Siparis(Kiyafet kiyafet, Kullanici siparis_sahibi) // , vector<Kiyafet> sepet
	:Kiyafet(kiyafet.getKiyafetAdi(), kiyafet.getKategori(), kiyafet.getRenk(), kiyafet.getBoyut(), kiyafet.getFiyat())
{
	setSiparisNo();

	this->siparis_sahibi = siparis_sahibi;

	setAdres(this->siparis_sahibi.getAdres_ilce());
	setAdresZamani();

	setSiparisFiyatı(this->fiyat);

	setSiparisBaslangic();

	this->urun_adedi = 1;

}

Siparis::Siparis(Sepet sepet, Kullanici siparis_sahibi)
	:Kiyafet()
{
	setSiparisNo();

	this->siparis_sahibi = siparis_sahibi;
	setAdres(this->siparis_sahibi.getAdres_ilce());
	setAdresZamani();

	setSiparisFiyatı(sepet.getSepetTotalFiyat());
	setSiparisBaslangic();

	this->urun_adedi = sepet.getUrunAdedi();
}

void Siparis::setSiparisNo() // 6 rakamlık bir siparis no
{
	srand(time(0));
	this->siparis_no = (rand() % 1000000);
}
int Siparis::getSiparisNo()
{
	return this->siparis_no;
}

void Siparis::setSiparisFiyatı(double fiyat)
{
	this->siparis_fiyat = fiyat;
}
double Siparis::getSiparisFiyatı()
{
	return this->siparis_fiyat;
}


void Siparis::setSiparisBaslangic()
{
	time_t now = time(0);
	tm* local_time = localtime(&now);
	siparis_baslangic.setSaat(local_time->tm_hour);
	siparis_baslangic.setDakika(local_time->tm_min);
}
Zaman Siparis::getSiparisBaslangic()
{
	return this->siparis_baslangic;
}

void Siparis::setSiparisUlasim(Zaman teslim)
{
	siparis_ulasim.setSaat(teslim.getSaat());
	siparis_ulasim.setDakika(teslim.getDakika());
}
Zaman Siparis::getSiparisUlasim()
{
	return this->siparis_ulasim;
}

void Siparis::setAdres(char* adres)
{
	this->adres = adres;
}
char* Siparis::getAdres()
{
	return this->adres;
}

void Siparis::setAdresZamani()
{
	Utility utility;
	// denensin

	if (utility.charToString(this->adres) == "Ortahisar")
	{
		Zaman zaman = Zaman(0, 35);
		this->adres_default_ulasim_zamani = zaman;
	}
	else if (utility.charToString(this->adres) == "Akcaabat")
	{
		Zaman zaman = Zaman(0, 50);
		this->adres_default_ulasim_zamani = zaman;
	}
	else if (utility.charToString(this->adres) == "Vakfikebir")
	{
		Zaman zaman = Zaman(0, 90);
		this->adres_default_ulasim_zamani = zaman;
	}
	else if (utility.charToString(this->adres) == "Besikdüzü")
	{
		this->adres_default_ulasim_zamani = Zaman(0, 110);
	}
	else if (utility.charToString(this->adres) == "Yomra")
	{
		this->adres_default_ulasim_zamani = Zaman(0, 55);
	}
	else if (utility.charToString(this->adres) == "Arsin")
	{
		this->adres_default_ulasim_zamani = Zaman(0, 70);
	}
	else if (utility.charToString(this->adres) == "Arakli")
	{
		this->adres_default_ulasim_zamani = Zaman(0, 100);
	}
}
Zaman Siparis::getAdresZamani()
{
	return this->adres_default_ulasim_zamani;
}

void Siparis::setKurye(int id)
{
	this->kuryeID = id;
}
int Siparis::getKurye()
{
	return this->kuryeID;
}

int Siparis::getUrunAdedi()
{
	return this->urun_adedi;
}


void Siparis::SiparisGoruntule(Kullanici user)
{
	// txt den fis verilerini çek
	int lineCount = utility.TxtlineCount("fis.txt");
	string* fisSatirlari = utility.getTxtContent("fis.txt", lineCount);
	vector<vector<string>> bolunmusFisSatirlari = utility.splitListItems(fisSatirlari, lineCount);
	string email = utility.charToString(user.getEposta());

	for (int satirIndex = 0; satirIndex < lineCount - 1; satirIndex++)
	{
		// eğer kullanıcının epostası ile satırdaki epposta uyuşuyorsa o halde satırdaki fatura verisini çek
		if (email == (bolunmusFisSatirlari[satirIndex][2]))
		{
			cout << "\n* SIPARISLERINIZ *\n" << endl;
			cout << std::left << setw(35) << "Siparis No: " << bolunmusFisSatirlari[satirIndex][0] << endl
				<< std::left << setw(35) << "Siparis Sahibi: " << bolunmusFisSatirlari[satirIndex][1] << endl
				<< std::left << setw(35) << "Siparis Sahibi Email: " << bolunmusFisSatirlari[satirIndex][2] << endl
				<< std::left << setw(35) << "Siparis Alim Saati: " << bolunmusFisSatirlari[satirIndex][3] << endl
				<< std::left << setw(35) << "Siparis Ulasim Saati: " << bolunmusFisSatirlari[satirIndex][4] << endl
				<< std::left << setw(35) << "Siparisi Teslim Edecek Kurye: " << bolunmusFisSatirlari[satirIndex][5] << endl
				<< std::left << setw(35) << "Siparis Toplam Fiyatı: " << bolunmusFisSatirlari[satirIndex][6] << endl
				<< "Siparis Icerigi:" << endl;

			for (int kelimeIndex = 7; kelimeIndex < (bolunmusFisSatirlari[satirIndex].size()); kelimeIndex++)
			{
				cout << "|- " << bolunmusFisSatirlari[satirIndex][kelimeIndex] << endl;
			}
		}
	}

	cout << "\n\n\n";
}

void Siparis::FisOlustur(Sepet sepet)
{
	fstream write;
	write.open("fis.txt", ios::in | ios::app);

	write << endl << getSiparisNo() << ","
		<< siparis_sahibi.getAdSoyad() << ","
		<< siparis_sahibi.getEposta() << ","
		<< getSiparisBaslangic() << ","
		<< getSiparisUlasim() << ","
		<< getKurye() << ","
		<< getSiparisFiyatı() << ",";



	for (int i = 0; i < sepet.getUrunAdedi(); i++)
	{
		write << std::left << setw(7) << sepet.getSepet()[i].getKiyafetAdi()
			<< std::left << setw(10) << sepet.getSepet()[i].getKategori()
			<< std::left << setw(10) << sepet.getSepet()[i].getRenk()
			<< std::left << setw(5) << sepet.getSepet()[i].getBoyut()
			<< std::left << sepet.getSepet()[i].getFiyat() << ",";
	}
}

void Siparis::FisOlustur()
{
	fstream write;
	write.open("fis.txt", ios::in | ios::app);
	write << endl << getSiparisNo() << ","
		<< siparis_sahibi.getAdSoyad() << ","
		<< siparis_sahibi.getEposta() << ","
		<< getSiparisBaslangic() << ","
		<< getSiparisUlasim() << ","
		<< getKurye() << ","
		<< getSiparisFiyatı() << ","
		<< std::left << setw(7) << getKiyafetAdi()
		<< std::left << setw(10) << getKategori()
		<< std::left << setw(10) << getRenk()
		<< std::left << setw(5) << getBoyut()
		<< std::left << getFiyat();

}


#pragma endregion

#pragma region KURYE
class Kurye : public Kisi
{
private:
	int kurye_id;
	int siparisMiktari;
	Zaman* dagitim_bitisler;
	int* siparisNumaraları;

public:
	Kurye(char* ad_soyad, char* telno, int id)
		:Kisi(ad_soyad, telno)
	{
		this->siparisMiktari = 0;

		setKuryeId(id);
		dagitim_bitisler = new Zaman();
		siparisNumaraları = new int();
	}

	Kurye() {}


	void setKuryeId(int id);
	int getKuryeId() const;

	int getSiparisMiktari() const;

	void setSiparis(Zaman ilce_zamani, int siparis_no);
	Zaman getSiparisTeslimZamani(int siparis_no) const;

	void operator = (const Kurye& kurye);

};


void Kurye::setKuryeId(int id)
{
	this->kurye_id = id;
}

int Kurye::getKuryeId() const
{
	return this->kurye_id;
}

int Kurye::getSiparisMiktari() const
{
	return siparisMiktari;
}

void Kurye::setSiparis(Zaman ilce_zamani, int siparis_no)
{
	if (this->siparisMiktari == 0)
	{
		dagitim_bitisler[siparisMiktari] = ilce_zamani;
		siparisNumaraları[siparisMiktari] = siparis_no;
	}
	else
	{
		dagitim_bitisler[siparisMiktari] = ilce_zamani + dagitim_bitisler[siparisMiktari - 1];
		siparisNumaraları[siparisMiktari] = siparis_no;
	}
	siparisMiktari++;

}
Zaman Kurye::getSiparisTeslimZamani(int siparis_no) const
{
	int target_index;

	for (int i = 0; i < siparisMiktari; i++)
	{
		if (siparisNumaraları[i] == siparis_no)
		{
			target_index = i;
		}
	}
	Zaman return_zaman = dagitim_bitisler[target_index];

	return return_zaman;
}

Kurye KuryeObjesiYarat(string pid, string pisim, string ptelno)
{
	Utility utility;
	int id = stoi(pid);
	char* ad_soyad = utility.stringToChar(pisim);
	char* telno = utility.stringToChar(ptelno);

	Kurye kurye = Kurye(ad_soyad, telno, id);
	return kurye;
}

void Kurye::operator = (const Kurye& kurye)
{
	this->kurye_id = kurye.getKuryeId();
	this->ad_soyad = kurye.getAdSoyad();
	this->telno = kurye.getTelNo();
	this->siparisMiktari = kurye.getSiparisMiktari();

	// deep copy 
	for (int i = 0; i < kurye.getSiparisMiktari(); i++)
	{
		this->dagitim_bitisler[i] = kurye.dagitim_bitisler[i];
	}

	for (int i = 0; i < kurye.getSiparisMiktari(); i++)
	{
		this->siparisNumaraları[i] = kurye.siparisNumaraları[i];
	}
}

#pragma endregion

#pragma region YONETICI
class Yonetici : public Kisi
{
private:
	char* sifre;

	// utility function

	string PasswordStrongness(string);
	bool IsSifreValid(string);

public:
	KiyafetList depo;

	Yonetici(char* ad_soyad, char* sifre, char* telno);
	Yonetici()
	{}

	void setSifre(char*);
	char* getSifre();


	void urunGirisi();
	void kuryeEklenmesi();
	void sikayetVeOneriler();
	void indirimKoduTanimla();
	void siparisFaturalariGoruntule();
};
Yonetici::Yonetici(char* ad_soyad, char* sifre, char* telno)
	:Kisi(ad_soyad, telno)

{
	setSifre(sifre);
}

string Yonetici::PasswordStrongness(string password)
{

	int sifre_uzunlugu = password.length();
	bool buyuk_harf = false;
	bool kucuk_harf = false;
	bool rakam = false;

	string special_chars = "~! @#$%^&*()_-+={[}]|:;'<,>.?/";
	bool ozel_char = false;

	for (int i = 0; i < sifre_uzunlugu; i++)
	{
		if (isupper(password[i])) { buyuk_harf = true; }
		if (islower(password[i])) { kucuk_harf = true; }
		if (isdigit(password[i])) { rakam = true; }

		size_t found = password.rfind(special_chars);
		if (found != std::string::npos) { ozel_char = true; }
	}

	string return_value;

	if (buyuk_harf && kucuk_harf && rakam && ozel_char && (sifre_uzunlugu >= 8))
	{
		return_value = " cok guclu";
	}
	if (buyuk_harf && kucuk_harf && rakam && (sifre_uzunlugu >= 8))
	{
		return_value = "guclu";
	}
	else if ((buyuk_harf || kucuk_harf) && (sifre_uzunlugu >= 8))
	{
		return_value = "ortalama";
	}
	else
	{
		return_value = "zayif";
	}
	return return_value;
}
bool Yonetici::IsSifreValid(string strogness)
{
	if ((strogness == "guclu") || (strogness == "ortalama"))
	{
		return true;
	}
	else {
		return false;
	}
}

void Yonetici::setSifre(char* param)
{
	string parameter = utility.charToString(param);
	string strongness = PasswordStrongness(parameter);
	bool isValid = IsSifreValid(strongness);
	while (true)
	{
		if (isValid)
		{
			this->sifre = param;
			break;
		}
		else
		{
			char* tempchar = nullptr;
			string tempstr;

			cout << "gecersiz sifre girimi lutfen bir daha giriniz: ";
			cin >> tempstr;
			tempchar = utility.stringToChar(tempstr);
			setSifre(tempchar);
			break;
		}
	}
}

char* Yonetici::getSifre()
{
	return sifre;
}


void Yonetici::urunGirisi()
{
	string urun_id;
	string kategori;
	string renk;
	string boyut;
	string fiyat;

	depo.urunleriGoruntule();
	cout << endl;


	cout << "1- Var olanin disinda bir id giriniz.\n2- Kategoriler : Pantolon, Etek, Gomlek, Elbise, Tshirt, Ayakkabi\n3- Renk Secenekleri : mavi, yesil, kirmizi, sari, siyah, beyaz\n4- Boyut Secenekleri : s, m, l, xl " << endl;
	cout << "5- Default para birimi -> TL" << endl;
	cout << "urun id:";
	cin >> urun_id;
	cout << "kategori :";
	cin >> kategori;
	cout << "renk:";
	cin >> renk;
	cout << "boyut:";
	cin >> boyut;
	cout << "fiyat :";
	cin >> fiyat;

	fstream write;
	write.open("kiyafetdeposu.txt", ios::in | ios::app);

	write << endl << urun_id << "," << kategori << "," << renk << "," << boyut << "," << fiyat;

	cout << "Isleminiz basariyla gerceklestirilmistir!!" << endl;

	int islem;
	cout << "Baska bir urun girisi yapmak istiyor musunuz?\n1- Evet\n2-Hayir" << endl;
	cin >> islem;

	if (islem == 1) {

		write.close();
		Kiyafet kiyafet = depo.KiyafetObjesiYarat(urun_id, kategori, renk, boyut, fiyat);
		depo.UrunEkle(kiyafet);
		urunGirisi();
	}
	else if (islem == 2)
	{
		write.close();
		Kiyafet kiyafet = depo.KiyafetObjesiYarat(urun_id, kategori, renk, boyut, fiyat);
		depo.UrunEkle(kiyafet);
		depo.urunleriGoruntule();
	}
	else {
		cout << "Hatali islem girdiniz. Cikis yapılıyor.\n";
	}
}

void Yonetici::kuryeEklenmesi()
{

	string ad_soyad;
	string telNo;
	string id;

	for (int i = 0; i < kuryeler.size(); i++)
	{
		cout << kuryeler[i].getAdSoyad() << " " << kuryeler[i].getTelNo() << endl;
	}


	cout << "Eklemek Istediginiz Kuryenin Bilgilerini Giriniz." << endl;
	cout << endl;
	cout << "Kurye ID:";
	cin >> id;
	cout << "ad_soyad:";
	cin.ignore();
	getline(cin, ad_soyad);
	cout << "telNo:";
	cin >> telNo;

	fstream write;
	write.open("kurye.txt", ios::in | ios::app);

	write << endl << ad_soyad << "," << telNo;

	cout << "Isleminiz basariyla gerceklestirilmistir!!" << endl;

	int islem;
	cout << "Baska bir kurye girisi yapmak istiyor musunuz?\n1- Evet\n2-Hayir" << endl;
	cin >> islem;

	if (islem == 1) {

		write.close();
		Kurye kurye = KuryeObjesiYarat(ad_soyad, telNo, id);
		kuryeler.push_back(kurye);
		kuryeEklenmesi();
	}
	else if (islem == 2)
	{
		write.close();
		Kurye kurye = KuryeObjesiYarat(ad_soyad, telNo, id);
		kuryeler.push_back(kurye);
		for (int i = 0; i < kuryeler.size(); i++)
		{
			cout << kuryeler[i].getAdSoyad() << " " << kuryeler[i].getTelNo() << endl;
		}

	}
	else {
		cout << "Hatali islem girdiniz. Cikis yapılıyor.\n";
	}

}

void Yonetici::sikayetVeOneriler()
{
	Utility utility;
	ifstream sikayetlerTxtsi;
	int sikayetlerTxtLineUzunlugu = utility.TxtlineCount("sikayetveOneriler.txt");
	sikayetlerTxtsi.open("sikayetveOneriler.txt", ios::in);

	string satir;

	if (sikayetlerTxtsi.is_open())
	{
		for (int i = 0; i < sikayetlerTxtLineUzunlugu; i++)
		{
			getline(sikayetlerTxtsi, satir);
			sikayetler.push_back(satir);
			cout << satir << endl;
		}
	}


}

void Yonetici::indirimKoduTanimla()
{
	Utility utility;

	cout << "Lutfen indirim kodu tanimlamak istediginiz kullanicinin emailini giriniz." << endl;

indirimKoduTanimla:
	string email;
	string indirimMiktari;
	cout << "kullanicinin emailini girin: ";
	cin >> email;
	Kullanici user;

	for (int i = 0; i < uyeler.size(); i++)
	{
		string asil_email = utility.charToString(uyeler[i].getEposta());

		if ((email == asil_email))
		{
			user = uyeler[i];
			cout << "Indirim miktarini giriniz :";
			cin >> indirimMiktari;


			user.setIndirim_kodu(utility.stringToChar(indirimMiktari));
			uyeler[i] = user;


			cout << "Indirim kodu tanimlandi. Verdiginiz Indirim Kodu : " << user.getIndirim_kodu() << endl;
			cout << endl;

			cout << uyeler[i].getIndirim_kodu();

		}
		else
		{
			cout << "hatali veri girdiniz, lutfen tekrar giriniz" << endl;
			goto indirimKoduTanimla;

		}
	}






}

void Yonetici::siparisFaturalariGoruntule()
{
	int fisTxtLineUzunlugu;

	string satir;
	ifstream fisTxtsi("fis.txt");
	for (fisTxtLineUzunlugu = 0; getline(fisTxtsi, satir); ++fisTxtLineUzunlugu);


	fisOkumaDosyasi.open("fis.txt", ios::in);
	if (fisOkumaDosyasi.is_open())
	{
		for (int i = 0; i < fisTxtLineUzunlugu; i++)
		{
			getline(fisOkumaDosyasi, satir);
			fisler.push_back(satir);
		}
		fisOkumaDosyasi.close();
	}
	for (int a = 0; a < fisler.size(); a++)
	{
		cout << fisler[a] << endl;
	}

}

Yonetici YoneticiObjesiYarat(string pisim, string psifre, string ptelno)
{
	Utility utility;
	char* ad_soyad = utility.stringToChar(pisim);
	char* sifre = utility.stringToChar(psifre);
	char* telno = utility.stringToChar(ptelno);

	Yonetici yonetici = Yonetici(ad_soyad, sifre, telno);
	return yonetici;
}


#pragma endregion

#pragma region MENU
class Menu
{
	void kullaniciArayuzunuCalistir();

public:
	Menu();
	Yonetici yoneticiIslemleri;
	KiyafetList urunIslemleri;
	Siparis siparisIslemleri;
	Kullanici kullaniciIslemleri;
	Sepet sepetIslemleri;

	Kullanici KullaniciKontrolu();

	Yonetici YoneticiKontrolu();



};

Menu::Menu() {

	kullaniciArayuzunuCalistir();

}

void Menu::kullaniciArayuzunuCalistir() {

	cout << "Menu Islemlerine Hosgeldiniz" << endl;
	cout << endl;
	int islem;
	int urun_id;

	while (true)
	{
		cout << " * ISLEMLER * " << endl;
		cout << "1- Yonetici Girisi \n2- Musteri Girisi \n3- Uye Kaydi \n4- Cikis Yap" << endl;
		cout << endl;
		cout << "Bir islem giriniz: ";
		cin >> islem;
		cout << endl;

		if (islem == 1)
		{
			Yonetici yönetici = YoneticiKontrolu();
			while (true)
			{

				cout << "*YONETICI ISLEMLERI*" << endl;
				cout << "1- Urun Girisi Yap\n2- Sisteme Kurye Ekle\n3- Sikayet ve Onerileri Goruntule\n4- Indirim Kodu Tanimla\n5- Siparis Faturalari Goruntule\n0- Menuye Don" << endl;
				cout << endl;
				cout << "Bir islem giriniz: ";
				cin >> islem;
				cout << endl;
				if (islem == 1)
				{
					cout << endl;
					yoneticiIslemleri.urunGirisi();
					cout << endl;
				}
				else if (islem == 2)
				{
					cout << endl;
					yoneticiIslemleri.kuryeEklenmesi();
					cout << endl;
				}
				else if (islem == 3)
				{
					cout << endl;
					yoneticiIslemleri.sikayetVeOneriler();
					cout << endl;
				}
				else if (islem == 4)
				{
					cout << endl;
					yoneticiIslemleri.indirimKoduTanimla();
					cout << endl;
				}
				else if (islem == 5)
				{
					cout << endl;
					yoneticiIslemleri.siparisFaturalariGoruntule();
					cout << endl;
				}
				else if (islem == 0)
				{
					cout << "Menuye Donuluyor" << endl;
					cout << endl;
					break;
				}
				else
				{
					cout << "Hatali bir islem girdiniz program sonlandiriliyor." << endl;
					cout << endl;
				}
			}
		}
		else if (islem == 2)
		{

			Kullanici user = KullaniciKontrolu();

			while (true)
			{
				cout << "MUSTERI ISLEMLERI" << endl;
				cout << "1- Urunleri Goruntule\n2- Siparis Goruntule\n3- Sikayet ve Oneri \n4- Sifre Degistir\n0- Menuye Don" << endl;
				cout << endl;
				cout << "Bir islem giriniz: ";
				cin >> islem;
				cout << endl;
				if (islem == 1)
				{
				urunlerigoruntuleme:
					cout << endl;
					urunIslemleri.urunleriGoruntule();
					cout << endl;
					cout << "Eklemek istediginiz urunun numarasini giriniz: " << endl;
					cin >> urun_id;
					sepetIslemleri.SepeteEkle(urunIslemleri.getUrun(urun_id));
					cout << endl;
					cout << "1- Alisverise devam et    2- Sepeti Goruntule" << endl;
					cin >> islem;
					cout << endl;
					if (islem == 1)
					{
						goto urunlerigoruntuleme;
					}
					else if (islem == 2)
					{
						while (islem == 2)
						{
							sepetIslemleri.printSepet();
							cout << "1- Geri Don   2- Sepeti Onayla" << endl;
							cin >> islem;
							cout << endl;
							if (islem == 1)
							{

								cout << endl;
								cout << "Urunlere Donuluyor" << endl;
								cout << endl;

								goto urunlerigoruntuleme;

							}
							else if (islem == 2)
							{
								// sepet onaylandı ise bir kurye ataması yapılabilir
								Kurye kurye = KuryeAtamasi(kuryeler);

								if (sepetIslemleri.getUrunAdedi() == 1)
								{
									// siparisin alınması
									siparisIslemleri = Siparis(sepetIslemleri.getSepet()[0], user); // siparis atanır

									// kurye olayları
									Zaman adres_zamani = siparisIslemleri.getAdresZamani(); // ilçe zamanı alınır
									int siparis_no = siparisIslemleri.getSiparisNo(); // siparis no alınır
									kurye.setSiparis(adres_zamani, siparis_no); // kuryeye bu bilgiler verilir, kurye elinde siparis olup olmamasına göre son teslim zamanını belirler

									// siparise siparisin teslim zamanının atanması
									Zaman teslim_zamani = kurye.getSiparisTeslimZamani(siparis_no);
									siparisIslemleri.setSiparisUlasim(teslim_zamani);

									// kuryeyi de siparişe setleyelim
									siparisIslemleri.setKurye(kurye.getKuryeId());

									// siparise dair tüm atamalar bitti fis olusturulabilir.
									siparisIslemleri.FisOlustur(); // burada blokta tek ürün olduğundan parametresi olmayan çağrılmıştır
								}
								else
								{
									siparisIslemleri = Siparis(sepetIslemleri, user);
									// kurye olayları
									Zaman adres_zamani = siparisIslemleri.getAdresZamani(); // ilçe zamanı alınır
									int siparis_no = siparisIslemleri.getSiparisNo(); // siparis no alınır
									kurye.setSiparis(adres_zamani, siparis_no); // kuryeye bu bilgiler verilir, kurye elinde siparis olup olmamasına göre son teslim zamanını belirler

									// siparisin teslim zamanının atanması
									Zaman teslim_zamani = kurye.getSiparisTeslimZamani(siparis_no);
									siparisIslemleri.setSiparisUlasim(teslim_zamani);

									// kuryeyi de siparişe setleyelim
									siparisIslemleri.setKurye(kurye.getKuryeId());

									// siparise dair tüm atamalar bitti fis olusturulabilir.
									siparisIslemleri.FisOlustur(sepetIslemleri); // burada blokta sepet ürünleri olduğundan parametresi olmayan çağrılmıştır
								}

								// siparis alımı bitti sepetin boşaltılması gerek,
								// çünkü şu durumda siparis alınmıs olmasına rağmen sepet ürünleri hala duruyor
								sepetIslemleri.SepetiBosalt();

								// bir de siparis miktarı güncellenmiş kuryeyi geri vektördeki asıla atayalım
								// çünkü şu durumda local değişken olan kurye ile devam ediyor vektör içindeki kuryelerde hiç bir değişiklik yok
								for (int i = 0; i < kuryeler.size(); i++)
								{
									if (kurye.getKuryeId() == kuryeler[i].getKuryeId())
									{
										kuryeler[i] = kurye;
									}
								}

								cout << "Siparisiniz onaylandi. Musteri islemlerinden siparisinizi goruntuleyebilirsiniz." << endl;
								cout << endl;
								cout << "Musteri Islemlerine Donuluyor.." << endl;
								cout << endl;
								break;
							}

						}
					}

				}
				else if (islem == 2)
				{
					siparisIslemleri.SiparisGoruntule(user);
				}
				else if (islem == 3)
				{
					kullaniciIslemleri.SikayetAl();

					cout << endl;
					cout << "Cikis yapmak icin 1'e basın." << endl;
					cin >> islem;
					cout << endl;
					if (islem == 1)
					{
						cout << endl;
						cout << "Cikis yapildi." << endl;
						cout << endl;
					}
				}
				else if (islem == 4)
				{
					Utility utility;

					cout << "Sifre degisikligi icin lutfen bilgilerinizi giriniz." << endl;

				sifredegisikligi:
					string password;
					string email;
					string newpassword;
					cout << "emailinizi girin: ";
					cin >> email;
					cout << "mevcut sifrenizi girin: ";
					cin >> password;

					for (int i = 0; i < uyeler.size(); i++)
					{
						string asil_sifre = utility.charToString(uyeler[i].getSifre());
						string asil_email = utility.charToString(uyeler[i].getEposta());

						if ((email == asil_email) && (password == asil_sifre))
						{
							cout << "yeni sifrenizi giriniz :";
							cin >> newpassword;
							password = newpassword;

							user.setSifre(utility.stringToChar(newpassword));


							for (int i = 0; i < uyeler.size(); i++)
							{
								if (email == utility.charToString(uyeler[i].getEposta()))
								{
									uyeler[i] = user;
								}
							}

							cout << "Sifreniz degistirildi. Yeni Sifreniz : " << user.getSifre() << endl;
							cout << endl;

						}
						else
						{
							cout << "hatali veri girdiniz, lutfen tekrar giriniz" << endl;
							goto sifredegisikligi;

						}
					}

					//txtyeVerileriYaz(user.getAdSoyad(), user.getKullanici_adi(),user.getEposta(), user.getSifre(), user.getTelNo(), user.getAdres_ilce(), user.getDtarihi());



				}
				else if (islem == 0)
				{
					cout << "Menuye Donuluyor" << endl;
					cout << endl;
					break;
				}
				else
				{
					cout << "Gecerli Bir Islem Giriniz." << endl;
				}
			}
		}
		else if (islem == 3)
		{
			cout << "* UYE KAYDI *" << endl;
			cout << endl;
			Kullanici users = kullaniciIslemleri.uyeKaydiOlustur();
			uyeler.push_back(users);
		}
		else if (islem == 4)
		{
			cout << "Programdan basariyla cikis yaptiniz.." << endl;
			cout << endl;
			break;
		}
		else
		{
			cout << "Hatali bir islem girdiniz program sonlandiriliyor." << endl;
			cout << endl;

		}
	}

	ofstream file("kullanicilar.txt", ios::in);
	for (int i = 0; i < yoneticiler.size(); i++)
	{
		file << yoneticiler[i].getAdSoyad() << "," << "null" << "," << "null" << yoneticiler[i].getSifre() << "," << yoneticiler[i].getTelNo() << "," << "null" << "," << "null" << "," << "null" << endl;
	}


	for (int i = 0; i < uyeler.size(); i++)
	{
		if (i == uyeler.size())
		{
			file << uyeler[i].getAdSoyad() << "," << uyeler[i].getKullanici_adi() << "," << uyeler[i].getEposta() << "," << uyeler[i].getSifre() << "," << uyeler[i].getTelNo() << "," << uyeler[i].getAdres_ilce() << "," << uyeler[i].getDtarihi() << "," << uyeler[i].getIndirim_kodu();
		}
		else
		{
			file << uyeler[i].getAdSoyad() << "," << uyeler[i].getKullanici_adi() << "," << uyeler[i].getEposta() << "," << uyeler[i].getSifre() << "," << uyeler[i].getTelNo() << "," << uyeler[i].getAdres_ilce() << "," << uyeler[i].getDtarihi() << "," << uyeler[i].getIndirim_kodu() << endl;
		}

	}
	file.close();

	// kullanıcılar txt içini sil sonra yöneticiler verktörünü kullanıcılar txt yazdır peşine hemen kullanıcılar vektörünü yazdır
}

Kullanici Menu::KullaniciKontrolu()
{
	Utility utility;
	string password;
	string email;
	cout << "emailinizi girin: ";
	cin >> email;
	cout << "sifrenizi girin: ";
	cin >> password;

	for (int i = 0; i < uyeler.size(); i++)
	{
		string asil_sifre = utility.charToString(uyeler[i].getSifre());
		string asil_email = utility.charToString(uyeler[i].getEposta());

		if ((email == asil_email) && (password == asil_sifre))
		{
			cout << endl;
			cout << "giris basarili" << endl;
			return uyeler[i];
		}
		else
		{
			cout << "hatali veri girdiniz, lutfen tekrar giriniz" << endl;
			KullaniciKontrolu();
		}
	}
}

Yonetici Menu::YoneticiKontrolu()
{
	Utility utility;
	string password;
	string isim;
	cout << "adinizi ve soyadinizi giriniz: ";
	cin.ignore();
	getline(cin, isim);
	cout << "sifrenizi giriniz: ";
	cin >> password;

	for (int i = 0; i < yoneticiler.size(); i++)
	{
		string asil_sifre = utility.charToString(yoneticiler[i].getSifre());
		string asil_isim = utility.charToString(yoneticiler[i].getAdSoyad());

		if ((isim == asil_isim) && (password == asil_sifre))
		{
			cout << "giris basarili" << endl;
			cout << endl;
			return yoneticiler[i];
		}
		else
		{
			cout << "hatalı veri girdiniz, lütfen tekrar giriniz" << endl;
			YoneticiKontrolu();
		}
	}
}

#pragma endregion

#pragma region txtIslemleri

void txtyeVerileriYaz(char* ad_soyad, char* kullanici_adi, char* eposta, char* sifre, char* telno, char* adres_ilce, char* dtarihi, char* indirimKodu) // hiçbir yerde kullanmamışız tüm classların destructorlarında yazdırılacak öğeleri yazdırılsın
{
	fstream kullanicilarTxtsi;
	kullanicilarTxtsi.open("kullanicilar.txt", ios::in | ios::app);
	kullanicilarTxtsi.setf(ios::left);
	kullanicilarTxtsi << endl << ad_soyad << "," << kullanici_adi << "," << eposta << "," << sifre << "," << telno << "," << adres_ilce << "," << dtarihi << "," << indirimKodu;

	kullanicilarTxtsi.close();
}

void txtLineSayisiniHesaplama() {
	ifstream kullanicilarTxtsi("kullanicilar.txt");
	for (kullanicilarTxtLineUzunlugu = 0; getline(kullanicilarTxtsi, satir); ++kullanicilarTxtLineUzunlugu);
}

void KullanicitxtdenVerileriCek() {
	Utility utility;
	txtLineSayisiniHesaplama();

	kullanicilarOkumaDosyasi.open("kullanicilar.txt", ios::in);

	string* kullaniciSatirleri = utility.getTxtContent("kullanicilar.txt", kullanicilarTxtLineUzunlugu);
	vector < vector<string> >bolunmusKullaniciListesi = utility.splitListItems(kullaniciSatirleri, kullanicilarTxtLineUzunlugu);

	if (kullanicilarOkumaDosyasi.is_open())
	{
		for (int i = 0; i < kullanicilarTxtLineUzunlugu; i++)
		{
			if (bolunmusKullaniciListesi[i][1] == "null")
			{
				Yonetici yonetici = YoneticiObjesiYarat(
					bolunmusKullaniciListesi[i][0],
					bolunmusKullaniciListesi[i][3],
					bolunmusKullaniciListesi[i][4]);
				yoneticiler.push_back(yonetici);
			}
			else
			{
				Kullanici user = KullaniciObjesiYarat(
					bolunmusKullaniciListesi[i][0],
					bolunmusKullaniciListesi[i][1],
					bolunmusKullaniciListesi[i][2],
					bolunmusKullaniciListesi[i][3],
					bolunmusKullaniciListesi[i][4],
					bolunmusKullaniciListesi[i][5],
					bolunmusKullaniciListesi[i][6],
					bolunmusKullaniciListesi[i][7]);

				uyeler.push_back(user);
			}

		}
		kullanicilarOkumaDosyasi.close();
	}
}


void KuryeTxtdenVerileriCek()
{
	Utility utility;
	fstream kuryeRead;

	int kuryeLines = utility.TxtlineCount("kurye.txt");

	kuryeRead.open("kurye.txt", ios::in);

	string* kuryeSatirleri = utility.getTxtContent("kurye.txt", kuryeLines);
	vector < vector<string> >bolunmusKuryeListesi = utility.splitListItems(kuryeSatirleri, kuryeLines);

	if (kuryeRead.is_open())
	{
		for (int i = 0; i < kuryeLines; i++)
		{
			Kurye kurye = KuryeObjesiYarat(
				bolunmusKuryeListesi[i][0],
				bolunmusKuryeListesi[i][1],
				bolunmusKuryeListesi[i][2]);
			kuryeler.push_back(kurye);
		}
		kuryeRead.close();
	}
}

Kurye KuryeAtamasi(vector<Kurye> kuryeler)
{
	Kurye musaitKurye = kuryeler[0];

	for (int i = 1; i < kuryeler.size(); i++)
	{
		if (kuryeler[i].getSiparisMiktari() <= musaitKurye.getSiparisMiktari())
		{
			musaitKurye = kuryeler[i];
			return musaitKurye;
		}
	}
	return musaitKurye;
}

#pragma endregion

int main()
{
	KullanicitxtdenVerileriCek();
	KuryeTxtdenVerileriCek();
	Menu menu;

}