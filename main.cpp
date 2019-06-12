#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "ConsoleTable.h"
#include "Star.h"
#include "Menu.h"

std::vector<Star> * getStarsFromFile(void);

std::string query(const std::string &);

void deleteStar(void);
void appHelp(void);
void about(void);


int main(int argc, char *argv[]) {

  system("cls");
  setlocale(LC_ALL, "Russian");

  std::initializer_list<std::string> mainMenu = { 
    "ГЛАВНОЕ МЕНЮ", "Показать таблицу", "Удалить запись", "Руководство пользователя", "О программе "
  };

  std::initializer_list<std::string> tableHeaders = {
    "ID", "Название", "Масса, M@", "Радиус, R@", "Расстояние, св. лет", "Спектр", "Светимость"
  };

  std::vector<Star> *stars = getStarsFromFile();

  ConsoleTable *table = new ConsoleTable(tableHeaders);
 
  for (Star & star : *stars) {
    table->addRow(star.getVector());
  }

  Menu MainMenu(mainMenu);
  int choice = 0;
  
  while (choice != -1) {
    choice = MainMenu.execute();
    std::string id;
    int index;
    switch (choice) {
    case 0:
      system("cls");
      std::cout << *table;
      system("pause");
      break;
    case 1:
      system("cls");
      std::cout << *table;
      id = query("ID звезды");
      index = 0;
      for (Star & star : *stars) {
        if (id == star.getID()) {
          stars->erase(stars->begin() + index);
          table->remove(id);
          break;
        }
        index++;
      }
      system("pause");
      break;
    case 2:
      system("cls");
      appHelp();
      system("pause");
      break;
    case 3:
      system("cls");
      about();
      system("pause");
      break;
    default:
      break;
    }
    MainMenu.resetPosition();
  }

  std::ofstream out("Stars.db", std::ios_base::trunc);
  if (out.is_open()) {
    for (Star & star : *stars) {
      int count = 0;
      for (auto val : star.getVector()) {
        if (count != 0) {
          out << val << ";";
        }
        count++;
      }
      out << std::endl;
    }
    out.close();
  }

  delete stars;
  delete table;

  return 0;
}

std::vector<Star> * getStarsFromFile() {
  std::ifstream file;
  file.open("Stars.db", std::ios::in);
  if (file.is_open()) {
    std::vector<Star> *stars = new std::vector<Star>();
    std::string line;
    while (getline(file, line)) {
      std::vector<std::string> starInitParameters;
      while (line.find(';') != std::string::npos) {
        size_t pos = line.find(';');
        if (line.length() - pos < 0) {
          break;
        }
        std::string param = line.substr(0, pos);
        starInitParameters.push_back(param);
        line = line.substr(pos + 1);
      }
      stars->push_back(Star(starInitParameters, stars->size()));
    }
    file.close();
    return stars;
  } else {
    return nullptr;
  }
}

std::string query(const std::string & question) {
  std::cout << std::setw(25) << std::left << question << ">> ";
  std::string x;
  std::cin >> x;
  return x;
}


void appHelp() {
  std::stringstream ss;
  ss << "Описание пунктов меню:" << std::endl <<
    "  +  \"Показать таблицу\" - просмотр записей о звездах в виде таблицы" << std::endl <<
    "  +  \"Удалить запись\" - удаление записи с заданным ID" << std::endl <<
    "  +  \"Руководство пользователя\" - данное сообщение" << std::endl <<
    "  +  \"О программе\" - информация о приложении и авторе" << std::endl << std::endl <<
    "Клавиши навигации:" << std::endl << "  ENTER - выбрать" << std::endl <<
    "  ESCAPE - завершить работу" << std::endl <<
    "  СТРЕЛКА ВВЕРХ/ВНИЗ - выбор пункта меню" << std::endl << std::endl;
  std::cout << ss.str();
}

void about() {
  std::stringstream ss;
  ss << "Астрофизическая база данных звезд v. 0.1-alpha" << std::endl <<
    "Приложение разработано в рамках лабораторной работы" << std::endl <<
    "и предназначено для хранения, просмотра и редактирования" << std::endl <<
    "записей о звездах." << std::endl <<   "Автор: Леонид Волков, ГУАП, гр. 4731" <<
    std::endl << "Санкт-Петербург, 2019 год" << std::endl;
  std::cout << ss.str();
}
