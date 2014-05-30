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

	printf(" �Է� :");
	scanf("%s", Array);
	Medi_Back(Array, Ch_Back);
	Account(Ch_Back, Cost);

	printf("���� : %0.1f\n", Cost[0]);
	printf(" �ƹ�Ű�� ��������.\n");
	getch();
}

int Operation(char Buho){   // ������ �켱 ������ ���ϴ� �Լ��̴�

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
	int B_Top = -1, S_Top = -1;  // B_Top �� ������ ������ �ּ� ���� S_Top �� Ch_Stack ����
	int i, langth;   // i �� �������� �ּ� ����

	char *Ch_Stack;   // �����ڸ� �ӽ÷� �����ϴ� ����
	Ch_Stack = (char *)malloc(sizeof(char)* 100);
	langth = strlen(Medium); // ������ ������ ���̸� �˾Ƴ��� ��ȯ�� �ݺ�Ƚ���� ���Ҽ� �ֵ�
	for (i = 0; i <= langth + 1; i++){
		if (Medium[i] >= '0' && Medium[i] <= '9'){ // ���ڸ� Back �迭�� �׳� �ٷ� ����
			B_Top++;
			Back[B_Top] = Medium[i];
		}
		else {   // �ƴ϶�� �������� ���� Back �� ������ �ְ� �����Ѵ�
			B_Top++;
			Back[B_Top] = ' ';
			if (S_Top == -1 || Medium[i] == '('){  // ������ ������ ����ְų� '(' ������ �׳� �ٷ� �ִ´�
				S_Top++;
				Ch_Stack[S_Top] = Medium[i];
			}
			else {       // + - * / ) �����ڰ� ���ý�
				if (Operation(Medium[i]) <= Operation(Ch_Stack[S_Top])){ // + - * / ������ �켱������ ������
					B_Top++;    // ���� �������� ����ִ� �����ڰ� ũ�ٸ� ���ÿ� �ִ°� ����
					Back[B_Top] = Ch_Stack[S_Top]; // Back �迭�� �ִ´�
					B_Top++;     // �����ڿ� ������ Ȥ�� ���ڶ� �����ϱ� ���� ���� ����
					Back[B_Top] = ' ';
					Ch_Stack[S_Top] = Medium[i];
				}
				else {     // �ƴ϶�� �׳� ���ÿ� ����
					if (Medium[i] != ')'){ // ')' �� ������ �����ڸ� ���ÿ� �ִ´�
						S_Top++;
						Ch_Stack[S_Top] = Medium[i];
					}
				}
				if (Medium[i] == ')'){       // ')' �� �����ٸ� '(' ���� ������ ����ִ� �����ڸ�
					for (; Ch_Stack[S_Top] != '('; S_Top--){ // ��� ������ ���� Back �ִ´�
						B_Top++;
						Back[B_Top] = Ch_Stack[S_Top];
					}
					S_Top--;    // ���Ҹ� �����Ҿ� '(' ��ȣ�� back �� �ȵ��� ���ؼ� �����ٰ� ��������
				}
				if (Medium[i] == '\0'){  // ������ ������ ���� �����ٸ� ���ÿ� �ִ� ��� �����ڸ�
					for (; S_Top>-1; S_Top--){ // back �ڿ� �ٿ� �ִ´�
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
	int C_Top = -1;  // Cost �迭�� �ּҷ� ����� ����
	int i, address = 0; // address �� ���ڸ� ��ȯ ��Ű�� �� �ּ��� ��Ŀ���� ���� ���� ��Ŀ���� �̵���Ű�� ���ؼ�
	langth = strlen(Back);
	while (1){
		for (i = address; i <= langth; i++){  // address �� i �� ��� �������־�� �Ѵ� address �� ��Ŀ���� �̵������ֱ� 
			if (Back[i] == ' '){    // �����̴�
				i++;      // ���� ���� ������ ���� ���ؼ� ���� �����ְ�
				address = i;     // �̰� address �� �ְ� 
				break;      // ���� for ��ȯ�� ���߰� �ٽ� �����Ѵ�
			}
			if (Back[i] >= '0' && Back[i] <= '9'){  // ���ڸ� 
				C_Top++;
				Cost[C_Top] = atof(&Back[i]);  // ������ ���ڸ� double �� ��ȯ�ؼ� ���ÿ� �־��ش�
				while (Back[i] != ' '){   // �׸��� ��Ŀ���� ������ ������ Ȥ�� ���� ���� �ִ� �������� ����
					i++;
					address = i;
				}
				break;
			}
			if (Back[i] == '+'){     // + �����ڸ� ������
				Cost[C_Top - 1] = Cost[C_Top - 1] + Cost[C_Top]; // ���ÿ� �ִ� �ٷ����Ͱ� ���ε����� �����ش�
				C_Top--;         // �׸��� ���� �ּҸ� ��ĭ ������ �ؾ� �ٽ� ���ο�
				i++;          // ���ڰ� ����
				address = i;
				break;
			}
			if (Back[i] == '-'){     // ������ �κе� �Ȱ���
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