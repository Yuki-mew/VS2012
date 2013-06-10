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
	case 0:			//Aが「Attack」
		switch(B.num){
		case 0:		//Bが「Attack」 ＝ 引き分け
			printf("引き分けです。\n");
			Adice = random_dice(8);
			Bdice = random_dice(8);
			printf("あなたの攻撃力/防御力:%d\n", Adice);
			printf("CPUの攻撃力/防御力:%d\n", Bdice);
			Dam = Adice - Bdice;
			if(Dam > 0){
				printf("\nCPUに%dのダメージ\n", abs(Dam));
				B_HP -= Dam;
			} else {
				printf("\nあなたに%dのダメージ\n", abs(Dam));
				A_HP += Dam;
			}
		break;
		case 1:		//Bが「Defence」　＝　Aの負け
			printf("あなたの負けです。\n");
			Adice = random_dice(8);
			Bdice = random_dice(8);
			Adam = A.def + Adice;
			Bdam = B.str + Bdice;
			printf("あなたの防御力:%d\n", Adam);
			printf("CPUの攻撃力:%d\n", Bdam);
			Dam = Bdam - Adam;
			if(Dam > 0){
				printf("\nあなたに%dのダメージ\n", Dam);
				A_HP -= Dam;
			} else {
				printf("\nあなたに0のダメージ\n");
			}
			break;
		case 2:		//Bが「Technique」　＝　Aの勝ち
			printf("あなたの勝ちです。\n");
			Adice = random_dice(8);
			Bdice = random_dice(8);
			Adam = A.str + Adice;
			Bdam = B.def + Bdice;
			printf("あなたの攻撃力:%d\n", Adam);
			printf("CPUの防御力:%d\n", Bdam);
			Dam = Adam - Bdam;
			if(Dam > 0){
				printf("\nCPUに%dのダメージ\n", Dam);
				B_HP -= Dam;
			} else {
				printf("\nCPUに0のダメージ\n");
			}
		break;
		}
	break;

	case 1:			//Aが「Defence」
		switch(B.num){
		case 0:		//Bが「Attack」 ＝ Aの勝ち
			printf("あなたの勝ちです。\n");
			Adice = random_dice(8);
			Bdice = random_dice(8);
			Adam = A.str + Adice;
			Bdam = B.def + Bdice;
			printf("あなたの攻撃力:%d\n", Adam);
			printf("CPUの防御力:%d\n", Bdam);
			Dam = Adam - Bdam;
			if(Dam > 0){
				printf("\nCPUに%dのダメージ\n", Dam);
				B_HP -= Dam;
			} else {
				printf("\nCPUに0のダメージ\n");
			}
		break;
		case 1:		//Bが「Defence」　＝　引き分け
			printf("引き分けです。\n");
			Adice = random_dice(8);
			Bdice = random_dice(8);
			printf("あなたの攻撃力/防御力:%d\n", Adice);
			printf("CPUの攻撃力/防御力:%d\n", Bdice);
			Dam = Adice - Bdice;
			if(Dam > 0){
				printf("\nCPUに%dのダメージ\n", abs(Dam));
				B_HP -= Dam;
			} else {
				printf("\nあなたに%dのダメージ\n", abs(Dam));
				A_HP += Dam;
			}
		break;
		case 2:		//Bが「Technique」　＝　Aの負け
			printf("あなたの負けです。\n");
			Adice = random_dice(8);
			Bdice = random_dice(8);
			Adam = A.def + Adice;
			Bdam = B.str + Bdice;
			printf("あなたの防御力:%d\n", Adam);
			printf("CPUの攻撃力:%d\n", Bdam);
			Dam = Bdam - Adam;
			if(Dam > 0){
				printf("\nあなたに%dのダメージ\n", Dam);
				A_HP -= Dam;
			} else {
				printf("\nあなたに0のダメージ\n");
			}
		break;
		}
	break;

	case 2:			//Aが「Technique」
		switch(B.num){
		case 0:		//Bが「Attack」 ＝ Aの負け
			printf("あなたの負けです。\n");
			Adice = random_dice(8);
			Bdice = random_dice(8);
			Adam = A.def + Adice;
			Bdam = B.str + Bdice;
			printf("あなたの防御力:%d\n", Adam);
			printf("CPUの攻撃力:%d\n", Bdam);
			Dam = Bdam - Adam;
			if(Dam > 0){
				printf("\nあなたに%dのダメージ\n", Dam);
				A_HP -= Dam;
			} else {
				printf("\nあなたに0のダメージ\n");
			}
			break;
		case 1:		//Bが「Defence」　＝　Aの勝ち
			printf("あなたの勝ちです。\n");
			Adice = random_dice(8);
			Bdice = random_dice(8);
			Adam = A.str + Adice;
			Bdam = B.def + Bdice;
			printf("あなたの攻撃力:%d\n", Adam);
			printf("CPUの防御力:%d\n", Bdam);
			Dam = Adam - Bdam;
			if(Dam > 0){
				printf("\nCPUに%dのダメージ\n", Dam);
				B_HP -= Dam;
			} else {
				printf("\nCPUに0のダメージ\n");
			}
				break;
		case 2:		//Bが「Technique」　＝　引き分け
			printf("引き分けです。\n");
			Adice = random_dice(8);
			Bdice = random_dice(8);
			printf("あなたの攻撃力/防御力:%d\n", Adice);
			printf("CPUの攻撃力/防御力:%d\n", Bdice);
			Dam = Adice - Bdice;
			if(Dam > 0){
				printf("\nCPUに%dのダメージ\n", abs(Dam));
				B_HP -= Dam;
			} else {
				printf("\nあなたに%dのダメージ\n", abs(Dam));
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
		printf("あなたの残りHP ＝＝ %d\n", A_HP);
		printf("　　Attack==%d　　Defence==%d　　Technique==%d\n", attA, defA, techA);
		printf("CPUの残りHP ＝＝ %d\n", B_HP);
		printf("　　Attack==%d　　Defence==%d　　Technique==%d\n", attB, defB, techB);
		printf("- - - - - - - - - - - - - - - - - -\n");

		printf("\n0…Attack, 1…Defence, 2…Technique\n");
		printf("カードを選択してください:");
		scanf_s("%d", &i);
		checkA = CheckCardStock(i);

		if((i!=0) && (i!=1) && (i!=2)){
			printf("\n\n0 or 1 or 2 を入力してください\n");
		} else if(checkA==-1){
			printf("\n\nストックがありません。\n\n", card[checkA].name);
		} else {
			printf("あなたは%sを選択しました。\n", card[checkA].name);
			j = BcardChose();
			printf("CPUは%sを選択しました\n", card[j].name);
			printf("\n\nバトルを開始します\n\n");
			Battle(card[checkA], card[j]);
		}
		system("pause");
	}

	if (B_HP <= 0){
		system("cls");
		printf("\n\nあなたのHP%d\n", A_HP);
		printf("CPUのHP%d\n", B_HP);		
		printf("\n\nおめでとうございます! あなたの勝ちです!\n\n\n");
		system("pause");
	} else if (A_HP <= 0){
		system("cls");
		printf("\n\nあなたのHP%d\n", A_HP);
		printf("CPUのHP%d\n", B_HP);		
		printf("\n\n残念ですが、あなたの負けです。\n\n\n");
		system("pause");
	}
	
	if(attA==0 && defA==0 && techA==0){
		if(A_HP == B_HP){
			system("cls");
			printf("\n\nあなたのHP%d\n", A_HP);
			printf("CPUのHP%d\n", B_HP);
			printf("\n\n引き分けです。\n\n\n");
			system("pause");
		} else if(A_HP > B_HP){
			system("cls");
			printf("\n\nあなたのHP%d\n", A_HP);
			printf("CPUのHP%d\n", B_HP);
			printf("\n\nおめでとうございます! あなたの勝ちです!\n\n\n");
			system("pause");
		} else {
			system("cls");
			printf("\n\nあなたのHP%d\n", A_HP);
			printf("CPUのHP%d\n", B_HP);
			printf("\n\n残念ですが、あなたの負けです。\n\n\n");
			system("pause");
		}
	}

	return 0;
}