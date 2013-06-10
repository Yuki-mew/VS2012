#ifndef CARDSETTING_H

#define CARDSETTING_H

typedef enum{
	eAtt,
	eDef,
	eTech,

	eCard_Num,
}eCard;

extern int IH_Card[4];

void CS_Initialize();
void CS_Finalize();

void CS_CardSet();
void CS_CardPlace_Update();
void CS_DrawCard();
void CS_CardOutSide();
void CS_SelectedCard_Draw( int, int);
void CS_CardPlaceReset();

#endif
