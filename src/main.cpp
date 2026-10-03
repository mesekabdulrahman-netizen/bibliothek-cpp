/* AUFGABENBLATT 52 - PROGRAMMIERTECHNIK

 AUFGABE - Stichsätze:
 - Konsolenprogramm zur Verwaltung einer Bibliothek erstellen
 - Medien: Buch, DVD und Zeitschrift verwalten
 - enum class MediumTyp verwenden
 - Klasse Medium mit privaten Attributen erstellen
 - Konstruktor und Getter verwenden
 - Medien ausleihen und zurückgeben können
 - Klasse Mitglied erstellen
 - Ein Mitglied darf maximal 3 Medien gleichzeitig ausleihen
 - Klasse Bibliothek erstellen
 - Medien und Mitglieder in vector speichern
 - Medien über ihre ID suchen
 - Mitglieder über ihre Mitgliedsnummer suchen
 - Ausleihen und Zurückgeben über die Bibliothek ermöglichen
 - operator<< für Medium überladen
 - operator== für Medium überladen
 - Mindestens 5 Medien und 2 Mitglieder erstellen
 - Verschiedene Ausleih-Szenarien testen
 - Mindestens 6 automatische Tests durchführen
 - README.md und REFLEXION.md erstellen
 - Projekt mit Git/GitHub verwalten*/

#include <iostream>          
#include <string>            
#include <vector>            
#include <algorithm>        
#include <stdexcept>         
#include <cassert>            


 // ENUM: MediumTyp
 // Hier werden die verschiedenen Medienarten definiert.
enum class MediumTyp
{
    Buch,                    // Medium ist ein Buch

    DVD,                     // Medium ist eine DVD

    Zeitschrift              // Medium ist eine Zeitschrift
};

// FREIE FUNKTION: typAlsText

// Diese Funktion wandelt den Enum-Wert in einen Text um.
std::string typAlsText(MediumTyp typ)
{
    // Prüft, welchen Typ das Medium besitzt.
    switch (typ)
    {

        // Wenn es ein Buch ist.
    case MediumTyp::Buch:

        return "Buch";

        // Wenn es eine DVD ist.
    case MediumTyp::DVD:

        return "DVD";

        // Wenn es eine Zeitschrift ist.
    case MediumTyp::Zeitschrift:

        return "Zeitschrift";

    }
    // Falls kein gültiger Typ gefunden wurde.
    return "Unbekannt";
}
// KLASSE: Medium
class Medium
{
private:
    // Eindeutige ID des Mediums.
    int id;

    // Titel des Mediums.
    std::string titel;

    // Autor, Regisseur oder Verlag.
    std::string urheber;

    // Erscheinungsjahr.
    int jahr;

    // Art des Mediums.
    MediumTyp typ;

    // Gibt an, ob das Medium verfügbar ist.
    bool verfuegbar;

public:
    // KONSTRUKTOR

    // Konstruktor mit Initialisierungsliste.
    Medium(

        int id,
        const std::string& titel,
        const std::string& urheber,
        int jahr,

        MediumTyp typ
    )
        : id(id),                       // ID initialisieren
        titel(titel),                 // Titel initialisieren
        urheber(urheber),             // Urheber initialisieren
        jahr(jahr),                   // Jahr initialisieren
        typ(typ),                     // Typ initialisieren
        verfuegbar(true)              // Neues Medium ist verfügbar
    {
        // Prüfen, ob der Titel leer ist.
        if (titel.empty())
        {
            // Fehler ausgeben, wenn kein Titel vorhanden ist.
            throw std::invalid_argument("Titel darf nicht leer sein.");
        }
        // Prüfen, ob der Urheber leer ist.
        if (urheber.empty())
        {
            // Fehler ausgeben, wenn kein Urheber vorhanden ist.
            throw std::invalid_argument("Urheber darf nicht leer sein.");
        }
        // Prüfen, ob das Jahr sinnvoll ist.
        if (jahr <= 0)
        {
            // Fehler ausgeben, wenn das Jahr ungültig ist.
            throw std::invalid_argument("Jahr muss positiv sein.");
        }
    }
    // GETTER

