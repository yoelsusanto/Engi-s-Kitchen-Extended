#include <curses.h>
#include "display.h"

/* Kelompok Tampilan */
/* Kamus Tampilan*/
    /* Pointer display */
    WINDOW *name_disp, *money_disp, *life_disp, *time_disp, *waitcust_disp, *order_disp, *map_disp, *food_disp, *hand_disp, *command_disp, *tree_disp;

    /* Ukuran display */
    int disp_height, disp_width;
    int name_height, name_width, money_height, money_width, life_height, life_width, time_height, time_width;
    int waitcust_height, waitcust_width, order_height, order_width, map_height, map_width, food_height, food_width, hand_height, hand_width;
    int command_height, command_width;
    int tree_height, tree_width;

    /* Cursor */
    int start_y, start_x;
    int player_y, player_x;

    char user_input[10];

void initLayout(){
    /* CURSES START */
    initscr();
    // cbreak();
    // raw();
    // noecho();
    setLayout();
    refresh();
    printLayout();
    updateLayout();
}

void setLayout(){
    /* Set Ukuran Display */
        name_height = 3;
        name_width = 25;
        money_height = name_height;
        money_width = 25;
        life_height = name_height;
        life_width = 25;
        time_height = name_height;
        time_width = 25;
        waitcust_height = 11;
        waitcust_width = name_width;
        order_height = 11;
        order_width = name_width;
        map_height = waitcust_height + order_height;
        map_width = 50;
        food_height = waitcust_height;
        food_width = 25;
        hand_height = order_height;
        hand_width = food_width;
        command_height = 3;
        command_width = order_width + map_width + hand_width;

        tree_height = 28;
        tree_width = 50;

        disp_height = 10;
        disp_width = 40;

        start_y = 0;
        start_x = 0;
}

void printLayout(){
    /* Print Layout */
        start_y = 0;
        start_x = 0;

        name_disp = newwin(name_height, name_width, start_y, start_x);
        box(name_disp,0,0);
        wrefresh(name_disp);

        start_x += name_width;
        money_disp = newwin(money_height, money_width, start_y, start_x);
        box(money_disp,0,0);
        wrefresh(money_disp);

        start_x += money_width;
        life_disp = newwin(life_height, life_width, start_y, start_x);
        box(life_disp,0,0);
        wrefresh(life_disp);

        start_x += life_width;
        time_disp = newwin(time_height, time_width, start_y, start_x);
        box(time_disp,0,0);
        wrefresh(time_disp);

        start_x = 0;
        start_y += name_height;
        waitcust_disp = newwin(waitcust_height, waitcust_width, start_y, start_x);
        box(waitcust_disp,0,0);
        wrefresh(waitcust_disp);

        start_x += waitcust_width;
        map_disp = newwin(map_height, map_width, start_y, start_x);
        box(map_disp,0,0);
        wrefresh(map_disp);

        start_x += map_width;
        food_disp = newwin(food_height, food_width, start_y, start_x);
        box(food_disp,0,0);
        wrefresh(food_disp);

        start_x = 0;
        start_y += waitcust_height;
        order_disp = newwin(order_height, order_width, start_y, start_x);
        box(order_disp,0,0);
        wrefresh(order_disp);

        start_x += order_width + map_width;
        hand_disp = newwin(hand_height, hand_width, start_y, start_x);
        box(hand_disp,0,0);
        wrefresh(hand_disp);

        start_x = 0;
        start_y += order_height;
        command_disp = newwin(command_height, command_width, start_y, start_x);
        box(command_disp,0,0);
        wrefresh(command_disp);
}

void CursePrintTreeRec (BinTree P, int level, int h, int *y, int x) {
	if (!IsTreeEmpty(P)) {
		int i;
		// for (i = 1; i <= level * h; i++)
		// 	if (i < level*h-(h-1))
		// 		mvwprintw(tree_disp,y,x," ");
		// 	else if (i == level*h-(h-1))
		// 		mvwprintw(tree_disp,y,x,"`");
		// 	else
		// 		mvwprintw(tree_disp,y,x,"-");
		if (IsTreeOneElmt(P))
			mvwprintw(tree_disp,*y,x,"%s", JenisMakanan[Akar(P)]);
		else
			mvwprintw(tree_disp,*y,x,"%s", JenisBahan[Akar(P)]);

		if (!IsTreeEmpty(Left(P))){
			(*y)++;
			CursePrintTreeRec(Left(P), level+1, h, y, x+h);
		}
		if (!IsTreeEmpty(Right(P))){
			(*y)++;
			CursePrintTreeRec(Right(P), level+1, h, y, x+h);
		}
	}
}

