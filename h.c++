#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;
enum enQuestionLevel {Easy = 1, Med = 2, Hard = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4 , mix = 5 };
struct stQuizz
{
	int NumberOfQuestion;
	enQuestionLevel QuestionLevel;
	enOperationType OperationType;
	int NumberOfRightQuestions;
	int NumberOfWrongQuestions;
};
int GetRandomNumbers(int from, int to)
{
	return rand() % (to - from + 1) + from;
}
int HowManyQuestions()
{
	int NumOfQuestions = 0;
	cout << "how many questions do you want to answer ?  ";
	cin >> NumOfQuestions;
	return NumOfQuestions;
}
enQuestionLevel ReadQuestionLevel()
{
	int QuestionLev = 0;
    do
	{
        cout << "enter question level : [1] Easy ,[2] Med ,[3] Hard ,[4] Mix ? ";
	    cin >> QuestionLev;
    }while(QuestionLev < 1 || QuestionLev > 4);
	return (enQuestionLevel)QuestionLev;
}
enOperationType ReadOperationType()
{
	int OperationType = 0;
    do
    {
 	    cout << " enter operation type : [1] Add ,[2] Sub ,[3] Mult ,[4] Div ,[5] Mix ? ";
	    cin >> OperationType;       
    } while (OperationType < 1 || OperationType > 5);
    
	return (enOperationType)OperationType;
}
string PrintQuestionLevelText(enQuestionLevel Qlevel)
{
	string level[4] = { "Easy" ,"Med" ,"Hard" ,"Mix" };
	return level[(int)Qlevel - 1];
}
string PrintOperationTypeText(enOperationType OperationType)
{
	string type[5] = { "+" , "-" , "*" , "/"  , "Mix" };
	return type[(int)OperationType - 1];
}
enQuestionLevel GetQuestionLevelMix(enQuestionLevel Qlevel)
{
	if (enQuestionLevel::Mix == Qlevel)
	{
		return (enQuestionLevel)GetRandomNumbers(1, 3);
	}
	return Qlevel;
}
enOperationType GetOperationTypeMix(enOperationType Otype)
{
	if (enOperationType::mix == Otype)
	{
		return (enOperationType)GetRandomNumbers(1, 3);
	}
	return Otype;
}
int ReadNumber(enQuestionLevel Qlevel)
{
	switch (Qlevel)
	{
	case enQuestionLevel::Easy:
		return GetRandomNumbers(1, 10);
		break;
	case enQuestionLevel::Med:
		return GetRandomNumbers(10, 50);
		break;
	case enQuestionLevel::Hard:
		return GetRandomNumbers(50, 100);
		break;
	}
}
int CalculateOperation(int num1, int num2, enOperationType Otype)
{
	switch (Otype)
	{
	case enOperationType::Add:
		return num1 + num2;
		break;
	case enOperationType::Sub:
		return num1 - num2;
		break;
	case enOperationType::Mult:
		return num1 * num2;
		break;
	case enOperationType::Div:
		return num1 / num2;
		break;
	}
}
void PrintOperation(int num1, int num2,enOperationType Otype,int &result)
{
	cout << endl;
	cout << num1 << "\n";
	cout << num2 << " " << PrintOperationTypeText(Otype);
	cout << "\n-------------\n";
	cin >> result;
}
bool CheckAnswer(int RightAnswer, int result)
{
	return result == RightAnswer;
}
void PrintResult(int RightAnswer,bool ChAnswer)
{
	if (ChAnswer)
	{
		cout << "Right Answer :-) \n";
	}
	else
	{
		cout << "Wrong Answer :-( \n";
		cout << "Right Answer is " << RightAnswer << endl;
	}
}
void ScreenColor(bool ResultAnswer)
{
	if (ResultAnswer)
		system("color 2F");
	else
		system("color 4F");
}
string CheckFinalResults(stQuizz Quizz)
{
	if (Quizz.NumberOfRightQuestions >= Quizz.NumberOfWrongQuestions)
		return "Pass :-)";
	else
		return "Fail :-(";
}
void PrintShowHeader(stQuizz Quizz)
{
	cout << "\n_________________________________\n\n";
	cout << "Final results is " << CheckFinalResults(Quizz);
	cout << "\n__________________________________\n\n";

}
void PrintFinalResults(stQuizz Quizz)
{
	PrintShowHeader(Quizz);
	cout << "Number Of Question     : " << Quizz.NumberOfQuestion << "\n";
	cout << "Question Level         : " << PrintQuestionLevelText(Quizz.QuestionLevel) <<"\n";
	cout << "Operation Type         : " << PrintOperationTypeText(Quizz.OperationType) << "\n";
	cout << "Number Of Right Answer : " << Quizz.NumberOfRightQuestions << "\n";
	cout << "Number Of Wrong Answer : " << Quizz.NumberOfWrongQuestions << endl;
	cout << "_______________________________________\n";
}
void StartGame(stQuizz &Quizz)
{
	int Result;
	int num1, num2;
	
	int right = 0, wrong = 0;
	Quizz.NumberOfQuestion  = HowManyQuestions();
	Quizz.QuestionLevel = ReadQuestionLevel();
	Quizz.OperationType = ReadOperationType();
	cout << endl;
	for (int i = 1; i <= Quizz.NumberOfQuestion;i++)
	{
		cout << "\nQuestion [" << i << "/" << Quizz.NumberOfQuestion << "]\n";
		enQuestionLevel QL = GetQuestionLevelMix(Quizz.QuestionLevel);
		num1 = ReadNumber(QL);
		num2 = ReadNumber(QL);

		enOperationType OT = GetOperationTypeMix(Quizz.OperationType);
		PrintOperation(num1, num2,OT, Result);

		int RightAnswer = CalculateOperation(num1, num2, OT);
		bool result = CheckAnswer(RightAnswer, Result);
		PrintResult(RightAnswer,result);
		ScreenColor(result);
		if (result)
			right++;
		else
			wrong++;

	}
	Quizz.NumberOfRightQuestions = right;
	Quizz.NumberOfWrongQuestions = wrong;
}
void ResetScreen()
{
	system("cls");
	system("color 0F");
}
void PlayGame()
{
	stQuizz Quizz;
	char PlayAgain = 'y';
	do
	{
		ResetScreen();

		StartGame(Quizz);
		PrintFinalResults(Quizz);

		cout << "do you want play again y/n ";
		cin >> PlayAgain;

	} while (PlayAgain == 'y' || PlayAgain == 'Y');
}
int main()
{
	srand((unsigned)time(NULL));
	
	PlayGame();
	return 0;
}