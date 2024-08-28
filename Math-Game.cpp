#include <iostream>
#include <time.h>
using namespace std;

enum enDeficultLevels { Easy = 1, Med = 2, Hard = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, Mixi = 5 };

struct stQustion
{
	int Number1 = 0;
	int Number2 = 0;
	enDeficultLevels Level;
	enOperationType OpType;
	int RightAnswer = 0;
	int PlayerAnswer = 0;
	bool MatchAnswers = 0;

};

struct stQuizz
{
	stQustion QuestionList[100];
	short QuestionsNumber = 1;
	enDeficultLevels Level;
	enOperationType OpType;
	short NumsOfRightAnswers = 0;
	short NumsOfWrongAnswers = 0;
	bool Pass = 0;
};

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

short ReadHowManyQuestion()
{
	short Num = 1;

	do
	{
		cout << "How many question do you want to answer ?";
		cin >> Num;
	}

	while (Num < 1 || Num>10);

	return Num;
}

enDeficultLevels ReadQuestionLevel()
{
	short Lev = 1;

	do
	{
		cout << "What Level do you want to be ? [1] Easy, [2] Medium, [3] Hard, [4] Mix : ";
		cin >> Lev;
	}

	while (Lev < 1 || Lev>4);

	return enDeficultLevels(Lev);

}

enOperationType ReadOpType()
{
	short Op = 1;

	do
	{
		cout << "What operate type do you want to take ? [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix : ";
		cin >> Op;
	}

	while (Op < 1 || Op>5);

	return enOperationType(Op);
}

int RandomNumber(int From, int To)
{
	int randNum = rand() % (To - From + 1) + From;

	return randNum;
}

int GetNumberOfQuestion(enDeficultLevels Level)
{
	switch (Level)
	{
	case enDeficultLevels::Easy:
		return RandomNumber(1, 10);
		break;

	case enDeficultLevels::Med:
		return RandomNumber(10, 50);
		break;

	case enDeficultLevels::Hard:
		return RandomNumber(50, 100);
		break;

	case enDeficultLevels::Mix:
		return RandomNumber(1, 100);
		break;
	}
}

int SimpleCalculater(int Number1, int Number2, enOperationType& Op)
{
	if (Op == enOperationType::Mixi)
		Op = enOperationType(RandomNumber(1, 4));

	switch (Op)
	{
	case enOperationType::Add:
		return Number1 + Number2;
		break;

	case enOperationType::Sub:
		return Number1 - Number2;
		break;

	case enOperationType::Mul:
		return Number1 * Number2;
		break;

	case enOperationType::Div:
		return Number1 / Number2;
		break;


	}
}

stQustion GenerateAQuestion(stQuizz& Quizz)
{
	stQustion Question;

	Question.Level = Quizz.Level;
	Question.OpType = Quizz.OpType;

	Question.Number1 = GetNumberOfQuestion(Quizz.Level);
	Question.Number2 = GetNumberOfQuestion(Quizz.Level);

	Question.RightAnswer = SimpleCalculater(Question.Number1, Question.Number2, Question.OpType);

	return Question;
}

stQuizz GenerateQuestionsList(stQuizz& Quizz)
{
	for (short QuestionOrder = 0; QuestionOrder < Quizz.QuestionsNumber; QuestionOrder++)
	{
		Quizz.QuestionList[QuestionOrder] = GenerateAQuestion(Quizz);

	}

	return Quizz;
}

string GetOpText(enOperationType Op)
{
	string OpText[5] = { "+",  "-",  "*",  "/",  "Mix" };

	return OpText[Op - 1];
}

void CorrectAnswer(bool Match, int RightAnswer)
{
	if (Match)
	{
		cout << "Right Answer :-)";
		system("color 2F");

	}
	else
	{
		cout << "Wrong Answer :-(";
		system("color 4F");
		cout << "\a";
		cout << "\nThe right answer is : " << RightAnswer;
	}
	cout << endl;
}

void PrintQuestion(stQuizz& Quizz, short QuestionOrder)
{
	cout << "\nQuestion  [" << QuestionOrder + 1 << "/" << Quizz.QuestionsNumber << "]\n\n";
	cout << Quizz.QuestionList[QuestionOrder].Number1 << endl;
	cout << Quizz.QuestionList[QuestionOrder].Number2 << " " << GetOpText(Quizz.QuestionList[QuestionOrder].OpType) << endl;
	cout << "-------------\n";
	cin >> Quizz.QuestionList[QuestionOrder].PlayerAnswer;

	Quizz.QuestionList[QuestionOrder].MatchAnswers = (Quizz.QuestionList[QuestionOrder].RightAnswer == Quizz.QuestionList[QuestionOrder].PlayerAnswer);
	CorrectAnswer(Quizz.QuestionList[QuestionOrder].MatchAnswers, Quizz.QuestionList[QuestionOrder].RightAnswer);

	if (Quizz.QuestionList[QuestionOrder].MatchAnswers)

		Quizz.NumsOfRightAnswers++;
	else
		Quizz.NumsOfWrongAnswers++;




}

void AskAndCorrectPlayerAnswer(stQuizz& Quizz)
{
	for (short QuestionOrder = 0; QuestionOrder < Quizz.QuestionsNumber; QuestionOrder++)
	{
		PrintQuestion(Quizz, QuestionOrder);
	}

	Quizz.Pass = (Quizz.NumsOfRightAnswers >= Quizz.NumsOfWrongAnswers);
}

string QuizzResult(bool Pass)
{
	if (Pass)
		return "Pass :-)";

	else return "Fail :-(";
}

string GetLevelText(enDeficultLevels Level)
{
	string LevelText[4] = { "Easy",  "Medium",  "Hard",  "Mix" };

	return LevelText[Level - 1];
}

void printFinalResult(stQuizz Quizz)
{
	cout << "\n-----------------------------------\n";
	cout << "Final result is " << QuizzResult(Quizz.Pass) << endl;
	cout << "-----------------------------------\n";
	cout << "Number of questions    : " << Quizz.QuestionsNumber << endl;
	cout << "Question Level         : " << GetLevelText(Quizz.Level) << endl;
	cout << "Operation Type         : " << GetOpText(Quizz.OpType) << endl;
	cout << "Number of right answer : " << Quizz.NumsOfRightAnswers << endl;
	cout << "Number of Wrong answer : " << Quizz.NumsOfWrongAnswers << endl;
	cout << "-----------------------------------\n";
}

void PlayGame()
{
	stQuizz Quizz;

	Quizz.QuestionsNumber = ReadHowManyQuestion();
	Quizz.Level = ReadQuestionLevel();
	Quizz.OpType = ReadOpType();

	GenerateQuestionsList(Quizz);
	AskAndCorrectPlayerAnswer(Quizz);
	printFinalResult(Quizz);
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		PlayGame();

		cout << "Do you want to play again ? Y/N? ";
		cin >> PlayAgain;

	}

	while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}
