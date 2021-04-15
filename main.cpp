#include <iostream>
#include <random>
#include <fstream>
#include <string>

#include <iomanip>
#include <windows.h>

#include "two_way_list/TwoWayList.h"
#include "array/DynamicArray.h"


using namespace std;
int input, index;
char operation;
//controls the main loop of the program
bool running = true;
//controls loop of given structure while working in specified mode
bool structure = true;
//controls loop of specified mode
bool mode = true;
//path to txt file, where randomly generated numbers are stored
string filepath="random_numbers.txt";

void random_numbers_to_txt() {
    fstream file;
    random_device device;
    mt19937 generator(device());
    int extreme, number;

    cout << "Maksymalna wartosc w strukturze: ";
    cin >> extreme;
    cout << "Minimalna wartosc w strukturze: " << -extreme << endl;
    cout << "Ile liczb do wylosowania: ";
    cin >> number;

    uniform_int_distribution<> distribution(-extreme, extreme);

    file.open(filepath, ios::out);
    file << number << endl;
    for (int i = 0; i < number; i++)
        file << distribution(generator) << endl;
    file.close();

}

long long int readQPC() {
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return ((long long int) count.QuadPart);
}

int main() {
    cout << "------------------SDiZO Projekt------------------" << endl;
    cout << "Jakub Wierzchowiec, 252738, 04.2021" << endl;
    while (running) {
        cout << "[0] Zakoncz program" << endl;
        cout << "[1] Tryb kontrolny" << endl;
        cout << "[2] Tryb pomiarowy" << endl;
        cout << ": ";
        cin >> input;
        switch (input) {
            case 0: {
                running = false;
                break;
            }

            case 1: {
                while (mode) {
                    cout << "-----------------Tryb kontrolny-----------------" << endl;
                    cout << "[1] Lista dwukierunkowa" << endl;
                    cout << "[2] Tablica dynamiczna" << endl;
                    cout << "[3] Kopiec binarny" << endl;
                    cout << "[4] Drzewo czerwono-czarne" << endl;
                    cout << "[5] Powrot do menu" << endl;
                    cout << ": ";
                    cin >> input;
                    switch (input) {
                        case 0: {
                            mode = false;
                            break;
                        }

                        case 1: {
                            structure = true;
                            auto *list = new TwoWayList();
                            cout << "[1] Lista dwukierunkowa" << endl;
                            while (structure) {
                                cout << "DODAWANIE: (A) na poczatek  (B) na koniec     (C) w dowolne miejsce" << endl;
                                cout << "USUWANIE:  (D) z poczatku   (E) z konca       (F) z dowolnego miejsca" << endl;
                                cout << "INNE:      (G) Wyszukiwanie (H) Wyczysc liste (X) Powrot" << endl;
                                cout << ": ";
                                cin >> operation;

                                switch (operation) {
                                    case 'A':
                                        cout << "Dodawana liczba: ";
                                        cin >> input;
                                        list->addFirst(input);
                                        break;

                                    case 'B':
                                        cout << "Dodawana liczba: ";
                                        cin >> input;
                                        list->addLast(input);
                                        break;

                                    case 'C':
                                        cout << "Dodawana liczba: ";
                                        cin >> input;
                                        cout << "Na jaka pozycje: ";
                                        cin >> index;
                                        list->add(input, index);
                                        break;

                                    case 'D':
                                        list->removeFirst();
                                        break;

                                    case 'E':
                                        list->removeLast();
                                        break;

                                    case 'F':
                                        cout << "Indeks elementu do usuniecia: ";
                                        cin >> index;
                                        list->remove(index);
                                        break;

                                    case 'G':
                                        cout << "Liczba, ktora ma zostac znaleziona: ";
                                        cin >> input;
                                        if (list->contains(input))
                                            cout << input << " znajduje sie na liscie." << endl;
                                        else
                                            cout << input << " nie znajduje sie na liscie" << endl;
                                        break;

                                    case 'H':
                                        list->removeAll();
                                        break;

                                    case 'X':
                                        structure = false;
                                        break;

                                    default:
                                        cout << "Niepoprawny wybor! Sproboj ponownie" << endl;
                                        break;
                                }
                            }
                            delete list;
                            break;
                        }

                        case 2: {
                            structure = true;
                            int *array = nullptr;
                            int size = 0;

                            cout << "[2] Tablica dynamiczna" << endl;

                            while (structure) {
                                show(array, &size);

                                cout << "DODAWANIE: (A) na poczatek  (B) na koniec (C) w dowolne miejsce" << endl;
                                cout << "USUWANIE:  (D) z poczatku   (E) z konca   (F) z dowolnego miejsca" << endl;
                                cout << "INNE:      (G) Wyszukiwanie (H) Wyczysc   (X) Powrot" << endl;
                                cout << ": ";
                                cin >> operation;

                                switch (operation) {
                                    case 'A': {
                                        cout << "Dodawana liczba: ";
                                        cin >> input;

                                        array = addFirst(array, &size, input);
                                        break;
                                    }

                                    case 'B': {
                                        cout << "Dodawana liczba: ";
                                        cin >> input;
                                        array = addLast(array, &size, input);
                                        break;
                                    }

                                    case 'C': {
                                        cout << "Dodawana liczba: ";
                                        cin >> input;
                                        cout << "Na jaka pozycje: ";
                                        cin >> index;
                                        array = add(array, &size, index, input);
                                        break;
                                    }

                                    case 'D': {
                                        array = removeFirst(array, &size);
                                        break;
                                    }

                                    case 'E': {
                                        array = removeLast(array, &size);
                                        break;
                                    }

                                    case 'F': {
                                        cout << "Pozycja do usuniecia: ";
                                        cin >> index;
                                        array = remove(array, &size, index);
                                        break;
                                    }

                                    case 'G': {
                                        cout << "Liczba do znalezienia: ";
                                        cin >> input;
                                        if (contains(array, &size, input))
                                            cout << input << " znajduje sie w tablicy." << endl;
                                        else
                                            cout << input << " nie znajduje sie w tablicy" << endl;
                                        break;
                                    }

                                    case 'H': {
                                        delete[] array;
                                        size = 0;
                                        array = nullptr;
                                        break;
                                    }

                                    case 'X': {
                                        structure = false;
                                        break;
                                    }

                                    default: {
                                        cout << "Niepoprawny wybor! Sproboj ponownie." << endl;
                                        break;
                                    }

                                }
                            }
                            delete[] array;
                            break;
                        }

                        case 3: {
                            cout << "[3] Kopiec binarny" << endl;
                            break;
                        }

                        case 4: {
                            cout << "[4] Drzewo czerwono - czarne" << endl;
                            break;
                        }

                        case 5: {
                            mode = false;
                            break;
                        }

                        default: {
                            cout << "Niepoprawny wybor! Sproboj ponownie." << endl;
                            break;
                        }
                    }
                }
                break;
            }

            case 2: {
                fstream file;
                string tmp;
                long long int frequency, start, elapsed = 0;
                QueryPerformanceCounter((LARGE_INTEGER *) &frequency);
                bool found;
                while (mode) {
                    structure = true;
                    cout << "-----------------Tryb pomiarowy----------------" << endl;
                    cout << "[1] Lista dwukierunkowa" << endl;
                    cout << "[2] Tablica dynamiczna" << endl;
                    cout << "[3] Kopiec binarny" << endl;
                    cout << "[4] Drzewo czerwono-czarne" << endl;
                    cout << "[5] Powrot do menu" << endl;
                    cout << ": ";
                    cin >> input;
                    switch (input) {
                        case 1: {
                            auto *list = new TwoWayList();
                            cout << "[1] Lista dwukierunkowa" << endl;
                            random_numbers_to_txt();

                            file.open(filepath, ios::in);
                            //fill the list with random numbers from txt file
                            while (getline(file, tmp))
                                list->addLast(atoi(tmp.c_str()));
                            file.close();

                            while (structure) {
                                cout << "DODAWANIE: (A) na poczatek  (B) na koniec  (C) w dowolne miejsce" << endl;
                                cout << "USUWANIE:  (D) z poczatku   (E) z konca    (F) z dowolnego miejsca" << endl;
                                cout << "INNE:      (G) Wyszukiwanie (X) Powrot" << endl;
                                cout << ": ";
                                cin >> operation;
                                if (operation == 'A' || operation == 'B' || operation == 'C') {
                                    cout << "Dodawana liczba: ";
                                    cin >> input;
                                    if (operation == 'A') {
                                        start = readQPC();
                                        list->addFirst(input);
                                        elapsed = readQPC() - start;
                                    } else if (operation == 'B') {
                                        start = readQPC();
                                        list->addLast(input);
                                        elapsed = readQPC() - start;
                                    } else {
                                        cout << "Na jaka pozycje: ";
                                        cin >> index;
                                        start = readQPC();
                                        list->add(input, index);
                                        elapsed = readQPC() - start;
                                    }
                                } else if (operation == 'D') {
                                    start = readQPC();
                                    list->removeFirst();
                                    elapsed = readQPC() - start;
                                } else if (operation == 'E') {
                                    start = readQPC();
                                    list->removeLast();
                                    elapsed = readQPC() - start;
                                } else if (operation == 'F') {
                                    cout << "Pozycja do usuniecia: ";
                                    cin >> index;
                                    start = readQPC();
                                    list->remove(index);
                                    elapsed = readQPC() - start;
                                } else if (operation == 'G') {
                                    cout << "Liczba do znalezienia: ";
                                    cin >> input;
                                    start = readQPC();
                                    found = list->contains(input);
                                    elapsed = readQPC() - start;
                                    if (found)
                                        cout << input << " znajduje sie na liscie" << endl;
                                    else
                                        cout << input << " nie znajduje sie na lisicie" << endl;
                                } else if (operation == 'X') {
                                    structure = false;
                                } else {
                                    cout << "Nieprawidlowy wybor sproboj ponownie!" << endl;
                                }

                                cout << "Time [s] = " << fixed << setprecision(30) << (float) elapsed /
                                                                                      frequency << endl;
                                cout << "Time [ms] = " << setprecision(30) << (1000.0 * elapsed) /
                                                                              frequency << endl;
                                cout << "Time [us] = " << setprecision(30) << (1000000.0 * elapsed) /
                                                                              frequency << endl << endl;
                            }

                            delete list;
                            break;
                        }

                        case 2: {
                            int *array = nullptr;
                            int size = 0;

                            cout << "[2] Tablica dynamiczna" << endl;
                            random_numbers_to_txt();
                            file.open(filepath, ios::in);

                            file >> size;
                            array = new int[size];
                            //fill the array with random numbers from txt file
                            for (int i = 0; i<size; i++)
                                file>>array[i];
                            file.close();

                            while (structure) {
                                cout << "DODAWANIE: (A) na poczatek  (B) na koniec (C) w dowolne miejsce" << endl;
                                cout << "USUWANIE:  (D) z poczatku   (E) z konca   (F) z dowolnego miejsca" << endl;
                                cout << "INNE:      (G) Wyszukiwanie (X) Powrot" << endl;
                                cout << ": ";
                                cin >> operation;
                                if (operation == 'A' || operation == 'B' || operation == 'C') {
                                    cout << "Dodawana liczba: ";
                                    cin >> input;
                                    if (operation == 'A') {
                                        start = readQPC();
                                        array = addFirst(array, &size, input);
                                        elapsed = readQPC() - start;
                                    } else if (operation == 'B') {
                                        start = readQPC();
                                        array = addLast(array, &size, input);
                                        elapsed = readQPC() - start;
                                    } else {
                                        cout << "Na jaka pozycje: ";
                                        cin >> index;
                                        start = readQPC();
                                        array = add(array, &size, index, input);
                                        elapsed = readQPC() - start;
                                    }
                                } else if (operation == 'D') {
                                    start = readQPC();
                                    array = removeFirst(array, &size);
                                    elapsed = readQPC() - start;
                                } else if (operation == 'E') {
                                    start = readQPC();
                                    array = removeLast(array, &size);
                                    elapsed = readQPC() - start;
                                } else if (operation == 'F') {
                                    cout << "Pozycja do usuniecia: " << endl;
                                    cin >> index;
                                    start = readQPC();
                                    array= remove(array, &size, index);
                                    elapsed = readQPC() - start;
                                } else if (operation == 'G') {
                                    cout << "Liczba do znalezienia: ";
                                    cin >> input;
                                    start = readQPC();
                                    found = contains(array, &size, input);
                                    elapsed = readQPC() - start;
                                    if (found)
                                        cout << input << " znajduje sie w tablicy" << endl;
                                    else
                                        cout << input << " nie znajduje sie w tablicy" << endl;
                                } else if (operation == 'X') {
                                    structure = false;
                                } else {
                                    cout << "Nieprawidlowy wybor! Sproboj ponownie." << endl;
                                }
                                cout << "Time [s] = " << fixed << setprecision(30) << (float) elapsed /
                                                                                      frequency << endl;
                                cout << "Time [ms] = " << setprecision(30) << (1000.0 * elapsed) /
                                                                              frequency << endl;
                                cout << "Time [us] = " << setprecision(30) << (1000000.0 * elapsed) /
                                                                              frequency << endl << endl;
                            }
                            delete array;
                            break;
                        }

                        case 3: {
                            break;
                        }

                        case 4: {
                            break;
                        }

                        case 5: {
                            mode = false;
                            break;
                        }

                        default: {
                            cout << "Niepoprawny wyobr! Sproboj ponownie" << endl;
                            break;
                        }
                    }

                }
                break;
            }

            default: {
                cout << "Niepoprawny wybor! Sproboj ponownie." << endl;
                break;
            }
        }
        mode = true;
    }

    return 0;
}
