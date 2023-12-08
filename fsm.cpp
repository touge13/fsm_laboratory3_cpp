#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

// Структура для представления перехода из одного состояния в другое
struct Transition {
    std::string input;         // Обрабатыаемый элемент
    std::string nextState;     // Следующее состояние
};

// Класс для представления конечного автомата
class FiniteStateMachine {
private:
    std::unordered_map<std::string, std::vector<Transition>> transitions;          // Хранение правил перехода
    std::string currentState;                                            // Текущее состояние
public:
    // Метод для добавления правила перехода
    void addTransition(std::string currentState, Transition transition) {
        transitions[currentState].push_back(transition);
    }

    // Метод для установки начального состояния
    void setInitialState(std::string initialState) {
        currentState = initialState;
    }

    // Метод для проверки, может ли обработан символ на текущем состоянии
    bool validateString(const std::string& input) {
        
            bool hasTransition = false;
            for (const Transition& transition : transitions[currentState]) {
                if (transition.input == input) {
                    currentState = transition.nextState;
                    hasTransition = true;
                    break;
                }
            }

            if (!hasTransition) {
                return false;
            }
        
        
        return true;
    }
};

std::vector<std::string> createMassive(const std::string input, const std::vector<std::string>& alphabit, bool &workFlag, std::string &nonExistelement) {
    std::vector<std::string> massive;
    std::string current;

    nonExistelement = input;

    for (int i = 0; i < input.length(); i++) {
        char c = input[i];
        if (c != ' ' && c != '?' && c != ',' && c != '!') {
            current += c;
        }
        
        for (const std::string& word : alphabit) {
            if (current == word) {
                massive.push_back(word);
                nonExistelement.erase(nonExistelement.find(current), current.length());
                current = "";
                workFlag = true;
                break;
            } else {
                workFlag = false;
            }
        }
    }
    
    

    return massive;
}

int main() {
    bool resultFlag = true;
    std::string nonExistelement = "";
    
    // Создание объекта конечного автомата
    FiniteStateMachine fsm;

    // Создание и добавление правил перехода
    Transition transition1{"abc", "A"};
    fsm.addTransition("S", transition1);

    Transition transition2{"deg", "S"};
    fsm.addTransition("A", transition2);
    
    // Установка начального состояния
    fsm.setInitialState("S");

    // Ввод исходной строки и проверка
    std::string input;
    std::cout << "Введите исходную строку: ";
    std::cin >> input;

    bool workFlag = true;

    std::vector<std::string> alphabit = {"abc", "deg", "uau", "uwu"};        // Алфавит автомата
    std::vector<std::string> result_massive = createMassive(input, alphabit, workFlag, nonExistelement);   //Массив из элементов, которые 
                                                                           //содержатся и во входной строке
                                                                           //input и в алфавите автомата alphabit
    
    if (workFlag == true) {
        //пошла жара
        bool result;

        for(int i = 0; i < result_massive.size(); i++) {
            std::string element = "";
            element += result_massive[i];
            
            result = fsm.validateString(element);
            
            if (result == false) {
                resultFlag = false;
            }
            
            // Вывод результата
            if (result) {
                std::cout << "Элемент " << element << " в строке " << input << ": True." << std::endl;
            } else {
                std::cout << "Элемент " << element << " в строке " << input << ": False." << std::endl;
                result = false;
            }

        }
        
        if (resultFlag == true) {
            std::cout << "Итог: строка может быть обработана.";
        } else if (resultFlag == false) {
            std::cout << "Итог: строка не может быть обработана.";
        }
    } else {
        std::cout << "Строки " << nonExistelement << " не существует в алфавите автомата";
    }

    return 0;
}

// |  Состояние  | Входной символ| Следующее состояние |
// |:-----------:|:-------------:|:-------------------:|
// |      S      |       abc     |         A           |
// |      A      |       deg     |         S           |