void CursePrintTree(BinTree P){
	int y;

	tree_disp = newwin(tree_height, tree_width, 2, 24);
    box(tree_disp,0,0);
    y = 1;
	CursePrintTreeRec(P, 0, 4, &y, 1);

	// mvwprintw(tree_disp, 0, 0, "#Recipe Tree");
	wattron(tree_disp, A_UNDERLINE);
	mvwprintw(tree_disp, tree_height-2, 1, "Press Enter to close recipe");
	wattroff(tree_disp, A_UNDERLINE);
	wrefresh(tree_disp);
	noecho();
	while (wgetch(tree_disp) != ENTER){}
	delwin(tree_disp);
	wrefresh(tree_disp);
	printLayout();
	updateLayout();
	echo();
}

void CursePrintQC(TypeQueueCustomer QC){
	int i;
	int y, x;

	x = 1;
	y = 2;

	if (!IsEmptyQC(QC))
		for(i = Head(QC)-1; i <= Tail(QC); i++){
			// printf("%d %d %d %d %u\n", QC.Customer[i].Id, QC.Customer[i].NoMeja, QC.Customer[i].Kesabaran, QC.Customer[i].JmlOrang, QC.Customer[i].Star);
			if (QC.Customer[i].Star)
				mvwprintw(waitcust_disp, y + i, x, "i=%d %d (%d) (Star)", i, QC.Customer[i].Id, QC.Customer[i].Kesabaran);
			else
				mvwprintw(waitcust_disp, y + i, x, "i=%d %d (%d)", i, QC.Customer[i].Id, QC.Customer[i].Kesabaran);
		}
	else
		mvwprintw(waitcust_disp, y, x, "There's no one here");
}

void CursePrintTabOrder(TabOrder T){
	// Kamus Lokal
	int x,y;
	int maxx, maxy;

	// Algoritma
	x = 1;
	y = 2;
	getmaxyx(order_disp, maxy, maxx);

  	for (int i=1; i<=Neff(T); i++){
  		// Tidak akan lanjut mencetak elemen jika window order_disp sudah penuh
  		if (y < maxy-1){ 
    		mvwprintw(order_disp, y, x, "%s, %d", JenisMakanan[ElmtArr(T, i).NoMenu], ElmtArr(T,i).NoMeja);
    		y++;
  		}
  	}

  	// Kasus jika elemen T melebihi batas window order_disp
  	if (y == maxy-1){
  		wattron(order_disp, A_UNDERLINE);
  		mvwprintw(order_disp, y, x, "etc...");
  		wattroff(order_disp, A_UNDERLINE);
  	}
}

void CurseTulisMatriks (Matriks M)
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/
{
    /* KAMUS LOKAL */
    matriksIndeks i, j;
    int x,y;

    /* ALGORITMA */
    x = 1;
    y = 1;

    wmove(map_disp, y,x);
    
    for(i=GetFirstIdxBrs(M);i<=GetLastIdxBrs(M);i++){

        for(j=GetFirstIdxKol(M);j<GetLastIdxKol(M);j++){
            wprintw(map_disp, "%c ", ElmtMat(M,i,j));
        }

        if(i==GetLastIdxBrs(M)){
            wprintw(map_disp, "%c", ElmtMat(M,i,GetLastIdxKol(M)));
        }
        else{
            wprintw(map_disp, "%c", ElmtMat(M,i,GetLastIdxKol(M)));
        }
        y++;
        wmove(map_disp, y,x);
    }
}

void CursePrintStack(WINDOW *win, Stack *Current, char opt)
{
    Stack ReverseStack;
    int Z;
    int y,x;
    int maxy,maxx;

    if(!IsEmptyStck(*Current)){
        /*Membuat salinan *Current*/
            CreateEmptyStck(&ReverseStack);
            do
            {
                Pop(&*Current,&Z);
                Push(&ReverseStack,Z);
            }
            while (!IsEmptyStck(*Current));

        /* Mencetak dan memasukkan kembali salinan *Current */
            x = 1;
            y = 2;
            getmaxyx(win,maxy,maxx);

            do{
                Pop(&ReverseStack, &Z);
                Push(&*Current, Z);
                if (y < maxy-1){
	                switch(opt){
	                	case 'h': mvwprintw(win, y, x, "%s", JenisBahan[Z]);
	                		break;
	                	case 't': mvwprintw(win, y, x, "%s", JenisMakanan[Z]);
	                }
                	y++;
            	}
                // printf("%c ", Z);
            }while (!IsEmptyStck(ReverseStack));

            if (y == maxy-1){
            	wattron(win, A_UNDERLINE);
            	mvwprintw(win, y, x, "etc...");
            	wattroff(win, A_UNDERLINE);
            }
    }
    else{
    	mvwprintw(win, 3, 1, "It's Empty, bro");
    }
}

