#include"Header.h"
int main() {
	sBuch* buchs = NULL;
	
	bool programmende = false;
	int auswahl, suchWert;
	string dateiname;
	do
	{
		auswahl = menue();
		switch (auswahl)
		{
		case 0:
			programmende = true;
			cout << endl << "Vielen Dank, dass Se Ihre Buecher mit Buecherwurm verwalten" << endl;
			cout << "Bis bald...!" << endl << endl;
			liste_loeschen(buchs);
			break;
		case 1:
			einfuegen(buchs);
			break;
		case 2:
			ausgeben(buchs);
			break;
		case 3:
			cout << endl << "Bitte geben Sie den Dateinamen ein: ";
			cin >> dateiname;
			if (buecher_in_Datei_schreiben(buchs, dateiname)) {
				cout << endl << "Bücher erfolgreich in Datei geschrieben!" << endl << endl;
			}
			else {
				cout << endl << "Datei kann nicht geöffnet werden" << endl << endl;
			}
			break;
		case 4:
			cout << endl << "Bitte geben Sie den Dateinamen ein: ";
			cin >> dateiname;
			if (buecher_aus_Datei_Lesen(buchs, dateiname)) {
				cout << endl << "Bücher wurden erfolgreich aus Datei gelesen!" << endl << endl;
			}
			else {
				cout << endl << "Datei kann nicht geöffnet werden" << endl << endl;
			}
			break;
		case 5:
		{
			cout << endl << "Bitte geben Sie die Signatur des Buches ein, das Sie durchsuchen möchten: ";
			cin >> suchWert;
			sBuch* buch = suchen(suchWert, buchs);
			if (buch == NULL) {
				cout << endl << "Das Buch mit der Signatur " << suchWert << " ist nicht in der Liste" << endl << endl;
			}
			else
			{
				if (buch->ausgeliehen) {
					cout << endl << "Es tut uns leid! Das Buch ist bereits ausgeliehen" << endl << endl;
				}
				else {
					cout << endl << "Das Buch mit der Signatur " << suchWert << " wird ausgeliehen " << buch->titel << endl << endl;
					buch->ausgeliehen = true;
				}
			}
		}
			break;
		case 6:
			//Suche das Buch in der Liste und wenn es gefunden wird, lösche es
		{
			cout << endl << "Bitte geben Sie die Signatur des Buches ein, das Sie durchsuchen möchten: ";
			cin >> suchWert;
			sBuch* buch = suchen(suchWert, buchs);
			if (buch == NULL) {
				cout << endl << "Das Buch mit der Signatur " << suchWert << " ist nicht in der Liste" << endl << endl;
			}
			else
			{
				sBuch* vorübergehprogrammende = buchs;
				sBuch* löschen;
				if (buchs->signatur == suchWert) {
					löschen = buchs;
					buchs = buchs->next;
					löschen->next = NULL;
					delete löschen;
					cout << endl << "Buch gelöscht!" << endl << endl;
				}
				else {
					while (vorübergehprogrammende->next != NULL) {
						if (vorübergehprogrammende->next->signatur == suchWert) {
							löschen = vorübergehprogrammende->next;
							vorübergehprogrammende->next = löschen->next;
							löschen->next = NULL;
							delete löschen;
							cout << endl << "Buch gelöscht!" << endl << endl;
						}
						else {
							vorübergehprogrammende = vorübergehprogrammende->next;
						}
					}
				}
			}
		}
			break;
		default:
			cout << endl << "Diesen menueepunkt gibt es leider nicht.." << endl << endl;
			break;
		}
	} while (!programmende);
	return 0;
}