    // Gibt die ID zurück.
    int getId() const
    {
        return id;
    }
    // Gibt den Titel zurück.
    std::string getTitel() const
    {
        return titel;
    }
    // Gibt den Urheber zurück.
    std::string getUrheber() const
    {
        return urheber;
    }
    // Gibt das Erscheinungsjahr zurück.
    int getJahr() const
    {
        return jahr;
    }
    // Gibt den Medium-Typ zurück.
    MediumTyp getTyp() const
    {
        return typ;
    }
    // Gibt zurück, ob das Medium verfügbar ist.
    bool istVerfuegbar() const
    {
        return verfuegbar;
    }
    // AUSLEIHEN

    // Versucht, das Medium auszuleihen.
    bool ausleihen()
    {
        // Wenn das Medium bereits ausgeliehen ist.
        if (!verfuegbar)
        {
            // Ausleihen ist nicht möglich.
            return false;
        }
        // Medium wird als nicht verfügbar markiert.
        verfuegbar = false;

        // Ausleihen war erfolgreich.
        return true;
    }
    // ZURÜCKGEBEN

    // Versucht, das Medium zurückzugeben.
    bool zurueckgeben()
    {
        // Wenn das Medium bereits verfügbar ist.
        if (verfuegbar)
        {
            // Zurückgeben ist nicht möglich.
            return false;
        }
        // Medium wird wieder verfügbar.
        verfuegbar = true;

        // Rückgabe war erfolgreich.
        return true;
    }
    // BESCHREIBUNG

    // Erstellt eine passende Beschreibung des Mediums.
    std::string beschreibung() const
    {
        // String für die Beschreibung.
        std::string text;

        // Je nach Medium-Typ wird ein anderer Text erstellt.
        switch (typ)
        {
            // Beschreibung für ein Buch.
        case MediumTyp::Buch:

            text = "Buch: " + titel +
                " von " + urheber +
                " (" + std::to_string(jahr) + ")";

            break;
            // Beschreibung für eine DVD.
        case MediumTyp::DVD:

            text = "DVD: " + titel +
                ", Regie: " + urheber +
                " (" + std::to_string(jahr) + ")";

            break;
            // Beschreibung für eine Zeitschrift.
        case MediumTyp::Zeitschrift:

            text = "Zeitschrift: " + titel +
                ", Verlag: " + urheber +
                " (" + std::to_string(jahr) + ")";

            break;
        }
        // Fertige Beschreibung zurückgeben.
        return text;
    }
};
// OPERATOR << FÜR MEDIUM

// Mit diesem Operator kann man ein Medium direkt mit cout ausgeben.
std::ostream& operator<<(std::ostream& os, const Medium& medium)
{
    // Beschreibung des Mediums ausgeben.
    os << medium.beschreibung();

    // Stream zurückgeben.
    return os;

}
// OPERATOR == FÜR MEDIUM

// Zwei Medien gelten als gleich, wenn ihre IDs gleich sind.
bool operator==(const Medium& a, const Medium& b)
{
    // IDs miteinander vergleichen.
    return a.getId() == b.getId();
}

// KLASSE: Mitglied
class Mitglied
{
private:

    // Name des Mitglieds.
    std::string name;

    // Eindeutige Mitgliedsnummer.
    int mitgliedsNr;

    // IDs der aktuell ausgeliehenen Medien.
    std::vector<int> ausgelieheneMedien;

public:

    // KONSTRUKTOR

    // Konstruktor für ein Mitglied.
    Mitglied(const std::string& name, int mitgliedsNr)

        : name(name),                         // Name setzen

        mitgliedsNr(mitgliedsNr)            // Mitgliedsnummer setzen
    {

        // Prüfen, ob der Name leer ist.
        if (name.empty())
        {
            // Fehler ausgeben.
            throw std::invalid_argument("Name darf nicht leer sein.");
        }
        // Prüfen, ob die Mitgliedsnummer gültig ist.
        if (mitgliedsNr <= 0)
        {
            // Fehler ausgeben.
            throw std::invalid_argument(

                "Mitgliedsnummer muss positiv sein."
            );
        }
    }
    // GETTER

    // Gibt den Namen zurück.
    std::string getName() const
    {
        return name;
    }
    // Gibt die Mitgliedsnummer zurück.
    int getMitgliedsNr() const
    {
        return mitgliedsNr;
    }
    // AUSLEIHEN

