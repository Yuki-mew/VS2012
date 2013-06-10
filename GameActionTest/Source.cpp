#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int A_HP = 25;
int B_HP = 25;
int attA=5, defA=5, techA=5;
int attB=5, defB=5, techB=5;

typedef struct {
	int num;
	char name[10];
	int str;
	int def;
} Card;

Card card[3]= {
	{0, "Attack", 4, 2},
	{1, "Defence", 2, 4},
	{2, "Technique", 3, 3}
};

int random_dice(int i){
	int random;
//	srand((unsigned)time(NULL));
	random = rand() % i;
	return random;
}

void Battle(Card A, Card B){
	int Dam, Adice, Bdice, Adam, Bdam;

	switch(A.num){
	case 0:			//A���uAttack�v
		switch(B.num){
		case 0:		//B���uAttack�v �� ��������
			printf("���������ł��B\n");
			Adice = random_dice(8);
			Bdice = random_dice(8);
			printf("���Ȃ��̍U����/�h���:%d\n", Adice);
			printf("CPU�̍U����/�h���:%d\n", Bdice);
			Dam = Adice - Bdice;
			if(Dam > 0){
				printf("\nCPU��%d�̃_���[�W\n", abs(Dam));
				B_HP -= Dam;
			} else {
				printf("\n���Ȃ���%d�̃_���[�W\n", abs(Dam));
				A_HP += Dam;
			}
		break;
		case 1:		//B���uDefence�v�@���@A�̕���
			printf("���Ȃ��̕����ł��B\n");
			Adice = random_dice(8);
			Bdice = random_dice(8);
			Adam = A.def + Adice;
			Bdam = B.str + Bdice;
			printf("���Ȃ��̖h���:%d\n", Adam);
			printf("CPU�̍U����:%d\n", Bdam);
			Dam = Bdam - Adam;
			if(Dam > 0){
				printf("\n���Ȃ���%d�̃_���[�W\n", Dam);
				A_HP -= Dam;
			} else {
				printf("\n���Ȃ���0�̃_���[�W\n");
			}
			break;
		case 2:		//B���uTechnique�v�@���@A�̏���
			printf("���Ȃ��̏����ł��B\n");
			Adice = random_dice(8);
			Bdice = random_dice(8);
			Adam = A.str + Adice;
			Bdam = B.def + Bdice;
			printf("���Ȃ��̍U����:%d\n", Adam);
			printf("CPU�̖h���:%d\n", Bdam);
			Dam = Adam - Bdam;
			if(Dam > 0){
				printf("\nCPU��%d�̃_���[�W\n", Dam);
				B_HP -= Dam;
			} else {
				printf("\nCPU��0�̃_���[�W\n");
			}
		break;
		}
	break;

	case 1:			//A���uDefence�v
		switch(B.num){
		case 0:		//B���uAttack�v �� A�̏���
			printf("���Ȃ��̏����ł��B\n");
			Adice = random_dice(8);
			Bdice = random_dice(8);
			Adam = A.str + Adice;
			Bdam = B.def + Bdice;
			printf("���Ȃ��̍U����:%d\n", Adam);
			printf("CPU�̖h���:%d\n", Bdam);
			Dam = Adam - Bdam;
			if(Dam > 0){
				printf("\nCPU��%d�̃_���[�W\n", Dam);
				B_HP -= Dam;
			} else {
				printf("\nCPU��0�̃_���[�W\n");
			}
		break;
		case 1:		//B���uDefence�v�@���@��������
			printf("���������ł��B\n");
			Adice = random_dice(8);
			Bdice = random_dice(8);
			printf("���Ȃ��̍U����/�h���:%d\n", Adice);
			printf("CPU�̍U����/�h���:%d\n", Bdice);
			Dam = Adice - Bdice;
			if(Dam > 0){
				printf("\nCPU��%d�̃_���[�W\n", abs(Dam));
				B_HP -= Dam;
			} else {
				printf("\n���Ȃ���%d�̃_���[�W\n", abs(Dam));
				A_HP += Dam;
			}
		break;
		case 2:		//B���uTechnique�v�@���@A�̕���
			printf("���Ȃ��̕����ł��B\n");
			Adice = random_dice(8);
			Bdice = random_dice(8);
			Adam = A.def + Adice;
			Bdam = B.str + Bdice;
			printf("���Ȃ��̖h���:%d\n", Adam);
			printf("CPU�̍U����:%d\n", Bdam);
			Dam = Bdam - Adam;
			if(Dam > 0){
				printf("\n���Ȃ���%d�̃_���[�W\n", Dam);
				A_HP -= Dam;
			} else {
				printf("\n���Ȃ���0�̃_���[�W\n");
			}
		break;
		}
	break;

	case 2:			//A���uTechnique�v
		switch(B.num){
		case 0:		//B���uAttack�v �� A�̕���
			printf("���Ȃ��̕����ł��B\n");
			Adice = random_dice(8);
			Bdice = random_dice(8);
			Adam = A.def + Adice;
			Bdam = B.str + Bdice;
			printf("���Ȃ��̖h���:%d\n", Adam);
			printf("CPU�̍U����:%d\n", Bdam);
			Dam = Bdam - Adam;
			if(Dam > 0){
				printf("\n���Ȃ���%d�̃_���[�W\n", Dam);
				A_HP -= Dam;
			} else {
				printf("\n���Ȃ���0�̃_���[�W\n");
			}
			break;
		case 1:		//B���uDefence�v�@���@A�̏���
			printf("���Ȃ��̏����ł��B\n");
			Adice = random_dice(8);
			Bdice = random_dice(8);
			Adam = A.str + Adice;
			Bdam = B.def + Bdice;
			printf("���Ȃ��̍U����:%d\n", Adam);
			printf("CPU�̖h���:%d\n", Bdam);
			Dam = Adam - Bdam;
			if(Dam > 0){
				printf("\nCPU��%d�̃_���[�W\n", Dam);
				B_HP -= Dam;
			} else {
				printf("\nCPU��0�̃_���[�W\n");
			}
				break;
		case 2:		//B���uTechnique�v�@���@��������
			printf("���������ł��B\n");
			Adice = random_dice(8);
			Bdice = random_dice(8);
			printf("���Ȃ��̍U����/�h���:%d\n", Adice);
			printf("CPU�̍U����/�h���:%d\n", Bdice);
			Dam = Adice - Bdice;
			if(Dam > 0){
				printf("\nCPU��%d�̃_���[�W\n", abs(Dam));
				B_HP -= Dam;
			} else {
				printf("\n���Ȃ���%d�̃_���[�W\n", abs(Dam));
				A_HP += Dam;
			}
			break;
		}
	break;
	}
}

