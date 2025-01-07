#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;
enum enQuestionLevel {Easy = 1, Med = 2, Hard = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4 , mix = 5 };
struct stQuestion
{
int number1;
int number2;
enOperationType OpType;
enQuestionLevel Qlevel;
int UserAnswer;
int CorrectAnswer;
bool ResultAnswer ;
};
struct stQuizz
{
	stQuestion QuestionsList[100];
	int NumberOfQuestions;
	enQuestionLevel QuestionLevel;
	enOperationType OperationType;
	int NumberOfRightQuestions = 0;
	int NumberOfWrongQuestions = 0;
	bool IsPass = false;
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
enQuestionLevel GetQuestionLevel()
{
	return (enQuestionLevel)GetRandomNumbers(1, 3);
}
enOperationType GetOperationType()
{

	return (enOperationType)GetRandomNumbers(1, 3);

}
int GetNumber(enQuestionLevel Qlevel)
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
int SimpleCalculate(int num1, int num2, enOperationType Otype)
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
stQuestion GenerateQuestion(enOperationType OpType, enQuestionLevel Qlevel)
{
	stQuestion Question;


	if(Qlevel == enQuestionLevel::Mix)
	{
		Qlevel = GetQuestionLevel();
	}
	Question.Qlevel = Qlevel;


	if(OpType == enOperationType::mix )
	{
		OpType = GetOperationType();
	}
	Question.OpType = OpType;


	Question.number1 = GetNumber(Question.Qlevel);
	Question.number2 = GetNumber(Question.Qlevel);
	
	Question.CorrectAnswer = SimpleCalculate(Question.number1, Question.number2,Question.OpType);

	return Question;
}
void GenarateQuizQuestions(stQuizz &Quizz)
{
	for(int s = 0; s < Quizz.NumberOfQuestions ; s++)
	{
		Quizz.QuestionsList[s] = GenerateQuestion(Quizz.OperationType,Quizz.QuestionLevel );
	}
}
void PrintOperation(stQuizz Quizz , int QuestionNumber)
{
	cout << endl;
	cout << "\nQuestion [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n";
	cout << Quizz.QuestionsList[QuestionNumber].number1 << "\n";
	cout << Quizz.QuestionsList[QuestionNumber].number2 << " " << PrintOperationTypeText(Quizz.QuestionsList[QuestionNumber].OpType);
	cout << "\n-------------\n";
}
void SetScreenColor(bool right)
{
	if (right)
		system("color 2F");
	else
		system("color 4F");
}
void CorrectTheQuestionAnswer(stQuizz &Quizz,int QuestionNumber)
{
	if ((Quizz.QuestionsList[QuestionNumber].UserAnswer == Quizz.QuestionsList[QuestionNumber].CorrectAnswer))
	{
		Quizz.QuestionsList[QuestionNumber].ResultAnswer = true;
		cout << "Right Answer :-) \n";
		Quizz.NumberOfRightQuestions++;

	}
	else
	{
		Quizz.QuestionsList[QuestionNumber].ResultAnswer = false;
		cout << "Wrong Answer :-( \n";
		cout << "Right Answer is " << Quizz.QuestionsList[QuestionNumber].CorrectAnswer << endl;
		Quizz.NumberOfWrongQuestions++;
	}

		SetScreenColor(Quizz.QuestionsList[QuestionNumber].ResultAnswer);
}
int ReadQuestionAnswer()
{
	int answer;
	cin >> answer;
	return answer;
}
void AskAndCorrectQuestionsListAnswers(stQuizz &Quizz)
{
	
	for(int QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions ; QuestionNumber++)
	{
		PrintOperation(Quizz,QuestionNumber);
		Quizz.QuestionsList[QuestionNumber].UserAnswer = ReadQuestionAnswer();
		CorrectTheQuestionAnswer(Quizz,QuestionNumber);
	
	}

	Quizz.IsPass = (Quizz.NumberOfRightQuestions >= Quizz.NumberOfWrongQuestions);

}
string CheckFinalResults(stQuizz Quizz)
{
	if (Quizz.IsPass)
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
	cout << "Number Of Question     : " << Quizz.NumberOfQuestions << "\n";
	cout << "Question Level         : " << PrintQuestionLevelText(Quizz.QuestionLevel) <<"\n";
	cout << "Operation Type         : " << PrintOperationTypeText(Quizz.OperationType) << "\n";
	cout << "Number Of Right Answer : " << Quizz.NumberOfRightQuestions << "\n";
	cout << "Number Of Wrong Answer : " << Quizz.NumberOfWrongQuestions << endl;
	cout << "_______________________________________\n";
}
void PlayMathGame()
{
	stQuizz Quizz;
	Quizz.NumberOfQuestions  = HowManyQuestions();
	Quizz.QuestionLevel = ReadQuestionLevel();
	Quizz.OperationType = ReadOperationType();
	
	GenarateQuizQuestions(Quizz);
	AskAndCorrectQuestionsListAnswers(Quizz);
	
	PrintFinalResults(Quizz);
	


}
void ResetScreen()
{
	system("cls");
	system("color 0F");
}
void StartGame()
{
	char PlayAgain = 'y';
	do
	{
		ResetScreen();
		PlayMathGame();
		

		cout << "do you want play again y/n ";
		cin >> PlayAgain;

	} while (PlayAgain == 'y' || PlayAgain == 'Y');
}
int main()
{
	srand((unsigned)time(NULL));
	
	StartGame();
	return 0;
}