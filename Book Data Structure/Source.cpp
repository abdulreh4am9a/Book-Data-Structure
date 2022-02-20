#include"header.h"
int menue() {
	int wahl;
	cout << "++ Buecherwurm V 0.0 ++" << endl;
	cout << "1. Neues Buch erfassen" << endl;
	cout << "2. Buecherliste ausgeben" << endl;
	cout << "3. Buecherliste in eine Datei schreiben" << endl;
	cout << "4. Buecherliste aus einer Datei lesen" << endl;
	cout << "5. Bestimmtes Buch suchen und ausleihen" << endl;
	cout << "6. Bestimmtes Buch suchen und loeschen" << endl;
	cout << "0. Programm beenden" << endl;
	cout << "   Ihre Wahl: ";
	cin >> wahl;
	return wahl;
}
void einfuegen(sBuch*& anfang) {
	//nimmt den Anfang des Baums und f�gt das Buch am Ende ein
	if (anfang == NULL) {
		int signatur, jahr, ch;
		string autor, titel;
		long long isbn;
		eGenre genre;
		cout << "Eingeben signatur: ";
		cin >> signatur;
		cout << "Eingeben titel: ";
		cin >> titel;
		cout << "Eingeben autor: ";
		cin >> autor;
		cout << "Eingeben jahr: ";
		cin >> jahr;
		cout << "Eingeben ISBN: ";
		cin >> isbn;
		cout << "W�hlen Sie aus folgenden Genres aus:" << endl;
		cout << "1. Krimi\n2. Sachbuch\n3. Roman\n4. Thriller\n5. Artwork\n6. unbekannt" << endl;
		cout << "Auswahl: ";
		cin >> ch;
		switch (ch) {
		case 1:genre = Krimi;break;
		case 2:genre = Sachbuch;break;
		case 3:genre = Roman;break;
		case 4:genre = Thriller;break;
		case 5:genre = Artwork;break;
		default:genre = unbekannt;break;
		}
		anfang = new sBuch;
		anfang->autor = unterstrich_zum_leerzeichen(autor);
		anfang->ausgeliehen = false;
		anfang->genre = genre;
		anfang->isbn = isbn;
		anfang->next = NULL;
		anfang->signatur = signatur;
		anfang->titel = unterstrich_zum_leerzeichen(titel);
		anfang->jahr = jahr;
		cout << endl << "Buch eingef�gt!" << endl << endl;
	}
	else {
		einfuegen(anfang->next);
	}
}
void ausgeben(sBuch* anfang) {
	//zeigt alle B�cher in der Liste in Listenform an
	if (anfang == NULL) {
		return;
	}
	else {
		cout << anfang->signatur << ". " << anfang->titel << " geschrieben von " << anfang->autor << " in " << anfang->jahr << endl;
		cout << "   Genre: ";
		switch (anfang->genre) {
		case 0:cout << "Krimi";break;
		case 1:cout << "Sachbuch";break;
		case 2:cout << "Roman";break;
		case 3:cout << "Thriller";break;
		case 4:cout << "Artwork";break;
		default:cout << "unbekannt";break;
		}
		cout << " ISBN: " << anfang->isbn << endl << endl;
		ausgeben(anfang->next);
	}
}
sBuch* suchen(int suchWert, sBuch* anfang) {
	//Durchsuchen Sie die gesamte Liste, w�hrend Sie das Buch auf der Grundlage des bereitgestellten Schl�ssels durchsuchen
	if (anfang == NULL) {
		return NULL;
	}
	else if (anfang->signatur == suchWert) {
		return anfang;
	}
	else {
		suchen(suchWert, anfang->next);
	}
}
void liste_loeschen(sBuch*& anfang) {
	//l�scht die gesamte Liste und gibt den Speicher frei
	if (anfang == NULL) {
		return;
	}
	else {
		sBuch* vor�bergehend = anfang;
		anfang = anfang->next;
		delete vor�bergehend;
		liste_loeschen(anfang);
	}
}
bool buecher_in_Datei_schreiben(sBuch* anfang, string dateiname) {
	//schreibt die Aufzeichnungen der B�cher in einem bestimmten unten definierten Format in die Datei:
	//signatur,titel,autor,jahr,genre,isbn,ausgeliehen
	if (anfang == NULL) {
		return true;
	}
	else {
		ofstream die_Datei(dateiname, ios_base::app);
		if (die_Datei.is_open()) {
			die_Datei << anfang->signatur << "," << anfang->titel << "," << anfang->autor << "," << anfang->jahr << "," << anfang->genre << "," << anfang->isbn << "," << anfang->ausgeliehen << endl;
			die_Datei.close();
			buecher_in_Datei_schreiben(anfang->next, dateiname);
		}
		else {
			return false;
		}
	}
}
bool buecher_aus_Datei_Lesen(sBuch*& anfang, string dateiname) {
	//liest die Datens�tze der B�cher aus der Datei in einem bestimmten, unten definierten Format:
	//signatur,titel,autor,jahr,genre,isbn,ausgeliehen
	ifstream die_Datei(dateiname);
	if (die_Datei.is_open()) {
		string line, signatur, jahr, genre, isbn, ausgeliehen;
		while (getline(die_Datei, line)){
			stringstream ss(line);
			sBuch* vor�bergehend;
			vor�bergehend = new sBuch;
			vor�bergehend->next = NULL;
			getline(ss, signatur, ',');
			getline(ss, vor�bergehend->titel, ',');
			getline(ss, vor�bergehend->autor, ',');
			getline(ss, jahr, ',');
			getline(ss, genre, ',');
			getline(ss, isbn, ',');
			getline(ss, ausgeliehen, ',');
			vor�bergehend->signatur = stoi(signatur);
			vor�bergehend->jahr = stoi(jahr);
			vor�bergehend->isbn = stoll(isbn, nullptr, 10);
			switch (stoi(genre)) {
			case 1:vor�bergehend->genre = Krimi;break;
			case 2:vor�bergehend->genre = Sachbuch;break;
			case 3:vor�bergehend->genre = Roman;break;
			case 4:vor�bergehend->genre = Thriller;break;
			case 5:vor�bergehend->genre = Artwork;break;
			default:vor�bergehend->genre = unbekannt;break;
			}
			if (stoi(ausgeliehen)) {
				vor�bergehend->ausgeliehen = true;
			}
			else {
				vor�bergehend->ausgeliehen = false;
			}
			if (anfang == NULL) {
				anfang = vor�bergehend;
			}
			else {
				sBuch* tmp = anfang;
				while (tmp->next != NULL) {
					tmp = tmp->next;
				}
				tmp->next = vor�bergehend;
			}
		}
		die_Datei.close();
		return true;
	}
	else {
		return false;
	}
}
string unterstrich_zum_leerzeichen(string val) {
	//durchqueren Sie die gesamte Zeichenfolge, w�hrend Sie den Unterstrich durch Leerzeichen tauschen
	for (int i = 0;i < val.size();i++) {
		if (val[i] == '_') {
			val[i] = ' ';
		}
	}
	return val;
}