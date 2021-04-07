/*
 * postfix.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixpush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
	char command;
	printf("[----- [김태인] [2018038033] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x; //탑스택을 1만큼 늘리고 스택안에 x를 저장 
}

char postfixPop()
{
    char x;
    if(postfixStackTop == -1) //탑스택이 -1일겅우 스택이 비어있으므로 \0을 반환
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--]; //가장 나중에 들어온 탑스택 부분의 스택을 지운다
    }
    return x;
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x; //탑스택을 1만큼 늘리고 스택안에 x를 저장 
}

int evalPop()
{
    if(evalStackTop == -1)  //탑스택이 -1일겅우 스택이 비어있으므로 -1을 반환
        return -1;
    else
        return evalStack[evalStackTop--]; //탑스택의 부분을 반환하고 탑스택을 -1함으로서 지운다.
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp); 
}

precedence getToken(char symbol)
{
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}

precedence getPriority(char x)
{
	return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */
	int i = 0;
	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0')
	{
		x = *exp;
		
		if('0'<= x && x<= '9')
		{
			postfixExp[i++] = x;
		}	
		switch (getToken(x))
		{
			case times:
			case divide:
			case plus:
			case minus:
				postfixPush(x);
				i--;
			case lparen:
			case rparen:
				*exp = postfixPop();
				i++;
				break; 
		}
		exp++;
	}
	do {
		postfixExp[i++] = postfixPop();
	} while(postfixExp[i - 1] != '\0');
	/* 필요한 로직 완성 */


}
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()
{
	/* postfixExp, evalStack을 이용한 계산 */
	int i, exp1, exp2, value;
	char x;

	for(i = 0; postfixExp[i] != '\0'; i++)
	{
		x = postfixExp[i];
		if(x != '*' && x != '/' && x != '+' && x != '-')
		{
			value = x - '0';
			evalPush(value);
		}
		else
		{
			exp1 = evalPop();
			exp2 = evalPop();
			switch(getToken(x))
			{
				case times:
					evalPush(exp1 * exp2);
					break;
				case divide:
					evalPush(exp1 / exp2);
					break;
				case plus:
					evalPush(exp1 + exp2);
					break;
				case minus:
					evalPush(exp1 - exp2);
					break;
			}
		}
	}
	evalResult = evalPop();
}