    // Mitglied versucht ein Medium auszuleihen.
    bool ausleihen(Medium& m)
    {

        // Ein Mitglied darf maximal 3 Medien gleichzeitig haben.
        if (ausgelieheneMedien.size() >= 3)
        {
            // Das Limit wurde erreicht.
            return false;
        }
        // Medium wird direkt ausgeliehen.
        if (!m.ausleihen())
        {

            // Das Medium ist bereits ausgeliehen.
            return false;
        }
        // Die ID des Mediums wird gespeichert.
        ausgelieheneMedien.push_back(m.getId());

        // Ausleihe war erfolgreich.
        return true;

    }

    // ZURÜCKGEBEN

    // Mitglied gibt ein Medium zurück.
    bool zurueckgeben(Medium& m)
    {

        // Nach der ID des Mediums suchen.
        for (auto it = ausgelieheneMedien.begin();

            it != ausgelieheneMedien.end();

            ++it)
        {
            // Prüfen, ob die ID gefunden wurde.
            if (*it == m.getId())
            {

                // Medium zurückgeben.
                if (!m.zurueckgeben())
                {

                    // Rückgabe war nicht möglich.
                    return false;

                }
                // ID aus der Liste entfernen.
                ausgelieheneMedien.erase(it);

                // Rückgabe war erfolgreich.
                return true;
            }
        }
        // Mitglied hatte dieses Medium nicht ausgeliehen.
        return false;
    }
    // AUSLEIHEN ANZEIGEN


    // Zeigt die IDs der ausgeliehenen Medien.
    void zeigeAusleihen() const
    {

        // Name des Mitglieds ausgeben.
        std::cout << "Mitglied: " << name << std::endl;

        // Wenn keine Medien ausgeliehen wurden.
        if (ausgelieheneMedien.empty())
        {
            // Entsprechenden Text ausgeben.
            std::cout << "Keine Medien ausgeliehen." << std::endl;

            // Funktion beenden.
            return;
        }

        // Überschrift ausgeben.
        std::cout << "Ausgeliehene Medien: ";

        // Alle IDs durchlaufen.
        for (int id : ausgelieheneMedien)
        {
            // ID ausgeben.
            std::cout << id << " ";
        }

        // Neue Zeile.
        std::cout << std::endl;

    }
    // HAT AUSGELIEHEN

    // Prüft, ob das Mitglied ein bestimmtes Medium ausgeliehen hat.
    bool hatAusgeliehen(int mediumId) const
    {

        // Alle gespeicherten IDs durchsuchen.
        for (int id : ausgelieheneMedien)
        {
            // Prüfen, ob die ID passt.
            if (id == mediumId)
            {
                // Medium wurde gefunden.
                return true;
            }
        }
        // Medium wurde nicht gefunden.
        return false;
    }
};
// KLASSE: Bibliothek

class Bibliothek
{
private:

    // Alle Medien der Bibliothek.
    std::vector<Medium> medien;

    // Alle Mitglieder der Bibliothek.
    std::vector<Mitglied> mitglieder;

public:

    // MEDIUM HINZUFÜGEN


    // Fügt ein neues Medium hinzu.
    void mediumHinzufuegen(Medium m)
    {

        // Prüfen, ob die ID bereits existiert.
        for (const Medium& vorhandenesMedium : medien)
        {

            // IDs vergleichen.
            if (vorhandenesMedium.getId() == m.getId())
            {

                // Fehler ausgeben.
                throw std::invalid_argument(

                    "Medium-ID existiert bereits."

                );
            }
        }
        // Medium in den Vector einfügen.
        medien.push_back(m);
    }

    // MITGLIED HINZUFÜGEN

    // Fügt ein neues Mitglied hinzu.
    void mitgliedHinzufuegen(Mitglied m)
    {

        // Prüfen, ob die Mitgliedsnummer schon existiert.
        for (const Mitglied& vorhandenesMitglied : mitglieder)
        {

            // Mitgliedsnummern vergleichen.
            if (vorhandenesMitglied.getMitgliedsNr()

                == m.getMitgliedsNr())
            {

                // Fehler ausgeben.
                throw std::invalid_argument(

                    "Mitgliedsnummer existiert bereits."

                );
            }
        }
        // Mitglied in den Vector einfügen.
        mitglieder.push_back(m);
    }

    // MEDIUM FINDEN