int BcardChose()
{
	int temp;
	while(1){
		temp = random_dice(3);
		if((temp==0) && (attB>0)){
			attB-=1;
			return 0;
		} else if ((temp==1) && (defB>0)){
			defB-=1;
			return 1;
		} else if ((temp==2) && (techB>0)){
			techB-=1;
			return 2;
		}
	}
}

int CheckCardStock(int num){
	switch(num)
	{
	case 0:
		if(attA>0){
			attA -= 1;
			return 0;
		} else {
			return -1;
		}
		break;
	case 1:
		if(defA>0){
			defA -= 1;
			return 1;
		} else {
			return -1;
		}
		break;
	case 2:
		if(techA>0){
			techA -= 1;
			return 2;
		} else {
			return -1;
		}
		break;
	}
}

int main(void){
	int i,j,checkA;

	while( ((A_HP > 0) || (B_HP > 0)) && !(attA==0 && defA==0 && techA==0)){	
		system("cls");
		printf("- - - - - - - - - - - - - - - - - -\n");
		printf("���Ȃ��̎c��HP ���� %d\n", A_HP);
		printf("�@�@Attack==%d�@�@Defence==%d�@�@Technique==%d\n", attA, defA, techA);
		printf("CPU�̎c��HP ���� %d\n", B_HP);
		printf("�@�@Attack==%d�@�@Defence==%d�@�@Technique==%d\n", attB, defB, techB);
		printf("- - - - - - - - - - - - - - - - - -\n");

		printf("\n0�cAttack, 1�cDefence, 2�cTechnique\n");
		printf("�J�[�h��I�����Ă�������:");
		scanf_s("%d", &i);
		checkA = CheckCardStock(i);

		if((i!=0) && (i!=1) && (i!=2)){
			printf("\n\n0 or 1 or 2 ����͂��Ă�������\n");
		} else if(checkA==-1){
			printf("\n\n�X�g�b�N������܂���B\n\n", card[checkA].name);
		} else {
			printf("���Ȃ���%s��I�����܂����B\n", card[checkA].name);
			j = BcardChose();
			printf("CPU��%s��I�����܂���\n", card[j].name);
			printf("\n\n�o�g�����J�n���܂�\n\n");
			Battle(card[checkA], card[j]);
		}
		system("pause");
	}

	if (B_HP <= 0){
		system("cls");
		printf("\n\n���Ȃ���HP%d\n", A_HP);
		printf("CPU��HP%d\n", B_HP);		
		printf("\n\n���߂łƂ��������܂�! ���Ȃ��̏����ł�!\n\n\n");
		system("pause");
	} else if (A_HP <= 0){
		system("cls");
		printf("\n\n���Ȃ���HP%d\n", A_HP);
		printf("CPU��HP%d\n", B_HP);		
		printf("\n\n�c�O�ł����A���Ȃ��̕����ł��B\n\n\n");
		system("pause");
	}
	
	if(attA==0 && defA==0 && techA==0){
		if(A_HP == B_HP){
			system("cls");
			printf("\n\n���Ȃ���HP%d\n", A_HP);
			printf("CPU��HP%d\n", B_HP);
			printf("\n\n���������ł��B\n\n\n");
			system("pause");
		} else if(A_HP > B_HP){
			system("cls");
			printf("\n\n���Ȃ���HP%d\n", A_HP);
			printf("CPU��HP%d\n", B_HP);
			printf("\n\n���߂łƂ��������܂�! ���Ȃ��̏����ł�!\n\n\n");
			system("pause");
		} else {
			system("cls");
			printf("\n\n���Ȃ���HP%d\n", A_HP);
			printf("CPU��HP%d\n", B_HP);
			printf("\n\n�c�O�ł����A���Ȃ��̕����ł��B\n\n\n");
			system("pause");
		}
	}

	return 0;
}