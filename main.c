#include<stdio.h>
#include<stdlib.h>

#define MAX_STRINGS 100   //一度に読み込める文字の最大値

//構造体の宣言
typedef struct {
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
} DATA;

DATA scan_DATA(FILE *fp);
void print_DATA(DATA *data, int num, FILE *fp);

int main(int argc,char **argv){
    //変数の宣言
    DATA *data;
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

    //入力人数の設定
    fgets(buf,MAX_STRINGS,fp_in);
    num = atoi(buf);
    
    //DATA型配列の動的確保
    data = (DATA *) malloc(num*sizeof(DATA));
    if(data == NULL){
        fprintf(stderr,"メモリの確保に失敗\n");
        return 1;
    }
    

    //データの入力
    for(i=0;i<num;i++){
        printf("%d人目の入力 :",i+1);
        data[i] = scan_DATA(fp_in);
        printf("完了\n");
    }

    //データの出力
    print_DATA(data,num,fp_out);

    //ファイルを閉じる
    fclose(fp_in);
    fclose(fp_out);
    
    //開放
    free(data);
    
    return 0;
}


//データを入力する関数
DATA scan_DATA(FILE *fp){
    DATA data;
    
    fscanf(fp,"%s %s %d %d %d %d",data.number,data.name,&data.time_yen,&data.month_time4,&data.month_time5,&data.month_time6);

    //月の給料の計算
    data.month_yen4 = data.month_time4*data.time_yen;
    data.month_yen5 = data.month_time5*data.time_yen;
    data.month_yen6 = data.month_time6*data.time_yen;
    
    //合計勤務時間と合計給料の計算
    data.all_time = data.month_time4+data.month_time5+data.month_time6;
    data.all_yen = data.month_yen4+data.month_yen5+data.month_yen6;

    return data;
}


//データを出力する関数
void print_DATA(DATA *data, int num, FILE *fp){
    int i;
    fprintf(fp,"No.   | Name                 | Apr.   | May    | June   | T.Time | T.Salary \n");
    fprintf(fp,"------+----------------------+--------+--------+--------+--------+---------\n");
    fprintf(stdout,"No.   | Name                 | Apr.   | May    | June   | T.Time | T.Salary \n");
    fprintf(stdout,"------+----------------------+--------+--------+--------+--------+---------\n");

    for(i=0;i<num;i++){
        fprintf(fp,"%-5s | %-20s | %6d | %6d | %6d | %6d | %8d\n",data[i].number,data[i].name,data[i].month_yen4,data[i].month_yen5,data[i].month_yen6,data[i].all_time,data[i].all_yen);
	fprintf(stdout,"%-5s | %-20s | %6d | %6d | %6d | %6d | %8d\n",data[i].number,data[i].name,data[i].month_yen4,data[i].month_yen5,data[i].month_yen6,data[i].all_time,data[i].all_yen);
    }

    return;
}