    // Sucht ein Medium über seine ID.
    Medium* findeMedium(int id)
    {

        // find_if durchsucht den Vector.
        auto it = std::find_if(

            medien.begin(),

            medien.end(),

            // Lambda-Funktion für den Vergleich.
            [id](const Medium& m)
            {

                // Prüft, ob die ID passt.
                return m.getId() == id;
            }
        );
        // Wenn das Medium gefunden wurde.
        if (it != medien.end())
        {
            // Zeiger auf das Medium zurückgeben.
            return &(*it);
        }
        // Wenn nichts gefunden wurde.
        return nullptr;
    }

    // MITGLIED FINDEN

    // Sucht ein Mitglied über die Mitgliedsnummer.
    Mitglied* findeMitglied(int mitgliedsNr)
    {

        // Alle Mitglieder durchlaufen.
        for (Mitglied& m : mitglieder)
        {

            // Mitgliedsnummer vergleichen.
            if (m.getMitgliedsNr() == mitgliedsNr)
            {
                // Zeiger auf das Mitglied zurückgeben.

                return &m;
            }
        }
        // Wenn kein Mitglied gefunden wurde.
        return nullptr;
    }

    // AUSLEIHEN

    // Ein Mitglied leiht ein Medium aus.
    bool ausleihen(int mitgliedsNr, int mediumId)
    {
        // Mitglied suchen.
        Mitglied* mitglied = findeMitglied(mitgliedsNr);

        // Medium suchen.
        Medium* medium = findeMedium(mediumId);

        // Prüfen, ob beide gefunden wurden.
        if (mitglied == nullptr || medium == nullptr)
        {
            // Ausleihe nicht möglich.
            return false;
        }
        // Mitglied leiht das Medium aus.
        return mitglied->ausleihen(*medium);
    }
    // ZURÜCKGEBEN

    // Ein Mitglied gibt ein Medium zurück.
    bool zurueckgeben(int mitgliedsNr, int mediumId)
    {
        // Mitglied suchen.
        Mitglied* mitglied = findeMitglied(mitgliedsNr);

        // Medium suchen.
        Medium* medium = findeMedium(mediumId);

        // Prüfen, ob beide gefunden wurden.
        if (mitglied == nullptr || medium == nullptr)
        {

            // Rückgabe nicht möglich.
            return false;
        }

        // Mitglied gibt das Medium zurück.
        return mitglied->zurueckgeben(*medium);
    }

    // BESTAND ANZEIGEN

    // Zeigt alle Medien der Bibliothek.
    void zeigeBestand() const
    {

        // Überschrift ausgeben.
        std::cout << "\n===== BIBLIOTHEKSBESTAND ====="

            << std::endl;

        // Alle Medien durchlaufen.
        for (const Medium& medium : medien)
        {
            // Medium über operator<< ausgeben.
            std::cout << "ID: "

                << medium.getId()

                << " | "

                << medium

                << " | ";

            // Verfügbarkeit anzeigen.
            if (medium.istVerfuegbar())
            {
                // Wenn verfügbar.
                std::cout << "verfügbar";
            }
            else
            {
                // Wenn ausgeliehen.
                std::cout << "ausgeliehen";
            }
            // Neue Zeile.
            std::cout << std::endl;
        }
    }
    // SUCHEN

    // Sucht im Titel und im Urheber.
    std::vector<const Medium*> suche(

        const std::string& suchtext

    ) const

    {
        // Vector für die Suchergebnisse.
        std::vector<const Medium*> ergebnisse;

        // Alle Medien durchsuchen.
        for (const Medium& medium : medien)
        {
            // Prüfen, ob Suchtext im Titel vorkommt.
            bool imTitel =
                medium.getTitel().find(suchtext)

                != std::string::npos;

            // Prüfen, ob Suchtext beim Urheber vorkommt.
            bool imUrheber =
                medium.getUrheber().find(suchtext)

                != std::string::npos;

            // Wenn im Titel oder Urheber gefunden.
            if (imTitel || imUrheber)
            {
                // Adresse des Mediums speichern.
                ergebnisse.push_back(&medium);
            }
        }
        // Ergebnisse zurückgeben.
        return ergebnisse;
    }
};

// TESTFUNKTION

