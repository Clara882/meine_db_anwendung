#include <iostream>
#include <CLI/CLI.hpp>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

int main(int argc, char** argv)
{
	std::cout << "Hello World" << "\n";

	CLI::App app{"Dies ist ein Programm was uns den Umgang mit Lagerhaltungsdaten zeigen soll","Lagerhaltungsprogramm"};

    std::string filepath;
    app.add_option("-r,--read", filepath,"Path to config file")
        ->required()
        ->check(CLI::ExistingFile);
        
	 try{
        app.parse(argc, argv);
    } catch(const CLI::ParseError& e){
        return app.exit(e);
    }

    std::ifstream file{filepath};
    if(!file.is_open()){
        std::cout << "Error opening file!\n";
        exit(0);
    }

    nlohmann::json database_object;
    try
    {
        database_object = nlohmann::json::parse(file);
    }
    catch (nlohmann::json::parse_error& ex)
    {
        std::cerr << "parse error at byte " << ex.byte << std::endl;
    }

   /* for (auto& element : database_object["Regale"]){
        std::cout << "Regalnummer:" << element["Regalnummer"] << std::endl;
        std::cout << "Anzahl Lagerplätze:" << element["Anzahl Lagerplätze"] << std::endl;
        std::cout << "Leere Plätze:" << element["Leere Plätze"] << std::endl;
        std::cout << "Inhalt:" << element["Inhalt"] << std::endl;
        std::cout << "-------------------------------------------------------------------" << std::endl;
        
        }
  */  //std::cout << database_object["Regale"];{"Inhalt"};.size() << std::endl;
    int belegte_plaetze, anzahl_plaetze;
    std::string c, d, e;
    int leere_plaetze;

    for (auto& element : database_object["Regale"]){
        std::cout << "Regalnummer:" << element["Regal"] << std::endl;
        std::cout << "Anzahl Lagerplätze:" << element["Anzahl Lagerplätze"] << std::endl;
        std::cout << "Inhalt:" << element["Inhalt"] << std::endl;
                //std::cout << "Leere Plätze:" << element["Leere Plätze"] << std::endl;
        belegte_plaetze = element["Inhalt"].size(); // Anzahl der Elemente in Inhalt
        anzahl_plaetze = element["Anzahl Lagerplätze"]; 
        leere_plaetze = anzahl_plaetze - belegte_plaetze; // berechnet Leere Plätze
        std::cout << "Leere Plätze:" << leere_plaetze << std::endl; // gibt Anzahl der Leeren Plätze aus
        c = element["Inhalt"].at(2); // setzt c = mit dem 3 Element in Inhalt
        std::cout << c << std::endl; 
        std::cin >> e; 
        element["Inhalt"].at(2).swap(e); // tauscht den Inhalt des 3. Elemente mit e
        std::cout << "Inhalt:" << element["Inhalt"] << std::endl;
        element["Inhalt"].at(2).swap(element["Inhalt"].at(1));
        std::cout << "Inhalt:" << element["Inhalt"] << std::endl;
        c = element["Inhalt"].at(2);
        std::cout << "-------------------------------------------------------------------" << std::endl;
        nlohmann::json::parse(file).update(database_object);
    }

    //nlohmann::json::parse(file).update(database_object);

    
    /* try
    {
        nlohmann::json::parse(file) = database_object;
    }
    catch (nlohmann::json::parse_error& ex)
    {
        std::cerr << "parse error at byte " << ex.byte << std::endl;
    }*/
    return 0;
}
