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
				cout << endl << "B�cher erfolgreich in Datei geschrieben!" << endl << endl;
			}
			else {
				cout << endl << "Datei kann nicht ge�ffnet werden" << endl << endl;
			}
			break;
		case 4:
			cout << endl << "Bitte geben Sie den Dateinamen ein: ";
			cin >> dateiname;
			if (buecher_aus_Datei_Lesen(buchs, dateiname)) {
				cout << endl << "B�cher wurden erfolgreich aus Datei gelesen!" << endl << endl;
			}
			else {
				cout << endl << "Datei kann nicht ge�ffnet werden" << endl << endl;
			}
			break;
		case 5:
		{
			cout << endl << "Bitte geben Sie die Signatur des Buches ein, das Sie durchsuchen m�chten: ";
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
			//Suche das Buch in der Liste und wenn es gefunden wird, l�sche es
		{
			cout << endl << "Bitte geben Sie die Signatur des Buches ein, das Sie durchsuchen m�chten: ";
			cin >> suchWert;
			sBuch* buch = suchen(suchWert, buchs);
			if (buch == NULL) {
				cout << endl << "Das Buch mit der Signatur " << suchWert << " ist nicht in der Liste" << endl << endl;
			}
			else
			{
				sBuch* vor�bergehprogrammende = buchs;
				sBuch* l�schen;
				if (buchs->signatur == suchWert) {
					l�schen = buchs;
					buchs = buchs->next;
					l�schen->next = NULL;
					delete l�schen;
					cout << endl << "Buch gel�scht!" << endl << endl;
				}
				else {
					while (vor�bergehprogrammende->next != NULL) {
						if (vor�bergehprogrammende->next->signatur == suchWert) {
							l�schen = vor�bergehprogrammende->next;
							vor�bergehprogrammende->next = l�schen->next;
							l�schen->next = NULL;
							delete l�schen;
							cout << endl << "Buch gel�scht!" << endl << endl;
						}
						else {
							vor�bergehprogrammende = vor�bergehprogrammende->next;
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