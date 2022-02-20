#include<iostream>
#include<fstream>
#include<sstream>
#include <iomanip>
#include <string>
using namespace std;
enum eGenre { Krimi, Sachbuch, Roman, Thriller, Artwork, unbekannt };
struct sBuch {
	int signatur; // Die Signatur dient nur zur Vereinfachung der Suche
	string autor; // Achtung, alle Strings enthalten KEINE Leerzeichen
	string titel;
	long long isbn; // ohne die Striche, 13 Stellen!!!!
	eGenre genre; // enum - Typ, siehe oben
	int jahr; // Erscheinungsjahr, vierstellig
	bool ausgeliehen;
	sBuch* next; // Zeiger auf das n�chste Buch
};

int menue();
void einfuegen(sBuch*& anfang); // Es wird genau ein Buch erfasst
void ausgeben(sBuch* anfang); // Ausgabe der kompletten Liste
sBuch* suchen(int suchWert, sBuch* anfang); // liefert den Zeiger auf ein gefundenes Buch zur�ck
void liste_loeschen(sBuch*& anfang); // R�umt den Speicher auf und l�scht alle Elemente der Liste
bool buecher_in_Datei_schreiben(sBuch* anfang, string dateiname); // liefert ein false zur�ck, wenn bei der Dateioperation etwas schief gegangen ist
bool buecher_aus_Datei_Lesen(sBuch*& anfang, string dateiname); // liefert ein false zur�ck, wenn bei der Dateioperation etwas schief gegangen ist
string unterstrich_zum_leerzeichen(string val); //tauscht die Unterstriche in einem Strimg gegen Leerzeichen aus