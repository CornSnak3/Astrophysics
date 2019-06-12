#pragma once

#include <conio.h>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <Windows.h>

#define CONSOLE_COLOR_BLACK 0
#define CONSOLE_COLOR_BLUE  1
#define CONSOLE_COLOR_WHITE 7

class Menu {
private:

  const int width = 97;

  struct MenuItem {
    uint8_t _number;
    std::string _text;
    std::string _paddedText;
    bool _isSelected;

    MenuItem() { }

    MenuItem(uint8_t number, const std::string & text)
      : _number(number), _text(text), _paddedText(""), _isSelected(false) { }
  };

  MenuItem header, hotkeys;
  std::vector<MenuItem> items_;

public:

  Menu(std::initializer_list<std::string> &menu) {
    uint8_t count = 98;
    hotkeys = MenuItem(count, "ÂÂÅĞÕ/ÂÍÈÇ(ÑÒĞÅËÊÈ) | ÂÛÕÎÄ(ESC) | ÂÂÎÄ(ENTER)");
    for (auto item : menu) {
      if (count == 98) {
        header = MenuItem(count, item);
        count = 0;
      } else {
        items_.push_back(MenuItem(count, item));
        count++;
      }
    }

    items_.front()._isSelected = true;
  };

  void draw(void) {
    system("cls");
    printItem(1, 15, header);
    std::cout << std::endl;
    for (auto &item : items_) {
      redraw(item);
      std::cout << std::endl;
    }
    std::cout << std::endl;
    printItem(7, 0, hotkeys);
  }

  void resetPosition(void) {
    int count = 0;
    for (auto & item : items_)
      item._isSelected = (count++ == 0) ? true : false;
  }

  void redraw(MenuItem &item) {

    int backgroundColor = (item._isSelected) ? 15 : 0;
    int foregroundColor = (item._isSelected) ? 0 : 15;
    printItem(backgroundColor, foregroundColor, item);
  }

  void printItem(int backgroundColor, int foregroundColor, MenuItem &item) {

    if (item._paddedText == "") {
      std::string text = item._text;
      uint8_t textLength = text.length();

      uint8_t padding = ((width - textLength) / 2) + 5;
      std::string paddingString(padding, ' ');

      item._paddedText = paddingString + text + paddingString;

      if (item._paddedText.length() == width - 1) {
        item._paddedText += ' ';
      }
    }

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (WORD)((backgroundColor << 4) | foregroundColor));
    std::cout << item._paddedText << std::endl;
    SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
  }

  int move(int step) {
    int newIdx;
    for (auto & item : items_) {
      if (item._isSelected) {
        int newSelection = item._number + step;
        if (newSelection < 0 || newSelection > items_.size() - 1) {
          return item._number;
        }
        item._isSelected = false;
        newIdx = newSelection;
        break;
      }
    }
    items_[newIdx]._isSelected = true;
    draw();
    return newIdx;
  }

  int execute(void) {
    int selectedItemNumber = 0;
    char keyPressed;
    do {
      keyPressed = 0;
      draw();
      keyPressed = _getch();
      switch (keyPressed) {
      case 72: // Ñòğåëêà ââåğõ
        selectedItemNumber = move(-1);
        break;
      case 80: // Ñòğåëêà âíèç
        selectedItemNumber = move(1);
        break;
      case '\r':
        return selectedItemNumber;
        break;
      default:
        break;
      }
    } while (keyPressed != 27);
    return -1;
  }

};


