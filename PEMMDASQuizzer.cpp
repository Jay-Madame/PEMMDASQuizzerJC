/*
Contains Modulus Quizzer and PEMMDAS Quizzer
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

double modulusQuiz();
double pemmdasQuiz();
int solvingPemmdas(int *equation, int repeat, int);
void printScores(vector<double> modulus, vector<double> pemmdas);

int getRandomInt(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

int operatorCase()
{
    int opp = rand() % 5 + 1;
    return opp;
}

int main()
{
    srand(time(0));
    char selection;
    vector<double> modulusScores;
    vector<double> pemmdasScores;

    do
    {
        std::cout << "Welcome to PEMMDAS practice.  " << endl
                  << endl
                  << "Select a menu option to proceed: " << endl
                  << "1  Modulus Practice" << endl
                  << "2  PEMMDAS Practice" << endl
                  << "3  Score Report" << endl;
        cin >> selection;

        double tempScore = 0.0;
        switch (selection)
        {
        case '1':
            tempScore = modulusQuiz();
            modulusScores.push_back(tempScore);
            break;
        case '2':
            tempScore = pemmdasQuiz();
            pemmdasScores.push_back(tempScore);
            break;
        case '3':
            printScores(modulusScores, pemmdasScores);
            break;
        case '4':
            return 0;
        default:
            cout << " Please enter a valid entry.";
        }
    } while (true);
}

double modulusQuiz()
{
    int times = 0;
    int score = 0;
    cout << "How many problems would you like to solve?" << endl;
    cin >> times;
    int total = times;

    while (times > 0)
    {
        int num1 = rand() % 10;
        int num2 = rand() % 9 + 1;
        int answer = 0;

        cout << "What is:" << endl
             << num1 << " % " << num2 << endl;
        cin >> answer;
        if (answer == (num1 % num2))
        {
            cout << "That's right!" << endl;
            score++;
        }
        else
        {
            cout << "No, the answer is " << (num1 % num2) << endl;
        }
        times--;
    }

    double percent = score / static_cast<double>(total) * 100;
    cout << "You scored " << score << " out of " << total << endl
         << "That's " << percent << "%." << endl;

    return percent;
}

double pemmdasQuiz()
{
    int times = 0;
    cout << "How many problems would you like to solve?" << endl;
    cin >> times;
    int total = times;
    int canswer, answer, score = 0;

    while (times > 0)
    {

        int *numbers = nullptr;
        int *operators = nullptr;
        int *equation = nullptr;
        numbers = new int[9];
        operators = new int[8];
        equation = new int[17];

        for (int i = 0; i < 9; i++)
        {
            *(numbers + i) = getRandomInt(1, 20);
        }
        for (int i = 0; i < 8; i++)
        {
            *(operators + i) = operatorCase();
        }

        cout << "What is: ";

        int nindex, oindex = 0;

        for (int i = 0; i < 17; i++)
        {
            if (i % 2 == 0)
            {
                cout << *(numbers + nindex);
                *(equation + i) = *(numbers + nindex);
                nindex++;
            }
            else
            {
                *(equation + i) = *(operators + oindex);
                switch (operators[oindex])
                {
                case 1:
                    cout << " % ";
                    oindex++;
                    break;
                case 2:
                    cout << " / ";
                    oindex++;
                    break;
                case 3:
                    cout << " * ";
                    oindex++;
                    break;
                case 4:
                    cout << " + ";
                    oindex++;
                    break;
                default:
                    cout << " - ";
                    oindex++;
                    break;
                }
            }
        }
        canswer = solvingPemmdas(equation, 17, 1);

        cout << " = ?" << endl;
        cin >> answer;
        if (canswer == answer)
        {
            cout << "That's right!" << endl;
            score++;
        }
        else
        {
            cout << "The correct answer is " << canswer << endl;
        }
        delete[] equation;
        delete[] numbers;
        delete[] operators;

        times--;
    }
    double percent = score / static_cast<double>(total) * 100;
    cout << "You scored " << score << " out of " << total << endl
         << "That's " << percent << "%." << endl;

    return percent;
}

int solvingPemmdas(int *equation, int size, int repeat)
{
    int *newProb = new int[size];

    for (int i = 0; i < size; i++)
    {
        newProb[i] = equation[i];
    }

    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if ((repeat == 1) || (i % 2 != 0))
        {
            count = i - 1;

            if (equation[i] == 1 || equation[i] == 2 || equation[i] == 3)
            {
                switch (equation[i])
                {
                case 1:
                    newProb[count] = equation[count] % equation[i + 1];
                    break;
                case 2:
                    newProb[count] = equation[count] / equation[i + 1];
                    break;
                case 3:
                    newProb[count] = equation[count] * equation[i + 1];
                    break;
                }
            }
        }
        else
        {
            count = i - 1;

            if (equation[i] == 4 || equation[i] == 5)
            {
                switch (equation[i])
                {
                case 4:
                    newProb[count] = equation[count] + equation[i + 1];
                    break;
                case 5:
                    newProb[count] = equation[count] - equation[i + 1];
                    break;
                }
            }
        }

        if (i % 2 == 0)
        {
            newProb[i] = equation[count];
        }
    }

    if (size > 3)
    {
        solvingPemmdas(newProb, size - 2, 2);
    }
    else
    {
        int answer = newProb[0];

        delete[] newProb;
        return answer;
    }

    delete[] newProb;
}

void printScores(vector<double> modulus, vector<double> pemmdas)
{
    int modCount = 1, pemCount = 1;
    cout << "Your percentages on modulus quizzes are:" << endl;
    for (double percent : modulus)
    {
        cout << modCount << ":\t" << percent << endl;
        modCount++;
    }
    cout << endl
         << endl;
    cout << "Your percentages on PEMMDAS quizzes are:" << endl;
    for (double percent : pemmdas)
    {
        cout << modCount << ":\t" << percent << endl;
        modCount++;
    }
}