
#include <iostream>
#include <cmath>
#include <string>
using namespace std;

namespace utils {
    static bool checkIfCinPass() {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Please enter a valid data type" << endl;
            return false;
        }
        return true;
    }
    static bool isNumInRange( short num,  short lowerLimit, unsigned short upperLimit) {
        if (num >= lowerLimit && num <= upperLimit)
        {
            return true;
        }
        cerr << "Please enter number between "
            << to_string(lowerLimit)
            << ":"
            << to_string(upperLimit)
            << endl;
        return false;
    }
    template <typename T> T promptNumBetween( short lowerLimit, unsigned short upperLimit, string promptingText) {
        T arg;
        bool isInvalidInput;
        do
        {
            cout << promptingText << endl;
            cin >> arg;
            if (!checkIfCinPass() || !isNumInRange(arg, lowerLimit, upperLimit)) isInvalidInput = true;
            else isInvalidInput = false;
        } while (isInvalidInput);
        return arg;
    }
    static unsigned short generateRandomNum(unsigned short lowerLimit, unsigned short upperLimit) {
        return rand() % (upperLimit - lowerLimit + 1) + lowerLimit;
    }
}
using namespace utils;

enum class enQuizDifficulty { Easy = 1, Med = 2, Hard = 3, Mix = 4 };
enum class enQuestionDifficulty { Easy = 1, Med = 2, Hard = 3, Mix = 4 };
enum class enQuestionsType { Add = 1, Subtract = 2, Multiply = 3, Divide = 4 };
struct stQuiz
{
    bool hasPassed;
    unsigned short quizResult, numberOfQuestions;
    enQuizDifficulty quizDifficulty;
    enQuestionsType questionsType;
};
struct stQuestion {
    short questionResult;
    enQuestionDifficulty questionDifficulty;
};

