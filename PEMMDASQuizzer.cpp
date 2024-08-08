#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

double modulusQuiz();
double pemmdasQuiz();
int solvingPemmdas(int *equation, int size);
void printScores(vector<double> modulus, vector<double> pemmdas);

int getRandomInt(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

int operatorCase()
{
    return rand() % 4 + 1;
}

int main()
{
    srand(static_cast<unsigned>(time(0)));
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
        default:
            cout << " Please enter a valid entry." << endl;
        }
    } while (true);

    return 0;
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
        int *numbers = new int[9];
        int *operators = new int[8];
        int *equation = new int[17];

        int nindex = 0, oindex = 0;

        for (int i = 0; i < 9; i++)
        {
            numbers[i] = getRandomInt(1, 20);
        }
        for (int i = 0; i < 8; i++)
        {
            operators[i] = operatorCase();
        }

        cout << "What is: ";

        for (int i = 0; i < 17; i++)
        {
            if (i % 2 == 0)
            {
                cout << numbers[nindex];
                equation[i] = numbers[nindex];
                nindex++;
            }
            else
            {
                equation[i] = operators[oindex];
                switch (operators[oindex])
                {
                case 1:
                    cout << " % ";
                    break;
                case 2:
                    cout << " / ";
                    break;
                case 3:
                    cout << " * ";
                    break;
                case 4:
                    cout << " + ";
                    break;
                default:
                    cout << " - ";
                    break;
                }
                oindex++;
            }
        }
        canswer = solvingPemmdas(equation, 17);

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
int solvingPemmdas(int *equation, int size)
{
    if (size == 1)
    {
        return equation[0];
    }

    // check for multiplication, division, and subtraction
    for (int i = 0; i < size; i++)
    {
        if (equation[i] == 1 || equation[i] == 2 || equation[i] == 3)
        {
            int result = 0;
            switch (equation[i])
            {
            case 1: // %
                result = equation[i - 1] % equation[i + 1];
                break;
            case 2: // /
                result = equation[i - 1] / equation[i + 1];
                break;
            case 3: // *
                result = equation[i - 1] * equation[i + 1];
                break;
            }

            for (int j = i - 1; j < size - 2; j++)
            {
                equation[j] = equation[j + 2];
            }
            equation[i - 1] = result;
            size -= 2;
            return solvingPemmdas(equation, size);
        }
    }

    // check for add or subtract
    for (int i = 0; i < size; i++)
    {
        if (equation[i] == 4 || equation[i] == 5)
        {
            int result = 0;
            switch (equation[i])
            {
            case 4: // +
                result = equation[i - 1] + equation[i + 1];
                break;
            case 5: // -
                result = equation[i - 1] - equation[i + 1];
                break;
            }

            for (int j = i - 1; j < size - 2; j++)
            {
                equation[j] = equation[j + 2];
            }
            equation[i - 1] = result;
            size -= 2;
            return solvingPemmdas(equation, size);
        }
    }
    return equation[0];
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