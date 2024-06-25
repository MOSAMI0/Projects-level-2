#include<iostream>
#include<cstdlib>

using namespace std;

enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

string GetOpTypeSymbol(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mult:
		return "*";
	case enOperationType::Div:
		return "/";
	default:
		return "Mix";
	}
}

string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
{
	string arrQuestionLevelText[4] = { "Easy", "Med", "Hard", "Mix" };
	return arrQuestionLevelText[QuestionLevel - 1];

}

int RandomNumber(int From, int To)
{
	//Function to generate a random number
	int randNum = rand() % (To - From + 1) + From;
	return randNum;
}

void SetScreenColor(bool Right)
{
	if (Right)
		system("color 2F");
	else
	{
		system("color 4F");
		cout << "\a";
	}
}

short ReadHowManyQuestions()
{
	short NumberOfQuestions;

	do
	{
		cout << "How Many Questions do you want to answer ? \n";
		cin >> NumberOfQuestions;

	} while (NumberOfQuestions < 1 || NumberOfQuestions >10);

	return NumberOfQuestions;
}

enQuestionsLevel ReadQuestionLevel()
{
	short QuestionLevel = 0;

	do
	{
		cout << "Enter Question Level [1] Easy, [2] Med, [3] Hard, [4] Mix? ";
		cin >> QuestionLevel;

	} while (QuestionLevel < 1 || QuestionLevel >4);

	return (enQuestionsLevel)QuestionLevel;
}

enOperationType ReadOpType()
{
	short OpType = 0;

	do
	{
		cout << "Enter Question Level [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
		cin >> OpType;

	} while (OpType < 1 || OpType >5);

	return (enOperationType)OpType;
}

struct stQuestion
{
	int Number1 = 0;
	int Number2 = 0;
	enOperationType OperationType;
	enQuestionsLevel QuestionsLevel;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};

struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestions;
	enQuestionsLevel QuestionsLevel;
	enOperationType OpType;
	short NumberOfWrongAnswer = 0;
	short NumberOfRightAnswer = 0;
	bool isPass = false;
};

int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case enOperationType::Mult:
		return Number1 * Number2;
	case enOperationType::Div:
		return Number1 / Number2;
	default:
		return Number1 + Number2;
	}
}

enOperationType GetRandomOperationType()
{
	int Op = RandomNumber(1, 4);
	return (enOperationType)Op;
}

stQuestion GenerateQuestion(enQuestionsLevel QuestionsLevel, enOperationType OperationType)
{
	stQuestion Question;

	if (QuestionsLevel == enQuestionsLevel::Mix)
	{
		QuestionsLevel = (enQuestionsLevel)RandomNumber(1, 3);
	}

	if (OperationType == enOperationType::MixOp)
	{
		OperationType = GetRandomOperationType();
	}

	Question.OperationType = OperationType;

	switch (QuestionsLevel)
	{
	case enQuestionsLevel::EasyLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);

		Question.QuestionsLevel = QuestionsLevel;

		return Question;

	case enQuestionsLevel::MedLevel:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);

		Question.QuestionsLevel = QuestionsLevel;

		return Question;

	case enQuestionsLevel::HardLevel:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);

		Question.QuestionsLevel = QuestionsLevel;

		return Question;
	}
	return Question;
}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
	{
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
	}
}

int ReadQuestionAnswer()
{
	int Answer = 0;
	cin >> Answer;
	return Answer;
}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
	cout << '\n';
	cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "] \n\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
	cout << "\n__________" << endl;

}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswer++;

		cout << "Wrong Answer :-( \n";
		cout << "The Right Answer is: " << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
		cout << endl;
	}

	else
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOfRightAnswer++;

		cout << "Right Answer :-) \n";
	}
	cout << endl;

	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionList(stQuizz& Quizz)
{
	for (short QuestionsNumber = 0; QuestionsNumber < Quizz.NumberOfQuestions; QuestionsNumber++)
	{
		PrintTheQuestion(Quizz, QuestionsNumber);

		Quizz.QuestionList[QuestionsNumber].PlayerAnswer = ReadQuestionAnswer();

		CorrectTheQuestionAnswer(Quizz, QuestionsNumber);
	}

	Quizz.isPass = (Quizz.NumberOfRightAnswer >= Quizz.NumberOfWrongAnswer);

	/* 👆
	if (Quizz.NumberOfRightAnswer >= Quizz.NumberOfWrongAnswer)
		Quizz.isPass = true;
	else
		Quizz.isPass = false;
	*/
}

string GetFinalResultsText(bool Pass)
{
	if (Pass)
		return "Pass :-)";
	else
		return "Fail :-(";
}

void PrintQuizzResults(stQuizz Quizz)
{
	cout << "\n";
	cout << "______________________________\n\n";
	cout << " Final Results are " << GetFinalResultsText(Quizz.isPass);
	cout << "\n______________________________\n\n";
	cout << "Number of Questions	: " << Quizz.NumberOfQuestions << endl;
	cout << "Question Level	        : " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
	cout << "Operation Type          : " << GetOpTypeSymbol(Quizz.OpType) << endl;
	cout << "Number of Right Answers : " << Quizz.NumberOfRightAnswer << endl;
	cout << "Number of Wrong Answers : " << Quizz.NumberOfWrongAnswer << endl;
	cout << "______________________________\n";
}

void PlayMathGame()
{
	stQuizz Quizz;

	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.QuestionsLevel = ReadQuestionLevel();
	Quizz.OpType = ReadOpType();

	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionList(Quizz);
	PrintQuizzResults(Quizz);
}

void ResetScreen()
{
	system("cls");
	system("color 0F");

}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		PlayMathGame();

		cout << endl << "Do you want to play again? Y/N? ";
		cin >> PlayAgain;


	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	// Seeds the random number grnerator in C++, called only once 
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}