void updateLayout(){
    /* Print data */
        wmove(name_disp, 1, 1);
        wprintw(name_disp, "<Name>"); // Display
        wrefresh(name_disp);

        wmove(money_disp, 1, 1);
        wprintw(money_disp, "Money: %ld", Money(GameData)); // Display
        wrefresh(money_disp);

        wmove(life_disp, 1, 1);
        wprintw(life_disp, "Life: %ld", Life(GameData)); // Display
        wrefresh(life_disp);

        wmove(time_disp, 1, 1);
        wprintw(time_disp, "Waktu: %ld", Waktu(GameData)); // Display
        wrefresh(time_disp);

        wmove(waitcust_disp, 1, 1);
        wattron(waitcust_disp, A_BOLD);
        wprintw(waitcust_disp, "Waiting Customer");
        wattroff(waitcust_disp, A_BOLD);
        CursePrintQC(QWaitingC);
        wrefresh(waitcust_disp);

        wmove(map_disp, 1, 1);
        CurseTulisMatriks(Room[1].Map); // Displaying the map
        wrefresh(map_disp);

        wmove(food_disp, 1, 1);
        wattron(food_disp, A_BOLD);
        wprintw(food_disp, "Food Stack");
        wattroff(food_disp, A_BOLD);
        CursePrintStack(food_disp, &Tray, 't'); // Displaying the food
        wrefresh(food_disp);

        wmove(order_disp, 1, 1);
        wattron(order_disp, A_BOLD);
        wprintw(order_disp, "Order");
        wattroff(order_disp, A_BOLD);
        CursePrintTabOrder(TabOrders);
        wrefresh(order_disp);

        wmove(hand_disp, 1, 1);
        wattron(hand_disp, A_BOLD);
        wprintw(hand_disp, "Hand");
        wattroff(hand_disp, A_BOLD);
        CursePrintStack(hand_disp, &Hand, 'h'); // Displaying what's on the hand
        wrefresh(hand_disp);

        start_x = 0;
        start_y = name_height + waitcust_height + order_height;
        command_disp = newwin(command_height, command_width, start_y, start_x);
        box(command_disp,0,0);

        mvprintw(start_y + 3,0,"Type EXIT to stop");
        refresh();

        wmove(command_disp, 1, 1);
        wattron(command_disp, A_BOLD);
        wprintw(command_disp, "Command: ");
        wattroff(command_disp, A_BOLD);
        wrefresh(command_disp);
}

void GetCommand(){
    CursorOnCommand();
    CurseBacaCommand();
    updateLayout();
}

void CursorOnCommand(){
    // wmove(command_disp, 1, 10); // memindah cursor ke posisi (10,1) relatif terhadap command_disp
    wmove(command_disp, 1, 10);
    wrefresh(command_disp);
}

void endLayout(){
    endwin();
    /* Terminate curses */
}

/* Kelompok MesinKata MesinKar */

void CurseADVCommand()
{
  /* Algoritma */
  CCommand = wgetch(command_disp);
  EOP = (CCommand == ENTER);
}

void CurseBacaCommand()
/* Procedure yang digunakan */
/* I.S. : CC sembarang 
   F.S. : EndKata = true, dan CC = MARK; 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
{
  STARTCommand();
  switch (CCommand)
  {
    case ENTER:
    {
      EndCommand = true;
      break;
    }
    default :
    {
      EndCommand = false;
      // printf("salin\n");
      CurseSalinCommand();
    }
  }
}

void CurseSalinCommand()
/* Mengakuisisi command dari console, menyimpan dalam CCommand
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CCommand berisi kata yang sudah diakuisisi; 
          CC = \n */
{
  int i;
  //Algoritma
  i=1;
  do
  {
    // printf("%c\n",CC);
    if (i<=NMax)
    {
      Command.TabKata[i] = CCommand;
      i++;
    }
    CurseADVCommand();
  } while (CCommand!=ENTER);
  i--;
  Command.Length = i;
}