// Führt mindestens 6 automatische Tests durch.
void testeAlles()
{
    // Test-Bibliothek erstellen.
    Bibliothek bibliothek;

    // Test-Medien erstellen.
    Medium buch(
        1,

        "C++ Grundlagen",
        "Max Mustermann",

        2020,

        MediumTyp::Buch
    );
    Medium dvd(
        2,

        "Matrix",
        "Lana Wachowski",

        1999,

        MediumTyp::DVD
    );

    // Medien zur Bibliothek hinzufügen.
    bibliothek.mediumHinzufuegen(buch);

    bibliothek.mediumHinzufuegen(dvd);

    // Test-Mitglieder erstellen.
    Mitglied anna("Anna", 101);

    Mitglied ben("Ben", 102);

    // Mitglieder hinzufügen.
    bibliothek.mitgliedHinzufuegen(anna);

    bibliothek.mitgliedHinzufuegen(ben);

    // TEST 1

    // Erfolgreiches Ausleihen testen.
    assert(bibliothek.ausleihen(101, 1));

    // TEST 2

    // Dasselbe Medium darf nicht noch einmal ausgeliehen werden.
    assert(!bibliothek.ausleihen(102, 1));

    // TEST 3

    // Rückgabe testen.
    assert(bibliothek.zurueckgeben(101, 1));

    // TEST 4

    // Nach der Rückgabe kann Ben das Medium ausleihen.
    assert(bibliothek.ausleihen(102, 1));

    // TEST 5

    // Unbekanntes Mitglied darf nichts ausleihen.
    assert(!bibliothek.ausleihen(999, 2));

    // TEST 6

    // Unbekanntes Medium darf nicht ausgeliehen werden.
    assert(!bibliothek.ausleihen(101, 999));

    // Meldung, wenn alle Tests erfolgreich waren.
    std::cout << "\nAlle Tests erfolgreich!" << std::endl;
}
// MAIN