static unsigned short  generateQuestionDetail(enQuestionsType questionType, unsigned short const & num1, unsigned short const& num2, unsigned short const& questionNumber) {
        short answer, result;
    switch (questionType)
    {
    case enQuestionsType::Add:
        cout << "Question (" << to_string(questionNumber) << "):\n"
            << to_string(num1) << " + " << to_string(num2) << " ="
            << endl;
        answer = promptNumBetween<unsigned short>(1, 10000, "Enter your answer");
        result = num1 + num2;
        cout << "answer: " << to_string(answer)
            << "\nResult: " << to_string(result) 
            << endl;
        if (answer == result) return 1;
        return 0;
    case enQuestionsType::Subtract:
        cout << "Question (" << to_string(questionNumber) << "):\n"
            << to_string(num1) << " - " << to_string(num2) << " ="
            << endl;
        answer = promptNumBetween<short>(-500, 10000, "Enter your answer");
        result = num1 - num2;
        if (answer == result)
        {
            return 1;
        }
        return 0;
    case enQuestionsType::Multiply:
        cout << "Question (" << to_string(questionNumber) << "):\n"
            << to_string(num1) << " * " << to_string(num2) << " ="
            << endl;
        answer = promptNumBetween<unsigned short>(1, 10000, "Enter your answer");
        result = num1 * num2;
        if (answer == result)
        {
            return 1;
        }
        return 0;
    case enQuestionsType::Divide:
        cout << "Question (" << to_string(questionNumber) << "):\n"
            << to_string(num1) << " / " << to_string(num2) << " ="
            << endl;
        answer = promptNumBetween<unsigned short>(1, 10000, "Enter your answer");
        result = num1 / num2;
        if (answer == result)
        {
            return 1;
        }
        return 0;
    }
}
static pair<unsigned short, unsigned short> generateNumbersBasedOnType(enQuestionDifficulty questionDiff) {
    unsigned short num1, num2;
    switch (questionDiff)
    {
    case enQuestionDifficulty::Easy:
        num1 = generateRandomNum(1, 10);
        num2 = generateRandomNum(1, 10);
        break;
    case enQuestionDifficulty::Med:
        num1 = generateRandomNum(10, 50);
        num2 = generateRandomNum(10, 50);

        break;
    case enQuestionDifficulty::Hard:
        num1 = generateRandomNum(50, 100);
        num2 = generateRandomNum(50, 100);
        break;
    default:
        break;
    }
    return make_pair(num1, num2);
}
static unsigned short generateQuestion(unsigned short const &questionNumber, enQuestionDifficulty questionDifficulty, enQuestionsType questionType) {
    unsigned short result = 0;
    pair<unsigned short, unsigned short> numbers;
    if (questionDifficulty == enQuestionDifficulty::Mix)
    {
        questionType = static_cast<enQuestionsType>(generateRandomNum(1, 4));
        questionDifficulty = static_cast<enQuestionDifficulty>(generateRandomNum(1, 3));
        numbers = generateNumbersBasedOnType(questionDifficulty);
        result += generateQuestionDetail(questionType, numbers.first, numbers.second, questionNumber + 1);
    }
    else {
        numbers = generateNumbersBasedOnType(questionDifficulty);
        result += generateQuestionDetail(questionType,numbers.first,numbers.second, questionNumber +1);
    }
    cout << "Result for this question in generateQuestion function: " << to_string(result)<<endl;
    return result;
}
static unsigned short generateQuiz(enQuizDifficulty quizDiff, enQuestionsType questionsType, unsigned short const & numOfQuestions) {
    enQuestionDifficulty questionDiff;
    unsigned short totalResult=0;
    switch (quizDiff)
    {
    case enQuizDifficulty::Easy:
        questionDiff = enQuestionDifficulty::Easy;
        for (size_t i = 0; i < numOfQuestions; i++)
        {
            totalResult+= generateQuestion(i,questionDiff,questionsType);
        }
        break;
    case enQuizDifficulty::Med:
        questionDiff = enQuestionDifficulty::Med;
        for (size_t i = 0; i < numOfQuestions; i++)
        {
            totalResult+= generateQuestion(i,questionDiff,questionsType);
        }
        break;
    case enQuizDifficulty::Hard:
        questionDiff = enQuestionDifficulty::Hard;
        for (size_t i = 0; i < numOfQuestions; i++)
        {
            totalResult+= generateQuestion(i,questionDiff,questionsType);
        }
        break;
    case enQuizDifficulty::Mix:
        for (size_t i = 0; i < numOfQuestions; i++)
        {
            questionDiff = static_cast<enQuestionDifficulty> (generateRandomNum(1, 4));
            totalResult+= generateQuestion(i,questionDiff,questionsType);
        }
        break;
    }
        return totalResult;
}
static void generateMathExam() {
    srand(time(0));
    stQuestion question;
    stQuiz quiz;
    string msg;
    //ask for the number of questions
    quiz.numberOfQuestions = promptNumBetween<unsigned short>(1, 10, "Number of questions from 1-10");
    //ask for the quiz difficulty (easy, med, hard, mix)
    quiz.quizDifficulty = static_cast<enQuizDifficulty>(promptNumBetween<unsigned short>(1, 4, "Quiz Difficulty:\n1) Ease\n2) Med\n3) Hard\n4) Mix"));
    //ask for the question Type (Add, Substract, Multiply, Divide)
    quiz.questionsType = static_cast<enQuestionsType>(promptNumBetween<unsigned short>(1, 4, "Questions Type:\n1) Add\n2) Substract\n3) Multiply\n4) Divide"));
    quiz.quizResult= generateQuiz(quiz.quizDifficulty,quiz.questionsType,quiz.numberOfQuestions);
    quiz.hasPassed = ((float)quiz.quizResult / quiz.numberOfQuestions) > 0.5;
    if (quiz.hasPassed) msg = "Passed";
    else msg = "Failed";
    //print result
    cout << "You have solved " << to_string(quiz.quizResult) << "/"
    << to_string(quiz.numberOfQuestions)<<"\nYou have " << msg<< "!" << endl;

}

    int main()
    {
        //generateMathExam
        generateMathExam();
    }
