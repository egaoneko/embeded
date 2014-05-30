#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
int Operation(char Buho);
char Medi_Back(char *Medium, char *Back);
char Account(char *Back, double *Cost);
void main()
{
	char Array[256];
	char Ch_Back[256];
	double Cost[100];

	printf(" 입력 :");
	scanf("%s", Array);
	Medi_Back(Array, Ch_Back);
	Account(Ch_Back, Cost);

	printf("답은 : %0.1f\n", Cost[0]);
	printf(" 아무키나 누르세요.\n");
	getch();
}

int Operation(char Buho){   // 연산자 우선 순위를 정하는 함수이다

	switch (Buho){
	case '(':
		return 0;
	case '+':
		return 1;
	case '-':
		return 1;
	case '*':
		return 2;
	case '/':
		return 2;
	}
}
char Medi_Back(char *Medium, char *Back){
	int B_Top = -1, S_Top = -1;  // B_Top 는 후위식 스택의 주소 변수 S_Top 는 Ch_Stack 변수
	int i, langth;   // i 는 중위식의 주소 변수

	char *Ch_Stack;   // 연산자를 임시로 저장하는 스택
	Ch_Stack = (char *)malloc(sizeof(char)* 100);
	langth = strlen(Medium); // 중위식 스택의 길이를 알아내야 순환문 반복횟수를 정할수 있따
	for (i = 0; i <= langth + 1; i++){
		if (Medium[i] >= '0' && Medium[i] <= '9'){ // 숫자면 Back 배열에 그냥 바로 넣자
			B_Top++;
			Back[B_Top] = Medium[i];
		}
		else {   // 아니라면 시작하자 마자 Back 에 공백을 넣고 시작한다
			B_Top++;
			Back[B_Top] = ' ';
			if (S_Top == -1 || Medium[i] == '('){  // 연산자 스택이 비어있거나 '(' 나오면 그냥 바로 넣는다
				S_Top++;
				Ch_Stack[S_Top] = Medium[i];
			}
			else {       // + - * / ) 연산자가 나올시
				if (Operation(Medium[i]) <= Operation(Ch_Stack[S_Top])){ // + - * / 연산자 우선순위를 가려서
					B_Top++;    // 스택 마지막에 들어있는 연산자가 크다면 스택에 있는걸 빼서
					Back[B_Top] = Ch_Stack[S_Top]; // Back 배열에 넣는다
					B_Top++;     // 연산자와 연산자 혹은 숫자랑 구분하기 위해 공백 넣자
					Back[B_Top] = ' ';
					Ch_Stack[S_Top] = Medium[i];
				}
				else {     // 아니라면 그냥 스택에 넣자
					if (Medium[i] != ')'){ // ')' 을 제외한 연산자를 스택에 넣는다
						S_Top++;
						Ch_Stack[S_Top] = Medium[i];
					}
				}
				if (Medium[i] == ')'){       // ')' 를 만난다면 '(' 여기 전까지 들어있는 연산자를
					for (; Ch_Stack[S_Top] != '('; S_Top--){ // 모두 끄집어 내서 Back 넣는다
						B_Top++;
						Back[B_Top] = Ch_Stack[S_Top];
					}
					S_Top--;    // 감소를 시켜죠야 '(' 괄호가 back 에 안들어간다 팝해서 버린다고 생각하자
				}
				if (Medium[i] == '\0'){  // 중위식 마지막 널을 만난다면 스택에 있던 모든 연산자를
					for (; S_Top>-1; S_Top--){ // back 뒤에 붙여 넣는다
						B_Top++;
						Back[B_Top] = Ch_Stack[S_Top];
					}
				}
			}
		}
	}
	free(Ch_Stack);
	return *Back;
}
char Account(char *Back, double *Cost){

	int langth;
	int C_Top = -1;  // Cost 배열의 주소로 사용할 변수
	int i, address = 0; // address 는 숫자를 변환 시키고 그 주소의 포커스를 다음 숫자 포커스로 이동시키기 위해서
	langth = strlen(Back);
	while (1){
		for (i = address; i <= langth; i++){  // address 로 i 를 계속 갱신해주어야 한다 address 는 포커스를 이동시켜주기 
			if (Back[i] == ' '){    // 때문이다
				i++;      // 공백 다음 번지로 가기 위해서 증가 시켜주고
				address = i;     // 이걸 address 에 넣고 
				break;      // 지금 for 순환을 멈추고 다시 시작한다
			}
			if (Back[i] >= '0' && Back[i] <= '9'){  // 숫자면 
				C_Top++;
				Cost[C_Top] = atof(&Back[i]);  // 문자형 숫자를 double 로 변환해서 스택에 넣어준다
				while (Back[i] != ' '){   // 그리고 포커스를 다음의 연산자 혹은 숫자 전에 있는 공백으로 간다
					i++;
					address = i;
				}
				break;
			}
			if (Back[i] == '+'){     // + 연산자를 만나면
				Cost[C_Top - 1] = Cost[C_Top - 1] + Cost[C_Top]; // 스택에 있는 바로전것과 새로들어간것을 더해준다
				C_Top--;         // 그리고 스택 주소를 한칸 밑으로 해야 다시 새로운
				i++;          // 숫자가 들어간다
				address = i;
				break;
			}
			if (Back[i] == '-'){     // 나머지 부분도 똑같다
				Cost[C_Top - 1] = Cost[C_Top - 1] - Cost[C_Top];
				C_Top--;
				i++;
				address = i;
				break;
			}
			if (Back[i] == '*'){
				Cost[C_Top - 1] = Cost[C_Top - 1] * Cost[C_Top];
				C_Top--;
				i++;
				address = i;
				break;
			}
			if (Back[i] == '/'){
				Cost[C_Top - 1] = Cost[C_Top - 1] / Cost[C_Top];
				C_Top--;
				i++;
				address = i;
				break;
			}
		}
		if (Back[i] == '\0') break;
	}
	return *Cost;
}