int main()
{

    // BIBLIOTHEK ERSTELLEN

    // Eine neue Bibliothek wird erstellt.
    Bibliothek bibliothek;

    // 5 MEDIEN ERSTELLEN

    // Erstes Medium: Buch.
    Medium medium1(
        1,

        "C++ Grundlagen",
        "Max Mustermann",

        2020,
        MediumTyp::Buch
    );

    // Zweites Medium: Buch.
    Medium medium2(
        2,

        "HTML und CSS",
        "Anna Beispiel",

        2022,
        MediumTyp::Buch
    );
    // Drittes Medium: DVD.
    Medium medium3(
        3,

        "Matrix",
        "Lana Wachowski",

        1999,
        MediumTyp::DVD
    );
    // Viertes Medium: DVD.
    Medium medium4(
        4,

        "Inception",
        "Christopher Nolan",

        2010,
        MediumTyp::DVD
    );
    // Fünftes Medium: Zeitschrift.
    Medium medium5(
        5,

        "IT Magazin",
        "Tech Verlag",

        2025,
        MediumTyp::Zeitschrift
    );

    // MEDIEN HINZUFÜGEN

    // Erstes Medium hinzufügen.
    bibliothek.mediumHinzufuegen(medium1);

    // Zweites Medium hinzufügen.
    bibliothek.mediumHinzufuegen(medium2);

    // Drittes Medium hinzufügen.
    bibliothek.mediumHinzufuegen(medium3);

    // Viertes Medium hinzufügen.
    bibliothek.mediumHinzufuegen(medium4);

    // Fünftes Medium hinzufügen.
    bibliothek.mediumHinzufuegen(medium5);

    // 2 MITGLIEDER ERSTELLEN

    // Erstes Mitglied erstellen.
    Mitglied mitglied1("Ali", 1001);

    // Zweites Mitglied erstellen.
    Mitglied mitglied2("Sara", 1002);

    // MITGLIEDER HINZUFÜGEN

    // Erstes Mitglied hinzufügen.
    bibliothek.mitgliedHinzufuegen(mitglied1);

    // Zweites Mitglied hinzufügen.
    bibliothek.mitgliedHinzufuegen(mitglied2);

    // BESTAND AM ANFANG

    // Bestand der Bibliothek anzeigen.
    bibliothek.zeigeBestand();

    // SZENARIO 1: ERFOLGREICHES AUSLEIHEN

    // Ali leiht Medium 1 aus.
    std::cout << "\n--- Szenario 1 ---" << std::endl;

    // Ergebnis ausgeben.
    if (bibliothek.ausleihen(1001, 1))
    {

        // Wenn erfolgreich.
        std::cout << "Medium 1 erfolgreich ausgeliehen."

            << std::endl;

    }
    else
    {
        // Wenn nicht erfolgreich.
        std::cout << "Ausleihen fehlgeschlagen."

            << std::endl;

    }

    // SZENARIO 2: BEREITS VERLIEHENES MEDIUM

    // Sara versucht, dasselbe Medium auszuleihen.
    std::cout << "\n--- Szenario 2 ---" << std::endl;

    // Ergebnis prüfen.
    if (!bibliothek.ausleihen(1002, 1))
    {
        // Fehlermeldung ausgeben.
        std::cout << "Medium 1 ist bereits ausgeliehen."

            << std::endl;
    }

    // SZENARIO 3: LIMIT VON 3 MEDIEN

    std::cout << "\n--- Szenario 3 ---" << std::endl;

    // Ali leiht Medium 2 aus.
    std::cout << "Medium 2: "

        << bibliothek.ausleihen(1001, 2)

        << std::endl;

    // Ali leiht Medium 3 aus.
    std::cout << "Medium 3: "

        << bibliothek.ausleihen(1001, 3)

        << std::endl;

    // Ali versucht ein viertes Medium auszuleihen.
    if (!bibliothek.ausleihen(1001, 4))
    {
        // Das Limit wurde erreicht.
        std::cout << "Medium 4 konnte nicht ausgeliehen werden."

            << std::endl;

        // Hinweis ausgeben.
        std::cout << "Das Mitglied darf maximal 3 Medien "

            << "gleichzeitig ausleihen."

            << std::endl;

    }

    // SZENARIO 4: RÜCKGABE UND ERNEUTES AUSLEIHEN

    std::cout << "\n--- Szenario 4 ---" << std::endl;

    // Ali gibt Medium 1 zurück.
    if (bibliothek.zurueckgeben(1001, 1))
    {
        // Rückgabe erfolgreich.
        std::cout << "Medium 1 wurde zurückgegeben."

            << std::endl;

    }
    // Sara leiht Medium 1 erneut aus.
    if (bibliothek.ausleihen(1002, 1))
    {
        // Neue Ausleihe erfolgreich.
        std::cout << "Sara hat Medium 1 ausgeliehen."

            << std::endl;

    }

    // SZENARIO 5: UNBEKANNTE ID

    std::cout << "\n--- Szenario 5 ---" << std::endl;

    // Nicht vorhandenes Medium testen.
    if (!bibliothek.ausleihen(1001, 999))
    {
        // Fehlermeldung ausgeben.
        std::cout << "Medium mit ID 999 wurde nicht gefunden."

            << std::endl;

    }
    // Nicht vorhandenes Mitglied testen.
    if (!bibliothek.ausleihen(9999, 2))
    {
        // Fehlermeldung ausgeben.
        std::cout << "Mitglied mit Nummer 9999 wurde nicht gefunden."

            << std::endl;
    }
    // AUSLEIHEN ANZEIGEN

    std::cout << "\n--- Ausleihen ---" << std::endl;

    /* Hinweis:
     Wir erstellen hier keine neuen Mitglieder,
     sondern zeigen den aktuellen Zustand über die gespeicherten Objekte.
     Die Aufgabenstellung verlangt die Methode zeigeAusleihen()
     in der Klasse Mitglied.
     Da die Bibliothek ihre Mitglieder intern verwaltet,
    wird hier demonstriert, wie die Methode bei einem eigenen
    Mitglied funktioniert.

    // Temporäres Mitglied für Demonstration erstellen.*/
    Mitglied demoMitglied("Demo", 5000);

    // Ausgabe des Demo-Mitglieds.
    demoMitglied.zeigeAusleihen();

    // SUCHFUNKTION TESTEN

    std::cout << "\n--- Suche nach 'C++' ---" << std::endl;

    // Nach "C++" suchen.
    std::vector<const Medium*> ergebnisse =

        bibliothek.suche("C++");

    // Alle Suchergebnisse ausgeben.
    for (const Medium* medium : ergebnisse)
    {
        // Gefundenes Medium ausgeben.
        std::cout << *medium << std::endl;
    }

    // ENDGÜLTIGEN BESTAND ANZEIGEN

    // Aktuellen Bestand anzeigen.
    bibliothek.zeigeBestand();

    // AUTOMATISCHE TESTS

    // Alle automatischen Tests durchführen.
    testeAlles();

    // PROGRAMM ENDE
    return 0;
}
