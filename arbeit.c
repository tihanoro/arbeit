#include<stdio.h>
#include<stdlib.h>

#define MAX_STRINGS 100   //一度に読み込める文字の最大値

//構造体の宣言
typedef struct ARBEIT{
    char number[6];   //番号
    char name[21];    //氏名
    int time_yen;     //時給
    int month_time4;  //4月の勤務時間
    int month_time5;  //5月の勤務時間
    int month_time6;  //6月の勤務時間
    int month_yen4;   //4月の給料
    int month_yen5;   //5月の給料
    int month_yen6;   //6月の給料
    int all_time;     //合計勤務時間
    int all_yen;      //合計給料
    struct ARBEIT *next;
} DATA;

char *scan_ARBEIT(DATA *root, FILE *fp);
void print_ARBEIT(DATA *root, FILE *fp);
void free_ARBEIT(DATA *root);

int main(int argc,char **argv){
    //変数の宣言
    DATA *root;
    int num,i;
    FILE *fp_in,*fp_out;
    char buf[MAX_STRINGS];

    //ファイルを開く
    printf("入力するファイル:%s\n",argv[1]);
    if((fp_in = fopen(argv[1],"r"))==NULL){
        printf("error\n");
        return 1;
    }
    printf("出力するファイル:%s\n",argv[2]);
    if((fp_out = fopen(argv[2],"w"))==NULL){
        printf("error\n");
        return 1;
    }
    
    //線形リストのroot
    root = (DATA *)malloc(num*sizeof(DATA));
    if(root == NULL){
        fprintf(stderr,"メモリの確保に失敗\n");
        return 1;
    }
    root->next = NULL;

    //データの入力
    while(scan_ARBEIT(root,fp_in) != NULL) ;

    //データの出力
    print_ARBEIT(root,fp_out);

    //ファイルを閉じる
    fclose(fp_in);
    fclose(fp_out);
    
    //開放
    free_ARBEIT(root);
    
    return 0;
}


//データを入力する関数
char *scan_ARBEIT(DATA *root, FILE *fp){
    DATA *data;
    char *ans;
    char buf[MAX_STRINGS];
    data = (DATA *)malloc(sizeof(DATA));
    data->next = root->next;
    root->next = data;
    
    ans = fgets(buf,MAX_STRINGS,fp);
    sscanf(buf,"%s %s %d %d %d %d",data->number,data->name,&data->time_yen,&data->month_time4,&data->month_time5,&data->month_time6);

    //月の給料の計算
    data->month_yen4 = data->month_time4*data->time_yen;
    data->month_yen5 = data->month_time5*data->time_yen;
    data->month_yen6 = data->month_time6*data->time_yen;
    
    //合計勤務時間と合計給料の計算
    data->all_time = data->month_time4+data->month_time5+data->month_time6;
    data->all_yen = data->month_yen4+data->month_yen5+data->month_yen6;

    return ans;
}


//データを出力する関数
void print_ARBEIT(DATA *root, FILE *fp){
    DATA *data;
    data = root->next;
    fprintf(fp,"No.   | Name                 | Apr.   | May    | June   | T.Time | T.Salary \n");
    fprintf(fp,"------+----------------------+--------+--------+--------+--------+---------\n");
    fprintf(stdout,"No.   | Name                 | Apr.   | May    | June   | T.Time | T.Salary \n");
    fprintf(stdout,"------+----------------------+--------+--------+--------+--------+---------\n");

    while(data!=NULL){
        fprintf(fp,"%-5s | %-20s | %6d | %6d | %6d | %6d | %8d\n",data->number,data->name,data->month_yen4,data->month_yen5,data->month_yen6,data->all_time,data->all_yen);
        fprintf(stdout,"%-5s | %-20s | %6d | %6d | %6d | %6d | %8d\n",data->number,data->name,data->month_yen4,data->month_yen5,data->month_yen6,data->all_time,data->all_yen);
        data = data->next;
    }

    return;
}

//線形リストを解放する関数
void free_ARBEIT(DATA *root){
    if(root->next != NULL) free_ARBEIT(root->next);
    free(root);
    return;
}